package SPVM::Builder::C;

use strict;
use warnings;
use Carp 'croak', 'confess';

use SPVM::Builder::Util;

use ExtUtils::CBuilder;
use File::Copy 'copy', 'move';
use File::Path 'mkpath';
use DynaLoader;

use File::Basename 'dirname', 'basename';

sub new {
  my $class = shift;
  
  my $self = {@_};
  
  return bless $self, $class;
}

sub category { shift->{category} }

sub quiet { shift->{quiet} }

sub builder { shift->{builder} }

sub build {
  my ($self, $opt) = @_;
  
  my $package_names = $self->builder->get_package_names;
  for my $package_name (@$package_names) {
    
    my $category = $self->{category};
    my $sub_names;
    if ($category eq 'native') {
      $sub_names = $self->builder->get_native_sub_names($package_name)
    }
    elsif ($category eq 'precompile') {
      $sub_names = $self->builder->get_precompile_sub_names($package_name)
    }
    
    if (@$sub_names) {
      # Shared library is already installed in distribution directory
      my $shared_lib_path = $self->get_shared_lib_path_dist($package_name);
      
      # Try runtime compile if shared library is not found
      unless (-f $shared_lib_path) {
        if ($category eq 'native') {
          $self->build_shared_lib_native_runtime($package_name, $sub_names);
        }
        elsif ($category eq 'precompile') {
          $self->build_shared_lib_precompile_runtime($package_name, $sub_names);
        }
        $shared_lib_path = $self->get_shared_lib_path_runtime($package_name);
      }
      $self->bind_subs($shared_lib_path, $package_name, $sub_names);
    }
  }
}

sub copy_shared_lib_to_build_dir {
  my ($self, $package_name, $category) = @_;
  
  my $shared_lib_path = $self->get_shared_lib_path_dist($package_name);
  
  my $shared_lib_rel_path = SPVM::Builder::Util::convert_package_name_to_shared_lib_rel_file($package_name, $category);
  
  my $build_dir = $self->builder->{build_dir};
  
  my $shared_lib_build_dir_path = "$build_dir/lib/$shared_lib_rel_path";
  
  my $shared_lib_build_dir_path_dir = dirname $shared_lib_build_dir_path;
  
  mkpath $shared_lib_build_dir_path_dir;
  
  copy $shared_lib_path, $shared_lib_build_dir_path
    or croak "Can't copy $shared_lib_path to $shared_lib_build_dir_path";
}

sub get_shared_lib_path_runtime {
  my ($self, $package_name) = @_;
  
  my $shared_lib_rel_file = SPVM::Builder::Util::convert_package_name_to_shared_lib_rel_file($package_name, $self->category);
  my $build_dir = $self->{build_dir};
  my $output_dir = "$build_dir/lib";
  my $shared_lib_path = "$output_dir/$shared_lib_rel_file";
  
  return $shared_lib_path;
}

sub create_cfunc_name {
  my ($self, $package_name, $sub_name) = @_;
  
  my $category = $self->category;
  my $prefix = 'SPVM_' . uc($category) . '_';
  
  # Precompile Subroutine names
  my $sub_abs_name_under_score = "${package_name}::$sub_name";
  $sub_abs_name_under_score =~ s/:/_/g;
  my $cfunc_name = "$prefix$sub_abs_name_under_score";
  
  return $cfunc_name;
}

sub bind_subs {
  my ($self, $shared_lib_path, $package_name, $sub_names) = @_;
  
  for my $sub_name (@$sub_names) {
    my $sub_abs_name = "${package_name}::$sub_name";

    my $cfunc_name = $self->create_cfunc_name($package_name, $sub_name);
    my $cfunc_address = SPVM::Builder::Util::get_shared_lib_func_address($shared_lib_path, $cfunc_name);
    
    unless ($cfunc_address) {
      my $cfunc_name = $self->create_cfunc_name($package_name, $sub_name);
      $cfunc_name =~ s/:/_/g;
      confess "Can't find function address of $cfunc_name";
    }
    
    my $category = $self->category;
    if ($category eq 'native') {
      $self->bind_sub_native($package_name, $sub_name, $cfunc_address);
    }
    elsif ($category eq 'precompile') {
      $self->bind_sub_precompile($package_name, $sub_name, $cfunc_address);
    }
  }
}

sub build_shared_lib {
  my ($self, $package_name, $sub_names, $opt) = @_;
  
  # Compile source file and create object files
  my $object_file = $self->compile($package_name, $opt);
  
  # Link object files and create shared library
  $self->link(
    $package_name,
    $sub_names,
    [$object_file],
    $opt
  );
}

sub compile {
  my ($self, $package_name, $opt) = @_;

  # Build directory
  my $build_dir = $self->{build_dir};
  unless (defined $build_dir && -d $build_dir) {
    confess "SPVM build directory must be specified for runtime " . $self->category . " build";
  }

  # Build directory
  my $work_dir = $opt->{work_dir};

  unless (defined $work_dir && -d $work_dir) {
    confess "Work directory must be specified for " . $self->category . " build";
  }
  
  # Output directory
  my $output_dir = $opt->{output_dir};
  unless (defined $output_dir && -d $output_dir) {
    confess "Output directory must be specified for " . $self->category . " build";
  }

  # shared lib file
  my $shared_lib_rel_file = SPVM::Builder::Util::convert_package_name_to_shared_lib_rel_file($package_name, $self->category);
  my $shared_lib_file = "$output_dir/$shared_lib_rel_file";
  
  # Quiet output
  my $quiet = $self->quiet;
 
  my $input_dir = $opt->{input_dir};
  my $package_path = SPVM::Builder::Util::convert_package_name_to_path($package_name, $self->category);
  my $input_src_dir = "$input_dir/$package_path";
  
  my $work_object_dir = "$work_dir/$package_path";
  mkpath $work_object_dir;
  
  # Package base name
  my $package_base_name = $package_name;
  $package_base_name =~ s/^.+:://;
  
  # Config file
  my $input_config_dir = $input_src_dir;
  my $config_file = "$input_config_dir/$package_base_name.config";
  
  # Config
  my $build_config;
  if (-f $config_file) {
    open my $config_fh, '<', $config_file
      or confess "Can't open $config_file: $!";
    my $config_content = do { local $/; <$config_fh> };
    $build_config = eval "$config_content";
    if (my $messge = $@) {
      confess "Can't parser $config_file: $@";
    }
  }
  else {
    $build_config = SPVM::Builder::Util::new_default_build_config;
  }

  # Source file
  my $src_exe = $build_config->get_src_ext;
  my $src_file = "$input_config_dir/$package_base_name.$src_exe";
  
  unless (-f $src_file) {
    confess "Can't find source file $src_file: $!";
  }

  # CBuilder configs
  my $ccflags = $build_config->get_ccflags;
  
  # Default include path
  $build_config->add_ccflags("-I$build_dir/inlcude");

  # Use all of default %Config not to use %Config directory by ExtUtils::CBuilder
  # and overwrite user configs
  my $config = $build_config->to_hash;

  # Compile source files
  my $cbuilder = ExtUtils::CBuilder->new(quiet => $quiet, config => $config);
  my $object_files = [];
  
  # Object file
  my $object_file = "$work_object_dir/$package_base_name.o";

  # Do compile. This is same as make command
  my $do_compile;
  if (!-f $object_file) {
    $do_compile = 1;
  }
  else {
    my $mod_time_src = (stat($src_file))[9];
    my $mod_time_object = (stat($object_file))[9];
    
    if ($mod_time_src > $mod_time_object) {
      $do_compile = 1;
    }
  }
  
  if ($do_compile) {
    # Compile source file
    $cbuilder->compile(
      source => $src_file,
      object_file => $object_file,
      extra_compiler_flags => $build_config->get_extra_compiler_flags,
    );
  }
  
  return $object_file;
}

sub link {
  my ($self, $package_name, $sub_names, $object_files, $opt) = @_;

  # Build directory
  my $build_dir = $self->{build_dir};
  unless (defined $build_dir && -d $build_dir) {
    confess "SPVM build directory must be specified for runtime " . $self->category . " build";
  }

  # Build directory
  my $work_dir = $opt->{work_dir};
  unless (defined $work_dir && -d $work_dir) {
    confess "Work directory must be specified for " . $self->category . " build";
  }
  
  # Output directory
  my $output_dir = $opt->{output_dir};
  unless (defined $output_dir && -d $output_dir) {
    confess "Output directory must be specified for " . $self->category . " build";
  }

  # shared lib file
  my $shared_lib_rel_file = SPVM::Builder::Util::convert_package_name_to_shared_lib_rel_file($package_name, $self->category);
  my $shared_lib_file = "$output_dir/$shared_lib_rel_file";

  # Quiet output
  my $quiet = $self->quiet;
 
  my $input_dir = $opt->{input_dir};
  my $package_path = SPVM::Builder::Util::convert_package_name_to_path($package_name, $self->category);
  my $input_src_dir = "$input_dir/$package_path";
  
  my $work_object_dir = "$work_dir/$package_path";
  mkpath $work_object_dir;
  
  # Config file
  my $package_base_name = $package_name;
  $package_base_name =~ s/^.+:://;
  my $input_config_dir = $input_src_dir;
  my $config_file = "$input_config_dir/$package_base_name.config";
  
  # Config
  my $build_config;
  if (-f $config_file) {
    open my $config_fh, '<', $config_file
      or confess "Can't open $config_file: $!";
    my $config_content = do { local $/; <$config_fh> };
    $build_config = eval "$config_content";
    if (my $messge = $@) {
      confess "Can't parser $config_file: $@";
    }
  }
  else {
    $build_config = SPVM::Builder::Util::new_default_build_config;
  }
  
  # CBuilder configs
  my $lddlflags = $build_config->get_lddlflags;

  # Default library path
  $build_config->add_lddlflags("-L$build_dir/lib");

  # Use all of default %Config not to use %Config directory by ExtUtils::CBuilder
  # and overwrite user configs
  my $config = $build_config->to_hash;
  
  my $cfunc_names = [];
  for my $sub_name (@$sub_names) {
    my $category = $self->category;
    my $category_uc = uc $category;
    my $cfunc_name = "SPVM_${category_uc}_${package_name}::$sub_name";
    $cfunc_name =~ s/:/_/g;
    push @$cfunc_names, $cfunc_name;
  }
  
  # This is dummy to suppress boot strap function
  # This is bad hack
  unless (@$cfunc_names) {
    push @$cfunc_names, '';
  }
  
  my $cbuilder = ExtUtils::CBuilder->new(quiet => $quiet, config => $config);
  my $tmp_shared_lib_file = $cbuilder->link(
    objects => $object_files,
    module_name => $package_name,
    dl_func_list => $cfunc_names,
    extra_linker_flags => $build_config->get_extra_linker_flags,
  );

  # Create shared lib blib directory
  my $shared_lib_dir = "$output_dir/$package_path";
  mkpath $shared_lib_dir;
  
  # Move shared library file to blib directory
  move($tmp_shared_lib_file, $shared_lib_file)
    or die "Can't move $tmp_shared_lib_file to $shared_lib_file";
  
  return $shared_lib_file;
}

sub get_shared_lib_path_dist {
  my ($self, $package_name) = @_;
  
  my @package_name_parts = split(/::/, $package_name);
  my $module_load_path = $self->builder->get_package_load_path($package_name);
  
  my $shared_lib_path = SPVM::Builder::Util::convert_module_path_to_shared_lib_path($module_load_path, $self->category);
  
  return $shared_lib_path;
}

sub build_shared_lib_precompile_runtime {
  my ($self, $package_name, $sub_names) = @_;

  # Output directory
  my $build_dir = $self->{build_dir};
  unless (defined $build_dir && -d $build_dir) {
    confess "SPVM build directory must be specified for runtime " . $self->category . " build";
  }
  
  my $work_dir = "$build_dir/work/tmp";
  mkpath $work_dir;
  my $input_dir = "$build_dir/work/src";
  mkpath $input_dir;
  my $output_dir = "$build_dir/lib";
  mkpath $output_dir;
  
  $self->create_source_precompile(
    $package_name,
    $sub_names,
    {
      input_dir => $input_dir,
      work_dir => $work_dir,
      output_dir => $work_dir,
    }
  );
  
  $self->build_shared_lib(
    $package_name,
    $sub_names,
    {
      input_dir => $work_dir,
      work_dir => $work_dir,
      output_dir => $output_dir,
    }
  );
}

sub build_shared_lib_native_runtime {
  my ($self, $package_name, $sub_names) = @_;
  
  my $package_load_path = $self->builder->get_package_load_path($package_name);
  my $input_dir = SPVM::Builder::Util::remove_package_part_from_path($package_load_path, $package_name);

  # Build directory
  my $build_dir = $self->{build_dir};
  unless (defined $build_dir && -d $build_dir) {
    confess "SPVM build directory must be specified for runtime " . $self->category . " build";
  }
  
  my $work_dir = "$build_dir/work/tmp";
  mkpath $work_dir;
  
  my $output_dir = "$build_dir/lib";
  mkpath $output_dir;
  
  $self->build_shared_lib(
    $package_name,
    $sub_names,
    {
      input_dir => $input_dir,
      work_dir => $work_dir,
      output_dir => $output_dir,
    }
  );
}

sub build_shared_lib_precompile_dist {
  my ($self, $package_name, $sub_names) = @_;
  
  my $input_dir = 'lib';

  my $work_dir = "spvm_build/work/tmp";
  mkpath $work_dir;

  my $output_dir = 'blib/lib';
  
  my $category = $self->category;
  
  my $module_base_name = $package_name;
  $module_base_name =~ s/^.+:://;
  my $config_file = "$input_dir/$module_base_name.config";

  $self->create_source_precompile(
    $package_name,
    $sub_names,
    {
      input_dir => $input_dir,
      work_dir => $work_dir,
      output_dir => $work_dir,
    }
  );
  
  $self->copy_source_precompile_dist(
    $package_name,
    $sub_names,
    {
      input_dir => $work_dir,
      output_dir => $output_dir,
    }
  );
  
  $self->build_shared_lib(
    $package_name,
    $sub_names,
    {
      input_dir => $work_dir,
      work_dir => $work_dir,
      output_dir => $output_dir,
    }
  );
}

sub build_shared_lib_native_dist {
  my ($self, $package_name, $sub_names) = @_;
  
  my $input_dir = 'lib';

  my $work_dir = "spvm_build/work/tmp";
  mkpath $work_dir;

  my $output_dir = 'blib/lib';

  my $category = $self->category;
  
  # Build shared library
  $self->build_shared_lib(
    $package_name,
    $sub_names,
    {
      input_dir => $input_dir,
      work_dir => $work_dir,
      output_dir => $output_dir,
    }
  );
}

sub create_source_precompile {
  my ($self, $package_name, $sub_names, $opt) = @_;
  
  my $work_dir = $opt->{work_dir};
  mkpath $work_dir;
  
  my $output_dir = $opt->{output_dir};
  
  my $package_path = SPVM::Builder::Util::convert_package_name_to_path($package_name, $self->category);
  my $work_src_dir = "$work_dir/$package_path";
  mkpath $work_src_dir;
  
  my $module_base_name = $package_name;
  $module_base_name =~ s/^.+:://;
  
  my $source_file = "$work_src_dir/$module_base_name.c";

  # Get old csource source
  my $old_package_csource;
  if (-f $source_file) {
    open my $fh, '<', $source_file
      or die "Can't open $source_file";
    $old_package_csource = do { local $/; <$fh> };
  }
  else {
    $old_package_csource = '';
  }
  
  # Create c source file
  my $package_csource = $self->build_package_csource_precompile($package_name, $sub_names);
  if ($package_csource ne $old_package_csource) {
    open my $fh, '>', $source_file
      or die "Can't create $source_file";
    print $fh $package_csource;
    close $fh;
  }
}

sub copy_source_precompile_dist {
  my ($self, $package_name, $sub_names, $opt) = @_;
  
  my $input_dir = $opt->{input_dir};

  my $output_dir = $opt->{output_dir};
  
  my $package_path = SPVM::Builder::Util::convert_package_name_to_path($package_name, $self->category);
  my $input_src_dir = "$input_dir/$package_path";
  my $output_src_dir = "$output_dir/$package_path";

  mkpath $output_src_dir;
  
  my $module_base_name = $package_name;
  $module_base_name =~ s/^.+:://;
  
  my $input_source_file = "$input_src_dir/$module_base_name.c";
  my $output_source_file = "$output_src_dir/$module_base_name.c";
  
  copy $input_source_file, $output_source_file
    or confess "Can't copy $input_source_file to $output_source_file: $!";
}

1;

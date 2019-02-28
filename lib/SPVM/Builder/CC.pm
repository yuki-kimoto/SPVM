package SPVM::Builder::CC;

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
      my $dll_file = $self->get_dll_file_dist($package_name);
      
      # Try runtime compile if shared objectrary is not found
      unless (-f $dll_file) {
        if ($category eq 'native') {
          $self->build_dll_native_runtime($package_name, $sub_names);
        }
        elsif ($category eq 'precompile') {
          $self->build_dll_precompile_runtime($package_name, $sub_names);
        }
        $dll_file = $self->get_dll_file_runtime($package_name);
      }
      $self->bind_subs($dll_file, $package_name, $sub_names);
    }
  }
}

sub copy_dll_to_build_dir {
  my ($self, $package_name, $category) = @_;
  
  my $dll_file = $self->get_dll_file_dist($package_name);
  
  my $dll_rel_file = SPVM::Builder::Util::convert_package_name_to_dll_category_rel_file($package_name, $category);
  
  my $build_dir = $self->builder->{build_dir};
  
  my $dll_build_dir = "$build_dir/work/lib/$dll_rel_file";
  
  my $dll_build_dir_dir = dirname $dll_build_dir;
  
  mkpath $dll_build_dir_dir;
  
  copy $dll_file, $dll_build_dir
    or croak "Can't copy $dll_file to $dll_build_dir";
}

sub get_dll_file_runtime {
  my ($self, $package_name) = @_;
  
  my $dll_rel_file = SPVM::Builder::Util::convert_package_name_to_dll_category_rel_file($package_name, $self->category);
  my $build_dir = $self->{build_dir};
  my $output_dir = "$build_dir/work/lib";
  my $dll_file = "$output_dir/$dll_rel_file";
  
  return $dll_file;
}

sub create_cfunc_name {
  my ($self, $package_name, $sub_name) = @_;
  
  my $category = $self->category;
  my $prefix = 'SP' . uc($category) . '__';
  
  # Precompile Subroutine names
  my $sub_abs_name_under_score = "${package_name}::$sub_name";
  $sub_abs_name_under_score =~ s/:/_/g;
  my $cfunc_name = "$prefix$sub_abs_name_under_score";
  
  return $cfunc_name;
}

sub bind_subs {
  my ($self, $dll_file, $package_name, $sub_names) = @_;
  
  for my $sub_name (@$sub_names) {
    my $sub_abs_name = "${package_name}::$sub_name";

    my $cfunc_name = $self->create_cfunc_name($package_name, $sub_name);
    my $cfunc_address = SPVM::Builder::Util::get_dll_func_address($dll_file, $cfunc_name);
    
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

sub build_dll {
  my ($self, $package_name, $sub_names, $opt) = @_;
  
  # Compile source file and create object files
  my $object_file = $self->compile($package_name, $opt);
  
  # Link object files and create shared objectrary
  $self->link(
    $package_name,
    $sub_names,
    $object_file,
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
  
  # Input directory
  my $input_dir = $opt->{input_dir};

  # Temporary directory
  my $object_dir = $opt->{object_dir};
  unless (defined $object_dir && -d $object_dir) {
    confess "Temporary directory must be specified for " . $self->category . " build";
  }
  
  # Output directory
  my $output_dir = $opt->{output_dir};
  unless (defined $output_dir && -d $output_dir) {
    confess "Output directory must be specified for " . $self->category . " build";
  }

  # Quiet output
  my $quiet = $self->quiet;
  
  my $category = $self->category;
 
  my $package_rel_file = SPVM::Builder::Util::convert_package_name_to_rel_file($package_name);
  my $package_rel_dir = SPVM::Builder::Util::convert_package_name_to_rel_dir($package_name);
  my $work_object_dir = "$object_dir/$package_rel_dir";
  mkpath $work_object_dir;
  
  # Package base name
  my $package_base_name = $package_name;
  $package_base_name =~ s/^.+:://;

  # Config file
  my $config_rel_file = SPVM::Builder::Util::convert_package_name_to_category_rel_file_with_ext($package_name, $category, 'config');
  my $config_file = "$input_dir/$config_rel_file";
  
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
  my $src_rel_file_no_ext = SPVM::Builder::Util::convert_package_name_to_category_rel_file_without_ext($package_name, $category);
  my $src_file_no_ext = "$input_dir/$src_rel_file_no_ext";
  my @available_exts = qw(.c .C .cpp .i .s .cxx .cc);
  my @src_files;
  for my $ext (@available_exts) {
    my $src_file = "$src_file_no_ext$ext";
    if (-f $src_file) {
      push @src_files, $src_file;
    }
  }
  if (@src_files > 1) {
    confess "Find multiple source file @src_files";
  }
  elsif (@src_files == 0) {
    confess "Can't find source file $src_file_no_ext with extension(@available_exts)";
  }
  my $src_file = $src_files[0];

  # CBuilder configs
  my $ccflags = $build_config->get_ccflags;
  
  # Default include path
  $build_config->add_ccflags("-I$build_dir/inlcude");

  # Use all of default %Config not to use %Config directory by ExtUtils::CBuilder
  # and overwrite user configs
  my $config = $build_config->to_hash;

  # Compile source files
  my $cbuilder = ExtUtils::CBuilder->new(quiet => $quiet, config => $config);
  
  # Object file
  my $object_rel_file = SPVM::Builder::Util::convert_package_name_to_category_rel_file_with_ext($package_name, $category, 'o');
  my $object_file = "$object_dir/$object_rel_file";

  # Do compile. This is same as make command
  my $do_compile;
  if ($package_name =~ /^anon/) {
    $do_compile = 1;
  }
  else {
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
  my ($self, $package_name, $sub_names, $object_file, $opt) = @_;

  # Build directory
  my $build_dir = $self->{build_dir};
  unless (defined $build_dir && -d $build_dir) {
    confess "SPVM build directory must be specified for runtime " . $self->category . " build";
  }
  
  # Input directory
  my $input_dir = $opt->{input_dir};

  # Work temporary directory
  my $object_dir = $opt->{object_dir};
  unless (defined $object_dir && -d $object_dir) {
    confess "Temporary directory must be specified for " . $self->category . " build";
  }
  
  # Output directory
  my $output_dir = $opt->{output_dir};
  unless (defined $output_dir && -d $output_dir) {
    confess "Output directory must be specified for " . $self->category . " build";
  }

  # shared object file
  my $dll_rel_file = SPVM::Builder::Util::convert_package_name_to_dll_category_rel_file($package_name, $self->category);
  my $dll_file = "$output_dir/$dll_rel_file";

  # Quiet output
  my $quiet = $self->quiet;
  
  # Create temporary package directory
  my $tmp_package_rel_file = SPVM::Builder::Util::convert_package_name_to_rel_file($package_name);
  my $tmp_package_rel_dir = SPVM::Builder::Util::convert_package_name_to_rel_dir($package_name);
  my $tmp_package_dir = "$object_dir/$tmp_package_rel_dir";
  mkpath $tmp_package_dir;
  
  # Category
  my $category = $self->category;

  # Config file
  my $config_rel_file = SPVM::Builder::Util::convert_package_name_to_category_rel_file_with_ext($package_name, $category, 'config');
  my $config_file = "$input_dir/$config_rel_file";
  
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
  my $tmp_dll_file = $cbuilder->link(
    objects => [$object_file],
    module_name => $package_name,
    dl_func_list => $cfunc_names,
    extra_linker_flags => $build_config->get_extra_linker_flags,
  );

  # Create shared object blib directory
  my $package_rel_file_without_ext = SPVM::Builder::Util::convert_package_name_to_rel_file_without_ext($package_name);
  my $dll_dir = "$output_dir/$package_rel_file_without_ext";
  mkpath $dll_dir;
  
  # Move shared objectrary file to blib directory
  move($tmp_dll_file, $dll_file)
    or die "Can't move $tmp_dll_file to $dll_file";
  
  return $dll_file;
}

sub get_dll_file_dist {
  my ($self, $package_name) = @_;
  
  my @package_name_parts = split(/::/, $package_name);
  my $module_module_file = $self->builder->get_module_file($package_name);
  
  my $dll_file = SPVM::Builder::Util::convert_module_file_to_dll_category_file($module_module_file, $self->category);
  
  return $dll_file;
}

sub build_dll_precompile_runtime {
  my ($self, $package_name, $sub_names) = @_;

  # Output directory
  my $build_dir = $self->{build_dir};
  unless (defined $build_dir && -d $build_dir) {
    confess "SPVM build directory must be specified for runtime " . $self->category . " build";
  }
  
  my $object_dir = "$build_dir/work/object";
  mkpath $object_dir;
  my $input_dir = "$build_dir/work/src";
  mkpath $input_dir;
  my $output_dir = "$build_dir/work/lib";
  mkpath $output_dir;
  
  $self->create_source_precompile(
    $package_name,
    $sub_names,
    {
      input_dir => $input_dir,
      object_dir => $object_dir,
      output_dir => $object_dir,
    }
  );
  
  $self->build_dll(
    $package_name,
    $sub_names,
    {
      input_dir => $object_dir,
      object_dir => $object_dir,
      output_dir => $output_dir,
    }
  );
}

sub build_dll_native_runtime {
  my ($self, $package_name, $sub_names) = @_;
  
  my $module_file = $self->builder->get_module_file($package_name);
  my $input_dir = SPVM::Builder::Util::remove_package_part_from_file($module_file, $package_name);

  # Build directory
  my $build_dir = $self->{build_dir};
  unless (defined $build_dir && -d $build_dir) {
    confess "SPVM build directory must be specified for runtime " . $self->category . " build";
  }
  
  my $object_dir = "$build_dir/work/object";
  mkpath $object_dir;
  
  my $output_dir = "$build_dir/work/lib";
  mkpath $output_dir;
  
  $self->build_dll(
    $package_name,
    $sub_names,
    {
      input_dir => $input_dir,
      object_dir => $object_dir,
      output_dir => $output_dir,
    }
  );
}

sub build_dll_precompile_dist {
  my ($self, $package_name, $sub_names) = @_;
  
  my $input_dir = 'lib';

  my $object_dir = "spvm_build/work/object";
  mkpath $object_dir;

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
      object_dir => $object_dir,
      output_dir => $object_dir,
    }
  );
  
  $self->copy_source_precompile_dist(
    $package_name,
    $sub_names,
    {
      input_dir => $object_dir,
      output_dir => $output_dir,
    }
  );
  
  $self->build_dll(
    $package_name,
    $sub_names,
    {
      input_dir => $object_dir,
      object_dir => $object_dir,
      output_dir => $output_dir,
    }
  );
}

sub build_dll_native_dist {
  my ($self, $package_name, $sub_names) = @_;
  
  my $input_dir = 'lib';

  my $object_dir = "spvm_build/work/object";
  mkpath $object_dir;

  my $output_dir = 'blib/lib';

  my $category = $self->category;
  
  # Build shared object
  $self->build_dll(
    $package_name,
    $sub_names,
    {
      input_dir => $input_dir,
      object_dir => $object_dir,
      output_dir => $output_dir,
    }
  );
}

sub create_source_precompile {
  my ($self, $package_name, $sub_names, $opt) = @_;
  
  my $object_dir = $opt->{object_dir};
  mkpath $object_dir;
  
  my $category = 'precompile';
  
  my $package_rel_file_without_ext = SPVM::Builder::Util::convert_package_name_to_rel_file_without_ext($package_name);
  my $package_rel_dir = SPVM::Builder::Util::convert_package_name_to_rel_dir($package_name);
  my $source_file = "$object_dir/$package_rel_file_without_ext.$category.c";
  my $source_dir = "$object_dir/$package_rel_dir";
  mkpath $source_dir;

  my $package_csource = $self->build_package_csource_precompile($package_name, $sub_names);
  
  my $is_create_source_file;
  # Anon sub
  if ($package_name =~ /^anon/) {
    $is_create_source_file = 1;
  }
  # Normal sub
  else {
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
    
    if ($package_csource ne $old_package_csource) {
      $is_create_source_file = 1;
    }
    else {
      $is_create_source_file = 0;
    }
  }
  
  # Create source fil
  if ($is_create_source_file) {
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
  
  my $category = 'precompile';
  
  my $package_rel_file_without_ext = SPVM::Builder::Util::convert_package_name_to_rel_file_without_ext($package_name);
  my $input_src_file = "$input_dir/$package_rel_file_without_ext.$category.c";
  my $output_src_file = "$output_dir/$package_rel_file_without_ext.$category.c";
  my $output_src_dir = dirname $output_src_file;
  mkpath $output_src_dir;
  
  copy $input_src_file, $output_src_file
    or confess "Can't copy $input_src_file to $output_src_file: $!";
}

1;

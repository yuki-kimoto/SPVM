package SPVM::Build::CBuilder;

use strict;
use warnings;
use Carp 'croak', 'confess';

use SPVM::Build::Util;

use ExtUtils::CBuilder;
use Config;
use File::Copy 'move';
use File::Path 'mkpath';
use DynaLoader;

use File::Basename 'dirname', 'basename';

sub new {
  my $class = shift;
  
  my $self = {@_};
  
  return bless $self, $class;
}

sub info {
  my $self = shift;
  
  return $self->{info};
}

sub category {
  my $self = shift;
  
  $self->{category};
}

sub build {
  my $self = shift;
  
  my $package_names = $self->info->get_package_names;
  for my $package_name (@$package_names) {
    
    my $sub_names = $self->get_sub_names($package_name);
    if (@$sub_names) {
      # Shared library is already installed in distribution directory
      my $shared_lib_path = $self->get_installed_shared_lib_path($package_name);

      # Try runtime compile if shared library is not found
      unless (-f $shared_lib_path) {
        $self->create_shared_lib_runtime($package_name);

        # Build directory
        my $shared_lib_rel_file = SPVM::Build::Util::convert_package_name_to_shared_lib_rel_file($package_name, $self->category);
        my $build_dir = $self->{build_dir};
        my $output_dir = "$build_dir/lib";
        $shared_lib_path = "$output_dir/$shared_lib_rel_file";
      }
      $self->bind_subs($shared_lib_path, $package_name, $sub_names);
    }
  }
}

sub create_cfunc_name {
  my ($self, $sub_abs_name) = @_;
  
  my $category = $self->category;
  my $prefix = 'SPVM_' . uc($category) . '_';
  
  # Precompile Subroutine names
  my $sub_abs_name_under_score = $sub_abs_name;
  $sub_abs_name_under_score =~ s/:/_/g;
  my $cfunc_name = "$prefix$sub_abs_name_under_score";
  
  return $cfunc_name;
}

sub bind_subs {
  my ($self, $shared_lib_path, $package_name, $sub_names) = @_;
  
  for my $sub_name (@$sub_names) {
    my $sub_abs_name = "${package_name}::$sub_name";

    my $cfunc_name = $self->create_cfunc_name($sub_abs_name);
    my $cfunc_address = SPVM::Build::Util::get_shared_lib_func_address($shared_lib_path, $cfunc_name);
    
    unless ($cfunc_address) {
      my $cfunc_name = $self->create_cfunc_name($sub_abs_name);
      $cfunc_name =~ s/:/_/g;
      confess "Can't find function address of $sub_abs_name(). C function name must be $cfunc_name";
    }
    $self->bind_sub($sub_abs_name, $cfunc_address);
  }
}

sub create_shared_lib {
  my ($self, %opt) = @_;
  
  # Package name
  my $package_name = $opt{package_name};

  # Build directory
  my $work_dir = $opt{work_dir};
  unless (defined $work_dir && -d $work_dir) {
    confess "Work directory must be specified for " . $self->category . " build";
  }
  
  # Output directory
  my $output_dir = $opt{output_dir};
  unless (defined $output_dir && -d $output_dir) {
    confess "Output directory must be specified for " . $self->category . " build";
  }

  # shared lib file
  my $shared_lib_rel_file = SPVM::Build::Util::convert_package_name_to_shared_lib_rel_file($package_name, $self->category);
  my $shared_lib_file = "$output_dir/$shared_lib_rel_file";

  # Return if source code is chaced and exists shared lib file
  if ($opt{is_cached} && -f $shared_lib_file) {
    return;
  }
  
  my $sub_names = $opt{sub_names};
  
  # Quiet output
  my $quiet = defined $opt{quiet} ? $opt{quiet} : 0;
 
  my $input_dir = $opt{input_dir};
  my $package_path = SPVM::Build::Util::convert_package_name_to_path($package_name, $self->category);
  my $input_src_dir = "$input_dir/$package_path";
  
  my $work_object_dir = "$work_dir/$package_path";
  mkpath $work_object_dir;
  
  # Correct source files
  my $src_files = [];
  my @valid_exts = ('c', 'C', 'cpp', 'i', 's', 'cxx', 'cc');
  for my $src_file (glob "$input_src_dir/*") {
    if (grep { $src_file =~ /\.$_$/ } @valid_exts) {
      push @$src_files, $src_file;
    }
  }
  
  # Config file
  my $package_base_name = $package_name;
  $package_base_name =~ s/^.+:://;
  my $input_config_dir = $input_src_dir;
  my $config_file = "$input_config_dir/$package_base_name.config";
  
  # Config
  my $build_setting;
  if (-f $config_file) {
    $build_setting = do $config_file
      or confess "Can't parser $config_file: $!$@";
  }
  else {
    $build_setting = SPVM::Build::Util::new_default_build_setting;
  }
  
  # CBuilder settings
  my $include_dirs = [@{$build_setting->get_include_dirs}];
  my $extra_compiler_flags = [@{$build_setting->get_extra_compiler_flags}];
  my $extra_linker_flags = [@{$build_setting->get_extra_linker_flags}];
  
  # Use all of default %Config not to use %Config directory by ExtUtils::CBuilder
  # and overwrite user settings
  my $config = {
    %Config,
    %{$build_setting->get_config}
  };
  
  # Default include path
  my $env_header_include_dir = $INC{"SPVM/Build.pm"};
  $env_header_include_dir =~ s/\.pm$//;
  $env_header_include_dir .= '/include';
  push @$include_dirs, $env_header_include_dir;
  push @$include_dirs, $input_src_dir;
  
  # Compile source files
  my $cbuilder = ExtUtils::CBuilder->new(quiet => $quiet, config => $config);
  my $object_files = [];
  for my $src_file (@$src_files) {
    # Object file
    my $object_file = "$work_object_dir/" . basename($src_file);
    $object_file =~ s/\.c$//;
    $object_file =~ s/\.C$//;
    $object_file =~ s/\.cpp$//;
    $object_file =~ s/\.i$//;
    $object_file =~ s/\.s$//;
    $object_file =~ s/\.cxx$//;
    $object_file =~ s/\.cc$//;
    $object_file .= '.o';
    
    # Compile source file
    $cbuilder->compile(
      source => $src_file,
      object_file => $object_file,
      include_dirs => $include_dirs,
      extra_compiler_flags => join(' ', @$extra_compiler_flags),
    );
    push @$object_files, $object_file;
  }
  
  my $dlext = $Config{dlext};
  
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
  
  my $tmp_shared_lib_file = $cbuilder->link(
    objects => $object_files,
    package_name => $package_name,
    dl_func_list => $cfunc_names,
    extra_linker_flags => join(' ', @$extra_linker_flags),
  );
  

  # Create shared lib blib directory
  my $shared_lib_dir = "$output_dir/$package_path";
  mkpath $shared_lib_dir;
  
  # Move shared library file to blib directory
  move($tmp_shared_lib_file, $shared_lib_file)
    or die "Can't move $tmp_shared_lib_file to $shared_lib_file";
  
  return $shared_lib_file;
}

sub get_installed_shared_lib_path {
  my ($self, $package_name) = @_;
  
  my @package_name_parts = split(/::/, $package_name);
  my $module_load_path = $self->info->get_package_load_path($package_name);
  
  my $shared_lib_path = SPVM::Build::Util::convert_module_path_to_shared_lib_path($module_load_path, $self->category);
  
  return $shared_lib_path;
}

1;

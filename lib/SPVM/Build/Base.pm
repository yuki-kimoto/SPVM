package SPVM::Build::Base;

# SPVM::Build::PPtUtil is used from Makefile.PL
# so this module must be wrote as pure per script, not contain XS and don't use any other SPVM modules.

use strict;
use warnings;
use Carp 'croak', 'confess';

use SPVM::Build::Util;
use SPVM::Build::SPVMInfo;

use ExtUtils::CBuilder;
use Config;
use File::Copy 'move';
use File::Path 'mkpath';
use DynaLoader;

use File::Basename 'dirname', 'basename';

sub new {
  my $class = shift;
  
  my $self = {};
  
  $self->{extra_compiler_flags} = SPVM::Build::Util::default_extra_compiler_flags();
  $self->{optimize} = SPVM::Build::Util::default_optimize();
  
  return bless $self, $class;
}

sub category {
  my $self = shift;
  
  $self->{category};
}

sub extra_compiler_flags {
  my $self = shift;
  
  return $self->{extra_compiler_flags};
}

sub optimize {
  my $self = shift;
  
  return $self->{optimize};
}

sub create_build_shared_lib_make_rule {
  my ($self, $package_name) = @_;
  
  my $make_rule;
  
  # dynamic section
  $make_rule
  = "dynamic :: ";

  my $package_name_under_score = $package_name;
  $package_name_under_score =~ s/:/_/g;
  
  $make_rule
    .= "shared_lib_$package_name_under_score ";
  $make_rule .= "\n\n";
  
  my $module_base_name = $package_name;
  $module_base_name =~ s/^.+:://;
  
  my $src_dir = $package_name;
  $src_dir =~ s/::/\//g;
  $src_dir = "lib/$src_dir." . $self->category;
  
  # Dependency
  my @deps = grep { $_ ne '.' && $_ ne '..' } glob "$src_dir/*";
  
  # Shared library file
  my $shared_lib_file = SPVM::Build::Util::convert_package_name_to_shared_lib_file("blib/lib", $package_name, $self->category);
  
  # Get source files
  my $module_category = $self->category;
  $module_category = ucfirst $module_category;
  $make_rule
    .= "shared_lib_$package_name_under_score :: $shared_lib_file\n\n";
  $make_rule
    .= "$shared_lib_file :: @deps\n\n";
  $make_rule
    .= "\tperl -Ilib -MSPVM::Build::$module_category -e \"SPVM::Build::$module_category->new->build_shared_lib_dist('$package_name')\"\n\n";
  
  return $make_rule;
}

sub build_and_bind {
  my $self = shift;
  
  my $packages = SPVM::Build::SPVMInfo::get_packages();
  for my $package (@$packages) {
    my $package_name = $package->{name};
    
    next if $package_name eq "CORE";
    
    my $subs = $self->get_subs_from_package_name($package_name);
    if (@$subs) {
      my $installed_shared_lib_path = $self->get_installed_shared_lib_path($package_name);
      
      # Shared library is already installed in distribution directory
      if (-f $installed_shared_lib_path) {
        $self->bind_subs($installed_shared_lib_path, $subs);
      }
      # Shared library is not installed, so try runtime build
      else {
        # Try runtime compile
        my $runtime_shared_lib_path = $self->build_shared_lib_runtime($package_name);
        $self->bind_subs($runtime_shared_lib_path, $subs);
      }
    }
  }
}

sub bind_subs {
  my ($self, $shared_lib_path, $subs) = @_;
  
  for my $sub (@$subs) {
    my $sub_name = $sub->{name};
    next if $sub_name =~ /^CORE::/;
    my $sub_name_spvm = "SPVM::$sub_name";

    my $cfunc_name = $self->create_cfunc_name($sub_name);
    my $cfunc_address = SPVM::Build::Util::get_shared_lib_func_address($shared_lib_path, $cfunc_name);
    
    unless ($cfunc_address) {
      my $sub_name_c = $sub_name_spvm;
      $sub_name_c =~ s/:/_/g;
      confess "Can't find function address of $sub_name_spvm(). Native function name must be $sub_name_c";
    }
    $self->bind_sub($sub_name, $cfunc_address);
  }
}

sub build_shared_lib {
  my ($self, %opt) = @_;
  
  # Source directory
  my $input_dir_new = $opt{input_dir};
  
  # Package name
  my $package_name = $opt{package_name};
  
  # Build directory
  my $build_dir = $opt{build_dir};
  unless (defined $build_dir && -d $build_dir) {
    confess "Build directory must be specified for " . $self->category . " build";
  }
  my $build_work_dir = "$build_dir/work/" . $self->category;
  mkpath $build_work_dir;
  
  # Output directory
  my $output_dir = $opt{output_dir};
  unless (defined $output_dir && -d $output_dir) {
    confess "Output directory must be specified for " . $self->category . " build";
  }
  
  my $sub_names = $opt{sub_names};
  
  # Quiet output
  my $quiet = defined $opt{quiet} ? $opt{quiet} : 0;
 
  my $module_base_name = $package_name;
  $module_base_name =~ s/^.+:://;
  
  my $input_dir = $opt{input_dir};
  
  # Correct source files
  my $src_files = [];
  my @valid_exts = ('c', 'C', 'cpp', 'i', 's', 'cxx', 'cc');
  for my $src_file (glob "$input_dir/*") {
    if (grep { $src_file =~ /\.$_$/ } @valid_exts) {
      push @$src_files, $src_file;
    }
  }
  
  # Config
  my $config_file = "$input_dir/$module_base_name.config";
  my $config;
  if (-f $config_file) {
    $config = do $config_file
      or confess "Can't parser $config_file: $!$@";
  }
  
  # Include directory
  my $include_dirs = [];
  
  # Default include path
  my $env_header_include_dir = $INC{"SPVM/Build/Base.pm"};
  $env_header_include_dir =~ s/\/Build\/Base\.pm$//;
  push @$include_dirs, $env_header_include_dir;
  
  push @$include_dirs, $input_dir;
  
  # CBuilder config
  my $cbuilder_config = {};
  
  # Convert ExtUitls::MakeMaker config to ExtUtils::CBuilder config
  if ($config) {
    # CBuilder config name which compatible with ExtUtils::MakeMaker
    my @cbuilder_config_names_compatible = qw(
      optimize
      cc
      ccflags
      ld
      lddlflags
    );
    for my $cbuilder_name (@cbuilder_config_names_compatible) {
      my $makemaker_name = uc $cbuilder_name;
      
      if (defined $config->{$makemaker_name}) {
        $cbuilder_config->{$cbuilder_name} = delete $config->{$makemaker_name};
      }
    }
  }
  
  # Include directory
  if (defined $config->{INC}) {
    my $inc = delete $config->{INC};
    
    my @include_dirs_tmp = split /\s+/, $inc;
    for my $include_dir_tmp (reverse @include_dirs_tmp) {
      if ($include_dir_tmp =~ s/^-I//) {
        unshift @$include_dirs, $include_dir_tmp;
      }
      else {
        confess "Invalid include option \"$inc\"";
      }
    }
  }
  
  # Shared library
  my $extra_linker_flags = '';
  if (defined $config->{LIBS}) {
    my $libs = delete $config->{LIBS};
    
    if (ref $libs eq 'ARRAY') {
      $libs = join(' ', @$libs);
    }
    
    $extra_linker_flags .= $libs;
  }
  
  my @keys = keys %$config;
  if (@keys) {
    confess "$keys[0] is not supported option";
  }
  
  # OPTIMIZE
  $cbuilder_config->{optimize} ||= $self->optimize;
  
  # Compile source files
  my $cbuilder = ExtUtils::CBuilder->new(quiet => $quiet, config => $cbuilder_config);
  my $object_files = [];
  for my $src_file (@$src_files) {
    # Object file
    my $object_file = "$build_work_dir/" . basename($src_file);
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
      extra_compiler_flags => $self->extra_compiler_flags
    );
    push @$object_files, $object_file;
  }
  
  my $dlext = $Config{dlext};
  
  my $cfunc_names = [];
  for my $sub_name (@$sub_names) {
    my $cfunc_name = "${package_name}::$sub_name";
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
    extra_linker_flags => $extra_linker_flags
  );

  # Create shared lib blib directory
  my $shared_lib_dir = SPVM::Build::Util::convert_package_name_to_shared_lib_dir($output_dir, $package_name, $self->category);
  mkpath $shared_lib_dir;
  
  # shared lib blib file
  my $shared_lib_file = SPVM::Build::Util::convert_package_name_to_shared_lib_file($output_dir, $package_name, $self->category);
  
  # Move shared library file to blib directory
  move($tmp_shared_lib_file, $shared_lib_file)
    or die "Can't move $tmp_shared_lib_file to $shared_lib_file";
  
  return $shared_lib_file;
}

sub get_installed_shared_lib_path {
  my ($self, $package_name) = @_;
  
  my $package_name_with_spvm = $package_name;
  $package_name_with_spvm =~ s/SPVM:://;
  my @package_name_parts = split(/::/, $package_name_with_spvm);
  my $module_load_path = SPVM::Build::SPVMInfo::get_package_load_path($package_name_with_spvm);
  
  my $shared_lib_path = SPVM::Build::Util::convert_module_path_to_shared_lib_path($module_load_path, $self->category);
  
  return $shared_lib_path;
}

1;

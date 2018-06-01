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
  $self->{category} = 'native';
  
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
  my $shared_lib_bilb_file = SPVM::Build::Util::convert_package_name_to_shared_lib_bilb_file($package_name, $self->category);
  
  # Get native source files
  my $module_category = $self->category;
  $module_category = ucfirst $module_category;
  $make_rule
    .= "shared_lib_$package_name_under_score :: $shared_lib_bilb_file\n\n";
  $make_rule
    .= "$shared_lib_bilb_file :: @deps\n\n";
  $make_rule
    .= "\tperl -Ilib -MSPVM::Build::$module_category -e \"SPVM::Build::$module_category->new->build_dist_shared_lib('$package_name')\"\n\n";
  
  return $make_rule;
}

sub build_dist_shared_lib {
  my ($self, $package_name) = @_;

  # Build shared library
  my $shared_lib_file = $self->build_shared_lib(
    package_name => $package_name,
    module_dir => 'lib',
    source_dir => 'lib',
    build_dir => '.'
  );
  
  # Create shared lib blib directory
  my $shared_lib_blib_dir = SPVM::Build::Util::convert_package_name_to_shared_lib_blib_dir($package_name, $self->category);
  mkpath $shared_lib_blib_dir;
  
  # shared lib blib file
  my $shared_lib_blib_file = SPVM::Build::Util::convert_package_name_to_shared_lib_bilb_file($package_name, $self->category);
  
  # Move shared library file to blib directory
  move($shared_lib_file, $shared_lib_blib_file)
    or die "Can't move $shared_lib_file to $shared_lib_blib_file";
}

sub build_package_runtime {
  my ($self, $package) = @_;
  
  my $package_name = $package->{name};
  
  my $source_dir = SPVM::Build::SPVMInfo::get_package_load_path($package_name);
  my $category = $self->category;
  $source_dir =~ s/\.spvm$/.$category/;
  
  # Build native code
  my $build_dir = $SPVM::BUILD_DIR;
  unless (defined $build_dir && -d $build_dir) {
    confess "SPVM build directory must be specified for native compile";
  }

  my $module_dir = SPVM::Build::SPVMInfo::get_package_load_path($package_name);
  $module_dir =~ s/\.spvm$//;
  
  my $package_name_slash = $package_name;
  $package_name_slash =~ s/::/\//g;
  
  $module_dir =~ s/$package_name_slash$//;
  $module_dir =~ s/\/$//;
  
  my $shared_lib_file = $self->build_shared_lib(
    module_dir => $module_dir,
    package_name => $package_name,
    source_dir => $source_dir,
    build_dir => $build_dir,
    quiet => 1,
  );
  
  return $shared_lib_file;
}

sub bind_subs {
  my ($self, $shared_lib_path, $subs) = @_;
  
  for my $sub (@$subs) {
    my $sub_name = $sub->{name};
    next if $sub_name =~ /^CORE::/;
    my $sub_name_spvm = "SPVM::$sub_name";

    my $cfunc_name = $self->create_cfunc_name($sub_name);
    my $native_address = SPVM::Build::Util::get_shared_lib_func_address($shared_lib_path, $cfunc_name);

    unless ($native_address) {
      my $sub_name_c = $sub_name_spvm;
      $sub_name_c =~ s/:/_/g;
      confess "Can't find function address of $sub_name_spvm(). Native function name must be $sub_name_c";
    }
    $self->bind_sub($sub_name, $native_address);
  }
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

sub build_and_bind {
  my $self = shift;
  
  my $packages = SPVM::Build::SPVMInfo::get_packages();
  for my $package (@$packages) {
    my $package_id = $package->{id};
    my $package_name = $package->{name};
    
    next if $package_name eq "CORE";
    
    my $subs = $self->get_subs_from_package_id($package_id);
    if (@$subs) {
      my $installed_shared_lib_path = $self->get_installed_shared_lib_path($package_name);
      
      # Shared library is already installed
      if (-f $installed_shared_lib_path) {
        $self->bind_subs($installed_shared_lib_path, $subs);
      }
      # Shared library is not installed
      else {
        # Try runtime compile
        my $runtime_shared_lib_path = $self->build_package_runtime($package);
        $self->bind_subs($runtime_shared_lib_path, $subs);
      }
    }
  }
}

1;

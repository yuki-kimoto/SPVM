package SPVM::Build;

use strict;
use warnings;

use Config;
use Carp 'confess';

use SPVM::Build::SPVMInfo;
use SPVM::Build::ExtUtil;
use SPVM::Build::JIT;
use SPVM::Build::Inline;

sub new {
  my $class = shift;
  
  my $self = {};
  
  return bless $self, $class;
}

sub compile_spvm {
  my $self = shift;
  
  # Compile SPVM source code
  my $compile_success = $self->compile();
  
  if ($compile_success) {
    # Build opcode
    $self->build_opcode;
    
    # Build run-time
    $self->build_runtime;
    
    # Bind native subroutines
    $self->bind_native_subs;
    
    # Build SPVM subroutines
    $self->build_spvm_subs;
  }
  
  return $compile_success;
}

my $package_name_h = {};

sub build_spvm_subs {
  my $self = shift;
  
  my $sub_names = SPVM::Build::SPVMInfo::get_sub_names();
  
  for my $abs_name (@$sub_names) {
    # Define SPVM subroutine
    no strict 'refs';
    
    # Declare package
    my ($package_name, $sub_name) = $abs_name =~ /^(?:(.+)::)(.+)/;
    $package_name = "SPVM::$package_name";
    unless ($package_name_h->{$package_name}) {
      
      my $code = "package $package_name; our \@ISA = ('SPVM::Perl::Object::Package');";
      eval $code;
      
      if (my $error = $@) {
        confess $error;
      }
      $package_name_h->{$package_name} = 1;
    }
    
    # Declare subroutine
    *{"SPVM::$abs_name"} = sub {
      
      my $return_value;
      eval { $return_value = SPVM::call_sub("$abs_name", @_) };
      my $error = $@;
      if ($error) {
        confess $error;
      }
      $return_value;
    };
  }
}

sub get_shared_lib_file {
  my ($self, $module_name) = @_;
  
  my $module_name2 = $module_name;
  $module_name2 =~ s/SPVM:://;
  my @module_name_parts = split(/::/, $module_name2);
  my $module_load_path = SPVM::Build::SPVMInfo::get_package_load_path($module_name2);
  
  my $shared_lib_path = SPVM::Build::ExtUtil->new->convert_module_path_to_shared_lib_path($module_load_path);
  
  return $shared_lib_path;
}

sub bind_native_subs {
  my $self = shift;
  
  my $native_func_names = SPVM::Build::SPVMInfo::get_native_sub_names();
  for my $native_func_name (@$native_func_names) {
    my $native_func_name_spvm = "SPVM::$native_func_name";
    my $native_address = $self->get_sub_native_address($native_func_name_spvm);
    unless ($native_address) {
      my $native_func_name_c = $native_func_name_spvm;
      $native_func_name_c =~ s/:/_/g;
      confess "Can't find native address of $native_func_name_spvm(). Native function name must be $native_func_name_c";
    }
    $self->bind_native_sub($native_func_name, $native_address);
  }
}

sub get_sub_native_address {
  my ($self, $sub_abs_name) = @_;
  
  my $package_name;
  my $sub_name;
  if ($sub_abs_name =~ /^(?:(.+)::)(.+)$/) {
    $package_name = $1;
    $sub_name = $2;
  }
  
  my $dll_package_name = $package_name;
  my $shared_lib_file = $self->get_shared_lib_file($dll_package_name);
  
  my $shared_lib_func_name = $sub_abs_name;
  $shared_lib_func_name =~ s/:/_/g;
  my $native_address = SPVM::Build::ExtUtil->new->search_shared_lib_func_address($shared_lib_file, $shared_lib_func_name);
  
  # Try inline compile
  unless ($native_address) {
    
    my $module_name = $package_name;
    $module_name =~ s/^SPVM:://;
    my $module_dir = SPVM::Build::SPVMInfo::get_package_load_path($module_name);
    $module_dir =~ s/\.spvm$//;
    
    my $module_name_slash = $package_name;
    $module_name_slash =~ s/::/\//g;
    
    $module_dir =~ s/$module_name_slash$//;
    $module_dir =~ s/\/$//;
    
    my $shared_lib_file;
    
    eval {
      $shared_lib_file = SPVM::Build::ExtUtil->new->build_shared_lib(
        module_dir => $module_dir,
        module_name => "SPVM::$module_name",
        object_dir => $SPVM::TMP_DIR,
        inline => 1
      );
    };
    
    if ($@) {
      return;
    }
    else {
      $native_address = SPVM::Build::ExtUtil->new->search_shared_lib_func_address($shared_lib_file, $shared_lib_func_name);
    }
  }
  
  return $native_address;
}

1;

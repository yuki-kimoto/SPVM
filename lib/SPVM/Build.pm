package SPVM::Build;

use strict;
use warnings;

use Config;
use Carp 'confess';

use SPVM::Build::SPVMInfo;
use SPVM::Build::Native;
use SPVM::Build::Precompile;
use SPVM::Build::Util;

use File::Path 'rmtree';
use File::Spec;

sub new {
  my $class = shift;
  
  my $self = {};
  
  $self->{native} = SPVM::Build::Native->new;
  
  $self->{precompile} = SPVM::Build::Precompile->new;
  
  return bless $self, $class;
}

sub native {
  my $self = shift;
  
  return $self->{native};
}

sub precompile {
  my $self = shift;
  
  return $self->{precompile};
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
    
    # Build Precompile code
    $self->precompile->build_runtime_precompile_packages;
    
    # Bind native subroutines
    $self->native->build_runtime_native_packages;
    
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
      
      my $code = "package $package_name; our \@ISA = ('SPVM::Data');";
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

1;

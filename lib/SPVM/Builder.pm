package SPVM::Builder;

use strict;
use warnings;

use Config;
use Carp 'confess';

use SPVM::Builder::C::Native;
use SPVM::Builder::C::Precompile;
use SPVM::Builder::Util;
use SPVM::Builder::Config;
use SPVM::Builder::Info;
use Scalar::Util 'weaken';

use File::Path 'rmtree';
use File::Spec;

use SPVM();

sub new {
  my $class = shift;
  
  my $self = {@_};
  
  my $build_dir = $self->{build_dir};
  
  $self->{package_infos} ||= [];
  
  bless $self, $class;
  
  $self->{info} ||= SPVM::Builder::Info->new;
  $self->{info}{builder} = $self;
  weaken($self->{info}{builder});
  
  $self->{cbuilder_native} ||= SPVM::Builder::C::Native->new(
    build_dir => $build_dir,
    info => $self->{info},
  );
  $self->{cbuilder_native}{builder} = $self;
  weaken $self->{cbuilder_native}{builder};
  
  $self->{cbuilder_precompile} ||= SPVM::Builder::C::Precompile->new(
    build_dir => $build_dir,
    info => $self->{info},
  );
  $self->{cbuilder_precompile}{builder} = $self;
  weaken $self->{cbuilder_precompile}{builder};
  
  $self->{config} ||= SPVM::Builder::Util::new_default_build_config;
  
  return $self;
}

sub build_spvm {
  my $self = shift;
  
  # Compile SPVM source code and create runtime env
  my $compile_success = $self->compile_spvm();
  
  if ($compile_success) {
    # Build Precompile packages - Compile C source codes and link them to SPVM precompile subroutine
    $self->build_precompile;
    
    # Build native packages - Compile C source codes and link them to SPVM native subroutine
    $self->build_native;
    
    # Bind SPVM to Perl
    $self->bind_to_perl;
  }
  
  return $compile_success;
}

sub use {
  my ($self, $package_name) = @_;
  
  my (undef, $file_name, $line) = caller;
  
  my $package_info = {
    name => $package_name,
    file => $file_name,
    line => $line,
  };
  
  push @{$self->{package_infos}}, $package_info;
}

sub info {
  my $self = shift;
  
  return $self->{info};
}

sub cbuilder_native {
  my $self = shift;
  
  return $self->{cbuilder_native};
}

sub cbuilder_precompile {
  my $self = shift;
  
  return $self->{cbuilder_precompile};
}

sub build_shared_lib_native_dist {
  my ($self, $package_name) = @_;
  
  $self->use($package_name);
  
  $self->compile_spvm;

  my $sub_names = $self->info->get_native_sub_names($package_name);
  
  $self->cbuilder_native->build_shared_lib_dist($package_name, $sub_names);
}

sub build_shared_lib_precompile_dist {
  my ($self, $package_name) = @_;
  
  $self->use($package_name);
  
  my $compile_success = $self->compile_spvm;
  unless ($compile_success) {
    die "Compile error";
  }
  
  my $sub_names = $self->info->get_precompile_sub_names($package_name);
  
  $self->cbuilder_precompile->build_shared_lib_dist($package_name, $sub_names);
}

sub build_precompile {
  my $self = shift;
  
  $self->cbuilder_precompile->build;
}

sub build_native {
  my $self = shift;
  
  $self->cbuilder_native->build;
}

my $package_name_h = {};

sub bind_to_perl {
  my $self = shift;

  my $package_names = $self->info->get_package_names;
  for my $package_name (@$package_names) {
    
    my $sub_names = $self->info->get_sub_names($package_name);
    
    for my $sub_name (@$sub_names) {
      my $sub_abs_name = "${package_name}::$sub_name";
      
      # Define SPVM subroutine
      no strict 'refs';
      
      my ($package_name, $sub_name) = $sub_abs_name =~ /^(?:(.+)::)(.*)/;
      unless ($package_name_h->{$package_name}) {
        
        my $code = "package $package_name; our \@ISA = ('SPVM::Data');";
        eval $code;
        
        if (my $error = $@) {
          confess $error;
        }
        $package_name_h->{$package_name} = 1;
      }
      
      # Declare subroutine
      *{"$sub_abs_name"} = sub {
        
        my $return_value;
        eval { $return_value = SPVM::call_sub($package_name, $sub_name, @_) };
        my $error = $@;
        if ($error) {
          confess $error;
        }
        $return_value;
      };
    }
  }
}

1;

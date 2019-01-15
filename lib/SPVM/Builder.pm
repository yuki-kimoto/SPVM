package SPVM::Builder;

use strict;
use warnings;

use Config;
use Carp 'confess';

use SPVM::Builder::Util;
use SPVM::Builder::Config;
use SPVM::Builder::CC;

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
  
  my $builder_c_precompile = SPVM::Builder::CC->new(
    build_dir => $self->{build_dir},
    category => 'precompile',
    builder => $self
  );
  weaken $builder_c_precompile->{builder};
  $self->{cbuilder_precompile} = $builder_c_precompile;
  
  $self->{packages} = {};
  
  return $self;
}

sub get_native_sub_names {
  my ($self, $package_name) = @_;

  my $packages = $self->{packages};
  my $package = $packages->{$package_name};
  my $subs = $package->{subs};
  
  my @native_sub_names;
  for my $sub_name (keys %$subs) {
    my $sub = $subs->{$sub_name};
    if ($sub->{have_native_desc}) {
      push @native_sub_names, $sub_name;
    }
  }
  
  return \@native_sub_names;
}

sub get_precompile_sub_names {
  my ($self, $package_name) = @_;

  my $packages = $self->{packages};
  my $package = $packages->{$package_name};
  my $subs = $package->{subs};
  
  my @precompile_sub_names;
  for my $sub_name (keys %$subs) {
    my $sub = $subs->{$sub_name};
    if ($sub->{have_precompile_desc}) {
      push @precompile_sub_names, $sub_name;
    }
  }
  
  return \@precompile_sub_names;
}

sub get_sub_names {
  my ($self, $package_name) = @_;
  
  my $packages = $self->{packages};
  my $package = $packages->{$package_name};
  my $subs = $package->{subs};
  my @sub_names = keys %$subs;
  
  return \@sub_names;
}

sub get_package_names {
  my ($self) = @_;
  
  my $packages = $self->{packages};
  my @package_names = keys %$packages;
  
  return \@package_names;
}

sub get_precompile_package_names {
  my ($self) = @_;
  
  my $precompile_package_names = [];
  
  my $package_names = $self->get_package_names;
  for my $package_name (@$package_names) {
    my $sub_names = $self->get_precompile_sub_names($package_name);
    if (@$sub_names) {
      push @$precompile_package_names, $package_name;
    }
  }
  
  return $precompile_package_names;
}

sub get_native_package_names {
  my ($self) = @_;
  
  my $native_package_names = [];
  
  my $package_names = $self->get_package_names;
  for my $package_name (@$package_names) {
    my $sub_names = $self->get_native_sub_names($package_name);
    if (@$sub_names) {
      push @$native_package_names, $package_name;
    }
  }
  
  return $native_package_names;
}

sub get_package_load_path {
  my ($self, $package_name) = @_;
  
  return $self->{packages}{$package_name}{load_path};
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

sub build_shared_object_native_dist {
  my ($self, $package_name) = @_;
  
  $self->use($package_name);
  
  $self->compile_spvm;

  my $sub_names = $self->get_native_sub_names($package_name);

  my $builder_c_native = SPVM::Builder::CC->new(
    build_dir => $self->{build_dir},
    category => 'native',
    builder => $self,
    quiet => 0,
  );
  
  $builder_c_native->build_shared_object_native_dist($package_name, $sub_names);
}

sub build_shared_object_precompile_dist {
  my ($self, $package_name) = @_;
  
  $self->use($package_name);
  
  my $compile_success = $self->compile_spvm;
  unless ($compile_success) {
    die "Compile error";
  }
  
  my $sub_names = $self->get_precompile_sub_names($package_name);

  my $builder_c_precompile = SPVM::Builder::CC->new(
    build_dir => $self->{build_dir},
    category => 'precompile',
    builder => $self,
    quiet => 0,
  );
  
  $builder_c_precompile->build_shared_object_precompile_dist($package_name, $sub_names);
}

sub build_precompile {
  my $self = shift;

  my $builder_c_precompile = SPVM::Builder::CC->new(
    build_dir => $self->{build_dir},
    category => 'precompile',
    builder => $self,
    quiet => 1,
  );
  
  $builder_c_precompile->build;
}

sub build_native {
  my $self = shift;

  my $builder_c_native = SPVM::Builder::CC->new(
    build_dir => $self->{build_dir},
    category => 'native',
    builder => $self,
    quiet => 1,
  );
  
  $builder_c_native->build;
}

my $package_name_h = {};

sub bind_to_perl {
  my $self = shift;
  
  my $package_names = $self->get_package_names;
  for my $package_name (@$package_names) {
    
    my $sub_names = $self->get_sub_names($package_name);
    
    for my $sub_name (@$sub_names) {
      if ($sub_name eq 'DESTROY') {
        next;
      }
      
      my $sub_abs_name = "${package_name}::$sub_name";
      
      # Define SPVM subroutine
      no strict 'refs';
      
      my ($package_name, $sub_name) = $sub_abs_name =~ /^(?:(.+)::)(.*)/;
      unless ($package_name_h->{$package_name}) {
        
        my $code = "package $package_name; our \@ISA = ('SPVM::Data::Package');";
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

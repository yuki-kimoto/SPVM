package SPVM::Builder;

use strict;
use warnings;

use Carp 'confess';
use Scalar::Util 'weaken';

use SPVM::Builder::CC;

# This SPVM load is needed for SPVM::Builder XS method binding to Perl
# because SPVM::Builder XS method is loaded when SPVM is loaded
use SPVM();

sub new {
  my $class = shift;
  
  my $self = {@_};
  
  my $build_dir = $self->{build_dir};
  
  $self->{package_infos} ||= [];
  
  bless $self, $class;
  
  my $cc_precompile = SPVM::Builder::CC->new(
    build_dir => $self->{build_dir},
    category => 'precompile',
    builder => $self
  );
  weaken $cc_precompile->{builder};
  $self->{cbuilder_precompile} = $cc_precompile;
  
  $self->{packages} = {};

  $self->{already_build_native_packages_h} = {};
  $self->{already_build_precompile_packages_h} = {};
  
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

sub get_module_file {
  my ($self, $package_name) = @_;
  
  return $self->{packages}{$package_name}{module_file};
}

sub get_config_file {
  my ($self, $package_name) = @_;
  
  my $module_file = $self->get_module_file($package_name);
  
  my $config_file;
  if (defined $module_file) {
    $config_file = $module_file;
    $config_file =~ s/\.spvm$/.config/;
  }
  
  return $config_file;
}

sub build_spvm {
  my $self = shift;
  
  # Compile SPVM source code and create runtime env
  $self->{compile_success} = 0;
  my $compile_success = $self->compile_spvm();
  
  if ($compile_success) {
    # Build Precompile packages - Compile C source codes and link them to SPVM precompile subroutine
    $self->build_precompile;
    
    # Build native packages - Compile C source codes and link them to SPVM native subroutine
    $self->build_native;
    
    $self->{compile_success} = 1;
  }
}

sub compile_success {
  my ($self) = @_;
  
  return $self->{compile_success};
}

sub use {
  my ($self, $package_name, $file, $line) = @_;
  
  my $package_info = {
    name => $package_name,
    file => $file,
    line => $line,
  };
  
  $self->{package_infos} = [];
  push @{$self->{package_infos}}, $package_info;
}

sub build_dll_native_dist {
  my ($self, $package_name) = @_;
  
  $self->use($package_name, '(build_dll_native_dist)', 0);
  
  $self->compile_spvm;

  my $sub_names = $self->get_native_sub_names($package_name);

  my $cc_native = SPVM::Builder::CC->new(
    build_dir => $self->{build_dir},
    category => 'native',
    builder => $self,
    quiet => 0,
  );
  
  $cc_native->build_dll_native_dist($package_name, $sub_names);
}

sub build_dll_precompile_dist {
  my ($self, $package_name) = @_;
  
  $self->use($package_name, '(build_dll_precompile_dist)', 0);
  
  my $compile_success = $self->compile_spvm;
  unless ($compile_success) {
    die "Compile error";
  }
  
  my $sub_names = $self->get_precompile_sub_names($package_name);

  my $cc_precompile = SPVM::Builder::CC->new(
    build_dir => $self->{build_dir},
    category => 'precompile',
    builder => $self,
    quiet => 0,
  );
  
  $cc_precompile->build_dll_precompile_dist($package_name, $sub_names);
}

sub build_precompile {
  my $self = shift;

  my $cc_precompile = SPVM::Builder::CC->new(
    build_dir => $self->{build_dir},
    category => 'precompile',
    builder => $self,
    quiet => 1,
  );
  
  $cc_precompile->build;
}

sub build_native {
  my $self = shift;

  my $cc_native = SPVM::Builder::CC->new(
    build_dir => $self->{build_dir},
    category => 'native',
    builder => $self,
    quiet => 1,
  );
  
  $cc_native->build;
}


1;

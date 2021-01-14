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
  
  my $self = {
    include_dirs => \@INC,
    @_
  };
  
  bless $self, ref $class || $class;
  
  $self->create_compiler;
  
  return $self;
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

sub build_dll_native_dist {
  my ($self, $package_name) = @_;
  
  $self->compile_spvm($package_name, '(build_dll_native_dist)', 0);

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
  
  my $compile_success = $self->compile_spvm($package_name, '(build_dll_precompile_dist)', 0);
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
  my ($self, $package_names) = @_;
  
  my $cc_precompile = SPVM::Builder::CC->new(
    build_dir => $self->{build_dir},
    category => 'precompile',
    builder => $self,
    quiet => 1,
  );
  
  for my $package_name (@$package_names) {
    $cc_precompile->build($package_name);
  }
}

sub build_native {
  my ($self, $package_names) = @_;

  my $cc_native = SPVM::Builder::CC->new(
    build_dir => $self->{build_dir},
    category => 'native',
    builder => $self,
    quiet => 1,
  );
  
  for my $package_name (@$package_names) {
    $cc_native->build($package_name);
  }
}

1;

=encoding UTF-8

=head1 NAME

SPVM::Builder - Compile SPVM program, bind native and precompile subroutines, generate Perl subrotuines correspoing to SPVM subroutines.

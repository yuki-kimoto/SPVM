package SPVM::Build::Config;

use strict;
use warnings;
use Config;

sub new {
  my $class = shift;
  
  my $self = {};
  
  $self->{config} = {};

  return bless $self, $class;
}

sub replace_all_config {
  my ($self, $config) = @_;
  
  $self->{config} = $config;
}

sub to_hash {
  my $self = shift;
  
  my $hash_config = {%{$self->{config}}};
  
  return $hash_config;
}

sub get_config {
  my ($self, $name) = @_;
  
  return $self->{config}{$name};
}

sub set_config {
  my ($self, $name, $value) = @_;
  
  $self->{config}{$name} = $value;
  
  return $self;
}

sub set_ccflags {
  my ($self, $ccflags) = @_;
  
  $self->set_config(ccflags => $ccflags);
  
  return $self;
}

sub get_ccflags {
  my $self = shift;
  
  return $self->get_config('ccflags');
}

sub add_ccflags {
  my ($self, $new_ccflags) = @_;
  
  my $ccflags = $self->get_config('ccflags');
  
  $ccflags .= " $new_ccflags";
  
  $self->set_config('ccflags' => $ccflags);
  
  return $self;
}

sub set_std {
  my ($self, $spec) = @_;
  
  my $ccflags = $self->get_ccflags;
  
  # Remove -std=foo section
  $ccflags =~ s/-std=[^ ]+//g;
  
  $ccflags .= " -std=$spec";
  
  # Add -std=foo section
  $self->set_ccflags($ccflags);
  
  return $self;
}

sub set_cc {
  my ($self, $cc) = @_;
  
  return $self->set_config(cc => $cc);
}

sub get_cc {
  my ($self, $cc) = @_;
  
  return $self->get_config('cc');
}

sub set_optimize {
  my ($self, $optimize) = @_;
  
  return $self->set_config(optimize => $optimize);
}

sub get_optimize {
  my ($self, $optimize) = @_;
  
  return $self->get_config('optimize');
}

sub set_ld {
  my ($self, $ld) = @_;
  
  return $self->set_config(ld => $ld);
}

sub get_ld {
  my ($self, $ld) = @_;
  
  return $self->get_config('ld');
}

sub set_ldflags {
  my ($self, $ldflags) = @_;
  
  $self->set_config(ldflags => $ldflags);
  
  return $self;
}

sub get_ldflags {
  my $self = shift;
  
  return $self->get_config('ldflags');
}

sub add_ldflags {
  my ($self, $new_ldflags) = @_;
  
  my $ldflags = $self->get_config('ldflags');
  
  $ldflags .= " $new_ldflags";
  
  $self->set_config('ldflags' => $ldflags);
  
  return $self;
}

=head1 NAME

SPVM::Build::Config - build config

=head1 DESCRIPTION

L<SPVM::Build::Config> is configuration of c/c++ compile and link.

=head1 Methods

=head2 new

  my $build_config = SPVM::Build::Config->new;
  
Create L<SPVM::Build::Config> object.

=head2 replace_all_config

  my $config = {cc => 'g++', ld => 'g++'};
  $build_config->replace_all_config($config);

Replace all config.

All of old configs is removed and added new config.

=head2 to_hash

  my $config = $build_config->to_hash;

Convert configs to hash reference.

=head2 get_config

  my $cc = $build_config->get_config('cc');

Get a config value.

=head2 set_config

  $build_config->set_config(cc => $cc);

Set a config value.

=head2 set_ccflags

  $build_config->set_ccflags($ccflags);

Set C<ccflags>.

=head2 get_ccflags

  my $ccflags = $build_config->get_ccflags;

Get C<ccflags>.

sub add_ccflags {
  my ($self, $new_ccflags) = @_;
  
  my $ccflags = $build_config->get_config('ccflags');
  
  $ccflags .= " $new_ccflags";
  
  $build_config->set_config('ccflags' => $ccflags);
  
  return $self;
}

sub set_std {
  my ($self, $spec) = @_;
  
  my $ccflags = $build_config->get_ccflags;
  
  # Remove -std=foo section
  $ccflags =~ s/-std=[^ ]+//g;
  
  $ccflags .= " -std=$spec";
  
  # Add -std=foo section
  $build_config->set_ccflags($ccflags);
  
  return $self;
}

sub set_cc {
  my ($self, $cc) = @_;
  
  return $build_config->set_config(cc => $cc);
}

sub get_cc {
  my ($self, $cc) = @_;
  
  return $build_config->get_config(cc => $cc);
}

sub set_optimize {
  my ($self, $optimize) = @_;
  
  return $build_config->set_config(optimize => $optimize);
}

sub get_optimize {
  my ($self, $optimize) = @_;
  
  return $build_config->get_config(optimize => $optimize);
}

sub set_ld {
  my ($self, $ld) = @_;
  
  return $build_config->set_config(ld => $ld);
}

sub get_ld {
  my ($self, $ld) = @_;
  
  return $build_config->get_config(ld => $ld);
}

sub set_ldflags {
  my ($self, $ldflags) = @_;
  
  $build_config->set_config(ldflags => $ldflags);
  
  return $self;
}

sub get_ldflags {
  my $self = shift;
  
  return $build_config->get_config('ldflags');
}

sub add_ldflags {


=cut

1;

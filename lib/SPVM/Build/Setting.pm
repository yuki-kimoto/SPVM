package SPVM::Build::Setting;

use strict;
use warnings;

use SPVM::Build::Setting::Config;

sub new {
  my $class = shift;
  
  my $self = {};
  
  $self->{config} = SPVM::Build::Setting::Config->new;
  
  bless $self, $class;
  
  return $self;
}

sub set_extra_compiler_flags {
  my ($self, $extra_compiler_flags) = @_;
  
  $self->{extra_compiler_flags} = $extra_compiler_flags;
  
  return $self;
}

sub get_extra_compiler_flags {
  my $self = shift;
  
  return $self->{extra_compiler_flags};
}

sub add_extra_compiler_flags {
  my ($self, $extra_compiler_flags) = @_;
  
  $self->{extra_compiler_flags} .= " $extra_compiler_flags";
  
  return $self;
}

sub set_extra_linker_flags {
  my ($self, $extra_linker_flags) = @_;
  
  $self->{extra_linker_flags} = $extra_linker_flags;
  
  return $self;
}

sub get_extra_linker_flags {
  my $self = shift;
  
  return $self->{extra_linker_flags};
}

sub add_extra_linker_flags {
  my ($self, $extra_linker_flags) = @_;
  
  $self->{extra_linker_flags} .= " $extra_linker_flags";
  
  return $self;
}

sub set_quiet_on {
  my $self = shift;
  
  $self->{quiet} = 1;
  
  return $self;
};

sub set_quiet_off {
  my $self = shift;
  
  $self->{quiet} = 0;

  return $self;
}

sub set_quiet_auto {
  my $self = shift;

  delete $self->{quiet};
  
  return $self;
}

sub get_quiet {
  my $self = shift;
  
  return $self->{quiet};
}

sub set_optimize {
  my ($self, $optimize) = @_;

  $self->{optimize} = $optimize;
  
  return $self;
}

sub get_optimize {
  my $self = shift;
  
  return $self->{optimize}
}

sub get_config {
  my $self = shift;
  
  return $self->{config};
}

1;

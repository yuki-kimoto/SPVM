package SPVM::Build::Setting::Config;

use strict;
use warnings;


sub new {
  my $class = shift;
  
  my $self = {};
  
  bless $self, $class;
  
  return $self;
}

sub set {
  my ($self, %key_values) = @_;
  
  for my $key (keys %key_values) {
    my $value = $key_values{$key};
    $self->{$key} = $value;
  }
  
  return $self;
}

sub add {
  my ($self, %key_values) = @_;
  
  for my $key (keys %key_values) {
    my $value = $key_values{$key};
    $self->{$key} .= " $value";
  }
  
  return $self;
}

sub get {
  my ($self, $key) = @_;
  
  return $self->{$key};
}

sub to_hash {
  my $self = shift;
  
  my $hash = {%$self};
  
  return $hash;
}

=head1 NAME

SPVM::Build::Setting::Config;

=head1 DESCRIPTION

L<ExtUtils::CBuilder> config option of C<new> method.

=cut

1;

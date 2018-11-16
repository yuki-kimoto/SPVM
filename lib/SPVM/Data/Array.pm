package SPVM::Data::Array;

use base 'SPVM::Data';

use SPVM::PerlAPI;

sub to_elements {
  my $self = shift;
  
  my $env = $self->{env};
  
  SPVM::PerlAPI::to_elements($env, $self);
}

sub to_binary {
  my $self = shift;

  my $env = $self->{env};
  
  SPVM::PerlAPI::to_binary($env, $self);
}

1;

=head1 NAME

SPVM::Data::Array - Array object

package SPVM::Data::String;

use base 'SPVM::Data';

use SPVM::ExchangeAPI;

sub to_elements {
  my $self = shift;
  
  my $env = $self->{env};
  
  SPVM::ExchangeAPI::to_elements($env, $self);
}

sub to_binary {
  my $self = shift;

  my $env = $self->{env};
  
  SPVM::ExchangeAPI::to_binary($env, $self);
}

sub to_string {
  my $self = shift;
  
  my $env = $self->{env};
  
  SPVM::ExchangeAPI::to_string($env, $self);
}

1;

=head1 NAME

SPVM::Data::String - SPVM String

=head1 METHODS

=head2 to_elements

  my $byte_array = $spvm_string->to_elements;

Convert SPVM string to Perl array reference.

Each element is corresponding byte of SPVM string.

=head2 to_binary

  my $binary = $spvm_string->to_binary;

Convert SPVM string to Perl byte string(encoded string).

=head2 to_string

  my $string = $spvm_string->to_string;

Convert SPVM string to Perl text string(decoded string).

=cut

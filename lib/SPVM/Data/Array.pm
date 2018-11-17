package SPVM::Data::Array;

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

SPVM::Data::Array - SPVM Array

=head1 METHODS

=head2 to_elements

  my $nums = $spvm_nums->to_elements;

Convert SPVM array to Perl array reference.

=head2 to_binary

  my $binary = $spvm_nums->to_binary;

Convert SPVM array to binary data.

Binary data is unpacked by C<unpack> function.

An exmaple when array is int array:

  my @nums = unpack 'l*', $binary;

=head2 to_string

  my $string = $spvm_nums->to_string;

Convert SPVM array to perl text string(decoded string).

This method have mean only when SPVM array is byte array.

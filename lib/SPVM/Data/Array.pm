package SPVM::Data::Array;

use base 'SPVM::Data';

use SPVM::ExchangeAPI;

sub to_elems {
  my $self = shift;
  
  my $env = $self->{env};
  
  SPVM::ExchangeAPI::to_elems($env, $self);
}

sub to_bin {
  my $self = shift;

  my $env = $self->{env};
  
  SPVM::ExchangeAPI::to_bin($env, $self);
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

=head2 to_elems

  my $nums = $spvm_nums->to_elems;

Convert SPVM array to Perl array reference.

=head2 to_bin

  my $binary = $spvm_nums->to_bin;

Convert SPVM array to binary data.

Binary data is unpacked by C<unpack> function.

An exmaple when array is int array:

  my @nums = unpack 'l*', $binary;

=head2 to_string

  my $string = $spvm_nums->to_string;

Convert SPVM array to perl text string(decoded string).

This method have mean only when SPVM array is byte array.

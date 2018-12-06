package SPVM::Data::String;

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

SPVM::Data::String - SPVM String

=head1 METHODS

=head2 to_elems

  my $byte_array = $spvm_string->to_elems;

Convert SPVM string to Perl array reference.

Each element is corresponding byte of SPVM string.

=head2 to_bin

  my $binary = $spvm_string->to_bin;

Convert SPVM string to Perl byte string(encoded string).

=head2 to_string

  my $string = $spvm_string->to_string;

Convert SPVM string to Perl text string(decoded string).

=cut

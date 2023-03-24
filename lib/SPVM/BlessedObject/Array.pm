package SPVM::BlessedObject::Array;

use strict;
use warnings;

use base 'SPVM::BlessedObject';

use overload '@{}' => sub {
  my ($array) = @_;
  
  my $elems = $array->to_elems;
  
  return $elems;
};

use overload fallback => 1;

use SPVM::ExchangeAPI;

sub length {
  my $self = shift;
  
  return $self->_xs_length;
}

sub to_elems {
  my $self = shift;
  
  return $self->api->array_to_elems($self);
}

sub to_strings {
  my $self = shift;
  
  my $elems = $self->to_elems;
  
  my $strings = [map { $_->to_string } @$elems];
  
  return $strings;
}

sub to_bins {
  my $self = shift;
  
  my $elems = $self->to_elems;
  
  my $binaries = [map { $_->to_bin } @$elems];
  
  return $binaries;
}

sub to_bin {
  my $self = shift;

  $self->api->array_to_bin($self);
}

sub set {
  my $self = shift;
  
  $self->api->array_set($self, @_);
}

sub get {
  my $self = shift;
  
  $self->api->array_get($self, @_);
}

1;

=head1 Name

SPVM::BlessedObject::Array - SPVM Array

=head2 DESCRIPTION

The object of the C<SPVM::BlessedObject::Array> class holds a SPVM array.

=head1 Usage

  # Gets an element of the array
  my $elem = $blessed_object_array->get(2);
  
  # Sets an element of the array
  $blessed_object_array->set(2 => 5);
  
  # Converts a SPVM array to a Perl array reference
  my $elems = $blessed_object_array->to_elems;
  
  # Converts a SPVM array to a binary
  my $binary = $blessed_object_array->to_bin;

=head1 Methods

=head2 get

  my $elem = $blessed_object_array->get(2);

Returns an element of the array with the index.

=head2 set

  $blessed_object_array->set(2 => 5);

Sets an element of the array with the index.

=head2 to_elems

  my $elems = $blessed_object_array->to_elems;

Converts a SPVM array to a Perl array reference and returns it.

=head2 to_bin

  my $binary = $blessed_object_array->to_bin;

Converts a SPVM array to a binary and returns it.

This binary is unpacked by L<unpack|https://perldoc.perl.org/functions/unpack> function.

Examples:

  # byte[]
  my @elems = unpack 'c*', $binary;
  
  # short[]
  my @elems = unpack 's*', $binary;
  
  # int[]
  my @elems = unpack 'l*', $binary;

  # long[]
  my @elems = unpack 'q*', $binary;

  # float[]
  my @elems = unpack 'f*', $binary;

  # double[]
  my @elems = unpack 'd*', $binary;

=head2 to_strings

  my $elems = $blessed_object_array->to_strings;

Converts a SPVM string array to a Perl array reference and returns it.

Each element calls L<to_string|SPVM::BlessedObject::String/"to_string"> method.

=head2 to_bins

  my $elems = $blessed_object_array->to_bins;

Converts a SPVM string array to Perl array reference and returns it.

Each element calls L<to_bin|SPVM::BlessedObject::String/"to_bin"> method.

=head1 Operators

Overloads the following operators.

=head2 array dereference
  
  my @elems = @$array;

This is the same as the following operation.

  my @elems = @{$array->to_elems};

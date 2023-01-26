package SPVM::BlessedObject::Array;

use strict;
use warnings;

use base 'SPVM::BlessedObject';

use overload '@{}' => sub {
  my ($array) = @_;
  
  my $elements = $array->to_elems;
  
  return $elements;
};

use overload fallback => 1;

use SPVM::ExchangeAPI;

sub length {
  my $self = shift;
  
  $self->api->array_length($self);
}

sub to_elems {
  my $self = shift;
  
  $self->api->array_to_elems($self);
}

sub to_strings {
  my $self = shift;
  
  my $elems = $self->api->array_to_elems($self);
  
  my $strings = [map { $_->to_string } @$elems];
  
  return $strings;
}

sub to_bins {
  my $self = shift;
  
  my $elems = $self->api->array_to_elems($self);
  
  my $strings = [map { $_->to_bin } @$elems];
  
  return $strings;
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

SPVM::BlessedObject::Array - Array based blessed object

=head2 DESCRIPTION

SPVM::BlessedObject::Array is array based blessed object.

This object contains SPVM array object.

=head1 Usage

  # Get the value of an array element
  my $value = $sp_array->get(2);

  # Set the value of an array element
  $sp_array->set(2 => 5);
  
  # Convert SPVM array to Perl array reference
  my $elems = $sp_array->to_elems;

  # Convert SPVM array to Perl binary data
  my $binary = $sp_array->to_bin;
  
=head1 Methods

=head2 get

  my $value = $sp_array->get(2);

Get the value of an array element.

=head2 set

  $sp_array->set(2 => 5);

Set the value of an array element

=head2 to_elems

  my $elems = $sp_array->to_elems;

Convert SPVM array to Perl array reference.

=head2 to_bin

  my $binary = $sp_array->to_bin;

Convert SPVM array to binary data.

Binary data is unpacked by C<unpack> function.

An exmaple when array is int array:

  my @nums = unpack 'l*', $binary;

=head2 to_strings

  my $elems = $sp_array->to_strings;

Convert SPVM C<string> array to Perl string array reference by calling C<to_string> method of each element.

=head2 to_bins

  my $elems = $sp_array->to_bins;

Convert SPVM C<string> array to Perl binary array reference by calling C<to_bin> method of each element.

=head1 Operators

L<SPVM::BlessedObject::Array> overloads the following operators.

=head2 array dereference
  
Array dereference get the elements of the array.

  # Get elements
  my @elements = @$array;

This is the same as the following.

  my @elements = @{$array->to_elems};

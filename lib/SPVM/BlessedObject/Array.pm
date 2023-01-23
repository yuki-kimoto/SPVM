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

sub to_string {
  my $self = shift;
  
  my $elems = $self->api->array_to_elems($self);
  
  my $string = join(" ", @$elems);
  
  return $string;
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
  my $value = $spvm_nums->get(2);

  # Set the value of an array element
  $spvm_nums->set(2 => 5);
  
  # Convert SPVM array to Perl array reference
  my $nums = $spvm_nums->to_elems;

  # Convert SPVM array to Perl binary data
  my $binary = $spvm_nums->to_bin;
  
=head1 Methods

=head2 get

  my $value = $spvm_nums->get(2);

Get the value of an array element.

=head2 set

  $spvm_nums->set(2 => 5);

Set the value of an array element

=head2 to_elems

  my $nums = $spvm_nums->to_elems;

Convert SPVM array to Perl array reference.

=head2 to_bin

  my $binary = $spvm_nums->to_bin;

Convert SPVM array to binary data.

Binary data is unpacked by C<unpack> function.

An exmaple when array is int array:

  my @nums = unpack 'l*', $binary;

=head1 Operators

L<SPVM::BlessedObject::Array> overloads the following operators.

=head2 array dereference
  
Array dereference get the elements of the array.

  # Get elements
  my @elements = @$array;

This is the same as the following.

  my @elements = @{$array->to_elems};

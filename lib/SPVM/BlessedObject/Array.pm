package SPVM::BlessedObject::Array;

use base 'SPVM::BlessedObject';

use overload '@{}' => sub {
  my ($array) = @_;
  
  my $elements = $array->to_elems;
  
  return $elements;
};

use SPVM::ExchangeAPI;

sub length {
  my $self = shift;
  
  SPVM::ExchangeAPI::array_length($SPVM::BUILDER, $self);
}

sub to_elems {
  my $self = shift;
  
  SPVM::ExchangeAPI::array_to_elems($SPVM::BUILDER, $self);
}

sub to_bin {
  my $self = shift;

  SPVM::ExchangeAPI::array_to_bin($SPVM::BUILDER, $self);
}

sub set {
  my $self = shift;
  
  SPVM::ExchangeAPI::array_set($SPVM::BUILDER, $self, @_);
}

sub get {
  my $self = shift;
  
  SPVM::ExchangeAPI::array_get($SPVM::BUILDER, $self, @_);
}

1;

=head1 Name

SPVM::BlessedObject::Array - Array based blessed object

=head2 DESCRIPTION

SPVM::BlessedObject::Array is array based blessed object.

This object contains SPVM array object.

=head1 Synopsys

  # Get the value of a array element
  my $value = $spvm_nums->get(2);

  # Set the value of a array element
  $spvm_nums->set(2 => 5);
  
  # Convert SPVM array to Perl array reference
  my $nums = $spvm_nums->to_elems;

  # Convert SPVM array to Perl binary data
  my $binary = $spvm_nums->to_bin;
  
=head1 Methods

=head2 get

  my $value = $spvm_nums->get(2);

Get the value of a array element.

=head2 set

  $spvm_nums->set(2 => 5);

Set the value of a array element

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

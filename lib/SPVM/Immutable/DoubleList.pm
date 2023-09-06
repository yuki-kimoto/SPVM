package SPVM::Immutable::DoubleList;

1;

=head1 Name

SPVM::Immutable::DoubleList - Immutable double Array

=head1 Description

The Immutable::DoubleList class has methods to manipulate an immutable double array.

=head1 Usage
  
  use Immutable::DoubleList;
  
  # Create a double list
  my $list = Immutable::DoubleList->new;
  my $list = Immutable::DoubleList->new([(double)1, 2, 3]);
  
  # Create a double list with array length
  my $list = Immutable::DoubleList->new_len(10);
  
  # Get list length
  my $length = $list->length;
  
  # Get value.
  my $element = $list->get(2);
  
  # Convert list to array.
  my $array = $list->to_array;
  
=head1 Fields

=head2 length

  has length : ro int;

Gets the C<length> field.

This field is the length of the elements of the list.

=head1 Class Methods

=head2 new

  static method new : Immutable::DoubleList ($array : double[] = undef);

Create a new L<Immutable::DoubleList|SPVM::Immutable::DoubleList> object using L</"new_len">.

The passed length to L</"new_len"> is the length of the array. If the array is undef, the length is 0.

The elements of the array are copied to the elements of the the created array.

Examples:

  my $list = Immutable::DoubleList->new;
  my $list = Immutable::DoubleList->new([(double)1, 2, 3]);

=head2 new_len

  static method new_len : Immutable::DoubleList ($length : int);

Creates a new L<Immutable::DoubleList|SPVM::Immutable::DoubleList> object with $length and $capacity.

Exceptions:

$length must be greater than or equal to 0. Otherwise an exception is thrown.

=head1 Instance Methods

=head2 get

  method get : double ($index : int);

Gets the element of the position of $index.

Exceptions:

$index must be greater than or equal to 0. Otherwise an exception is thrown.

$index must be less than the length of $list.

=head2 to_array

  method to_array : double[] ();

Converts the list to an array.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

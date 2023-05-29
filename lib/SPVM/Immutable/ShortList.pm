package SPVM::Immutable::ShortList;

1;

=head1 Name

SPVM::Immutable::ShortList - Immutable short Array

=head1 Description

The Immutable::ShortList class has methods to manipulate an immutable short array.

=head1 Usage
  
  use Immutable::ShortList;
  
  # Create a short list
  my $list = Immutable::ShortList->new;
  my $list = Immutable::ShortList->new([(short)1, 2, 3]);
  
  # Create a short list with array length
  my $list = Immutable::ShortList->new_len(10);
  
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

  static method new : Immutable::ShortList ($array : short[] = undef);

Create a new L<Immutable::ShortList|SPVM::Immutable::ShortList> object using L</"new_len">.

The passed length to L</"new_len"> is the length of the array. If the array is undef, the length is 0.

The elements of the array are copied to the values of the the created array.

Examples:

  my $list = Immutable::ShortList->new;
  my $list = Immutable::ShortList->new([(short)1, 2, 3]);

=head2 new_len

  static method new_len : Immutable::ShortList ($length : int);

Creates a new L<Immutable::ShortList|SPVM::Immutable::ShortList> object with the $length.

Exceptions:

The $length must be greater than or equal to 0. Otherwize an exception is thrown.

=head1 Instance Methods

=head2 get

  method get : int ($index : int);

Gets the element of the position of the $index.

Exceptions:

The $index must be greater than or equal to 0. Otherwize an exception is thrown.

The $index must be less than the length of the $list. Otherwize an exception is thrown.

=head2 to_array

  method to_array : short[] ();

Converts the list to an array.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

package SPVM::FloatList;

1;

=head1 Name

SPVM::FloatList - Dynamic float Array

=head1 Usage
  
  use FloatList;
  
  # Create a float list
  my $list = FloatList->new;
  my $list = FloatList->new([(float)1, 2, 3]);
  
  # Create a float list with array length
  my $list = FloatList->new_len(10);
  
  # Get list length
  my $length = $list->length;
  
  # Push value
  $list->push((float)3);
  
  # Pop value.
  my $element = $list->pop;
  
  # Unshift value.
  $list->unshift((float)3);
  
  # Shift value.
  my $element = $list->shift;
  
  # Set value.
  $list->set(2, (float)3);
  
  # Get value.
  my $element = $list->get(2);
  
  # Insert value
  $list->insert(1, 3);
  
  # Remove value
  my $element = $list->remove(1);
  
  # Convert list to array.
  my $array = $list->to_array;
  
=head1 Description

C<FloatList> is a dynamic C<float> array.

=head1 Enumerations

  enum {
    DEFAULT_CAPACITY = 4,
  }

=head2 DEFAULT_CAPACITY

The default capacity. The value is 4.

=head1 Fields

=head2 capacity

  has capacity : ro int;

The capacity. This is the length of the internally reserved elements to extend the length of the list.

=head2 length

  has length : ro int;

The length of the list.

=head1 Class Methods

=head2 new

C<static method new : L<FloatList|SPVM::FloatList> ($array : float[] = undef, $capacity : int = -1);>

Create a new C<FloatList> object using L</"new_len">.

The passed length to L</"new_len"> is the length of the array. If the array is undef, the length is 0.

The elements of the array are copied to the elements of the the created array.

Examples:

  my $list = FloatList->new;
  my $list = FloatList->new([(float)1, 2, 3]);

=head2 new_len

C<static method new_len : L<FloatList|SPVM::FloatList> ($length : int, $capacity : int = -1);>

Creates a new C<FloatList> object with $length and $capacity.

If $capacity is less than 0, the capacity is set to the value of L</"DEFAULT_CAPACITY">.

If $length is greater than $capacity, $capacity is set to $length.

Exceptions:

$length must be greater than or equal to 0. Otherwise an exception is thrown.

=head1 Instance Methods

=head2 get

C<method get : float ($index : int);>

Gets the element of the position of $index.

Exceptions:

$index must be greater than or equal to 0. Otherwise an exception is thrown.

$index must be less than the length of $list.

=head2 insert

C<method insert : void ($index : int, $element : float);>

Inserts an $element to the position of $index.

Exceptions:

$index must be greater than or equal to 0. Otherwise an exception is thrown.

$index must be less than or equal to the length of $list. Otherwise an exception is thrown.

=head2 pop

C<method pop : float ();>

Removes the last element and return it.

Exceptions:

The length of $list must be greater than 0. Otherwise an exception is thrown.

=head2 push
  
C<method push : void ($element : float);>

Adds an $element after the end of the list.

=head2 remove

C<method remove : float ($index : int);>

Removes the element at the position of $index and return it.

Exceptions:

$index must be greater than or equal to 0. Otherwise an exception is thrown.

$index must be less than the length of $list.

=head2 replace

C<method replace : void ($offset : int, $remove_length : int, $replace : float[]);>

Replaces the elements of the range specified by $offset and $lenght with $replace array.

Exceptions:

$offset must be greater than or equal to 0. Otherwise an exception is thrown.

$remove_length must be greater than or equal to 0. Otherwise an exception is thrown.

$offset + $removing lenght must be less than or equal to the length of $list. Otherwise an exception is thrown.

=head2 reserve

C<method reserve : void ($new_capacity : int);>

Reserves the elements with $new_capacity.

If $new_capacity is greater than the capacity of the list, the capacity of the list is extended to $new_capacity.

Exceptions:

$new_capacity must be greater than or equal to 0. Otherwise an exception is thrown.

=head2 resize

C<method resize : void ($new_length : int);>

Resize the list with $new_length.

Exceptions:

$new_length must be greater than or equal to 0. Otherwise an exception is thrown.

=head2 set

C<method set : void ($index : int, $element : float);>

Sets $element at the position of $index.

Exceptions:

$index must be greater than or equal to 0. Otherwise an exception is thrown.

$index must be less than the length of $list. Otherwise an exception is thrown.

=head2 set_array

C<method set_array : void ($array : float[]);>

Sets an $array. Each element of $array is copied to the element of the list.

Exceptions:

$array must be defined. Otherwise an exception is thrown.

The length of $array must be equal to the length of $list. Otherwise an exception is thrown.

=head2 shift

C<method shift : float ();>

Removes the first element and return it.

Exceptions:

The length of $list must be greater than 0. Otherwise an exception is thrown.

=head2 to_array

C<method to_array : float[] ();>

Creates a new array with the length of the list and copies all elements of the list into the new array, and returns it.

=head2 get_array_unsafe

C<method get_array_unsafe : float[] ();>

Gets the internally array.

This array is unsafe because it continues to point to the old array if the internal array is extended.

=head2 unshift

C<method unshift : void ($element : float);>

Inserts an $element at the beginning of the list.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

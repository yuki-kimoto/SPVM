package SPVM::DoubleList;

1;

=head1 Name

SPVM::DoubleList - Dynamic double Arrays

=head1 Description

The DoubleList class in L<SPVM> has methods to manipulate dynamic double arrays.

=head1 Usage
  
  use DoubleList;
  
  # Create a double list
  my $list = DoubleList->new;
  my $list = DoubleList->new([(double)1, 2, 3]);
  
  # Create a double list with array length
  my $list = DoubleList->new_len(10);
  
  # Get list length
  my $length = $list->length;
  
  # Push value
  $list->push((double)3);
  
  # Pop value.
  my $element = $list->pop;
  
  # Unshift value.
  $list->unshift((double)3);
  
  # Shift value.
  my $element = $list->shift;
  
  # Set value.
  $list->set(2, (double)3);
  
  # Get value.
  my $element = $list->get(2);
  
  # Insert value
  $list->insert(1, 3);
  
  # Remove value
  my $element = $list->remove(1);
  
  # Convert list to array.
  my $array = $list->to_array;
  
=head1 Details

=head2 Internal Data Structure

The L</"array"> stored in a DoubleList object always starts at index 0.

The elements in the range that is greater than or equal to the L</"length"> field and less than the L</"capacity"> field are filled with 0.

=head1 Fields

=head2 capacity

 C<has capacity : ro int;>

The capacity. This is the length of the internally reserved elements to extend the length of the list.

=head2 length

C<has length : ro int;>

The length of the list.

=head2 array

C<has array : double[];>

The internal array stored in the DoubleList object.

=head1 Class Methods

=head2 new

C<static method new : L<DoubleList|SPVM::DoubleList> ($array : double[] = undef, $capacity : int = -1);>

Create a new C<DoubleList> object using L</"new_len">.

The passed length to L</"new_len"> is the length of the array. If the array is undef, the length is 0.

The elements of the array are copied to the elements of the the created array.

Examples:

  my $list = DoubleList->new;
  my $list = DoubleList->new([(double)1, 2, 3]);

=head2 new_len

C<static method new_len : L<DoubleList|SPVM::DoubleList> ($length : int, $capacity : int = -1);>

Creates a new C<DoubleList> object with $length and $capacity.

If $capacity is less than 0, the capacity is set to the default value.

If $length is greater than $capacity, $capacity is set to $length.

Exceptions:

$length must be greater than or equal to 0. Otherwise an exception is thrown.

=head1 Instance Methods

=head2 get

C<method get : double ($index : int);>

Gets the element of the position of $index.

Exceptions:

$index must be greater than or equal to 0. Otherwise an exception is thrown.

$index must be less than the length of $list.

=head2 insert

C<method insert : void ($index : int, $element : double);>

Inserts an $element to the position of $index.

Exceptions:

$index must be greater than or equal to 0. Otherwise an exception is thrown.

$index must be less than or equal to the length of $list.

=head2 pop

C<method pop : double ();>

Removes the last element and return it.

Exceptions:

The length of $list must be greater than 0. Otherwise an exception is thrown.

=head2 push
  
C<method push : void ($element : double);>

Adds an $element after the end of the list.

=head2 remove

C<method remove : double ($index : int);>

Removes the element at the position of $index and return it.

Exceptions:

$index must be greater than or equal to 0. Otherwise an exception is thrown.

$index must be less than the length of $list. Otherwise an exception is thrown.

=head2 replace

C<method replace : void ($offset : int, $remove_length : int, $replace : double[]);>

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

C<method set : void ($index : int, $element : double);>

Sets $element at the position of $index.

Exceptions:

$index must be greater than or equal to 0. Otherwise an exception is thrown.

$index must be less than the length of $list. Otherwise an exception is thrown.

=head2 shift

C<method shift : double ();>

Removes the first element and return it.

Exceptions:

The length of $list must be greater than 0. Otherwise an exception is thrown.

=head2 to_array

C<method to_array : double[] ();>

Creates a new array with the length of the list and copies all elements of the list into the new array, and returns it.

=head2 get_array_unsafe

C<method get_array_unsafe : double[] ();>

Gets the internally array.

This array is unsafe because it continues to point to the old array if the internal array is extended.

=head2 unshift

C<method unshift : void ($element : double);>

Inserts an $element at the beginning of the list.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

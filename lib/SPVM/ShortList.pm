package SPVM::ShortList;

1;

=head1 Name

SPVM::ShortList - Dynamic short Arrays

=head1 Description

The ShortList class in L<SPVM> has methods to manipulate dynamic short arrays.

=head1 Usage
  
  use ShortList;
  
  # Create a short list
  my $list = ShortList->new;
  my $list = ShortList->new([(short)1, 2, 3]);
  
  # Create a short list with array length
  my $list = ShortList->new_len(10);
  
  # Get list length
  my $length = $list->length;
  
  # Push value
  $list->push(3);
  
  # Pop value.
  my $element = $list->pop;
  
  # Unshift value.
  $list->unshift(3);
  
  # Shift value.
  my $element = $list->shift;
  
  # Set value.
  $list->set(2, 3);
  
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

The L</"array"> stored in a ShortList object always starts at index 0.

The elements in the range that is greater than or equal to L</"length"> field and less than L</"capacity"> field are filled with 0.

=head1 Interfaces

=over 2

=item * L<Cloneable|SPVM::Cloneable>

=item * L<Countable|SPVM::Countable>

=back

=head1 Fields

=head2 capacity

C<has capacity : ro int;>

The capacity. This is the length of the internally reserved elements to extend the length of the list.

=head2 length

C<has length : ro int;>

The length of the list.

=head2 array

C<has array : short[];>

The internal array stored in the ShortList object.

=head1 Class Methods

=head2 new

C<static method new : L<ShortList|SPVM::ShortList> ($array : short[] = undef, $capacity : int = -1);>

Create a new C<ShortList> object using L</"new_len">.

The passed length to L</"new_len"> is the length of the array. If the array is undef, the length is 0.

The elements of the array are copied to the elements of the the created array.

Examples:

  my $list = ShortList->new;
  my $list = ShortList->new([(short)1, 2, 3]);

=head2 new_len

C<static method new_len : L<ShortList|SPVM::ShortList> ($length : int, $capacity : int = -1);>

Creates a new C<ShortList> object with $length and $capacity.

If $capacity is less than 0, the capacity is set to the default value.

If $length is greater than $capacity, $capacity is set to $length.

Exceptions:

$length must be greater than or equal to 0. Otherwise an exception is thrown.

=head2 new_ref

C<static method new_ref : L<ShortList|SPVM::ShortList> ($array : short[]);>

Creates a new L<ShortList|SPVM::ShortList> object, and set L</"array"> field to the array $array, and return the new object.

Exceptions:

The array $array must be defined. Otherwise an exception is thrown.

=head1 Instance Methods

=head2 get

C<method get : int ($index : int);>

Gets the element of the position of $index.

If $index is a netative value, $index is set to L</"length"> plus $index.

Exceptions:

$index must be greater than or equal to 0. Otherwise an exception is thrown.

$index must be less than the length of $list. Otherwise an exception is thrown.

=head2 insert

C<method insert : void ($index : int, $element : int);>

Inserts an $element to the position of $index.

Exceptions:

$index must be greater than or equal to 0. Otherwise an exception is thrown.

$index must be less than or equal to the length of $list. Otherwise an exception is thrown.

=head2 pop

C<method pop : int ();>

Removes the last element and return it.

Exceptions:

The length of $list must be greater than 0. Otherwise an exception is thrown.

=head2 push
  
C<method push : void ($element : int);>

Adds an $element after the end of the list.

=head2 remove

C<method remove : int ($index : int);>

Removes the element at the position of $index and return it.

Exceptions:

$index must be greater than or equal to 0. Otherwise an exception is thrown.

$index must be less than the length of $list. Otherwise an exception is thrown.

=head2 replace

C<method replace : void ($offset : int, $remove_length : int, $replace : short[] = undef);>

Same as L</"splice"> method, but the return vlaue is not returned.

Exceptions:

Exceptions thrown by L</"splice"> method could be thrown.

=head2 splice

C<method splice : short[] ($offset : int, $remove_length : int, $replace : short[] = undef);>

Replaces the elements of the range specified by $offset and $length with $replace array, and returns removed elements creating a new array.

If $replace is not defined, the replacemnet is not performed.

Exceptions:

$offset must be greater than or equal to 0. Otherwise an exception is thrown.

$remove_length must be greater than or equal to 0. Otherwise an exception is thrown.

$offset + $removing length must be less than or equal to the length of $list. Otherwise an exception is thrown.

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

C<method set : void ($index : int, $element : int);>

Sets $element at the position of $index.

If $index is a netative value, $index is set to L</"length"> plus $index.

Exceptions:

$index must be greater than or equal to 0. Otherwise an exception is thrown.

$index must be less than the length of $list. Otherwise an exception is thrown.

=head2 shift

C<method shift : int ();>

Removes the first element and return it.

Exceptions:

The length of $list must be greater than 0. Otherwise an exception is thrown.

=head2 to_array

C<method to_array : short[] ();>

Creates a new array with the length of the list and copies all elements of the list into the new array, and returns it.

=head2 get_array

C<method get_array : short[] ();>

Returns the internal L</"array">.

=head2 unshift

C<method unshift : void ($element : int);>

Inserts an $element at the beginning of the list.

=head2 clone

C<method clone : L<ShortList|SPVM::ShortList> ();>

Clones this instance and returns it.

=head2 push_

C<method push_ : void ($elements : short[]);>

Adds the elements $elements after the end of this list.

This method calls L</"push"> method internally.

Exceptions:

The elements $elements must be defined.

Exceptions thrown by L</"push"> method could be thrown.

=head2 unshift_

C<method unshift_ : void ($elements : short[]);>

Inserts the elemnets $elements at the beginning of the list.

Exceptions:

The elements $elements must be defined.

Exceptions thrown by L</"unshift"> method could be thrown.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

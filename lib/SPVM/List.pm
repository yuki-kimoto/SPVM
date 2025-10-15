package SPVM::List;

1;

=head1 Name

SPVM::List - Dynamic Object Array

=head1 Usage
  
  use List;
  
  # Create an object list
  my $list = List->new;
  my $list = List->new([(object)Byte->new(1), Int->new(2), Long->new(3)]);

  # Create a Int list
  my $list = List->new([Int->new(1), Int->new(2), Int->new(3)]);
  
  # Create an object list with length
  my $list = List->new_len([], 3);

  # Create a Int list with length
  my $list = List->new_len(new Int[0], 3);

  # Get list length
  my $length = $list->length;
  
  # Push object value
  $list->push(Int->new(3));

  # Pop object value.
  my $element = $list->pop;

  # Unshift object value.
  $list->unshift(Int->new(3));
  
  # Shift object value.
  my $element = $list->shift;
  
  # Set object value.
  $list->set(2, Int->new(3));
  
  # Get object value.
  my $element = $list->get(2);

  # Insert object value
  $list->insert(1, Int->new(3));

  # Remove object value
  my $element = $list->remove(1);

  # Convert List to object array.
  my $int_array = $list->to_array;

  # Convert List to Int array.
  my $int_array = (Int[])$list->to_array;

=head1 Description

C<List> class in L<SPVM> is the dynamic object array that has a specified object array type.

=head1 Details

=head2 Internal Data Structure

The L</"array"> stored in an IntList object always starts at index 0.

The elements in the range that is greater than or equal to L</"length"> field and less than L</"capacity"> field are filled with C<undef>.

=head1 Interfaces

=over 2

=item * L<Cloneable|SPVM::Cloneable>

=item * L<Countable|SPVM::Countable>

=back

=head1 Fields

=head2 capacity

C<has capacity : virtual ro int;>

The capacity. This is the length of the internally reserved elements to extend the length of the list.

=head2 length

C<has length : virtual ro int;>

The length of the list.

=head1 Class Methods

=head2 new

C<static method new : L<List|SPVM::List> ($array : object[] = undef, $capacity : int = -1);>

Creates a new C<List> object using L</"new_len">.

The passed length to L</"new_len"> is the length of $array. If the array is undef, the length is 0.

The element's addresses of the object array are copied to the elements of the the created array.
  
  # object[]
  my $list = List->new([(object)Byte->new(1), Int->new(2), Long->new(3)]);
  
  # Int[]
  my $list = List->new([Int->new(1), Int->new(2), Int->new(3)]);

=head2 new_len

C<static method new_len : L<List|SPVM::List> ($proto_array : object[], $length : int, $capacity : int = -1);>

Creates a new C<StringList> object with $protot_array, $length and $capacity.

If $protot_array is undefined, $protot_array is set to an C<object[]> object.

If $capacity is less than 0, $capacity is set to the default value.

If $length is greater than $capacity, $capacity is set to the length.

Exceptions:

$length must be greater than or equal to 0. Otherwise an exception is thrown.

Examples:

  # Create a Int list with length
  my $list = List->new_len(new Int[0], 3);

=head2 new_ref

C<static method new_ref : L<List|SPVM::List> ($array : object[]);>

Creates a new L<List|SPVM::List> object, and set L</"array"> field to the array $array, and return the new object.

Exceptions:

The array $array must be defined. Otherwise an exception is thrown.

=head1 Instance Methods

=head2 get

C<method get : element ($index : int);>

Gets the element of the position of $index.

If $index is a netative value, $index is set to L</"length"> plus $index.

Exceptions:

$index must be greater than or equal to 0. Otherwise an exception is thrown.

$index must be less than the length of $list. Otherwise an exception is thrown.

=head2 insert

C<method insert : void ($index : int, $element : object);>

Inserts an $element to the position of $index.

Exceptions:

$index must be greater than or equal to 0. Otherwise an exception is thrown.

$index must be less than or equal to the length of $list. Otherwise an exception is thrown.

=head2 pop

C<method pop : element ();>

Removes the last element and return it.

Exceptions:

The length of $list must be greater than 0. Otherwise an exception is thrown.
            
=head2 push
  
C<method push : void ($element : object);>

Adds an $element after the end of the list.

=head2 remove

C<method remove : element ($index : int);>

Removes the element at the position of $index and return it.

Exceptions:

$index must be greater than or equal to 0. Otherwise an exception is thrown.

$index must be less than the length of $list. Otherwise an exception is thrown.

=head2 replace

C<method replace : void ($offset : int, $remove_length : int, $replace : object[] = undef);>

Same as L</"splice"> method, but the return vlaue is not returned.

Exceptions:

Exceptions thrown by L</"splice"> method could be thrown.

=head2 splice

C<method splice : element[] ($offset : int, $remove_length : int, $replace : object[] = undef);>

Replaces the elements of the range specified by $offset and $length with $replace array, and returns removed elements creating a new array.

If $replace is not defined, the replacemnet is not performed.

Exceptions:

$offset must be greater than or equal to 0. Otherwise an exception is thrown.

$remove_length must be greater than or equal to 0. Otherwise an exception is thrown.

$offset + $removing length must be less than or equal to the length of $list. Otherwise an exception is thrown.

=head2 reserve

C<method reserve : void ($new_capacity : int);>

If $new_capacity is greater than the capacity of the list, the capacity of the list is extended to $new_capacity.

=head2 resize

C<method resize : void ($new_length : int);>

Resize the list with $new_length.

Exceptions:

$new_length must be greater than or equal to 0. Otherwise an exception is thrown.

=head2 set

C<method set : void ($index : int, $element : object);>

Sets $element at the position of $index.

If $index is a netative value, $index is set to L</"length"> plus $index.

Exceptions:

$index must be greater than or equal to 0. Otherwise an exception is thrown.

$index must be less than the length of $list. Otherwise an exception is thrown.

=head2 shift

C<method shift : element ();>

Removes the first element and return it.

Exceptions:

The length of $list must be greater than 0. Otherwise an exception is thrown.

=head2 to_array

C<method to_array : element[] ();>

Creates a new array and copies all elements of the list into the new array, and returns it.

=head2 unshift

C<method unshift : void ($element : object);>

Inserts an $element at the beginning of the list.

=head2 clone

C<method clone : L<List|SPVM::List> ();>

Clones this instance and returns it.

Each element is cloned by L<Cloneable#clone|SPVM::Cloneable/"clone"> method if it is defined, otherwise undef is assigned.

=head2 push_

C<method push_ : void ($elements : object[]);>

Adds the elements $elements after the end of this list.

This method calls L</"push"> method internally.

Exceptions:

The elements $elements must be defined.

Exceptions thrown by L</"push"> method could be thrown.

=head2 unshift_

C<method unshift_ : void ($elements : object[]);>

Inserts the elemnets $elements at the beginning of the list.

Exceptions:

The elements $elements must be defined.

Exceptions thrown by L</"unshift"> method could be thrown.

=head2 get_array_unsafe

C<method get_array_unsafe : element[] ();>

Same as L</"get_array">, but this method is deprecated.

=head2 get_array

C<method get_array : element[] ();>

Returns the internal L</"array">.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

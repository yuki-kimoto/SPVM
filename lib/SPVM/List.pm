package SPVM::List;

1;

=head1 Name

SPVM::List - Dynamic object array

=head1 Synopsys
  
  use List;
  
  # Create a object list
  my $list = List->new;
  my $list = List->new([(object)Byte->new(1), Int->new(2), Long->new(3)]);

  # Create a Int list
  my $list = List->new([Byte->new(1), Int->new(2), Int->new(3)]);
  
  # Create a object list with length
  my $list = List->new_len([], 3);

  # Create a Int list with length
  my $list = List->new_len(new Int[0], 3);

  # Get list length
  my $length = $list->length;
  
  # Push object value
  $list->push(Int->new(3));

  # Pop object value.
  my $object_value = $list->pop;

  # Unshift object value.
  $list->unshift(Int->new(3));
  
  # Shift object value.
  my $object_value = $list->shift;
  
  # Set object value.
  $list->set(2, Int->new(3));
  
  # Get object value.
  my $object_value = $list->get(2);

  # Insert object value
  $list->insert(1, Int->new(3));

  # Remove object value
  my $object_value = $list->remove(1);

  # Convert List to object array.
  my $int_array = $list->to_array;

  # Convert List to Int array.
  my $int_array = (Int[])$list->to_array;

=head1 Description

L<List|SPVM::List> is dynamic object array.

=head1 Class Methods

=head2 new

    static method new : List ($objects : object[]...)

Create a new L<List|SPVM::List> object with specific C<object> array.

Internally, new array is created, and each element of argument array is copied to internal array.

If the array of the argument is C<undef>, 0-length internal array is created.

  my $list = List->new;
  my $list = List->new([(object)Byte->new(1), Int->new(2), Long->new(3)]);

=head2 new_len

    static method new_len : List ($proto_array : object[], $length : int)

Create a new L<List|SPVM::List> object with prototype array and array length. Prototype array is used to decide the array type of internal values.

=head1 Instance Methods

=head2 get

  method get : object ($index : int)

Get the value with index.

=head2 insert

  method insert : void ($index : int, $value : object)

Insert a element to the specific index.

=head2 length
  
  static method length : int ()

Get list length.

=head2 pop

  method pop : object ()

Pops and returns the last value of the list, shortening the array by one element
If there are no elements in the list, exception occur.
            
=head2 push
  
  method push : void ($value : object)

Appending the value to the end of list.

=head2 remove

  method remove : object ($index : int)

Remove and return the element which is specified by the index.
  
=head2 resize

  method resize : void ($new_length : int)

Resize this list. If the new length is shorter than the current length, the list is truncated to the new length. If the new length is shorter than the current length, the list is truncated to the new length. If the new length is same as the current length, there is nothing to do. If the new length is longer than the current length, the list grows to the new length, and the values of the added elements are set to undef.

New length must be more than or equals to 0, otherwise a exception occur.

=head2 set

  method set : void ($index : int, $value : object)

Set the value with index.

=head2 set_array

  method set_array : void ($array : object[])

Set a array. Each elements of the array is copied to the correspoinding index of the array this list has. Note that this copy is address copy.

Array must be defined, otherwise a exception occurs.

The length of argument array must be same as the length of current list array, otherwise a exception occures.

=head2 to_array

  method to_array : object[] ()

Convert L<List|SPVM::List> to object array.

=head2 shift

  method shift : object ()

Shifts the first value of the list off and returns it, shortening
the array by 1 and moving everything down.
If there are no elements in the list, exception occur.

=head2 unshift

  method unshift : void ($value : object)

Appending the value to the top of list.


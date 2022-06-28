package SPVM::IntList;

1;

=head1 Name

SPVM::IntList - Dynamic int array

=head1 Synopsys
  
  use IntList;
  
  # Create a int list
  my $int_list = IntList->new;
  my $int_list = IntList->new([1, 2, 3]);
  
  # Create a int list with array length
  my $int_list = IntList->new_len(10);

  # Get list length
  my $length = $int_list->length;
  
  # Push int value
  $int_list->push(3);

  # Pop int value.
  my $int_value = $int_list->pop;

  # Unshift int value.
  $int_list->unshift(3);
  
  # Shift int value.
  my $int_value = $int_list->shift;
  
  # Set int value.
  $int_list->set(2, 3);

  # Get int value.
  my $int_value = $int_list->get(2);

  # Insert int value
  $int_list->insert(1, 3);

  # Remove int value
  my $int_value = $int_list->remove(1);

  # Convert IntList to int array.
  my $int_array = $int_list->to_array;

=head1 Description

L<IntList|SPVM::IntList> is dynamic int array.

=head1 Class Methods

=head2 new

    static method new : IntList ($array : int[]...)

Create a new L<IntList|SPVM::IntList> object with specific C<int> array.

Internally, new array is created, and each element of argument array is copied to internal array.

If the array of the argument is C<undef>, 0-length internal array is created.

  my $int_list = IntList->new;
  my $int_list = IntList->new([1, 2, 3]);

=head2 new_len

    static method new_len : IntList ($length : int)

Create a new L<IntList|SPVM::IntList> object with array length.

=head1 Instance Methods

=head2 get

  method get : int ($index : int)

Get the value with index.

=head2 insert

  method insert : void ($index : int, $value : int)

Insert a element to the specific index.

=head2 length
  
  static method length : int ()

Get list length.

=head2 pop

  method pop : int ()

Pops and returns the last value of the list, shortening the array by one element
If there are no elements in the list, exception occur.

=head2 push
  
  method push : void ($value : int)

Appending the value to the end of list.

=head2 remove

  method remove : int ($index : int)

Remove and return the element which is specified by the index.

=head2 resize

  method resize : void ($new_length : int)

Resize this list. If the new length is shorter than the current length, the list is truncated to the new length. If the new length is shorter than the current length, the list is truncated to the new length. If the new length is same as the current length, there is nothing to do. If the new length is longer than the current length, the list grows to the new length, and the values of the added elements are set to 0.

New length must be more than or equals to 0, otherwise a exception occur.

=head2 set

  method set : void ($index : int, $value : int)

Set the value with index.

=head2 set_array

  method set_array : void ($array : int[])

Set a array. Each elements of the array is copied to the correspoinding index of the array this list has.

Array must be defined, otherwise a exception occurs.

The length of argument array must be same as the length of current list array, otherwise a exception occures.

=head2 shift

  method shift : int ()

Shifts the first value of the list off and returns it, shortening
the array by 1 and moving everything down.
If there are no elements in the list, exception occur.

=head2 to_array

  method to_array : int[] ()

Convert L<IntList|SPVM::IntList> to int array.

=head2 unshift

  method unshift : void ($value : int)

Appending the value to the top of list.


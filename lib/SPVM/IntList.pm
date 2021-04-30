package SPVM::IntList;

1;

=head1 NAME

SPVM::IntList - Dynamic int array

=head1 SYNOPSYS
  
  use SPVM::IntList;
  
  # Create a int list with array length
  my $int_list = SPVM::IntList->new_len(10);

  # Create a int list with array
  my $int_list = SPVM::IntList->new([1, 2, 3]);
  
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

  # Convert SPVM::IntList to int array.
  my $int_array = $int_list->to_array;

=head1 DESCRIPTION

L<SPVM::IntList> is dynamic int array.

=head1 STATIC METHODS

=head2 new

    sub new : SPVM::IntList ($array : int[])

Create a new L<SPVM::IntList> object with specific C<int> array.

Internally, new array is created, and each element of argument array is copied to internal array.

If array is undef, 0-length internal array is created.

=head2 new_len

    sub new_len : SPVM::IntList ($length : int)

Create a new L<SPVM::IntList> object with array length.

=head1 INSTANCE METHODS

=head2 get

  sub get : int ($self : self, $index : int)

Get the value with index.

=head2 insert

  sub insert : void ($self : self, $index : int, $value : int)

Insert a element to the specific index.

=head2 length
  
  sub length : int ()

Get list length.

=head2 pop

  sub pop : int ($self : self)

Pops and returns the last value of the list, shortening the array by one element
If there are no elements in the list, exception occur.

=head2 push
  
  sub push : void ($self : self, $value : int)

Appending the value to the end of list.

=head2 remove

  sub remove : int ($self : self, $index : int)

Remove and return the element which is specified by the index.

=head2 resize

  sub resize : void ($self : self, $new_length : int)

Resize this list. If the new length is shorter than the current length, the list is truncated to the new length. If the new length is shorter than the current length, the list is truncated to the new length. If the new length is same as the current length, there is nothing to do. If the new length is longer than the current length, the list grows to the new length, and the values of the added elements are set to 0.

New length must be more than or equals to 0, otherwise a exception occur.

=head2 set

  sub set : void ($self : self, $index : int, $value : int)

Set the value with index.

=head2 set_array

  sub set_array : void ($self : self, $array : int[])

Set a array. Each elements of the array is copied to the correspoinding index of the array this list has.

Array must be defined, otherwise a exception occurs.

The length of argument array must be same as the length of current list array, otherwise a exception occures.

=head2 shift

  sub shift : int ($self : self)

Shifts the first value of the list off and returns it, shortening
the array by 1 and moving everything down.
If there are no elements in the list, exception occur.

=head2 to_array

  sub to_array : int[] ($self : self)

Convert L<SPVM::IntList> to int array.

=head2 unshift

  sub unshift : void ($self : self, $value : int)

Appending the value to the top of list.


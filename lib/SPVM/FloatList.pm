package SPVM::FloatList;

1;

=head1 NAME

SPVM::FloatList - Dynamic float array

=head1 SYNOPSYS
  
  use FloatList;
  
  # Create a float list
  my $float_list = FloatList->new_len(10);

  # Create a float list with array
  my $float_list = FloatList->new([1.5f, 2.5f, 3.5f]);
  
  # Get list length
  my $length = $float_list->length;
  
  # Push float value
  $float_list->push(3.5f);

  # Pop float value.
  my $float_value = $float_list->pop;

  # Unshift float value.
  $float_list->unshift(3.2f);
  
  # Shift float value.
  my $float_value = $float_list->shift;
  
  # Set float value.
  $float_list->set(2, 3.2f);

  # Get float value.
  my $float_value = $float_list->get(2);

  # Insert float value
  $float_list->insert(1, 3);

  # Remove float value
  my $float_value = $float_list->remove(1);

  # Convert FloatList to float array.
  my $float_array = $float_list->to_array;

=head1 DESCRIPTION

L<FloatList|SPVM::FloatList> is dynamic float array.

=head1 STATIC METHODS

=head2 new

    sub new : FloatList ($array : float[])

Create a new L<FloatList|SPVM::FloatList> object with specific C<float> array.

Internally, new array is created, and each element of argument array is copied to internal array.

If array is undef, 0-length internal array is created.

=head2 new_len

    sub new_len : FloatList ($length : int)

Create a new L<FloatList|SPVM::FloatList> object with array length.

=head1 INSTANCE METHODS

=head2 get

  sub get : float ($self : self, $index : int)

Get the value with index.

=head2 insert

  sub insert : void ($self : self, $index : int, $value : float)

Insert a element to the specific index.

=head2 length
  
  sub length : int ()

Get list length.

=head2 pop

  sub pop : float ($self : self)

Pops and returns the last value of the list, shortening the array by one element
If there are no elements in the list, exception occur.

=head2 push
  
  sub push : void ($self : self, $value : float)

Appending the value to the end of list.

=head2 remove

  sub remove : float ($self : self, $index : int)

Remove and return the element which is specified by the index.
  
=head2 resize

  sub resize : void ($self : self, $new_length : int)

Resize this list. If the new length is shorter than the current length, the list is truncated to the new length. If the new length is shorter than the current length, the list is truncated to the new length. If the new length is same as the current length, there is nothing to do. If the new length is longer than the current length, the list grows to the new length, and the values of the added elements are set to 0.

New length must be more than or equals to 0, otherwise a exception occur.

=head2 set

  sub set : void ($self : self, $index : int, $value : float)

Set the value with index.

=head2 set_array

  sub set_array : void ($self : self, $array : float[])

Set a array. Each elements of the array is copied to the correspoinding index of the array this list has.

Array must be defined, otherwise a exception occurs.

The length of argument array must be same as the length of current list array, otherwise a exception occures.

=head2 shift

  sub shift : float ($self : self)

Shifts the first value of the list off and returns it, shortening
the array by 1 and moving everything down.
If there are no elements in the list, exception occur.

=head2 to_array

  sub to_array : float[] ($self : self)

Convert L<FloatList|SPVM::FloatList> to float array.

=head2 unshift

  sub unshift : void ($self : self, $value : float)

Appending the value to the top of list.


package SPVM::FloatList;

1;

=head1 NAME

SPVM::FloatList - Dynamic float array

=head1 SYNOPSYS
  
  use FloatList;

  # Create a float list with array
  my $float_list = FloatList->new;
  my $float_list = FloatList->new([1.5f, 2.5f, 3.5f]);
  
  # Create a float list
  my $float_list = FloatList->new_len(10);

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

=head1 CLASS METHODS

=head2 new

    static method new : FloatList ($array : float[]...)

Create a new L<FloatList|SPVM::FloatList> object with specific C<float> array.

Internally, new array is created, and each element of argument array is copied to internal array.

If the array of the argument is C<undef>, 0-length internal array is created.

  my $float_list = FloatList->new;
  my $float_list = FloatList->new([1.5f, 2.5f, 3.5f]);

=head2 new_len

    static method new_len : FloatList ($length : int)

Create a new L<FloatList|SPVM::FloatList> object with array length.

=head1 INSTANCE METHODS

=head2 get

  method get : float ($index : int)

Get the value with index.

=head2 insert

  method insert : void ($index : int, $value : float)

Insert a element to the specific index.

=head2 length
  
  static method length : int ()

Get list length.

=head2 pop

  method pop : float ()

Pops and returns the last value of the list, shortening the array by one element
If there are no elements in the list, exception occur.

=head2 push
  
  method push : void ($value : float)

Appending the value to the end of list.

=head2 remove

  method remove : float ($index : int)

Remove and return the element which is specified by the index.
  
=head2 resize

  method resize : void ($new_length : int)

Resize this list. If the new length is shorter than the current length, the list is truncated to the new length. If the new length is shorter than the current length, the list is truncated to the new length. If the new length is same as the current length, there is nothing to do. If the new length is longer than the current length, the list grows to the new length, and the values of the added elements are set to 0.

New length must be more than or equals to 0, otherwise a exception occur.

=head2 set

  method set : void ($index : int, $value : float)

Set the value with index.

=head2 set_array

  method set_array : void ($array : float[])

Set a array. Each elements of the array is copied to the correspoinding index of the array this list has.

Array must be defined, otherwise a exception occurs.

The length of argument array must be same as the length of current list array, otherwise a exception occures.

=head2 shift

  method shift : float ()

Shifts the first value of the list off and returns it, shortening
the array by 1 and moving everything down.
If there are no elements in the list, exception occur.

=head2 to_array

  method to_array : float[] ()

Convert L<FloatList|SPVM::FloatList> to float array.

=head2 unshift

  method unshift : void ($value : float)

Appending the value to the top of list.


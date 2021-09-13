package SPVM::DoubleList;

1;

=head1 NAME

SPVM::DoubleList - DoubleList in SPVM | Dynamic double array

=head1 SYNOPSYS
  
  use DoubleList;
  
  # Create a double list
  my $double_list = DoubleList->new_len;

  # Create a double list with array
  my $double_list = DoubleList->new([1.5, 2.5, 3.5]);
  
  # Get list length
  my $length = $double_list->length;
  
  # Push double value
  $double_list->push(3.5);

  # Pop double value.
  my $double_value = $double_list->pop;

  # Unshift double value.
  $double_list->unshift(3.5);
  
  # Shift double value.
  my $double_value = $double_list->shift;
  
  # Set double value.
  $double_list->set(2, 3.5);

  # Get double value.
  my $double_value = $double_list->get(2);

  # Insert double value
  $double_list->insert(1, 3);

  # Remove double value
  my $double_value = $double_list->remove(1);

  # Convert DoubleList to double array.
  my $double_array = $double_list->to_array;

=head1 DESCRIPTION

L<DoubleList|SPVM::DoubleList> is dynamic double array.

=head1 CLASS METHODS

=head2 new

    static method new : DoubleList ($array : double[])

Create a new L<DoubleList|SPVM::DoubleList> object with specific C<double> array.

Internally, new array is created, and each element of argument array is copied to internal array.

If array is undef, 0-length internal array is created.

=head2 new_len

    static method new_len : DoubleList ($length : int)

Create a new L<DoubleList|SPVM::DoubleList> object with array length.

=head1 INSTANCE METHODS

=head2 unshift

  method unshift : void ($value : double)

Appending the value to the top of list.

=head2 get

  method get : double ($index : int)

Get the value with index.

=head2 insert

  method insert : void ($index : int, $value : double)

Insert a element to the specific index.

=head2 length
  
  static method length : int ()

Get list length.

=head2 remove

  method remove : double ($index : int)

Remove and return the element which is specified by the index.
  
=head2 resize

  method resize : void ($new_length : int)

Resize this list. If the new length is shorter than the current length, the list is truncated to the new length. If the new length is shorter than the current length, the list is truncated to the new length. If the new length is same as the current length, there is nothing to do. If the new length is longer than the current length, the list grows to the new length, and the values of the added elements are set to 0.

New length must be more than or equals to 0, otherwise a exception occur.

=head2 set

  method set : void ($index : int, $value : double)

Set the value with index.

=head2 set_array

  method set_array : void ($array : double[])

Set a array. Each elements of the array is copied to the correspoinding index of the array this list has.

Array must be defined, otherwise a exception occurs.

The length of argument array must be same as the length of current list array, otherwise a exception occures.

=head2 shift

  method shift : double ()

Shifts the first value of the list off and returns it, shortening
the array by 1 and moving everything down.
If there are no elements in the list, exception occur.

=head2 to_array

  method to_array : double[] ()

Convert L<DoubleList|SPVM::DoubleList> to double array.

=head2 pop

  method pop : double ()

Pops and returns the last value of the list, shortening the array by one element
If there are no elements in the list, exception occur.

=head2 push
  
  method push : void ($value : double)

Appending the value to the end of list.


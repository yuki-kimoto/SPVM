package SPVM::DoubleList;

1;

=head1 NAME

SPVM::DoubleList - Continuous dynamic double array

=head1 SYNOPSYS
  
  use SPVM::DoubleList;
  
  # Create a double list
  my $double_list = SPVM::DoubleList->new_len;

  # Create a double list with array
  my $double_list = SPVM::DoubleList->new([1.5, 2.5, 3.5]);
  
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

  # Convert SPVM::DoubleList to double array.
  my $double_array = $double_list->to_array;

=head1 DESCRIPTION

L<SPVM::DoubleList> is continuous dynamic double array.

=head1 STATIC METHODS

=head2 new

    sub new : SPVM::DoubleList ($array : double[])

Create a new L<SPVM::DoubleList> object with specific C<double> array.

=head2 new_len

    sub new_len : SPVM::DoubleList ($length : int)

Create a new L<SPVM::DoubleList> object with array length.

=head1 INSTANCE METHODS

=head2 unshift

  sub unshift : void ($self : self, $value : double)

Appending the value to the top of list.

=head2 get

  sub get : double ($self : self, $index : int)

Get the value with index.

=head2 insert

  sub insert : void ($self : self, $index : int, $value : double)

Insert a element to the specific index.

=head2 length
  
  sub length : int ()

Get list length.

=head2 remove

  sub remove : double ($self : self, $index : int)

Remove and return the element which is specified by the index.
  
=head2 resize

  sub resize : void ($self : self, $new_length : int)

Resize list.

New length must be more than or equals to 0, otherwise a exception occur.

=head2 set

  sub set : void ($self : self, $index : int, $value : double)

Set the value with index.

=head2 set_array

  sub set_array : void ($self : self, $array : double[])

Set a array. Each elements of the array is copied to the correspoinding index of the array this list has.

Array must be defined, otherwise a exception occurs.

The length of argument array must be same as the length of current list array, otherwise a exception occures.

=head2 shift

  sub shift : double ($self : self)

Shifts the first value of the list off and returns it, shortening
the array by 1 and moving everything down.
If there are no elements in the list, exception occur.

=head2 to_array

  sub to_array : double[] ($self : self)

Convert L<SPVM::DoubleList> to double array.

=head2 pop

  sub pop : double ($self : self)

Pops and returns the last value of the list, shortening the array by one element
If there are no elements in the list, exception occur.

=head2 push
  
  sub push : void ($self : self, $value : double)

Appending the value to the end of list.


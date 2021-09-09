package SPVM::ByteList;

1;

=head1 NAME

SPVM::ByteList - ByteList in SPVM | Dynamic Byte Array

=head1 SYNOPSYS
  
  use ByteList;
  
  # Create a byte list with array
  my $byte_list = ByteList->new([(byte)1, 2, 3]);
  
  # Create a byte list with array length
  my $byte_list = ByteList->new_len(10);

  # Get list length
  my $length = $byte_list->length;
  
  # Push byte value
  $byte_list->push((byte)3);

  # Pop byte value.
  my $byte_value = $byte_list->pop;

  # Unshift byte value.
  $byte_list->unshift((byte)3);
  
  # Shift byte value.
  my $byte_value = $byte_list->shift;
  
  # Set byte value.
  $byte_list->set(2, (byte)3);
  
  # Get byte value.
  my $byte_value = $byte_list->get(2);

  # Insert byte value
  $byte_list->insert(1, 3);

  # Remove byte value
  my $byte_value = $byte_list->remove(1);

  # Convert ByteList to byte array.
  my $byte_array = $byte_list->to_array;

=head1 DESCRIPTION

L<ByteList|SPVM::ByteList> is Dynamic Byte Array.

=head1 CLASS METHODS

=head2 new

    sub new : ByteList ($array : byte[])

Create a new L<ByteList|SPVM::ByteList> object with byte array.

Internally, new array is created, and each element of argument array is copied to internal array.

If array is undef, 0-length internal array is created.

=head2 new_len

    sub new_len : ByteList ($length : int)

Create a new L<ByteList|SPVM::ByteList> object with array length.

=head1 INSTANCE METHODS

=head2 get

  sub get : byte ($self : self, $index : int)

Get the value with index.

=head2 insert

  sub insert : void ($self : self, $index : int, $value : byte)

Insert a element to the specific index.

=head2 length
  
  sub length : int ()

Get list length.
           
=head2 remove

  sub remove : byte ($self : self, $index : int)

Remove and return the element which is specified by the index.

=head2 set

  sub set : void ($self : self, $index : int, $value : byte)

Set the value with index.

=head2 set_array

  sub set_array : void ($self : self, $array : byte[])

Set a array. Each elements of the array is copied to the correspoinding index of the array this list has.

Array must be defined, otherwise a exception occurs.

The length of argument array must be same as the length of current list array, otherwise a exception occures.

=head2 pop

  sub pop : byte ($self : self)

Pops and returns the last value of the list, shortening the array by one element
If there are no elements in the list, exception occur.

=head2 push
  
  sub push : void ($self : self, $value : byte)

Appending the value to the end of list.

=head2 resize

  sub resize : void ($self : self, $new_length : int)

Resize this list. If the new length is shorter than the current length, the list is truncated to the new length. If the new length is shorter than the current length, the list is truncated to the new length. If the new length is same as the current length, there is nothing to do. If the new length is longer than the current length, the list grows to the new length, and the values of the added elements are set to 0.

New length must be more than or equals to 0, otherwise a exception occur.

=head2 shift

  sub shift : byte ($self : self)

Shifts the first value of the list off and returns it, shortening
the array by 1 and moving everything down.
If there are no elements in the list, exception occur.

=head2 to_array

  sub to_array : byte[] ($self : self)

Convert L<ByteList|SPVM::ByteList> to byte array.

=head2 unshift

  sub unshift : void ($self : self, $value : byte)

Appending the value to the top of list.


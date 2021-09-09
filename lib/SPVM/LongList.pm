package SPVM::LongList;

1;

=head1 NAME

SPVM::LongList - Dynamic long array

=head1 SYNOPSYS
  
  use LongList;
  
  # Create a long list
  my $long_list = LongList->new_len(10);

  # Create a long list with array
  my $long_list = LongList->new([(long)1, 2, 3]);
  
  # Get list length
  my $length = $long_list->length;
  
  # Push long value
  $long_list->push(3L);

  # Pop long value.
  my $long_value = $long_list->pop;

  # Unshift long value.
  $long_list->unshift(3L);
  
  # Shift long value.
  my $long_value = $long_list->shift;
  
  # Set long value.
  $long_list->set(2, 3L);

  # Get long value.
  my $long_value = $long_list->get(2);

  # Insert long value
  $long_list->insert(1, 3);

  # Remove long value
  my $long_value = $long_list->remove(1);

  # Convert LongList to long array.
  my $long_array = $long_list->to_array;

=head1 DESCRIPTION

L<LongList|SPVM::LongList> is dynamic long array.

=head1 STATIC METHODS

=head2 new

    sub new : LongList ($array : long[])

Create a new L<LongList|SPVM::LongList> object with specific C<long> array.

Internally, new array is created, and each element of argument array is copied to internal array.

If array is undef, 0-length internal array is created.

=head2 new_len

    sub new_len : LongList ($length : int)

Create a new L<LongList|SPVM::LongList> object with array length.

=head1 INSTANCE METHODS

=head2 get

  sub get : long ($self : self, $index : int)

Get the value with index.

=head2 insert

  sub insert : void ($self : self, $index : int, $value : long)

Insert a element to the specific index.

=head2 length
  
  sub length : int ()

Get list length.

=head2 pop

  sub pop : long ($self : self)

Pops and returns the last value of the list, shortening the array by one element
If there are no elements in the list, exception occur.

=head2 push
  
  sub push : void ($self : self, $value : long)

Appending the value to the end of list.

=head2 remove

  sub remove : long ($self : self, $index : int)

Remove and return the element which is specified by the index.
  
=head2 resize

  sub resize : void ($self : self, $new_length : int)

Resize this list. If the new length is shorter than the current length, the list is truncated to the new length. If the new length is shorter than the current length, the list is truncated to the new length. If the new length is same as the current length, there is nothing to do. If the new length is longer than the current length, the list grows to the new length, and the values of the added elements are set to 0.

New length must be more than or equals to 0, otherwise a exception occur.

=head2 set

  sub set : void ($self : self, $index : int, $value : long)

Set the value with index.

=head2 set_array

  sub set_array : void ($self : self, $array : long[])

Set a array. Each elements of the array is copied to the correspoinding index of the array this list has.

Array must be defined, otherwise a exception occurs.

The length of argument array must be same as the length of current list array, otherwise a exception occures.

=head2 shift

  sub shift : long ($self : self)

Shifts the first value of the list off and returns it, shortening
the array by 1 and moving everything down.
If there are no elements in the list, exception occur.

=head2 to_array

  sub to_array : long[] ($self : self)

Convert L<LongList|SPVM::LongList> to long array.

=head2 unshift

  sub unshift : void ($self : self, $value : long)

Appending the value to the top of list.


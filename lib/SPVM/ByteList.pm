package SPVM::ByteList;

1;

=head1 NAME

SPVM::ByteList - 0 index based continuous dynamic byte array

=head1 SYNOPSYS
  
  use SPVM::ByteList;
  
  # Create a byte list with array
  my $byte_list = SPVM::ByteList->new([(byte)1, 2, 3]);
  
  # Create a byte list with array length
  my $byte_list = SPVM::ByteList->new_len(10);

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

  # Convert SPVM::ByteList to byte array.
  my $byte_array = $byte_list->to_array;

=head1 DESCRIPTION

L<SPVM::ByteList> is continuous dynamic byte array.

=head1 STATIC METHODS

=head2 new

    sub new : SPVM::ByteList ($array : byte[])

Create a new L<SPVM::ByteList> object with specific C<byte> array.

=head2 new_len

    sub new_len : SPVM::ByteList ($length : int)

Create a new L<SPVM::ByteList> object with array length.

=head1 INSTANCE METHODS

=head2 length
  
  sub length : int ()

Get list length.

=head2 push
  
  sub push : void ($self : self, $value : byte)

Appending the value to the end of list.

=head2 pop

  sub pop : byte ($self : self)

Pops and returns the last value of the list, shortening the array by one element
If there are no elements in the list, exception occur.
            
=head2 unshift

  sub unshift : void ($self : self, $value : byte)

Appending the value to the top of list.

=head2 shift

  sub shift : byte ($self : self)

Shifts the first value of the list off and returns it, shortening
the array by 1 and moving everything down.
If there are no elements in the list, exception occur.

=head2 set

  sub set : void ($self : self, $index : int, $value : byte)

Set the value with index.

=head2 get

  sub get : byte ($self : self, $index : int)

Get the value with index.

=head2 insert

  sub insert : void ($self : self, $index : int, $value : byte)

Insert a element to the specific index.

=head2 remove

  sub remove : byte ($self : self, $index : int)

Remove and return the element which is specified by the index.
  
=head2 to_array

  sub to_array : byte[] ($self : self)

Convert L<SPVM::ByteList> to byte array.

=head2 resize

  sub resize : void ($self : self, $new_length : int)

Resize list.

New length must be more than or equals to 0, otherwise a exception occur.

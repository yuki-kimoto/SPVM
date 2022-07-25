package SPVM::LongList;

1;

=head1 Name

SPVM::LongList - Dynamic long Array

=head1 Usage
  
  use LongList;
  
  # Create a long list
  my $list = LongList->new;
  my $list = LongList->new([(long)1, 2, 3]);
  
  # Create a long list with array length
  my $list = LongList->new_len(10);
  
  # Get list length
  my $length = $list->length;
  
  # Push value
  $list->push((long)3);
  
  # Pop value.
  my $value = $list->pop;
  
  # Unshift value.
  $list->unshift((long)3);
  
  # Shift value.
  my $value = $list->shift;
  
  # Set value.
  $list->set(2, (long)3);
  
  # Get value.
  my $value = $list->get(2);
  
  # Insert value
  $list->insert(1, 3);
  
  # Remove value
  my $value = $list->remove(1);
  
  # Convert list to array.
  my $array = $list->to_array;
  
=head1 Description

C<LongList> is a dynamic C<long> array.

=head1 Fields

=head2 length

  has length : ro int;

The length.

=head2 values

  has values : ro long[];

The values. This is the internally used array, but it can be manipulated directly.

  my $values = $list->values;
  $valeus->[0] = 5;

=head1 Class Methods

=head2 new

  static method new : LongList ($array : long[]...)

Create a new C<LongList> object with a C<long> array.

Internally, a new array is created, and each element of the specified array is copied to the new array.

If the array is C<undef>, a new array that length is C<0> is created.

B<Examples:>

  my $list = LongList->new;
  my $list = LongList->new([(long)1, 2, 3]);
  my $list = LongList->new(undef);

=head2 new_len

  static method new_len : LongList ($length : int)

Create a new C<LongList> object with the length.

The length must be greater than or equal to C<0>. Otherwise an excpetion will be thrown.

=head1 Instance Methods

=head2 get

  method get : long ($index : int)

Get the element of the position of the index.

The index must be greater than or equal to 0. Otherwise an excpetion will be thrown.

The index must be less than the length of the list. Otherwise an excpetion will be thrown.

=head2 insert

  method insert : void ($index : int, $value : long)

Insert an element to the position of the index.

The index must be greater than or equal to C<0>. Otherwise an excpetion will be thrown.

The index must be less than or equal to the length of the list. Otherwise an excpetion will be thrown.

=head2 pop

  method pop : long ()

Remove the last element and return it.

The length of the list must be greater than C<0>. Otherwise an excpetion will be thrown.

=head2 push
  
  method push : void ($value : long)

Add an element after the end of the list.

=head2 remove

  method remove : long ($index : int)

Remove the element at the position of the index and return it.

The index must be greater than or equal to C<0>. Otherwise an excpetion will be thrown.

The index must be less than the length of the list. Otherwise an excpetion will be thrown.

=head2 replace

  method replace : void ($offset : int, $remove_length : int, $replace : long[])

Replace the elements of the range specified by the offset and the lenght with the replacement array.

The offset must be greater than or equal to C<0>. Otherwise an excpetion will be thrown.

The removing length must be greater than or equal to C<0>. Otherwise an excpetion will be thrown.

The offset + the removing lenght must be less than or equal to the length of the list. Otherwise an excpetion will be thrown.

=head2 resize

  method resize : void ($new_length : int)

Resize the list.

The new length must be greater than or equal to C<0>. Otherwise an excpetion will be thrown.

=head2 set

  method set : void ($index : int, $value : long)

Set the element at the position of the index.

The index must be greater than or equal to C<0>. Otherwise an excpetion will be thrown.

The index must be less than the length of the list. Otherwise an excpetion will be thrown.

=head2 set_array

  method set_array : void ($array : long[])

Set a array. Each element of the array is copied to the element of the list.

The array must be defined. Otherwise an excpetion will be thrown.

The length of the array must be the same as the length of the list. Otherwise an excpetion will be thrown.

=head2 shift

  method shift : long ()

Remove the first element and return it.

The length of the list must be greater than C<0>. Otherwise an excpetion will be thrown.

=head2 to_array

  method to_array : long[] ()

Convert the list to an array.

=head2 unshift

  method unshift : void ($value : long)

Insert an element at the beginning of the list.

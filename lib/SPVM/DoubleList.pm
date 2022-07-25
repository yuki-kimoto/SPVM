package SPVM::DoubleList;

1;

=head1 Name

SPVM::DoubleList - Dynamic double Array

=head1 Usage
  
  use DoubleList;
  
  # Create a double list
  my $list = DoubleList->new;
  my $list = DoubleList->new([(double)1, 2, 3]);
  
  # Create a double list with array length
  my $list = DoubleList->new_len(10);
  
  # Get list length
  my $length = $list->length;
  
  # Push value
  $list->push((double)3);
  
  # Pop value.
  my $value = $list->pop;
  
  # Unshift value.
  $list->unshift((double)3);
  
  # Shift value.
  my $value = $list->shift;
  
  # Set value.
  $list->set(2, (double)3);
  
  # Get value.
  my $value = $list->get(2);
  
  # Insert value
  $list->insert(1, 3);
  
  # Remove value
  my $value = $list->remove(1);
  
  # Convert list to array.
  my $array = $list->to_array;
  
=head1 Description

C<DoubleList> is a dynamic C<double> array.

=head1 Fields

=head2 length

  has length : ro int;

The length.

=head2 values

  has values : ro double[];

The values. This is the internally used array, but it can be manipulated directly.

  my $values = $list->values;
  $valeus->[0] = 5;

=head1 Class Methods

=head2 new

  static method new : DoubleList ($array : double[]...)

Create a new C<DoubleList> object with a C<double> array.

Internally, a new array is created, and each element of the specified array is copied to the new array.

If the array is C<undef>, a new array that length is C<0> is created.

B<Examples:>

  my $list = DoubleList->new;
  my $list = DoubleList->new([(double)1, 2, 3]);
  my $list = DoubleList->new(undef);

=head2 new_len

  static method new_len : DoubleList ($length : int)

Create a new C<DoubleList> object with the length.

The length must be greater than or equal to C<0>. Otherwise an excpetion will be thrown.

=head1 Instance Methods

=head2 get

  method get : double ($index : int)

Get the element of the position of the index.

The index must be greater than or equal to 0. Otherwise an excpetion will be thrown.

The index must be less than the length of the list. Otherwise an excpetion will be thrown.

=head2 insert

  method insert : void ($index : int, $value : double)

Insert an element to the position of the index.

The index must be greater than or equal to C<0>. Otherwise an excpetion will be thrown.

The index must be less than or equal to the length of the list. Otherwise an excpetion will be thrown.

=head2 pop

  method pop : double ()

Remove the last element and return it.

The length of the list must be greater than C<0>. Otherwise an excpetion will be thrown.

=head2 push
  
  method push : void ($value : double)

Add an element after the end of the list.

=head2 remove

  method remove : double ($index : int)

Remove the element at the position of the index and return it.

The index must be greater than or equal to C<0>. Otherwise an excpetion will be thrown.

The index must be less than the length of the list. Otherwise an excpetion will be thrown.

=head2 replace

  method replace : void ($offset : int, $remove_length : int, $replace : double[])

Replace the elements of the range specified by the offset and the lenght with the replacement array.

The offset must be greater than or equal to C<0>. Otherwise an excpetion will be thrown.

The removing length must be greater than or equal to C<0>. Otherwise an excpetion will be thrown.

The offset + the removing lenght must be less than or equal to the length of the list. Otherwise an excpetion will be thrown.

=head2 resize

  method resize : void ($new_length : int)

Resize the list.

The new length must be greater than or equal to C<0>. Otherwise an excpetion will be thrown.

=head2 set

  method set : void ($index : int, $value : double)

Set the element at the position of the index.

The index must be greater than or equal to C<0>. Otherwise an excpetion will be thrown.

The index must be less than the length of the list. Otherwise an excpetion will be thrown.

=head2 set_array

  method set_array : void ($array : double[])

Set a array. Each element of the array is copied to the element of the list.

The array must be defined. Otherwise an excpetion will be thrown.

The length of the array must be the same as the length of the list. Otherwise an excpetion will be thrown.

=head2 shift

  method shift : double ()

Remove the first element and return it.

The length of the list must be greater than C<0>. Otherwise an excpetion will be thrown.

=head2 to_array

  method to_array : double[] ()

Convert the list to an array.

=head2 unshift

  method unshift : void ($value : double)

Insert an element at the beginning of the list.

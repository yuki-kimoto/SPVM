package SPVM::List;

1;

=head1 Name

SPVM::List - Dynamic Object Array

=head1 Usage
  
  use List;
  
  # Create a object list
  my $list = List->new;
  my $list = List->new([(object)Byte->new(1), Int->new(2), Long->new(3)]);

  # Create a Int list
  my $list = List->new([Int->new(1), Int->new(2), Int->new(3)]);
  
  # Create a object list with length
  my $list = List->new_len([], 3);

  # Create a Int list with length
  my $list = List->new_len(new Int[0], 3);

  # Get list length
  my $length = $list->length;
  
  # Push object value
  $list->push(Int->new(3));

  # Pop object value.
  my $value = $list->pop;

  # Unshift object value.
  $list->unshift(Int->new(3));
  
  # Shift object value.
  my $value = $list->shift;
  
  # Set object value.
  $list->set(2, Int->new(3));
  
  # Get object value.
  my $value = $list->get(2);

  # Insert object value
  $list->insert(1, Int->new(3));

  # Remove object value
  my $value = $list->remove(1);

  # Convert List to object array.
  my $int_array = $list->to_array;

  # Convert List to Int array.
  my $int_array = (Int[])$list->to_array;

=head1 Description

C<List> is the dynamic object array that has a specified object array type.

=head1 Fields

=head2 length

  has length : ro int;

The length.

=head2 values

  has values : ro object[];

The values. This is the internally used array, but it can be manipulated directly.

=head1 Class Methods

=head2 new

  static method new : List ($objects : object[]...)

Create a new C<List> object with the object array.

Internally, a new array is created. The type of the created array is the same type as the array specified by the argument. Each element of the array specified by the arugment is copied to the element of the new array.

If the array of the argument is C<undef>, 0-length internal array is created.
  
  # object[]
  my $list = List->new([(object)Byte->new(1), Int->new(2), Long->new(3)]);
  
  # Int[]
  my $list = List->new([Int->new(1), Int->new(2), Int->new(3)]);

=head2 new_len

  static method new_len : List ($proto_array : object[], $length : int)

Create a new C<List> object with the prototype array and the length of the created array.

Internally, a new array is created. The type of the created array is the same type as the prototype array specified by the argument.

The length must be greater than or equal to C<0>. Otherwise an excpetion will be thrown.

B<Examples:>

  # Create a Int list with length
  my $list = List->new_len(new Int[0], 3);

=head1 Instance Methods

=head2 get

  method get : object ($index : int)

Get the element of the position of the index.

The index must be greater than or equal to C<0>. Otherwise an excpetion will be thrown.

The index must be less than the length of the list. Otherwise an excpetion will be thrown.

=head2 insert

  method insert : void ($index : int, $value : object)

Insert an element to the position of the index.

The index must be greater than or equal to C<0>. Otherwise an excpetion will be thrown.

The index must be less than or equal to the length of the list. Otherwise an excpetion will be thrown.

=head2 pop

  method pop : object ()

Remove the last element and return it.

The length of the list must be greater than C<0>. Otherwise an excpetion will be thrown.
            
=head2 push
  
  method push : void ($value : object)

Add an element after the end of the list.

=head2 remove

  method remove : object ($index : int)

Remove the element at the position of the index and return it.

The index must be greater than or equal to C<0>. Otherwise an excpetion will be thrown.

The index must be less than the length of the list. Otherwise an excpetion will be thrown.

=head2 resize

  method resize : void ($new_length : int)

Resize the list.

The new length must be greater than or equal to C<0>. Otherwise an excpetion will be thrown.

=head2 replace

  method replace : void ($offset : int, $remove_length : int, $replace : object[])

Replace the elements of the range specified by the offset and the lenght with the replacement array.

The offset must be greater than or equal to C<0>. Otherwise an excpetion will be thrown.

The removing length must be greater than or equal to C<0>. Otherwise an excpetion will be thrown.

The offset + the removing lenght must be less than or equal to the length of the list. Otherwise an excpetion will be thrown.

=head2 set

  method set : void ($index : int, $value : object)

Set the element at the position of the index.

The index must be greater than or equal to C<0>. Otherwise an excpetion will be thrown.

The index must be less than the length of the list. Otherwise an excpetion will be thrown.

=head2 set_array

  method set_array : void ($array : object[])

Set a array. Each element of the array is copied to the element of the list.

The array must be defined. Otherwise an excpetion will be thrown.

The length of the array must be the same as the length of the list. Otherwise an excpetion will be thrown.

=head2 shift

  method shift : object ()

Remove the first element and return it.

The length of the list must be greater than C<0>. Otherwise an excpetion will be thrown.

=head2 to_array

  method to_array : object[] ()

Convert the list to an array.

=head2 unshift

  method unshift : void ($value : object)

Insert an element at the beginning of the list.

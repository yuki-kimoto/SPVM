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
  my $element = $list->pop;

  # Unshift object value.
  $list->unshift(Int->new(3));
  
  # Shift object value.
  my $element = $list->shift;
  
  # Set object value.
  $list->set(2, Int->new(3));
  
  # Get object value.
  my $element = $list->get(2);

  # Insert object value
  $list->insert(1, Int->new(3));

  # Remove object value
  my $element = $list->remove(1);

  # Convert List to object array.
  my $int_array = $list->to_array;

  # Convert List to Int array.
  my $int_array = (Int[])$list->to_array;

=head1 Description

C<List> is the dynamic object array that has a specified object array type.

=head1 Enumerations

  enum {
    DEFAULT_CAPACITY = 4,
  }

=head2 DEFAULT_CAPACITY

The default capacity. The value is C<4>.

=head1 Fields

=head2 capacity

  has capacity : ro int;

The capacity. This is the length of the internally reserved elements to extend the length of the list.

=head2 length

  has length : ro int;

The length of the list.

=head2 values

  has values : ro object[];

The values. This is the elements in the internally used array, but it can be manipulated directly.

=head1 Class Methods

=head2 new

  static method new : List ($array = undef : object[], $capacity = -1 : int);

Creates a new C<List> object using L</"new_len">.

The passed length to L</"new_len"> is the length of the C<$array>. If the array is C<undef>, the length is C<0>.

The element's addresses of the object array are copied to the values of the the created array.
  
  # object[]
  my $list = List->new([(object)Byte->new(1), Int->new(2), Long->new(3)]);
  
  # Int[]
  my $list = List->new([Int->new(1), Int->new(2), Int->new(3)]);

=head2 new_len

  static method new_len : List ($proto_array : object[], $length : int, $capacity = -1 : int);

Creates a new C<StringList> object with the C<$protot_array>, the C<$length> and the C<$capacity>.

If the C<$protot_array> is undefined, the C<$protot_array> is set to an C<object[]> object.

If the C<$capacity> is less than C<0>, the C<$capacity> is set to the value of L</"DEFAULT_CAPACITY">.

If the C<$length> is greater than the C<$capacity>, the C<$capacity> is set to the length.

Exceptions:

The C<$length> must be greater than or equal to C<0>.

B<Examples:>

  # Create a Int list with length
  my $list = List->new_len(new Int[0], 3);

=head1 Instance Methods

=head2 get

  method get : object ($index : int);

Gets the element of the position of the C<$index>.

Exceptions:

The C<$index> must be greater than or equal to C<0>.

The C<$index> must be less than the length of the C<$list>.

=head2 insert

  method insert : void ($index : int, $element : object);

Inserts an C<$element> to the position of the C<$index>.

Exceptions:

The C<$index> must be greater than or equal to C<0>.

The C<$index> must be less than or equal to the length of the C<$list>.

=head2 pop

  method pop : object ();

Removes the last element and return it.

Exceptions:

The length of the C<$list> must be greater than C<0>.
            
=head2 push
  
  method push : void ($element : object);

Adds an C<$element> after the end of the list.

=head2 remove

  method remove : object ($index : int);

Removes the element at the position of the C<$index> and return it.

Exceptions:

The C<$index> must be greater than or equal to C<0>.

The C<$index> must be less than the length of the C<$list>.

=head2 replace

  method replace : void ($offset : int, $remove_length : int, $replace : string[]);

Replaces the elements of the range specified by the C<$offset> and the C<$lenght> with the C<$replace> array.

Exceptions:

The C<$offset> must be greater than or equal to C<0>.

The C<$remove_length> must be greater than or equal to C<0>.

The C<$offset> + the C<$removing> lenght must be less than or equal to the length of the C<$list>.

=head2 reserve

  method reserve : void ($new_capacity : int);

Reserves the elements with the C<$new_capacity>.

If the C<$new_capacity> is greater than the capacity of the list, the capacity of the list is extended to the C<$new_capacity>.

Note that L</"values"> is replaced with the new values and the values of the original list are copied to the new values in the above case.

Exceptions:

The C<$new_capacity> must be greater than or equal to C<0>.

=head2 resize

  method resize : void ($new_length : int);

Resize the list with the C<$new_length>.

Exceptions:

The C<$new_length> must be greater than or equal to C<0>.

=head2 replace

  method replace : void ($offset : int, $remove_length : int, $replace : object[]);

Replaces the elements of the range specified by the C<$offset> and the C<$remove_length> with the replacement array.

Exceptions:

The C<$offset> must be greater than or equal to C<0>.

The C<$remove_length> must be greater than or equal to C<0>.

The C<$offset> + the C<$removing> lenght must be less than or equal to the length of the C<$list>.

=head2 set

  method set : void ($index : int, $element : object);

Sets the C<$element> at the position of the C<$index>.

Exceptions:

The C<$index> must be greater than or equal to C<0>.

The C<$index> must be less than the length of the C<$list>.

=head2 set_array

  method set_array : void ($array : object[]);

Sets an C<$array>. Each element of the C<$array> is copied to the element of the list.

Exceptions:

The C<$array> must be defined.

The length of the C<$array> must be the C<$same> as the length of the C<$list>.

=head2 shift

  method shift : object ();

Removes the first element and return it.

Exceptions:

The length of the C<$list> must be greater than C<0>.

=head2 to_array

  method to_array : object[] ();

Converts the list to an array.

=head2 unshift

  method unshift : void ($element : object);

Inserts an C<$element> at the beginning of the list.

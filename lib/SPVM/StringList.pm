package SPVM::StringList;

1;

=head1 Name

SPVM::StringList - Dynamic string array

=head1 Usage
  
  use StringList;
  
  # Create a string list
  my $list = StringList->new;
  my $list = StringList->new(["abc", "def", "ghi"]);
  
  # Create a string list
  my $list = StringList->new_len(10);

  # Get list length
  my $length = $list->length;
  
  # Push string value
  $list->push("abc");

  # Pop string value.
  my $element = $list->pop;

  # Unshift string value.
  $list->unshift("abc");
  
  # Shift string value.
  my $element = $list->shift;
  
  # Set string value.
  $list->set(2, "abc");

  # Get string value.
  my $element = $list->get(2);

  # Insert string value
  $list->insert(1, "abc");

  # Remove string value
  my $element = $list->remove(1);

  # Convert StringList to string array.
  my $array = $list->to_array;

=head1 Description

C<StringList> is a dynamic C<string> array.

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

  has values : ro string[];

The values. This is the internally used array, but it can be manipulated directly.

  my $elements = $list->values;
  $valeus->[0] = "d";

=head1 Class Methods

=head2 new

  static method new : StringList ($array = undef : string[], $capacity = -1 : int);

Create a new C<StringList> object using L</"new_len">.

The passed length to L</"new_len"> is the length of the array. If the array is C<undef>, the length is C<0>.

The element's addresses of the string array are copied to the values of the the created array.

B<Examples:>

  my $list = StringList->new;
  my $list = StringList->new(["abc", "def", "ghi"]);

=head2 new_len

  static method new_len : StringList ($length : int, $capacity = -1 : int);

Creates a new C<StringList> object with the C<$length> and the C<$capacity>.

If the C<$capacity> is less than C<0>, the capacity is set to the value of L</"DEFAULT_CAPACITY">.

If the C<$length> is greater than the C<$capacity>, the C<$capacity> is set to the C<$length>.

Exceptions:

The C<$length> must be greater than or equal to C<0>.

=head1 Instance Methods

=head2 get

  method get : string ($index : int);

Gets the element of the position of the C<$index>.

Exceptions:

The C<$index> must be greater than or equal to 0.

The C<$index> must be less than the length of the C<$list>.

=head2 insert

  method insert : void ($index : int, $element : string);

Inserts an C<$element> to the position of the C<$index>.

Exceptions:

The C<$index> must be greater than or equal to C<0>.

The C<$index> must be less than or equal to the length of the C<$list>.

=head2 pop

  method pop : string ();

Removes the last element and return it.

Exceptions:

The length of the C<$list> must be greater than C<0>.

=head2 push
  
  method push : void ($element : string);

Adds an C<$element> after the end of the list.

=head2 remove

  method remove : string ($index : int);

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

Resizes the list with the C<$new_length>.

Exceptions:

The C<$new_length> must be greater than or equal to C<0>.

=head2 set

  method set : void ($index : int, $element : string);

Sets the C<$element> at the position of the C<$index>.

Exceptions:

The C<$index> must be greater than or equal to C<0>.

The C<$index> must be less than the length of the C<$list>.

=head2 set_array

  method set_array : void ($array : string[]);

Sets an C<$array>. Each element of the C<$array> is copied to the element of the list.

Exceptions:

The C<$array> must be defined.

The length of the C<$array> must be the C<$same> as the length of the C<$list>.

=head2 shift

  method shift : string ();

Removes the first element and return it.

Exceptions:

The length of the C<$list> must be greater than C<0>.

=head2 to_array

  method to_array : string[] ();

Converts the list to an array.

=head2 unshift

  method unshift : void ($element : string);

Inserts an C<$element> at the beginning of the list.

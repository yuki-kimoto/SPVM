package SPVM::StringList;

1;

=head1 NAME

SPVM::StringList - Dynamic string array

=head1 SYNOPSYS
  
  use StringList;
  
  # Create a string list
  my $string_list = StringList->new;
  my $string_list = StringList->new(["abc", "def", "ghi"]);
  
  # Create a string list
  my $string_list = StringList->new_len(10);

  # Get list length
  my $length = $string_list->length;
  
  # Push string value
  $string_list->push("abc");

  # Pop string value.
  my $string_value = $string_list->pop;

  # Unshift string value.
  $string_list->unshift("abc");
  
  # Shift string value.
  my $string_value = $string_list->shift;
  
  # Set string value.
  $string_list->set(2, "abc");

  # Get string value.
  my $string_value = $string_list->get(2);

  # Insert string value
  $string_list->insert(1, "abc");

  # Remove string value
  my $string_value = $string_list->remove(1);

  # Convert StringList to string array.
  my $string_array = $string_list->to_array;

=head1 DESCRIPTION

L<StringList|SPVM::StringList> is dynamic string array.

=head1 CLASS METHODS

=head2 new

  static method new : StringList ($array : string[]...)

Create a new L<StringList|SPVM::StringList> object with specific C<string> array.

Internally, new array is created, and each element of argument array is copied to internal array.

If the array of the argument is C<undef>, 0-length internal array is created.

  my $string_list = StringList->new;
  my $string_list = StringList->new(["abc", "def", "ghi"]);

=head2 new_len

  static method new_len : StringList ($length : int)

Create a new L<StringList|SPVM::StringList> object with array length.

=head1 INSTANCE METHODS

=head2 get

  method get : string ($index : int)

Get the value with index.

=head2 length
  
  static method length : int ()

Get list length.

=head2 insert

  method insert : void ($index : int, $value : string)

Insert a element to the specific index.

=head2 pop

  method pop : string ()

Pops and returns the last value of the list, shortening the array by one element
If there are no elements in the list, exception occur.

=head2 push
  
  method push : void ($value : string)

Appending the value to the end of list.

=head2 remove

  method remove : string ($index : int)

Remove and return the element which is specified by the index.

=head2 resize

  method resize : void ($new_length : int)

Resize this list. If the new length is shorter than the current length, the list is truncated to the new length. If the new length is shorter than the current length, the list is truncated to the new length. If the new length is same as the current length, there is nothing to do. If the new length is longer than the current length, the list grows to the new length, and the values of the added elements are set to undef.

New length must be more than or equals to 0, otherwise a exception occur.

=head2 set

  method set : void ($index : int, $value : string)

Set the value with index.

=head2 set_array

  method set_array : void ($array : string[])

Set a array. Each elements of the array is copied to the correspoinding index of the array this list has. Note that this copy is address copy.
Array must be defined, otherwise a exception occurs.

The length of argument array must be same as the length of current list array, otherwise a exception occures.

=head2 shift

  method shift : string ()

Shifts the first value of the list off and returns it, shortening
the array by 1 and moving everything down.
If there are no elements in the list, exception occur.

=head2 to_array

  method to_array : string[] ()

Convert L<StringList|SPVM::StringList> to string array.

=head2 unshift

  method unshift : void ($value : string)

Appending the value to the top of list.

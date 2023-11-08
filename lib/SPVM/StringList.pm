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

=head1 Inheritance

L<List|SPVM::List>.

=head1 Fields

=head2 capacity

  has capacity : ro int;

The capacity. This is the length of the internally reserved elements to extend the length of the list.

=head2 length

  has length : ro int;

The length of the list.

=head1 Class Methods

=head2 new

C<static method new : L<StringList|SPVM::StringList> ($array : string[] = undef, $capacity : int = -1);>

Create a new C<StringList> object using L</"new_len">.

The passed length to L</"new_len"> is the length of the array. If the array is undef, the length is 0.

The element's addresses of the string array are copied to the values of the the created array.

Examples:

  my $list = StringList->new;
  my $list = StringList->new(["abc", "def", "ghi"]);

=head2 new_len

C<static method new_len : L<StringList|SPVM::StringList> ($length : int, $capacity : int = -1);>

Creates a new C<StringList> object with $length and $capacity.

If $capacity is less than 0, the capacity is set to the default value.

If $length is greater than $capacity, $capacity is set to $length.

Exceptions:

$length must be greater than or equal to 0. Otherwise an exception is thrown.

=head1 Instance Methods

=head2 get

C<method get : string ($index : int);>

Gets the element of the position of $index.

Exceptions:

$index must be greater than or equal to 0. Otherwise an exception is thrown.

$index must be less than the length of $list. Otherwise an exception is thrown.

=head2 insert

C<method insert : void ($index : int, $element : string);>

Inserts an $element to the position of $index.

Exceptions:

$index must be greater than or equal to 0. Otherwise an exception is thrown.

$index must be less than or equal to the length of $list. Otherwise an exception is thrown.

=head2 pop

C<method pop : string ();>

Removes the last element and return it.

Exceptions:

The length of $list must be greater than 0. Otherwise an exception is thrown.

=head2 push
  
C<method push : void ($element : string);>

Adds an $element after the end of the list.

=head2 remove

C<method remove : string ($index : int);>

Removes the element at the position of $index and return it.

Exceptions:

$index must be greater than or equal to 0. Otherwise an exception is thrown.

$index must be less than the length of $list. Otherwise an exception is thrown.

=head2 replace

C<method replace : void ($index : int, $remove_length : int, $replace : string[]);>

Replaces the elements of the range specified by $index and $lenght with $replace array.

Exceptions:

$index must be greater than or equal to 0. Otherwise an exception is thrown.

$remove_length must be greater than or equal to 0. Otherwise an exception is thrown.

$index + $removing lenght must be less than or equal to the length of $list.

=head2 set

C<method set : void ($index : int, $element : string);>

Sets $element at the position of $index.

Exceptions:

$index must be greater than or equal to 0. Otherwise an exception is thrown.

$index must be less than the length of $list. Otherwise an exception is thrown.

=head2 shift

C<method shift : string ();>

Removes the first element and return it.

Exceptions:

The length of $list must be greater than 0. Otherwise an exception is thrown.

=head2 to_array

C<method to_array : string[] ();>

Converts the list to an array.

=head2 unshift

C<method unshift : void ($element : string);>

Inserts an $element at the beginning of the list.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

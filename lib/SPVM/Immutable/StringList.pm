package SPVM::Immutable::StringList;

1;

=head1 Name

SPVM::Immutable::StringList - Immutable string array

=head1 Usage
  
  use Immutable::StringList;
  
  # Create a string list
  my $list = Immutable::StringList->new;
  my $list = Immutable::StringList->new(["abc", "def", "ghi"]);
  
  # Create a string list
  my $list = Immutable::StringList->new_len(10);
  
  # Get list length
  my $length = $list->length;
  
  # Get string value.
  my $element = $list->get(2);
  
  # Convert Immutable::StringList to string array.
  my $array = $list->to_array;

=head1 Description

The Immutable::StringList class has methods to manipulate an immutable string array.

=head1 Fields

=head2 length

  has length : ro int;

Gets the C<length> field.

This field is the length of the elements of the list.

=head1 Class Methods

=head2 new

C<static method new : L<Immutable::StringList|SPVM::Immutable::StringList> ($array : string[] = undef);>

Create a new L<Immutable::StringList|SPVM::Immutable::StringList> object using L</"new_len">.

The passed length to L</"new_len"> is the length of the array. If the array is undef, the length is 0.

The each string of the array is copied and to each value of the the created array and each string is made read-only.

Examples:

  my $list = Immutable::StringList->new;
  my $list = Immutable::StringList->new(["abc", "def", "ghi"]);

=head2 new_len

C<static method new_len : L<Immutable::StringList|SPVM::Immutable::StringList> ($length : int);>

Creates a new L<Immutable::StringList|SPVM::Immutable::StringList> object with $length.

Exceptions:

$length must be greater than or equal to 0. Otherwise an exception is thrown.

=head1 Instance Methods

=head2 get

C<method get : string ($index : int);>

Gets the element of the position of $index.

If $index is a netative value, $index is set to L</"length"> plus $index.

Exceptions:

$index must be greater than or equal to 0. Otherwise an exception is thrown.

$index must be less than the length of $list. Otherwise an exception is thrown.

=head2 to_array

C<method to_array : string[] ();>

Converts the list to an array.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

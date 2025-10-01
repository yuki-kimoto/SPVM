package SPVM::Immutable::IntList;

1;

=head1 Name

SPVM::Immutable::IntList - Immutable int Array

=head1 Description

The Immutable::IntList class has methods to manipulate an immutable int array.

=head1 Usage
  
  use Immutable::IntList;
  
  # Create a int list
  my $list = Immutable::IntList->new;
  my $list = Immutable::IntList->new([(int)1, 2, 3]);
  
  # Create a int list with array length
  my $list = Immutable::IntList->new_len(10);
  
  # Get list length
  my $length = $list->length;
  
  # Get value.
  my $element = $list->get(2);
  
  # Convert list to array.
  my $array = $list->to_array;
  
=head1 Fields

=head2 length

  has length : ro int;

Gets the C<length> field.

This field is the length of the elements of the list.

=head1 Class Methods

=head2 new

C<static method new : L<Immutable::IntList|SPVM::Immutable::IntList> ($array : int[] = undef);>

Create a new L<Immutable::IntList|SPVM::Immutable::IntList> object using L</"new_len">.

The passed length to L</"new_len"> is the length of the array. If the array is undef, the length is 0.

The elements of the array are copied to the elements of the the created array.

Examples:

  my $list = Immutable::IntList->new;
  my $list = Immutable::IntList->new([(int)1, 2, 3]);

=head2 new_len

C<static method new_len : L<Immutable::IntList|SPVM::Immutable::IntList> ($length : int);>

Creates a new L<Immutable::IntList|SPVM::Immutable::IntList> object with $length.

Exceptions:

$length must be greater than or equal to 0.

=head1 Instance Methods

=head2 get

C<method get : int ($index : int);>

Gets the element of the position of $index.

If $index is a netative value, $index is set to L</"length"> plus $index.

Exceptions:

$index must be greater than or equal to 0.

$index must be less than the length of $list.

=head2 to_array

C<method to_array : int[] ();>

Converts the list to an array.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

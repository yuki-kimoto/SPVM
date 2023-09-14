package SPVM::StringBuffer;

1;

=head1 Name

SPVM::StringBuffer - String Buffer

=head1 Usage
  
  use StringBuffer;
  
  # new
  my $buffer = StringBuffer->new;
  
  # push string
  $buffer->push("abc");
  $buffer->push("def");
  
  # Convert to string - abcdef
  my $string = $buffer->to_string;
  
=head1 Description

String buffer.

=head1 Enumerations

  enum {
    DEFAULT_CAPACITY = 4,
  }

=head2 DEFAULT_CAPACITY

The default capacity. The value is 4.

=head1 Fields

=head2 capacity

  has capacity : ro int;

The capacity. This is the length of the internally reserved characters to extend the length of the string buffer.

=head2 length

  has length : ro int;

The length of the string buffer.

=head1 Class Methods

=head2 new

C<static method new : L<StringBuffer|SPVM::StringBuffer> ($string : string = undef, $capacity : int = -1);>

Creates a new C<StringBuffer> object using L</"new_len">.

The passed $length to L</"new_len"> is the length of $string. If the string is undef, it is 0.

$string is copied to the value of the the created string buffer.

=head2 new_len

C<static method new_len : L<StringBuffer|SPVM::StringBuffer> ($length : int, $capacity : int = -1);>

Creates a new C<StringBuffer> object with $length and $capacity.

If $capacity is less than 0, $capacity is set to the value of L</"DEFAULT_CAPACITY">.

If $length is greater than $capacity, $capacity is set to $length.

Exceptions:

$length must be greater than or equal to 0. Otherwise an exception is thrown.

=head1 Instance Methods

=head2 push

C<method push : void ($string : string, $offset : int = 0, $length : int = -1);>

Adds a $string from $offset to the position proceeded by $length after the end of the string in the string buffer.

Exceptions:

$string must be defined. Otherwise an exception is thrown.

$offset must be greater than or equal to 0. Otherwise an exception is thrown.

$offset + $length must be less than or equal to the length of $string. Otherwise an exception is thrown.

=head2 push_char

C<method push_char : void ($char : int);>

Adds Ascii $char after the end of the string in the string buffer.

=head2 replace

C<method replace : void ($offset : int, $length : int, $replace : string);>

Replace the characters of the range specified by $offset and $length in the buffer with $replace string.

Exceptions:

$offset must be greater than or equal to 0. Otherwise an exception is thrown.

$offset + $length must be less than or equal to the length of the string buffer. Otherwise an exception is thrown.

=head2 reserve

C<method reserve : void ($new_capacity : int);>

Reserves the characters that size is $new_capacity.

If $new_capacity is greater than the capacity of the string buffer, the capacity of the string buffer is extended to $new_capacity.

Exceptions:

$new_capacity must be greater than or equal to 0. Otherwise an exception is thrown.

=head2 to_string

C<method to_string : string ();>

Creates a new string with the length of the buffer and copies all characters in the buffer into the new string, and returns it.

=head2 get_string_unsafe

C<method get_string_unsafe : string ();>

Gets the internally string. 

This buffer is unsafe because it continues to point to the old string if the internal string is extended.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

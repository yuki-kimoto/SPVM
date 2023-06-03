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

=head2 value

  has value : ro mutable string;

The value. This is the internally used string, but it can be manipulated directly.

  my $value = $buffer->value;
  $valeu->[0] = 'a';

=head1 Class Methods

=head2 new

  static method new : StringBuffer ($string : string = undef, $capacity : int = -1);

Creates a new C<StringBuffer> object using L</"new_len">.

The passed $length to L</"new_len"> is the length of the $string. If the string is undef, it is 0.

The $string is copied to the value of the the created string buffer.

=head2 new_len

  static method new_len : StringBuffer ($length : int, $capacity : int = -1);

Creates a new C<StringBuffer> object with the $length and the $capacity.

If the $capacity is less than 0, the $capacity is set to the value of L</"DEFAULT_CAPACITY">.

If the $length is greater than the $capacity, the $capacity is set to the $length.

Exceptions:

The $length must be greater than or equal to 0. Otherwise an exception is thrown.

=head1 Instance Methods

=head2 push

  method push : void ($string : string, $offset : int = 0, $length : int = -1);

Adds a $string from the $offset to the position proceeded by the $length after the end of the string in the string buffer.

Exceptions:

The $string must be defined. Otherwise an exception is thrown.

The $offset must be greater than or equal to 0. Otherwise an exception is thrown.

The $offset + $length must be less than or equal to the length of the $string. Otherwise an exception is thrown.

=head2 push_char

  method push_char : void ($char : int);

Adds Ascii $char after the end of the string in the string buffer.

=head2 replace

  method replace : void ($offset : int, $length : int, $replace : string);

Replace the characters of the range specified by the $offset and the $length in the buffer with the $replace string.

Exceptions:

The $offset must be greater than or equal to 0. Otherwise an exception is thrown.

The $offset + the $length must be less than or equal to the length of the string buffer. Otherwise an exception is thrown.

=head2 reserve

  method reserve : void ($new_capacity : int);

Reserves the characters that size is the $new_capacity.

If the $new_capacity is greater than the capacity of the string buffer, the capacity of the string buffer is extended to the $new_capacity.

Note that L</"value"> is replaced with the new value and the value of the original string buffer are copied to the new value in the above case.

Exceptions:

The $new_capacity must be greater than or equal to 0. Otherwise an exception is thrown.

=head2 to_string

  method to_string : string ();

Convert the string buffer to a string.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

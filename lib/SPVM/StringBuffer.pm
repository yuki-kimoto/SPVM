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

The default capacity. The value is C<4>.

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

  static method new : StringBuffer ($string = undef : string, $capacity = -1 : int);

Creates a new C<StringBuffer> object using L</"new_len">.

The passed C<$length> to L</"new_len"> is the length of the C<$string>. If the string is C<undef>, it is C<0>.

The C<$string> is copied to the value of the the created string buffer.

=head2 new_len

  static method new_len : StringBuffer ($length : int, $capacity = -1 : int);

Creates a new C<StringBuffer> object with the C<$length> and the C<$capacity>.

If the C<$capacity> is less than C<0>, the C<$capacity> is set to the value of L</"DEFAULT_CAPACITY">.

If the C<$length> is greater than the C<$capacity>, the C<$capacity> is set to the C<$length>.

Exceptions:

The C<$length> must be greater than or equal to C<0>.

=head1 Instance Methods

=head2 push

  method push : void ($string : string, $offset = 0 : int, $length = -1 : int);

Adds a C<$string> from the C<$offset> to the position proceeded by the C<$length> after the end of the string in the string buffer.

Exceptions:

The C<$string> must be defined.

The C<$offset> must be greater than or equal to 0.

The C<$offset> + C<$length> must be less than or equal to the length of the C<$string>.

=head2 push_char

  method push_char : void ($char : int);

Adds Ascii C<$char> after the end of the string in the string buffer.

=head2 replace

  method replace : void ($offset : int, $length : int, $replace : string);

Replace the characters of the range specified by the C<$offset> and the C<$length> in the buffer with the C<$replace> string.

Exceptions:

The C<$offset> must be greater than or equal to C<0>.

The C<$offset> + the C<$length> must be less than or equal to the length of the string buffer.

=head2 reserve

  method reserve : void ($new_capacity : int);

Reserves the characters that size is the C<$new_capacity>.

If the C<$new_capacity> is greater than the capacity of the string buffer, the capacity of the string buffer is extended to the C<$new_capacity>.

Note that L</"value"> is replaced with the new value and the value of the original string buffer are copied to the new value in the above case.

Exceptions:

The C<$new_capacity> must be greater than or equal to C<0>.

=head2 to_string

  method to_string : string ();

Convert the string buffer to a string.

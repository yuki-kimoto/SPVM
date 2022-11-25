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

Create a new C<StringBuffer> object using L</"new_len">.

The passed length to L</"new_len"> is the length of the string. If the string is C<undef>, the length is C<0>.

The string is copied to the value of the the created string buffer.

=head2 new_len

  static method new_len : StringBuffer ($length : int, $capacity = -1 : int);

Create a new C<StringBuffer> object with the length and the capacity.

If the capacity is less than C<0>, the capacity is set to the value of L</"DEFAULT_CAPACITY">.

If the length is greater than the capacity, the capacity is set to the length.

The $length must be greater than or equal to C<0>. Otherwise an excpetion will be thrown.

=head1 Instance Methods

=head2 push

  method push  : void ($string : string);

Add a string after the end of the string in the string buffer.

=head2 push_char

  method push_char : void ($char : int);

Add a character after the end of the string in the string buffer.

=head2 replace

  method replace : void ($offset : int, $length : int, $replace : string);

Replace the characters of the range specified by the offset and the lenght with the replacement string.

Exceptions:

The $offset must be greater than or equal to C<0>.

The $offset + the $removing lenght must be less than or equal to the length of the $string buffer.

=head2 reserve

  method reserve : void ($new_capacity : int);

Reserve the characters with the new capacity.

If the new capacity is greater than the capacity of the string buffer, the capacity of the string buffer is extended to the new capacity.

Note that L</"value"> is replaced with the new value and the value of the original string buffer are copied to the new value in the above case.

The $new_capacity must be greater than or equal to C<0>. Otherwise an excpetion will be thrown.

=head2 to_string

  method to_string : string ();

Convert the string buffer to a string.

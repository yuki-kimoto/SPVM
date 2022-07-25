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

=head1 Fields

=head2 length

  has length : ro int;

The length.

=head2 value

  has value : ro mutable string;

The value. This is the internally used string, but it can be manipulated directly.

  my $value = $buffer->value;
  $valeu->[0] = 'a';

=head1 Class Methods

=head2 new

  static method new : StringBuffer ()

Create new L<StringBuffer|SPVM::StringBuffer> object.

=head1 Instance Methods

=head2 push

  method push  : void ($string : string)

Add a string after the end of the string in the string buffer.

=head2 push_char

  method push_char : void ($char : byte)

Add a character after the end of the string in the string buffer.

=head2 replace

  method replace : void ($offset : int, $length : int, $replace : string)

Replace the characters of the range specified by the offset and the lenght with the replacement string.

The offset must be greater than or equal to 0. Otherwise an exception will be thrown.

The offset + the lenght must be less than or equal to the length of the string that the string buffer has. Otherwise an exception will be thrown.

=head2 to_string

  method to_string : string ()

Convert the string buffer to a string.

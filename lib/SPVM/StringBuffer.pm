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

=head1 Class Methods

=head2 new

  static method new : StringBuffer ()

Create new L<StringBuffer|SPVM::StringBuffer> object.

=head1 Instance Methods

=head2 value

  method value : mutable string; ()

Get the value of the string buffer.

=head2 length

  method length : int ()

Get the string length.

=head2 push

  method push  : void ($string : string)

Push a string to the string buffer.

=head2 push_char

  method push_char : void ($char : byte)

Push a character to the string buffer.

=head2 replace

  method replace : void ($offset : int, $length : int, $replace : string) {

Replace the range(from the offset to the offeset + the lenth) of the string buffer with the replacement string.

The offset must be greater than or equal to 0. Otherwise an exception will be thrown.

The offset + the lenght must be less than or equal to the length of the string that the string buffer has. Otherwise an exception will be thrown.

=head2 to_string

  method to_string : string ()

Convert the string buffer to a string.

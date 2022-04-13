package SPVM::StringBuffer;

1;

=head1 NAME

SPVM::StringBuffer - String buffer

=head1 SYNOPSYS
  
  use StringBuffer;
  
  # new
  my $buffer = StringBuffer->new;
  
  # push string
  $buffer->push("abc");
  $buffer->push("def");
  
  # Convert to string - abcdef
  my $string = $buffer->to_string;
  
=head1 DESCRIPTION

String buffer.

=head1 CLASS METHODS

=head2 new

  static method new : StringBuffer ()

Create new L<StringBuffer|SPVM::StringBuffer> object.

=head1 INSTANCE METHODS

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

=head2 to_string

  method to_string : string ()

Convert the string buffer to a string.

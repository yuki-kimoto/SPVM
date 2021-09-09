package SPVM::StringBuffer;

1;

=head1 NAME

SPVM::StringBuffer - StringBuffer in SPVM | String buffer

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

  sub new : StringBuffer ()

Create new L<StringBuffer|SPVM::StringBuffer> object.

=head1 INSTANCE METHODS

=head2 length

  sub length : int ($self : self)

Get the string length.

=head2 push

  sub push  : void ($self : self, $string : string)

Push a string to the string buffer.

=head2 push_char

  sub push_char : void ($self : self, $char : byte)

Push a character to the string buffer.

=head2 to_string

  sub to_string : string ($self : self)

Convert the string buffer to a string.

package SPVM::StringBuffer;

1;

=head1 NAME

SPVM::StringBuffer - String buffer

=head1 SYNOPSYS
  
  use SPVM::StringBuffer;
  
  # new
  my $buffer = SPVM::StringBuffer->new;
  
  # push string
  $buffer->push("abc");
  $buffer->push("def");
  
  # Convert to string - abcdef
  my $str = $buffer->to_string;
  
  # Cat sub string - bcd
  my $offset = 1;
  my $length = 3;
  my $substr = $buffer->substr($offset, $length);

  # Search string
  my $search = "cd";
  my $start_pos = 1;
  my $found_pos = $buffer->index($search, $start_pos);
  
  # new with option
  my $buffer = SPVM::StringBuffer->new_opt([(object)capacity => 256]);

=head1 DESCRIPTION

String buffer. Performance is better than concat operator when many strings is joined.

=head1 STATIC METHODS

=head2 new

  sub new : SPVM::StringBuffer ()

Create new L<SPVM::StringBuffer> object which capacity is 16 bytes without string 

=head2 new_opt

  sub new_opt : SPVM::StringBuffer ($options : object[])

Create new L<SPVM::StringBuffer> object with options.

=over 2

=item * capacity : SPVM::Int

Capacity of string buffer. Capacity must be more than 0.

=back

=head1 INSTANCE METHODS

=head2 length

  sub length : int ($self : self)

Get string length.

=head2 capacity

  sub capacity : int ($self : self)

Get capacity of string buffer.

=head2 push

  sub push  : void ($self : self, $string : string)

Push string to string buffer.

=head2 to_string

  sub to_string : string ($self : self)

Convert string buffer to string.

=head2 clear

  sub clear : void ($self : self)

Clear string.

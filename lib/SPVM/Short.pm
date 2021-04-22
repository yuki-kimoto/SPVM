package SPVM::Short;

1;

=head1 NAME

SPVM::Short - Short object

=head1 SYNOPSYS
  
  use SPVM::Short;
  
  my $short_object = SPVM::Short->new(5);
  my $short_value = $short_object->value;

=head1 DESCRIPTION

L<SPVM::Short> object stores a C<short> value.

This object is immutable and its value cannot be changed.

L<SPVM::Short> is automatically loaded just after the program starts.

=head1 STATIC METHODS

=head2 new

  sub new : SPVM::Short ($value : short)

Create a new L<SPVM::Short> object with a C<short> value.

=head1 INSTANCE METHODS

=head2 value

  sub value : short ($self : self)

Get a C<short> value.

package SPVM::Long;

1;

=head1 NAME

SPVM::Long - Long object

=head1 SYNOPSYS

  use SPVM::Long;
  
  my $long_object = SPVM::Long->new(5L);
  my $long_value = $long_object->value;

=head1 DESCRIPTION

L<SPVM::Long> object stores a C<long> value.

This object is immutable and its value cannot be changed.

L<SPVM::Long> is automatically loaded just after the program starts.

=head1 STATIC METHODS

=head2 new

  sub new : SPVM::Long ($value : long)

Create a new L<SPVM::Long> object with a C<long> value.

=head1 INSTANCE METHODS

=head2 value

  sub value : long ($self : self)

Get a C<long> value.

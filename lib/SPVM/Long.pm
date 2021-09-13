package SPVM::Long;

1;

=head1 NAME

SPVM::Long - Long in SPVM | Long object

=head1 SYNOPSYS

  use Long;
  
  my $long_object = Long->new(5L);
  my $long_value = $long_object->value;

=head1 DESCRIPTION

L<Long|SPVM::Long> object stores a C<long> value.

This object is immutable and its value cannot be changed.

L<Long|SPVM::Long> is automatically loaded just after the program starts.

=head1 CLASS METHODS

=head2 new

  static method new : Long ($value : long)

Create a new L<Long|SPVM::Long> object with a C<long> value.

=head1 INSTANCE METHODS

=head2 value

  method value : long ()

Get a C<long> value.

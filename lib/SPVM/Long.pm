package SPVM::Long;

1;

=head1 Name

SPVM::Long - Long object

=head1 Synopsys

  use Long;
  
  my $long_object = Long->new(5L);
  my $long_value = $long_object->value;

=head1 Description

L<Long|SPVM::Long> object stores a C<long> value.

This object is immutable and its value cannot be changed.

L<Long|SPVM::Long> is automatically loaded just after the program starts.

=head1 Class Methods

=head2 new

  static method new : Long ($value : long)

Create a new L<Long|SPVM::Long> object with a C<long> value.

=head1 Instance Methods

=head2 value

  method value : long ()

Get a C<long> value.

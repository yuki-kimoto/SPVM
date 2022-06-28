package SPVM::Short;

1;

=head1 Name

SPVM::Short - Short object

=head1 Synopsys
  
  use Short;
  
  my $short_object = Short->new(5);
  my $short_value = $short_object->value;

=head1 Description

L<Short|SPVM::Short> object stores a C<short> value.

This object is immutable and its value cannot be changed.

L<Short|SPVM::Short> is automatically loaded just after the program starts.

=head1 Class Methods

=head2 new

  static method new : Short ($value : short)

Create a new L<Short|SPVM::Short> object with a C<short> value.

=head1 Instance Methods

=head2 value

  method value : short ()

Get a C<short> value.

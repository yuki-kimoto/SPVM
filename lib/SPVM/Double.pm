package SPVM::Double;

1;

=head1 Name

SPVM::Double - Double object

=head1 Usage

  use Double;
  
  my $double_object = Double->new(0.25);
  my $double_value = $double_object->value;

=head1 Description

L<Double|SPVM::Double> object stores a C<double> value.

This object is immutable and its value cannot be changed.

L<Double|SPVM::Double> is automatically loaded just after the program starts.

=head1 Class Methods

=head2 new

  static method new : Double ($value : double)

Create a new L<Double|SPVM::Double> object with a C<double> value.

=head1 Instance Methods

=head2 value

  method value : double ()

Get a C<double> value.

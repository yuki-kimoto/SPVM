package SPVM::Double;

1;

=head1 NAME

SPVM::Double - Double in SPVM | Double object

=head1 SYNOPSYS

  use Double;
  
  my $double_object = Double->new(0.25);
  my $double_value = $double_object->value;

=head1 DESCRIPTION

L<Double|SPVM::Double> object stores a C<double> value.

This object is immutable and its value cannot be changed.

L<Double|SPVM::Double> is automatically loaded just after the program starts.

=head1 STATIC METHODS

=head2 new

  sub new : Double ($value : double)

Create a new L<Double|SPVM::Double> object with a C<double> value.

=head1 INSTANCE METHODS

=head2 value

  sub value : double ($self : self)

Get a C<double> value.

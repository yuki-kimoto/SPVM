package SPVM::Int;

1;

=head1 NAME

SPVM::Int - Int object

=head1 SYNOPSYS

  use Int;

  my $int_object = Int->new(5);
  my $int_value = $int_object->value;

=head1 DESCRIPTION

L<Int|SPVM::Int> object stores a C<int> value.

This object is immutable and its value cannot be changed.

L<Int|SPVM::Int> is automatically loaded just after the program starts.

=head1 CLASS METHODS

=head2 new

  static method new : Int ($value : int)

Create a new L<Int|SPVM::Int> object with a C<int> value.

=head1 INSTANCE METHODS

=head2 value

  method value : int ()

Get a C<int> value.

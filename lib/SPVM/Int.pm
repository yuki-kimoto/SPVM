package SPVM::Int;

1;

=head1 Name

SPVM::Int - Int Class

=head1 Usage
  
  my $int_object = Int->new(5);
  my $int_value = $int_object->value;
  $int_object->set_value(10);

=head1 Description

C<Int> is the class to hold a value of the C<int> type.

This class is automatically loaded.

=head1 Fields

=head2 value

  has value : rw int;

The value.

=head1 Class Methods

=head2 new

  static method new : Int ($value : int)

Create a new L<Int|SPVM::Int> object with a C<int> value.

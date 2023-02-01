package SPVM::Long;

1;

=head1 Name

SPVM::Long - Long Class

=head1 Usage
  
  my $long_object = Long->new(5);
  my $long_value = $long_object->value;
  $long_object->set_value(10);

=head1 Description

C<Long> is the class to hold a value of the C<long> type.

This class is automatically loaded.

=head1 Fields

=head2 value

  has value : rw long;

The value.

=head1 Class Methods

=head2 new

  static method new : Long ($value : long);

Creates a new L<Long|SPVM::Long> object with a C<long> $value.

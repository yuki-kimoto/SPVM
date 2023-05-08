package SPVM::Double;

1;

=head1 Name

SPVM::Double - Double Object

=head1 Description

The Double class has methods to manipulate an object that has a double value.

This class is immutable.

This class is automatically loaded.

=head1 Usage
  
  my $double_object = Double->new(5);
  my $double_value = $double_object->value;

=head1 Fields

=head2 value

  has value : ro double;

The value.

=head1 Class Methods

=head2 new

  static method new : Double ($value : double);

Creates a new L<Double|SPVM::Double> object with a C<double> $value.

=head1 See Also

=over 2

=item * L<Mutable::Double|SPVM::Mutable::Double> - Mutable Double Object

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

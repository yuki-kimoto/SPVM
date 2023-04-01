package SPVM::Double;

1;

=head1 Name

SPVM::Double - Double Class

=head1 Usage
  
  my $double_object = Double->new(5);
  my $double_value = $double_object->value;
  $double_object->set_value(10);

=head1 Description

C<Double> is the class to hold a value of the C<double> type.

This class is automatically loaded.

=head1 Fields

=head2 value

  has value : rw double;

The value.

=head1 Class Methods

=head2 new

  static method new : Double ($value : double);

Creates a new L<Double|SPVM::Double> object with a C<double> $value.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

package SPVM::Double;

1;

=head1 Name

SPVM::Double - A double value as An Object

=head1 Description

Double class in L<SPVM> represents a double value as an object.

=head1 Usage
  
  my $double_object = Double->new(5);
  my $double_value = $double_object->value;

=head1 Details

This class is immutable.

This class is automatically loaded.

=head1 Interfaces

=over 2

=item * L<Stringable|SPVM::Stringable>

=back

=head1 Fields

=head2 value

C<has value : ro double;>

The value.

=head1 Class Methods

=head2 new

C<static method new : L<Double|SPVM::Double> ($value : double);>

Creates a new L<Double|SPVM::Double> object with a C<double> $value.

=head1 Instance Methods

=head2 to_string

C<method to_string : string ();>

Casts the value to string type and returns it.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

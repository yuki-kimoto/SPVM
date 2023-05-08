package SPVM::Long;

1;

=head1 Name

SPVM::Long - The long Object

=head1 Description

The Long class has methods to manipulate an object that has a long value.

This class is immutable.

This class is automatically loaded.

=head1 Usage
  
  my $long_object = Long->new(5);
  my $long_value = $long_object->value;

=head1 Fields

=head2 value

  has value : ro long;

The value.

=head1 Class Methods

=head2 new

  static method new : Long ($value : long);

Creates a new L<Long|SPVM::Long> object with a C<long> $value.

=head1 See Also

=over 2

=item * L<Mutable::Long|SPVM::Mutable::Long> - Mutable Long Object

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

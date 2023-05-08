package SPVM::Mutable::Long;

1;

=head1 Name

SPVM::Mutable::Long - Mutable long Object

=head1 Description

The Mutable::Long class has methods to manipulate an object that has a long value.

This class is mutable.

=head1 Usage
  
  my $long_object = Mutable::Long->new(5);
  my $long_value = $long_object->value;
  $long_object->set_value(10);

=head1 Fields

=head2 value

  has value : rw long;

The value.

=head1 Class Methods

=head2 new

  static method new : Mutable::Long ($value : long);

Creates a new L<Mutable::Long|SPVM::Mutable::Long> object with a C<long> $value.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

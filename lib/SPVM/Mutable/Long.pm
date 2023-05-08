package SPVM::Mutable::Long;

1;

=head1 Name

SPVM::Mutable::Long - Mutable::Long Class

=head1 Usage
  
  my $long_object = Mutable::Long->new(5);
  my $long_value = $long_object->value;
  $long_object->set_value(10);

=head1 Description

C<Mutable::Long> is the class to hold a value of the C<long> type.

This class is automatically loaded.

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

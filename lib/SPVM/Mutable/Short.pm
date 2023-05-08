package SPVM::Mutable::Short;

1;

=head1 Name

SPVM::Mutable::Short - Mutable short Object

=head1 Description

The Mutable::Short class has methods to manipulate an object that has a short value.

This class is mutable.

=head1 Usage
  
  my $short_object = Mutable::Short->new(5);
  my $short_value = $short_object->value;
  $short_object->set_value(10);

=head1 Fields

=head2 value

  has value : rw short;

The value.

=head1 Class Methods

=head2 new

  static method new : Mutable::Short ($value : int);

Creates a new L<Mutable::Short|SPVM::Mutable::Short> object with a C<short> $value.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

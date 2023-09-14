package SPVM::Short;

1;

=head1 Name

SPVM::Short - The short Class

=head1 Description

The Short class has methods to manipulate an object that has a short value.

This class is immutable.

This class is automatically loaded.

=head1 Usage
  
  my $short_object = Short->new(5);
  my $short_value = $short_object->value;

=head1 Fields

=head2 value

  has value : ro short;

The value.

=head1 Class Methods

=head2 new

C<static method new : L<Short|SPVM::Short> ($value : int);>

Creates a new L<Short|SPVM::Short> object with a C<short> $value.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

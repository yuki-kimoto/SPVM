package SPVM::Long;

1;

=head1 Name

SPVM::Long - A long value as An Object

=head1 Description

The Long class in L<SPVM> represents a long value as an object.

=head1 Usage
  
  my $long_object = Long->new(5);
  my $long_value = $long_object->value;

=head1 Details

This class is immutable.

This class is automatically loaded.

=head1 Fields

=head2 value

C<has value : ro long;>

The value.

=head1 Class Methods

=head2 new

C<static method new : L<Long|SPVM::Long> ($value : long);>

Creates a new L<Long|SPVM::Long> object with a C<long> $value.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

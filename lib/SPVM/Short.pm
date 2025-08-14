package SPVM::Short;

1;

=head1 Name

SPVM::Short - A short Value as An Object

=head1 Description

Short class in L<SPVM> represents a short value as an object.

=head1 Usage
  
  my $short_object = Short->new(5);
  my $short_value = $short_object->value;

=head1 Details

This class is immutable.

This class is automatically loaded.

=head1 Interfaces

=over 2

=item * L<Stringable|SPVM::Stringable>

=back

=head1 Fields

=head2 value

C<has value : ro short;>

The value.

=head1 Class Methods

=head2 new

C<static method new : L<Short|SPVM::Short> ($value : int);>

Creates a new L<Short|SPVM::Short> object with a C<short> $value.

=head1 Instance Methods

=head2 to_string

C<method to_string : string ();>

Casts the value to string type and returns it.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

package SPVM::Long;

1;

=head1 Name

SPVM::Long - A long value as An Object

=head1 Description

Long class in L<SPVM> represents a long value as an object.

=head1 Usage
  
  my $long_object = Long->new(5L);
  my $long_value = $long_object->value;
  $long_object->set_value(10L);

  # New unsigned object
  my $unsigned_long = Long->new_unsigned(0xFFFFFFFFFFFFFFFFL); # 18446744073709551615

=head1 Details

This class is automatically loaded.

=head1 Interfaces

=over 2

=item * L<Stringable|SPVM::Stringable>
=item * L<Cloneable|SPVM::Cloneable>

=back

=head1 Fields

=head2 value

C<has value : rw long;>

The value.

If the L</"unsigned"> field is 1, the value is treated as an unsigned 64-bit integer (0 to 18446744073709551615).

If the L</"is_read_only"> field is 1, a compilation error or a runtime error occurs when setting the value.

=head2 is_read_only

C<has is_read_only : ro byte;>

If this value is 1, the L</"value"> field is read-only.

=head2 unsigned

C<has unsigned : rw byte;>

If this value is 1, the value is treated as an unsigned 64-bit integer.

=head1 Class Methods

=head2 new

C<static method new : L<Long|SPVM::Long> ($value : long);>

Creates a new L<Long|SPVM::Long> object with a C<long> $value. The L</"unsigned"> field is initialized to 0.

=head2 new_unsigned

C<static method new_unsigned : L<Long|SPVM::Long> ($value : long);>

Creates a new L<Long|SPVM::Long> object with a C<long> $value. The L</"unsigned"> field is initialized to 1.

=head1 Instance Methods

=head2 make_read_only

C<method make_read_only : void ();>

Sets L</"is_read_only"> field to 1.

=head2 clone

C<method clone : L<Long|SPVM::Long> ();>

Creates a new L<Long|SPVM::Long> object that clones this object.

The L</"unsigned"> field is copied to the new object.

The value of L</"is_read_only"> field in the new object is 0.

=head2 to_string

C<method to_string : string ();>

Casts the value to string type and returns it.

If L</"unsigned"> field is 1, the value is converted to a string as an unsigned 64-bit integer.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

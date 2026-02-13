package SPVM::Int;

1;

=head1 Name

SPVM::Int - An int value as An Object

=head1 Description

Int class in L<SPVM> represents an int value as an object.

=head1 Usage
  
  my $int_object = Int->new(5);
  my $int_value = $int_object->value;
  $int_object->set_value(10);

  # New unsigned object
  my $unsigned_int = Int->new_unsigned(0xFFFFFFFF); # 4294967295

=head1 Details

This class is automatically loaded.

=head1 Interfaces

=over 2

=item * L<Stringable|SPVM::Stringable>
=item * L<Cloneable|SPVM::Cloneable>

=back

=head1 Fields

=head2 value

C<has value : rw int;>

The value.

If the L</"unsigned"> field is 1, the value is treated as an unsigned 32-bit integer (0 to 4294967295).

If the L</"is_read_only"> field is 1, a compilation error or a runtime error occurs when setting the value.

=head2 is_read_only

C<has is_read_only : ro byte;>

If this value is 1, the L</"value"> field is read-only.

=head2 unsigned

C<has unsigned : rw byte;>

If this value is 1, the value is treated as an unsigned 32-bit integer.

=head1 Class Methods

=head2 new

C<static method new : L<Int|SPVM::Int> ($value : int);>

Creates a new L<Int|SPVM::Int> object with an C<int> $value. The L</"unsigned"> field is initialized to 0.

=head2 new_unsigned

C<static method new_unsigned : L<Int|SPVM::Int> ($value : int);>

Creates a new L<Int|SPVM::Int> object with an C<int> $value. The L</"unsigned"> field is initialized to 1.

=head1 Instance Methods

=head2 make_read_only

C<method make_read_only : void ();>

Sets L</"is_read_only"> field to 1.

=head2 clone

C<method clone : L<Int|SPVM::Int> ();>

Creates a new L<Int|SPVM::Int> object that clones this object.

The L</"unsigned"> field is copied to the new object.

The value of L</"is_read_only"> field in the new object is 0.

=head2 to_string

C<method to_string : string ();>

Casts the value to string type and returns it.

If L</"unsigned"> field is 1, the value is converted to a string as an unsigned 32-bit integer.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

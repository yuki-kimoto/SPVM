package SPVM::Byte;

1;

=head1 Name

SPVM::Byte - A byte Value as An Object

=head1 Description

Byte class in L<SPVM> represents a byte value as an object.

=head1 Usage
  
  my $byte_object = Byte->new(5);
  my $byte_value = $byte_object->value;
  $byte_object->set_value(10);

=head1 Details

This class is automatically loaded.

=head1 Interfaces

=over 2

=item * L<Stringable|SPVM::Stringable>
=item * L<Cloneable|SPVM::Cloneable>

=back

=head1 Fields

=head2 value

C<has value : rw byte;>

The value. If the L</"is_read_only"> field is 1, a compilation error or a runtime error occurs when setting the value.

=head2 is_read_only

C<has is_read_only : ro byte;>

If this value is 1, the L</"value"> field is read-only.

=head1 Class Methods

=head2 new

C<static method new : L<Byte|SPVM::Byte> ($value : int);>

Creates a new L<Byte|SPVM::Byte> object with a C<byte> $value.

=head1 Instance Methods

=head2 make_read_only

C<method make_read_only : void ();>

Sets L</"is_read_only"> field to 1.

=head2 clone

C<method clone : L<Byte|SPVM::Byte> ();>

Creates a new L<Byte|SPVM::Byte> object that clones this object. The value of L</"is_read_only"> field in the new object is 0.

=head2 to_string

C<method to_string : string ();>

Casts the value to string type and returns it.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

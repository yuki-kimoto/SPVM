package SPVM::Short;

1;

=head1 Name

SPVM::Short - A short Value as An Object

=head1 Description

Short class in L<SPVM> represents a short value as an object.

=head1 Usage
  
  my $short_object = Short->new(5);
  my $short_value = $short_object->value;
  $short_object->set_value(10);

=head1 Details

This class is automatically loaded.

=head1 Interfaces

=over 2

=item * L<Stringable|SPVM::Stringable>
=item * L<Cloneable|SPVM::Cloneable>

=back

=head1 Fields

=head2 value

C<has value : rw short;>

The value. If the L</"is_read_only"> field is 1, a compilation error or a runtime error occurs when setting the value.

=head2 is_read_only

C<has is_read_only : ro byte;>

If this value is 1, the L</"value"> field is read-only.

=head1 Class Methods

=head2 new

C<static method new : L<Short|SPVM::Short> ($value : int);>

Creates a new L<Short|SPVM::Short> object with a C<short> $value.

=head1 Instance Methods

=head2 make_read_only

C<method make_read_only : void ();>

Sets L</"is_read_only"> field to 1.

=head2 clone

C<method clone : L<Short|SPVM::Short> ();>

Creates a new L<Short|SPVM::Short> object that clones this object. The value of L</"is_read_only"> field in the new object is 0.

=head2 to_string

C<method to_string : string ();>

Casts the value to string type and returns it.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

package SPVM::Int;

1;

=head1 Name

SPVM::Int - An int value as An Object
=head1 Description

The Int class in L<SPVM> represents an int value as an object.

=head1 Usage
  
  my $int_object = Int->new(5);
  my $int_value = $int_object->value;

=head1 Details

This class is immutable.

This class is automatically loaded.

=head1 Fields

=head2 value

C<has value : ro int;>

The value.

=head1 Class Methods

=head2 new

C<static method new : L<Int|SPVM::Int> ($value : int);>

Creates a new L<Int|SPVM::Int> object with a C<int> $value.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

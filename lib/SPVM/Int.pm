package SPVM::Int;

1;

=head1 Name

SPVM::Int - Int Object

=head1 Description

The Int class has methods to manipulate an object that has an int value.

This class is immutable.

This class is automatically loaded.

=head1 Usage
  
  my $int_object = Int->new(5);
  my $int_value = $int_object->value;

=head1 Fields

=head2 value

  has value : ro int;

The value.

=head1 Class Methods

=head2 new

  static method new : Int ($value : int);

Creates a new L<Int|SPVM::Int> object with a C<int> $value.

=head1 See Also

=over 2

=item * L<Mutable::Int|SPVM::Mutable::Int> - Mutable Int Object

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

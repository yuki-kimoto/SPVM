package SPVM::Mutable::Int;

1;

=head1 Name

SPVM::Mutable::Int - Mutable::Int Class

=head1 Usage
  
  my $int_object = Mutable::Int->new(5);
  my $int_value = $int_object->value;
  $int_object->set_value(10);

=head1 Description

C<Mutable::Int> is the class to hold a value of the C<int> type.

This class is automatically loaded.

=head1 Fields

=head2 value

  has value : rw int;

The value.

=head1 Class Methods

=head2 new

  static method new : Mutable::Int ($value : int);

Creates a new L<Mutable::Int|SPVM::Mutable::Int> object with a C<int> $value.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

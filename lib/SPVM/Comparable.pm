package SPVM::Comparable;



1;

=head1 Name

SPVM::Comparable - Comparable Interface

=head1 Description

Comparable interface in L<SPVM> has interface methods to compare two objects.

=head1 Usage

  interface Comparable;

=head1 Interface Methods

C<required method cmp : int ($a : object, $b : object);>

An interface method to compare two objects.

If $a is greater than $b, returns a positive value.

If $a is equal to $b, returns 0.

If $a is less than $b, returns a negative value.

=head1 Copyright & License

Copyright (c) 2024 Yuki Kimoto

MIT License

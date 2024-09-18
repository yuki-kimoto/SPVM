package SPVM::EqualityCheckable;



1;

=head1 Name

SPVM::EqualityCheckable - EqualityCheckable Interface

=head1 Description

EqualityCheckable interface in L<SPVM> has interface methods to check equality of two objects.

=head1 Usage

  interface EqualityCheckable;

=head1 Interface Methods

C<required method eq : int ($a : object, $b : object);>

An interface method to check equality of two objects.

If $a is equal to $b, returns 1, otherwise returns 0.

=head1 Copyright & License

Copyright (c) 2024 Yuki Kimoto

MIT License


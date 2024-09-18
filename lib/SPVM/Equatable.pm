package SPVM::Equatable;



1;

=head1 Name

SPVM::Equatable - Equatable Interface

=head1 Description

Equatable interface in L<SPVM> has interface methods to check equality of two objects.

=head1 Usage

  interface Equatable;

=head1 Interface Methods

C<required method eq : int ($a : object, $b : object);>

An interface method to check equality of two objects.

If $a is equal to $b, returns 1, otherwise returns 0.

=head1 Copyright & License

Copyright (c) 2024 Yuki Kimoto

MIT License


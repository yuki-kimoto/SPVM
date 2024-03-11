package SPVM::Callback::MapExpand;



1;

=head1 Name

SPVM::Callback::MapExpand - A Callback for The map_expand Method
=head1 Description

The Callback::MapExpand interface in L<SPVM> has interface methods for the L<map_expand|Fn/"map_expand"> method in the Fn class.

=head1 Usage

  interface Callback::MapExpand;

=head1 Interface Methods

C<required method : object[] ($element : object);>

Returns elements after operating the element $element.

=head1 Copyright & License

Copyright (c) 2024 Yuki Kimoto

MIT License


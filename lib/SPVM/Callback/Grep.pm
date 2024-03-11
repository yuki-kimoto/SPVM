package SPVM::Callback::Grep;



1;

=head1 Name

SPVM::Callback::Grep - A Callback for The grep Method

=head1 Description

The Callback::Grep interface in L<SPVM> has interface methods for the L<grep|Fn/"grep"> method in the Fn class.

=head1 Usage

  interface Callback::Grep;

=head1 Interface Methods

C<required method : int ($element : object);>

Returns a true value if the condition corresponding to the element $element is satisfied, otherwise returns 0.

=head1 Copyright & License

Copyright (c) 2024 Yuki Kimoto

MIT License


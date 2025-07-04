package SPVM::Callback::Grep;



1;

=head1 Name

SPVM::Callback::Grep - A Callback Interface for grep Method

=head1 Description

Callback::Grep interface in L<SPVM> is a callback interface for L<Fn#grep|SPVM::Fn/"grep"> method.

=head1 Interface Methods

C<required method : int ($element : object);>

If a condition for the element $element is satisfied, returns 1; otherwise returns 0.

=head1 Copyright & License

Copyright (c) 2024 Yuki Kimoto

MIT License


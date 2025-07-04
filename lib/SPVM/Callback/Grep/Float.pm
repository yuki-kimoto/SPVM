package SPVM::Callback::Grep::Float;



1;

=head1 Name

SPVM::Callback::Grep::Float - A Callback Interface for grep_float Method

=head1 Description

Callback::Grep::Float interface in L<SPVM> is a callback interface for L<Fn#grep_float|SPVM::Fn/"grep_float"> method.

=head1 Interface Methods

C<required method : int ($element : float);>

If a condition for the element $element is satisfied, returns 1; otherwise returns 0.

=head1 Copyright & License

Copyright (c) 2024 Yuki Kimoto

MIT License


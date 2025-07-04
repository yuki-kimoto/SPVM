package SPVM::Callback::Grep::Int;



1;

=head1 Name

SPVM::Callback::Grep::Int - A Callback Interface for grep_int Method

=head1 Description

Callback::Grep::Int interface in L<SPVM> is a callback interface for L<Fn#grep_int|SPVM::Fn/"grep_int"> method.

=head1 Interface Methods

C<required method : int ($element : int);>

If a condition for the element $element is satisfied, returns 1; otherwise returns 0.

=head1 Copyright & License

Copyright (c) 2024 Yuki Kimoto

MIT License


package SPVM::Callback::Grep::Double;



1;

=head1 Name

SPVM::Callback::Grep::Double - A Callback Interface for grep_double Method

=head1 Description

Callback::Grep interface::Double in L<SPVM> is a callback interface for L<Fn#grep_double|SPVM::Fn/"grep_double"> method.

=head1 Interface Methods

C<required method : int ($element : double);>

If a condition for the element $element is satisfied, returns 1; otherwise returns 0.

=head1 Copyright & License

Copyright (c) 2024 Yuki Kimoto

MIT License


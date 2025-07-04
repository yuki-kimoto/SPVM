package SPVM::Callback::Grep::Long;



1;

=head1 Name

SPVM::Callback::Grep::Long - A Callback Interface for grep_long Method

=head1 Description

Callback::Grep::Long interface in L<SPVM> is a callback interface for L<Fn#grep_long|SPVM::Fn/"grep_long"> method.

=head1 Interface Methods

C<required method : int ($element : long);>

If a condition for the element $element is satisfied, returns 1; otherwise returns 0.

=head1 Copyright & License

Copyright (c) 2024 Yuki Kimoto

MIT License


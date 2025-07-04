package SPVM::Callback::Grep::Byte;



1;

=head1 Name

SPVM::Callback::Grep::Byte - A Callback Interface for grep_byte Method

=head1 Description

Callback::Grep::Byte interface in L<SPVM> is a callback interface for L<Fn#grep_byte|SPVM::Fn/"grep_byte"> method.

=head1 Interface Methods

C<required method : int ($element : byte);>

If a condition for the element $element is satisfied, returns 1; otherwise returns 0.

=head1 Copyright & License

Copyright (c) 2024 Yuki Kimoto

MIT License


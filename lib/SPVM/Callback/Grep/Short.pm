package SPVM::Callback::Grep::Short;



1;

=head1 Name

SPVM::Callback::Grep::Short - A Callback Interface for grep_short Method

=head1 Description

Callback::Grep::Short interface in L<SPVM> is a callback interface for L<Fn#grep_short|SPVM::Fn/"grep_short"> method.

=head1 Interface Methods

C<required method : int ($element : short);>

If a condition for the element $element is satisfied, returns 1; otherwise returns 0.

=head1 Copyright & License

Copyright (c) 2024 Yuki Kimoto

MIT License


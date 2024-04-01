=head1 Name

SPVM::Document::Language::System - System Setting in the SPVM Language

=head1 Description

This document describes system setting in the SPVM language.

=head1 System Setting

=head2 Standard Streams

SPVM opens own standard input, standard output, and standard error for a runtime just after a runtime is build.

Their open modes are set to the L<binary mode|https://learn.microsoft.com/en-us/cpp/c-runtime-library/text-and-binary-mode-file-i-o?view=msvc-170> in Windows.

The L<print operator|SPVM::Document::Language::Operators/"print Operator"> outputs to this SPVM's standard output.

The L<say operator|SPVM::Document::Language::Operators/"say Operator"> outputs to this SPVM's standard output.

The L<warn operator|SPVM::Document::Language::Operators/"warn Operator"> outputs to this SPVM's standard error.

=head1 See Also

=over 2

=item * L<SPVM::Document::Language::Operators>

=item * L<SPVM::Document::Language>

=item * L<SPVM::Document>

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

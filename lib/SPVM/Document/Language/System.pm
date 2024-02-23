=head1 Name

SPVM::Document::Language::System - System Setting in SPVM Language

=head1 Description

This document describes system setting in SPVM language.

=head1 System Setting

=head2 Standard IO

SPVM has own C<stdin>, C<stdout>, and C<stderr>. These are set to the binary mode.

The say operator and the print operator output to this SPVM's C<stdout>.

The warn operator outputs to this SPVM's C<stderr>.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

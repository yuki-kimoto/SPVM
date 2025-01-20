package SPVM::CommandInfo;

1;

=head1 Name

SPVM::CommandInfo - Command Line Information

=head1 Usage

  use CommandInfo;

=head1 Description

C<CommandInfo> in L<SPVM> has methods to get command line information such as a program name and arguments.

=head1 Class Variables

=head2 PROGRAM_NAME

C<our $PROGRAM_NAME : ro string;>

A program name when the program starts.

=head2 ARGV

C<our $ARGV : ro string[];>

Comand line arguments passed when the program starts.

=head2 BASETIME

C<our $BASETIME : ro long;>

The time when the program starts. This is the same as Perl C<$^T>.

=head2 WARNING

C<our $WARNING : ro byte;>

A warning flag.

=head1 Class Methods

=head2 BASE_TIME

B<Deprecated>

C<method BASE_TIME : long ();>

Returns the value of L</"BASETIME"> field.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

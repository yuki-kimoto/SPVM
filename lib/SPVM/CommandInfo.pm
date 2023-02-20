package SPVM::CommandInfo;

1;

=head1 Name

SPVM::CommandInfo - Command Line Information

=head1 Usage

  use CommandInfo;

=head1 Description

C<CommandInfo> is a class that has command line information such as the program name and the arguments.

C<CommandInfo> is a L<SPVM> class.

=head1 Class Variables

=head2 PROGRAM_NAME

  our $PROGRAM_NAME : ro string;

Gets the program name. This is the same as Perl C<$0>.

=head2 ARGV

  our $ARGV : ro string[];

Gets the comand line arguments. This is the same as Perl C<@ARGV>.

=head2 BASE_TIME

  our $BASE_TIME : ro long;

Gets the time when the program starts. This is the same as Perl C<$^T>.

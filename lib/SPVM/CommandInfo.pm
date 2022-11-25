package SPVM::CommandInfo;

1;

=head1 Name

SPVM::CommandInfo - Command Line Information

=head1 Usage

  use CommandInfo;

=head1 Description

C<CommandInfo> is a class that has command line information such as the program name and the arguments.

C<CommandInfo> is a L<SPVM> class.

=head1 Class Variable Methods

=head2 PROGRAM_NAME

  static method PROGRAM_NAME : string ();

Get the program name. This is same as Perl C<$0>.

=head2 ARGV

  static method ARGV : string[] ();

Get the comand line arguments. This is same as Perl C<@ARGV>.

package SPVM::Native::API;



1;

=head1 Name

SPVM::Native::API - Native APIs

=head1 Description

The Native::API class in L<SPVM> has methods to call native APIs.

=head1 Usage

  use Native::API;

=head1 Fields

=head2 env

C<has env : L<Native::Env|SPVM::Native::Env>;>

=head2 stack

C<has stack : L<Native::Stack|SPVM::Native::Stack>;>

=head1 Class Methods

C<static method new : Native::API ($env : Native::Env, $stack : Native::Stack);>

=head1 Instance Methods

=head2 set_command_info_program_name

C<method set_command_info_program_name : void ($program_name : string);>

Copies the program name $program_name and sets the L<program_name|CommandInfo/"program_name"> class variable in C<CommandInfo> in this instance class to it.

=head2 set_command_info_argv

C<method set_command_info_argv : void ($argv : string[]);>

Copies the command line arguments $argv and sets the L<argv|CommandInfo/"argv"> class variable in C<CommandInfo> class in this instance to it.

=head2 set_command_info_base_time

C<method set_command_info_base_time : void ($base_time : long);>

Sets the L<base_time|CommandInfo/"base_time"> class variable in C<CommandInfo> class in this instance to the base time $base_time.

=head2 call_init_methods

C<method call_init_methods : void ();>

Calls all L<INIT blocks|SPVM::Document::Language::Class/"INIT Block"> in this instance.

=head2 destroy_class_vars

C<method destroy_class_vars : void ();>

Destroys all class variables in this instance.

=head2 get_exception

C<method get_exception : string ();>

Gets the excetpion.

=head2 set_exception

C<method set_exception : void ($exception : string);>

Sets an excetpion.

=head1 Copyright & License

Copyright (c) 2024 Yuki Kimoto

MIT License


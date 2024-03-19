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

=head2 set_command_info

C<method set_command_info : void ($program_name : string, $argv : string[]);>

Sets command line information.

=head2 call_init_methods

C<method call_init_methods : void ();>

Calls all L<INIT blocks|SPVM::Document::Language/"INIT Block">.

=head2 get_exception

C<method get_exception : string ();>

Gets the excetpion.

=head2 set_exception

C<method set_exception : void ($exception : string);>

Sets an excetpion.

=head1 Copyright & License

Copyright (c) 2024 Yuki Kimoto

MIT License


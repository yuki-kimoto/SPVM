package SPVM::Env;



1;

=head1 Name

SPVM::Env - Execution Environment

=head1 Description

C<SPVM::Env> is the C<Env> class in the L<SPVM> language. 

The instance is an execution environemnt. It has the Native APIs and the data of class variables.

An instance of the C<Env> class is build by the L<build_env|SPVM::Runtime/"build_env"> method in the L<Runtime|SPVM::Runtime> class.

A call stack is build by the L<build_stack|/"build_stack"> method in this class.

=head1 Usage

  use Env;
  
  my $env = $runtime->build_env;
  
  my $stack = $env->build_stack;

=head1 Pointer

The C<Env> class is a L<pointer class|SPVM::Document::Language/"Pointer Class">.

Its insntace has a pointer to an object of the L<SPVM_ENV|SPVM::Document::NativeAPI/"Execution Environment"> type.

=head1 Fields

=head2 runtime

  has runtime : ro Runtime;

A runtime. The field type is the L<Runtime|SPVM::Runtime> class.

=head1 Instance Methods

=head2 set_command_info

  method set_command_info : void ($program_name : string, $argv : string[]);

Sets command line information.

=head2 call_init_blocks

  method call_init_blocks : void ();

Calls all L<INIT blocks|SPVM::Document::Language/"INIT Block">.

=head2 build_stack

  method build_stack : Stack ();

Builds a call stack and returns it.

The return type is the L<Stack|SPVM::Stack> class.

=head2 DESTROY

  method DESTROY : void ();

The destructor.

=head1 See Also

=head2 Runtime

The L<build_runtime|SPVM::Runtime/"build_runtime"> method in the L<Runtime|SPVM::Runtime> class builds an executable environement.

=head2 Stack

The instance of the L<Stack|SPVM::Stack> class is build by the L</"build_stack"> method in this class.

=head1 Copyright & License

Copyright 2023-2023 Yuki Kimoto, all rights reserved.

This program is free software; you can redistribute it and/or modify it
under the same terms as Perl itself.

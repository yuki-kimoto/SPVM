package SPVM::Env;



1;

=head1 Name

SPVM::Env - Execution Environment

=head1 Description

C<SPVM::Env> is the C<Env> class in the L<SPVM> language. 

The instance is an execution environemnt. It has the Native APIs and the data of class variables.

An instance of the C<Env> class is build by the L<get_env|SPVM::Runtime/"get_env"> method in the L<Runtime|SPVM::Runtime> class.

A call stack is build by the L<new_stack|/"new_stack"> method in this class.

=head1 Usage

  use Env;
  
  my $env = $runtime->get_env;
  
  my $stack = $env->new_stack;

=head1 Pointer

The C<Env> class is a L<pointer class|SPVM::Document::Language/"Pointer Class">.

Its insntace has a pointer to an object of the L<SPVM_ENV|SPVM::Document::NativeAPI/"Execution Environment"> type.

=head1 Fields

=head2 runtime

  has runtime : ro Runtime;

A runtime. The field type is the L<Runtime|SPVM::Runtime> class.

=head1 Class Methods

  native static method new : Env ($runtime = undef : Runtime);

Creates a new L<Env|SPVM::Env> ojbect, and returns it.

=head1 Instance Methods

=head2 set_command_info

  method set_command_info : void ($program_name : string, $argv : string[]);

Sets command line information.

=head2 call_init_methods

  method call_init_methods : void ();

Calls all L<INIT blocks|SPVM::Document::Language/"INIT Block">.

=head2 new_stack

  method new_stack : Stack ();

Builds a call stack and returns it.

The return type is the L<Stack|SPVM::Stack> class.

=head2 get_exception

  method get_exception : string ();

Gets the excetpion.

=head2 set_exception

  method set_exception : void ($exception : string);

Sets an excetpion.

=head2 DESTROY

  method DESTROY : void ();

The destructor.

=head1 See Also

=head2 Runtime

The L<get_runtime|SPVM::Runtime/"get_runtime"> method in the L<Runtime|SPVM::Runtime> class builds an executable environement.

=head2 Stack

The instance of the L<Stack|SPVM::Stack> class is build by the L</"new_stack"> method in this class.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

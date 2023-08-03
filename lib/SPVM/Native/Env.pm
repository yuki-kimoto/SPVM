package SPVM::Native::Env;



1;

=head1 Name

SPVM::Native::Env - Execution Native::Environment

=head1 Description

C<SPVM::Native::Env> is the C<Native::Env> class in the L<SPVM> language. 

The instance is an execution environemnt. It has the Native APIs and the data of class variables.

An instance of the C<Native::Env> class is build by the L<get_env|SPVM::Native::Runtime/"get_env"> method in the L<Native::Runtime|SPVM::Native::Runtime> class.

A call stack is build by the L<new_stack|/"new_stack"> method in this class.

=head1 Usage

  use Native::Env;
  
  my $env = $runtime->get_env;
  
  my $stack = $env->new_stack;

=head1 Pointer

The C<Native::Env> class is a L<pointer class|SPVM::Document::Language/"Pointer Class">.

Its insntace has a pointer to an object of the L<SPVM_ENV|SPVM::Document::NativeAPI/"Execution Native::Environment"> type.

=head1 Fields

=head2 compiler

  has compiler : ro Native::Compiler;

A compiler. The field type is the L<Native::Compiler|SPVM::Native::Compiler> class.

=head1 Class Methods

  static method new : Native::Env ($compiler : Native::Compiler = undef);

Creates a new L<Native::Env|SPVM::Native::Env> ojbect, and returns it.

=head1 Instance Methods

=head2 set_command_info

  method set_command_info : void ($program_name : string, $argv : string[]);

Sets command line information.

=head2 call_init_methods

  method call_init_methods : void ();

Calls all L<INIT blocks|SPVM::Document::Language/"INIT Block">.

=head2 new_stack

  method new_stack : Native::Stack ();

Builds a call stack and returns it.

The return type is the L<Native::Stack|SPVM::Native::Stack> class.

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

=head2 Native::Runtime

The L<get_runtime|SPVM::Native::Runtime/"get_runtime"> method in the L<Native::Runtime|SPVM::Native::Runtime> class builds an executable environement.

=head2 Native::Stack

The instance of the L<Native::Stack|SPVM::Native::Stack> class is build by the L</"new_stack"> method in this class.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

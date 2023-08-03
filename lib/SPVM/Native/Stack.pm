package SPVM::Native::Stack;



1;

=head1 Name

SPVM::Native::Stack - Call Native::Stack

=head1 Description

C<SPVM::Native::Stack> is the C<Native::Stack> class in the L<SPVM> language. 

The instance is a call stack. It has information of the call stack.

An instance of the C<Native::Stack> class is build by the L<new_stack|SPVM::Native::Env/"new_stack"> method in the L<Native::Env|SPVM::Native::Env> class.

=head1 Usage

  use Native::Stack;
  
  my $stack = $env->new_stack;

=head1 Pointer

The C<Native::Stack> class is a L<pointer class|SPVM::Document::Language/"Pointer Class">.

Its insntace has a pointer to an object of the L<SPVM_VALUE|SPVM::Document::NativeAPI/"Call Native::Stack"> type.

=head1 Fields

=head2 env

  has env : ro Native::Env;

An executable environemnt. The field type is the L<Native::Env|SPVM::Native::Env> class.

=head1 Instance Methods

=head2 DESTROY

  method DESTROY : void ();

The destructor.

=head1 See Also

=head2 Native::Env

The L<new_stack|SPVM::Native::Env/"new_stack"> method in the L<Native::Env|SPVM::Native::Env> class builds a call stack.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

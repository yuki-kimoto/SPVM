package SPVM::Native::Env;



1;

=head1 Name

SPVM::Native::Env - Runtime Environment

=head1 Description

The Native::Env class in L<SPVM> represents an L<runtime environment|SPVM::Document::NativeClass/"Runtime Environment">.

=head1 Usage

  use Native::Env;
  
  my $env = $runtime->new_env;
  
  my $stack = $env->new_stack;

=head1 Details

This class is a pointer class.

Its insntace has the pointer to an object of the L<SPVM_ENV|SPVM::Document::NativeClass/"Runtime Environment"> type.

=head1 Fields

C<has runtime : ro Native::Runtime;>

The runtime for this runtime environment.

=head1 Instance Methods

=head2 DESTROY

C<method DESTROY : void ();>

The destructor.

=head2 new_stack

C<method new_stack : L<Native::Stack|SPVM::Native::Stack> ();>

Builds a call stack and returns it.

The return type is the L<Native::Stack|SPVM::Native::Stack> class.

=head1 See Also

=head2 Native::Runtime

The L<get_runtime|SPVM::Native::Runtime/"get_runtime"> method in the L<Native::Runtime|SPVM::Native::Runtime> class builds an executable environement.

=head2 Native::Stack

The instance of the L<Native::Stack|SPVM::Native::Stack> class is build by the L</"new_stack"> method in this class.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

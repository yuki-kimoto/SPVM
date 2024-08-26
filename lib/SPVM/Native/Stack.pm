package SPVM::Native::Stack;



1;

=head1 Name

SPVM::Native::Stack - Call Native::Stack

=head1 Description

C<SPVM::Native::Stack> is C<Native::Stack> class in L<SPVM> language. 

The instance is a call stack. It has information of the call stack.

An instance of C<Native::Stack> class is build by L<Native::Env#new_stack|SPVM::Native::Env/"new_stack">.

=head1 Usage

  use Native::Stack;
  
  my $stack = $env->new_stack;

=head1 Pointer

The C<Native::Stack> class is a L<pointer class|SPVM::Document::Language/"Pointer Class">.

Its insntace has a pointer to an object of L<SPVM_VALUE|SPVM::Document::NativeAPI/"Call Native::Stack"> type.

=head1 Fields

=head2 env

  has env : ro Native::Env;

An executable environemnt. The field type is L<Native::Env|SPVM::Native::Env> class.

=head1 Instance Methods

=head2 DESTROY

C<method DESTROY : void ();>

The destructor.

=head1 See Also

=over 2

=item * L<Native::Env|SPVM::Native::Env>

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

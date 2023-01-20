package SPVM::Stack;



1;

=head1 Name

SPVM::Stack - Call Stack

=head1 Description

C<SPVM::Stack> is the C<Stack> class in the L<SPVM> language. 

The instance is a call stack. It has information of the call stack.

An instance of the C<Stack> class is build by the L<build_stack|SPVM::Env/"build_stack"> method in the L<Env|SPVM::Env> class.

=head1 Usage

  use Stack;
  
  my $stack = $env->build_stack;

=head1 Pointer

The C<Stack> class is a L<pointer class|SPVM::Document::Language/"Pointer Class">.

Its insntace has a pointer to an object of the L<SPVM_VALUE|SPVM::Document::NativeAPI/"Call Stack"> type.

=head1 Fields

=head2 env

  has env : ro Env;

An executable environemnt. The field type is the L<Env|SPVM::Env> class.

=head1 Instance Methods

=head2 DESTROY

  method DESTROY : void ();

The destructor.

=head1 See Also

=head2 Env

The L<build_stack|SPVM::Env/"build_stack"> method in the L<Env|SPVM::Env> class builds a call stack.

=head1 Copyright & License

Copyright 2023-2023 Yuki Kimoto, all rights reserved.

This program is free software; you can redistribute it and/or modify it
under the same terms as Perl itself.

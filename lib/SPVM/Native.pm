package SPVM::Native;



1;

=head1 Name

SPVM::Native - Getting the current native environment, stack, runtime, compiler.

=head1 Description

The Native class of L<SPVM> has methods to get the current native environment, stack, runtime, compiler.

=head1 Usage

  use Native;

=head1 Class Methods

=head2 get_current_stack

C<static method get_current_stack : L<Native::Stack|SPVM::Native::Stack> ();>

Returns the current execution stack.

=head2 get_current_env

C<static get_current_env : L<Native::Env|SPVM::Native::Env> ();>

Returns the current execution environemnt.

=head2 get_current_runtime

C<static method get_current_runtime : L<Native::Runtime|SPVM::Native::Runtime> ();>

Returns the current runtime.

=head2 get_current_compiler

C<static method get_current_compiler : L<Native::Compiler|SPVM::Native::Compiler> ();>

Returns the current compiler.

=head2 check_bootstrap_method

C<static method check_bootstrap_method : void ($basic_type_name : string);>

Check the bootstrap method in the basic type $basic_type_name.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License


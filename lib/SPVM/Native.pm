package SPVM::Native;



1;

=head1 Name

SPVM::Native - Native Class Utilities

=head1 Description

The Native class of L<SPVM> has methods for native class utilities.

=head1 Usage

  use Native;

=head1 Class Methods

=head2 get_current_env

  static get_current_env : Native::Env ();

Gets the current execution environemnt. This is a L<Native::Env|SPVM::Native::Env> object.

=head2 get_current_stack

  static get_current_stack : Native::Stack ();

Gets the current execution stack. This is a L<Native::Stack|SPVM::Native::Stack> object.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License


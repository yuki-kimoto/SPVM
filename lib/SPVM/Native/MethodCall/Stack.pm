package SPVM::Native::MethodCall::Stack;



1;

=head1 Name

SPVM::Native::MethodCall::Stack - Method Call on Stack

=head1 Description

The Native::MethodCall::Stack class of L<SPVM> has methods to call methods on a stack.

=head1 Usage

  use Native::MethodCall::Stack;

=head1 Class Methods

=head2 call_callback

  static method call_callback : void ($stack : Native::Stack, $callback : Native::MethodCall::Callback, $error_id : int*);

Calls a callback with a stack.

The stack is a L<Native::Stack|SPVM::Native::Stack> object.

The callback is a L<Native::MethodCall::Callback|SPVM::Native::MethodCall::Callback> object.

If the callback throw exception, the error id is set to $error_id. Otherwise 0 is set to $error_id.

=head2 get_exception

  static method get_exception : string ($stack : Native::Stack);

Gets an excetpion that is set to a stack.

The stack is a L<Native::Stack|SPVM::Native::Stack> object.

=head2 set_exception

  static method set_exception : void ($stack : Native::Stack, $exception : string);

Sets an excetpion that is set to a stack.

The stack is a L<Native::Stack|SPVM::Native::Stack> object.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License


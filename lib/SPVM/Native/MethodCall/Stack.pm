package SPVM::Native::MethodCall::Stack;



1;

=head1 Name

SPVM::Native::MethodCall::Stack - Method Call on Stack

=head1 Description

The Native::MethodCall::Stack class of L<SPVM> has methods to call methods on a stack.

=head1 Usage

  use Native::MethodCall::Stack;

=head1 Class Methods

  static method call_callback : void ($stack : Native::Stack, $error_id : int*, $callback : Native::MethodCall::Callback);

Calls a callback with a stack.

The stack is a L<Native::Stack|SPVM::Native::Stack> object.

The callback is a L<Native::MethodCall::Callback|SPVM::Native::MethodCall::Callback> object.

If the callback throw exception, the error id is set to $error_id. Otherwise 0 is set to $error_id.

=head1 Instance Methods

  static method get_exception : void ($stack : Native::Stack);

Gets an excetpion that is set to a stack.

The stack is a L<Native::Stack|SPVM::Native::Stack> object.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License


package SPVM::Native::MethodCall::EnvStack;



1;

=head1 Name

SPVM::Native::MethodCall::EnvStack - Method Call on Environment/Stack

=head1 Description

The Native::MethodCall::EnvStack class of L<SPVM> has methods to call methods on an execution environment and an execution stack.

=head1 Usage

  use Native::MethodCall::EnvStack;

=head1 Class Methods

=head2 call_class_method

  static method call_class_method : void ($env : Native::Env, $stack : Native::Stack, $basic_type_name : string, $method_name : string, $error_id : int*);
  
Calls a class method with an execution environment and an execution stack.

The environment is a L<Native::Env|SPVM::Native::Env> object.

The stack is a L<Native::Stack|SPVM::Native::Stack> object.

=head2 get_exception

  static method get_exception : void ($env : Native::Env, $stack : Native::Stack);

Copies an excetpion that is set to a stack on an environment, and returns it.

The environment is a L<Native::Env|SPVM::Native::Env> object.

The stack is a L<Native::Stack|SPVM::Native::Stack> object.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License


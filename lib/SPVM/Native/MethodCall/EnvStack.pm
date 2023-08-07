package SPVM::Native::MethodCall::EnvStack;



1;

=head1 Name

SPVM::Native::MethodCall::EnvStack - Method Call on Environment/Stack

=head1 Description

The Native::MethodCall::EnvStack class of L<SPVM> has methods to call methods on an execution environment and an execution stack.

=head1 Usage

  use Native::MethodCall::EnvStack;

=head1 Class Methods

  static method call_class_method : Native::MethodCall::EnvStack ($env : Native::Env, $stack : Native::Stack, $basic_type_name : string, $method_name : string);
  
Calls a class method with an execution environment and an execution stack.

The execution environment is a L<Native::Env|SPVM::Native::Env> object.

The execution stack is a L<Native::Stack|SPVM::Native::Stack> object.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License


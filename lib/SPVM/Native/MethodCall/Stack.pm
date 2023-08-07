package SPVM::Native::MethodCall::Stack;



1;

=head1 Name

SPVM::Native::MethodCall::Stack - Method Call on Stack

=head1 Description

The Native::MethodCall::Stack class of L<SPVM> has methods to call methods on a stack.

=head1 Usage

  use Native::MethodCall::Stack;

=head1 Class Methods

  static method new_class_method : Native::MethodCall::Stack ($basic_type_name : string, $method_name : string);

Create a class method call and returns it. It is a L<Native::MethodCall>.

Exceptions:

The length of the arguments of the \"%s\" method in the \"%s\" class must be 0. Otherwise an exception is thrown.

The return type of the \"%s\" method in the \"%s\" must be the void type. Otherwise an exception is thrown.

=head1 Instance Methods

  method call : void ($stack : Native::Stack);

Calls a method with a stack. The stack is a L<Native::Stack|SPVM::Native::Stack> object.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License


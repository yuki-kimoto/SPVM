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
  
=head1 Instance Methods

  method call : void ($stack : Native::Stack);
  
=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License


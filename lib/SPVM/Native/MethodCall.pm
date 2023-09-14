package SPVM::Native::MethodCall;



1;

=head1 Name

SPVM::Native::MethodCall - Method Call

=head1 Description

The Native::MethodCall class of L<SPVM> has methods to call methods.

=head1 Usage

  use Native::MethodCall;
  
  my $class_method_call = Native::MethodCall->new_class_method("Point", "new");
  
  my $point = (Point)$class_method_call->call([(object)1, 2]);
  
  say $point->x;
  
  say $point->y;

=head1 Class Methods

=head2 new_class_method

C<static method new_class_method : L<Native::MethodCall|SPVM::Native::MethodCall> ($basic_type_name : string, $method_name : string);>

Create a class method call and returns it. It is a L<Native::MethodCall>.

=head2 call_callback

C<static method call_callback : void ($callback : L<Native::MethodCall::Callback|SPVM::Native::MethodCall::Callback>, $error_id : int*, $stack = undef : L<Native::Stack|SPVM::Native::Stack>);>

Calls a callback with a stack. If $stack is not defined, the current stack is used.

The stack is a L<Native::Stack|SPVM::Native::Stack> object.

The callback is a L<Native::MethodCall::Callback|SPVM::Native::MethodCall::Callback> object.

If the callback throw exception, the error id is set to $error_id. Otherwise 0 is set to $error_id.

=head2 call_class_method

C<static method call_class_method : void ($basic_type_name : string, $method_name : string, $error_id : int*, $stack : L<Native::Stack|SPVM::Native::Stack> = undef, $env : L<Native::Env|SPVM::Native::Env> = undef);>
  
Calls a class method with an environment and a stack without arguments. If the environment is not given, the current environment is used.

The stack is a L<Native::Stack|SPVM::Native::Stack> object.

The environment is a L<Native::Env|SPVM::Native::Env> object.

If $stack is not defined, the current stackt is used.

If $environment is not defined, the current environment is used.

=head2 get_exception

C<static method get_exception : string ($stack : L<Native::Stack|SPVM::Native::Stack> = undef, $env : L<Native::Env|SPVM::Native::Env> = undef);>

Copies an excetpion on a stack, and returns it.

The stack is a L<Native::Stack|SPVM::Native::Stack> object.

The environment is a L<Native::Env|SPVM::Native::Env> object.

If $stack is not defined, the current stackt is used.

If $environment is not defined, the current environment is used.

=head2 set_exception

C<static method set_exception : void ($exception : string, $stack : L<Native::Stack|SPVM::Native::Stack> = undef, $env : L<Native::Env|SPVM::Native::Env> = undef);>

Copies an excetpion on a stack using an enviroment, and sets it to the stack.

The stack is a L<Native::Stack|SPVM::Native::Stack> object.

The environment is a L<Native::Env|SPVM::Native::Env> object.

If $stack is not defined, the current stackt is used.

If $environment is not defined, the current environment is used.

=head1 Instance Methods

=head2 call

C<method call : object ($args : object[]);>

Calls a method with arguments and returns the return value.

=head2 Arguments

Each argument must be an object type. The following conversion is perfromed.
  
  # Numeric types
  Byte -> byte
  Short -> short
  Int -> int
  Long -> long
  Float -> float
  Double -> double
  
  # Multi-Numeric types
  byte[] -> multi-numeric byte
  short[] -> multi-numeric short
  int[] -> multi-numeric int
  long[] -> multi-numeric long
  float[] -> multi-numeric float
  double[] -> multi-numeric double
  
  # Numeric reference types
  byte[] -> byte*
  short[] -> short*
  int[] -> int*
  long[] -> long*
  float[] -> float*
  double[] -> double*
  
  # Multi-Numeric reference types
  byte[] -> multi-numeric byte reference
  short[] -> multi-numeric short reference
  int[] -> multi-numeric int reference
  long[] -> multi-numeric long reference
  float[] -> multi-numeric float reference
  double[] -> multi-numeric double reference

If the type of an argument cannot be assigned, an exception is thrown.

=head3 Return Value

If the type of the return value is a numeric type, it is converted to a numeric object.

  byte -> Byte
  short -> Short
  int -> Int
  long -> Long
  float -> Float
  double -> Double


If the type of the return value is a multi-numeric type, it is converted to a numeric array.

  multi-numeric byte type -> byte[]
  multi-numeric short type -> short[]
  multi-numeric int type -> int[]
  multi-numeric long type -> long[]
  multi-numeric float type -> float[]
  multi-numeric double type -> double[]

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License


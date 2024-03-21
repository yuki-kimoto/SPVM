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

=head2 new_class_method_with_env_stack

C<static method new_class_method_with_env_stack : L<Native::MethodCall|SPVM::Native::MethodCall> ($env : L<Native::Env|SPVM::Native::Env>, $stack : L<Native::Stack|SPVM::Native::Stack>, $basic_type_name : string, $method_name : string);>
Creates a class method call given the runtime environment $env, the runtime stck $stack, the basic type name $basic_type_name and the method name $method_name and returns it.

If $env is not given, $env is set to the current runtime environment.

If $stack is not given, $stack is set to the current runtime environment.

=head2 new_instance_method_static_with_env_stack

C<static method new_instance_method_static_with_env_stack : L<Native::MethodCall|SPVM::Native::MethodCall> ($env : L<Native::Env|SPVM::Native::Env>, $stack : L<Native::Stack|SPVM::Native::Stack>, $basic_type_name : string, $method_name : string);>

Creates a instance method call given the runtime environment $env, the runtime stck $stack,  the basic type name $basic_type_name and the method name $method_name, and returns it.

If $env is not given, $env is set to the current runtime environment.

If $stack is not given, $stack is set to the current runtime environment.

=head2 new_instance_method_with_env_stack

C<static method new_instance_method_with_env_stack : L<Native::MethodCall|SPVM::Native::MethodCall> ($env : L<Native::Env|SPVM::Native::Env>, $stack : L<Native::Stack|SPVM::Native::Stack>, $instance : object, $method_name : string);>

Creates a instance method call given the runtime environment $env, the runtime stck $stack,  the instance $instance and the method name $method_name, and returns it.

If $env is not given, $env is set to the current runtime environment.

If $stack is not given, $stack is set to the current runtime environment.

=head2 new_class_method

C<static method new_class_method : L<Native::MethodCall|SPVM::Native::MethodCall> ($basic_type_name : string, $method_name : string);>

Calls the L</"new_class_method_with_env_stack"> method given $env to undef and $stack to undef, and returns its return value.

Creates a class method call given the basic type name $basic_type_name and the method name $method_name and returns it.

=head2 new_instance_method_static

C<static method new_instance_method_static : L<Native::MethodCall|SPVM::Native::MethodCall> ($basic_type_name : string, $method_name : string);>

Calls the L</"new_instance_method_static_with_env_stack"> method given $env to undef and $stack to undef, and returns its return value.

=head2 new_instance_method

C<static method new_instance_method : L<Native::MethodCall|SPVM::Native::MethodCall> ($instance : object, $method_name : string);>

Calls the L</"new_instance_method_with_env_stack"> method given $env to undef and $stack to undef, and returns its return value.

=head2 call_class_method

C<static method call_class_method : void ($basic_type_name : string, $method_name : string, $args : object[] = undef, $error_id_ref : int[] = undef);>

Calls a class method given the basic type name $basic_type_name, the method name $method_name, and the arguments $args.

=head2 call_instance_method_static

C<static method call_instance_method_static : object ($basic_type_name : string, $method_name : string, $args : object[] = undef, $error_id_ref : int[] = undef);>

Calls a instance method given the basic type name $basic_type_name, the method name $method_name, and the arguments $args.

=head2 call_instance_method

C<static method call_instance_method : object ($method_name : string, $args : object[] = undef, $error_id_ref : int[] = undef);>

Calls a instance method given the method name $method_name, and the arguments $args. The first argument in $args must be an instance.

=head1 Instance Methods

=head2 call

C<method call : object ($args : object[] = undef, $error_id_ref : int[] = undef);>

Calls a method with arguments and returns the return value.

=head2 get_exception

C<method get_exception : string ();>

Gets the excetpion on the runtime enviroment and runtime stack owned by this instance.

=head2 set_exception

C<method set_exception : void ($exception : string);>

Sets the excetpion on the runtime enviroment and runtime stack owned by this instance to the string $exception.

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


=head1 Name

SPVM::Document::NativeClass - Native Classes

=head1 Description

A native class is the class implemented by a native language such as the C language and C++.

=head1 Native Method Definition

A native method is defined by the L<native method attribute|SPVM::Document::Language::Class/"Method Attributes"> in a SPVM class file. It ends with a semicolon. A native method does not have its block. 

  # SPVM/MyClass.spvm
  class MyClass {
    native static method sum : int ($num1 : int, $num2 : int);
  }

=head1 Native Config File

A native config file is needed for a native class. The name of the config file is the same as the SPVM class name, but the extension C<.spvm> is replaced with C<.config>. 

  # The name of a native config file
  SPVM/MyClass.config

A native config file is writen by Perl. It must end with a L<Builder::Config|SPVM::Builder::Config> object.

A config file is executed by Perl's L<do|https://perldoc.perl.org/functions/do> function. The returned L<Builder::Config|SPVM::Builder::Config> object is used as the config of a native class.

Exceptions:

If the native config file does not exist, an exception is thrown.

A config file must end with a L<Builder::Config|SPVM::Builder::Config> object, otherwise an exception is thrown.

Examples:

GNU C99:

  my $config = SPVM::Builder::Config->new_gnu99(file => __FILE__);
  
  $config;

C++:

  my $config = SPVM::Builder::Config->new_cpp(file => __FILE__);
  
  $config;

See also L<Builder::Config|SPVM::Builder::Config/"Examples">.

=head1 Native Class

A native class is the class implemented by a native language such as the C language and C++.

The name of the native class file is the same as the SPVM class name, but the extension C<.spvm> is replaced with C<.> and the L<extension of the native class|/"Native Class File Extension">.

  SPVM/MyClass.c

=head2 Native Class File Extension

The file extension of a native class is defined by the L<ext|SPVM::Builder::Config/"ext"> field in a config file .

Examples:

  $config->ext('c');
  
  $config->ext('cpp');
  
  $config->ext('cc');
  
  $config->ext('cu');

Exceptions:

If the L<ext|SPVM::Builder::Config/"ext"> is defined, but its corresponding config file does not exist, an exception is thrown.

=head2 Native Function

A native function is the function defined in a native class.

Examples:

  // SPVM/MyClass.c
  
  #include "spvm_native.h"
  
  int32_t SPVM__MyClass__sum(SPVM_ENV* env, SPVM_VALUE* stack) {
    
    int32_t num1 = stack[0].ival;
    int32_t num2 = stakc[1].ival;
    
    int32_t total = num1 + num2;
    
    stack[0].ival = total;
    
    return 0;
  }

=head3 Native Function Name

A native function must have the name following the rules below.

=over 2

=item * 1. Starts with C<SPVM__>.

=item * 2. Followed by the SPVM class name, but C<::> is replaced with C<__>.

=item * 3. Followed by C<__>.

=item * 3. Followed by the name of the method.

=back

Exceptions:

If the name of a native function is invalid, an exception is thrown.

Examples:

For example, if the class is C<MyClass::Math> and the method name is C<sum_value>, the name of the native function is C<SPVM__MyClass__Math__sum_value>.
  
  # SPVM class
  class MyClass::Math {
    native method sum_value : void ();
  }
  
  // Native class
  SPVM__MyClass__Math__sum_value(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  }

=head2 Native API Header

  #include "spvm_native.h"

C<spvm_native.h> is the header file for L<SPVM Native API|SPVM::Document::NativeAPI>.

=head2 Native Function Arguments

A native function must has two arguments.

  int32_t SPVM__MyClass__sum(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  }

The first argument C<env> is the current L<runtime environment|Runtime Environment>. Its type is the C<SPVM_ENV*> type.

The second argument C<stack> is the current L<runtime stack|Runtime Stack>. Its type is the pointer to an array of L<SPVM_VALUE/"SPVM_VALUE type"> type.

The arguments given to this native function are stored in the stack.

See L</"Getting Argument"> to get the values of the arguments.

=head2 Native Function Return Value

A native function must return a value of the C<int32_t> type.

  int32_t SPVM__MyClass__sum(SPVM_ENV* env, SPVM_VALUE* stack) {
    
    # ...
    
    return 0;
  }
  
If an exception is thrown in this native function, a native function must return a basic type ID of an error class, otherwise return 0.

See L</"Exception"> for exception handling in a native class.

=head2 SPVM_VALUE type

C<SPVM_VALUE> type is an union type in the C language.

  typedef union spvm_value SPVM_VALUE;
  
  union spvm_value {
    int8_t bval;
    int16_t sval;
    int32_t ival;
    int64_t lval;
    float fval;
    double dval;
    void* oval;
    int8_t* bref;
    int16_t* sref;
    int32_t* iref;
    int64_t* lref;
    float* fref;
    double* dref;
  };

=head2 Getting Argument

Arguments given to a native function are stored in the L<runtime stack|Runtime Stack> I<stack>.

  int32_t SPVM__MyClass__sum(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  }

Consider the following method definition.

  method foo ($args0 : int, $args1 : Point, $arg2 : Complex_2d);

To get the value of $args0 of the int type, do the following using C<ival> field of the L<SPVM_VALUE/"SPVM_VALUE type"> type. 

  int32_t args0 = stack[0].ival;

To get the value of $args1 of the L<Point|SPVM::Point> type, do the following, using C<oval> field of the L<SPVM_VALUE/"SPVM_VALUE type"> type. 

  int64_t args1 = stack[1].oval;

To get the values of $args2 of the L<Complex_2d|SPVM::Complex_2d> multi-numeric type, do the following.

Note that the values of the multi-numeric type are stored in the values of the length of the fields of the multi-numeric type.

  double args2_re = stack[2].dval;
  double args2_im = stack[3].dval;

=head3 Getting byte Type Argument

Use the C<bval> field of the L<SPVM_VALUE/"SPVM_VALUE type"> type to get the value of the SPVM C<byte> type from an argument, 

  int8_t args0 = stack[0].bval;

=head3 Getting short Type Argument

Use the C<sval> field to get the short argument of SPVM, 

  int16_t args0 = stack[0].sval;

=head3 Getting int Type Argument

Use the C<ival> field of the L<SPVM_VALUE/"SPVM_VALUE type"> type to get the value of the SPVM C<int> type from an argument, 

  int32_t args0 = stack[0].ival;

=head3 Getting long Type Argument

Use the C<lval> field of the L<SPVM_VALUE/"SPVM_VALUE type"> type to get the value of the SPVM C<long> type from an argument, 

  int64_t args0 = stack[0].lval;

=head3 Getting float Type Argument

Use the C<fval> field of the L<SPVM_VALUE/"SPVM_VALUE type"> type to get the value of the SPVM C<float> type from an argument.

  float args0 = stack[0].fval;

=head3 Getting double Type Argument

Use the C<dval> field of the L<SPVM_VALUE/"SPVM_VALUE type"> type to get the value of the SPVM C<double> type from an argument, 

  double args0 = stack[0].dval;

=head3 Getting Object Type Argument

Use the C<oval> field of the L<SPVM_VALUE/"SPVM_VALUE type"> type to get the value of an SPVM object type from an argument, 

  void* args0 = stack[0].oval;

=head3 Getting byte Reference Type Argument

Use the C<bref> field of the L<SPVM_VALUE/"SPVM_VALUE type"> type to get the value of a SPVM C<byte> reference type from an argument, 

  int8_t* args0 = stack[0].bref;

=head3 Getting short Reference Type Argument

Use the C<sref> field of the L<SPVM_VALUE/"SPVM_VALUE type"> type to get the value of a SPVM C<short> reference type from an argument, 

  int16_t* args0 = stack[0].sref;

=head3 Getting int Reference Type Argument

Use the C<iref> field of the L<SPVM_VALUE/"SPVM_VALUE type"> type to get the value of a SPVM C<int> reference type from an argument, 

  int32_t* args0 = stack[0].iref;

=head3 Getting long Reference Type Argument

Use the C<lref> field of the L<SPVM_VALUE/"SPVM_VALUE type"> type to get the value of a SPVM C<long> reference type from an argument, 

  int64_t* args0 = stack[0].lref;

=head3 Getting float Reference Type Argument

Use the C<fref> field of the L<SPVM_VALUE/"SPVM_VALUE type"> type to get the value of a SPVM C<float> reference type from an argument, 

  float* args0 = stack[0].fref;

=head3 Getting double Reference Type Argument

To get the value of an SPVM C<double> reference type from an argument, use C<dref> field of the L<SPVM_VALUE/"SPVM_VALUE type"> type.

  double* args0 = stack[0].dref;

=head3 Getting Multi-Numeric Type Arguments

The values of an SPVM multi-numeric type from an argument are assigned multiple fields of the L<SPVM_VALUE/"SPVM_VALUE type"> type, which length is the same as the length of the fields of the SPVM multi-numeric type.

For example, if the argument type is the L<Complex_2d|SPVM::Complex_2d> type, these values are assinged to multiple fields of the L<SPVM_VALUE/"SPVM_VALUE type"> type.

  double args0_re = stack[0].dval;
  double args0_im = stack[1].dval;

=head2 Return Value

A return value of a SPVM method can be set to the first argument of the L<runtime stack|Runtime Stack>.
  
  int32_t return_value = 5;
  
  stack[0].ival = return_value;

=head3 Setting Return Value of byte Type

Use the C<bval> field of the L<SPVM_VALUE|/"SPVM_VALUE Type"> type to set a return value of the SPVM C<byte> type.

  stack[0].bval = return_value;

=head3 Setting Return Value of short Type

Use the C<sval> field of the L<SPVM_VALUE|/"SPVM_VALUE Type"> type to set a return value of the SPVM C<short> type.

  stack[0].sval = return_value;

=head3 Setting Return Value of int Type

Use the C<ival> field of the L<SPVM_VALUE|/"SPVM_VALUE Type"> type to set a return value of the SPVM C<int> type.

  stack[0].ival = return_value;

=head3 Setting Return Value of long Type

Use the C<lval> field of the L<SPVM_VALUE|/"SPVM_VALUE Type"> type to set a return value of the SPVM C<long> type.

  stack[0].lval = return_value;

=head3 Setting Return Value of float Type

Use the C<fval> field of the L<SPVM_VALUE|/"SPVM_VALUE Type"> type to set a return value of the SPVM C<float> type.

  stack[0].fval = return_value;

=head3 Setting Return Value of double Type

Use the C<dval> field of the L<SPVM_VALUE|/"SPVM_VALUE Type"> type to set a return value of the SPVM C<double> type.

  stack[0].dval = return_value;

=head3 Setting Return Value of Object Type

Use the C<oval> field of the L<SPVM_VALUE|/"SPVM_VALUE Type"> type to set a return value which type of SPVM is object.

  stack[0].oval = return_value;

=head3 Setting Return Value of Multi-Numeric Type

Return value of the multi-numeric type are needed to be set to multiple fields of the L<SPVM_VALUE|/"SPVM_VALUE Type"> type, which length is the same as the fields of the multi-numeric type.

There is an example in the case that the return type is the L<Complex_2d|SPVM::Complex_2d>.

  double return_value_x;
  double return_value_y;
  stack[0].dval = return_value_x;
  stack[1].dval = return_value_y;

=head2 Native APIs

L<Native APIs|SPVM::Document::NativeAPI> are the APIs written by the C language for SPVM operations. Native APIs can be called in native classes. 

=head2 Examples of Native APIs:

Create a Point object.
  
  int32_t error_id = 0;
  void* obj_point = env->new_object_by_name(env, stack, "Point", &error_id, __func__, __FILE__, __LINE__);
  if (error_id) { return error_id; }

Call a class method.

  int32_t error_id = 0;
  int32_t total;
  {
    int32_t args_width = 2;
    stack[0].ival = 5;
    stack[1].ival = 10;
    env->call_class_method_by_name(env, stack, "MyClass", "sum", args_width, &error_id, __func__, __FILE__, __LINE__);
    if (error_id) { return error_id; }
    
    total = stack[0].ival;
  }

Get the characters of a string.

  const char* chars = env->get_chars(env, stack, obj_string);

Get the elements of an array of the int type.

  int32_t* values = env->get_elems_int(env, stack, obj_array);

=head2 Exception

In the native method, it is the return value that indicates whether an exception has occurred.

  return 0;

  return 1;

If no exception occurs, "0" is returned. This is defined as "0".

If an exception is thrown, "1" is returned. It is defined as a value other than "0".

If you want to set the exception message yourself, you can create an exception message with "new_string_nolen" and set it with "set_exception".

  env->set_exception(env, stack, env->new_string_nolen(env, stack, "Exception occur");
  return 1;

If no exception message is set, a default exception message will be set.

Usually, L<die|"die"">  is defined to make it easier to use, so it is better to use this.

  return env->die("Error. Values must be %d and %d", 3, 5, __func__, "MyClass.c", __LINE__);

L<die|"die""> can be used in the same way as the C language sprintf function. Be sure to include this file name in the second from the end, and the line number in the last argument. If the message exceeds 255 bytes, the excess is truncated.

The exception is stored in env.

=head2 Pointer Class

There is a type called pointer type in SPVM, but I will explain how to use it.

The pointer type definition specifies the pointer attribute in the SPVM class definition. Pointer types cannot have field definitions. This example describes how to use the C standard "struct tm" as a pointer type.

  # SPVM/MyTimeInfo.spvm
  class MyTimeInfo : pointer {

    # Constructor
    native static method new : MyTimeInfo ();

    # Get second
    native method sec : int ();

    # Destructor
    native method DESTROY : ();
  }

It defines a new constructor, a method that takes seconds information called sec, and a destructor called DESTROY. These are Native Method.

Next is the definition on the C language side.

  # SPVM/MyTimeInfo.c

  int32_t SPVM__MyTimeInfo__new(SPVM_ENV* env, SPVM_VALUE* stack) {

    // Alloc strcut tm
    void* tm_ptr = env->new_memory_block(env, stack, sizeof (struct tm));

    // Create strcut tm instance
    void* tm_obj = env->new_pointer_object(env, stack, "MyTimeInfo", tm_ptr);

    stack[0].oval = tm_obj;

    return 0;
  }

  int32_t SPVM__MyTimeInfo__sec(SPVM_ENV* env, SPVM_VALUE* stack) {
    void* tm_obj = stack[0].oval;

    strcut tm* tm_ptr = (struct tm*) env->get_pointer(env, stack, tm_obj);

    stack[0].ival = tm_ptr-> tm_sec;

    return 0;
  }

  int32_t SPVM__MyTimeInfo__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {

    void* tm_obj = stack[0].oval;
    strcut tm* tm_ptr = (struct tm*) env->get_pointer(env, stack, tm_obj);

    env->free_memory_block(tm_ptr);

    return 0;
  }

In the constructor new, the memory of "struct tm" is first allocated by the new_memory_block function. This is a function that reserves one memory block in SPVM. Similar to malloc, this function increments the memory block count by one, making it easier to spot memory leaks.

  // Alloc strcut tm
  void* tm_ptr = env->new_memory_block(env, stack, sizeof (struct tm));

Next, use the new_pointer_object function to create a new pointer type object with MyTimeInfo associated with it in the allocated memory.

  // Create strcut tm instance
  void* tm_obj = env->new_pointer_object(env, stack, "MyTimeInfo", tm_ptr);

If you return this as a return value, the constructor is complete.

  stack[0].ival = tm_ptr-> tm_sec;
  
  return 0;

Next, let's get the value of tm_sec. sec method. The get_pointer function can be used to get a pointer to the memory allocated as a "struct tm" from a pointer type object.

  void* tm_obj = stack[0].oval;

  strcut tm* tm_ptr = (struct tm*) env->get_pointer(env, stack, tm_obj);

  stack[0].ival = tm_ptr-> tm_sec;

The last is the destructor. Be sure to define a destructor, as the allocated memory will not be released automatically.

  int32_t SPVM__MyTimeInfo__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {

    void* tm_obj = stack[0].oval;

    strcut tm* tm_ptr = (struct tm*) env->get_pointer(env, stack, tm_obj);

    env->free_memory_block(tm_ptr);

    return 0;
  }

Execute the free_memory_block function to free the memory. Be sure to free the memory allocated by new_memory_block with the free_memory_block function. Releases the memory and decrements the memory block count by one.

=head2 Scope

Native method are entirely enclosed in scope.

Objects added to the mortal stack will automatically have their reference count decremented by 1 when the native method ends. When the reference count reaches 0, it is released.

Use push_mortal to add objects to the mortal stack.

  env->push_mortal(env, stack, object);

Native APIs that normally create an object such as "new_object" will add the automatically created object to the mortal stack so you don't need to use this.

Use "enter_scope" to create a scope. The return value is the ID of that scope.

  int32_t mortal_stack_top = env->enter_scope(env, stack);

Use "leave_scope" to leave the scope. For the argument, it is necessary to specify the scope ID obtained in "enter_scope".

  env->leave_scope(env, stack, mortal_stack_top);

=head3 Mortal Stack

A mortal stack is created for a stack. A mortal stack is the stack to push local variables to destroy at the end of the scope.

=head2 Runtime Environment

The object of the C<SPVM_ENV*> type is an runtime environement.

  SPVM_ENV* env;

This object is passed as the first argument of a Native API.

  int32_t SPVM__MyClass__sum(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  }

=head2 Runtime Stack

A runtime stack is passed to the second argument of the definition of the native method. A runtime stack is used getting arguments and return the value.

  int32_t SPVM__MyClass__sum(SPVM_ENV* env, SPVM_VALUE* stack) {
    
  }

SPVM_VALUE is a union type of C language to store SPVM values. You can save integral value, floating point value, object value, and reference value to it.

=head2 Arguments Width

The width of the arguments is the length in units of the L<SPVM_VALUE|SPVM::Document::NativeClass/"Runtime Stack"> type.

=head1 Compilation and Link

A native class and native source files are compiled to object files and are linked and a shared library is generated.

The extension of a shared library is C<.so> in Linux/UNIX, C<.dylib> in Mac, C<.dll> in Windows.

A build directoy path must be set to the L<SPVM_BUILD_DIR|SPVM::Document::EnvironmentVariables/"SPVM_BUILD_DIR"> environment variable.

Normally, C<~/.spvm_build> is set to it.

  ~/.spvm_build

Object files and a shared library file are output to the build directory.

If the build directory does not exist, it is created.

Exceptions:

A string of non-zero length must be set to the L<SPVM_BUILD_DIR|SPVM::Document::EnvironmentVariables/"SPVM_BUILD_DIR"> environment variable, otherwise an exception is thrown.

=head1 Resource

A native class uses native headers and native source files writen by native langauges such as the C language and C++ using the L<use_resource|SPVM::Builder::Config/"use_resource"> method in SPVM::Builder::Config class.

  # MyClass.config
  $config->use_resource("Resource::Zlib");
  
  // MyClass.c
  #include "zlib.h"

For details, see L<SPVM::Document::Resource>.

=head1 Distribution

A distribution for a native class can be generated by the L<spvmdist> command.
  
  # C
  spvmdist --native c --user-name="Yuki Kimoto" --user-email="kimoto.yuki@gmail.com" MyNativeClass
  
  # C++
  spvmdist --native c++ --user-name="Yuki Kimoto" --user-email="kimoto.yuki@gmail.com" MyNativeClass

Only a native class file and a config file can be added to an existing distribution.

  # C
  spvmdist --only-lib-files --native c --user-name="Yuki Kimoto" --user-email="kimoto.yuki@gmail.com" MyNativeClass lib
  
  # C++
  spvmdist --only-lib-files --native c++ --user-name="Yuki Kimoto" --user-email="kimoto.yuki@gmail.com" MyNativeClass lib

=over 2

=item * L<spvmdist>

=back

=head1 See Also

=head2 Documents

=over 2

=item * L<SPVM::Document::Language::Class>

=back

=head2 Config

=over 2

=item * L<SPVM::Builder::Config>

=item * L<SPVM::Builder::Config::Exe>

=back

=head2 Native APIs

=over 2

=item * L<SPVM::Document::NativeAPI>

=item * L<SPVM::Document::NativeAPI::Method>

=item * L<SPVM::Document::NativeAPI::ClassVariable>

=item * L<SPVM::Document::NativeAPI::Allocator>

=item * L<SPVM::Document::NativeAPI::Compiler>

=item * L<SPVM::Document::NativeAPI::Internal>

=item * L<SPVM::Document::NativeAPI::Mutex>

=item * L<SPVM::Document::NativeAPI::Field>

=item * L<SPVM::Document::NativeAPI::BasicType>

=item * L<SPVM::Document::NativeAPI::Runtime>

=item * L<SPVM::Document::NativeAPI::Type>

=item * L<SPVM::Document::NativeAPI::StringBuffer>

=item * L<SPVM::Document::NativeAPI::ModuleFile>

=item * L<SPVM::Document::NativeAPI::ClassFile>

=item * L<SPVM::Document::NativeAPI::Argument>

=item * L<Examples using native methods|https://github.com/yuki-kimoto/SPVM/tree/master/examples/native>

=back

=head2 Resource

=over 2

=item * L<SPVM::Document::Resource>

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

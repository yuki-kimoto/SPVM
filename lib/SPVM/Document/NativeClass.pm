=head1 Name

SPVM::Document::NativeClass - Native Classes

=head1 Description

A native class is the class implemented by a native language such as the C language and C++.

=head1 Native Method Definition

A native method is defined by L<native method attribute|SPVM::Document::Language::Class/"Method Attributes"> in an SPVM class file. It ends with a semicolon. A native method does not have its block. 

  # SPVM/MyClass.spvm
  class MyClass {
    native static method sum : int ($num1 : int, $num2 : int);
  }

=head1 Native Config File

A native config file is needed for a native class. The name of the config file is the same as the SPVM class name, but the extension C<.spvm> is replaced with C<.config>. 

  # The name of a native config file
  SPVM/MyClass.config

A native config file is writen by Perl. It must end with a L<Builder::Config|SPVM::Builder::Config> object.

A config file is executed by Perl's L<do|https://perldoc.perl.org/functions/do> function. The returned L<Builder::Config|SPVM::Builder::Config> object is used as the config for a native class.

Exceptions:

If the native config file does not exist, an exception is thrown.

A config file must end with a L<Builder::Config|SPVM::Builder::Config> object. Otherwise, an exception is thrown.

Examples:

GNU C99:

  my $config = SPVM::Builder::Config->new_gnu99;
  
  $config;

C++:

  my $config = SPVM::Builder::Config->new_cpp;
  
  $config;

=head1 Native Class

A native class is the class implemented by a native language such as the C language and C++.

The name of the native class file is the same as the SPVM class name, but the extension C<.spvm> is replaced with C<.> and L<extension of the native class|/"Native Class File Extension">.

  SPVM/MyClass.c

=head2 Native Class File Extension

The file extension of a native class is defined by L<Builder::Config#ext|SPVM::Builder::Config/"ext"> field in a config file.

Examples:

  $config->ext('c');
  
  $config->ext('cpp');
  
  $config->ext('cc');
  
  $config->ext('cu');

Exceptions:

If L<ext|SPVM::Builder::Config/"ext"> is defined, but its corresponding config file does not exist, an exception is thrown.

=head2 Native Function

A native function is a function defined in a native class.

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

C<spvm_native.h> is the header file for L<SPVM Native APIs|SPVM::Document::NativeAPI>.

=head2 Native Function Arguments

A native function must have two arguments.

  int32_t SPVM__MyClass__sum(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  }

The first argument C<env> is the current L<runtime environment|/"Runtime Environment">. This is the pointer to a value of C<SPVM_ENV> type.

The second argument C<stack> is the current L<runtime stack|/"Runtime Stack">. This is is the pointer to the values of L<SPVM_VALUE|/"SPVM_VALUE Type"> type.

The arguments given to this native function have been stored in the runtime stack.

See L</"Getting Argument"> to get the values of the arguments.

=head2 Native Function Return Value

A native function must return a value of the C<int32_t> type.

  int32_t SPVM__MyClass__sum(SPVM_ENV* env, SPVM_VALUE* stack) {
    
    # ...
    
    return 0;
  }
  
If an exception is thrown in this native method, the native function must return a non-zero value. Otherwise, must return 0.

See L</"Exception"> for exception handling in native classes.

=head2 SPVM_VALUE Type

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

Arguments given to a native function have been stored in L<runtime stack|/"Runtime Stack"> I<stack>.

  int32_t SPVM__MyClass__sum(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  }

Consider the following method definition.

  method foo ($args0 : int, $args1 : Point, $arg2 : Complex_2d);

Do the following using the C<ival> field of L<SPVM_VALUE|/"SPVM_VALUE Type"> type to get the value of $args0 which type is int type.

  int32_t args0 = stack[0].ival;

Do the following using the C<oval> field of L<SPVM_VALUE|/"SPVM_VALUE Type"> type to get the value of $args1 which type is L<Point|SPVM::Point> type.

  int64_t args1 = stack[1].oval;

Do the following to get the values of $args2 which type is L<Complex_2d|SPVM::Complex_2d> multi-numeric type.

  double args2_re = stack[2].dval;
  double args2_im = stack[3].dval;

Note that the values of the multi-numeric type have been stored in the multiple values in the runtime stack. The length of the value in the runtime stack is the same as the length of the fields of the multi-numeric type.

=head3 Getting byte Type Argument

Use the C<bval> field of L<SPVM_VALUE|/"SPVM_VALUE Type"> type to get the value of the SPVM C<byte> type from an argument.

  int8_t args0 = stack[0].bval;

=head3 Getting short Type Argument

Use the C<sval> field of L<SPVM_VALUE|/"SPVM_VALUE Type"> type to get the value of the SPVM C<short> type from an argument.

  int16_t args0 = stack[0].sval;

=head3 Getting int Type Argument

Use the C<ival> field of L<SPVM_VALUE|/"SPVM_VALUE Type"> type to get the value of the SPVM C<int> type from an argument.

  int32_t args0 = stack[0].ival;

=head3 Getting long Type Argument

Use the C<lval> field of L<SPVM_VALUE|/"SPVM_VALUE Type"> type to get the value of the SPVM C<long> type from an argument.

  int64_t args0 = stack[0].lval;

=head3 Getting float Type Argument

Use the C<fval> field of L<SPVM_VALUE|/"SPVM_VALUE Type"> type to get the value of the SPVM C<float> type from an argument.

  float args0 = stack[0].fval;

=head3 Getting double Type Argument

Use the C<dval> field of L<SPVM_VALUE|/"SPVM_VALUE Type"> type to get the value of the SPVM C<double> type from an argument.

  double args0 = stack[0].dval;

=head3 Getting Object Type Argument

Use the C<oval> field of L<SPVM_VALUE|/"SPVM_VALUE Type"> type to get the value of an SPVM object type from an argument.

  void* args0 = stack[0].oval;

=head3 Getting byte Reference Type Argument

Use the C<bref> field of L<SPVM_VALUE|/"SPVM_VALUE Type"> type to get the value of an SPVM C<byte> reference type from an argument.

  int8_t* args0 = stack[0].bref;

=head3 Getting short Reference Type Argument

Use the C<sref> field of L<SPVM_VALUE|/"SPVM_VALUE Type"> type to get the value of an SPVM C<short> reference type from an argument.

  int16_t* args0 = stack[0].sref;

=head3 Getting int Reference Type Argument

Use the C<iref> field of L<SPVM_VALUE|/"SPVM_VALUE Type"> type to get the value of an SPVM C<int> reference type from an argument.

  int32_t* args0 = stack[0].iref;

=head3 Getting long Reference Type Argument

Use the C<lref> field of L<SPVM_VALUE|/"SPVM_VALUE Type"> type to get the value of an SPVM C<long> reference type from an argument.

  int64_t* args0 = stack[0].lref;

=head3 Getting float Reference Type Argument

Use the C<fref> field of L<SPVM_VALUE|/"SPVM_VALUE Type"> type to get the value of an SPVM C<float> reference type from an argument.

  float* args0 = stack[0].fref;

=head3 Getting double Reference Type Argument

Use the C<dref> field of L<SPVM_VALUE|/"SPVM_VALUE Type"> type to get the value of an SPVM C<double> reference type from an argument.

  double* args0 = stack[0].dref;

=head3 Getting Multi-Numeric Type Arguments

The values of an SPVM multi-numeric type from an argument have been stored to the multiple values in L<runtime stack|/"Runtime Stack">. the length of the values in the runtime stack is the same as the length of the fields of the SPVM multi-numeric type.

For example, if the argument type is L<Complex_2d|SPVM::Complex_2d> type, these values have been stored to multiple fields the multiple values in the runtime stack.

  double args0_re = stack[0].dval;
  double args0_im = stack[1].dval;

=head2 Return Value

If the reutrn type of an SPVM method is not the C<void> type, the first argument of L<runtime stack|/"Runtime Stack"> must be set to a return value.

  int32_t return_value = 5;
  
  stack[0].ival = return_value;

=head3 Setting Return Value of byte Type

Use the C<bval> field of L<SPVM_VALUE|/"SPVM_VALUE Type"> type to set a return value of the SPVM C<byte> type.

  stack[0].bval = return_value;

=head3 Setting Return Value of short Type

Use the C<sval> field of L<SPVM_VALUE|/"SPVM_VALUE Type"> type to set a return value of the SPVM C<short> type.

  stack[0].sval = return_value;

=head3 Setting Return Value of int Type

Use the C<ival> field of L<SPVM_VALUE|/"SPVM_VALUE Type"> type to set a return value of the SPVM C<int> type.

  stack[0].ival = return_value;

=head3 Setting Return Value of long Type

Use the C<lval> field of L<SPVM_VALUE|/"SPVM_VALUE Type"> type to set a return value of the SPVM C<long> type.

  stack[0].lval = return_value;

=head3 Setting Return Value of float Type

Use the C<fval> field of L<SPVM_VALUE|/"SPVM_VALUE Type"> type to set a return value of the SPVM C<float> type.

  stack[0].fval = return_value;

=head3 Setting Return Value of double Type

Use the C<dval> field of L<SPVM_VALUE|/"SPVM_VALUE Type"> type to set a return value of the SPVM C<double> type.

  stack[0].dval = return_value;

=head3 Setting Return Value of Object Type

Use the C<oval> field of L<SPVM_VALUE|/"SPVM_VALUE Type"> type to set a return value of an SPVM object type.

  stack[0].oval = return_value;

=head3 Setting Return Value of Multi-Numeric Type

Multiple values in L<runtime stack|/"Runtime Stack"> are needed to be set to values of the field type of the multi-numeric type. The length of the values in the runtime stack is the same as the length of the fields of the SPVM multi-numeric type.

There is an example in the case that the return type is L<Complex_2d|SPVM::Complex_2d>.

  double return_value_x;
  double return_value_y;
  stack[0].dval = return_value_x;
  stack[1].dval = return_value_y;

=head2 Native APIs

L<Native APIs|SPVM::Document::NativeAPI> are the APIs written by the C language for SPVM operations. Native APIs can be called in native classes. 

=head3 Examples of Native APIs

Create a Point object.
  
  int32_t error_id = 0;
  void* obj_point = env->new_object_by_name(env, stack, "Point", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }

Call a class method.

  int32_t error_id = 0;
  int32_t total;
  {
    int32_t args_width = 2;
    stack[0].ival = 5;
    stack[1].ival = 10;
    env->call_class_method_by_name(env, stack, "MyClass", "sum", args_width, &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    total = stack[0].ival;
  }

Get the characters of a string.

  const char* chars = env->get_chars(env, stack, obj_string);

Get the elements of an array of int type.

  int32_t* values = env->get_elems_int(env, stack, obj_array);

=head2 Exception

If a native method throws an exception, the native function must return a non-zero value, normally the basic type ID of an error class.

A message can be set to L<exception variable|SPVM::Document::Language::ExceptionHandling/"Exception Variable">. If no message is set to L<exception variable|SPVM::Document::Language::ExceptionHandling/"Exception Variable">, a default exception message is set to it.

  env->set_exception(env, stack, env->new_string_nolen(env, stack, "An exception is thrown."));
  
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;

L<die|SPVM::Document::NativeAPI/"die"> native API can be used to throw an exception easily.

  return env->die("The value must be %d.", 3, __func__, FILE_NAME, __LINE__);

=head2 Pointer Class

An SPVM object can have a L<pointer value|/"Pointer Value">.

If necessary, you can mark a class as a pointer class using L<pointer class attribute|SPVM::Document::Language::Class/"Class Attributes">.

  class MyClass : pointer {
    
  }

Examples of Pointer Classes:

C<SPVM/MyTm.spvm>:

  class MyTm : pointer {
    
    native static method new : MyTm ();
    
    native method sec : int ();
    
    native method DESTROY : ();
  }

C<SPVM/MyTm.c>:
  
  static const char* FILE_NAME = "MyTm.c";
  
  int32_t SPVM__MyTm__new(SPVM_ENV* env, SPVM_VALUE* stack) {
    
    int32_t error_id = 0;
    
    strcut tm* st_tm = (struct tm*)env->new_memory_block(env, stack, sizeof (struct tm));
    
    void* obj_tm = env->new_object_by_name(env, stack, "MyTm", error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    env->set_pointer(env, stack, obj_tm, st_tm);
    
    stack[0].oval = obj_tm;
    
    return 0;
  }
  
  int32_t SPVM__MyTm__sec(SPVM_ENV* env, SPVM_VALUE* stack) {
    
    void* obj_tm = stack[0].oval;
    
    strcut tm* st_tm = (struct tm*)env->get_pointer(env, stack, obj_tm);
    
    stack[0].ival = st_tm->tm_sec;
    
    return 0;
  }
  
  int32_t SPVM__MyTm__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
    
    void* obj_tm = stack[0].oval;
    
    strcut tm* st_tm = (struct tm*)env->get_pointer(env, stack, obj_tm);
    
    env->free_memory_block(env, stack, st_tm);
    
    return 0;
  }

=head3 Pointer Value

An object can have a pointer value. A pointer value is the address of a C/C++ object.

See L<get_pointer|SPVM::Document::NativeAPI/"get_pointer"> native API to get a pointer value of an object.

See L<set_pointer|SPVM::Document::NativeAPI/"set_pointer"> native API to set a pointer value of an object.

=head2 Native Directory

A native directory is the directory for native header files and native source files.

The name of the native directory is the same as the SPVM class name, but the extension C<.spvm> is replaced with C<.native>. 

  # The name of a native directory
  SPVM/MyClass.native

=head3 Native Header Files

A native class can include native header files in the C<include> directory under the native directory.
  
  # Native header files
  SPVM/MyClass.native/include/foo.h
                             /dir/bar.h
  
  // Native class
  #include "foo.h"
  #include "dir/bar.h"

=head3 Native Source Files

A native class can compile native source files in the C<src> directory under the native directory using L<add_source_file|SPVM::Builder::Config/"add_source_file"> in C<SPVM::Builder::Config> class.
  
  # Native source files
  SPVM/MyClass.native/src/foo.c
                         /dir/bar.c
  
  # Native config file
  my @source_files = ("foo.c", "dir/bar.c");
  $config->add_source_file(@source_files);

=head2 Scope

A native function has its scope.

L<enter_scope|SPVM::Document::NativeAPI/"enter_scope"> native API is called before the call of the native function.

L<leave_scope|SPVM::Document::NativeAPI/"leave_scope"> native API is called after the call of the native function.

You can create a scope and push objects to the L<native mortal stack|/"Native Mortal Stack">.

  int32_t mortal_stack_top = env->enter_scope(env, stack);
  
  env->push_mortal(env, stack, object);
  
  env->leave_scope(env, stack, mortal_stack_top);

=head3 Native Mortal Stack

A mortal stack is created for a L<runtime stack|/"Runtime Stack">.

A mortal stack is the stack to save local variables to be destroyed at the end of the scope.

=head2 Runtime Environment

A runtime environement is created for an SPVM runtime.

This is the pointer to the value of C<SPVM_ENV> type, normally named C<env>.

  SPVM_ENV* env;

A runtime environement is given to the first argument of a native function.

  int32_t SPVM__MyClass__sum(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  }

=head2 Runtime Stack

A runtime stack represents the execution context of an SPVM program. It is created for each native thread or coroutine. The SPVM runtime automatically creates a primary runtime stack for the main thread.

While it is named a "stack," it serves as a thread-local storage area that persists across function calls within the same execution unit. It is used to pass arguments to functions, receive return values, and store internal state specific to that thread, such as the L<exception variable|SPVM::Document::Language::ExceptionHandling/"Exception Variable"> and caller information.

Technically, a runtime stack is a pointer to an array of L<SPVM_VALUE|/"SPVM_VALUE Type"> elements, and by convention, it is named C<stack>.

SPVM_VALUE* stack;

A runtime stack is passed as the second argument to all native functions:

int32_t SPVM__MyClass__sum(SPVM_ENV* env, SPVM_VALUE* stack) { // ... }

You can manually manage runtime stacks for new threads or coroutines using the L<new_stack|SPVM::Document::NativeAPI/"new_stack"> and L<free_stack|SPVM::Document::NativeAPI/"free_stack"> native APIs.

=head3 Caller Stack

The B<caller stack> is a special region within the L<runtime stack|/"Runtime Stack"> used to store the history of method calls. It allows the runtime to trace back the execution path when an exception occurs or when debugging.

Each record in the caller stack consists of 4 elements (the record size is 4).

=over 2

=item * 0: current_method (The method currently being executed)

=item * 1: caller_name (The name of the caller method, such as C<Foo#bar> or C<SPVM__FOO__bar>)

=item * 2: caller_file (The file name of the caller)

=item * 3: caller_line (The line number of the caller)

=back

Example:

  // Get the current depth of the caller stack
  int32_t call_depth = env->get_call_depth(env, stack);
  
  // Get the raw pointer to the caller information stack
  void** caller_info_stack = env->get_caller_info_stack(env, stack);
  
  // Get the size of each record (Normally 4)
  int32_t record_size = env->get_caller_info_stack_record_size(env, stack);
  
  // Traverse the caller stack to build a backtrace
  for (int32_t i = 0; i < call_depth; i++) {
    void** record = &caller_info_stack[i * record_size];
    
    // Get the current method information from the pointer
    void* current_method = record[0];
    const char* current_method_name = env->api->method->get_name(env->runtime, current_method);
    
    // Get the current class (basic type) name from the method
    void* current_basic_type = env->api->method->get_current_basic_type(env->runtime, current_method));
    const char* current_class_name = env->api->basic_type->get_name(env->runtime, current_basic_type);
    
    // Get caller information from the record
    // caller_name could be "Foo#bar" or "SPVM__FOO__bar"
    const char* caller_name = (const char*)record[1];
    const char* caller_file = (const char*)record[2];
    int32_t caller_line = (int32_t)(intptr_t)record[3];
    
    // Process the information (e.g., printing a trace)
  }

=head2 Arguments Width

The width of the arguments is the length in units of L<SPVM_VALUE|/"SPVM_VALUE Type"> type.

If the type is a multi-numeric type, the width of the arguments is the length of the fields of the multi-numeric type. Otherwise, it is 1.

Consider the following method definition.

  method foo ($args0 : int, $args1 : Point, $arg2 : Complex_2d);

The argument width of the C<int> type is 1.

The argument width of the object type L<Point|SPVM::Point> is 1.

The argument width of the multi-numeric type L<Complex_2d|SPVM::Complex_2d> is the length of its field. It is 2.

So the width of the arguments is totally 4. 

=head2 Native Motal Stack

A native mortal stack is a stack that is used by L<enter_scope|SPVM::Document::NativeAPI/"enter_scope"> native API and L<leave_scope|SPVM::Document::NativeAPI/"leave_scope"> native API.

A L<runtime stack|/"Runtime Stack"> has one native mortal stack.

=head2 Compilation and Link

A native class and native source files are compiled to object files and are linked and a shared library is generated.

The extension of a shared library is C<.so> in Linux and UNIX, C<.dylib> in Mac, C<.dll> in Windows.

L<SPVM_BUILD_DIR|SPVM::Document::EnvironmentVariables/"SPVM_BUILD_DIR"> environment variable must be set to a build directoy path.

Normally, C<~/.spvm_build> is set to it.

  ~/.spvm_build

Object files and a shared library file are output to the build directory.

If the build directory does not exist, it is created.

Exceptions:

A string of non-zero length must be set to L<SPVM_BUILD_DIR|SPVM::Document::EnvironmentVariables/"SPVM_BUILD_DIR"> environment variable. Otherwise, an exception is thrown.

=head2 Dependency Resolution

The dependencies of compilation and link of a L<native class|/"Native Class">, L<native header files|/"Native Header Files">, and L<native source files|/"Native Source Files"> are resolved by the following rules.

=over 2

=item * If the version of SPVM is newer, the compilation and the link are performed.

=item * If the modification time of a native config file is newer than the generated dynamic library, the compilation and the link are performed.

=item * If the max of the modification time of the object files generated by compiliation is newer than the generated dynamic library, the link is performed.

=item * If the modification time of a native class is newer than the object file generated from the native class, the compilation is performed.

=item * If the modification time of a native source file is newer than the generated object file, the compilation is performed.

=item * If the max of the modification time of header source files is newer than the object file generated from a native source file, the compilation of the native source file is performed.

=back

If L<SPVM::Builder::Config#force|SPVM::Builder::Config/"force"> field is set to 1, the compilation and the link are forced.

  $config->force(1);

=head1 Resource

A native class can use native header files and native source files writen by native langauges such as the C language and C++ using L<SPVM::Builder::Config#use_resource|SPVM::Builder::Config/"use_resource">.

  # MyClass.config
  $config->use_resource("Resource::Zlib");
  
  // MyClass.c
  #include "zlib.h"

For details, see L<SPVM::Document::Resource>.

=head1 Distribution

A distribution for a native class can be generated by L<spvmdist> command.
  
  # C
  spvmdist --native c --user-name="Yuki Kimoto" --user-email="kimoto.yuki@gmail.com" MyNativeClass
  
  # C++
  spvmdist --native c++ --user-name="Yuki Kimoto" --user-email="kimoto.yuki@gmail.com" MyNativeClass

A native class file and a config file only can be added to an existing distribution.

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

=item * L<SPVM::Document>

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

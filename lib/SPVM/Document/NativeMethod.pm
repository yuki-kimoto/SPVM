=head1 NAME

SPVM::Document::NativeMethod - How to write native methods

=head1 DESCRIPTION

The native methods are the methods that the implementations are writen by native language such as C<C language> or C<C++>.

=head1 Native Methods

=head2 Native Method Declarations

A native method declaration are written using the method descriptor "native" in a SPVM module file. The method can't have the block. it ends with a semicolon.

  # SPVM/Foo/Bar.spvm
  class Foo::Bar {
    native static method sum : int ($num1 : int, $num2 : int);
  }

=head2 Native Config Files

A native config file is needed for the native module. The extension is C<config>. Put the config file in the same directory as the SPVM module.

  # Native configuration file for Foo::Bar module
  SPVM/Foo/Bar.config

If the native config file does not exist, an exception occurs.

Native config files are writen by Perl. It must return L<Builder::Config|SPVM::Builder::Config> object, otherwise an exception occurs.

I show some examples of native config files.

=head3 GNU99 Config Files

  # GNU99 Config File
  use strict;
  use warnings;

  use SPVM::Builder::Config;
  my $config = SPVM::Builder::Config->new_gnu99;

  $config;

=head3 C99 Config Files

  # C99 Config File
  use strict;
  use warnings;

  use SPVM::Builder::Config;
  my $config = SPVM::Builder::Config->new_c99;

  $config;

=head3 C11 Config Files

  # C11 Config File
  use strict;
  use warnings;

  use SPVM::Builder::Config;
  my $config = SPVM::Builder::Config->new_c;

  $config->set_std('c11');

  $config;

=head3 C++ Config Files

  # C++ Config File
  use strict;
  use warnings;

  use SPVM::Builder::Config;
  my $config = SPVM::Builder::Config->new_cpp;

  $config;

=head3 C++11 Config Files

  # C++11 Config File
  use strict;
  use warnings;

  use SPVM::Builder::Config;
  my $config = SPVM::Builder::Config->new_cpp;

  $config->set_std('c++11');

  $config;

=head3 CUDA/nvcc Config Files

  use strict;
  use warnings;

  my $config = SPVM::Builder::Config->new;

  # Compiler and Linker common
  my @ccldflags = qw(--compiler-options '-fPIC');

  # Compiler
  $config->cc('nvcc');
  $config->add_ccflags(@ccldflags);
  $config->ext('cu');

  # Linker
  $config->ld('nvcc');
  $config->add_ldflags('-shared', @ccldflags);

  $config;

=head3 The Options of Config Files

B<Output the commands of the compililation and the link:>

  use strict;
  use warnings;

  use SPVM::Builder::Config;
  my $config = SPVM::Builder::Config->new_gnu99;

  # Output the commands of the compililation and link
  $config->quiet(0);

  $config;

B<Force the compilation and the link:>

  use strict;
  use warnings;

  use SPVM::Builder::Config;
  my $config = SPVM::Builder::Config->new_gnu99;

  # Force the compilation and the link
  $config->force(1);

  $config;

=head2 Native Method Definitions

A native method definition is written in the native module file. Native module files are writen C, C++, or the language that the rule of function call is same as C. 

The extension is defined L<ext|SPVM::Builder::Config/"ext"> method in L<the config file|"Native-Config-Files">.

  $config->ext('cpp');

Generally the extension of C is C<c>, C++ is C<cpp>, CUDA/nvcc is C<cu>.

Put the config file in the same directory as the SPVM module.

  # Native module file for Foo::Bar module
  SPVM/Foo/Bar.c

This is an example of SPVM natvie module. The config file is L<GNU99|/"GNU99 Config Files">.

  #include "spvm_native.h"

  int32_t SPVM__Foo__Bar__sum(SPVM_ENV* env, SPVM_VALUE* stack) {

    int32_t num1 = stack[0].ival;
    int32_t num2 = stakc[1].ival;

    int32_t total = num1 + num2;

    stack[0].ival = total;

    return 0;
  }

=head3 The header of Native APIs

Include C<spvm_native.h> at the beginning of the natvie module. C<spvm_native.h> is the header of Native APIs. It defines L<the native APIs||/"List-of-Native-APIs"> and the data structures, such as C<SPVM_ENV>, C<SPVM_VALUE>.

=head3 Native Function Names

A SPVM native method have a native function.

Native funtions have the rule of the names. For example, the name is C<SPVM__Foo__Bar__sum>.

  SPVM__Foo__Bar__sum

This name is write by the following rules.

The function name starts with "SPVM__".

Followed by the class name "Foo__Bar", that is replaced "::" with "__".

Followed by "__".

Followed by the method name "sum".

If the name is invalid, a compilation error occurs.

=head3 Native Function Arguments

A native function has two arguments.

The first argument is C<env> that type is C<SPVM_ENV*>. This has the information of the runtime environment.

The second argument is C<stack> that type is C<SPVM_VALUE*>. This is used for getting the values of the arguments and setting the return value.

  int32_t SPVM__Foo__Bar__sum(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  }

In the above example, SPVM native method takes two arguments that type is C<int>. It calculates the sum of the tow values, and returns the total value.

  #include "spvm_native.h"

  int32_t SPVM__Foo__Bar__sum(SPVM_ENV* env, SPVM_VALUE* stack) {

    int32_t num1 = stack[0].ival;
    int32_t num2 = stakc[1].ival;

    int32_t total = num1 + num2;

    stack[0].ival = total;

    return 0;
  }

=head3 Native Function Return Value

The type of return value of native function is C<int32_t>. If the method succeeds, the method must return C<1>.  If the method fails, the method must return C<0>.

Note that this is B<not> the return value of the SPVM native method, such as the total value in the above example.

=head2 Compile Native Method

Native methods are compiled into a shared libraries. teay are shared libraries (.so) on Unix/Linux, dynamic link libraries (.dll) on Windows or etc corresponding to your os.

The compilation is done when SPVM is compiled. The build directory must exist, otherwise an exception occures.

The default build directory is the "~/.spvm_build" directory in the directory containing the executed Perl script, and can be changed with the environment variable "SPVM_BUILD_DIR".

If you want to use SPVM Native Method from Perl, create a "~/.spvm_build" directory in the directory where the executed Perl script exists.

  ~/.spvm_build

The generated object files exists under "work/object" under the build directory. The object file name is the name which the extension of the SPVM module name is changed to ".o".

  ~/.spvm_build/work/object/Foo/Bar.o

The generated shared libraries exists under "work/lib" under the build directory. The name of shared library is the name which the extension of the SPVM module name is changed to ".so", or etc corresponding to your os.

  # Unix/Linux
  ~/.spvm_build/work/object/Foo/Bar.so

  # Windows
  ~/.spvm_build/work/object/Foo/Bar.dll

=head2 Stack

The stack is the second argument of the definition of the Native Method. This is called stack. Stack is used getting arguments and return the value.

  int32_t SPVM__Foo__Bar__sum(SPVM_ENV* env, SPVM_VALUE* stack) {

  }

SPVM_VALUE is a union type of C language to store SPVM values. You can save integral value, floating point value, object value, and reference value to it.

For example, to get the value of the first argument(0th) of int type, write as follows.

  int32_t args0 = stack[0].ival;

For example, to get the value of the second argument(1th) of long type, write as follows.

  int64_t args1 = stack[1].lval;

For example, to return a value of double type, write as follows.

  stack[0].dval = 0.5;
  
=head2 Getting Arguments

=head3 Get byte type argument

To get the SPVM byte argument, access the bval field. Assign to the C language int8_t type.

  int8_t args0 = stack[0].bval;

=head3 Get short type argument

To get the short argument of SPVM, access the sval field. Assign it to the C language int16_t type.

  int16_t args0 = stack[0].sval;

=head3 Get int type argument

To get the SPVM int type argument, access the ival field. Assign to the C language int32_t type.

  int32_t args0 = stack[0].ival;

=head3 Get long type argument

To get the long argument of SPVM, access the lval field. Assign to the C language int64_t type.

  int64_t args0 = stack[0].lval;

=head3 Get float type argument

To get the SPVM float type argument, access the fval field. Assign to float type of C language.

  float args0 = stack[0].fval;

=head3 Get double type argument

To get the SPVM double argument, access the dval field. Assign to the C language double type.

  double args0 = stack[0].dval;

=head3 Get object type argument

To get the SPVM object type argument, access the oval field. Assign it to void* type in C language.

  void* args0 = stack[0].oval;

=head3 Get byte Reference Type Argument

If you get SPVM byte Reference Type argument, use "bref" field. it can be assinged to the value of C language int8_t* type.

  int8_t* args0 = stack[0].bref;

=head3 Get short Reference Type Argument

If you get SPVM short Reference Type argument, use "sref" field. it can be assinged to the value of C language int16_t* type.

  int16_t* args0 = stack[0].sref;

=head3 Get int Reference Type Argument

If you get SPVM int Reference Type argument, use "iref" field. it can be assinged to the value of C language int32_t* type.

  int32_t* args0 = stack[0].iref;

=head3 Get long Reference Type Argument

If you get SPVM long Reference Type argument, use "lref" field. it can be assinged to the value of C language int64_t* type.

  int64_t* args0 = stack[0].lref;

=head3 Get float Reference Type Argument

If you get SPVM float Reference Type argument, use "fref" field. it can be assinged to the value of C language float* type.

  float* args0 = stack[0].fref;

=head3 Get double Reference Type Argument

If you get SPVM double Reference Type Argument, use "dref" field. it can be assinged to the value of C language double* type.

  double* args0 = stack[0].dref;

=head3 Get multiple numeric type arguments

In a Native Method, multiple numeric type arguments are assigned to the coresponding multiple arguments.

For example, In the case of the argument values of L<Complex_2d|SPVM::Complex_2d> type, you can get them by the following way.

  double args_re = stack[0].dval;
  double args_im = stack[1].dval;

Note that you cannot access the values by the field name of L<Complex_2d|SPVM::Complex_2d>.


=head2 Return Value
  
=head3 Set return value of byte type

Use C<bval> field of C<SPVM_VALUE> to set a return value which type of SPVM is C<byte>. This is corresponding to C<int8_t> type of C language.

  int8_t retval;
  stack[0].bval = retval;

=head3 Set return value of short type

Use C<sval> field of C<SPVM_VALUE> to set a return value which type of SPVM is C<short>. This is corresponding to C<int16_t> type of C language.

  int16_t retval;
  stack[0].sval = retval;

=head3 Set return value of int type

Use C<ival> field of C<SPVM_VALUE> to set a return value which type of SPVM is C<int>. This is corresponding to C<int32_t> type of C language.

  int32_t retval;
  stack[0].ival = retval;

=head3 Set long type return value

Use C<lval> field of C<SPVM_VALUE> to set a return value which type of SPVM is C<long>. This is corresponding to C<int64_t> type of C language.

  int64_t retval;
  stack[0].lval = retval;

=head3 Set return value of float type

Use C<fval> field of C<SPVM_VALUE> to set a return value which type of SPVM is C<float>. This is corresponding to C<float> type of C language.

  float retval;
  stack[0].fval = retval;

=head3 Set return value of double type

Use C<dval> field of C<SPVM_VALUE> to set a return value which type of SPVM is C<double>. This is corresponding to C<double> type of C language.

  double retval;
  stack[0].dval = retval;

=head3 Set return value of object type

Use C<oval> field of C<SPVM_VALUE> to set a return value which type of SPVM is object. This is corresponding to C<void*> type of C language.

  void* retval;
  stack[0].oval = retval;

=head3 Set multiple numeric return value

If you set multiple numeric return value in native method, set multiple return values.

For example, in the case of L<Complex_2d|SPVM::Complex_2d>, do the following.

  double retval_x;
  double retval_y;
  stack[0].dval = retval_x;
  stack[1].dval = retval_y;

=head2 Call SPVM Method

If you want to call a method, you get a method id using L<get_class_method_id|"get_class_method_id"> or L<get_instance_method_id|"get_instance_method_id">.

L<get_class_method_id|"get_class_method_id"> get a method id of a class method.

L<get_instance_method_id|"get_instance_method_id"> get a method id of a instance method.

  // Get method id of class method
  int32_t method_id = env->get_class_method_id(env, "Foo", "sum", "int(int,int)");

  // Get method id of instance method
  int32_t method_id = env->get_instance_method_id(env, object, "sum", "int(int,int)");

If method_id is less than 0, it means that the method was not found. It is safe to handle exceptions as follows.

  if (method_id < 0) { return env->die(env, "Can't find method id", "Foo/Bar.c", __LINE__); }

Set the SPVM method argument to stack before calling the method.

  stack[0].ival = 1;
  stack[0].ival = 2;

To call a SPVM method, use the <a href="#native-api-native-sub-api-call_spvm_method">call_spvm_method</a> function.

  int32_t exception_flag = env->call_spvm_method(env, method_id, stack);

Nonzero if the method raised an exception, 0 if no exception occurred.

The return value of the method is stored in the first element of the stack.

  int32_t total = stack[0].ival;

=head2 Native Method Scope

Native method are entirely enclosed in scope.

Objects added to the mortal stack will automatically have their reference count decremented by 1 when the Native Method ends. When the reference count reaches 0, it is released.

Use push_mortal to add objects to the mortal stack.

  env->push_mortal(env, object);

Native APIs that normally create an object such as "new_object" will add the automatically created object to the mortal stack so you don't need to use this.

Use "enter_scope" to create a scope. The return value is the ID of that scope.

  int32_t scope_id = env->enter_scope (env);

Use "leave_scope" to leave the scope. For the argument, it is necessary to specify the scope ID obtained in "enter_scope".

  env->leave_scope(env, scope_id);

Use "remove_mortal" to remove the object from the mortal stack. For the argument, specify the scope ID obtained by "enter_scope" and the object you want to remove. The object is removed from the mortal stack and the reference count is automatically decremented by 1. When the reference count reaches 0, it is released.

  env->remove_mortal(env, scope_id, object);

Information about the mortal stack is stored in env.

=head2 Exception in Native Method

In the Native Method, it is the return value that indicates whether an exception has occurred.

  return 0;

  return 1;

If no exception occurs, "0" is returned. This is defined as "0".

If an exception occurs, "1" is returned. It is defined as a value other than "0".

If you want to set the exception message yourself, you can create an exception message with "new_string_nolen" and set it with "set_exception".

  env->set_exception(env, env->new_string_nolen(env, "Exception occur");
  return 1;

If no exception message is set, a default exception message will be set.

Usually, L<die|"die"">  is defined to make it easier to use, so it is better to use this.

  return env->die("Error. Values must be %d and %d", 3, 5, "Foo/Bar.c", __LINE__);

L<die|"die""> can be used in the same way as the C language sprintf function. Be sure to include this file name in the second from the end, and the line number in the last argument. If the message exceeds 255 bytes, the excess is truncated.

The exception is stored in env.

=head2 Pointer Type

There is a type called pointer type in SPVM, but I will explain how to use it.

The pointer type definition specifies the pointer_t descriptor in the SPVM class definition. Pointer types cannot have field definitions. This example describes how to use the C standard "struct tm" as a pointer type.

  # SPVM/MyTimeInfo.spvm
  class MyTimeInfo : pointer_t {

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
    void* tm_ptr = env->alloc_memory_block_zero (sizeof (struct tm));

    // Create strcut tm instance
    void* tm_obj = env->new_pointer(env, "MyTimeInfo", tm_ptr);

    stack[0].oval = tm_obj;

    return 0;
  }

  int32_t SPVM__MyTimeInfo__sec(SPVM_ENV* env, SPVM_VALUE* stack) {
    void* tm_obj = stack[0].oval;

    strcut tm* tm_ptr = (struct tm*) env->get_pointer(env, tm_obj);

    stack[0].ival = tm_ptr-> tm_sec;

    return 0;
  }

  int32_t SPVM__MyTimeInfo__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {

    void* tm_obj = stack[0].oval;
    strcut tm* tm_ptr = (struct tm*) env->get_pointer(env, tm_obj);

    env->free_memory_block (tm_ptr);

    return 0;
  }

In the constructor new, the memory of "struct tm" is first allocated by the alloc_memory_block_zero function. This is a function that reserves one memory block in SPVM. Similar to malloc, this function increments the memory block count by one, making it easier to spot memory leaks.

  // Alloc strcut tm
  void* tm_ptr = env->alloc_memory_block_zero (sizeof (struct tm));

Next, use the new_pointer function to create a new pointer type object with MyTimeInfo associated with it in the allocated memory.

  // Create strcut tm instance
  void* tm_obj = env->new_pointer(env, "MyTimeInfo", tm_ptr);

If you return this as a return value, the constructor is complete.

  stack[0].ival = tm_ptr-> tm_sec;
  
  return 0;

Next, let's get the value of tm_sec. sec method. The get_pointer function can be used to get a pointer to the memory allocated as a "struct tm" from a pointer type object.

  void* tm_obj = stack[0].oval;

  strcut tm* tm_ptr = (struct tm*) env->get_pointer(env, tm_obj);

  stack[0].ival = tm_ptr-> tm_sec;

The last is the destructor. Be sure to define a destructor, as the allocated memory will not be released automatically.

  int32_t SPVM__MyTimeInfo__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {

    void* tm_obj = stack[0].oval;

    strcut tm* tm_ptr = (struct tm*) env->get_pointer(env, tm_obj);

    env->free_memory_block (tm_ptr);

    return 0;
  }

Execute the free_memory_block function to free the memory. Be sure to free the memory allocated by alloc_memory_block_zero with the free_memory_block function. Releases the memory and decrements the memory block count by one.

=head2 Call Native API

Native API can be called from "SPVM_ENV* env" passed as an argument. Note that you have to pass env as the first argument.

  int32_t basic_type_id = env->get_basic_type_id(env, "Int");

=head1 Utilities

Utilities.

=head2 spvmgenlib

If you want to create SPVM module that have the native module, L<spvmgenlib> is useful.

=over 2

=item * L<spvmgenlib>

=back

=head1 Examples

=over 2

=item * L<Examples using native methods|https://github.com/yuki-kimoto/SPVM/tree/master/examples/native>

=back


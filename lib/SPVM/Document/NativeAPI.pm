=head1 NAME

SPVM::Document::NativeAPI - SPVM Native APIs

=head1 DESCRIPTION

SPVM Native APIs is C APIs used in SPVM native method. This document describes the way to define native methods, and shows the all of SPVM Native APIs. If you want to know the list of Native APIs, see L<List of Native APIs|/"List-of-Native-APIs">.

Native method can be written by C language or C++, If the code is compatible with C language or C++(for example, CUDA/nvcc), it can be compiled into native method. If you see examples of SPVM Native APIs, see L<Examples using SPVM Native APIs|https://github.com/yuki-kimoto/SPVM/tree/master/examples/native>. This contains the examples of C language, C++ and CUDA/nvcc.

=head1 How to define SPVM native method?

=begin html

<h2>Native Method Declaration</h2>

Native Method Declaration is written using Method Descriptor "native" in SPVM module file. SPVM Native Method Declaration ends with a semicolon without Sobroutine Block.

<pre>
# Foo/Bar.spvm
package Foo::Bar {
  native sub sum : int ($num1 : int, $num2 : int);
}
</pre>

<h2>SPVM Native Config File</h2>

SPVM Native Config File must be created for SPVM Native Method. The base name without the extension of native config file must be same as SPVM module file and the extension must be ".config".

<pre>
# Native configuration file for Foo::Bar module
Foo/Bar.config
</pre>

If native configuration file does not exist, an exception occurs.

Native Config File is Perl source code. Native Config File must return properly L<SPVM::Builder:Config> object, otherwise an exception occurs.

<b>1. C99 Config File Example</b>

<pre>
# C99 Config File
use strict;
use warnings;

use SPVM::Builder::Config;
my $bconf = SPVM::Builder::Config->new_c99;

$bconf;
</pre>

<b>2. C11 Config File Example</b>

<pre>
# C11 Config File
use strict;
use warnings;

use SPVM::Builder::Config;
my $bconf = SPVM::Builder::Config->new_c;

$bconf->set_std('c11');

$bconf;
</pre>

<b>3. C++ Config File Example</b>

<pre>
# C++ Config File
use strict;
use warnings;

use SPVM::Builder::Config;
my $bconf = SPVM::Builder::Config->new_cpp;

$bconf;
</pre>

<b>4. C++11 Config File Example</b>

<pre>
# C++11 Config File
use strict;
use warnings;

use SPVM::Builder::Config;
my $bconf = SPVM::Builder::Config->new_cpp;

$bconf->set_std('c++11');

$bconf;
</pre>

<b>5. CUDA/nvcc Config File Example</b>

<pre>
use strict;
use warnings;

my $bconf = SPVM::Builder::Config->new;

# Compiler and Linker common
$bconf->set_cccdlflags(q(--compiler-options '-fPIC'));

# Compiler
$bconf->set_cc('nvcc');
$bconf->set_ccflags('');
$bconf->set_ext('cu');

# Linker
$bconf->set_ld('nvcc');
$bconf->set_lddlflags('-shared');

$bconf;
</pre>

<h2 id="native-api-native-sub-definition">Native Method Definition</h2>

Native Method Definition is written in native source file. native source file is basically C language source file which extension is ".c". This extension can be changed to ".cpp" for C++ source file, to ".cu" for CUDA source file, etc.

<pre>
# Native source file for Foo::Bar module
Foo/Bar.c
</pre>

The following is natvie source file example written by C language.

<pre>
#include "spvm_native.h"

int32_t SPNATIVE__Foo__Bar__sum(SPVM_ENV* env, SPVM_VALUE* stack) {

  int32_t num1 = stack[0].ival;
  int32_t num2 = stakc[1].ival;

  int32_t total = num1 + num2;

  stack[0].ival = total;

  return 0;
}
</pre>

<h3>Include spvm_native.h</h3>

Include "spvm_native.h" at the beginning of the native source file. This header file defines SPVM Native APIs and data structures for Native API and useful macro functions.

See <a href="#native-api-list">List of SPVM Native APIs</a> about included SPVM Native APIs by this header.

spvm_native.h include the following data structures.

<pre>
SPVM_ENV
SPVM_VALUE
</pre>

See <a href="#native-api-list">List of SPVM Native APIs</a> about included SPVM Native APIs by this header.

See <a href="#native-api-list">List of SPVM Native APIs</a> about included SPVM Native APIs by this header.

<h3>Return Value</h3>

The return type is "int32_t". If the subroutine raises an exception, "1" is returned, otherwise "0" is returned.

<h3>Function Name</h3>

Native Method Definition is a simple C language function such as

<pre>
SPNATIVE__Foo__Bar__sum
</pre>

The function name starts with "SPNATIVE__".

Followed by package name "Foo__Bar", which is replaced "::" in Foo::Bar.

Followed by "__".

Followed by subroutine name "sum".

If Native Method Name is invalid, a compile error will occur.


  <p>
    There are two arguments, the first argument is "SPVM_ENV* env" which has the information of the execution environment, and the second argument is "SPVM_VALUE* stack" which is used for the argument and return value.
  </p>
  <p>
  </p>
  <p>
    In the above sample, it takes two int type arguments of SPVM, calculates the sum, and returns the return value.
  </p>
  
  <h2 id="native-api-native-sub-compile">Compile Native Method</h2>
  <p>
    Native subroutine are compiled with Perl and are compiled into a dynamically readable shared library depending on the OS. Shared libraries (.so) on Unix/Linux, dynamic link libraries (.dll) on Windows.
  </p>
  <p>
    Compilation into a dynamically readable shared library is done during SPVM compilation. The build directory must exist at compile time. If the build directory does not exist, an exception will be thrown.
  </p>
  <p>
    The default build directory is the "~/.spvm_build" directory in the directory containing the executed Perl script, and can be changed with the environment variable "SPVM_BUILD_DIR".
  </p>
  <p>
    If you want to use SPVM Native Method from Perl, create a "~/.spvm_build" directory in the directory where the executed Perl script exists.
  </p>
<pre>
script.pl
~/.spvm_build
</pre>
  <p>
    The intermediately generated object files are generated under "work/object" under the build directory. The object file name has the extension of the SPVM module changed to ".o".
  </p>
<pre>
~/.spvm_build/work/object/Foo/Bar.o
</pre>
  <p>
    Dynamically readable shared libraries are generated under "work/lib" under the build directory. The file name of the dynamically readable shared library is the extension of the SPVM module changed to the dynamically readable shared library extension according to the OS.
  </p>
<pre>
# Unix/Linux
~/.spvm_build/work/object/Foo/Bar.so

# Windows
~/.spvm_build/work/object/Foo/Bar.dll
</pre>

  <h2 id="native-api-native-sub-get-arg">Arguments</h2>
  <ul>
    <li><a href="#native-api-native-sub-get-arg-stack">Arguments and Stack</a></li>
    <li><a href="#native-api-native-sub-get-arg-byte">Get byte type argument</a></li>
    <li><a href="#native-api-native-sub-get-arg-short">Get short type argument</a></li>
    <li><a href="#native-api-native-sub-get-arg-int">Get int type argument</a></li>
    <li><a href="#native-api-native-sub-get-arg-long">Get long type argument</a></li>
    <li><a href="#native-api-native-sub-get-arg-float">Get float type argument</a></li>
    <li><a href="#native-api-native-sub-get-arg-double">Get double type argument</a></li>
    <li><a href="#native-api-native-sub-get-arg-object">Get object type argument</a></li>
    <li><a href="#native-api-native-sub-get-arg-stack">Stack of arguments</a></li>
    <li><a href="#native-api-native-sub-get-arg-byte-ref">Get reference type argument of byte</a></li>
    <li><a href="#native-api-native-sub-get-arg-short-ref">Get reference type argument of short</a></li>
    <li><a href="#native-api-native-sub-get-arg-int-ref">Get int reference type argument</a></li>
    <li><a href="#native-api-native-sub-get-arg-long-ref">Get long reference type argument</a></li>
    <li><a href="#native-api-native-sub-get-arg-float-ref">Get float reference type argument</a></li>
    <li><a href="#native-api-native-sub-get-arg-double-ref">Get double reference type argument</a></li>
    <li><a href="#native-api-native-sub-get-arg-mulnum">Get multiple numeric argument</a></li>
  </ul>
  
<h3 href = "# native-api-native-sub-get-arg-stack">Arguments and Stack</h3>
  <p>
    The stack is the "SPVM_VALUE* stack" passed as the second argument in the definition of the Native Method, and the arguments are stored in this.
  </p>
<pre>
int32_t SPNATIVE__Foo__Bar__sum(SPVM_ENV* env, SPVM_VALUE* stack) {

}
</pre>
  <p>
    SPVM_VALUE is a C language union for storing SPVM values. You can save numeric, object, and reference values.
  </p>
  <p>
    Pointer to the beginning of the "SPVM_VALUE type array" of "SPVM_VALUE* stack". The value of the argument of the Native Method called from SPVM side is set in this array.
  </p>
  <p>
    For example, to get the value of the first argument(0th) of int type, write as follows.
  </p>
<pre>
int32_t args0 = stack[0].ival;
</pre>
  <p>
    For example, to get the value of the second argument(1th) of long type, write as follows.
  </p>
<pre>
int64_t args1 = stack[1].lval;
</pre>

<h3 id="native-api-native-sub-get-arg-byte">Get byte type argument</h3>
  <p>
    To get the SPVM byte argument, access the bval field. Assign to the C language int8_t type.
  </p>
<pre>
int8_t args0 = stack[0].bval;
</pre>

<h3 id="native-api-native-sub-get-arg-short">Get short type argument</h3>
  <p>
    To get the short argument of SPVM, access the sval field. Assign it to the C language int16_t type.
  </p>
<pre>
int16_t args0 = stack[0].sval;
</pre>

<h3 id="native-api-native-sub-get-arg-int">Get int type argument</h3>
  <p>
    To get the SPVM int type argument, access the ival field. Assign to the C language int32_t type.
  </p>
<pre>
int32_t args0 = stack[0].ival;
</pre>

<h3 id="native-api-native-sub-get-arg-long">Get long type argument</h3>
  <p>
    To get the long argument of SPVM, access the lval field. Assign to the C language int64_t type.
  </p>
<pre>
int64_t args0 = stack[0].lval;
</pre>

<h3 id="native-api-native-sub-get-arg-float">Get float type argument</h3>
  <p>
    To get the SPVM float type argument, access the fval field. Assign to float type of C language.
  </p>
<pre>
float args0 = stack[0].fval;
</pre>

<h3 id="native-api-native-sub-get-arg-double">Get double type argument</h3>
  <p>
    To get the SPVM double argument, access the dval field. Assign to the C language double type.
  </p>
<pre>
double args0 = stack[0].dval;
</pre>

<h3 id="native-api-native-sub-get-arg-object">Get object type argument</h3>
  <p>
    To get the SPVM object type argument, access the oval field. Assign it to void* type in C language.
  </p>
<pre>
void* args0 = stack[0].oval;
</pre>

<h3 id="native-api-native-sub-get-arg-byte-ref">Get byte Reference Type Argument</h3>

If you get SPVM byte Reference Type argument, use "bref" field. it can be assinged to the value of C language int8_t* type.

<pre>
int8_t* args0 = stack[0].bref;
</pre>

<h3 id="native-api-native-sub-get-arg-short">Get short Reference Type Argument</h3>

If you get SPVM short Reference Type argument, use "sref" field. it can be assinged to the value of C language int16_t* type.

<pre>
int16_t* args0 = stack[0].sref;
</pre>

<h3 id="native-api-native-sub-get-arg-int">Get int Reference Type Argument</h3>

If you get SPVM int Reference Type argument, use "iref" field. it can be assinged to the value of C language int32_t* type.

<pre>
int32_t* args0 = stack[0].iref;
</pre>

<h3 id="native-api-native-sub-get-arg-long">Get long Reference Type Argument</h3>

If you get SPVM long Reference Type argument, use "lref" field. it can be assinged to the value of C language int64_t* type.

<pre>
int64_t* args0 = stack[0].lref;
</pre>

<h3 id="native-api-native-sub-get-arg-float">Get float Reference Type Argument</h3>

If you get SPVM float Reference Type argument, use "fref" field. it can be assinged to the value of C language float* type.

<pre>
float* args0 = stack[0].fref;
</pre>

<h3 id="native-api-native-sub-get-arg-double">Get double Reference Type Argument</h3>

If you get SPVM double Reference Type Argument, use "dref" field. it can be assinged to the value of C language double* type.

<pre>
double* args0 = stack[0].dref;
</pre>

<h3 id="native-api-native-sub-get-arg-mulnum">Get multiple numeric type arguments</h3>
  <p>
    In a Native Method, multiple numeric type arguments are assigned to multiple arguments.
  </p>
  <p>
    For example, in the case of the argument of SPVM::Complex_2d type, it gets from two arguments. Note that you cannot access it by field name.
  </p>
<pre>
double args_re = stack[0].dval;
double args_im = stack[1].dval;
</pre>

  <h2 id="native-api-native-sub-set-retval">Return Value</h2>
  <ul>
    <li><a href="#native-api-native-sub-set-retval-stack">Return value and stack</a></li>
    <li><a href="#native-api-native-sub-set-retval-byte">Set return value of byte type</a></li>
    <li><a href="#native-api-native-sub-set-retval-short">Set return value of short type</a></li>
    <li><a href="#native-api-native-sub-set-retval-int">Set return value of int type</a></li>
    <li><a href="#native-api-native-sub-set-retval-long">Set long type return value</a></li>
    <li><a href="#native-api-native-sub-set-retval-float">Set return value of float type</a></li>
    <li><a href="#native-api-native-sub-set-retval-double">Set return value of double type</a></li>
    <li><a href="#native-api-native-sub-set-retval-object">Set return value of object type</a></li>
    <li><a href="#native-api-native-sub-set-retval-mulnum">Multiple numeric return value setting</a></li>
  </ul>
  
<h3 id="native-api-native-sub-set-retval-stack">Return value and stack</h3>
  <p>
    Native subroutine use the stack to set the return value, rather than returning it with a C language return statement.
  </p>
  <p>
    For example, to return an int type return value, write as follows.
  </p>
<pre>
stack[0].ival = 3;
</pre>
  <p>
    For example, to get the value of the second argument of long type, write as follows.
  </p>
<pre>
stack[0].lval = 56;
</pre>

<h3 id="native-api-native-sub-set-retval-byte">Set return value of byte type</h3>
  <p>
    To set the SPVM byte return value, assign it to the bval field. Assigns a value of type int8_t in C language.
  </p>
<pre>
int8_t retval;
stack[0].bval = retval;
</pre>

<h3 id="native-api-native-sub-set-retval-short">Set return value of short type</h3>
  <p>
    To set the SPVM short return value, assign it to the sval field. Assigns a C language int16_t type value.
  </p>
<pre>
int16_t retval;
stack[0].sval = retval;
</pre>

<h3 id="native-api-native-sub-set-retval-int">Set return value of int type</h3>
  <p>
    To set the SPVM int return value, assign it to the ival field. Assigns a C language int32_t type value.
  </p>
<pre>
int32_t retval;
stack[0].ival = retval;
</pre>

<h3 id="native-api-native-sub-set-retval-long">Set long type return value</h3>
  <p>
    To set the SPVM long return value, assign it to the lval field. Assigns a value of C language int64_t type.
  </p>
<pre>
int64_t retval;
stack[0].lval = retval;
</pre>

<h3 id="native-api-native-sub-set-retval-float">Set return value of float type</h3>
  <p>
    To set the SPVM float return value, assign it to the fval field. Substitutes a C type float type value.
  </p>
<pre>
float retval;
stack[0].fval = retval;
</pre>

<h3 id="native-api-native-sub-set-retval-double">Set return value of double type</h3>
  <p>
    To set the SPVM double return value, assign it to the dval field. Assigns a C type double value.
  </p>
<pre>
double retval;
</pre>

<h3 id="native-api-native-sub-set-retval-object">Set return value of object type</h3>
  <p>
    To set the return value of the SPVM object type, assign it to the oval field. Assign a value of void* type in C language.
  </p>
<pre>
void* retval;
stack[0].oval = retval;
</pre>

<h3 id="native-api-native-sub-set-retval-mulnum">Set multiple numeric return value</h3>
  <p>
    In a Native Method, multiple numeric return values assigned to multiple return values.
  </p>
  <p>
    For example, for the return value of SPVM::Complex_2d type, set two return values.
  </p>
<pre>
double retval_x;
double retval_y;
stack[0].dval = retval_x;
stack[1] .dval = retval_y;
</pre>

  <h2 id="native-api-native-call-sub">Call SPVM Method</h2>
  <p>
    To call the SPVM subroutine, first use the <a href="#native-api-native-sub-api-sub_id">sub_id</a> function or the <a href = "# native-api-native- Get the ID of the subroutine using the sub-api-method_sub_id ">method_sub_id</a> function
  </p>
<pre>
// For a subroutine that is not a method
int32_t sub_id = env->get_sub_id(env, "Foo", "sum", "int (int, int)");

// For method
int32_t sub_id = env->get_sub_id_by_object(env, object, "sum", "int (self, int, int)");
</pre>
  <p>
    If sub_id is less than 0, it means that the subroutine was not found. It is safe to handle exceptions as follows.
  </p>
<pre>
if (sub_id <0) {
  SPVM_DIE ("Can't find sub id", "Foo/Bar.c", __LINE__);
}
</pre>
  <p>
    Set the SPVM subroutine argument to stack before calling the subroutine.
  </p>
<pre>
stack[0].ival = 1;
stack[0].ival = 2;
</pre>
  <p>
    To call a SPVM subroutine, use the <a href="#native-api-native-sub-api-call_sub">call_sub</a> function.
  </p>
<pre>
int32_t exception_flag = env->call_sub(env, sub_id, stack);
</pre>
  <p>
    Nonzero if the subroutine raised an exception, 0 if no exception occurred.
  </p>
  <p>
    The return value of the subroutine is stored in the first element of the stack.
  </p>
<pre>
int32_t total = stack[0].ival;
</pre>

  <h2 id="native-api-native-sub-scope">Native Method Scope</h2>
  <p>
    Native subroutine are entirely enclosed in scope.
  </p>
  <p>
    Objects added to the mortal stack will automatically have their reference count decremented by 1 when the Native Method ends. When the reference count reaches 0, it is released.
  </p>
  <p>
    Use push_mortal to add objects to the mortal stack.
  </p>
<pre>
env->push_mortal(env, object);
</pre>
  <p>
    Native APIs that normally create an object such as "new_object" will add the automatically created object to the mortal stack so you don't need to use this.
  </p>
  <p>
    Use "enter_scope" to create a scope. The return value is the ID of that scope.
  </p>
<pre>
int32_t scope_id = env->enter_scope (env);
</pre>
  <p>
    Use "leave_scope" to leave the scope. For the argument, it is necessary to specify the scope ID obtained in "enter_scope".
  </p>
<pre>
env->leave_scope(env, scope_id);
</pre>
  
  <p>
    Use "remove_mortal" to remove the object from the mortal stack. For the argument, specify the scope ID obtained by "enter_scope" and the object you want to remove. The object is removed from the mortal stack and the reference count is automatically decremented by 1. When the reference count reaches 0, it is released.
  </p>
<pre>
env->remove_mortal(env, scope_id, object);
</pre>
  <p>
    Information about the mortal stack is stored in env.
  </p>

  <h2 id="native-api-native-sub-exception">Exception in Native Method</h2>
  <p>
    In the Native Method, it is the return value that indicates whether an exception has occurred.
  </p>
<pre>
return 0;

return 1;
</pre>
  <p>
    If no exception occurs, "0" is returned. This is defined as "0".
  <p>
  <p>
    If an exception occurs, "1" is returned. It is defined as a value other than "0".
  <p>
  <p>
    If you want to set the exception message yourself, you can create an exception message with "new_string_nolen" and set it with "set_exception".
  </p>
<pre>
env->set_exception(env, env->new_string_nolen(env, "Exception occur");
return 1;
</pre>
  <p>
    If no exception message is set, a default exception message will be set.
  </p>
  <p>
    Usually, "SPVM_DIE" is defined to make it easier to use, so it is better to use this.
  </p>
<pre>
SPVM_DIE ("Error. Values must be %d and %d", 3, 5, "Foo/Bar.c", __LINE__);
</pre>
  <p>
    SPVM_DIE can be used in the same way as the C language sprintf function. Be sure to include this file name in the second from the end, and the line number in the last argument. If the message exceeds 255 bytes, the excess is truncated.
  </p>
  <p>
    The exception is stored in env.
  </p>

  <h2 id="native-api-use-pointer-type">Pointer Type</h2>
  <p>
    There is a type called pointer type in SPVM, but I will explain how to use it.
  </p>
  <p>
    The pointer type definition specifies the pointer_t descriptor in the SPVM package definition. Pointer types cannot have field definitions. This example describes how to use the C standard "struct tm" as a pointer type.
  </p>
<pre>
# MyTimeInfo.spvm
package MyTimeInfo : pointer_t {

  # Constructor
  native sub new : MyTimeInfo ();

  # Get second
  native sub sec : int ($self : self);

  # Destructor
  native sub DESTROY : ($self : self);
}
</pre>
  <p>
    It defines a new constructor, a method that takes seconds information called sec, and a destructor called DESTROY. These are Native Method.
  </p>
  <p>
    Next is the definition on the C language side.
  </p>
<pre>
# MyTimeInfo.c

int32_t SPNATIVE__MyTimeInfo__new(SPVM_ENV* env, SPVM_VALUE* stack) {

  // Alloc strcut tm
  void* tm_ptr = env->alloc_memory_block_zero (sizeof (struct tm));

  // Create strcut tm instance
  void* tm_obj = env->new_pointer(env, "MyTimeInfo", tm_ptr);

  stack[0].oval = tm_obj;

  return 0;
}

int32_t SPNATIVE__MyTimeInfo__sec(SPVM_ENV* env, SPVM_VALUE* stack) {
  void* tm_obj = stack[0].oval;

  strcut tm* tm_ptr = (struct tm*) env->get_pointer(env, tm_obj);

  stack[0].ival = tm_ptr-> tm_sec;

  return 0;
}

int32_t SPNATIVE__MyTimeInfo__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {

  void* tm_obj = stack[0].oval;
  strcut tm* tm_ptr = (struct tm*) env->get_pointer(env, tm_obj);

  env->free_memory_block (tm_ptr);

  return 0;
}
</pre>
  <p>
    In the constructor new, the memory of "struct tm" is first allocated by the alloc_memory_block_zero function. This is a function that reserves one memory block in SPVM. Similar to malloc, this function increments the memory block count by one, making it easier to spot memory leaks.
  </p>
<pre>
// Alloc strcut tm
void* tm_ptr = env->alloc_memory_block_zero (sizeof (struct tm));
</pre>
  <p>
    Next, use the new_pointer function to create a new pointer type object with MyTimeInfo associated with it in the allocated memory.
  </p>
<pre>
// Create strcut tm instance
void* tm_obj = env->new_pointer(env, "MyTimeInfo", tm_ptr);
</pre>
  <p>
    If you return this as a return value, the constructor is complete.
  </p>
<pre>
stack[0].ival = tm_ptr-> tm_sec;

return 0;
</pre>
  <p>
    Next, let's get the value of tm_sec. sec method. The get_pointer function can be used to get a pointer to the memory allocated as a "struct tm" from a pointer type object.
  </p>
<pre>
void* tm_obj = stack[0].oval;

strcut tm* tm_ptr = (struct tm*) env->get_pointer(env, tm_obj);

stack[0].ival = tm_ptr-> tm_sec;
</pre>
  <p>
    The last is the destructor. Be sure to define a destructor, as the allocated memory will not be released automatically.
  </p>
<pre>
int32_t SPNATIVE__MyTimeInfo__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {

  void* tm_obj = stack[0].oval;

  strcut tm* tm_ptr = (struct tm*) env->get_pointer(env, tm_obj);

  env->free_memory_block (tm_ptr);

  return 0;
}
</pre>
  <p>
    Execute the free_memory_block function to free the memory. Be sure to free the memory allocated by alloc_memory_block_zero with the free_memory_block function. Releases the memory and decrements the memory block count by one.
  </p>

  <h2 id="native-api-call">Call Native API</h2>
  <p>
    Native API can be called from "SPVM_ENV* env" passed as an argument. Note that you have to pass env as the first argument.
  </p>
<pre>
int32_t basic_type_id = env->get_basic_type_id(env, "SPVM::Int");
</pre>

=end html

=head1 List of Native APIs

=head2 package_vars_heap

the pointer to the storage area of the package variables. This is used internally.


=head2 object_header_byte_size

The byte size of the object's header. This is used internally.


=head2 object_weaken_backref_head_offset

Offset to a pointer to the back reference of the weak reference in the object structure. This is used internally.


=head2 object_ref_count_offset

Reference count offset in the object structure. This is used internally.


=head2 object_basic_type_id_offset

Offset of basic type ID in object structure. This is used internally.


=head2 object_type_dimension_offset

Offset of type dimension in object structure. This is used internally.

=head2 object_type_category_offset

Offset of runtime type category in object structure. This is used internally.

=head2 object_flag_offset

Offset of flag in object structure. This is used internally.


=head2 object_length_offset

The length offset in the object structure. This is used internally.


=head2 byte_object_basic_type_id

Basic type ID of SPVM::Byte type. This is used internally.


=head2 short_object_basic_type_id

ID of the base type of SPVM::Short type. This is used internally.


=head2 int_object_basic_type_id

ID of the base type of SPVM::Int type. This is used internally.


=head2 long_object_basic_type_id

ID of the base type of SPVM::Long type. This is used internally.


=head2 float_object_basic_type_id

ID of the base type of SPVM::Float type. This is used internally.


=head2 double_object_basic_type_id

ID of the base type of SPVM::Double type. This is used internally.


=head2 compiler

A pointer to the SPVM compiler. This is used internally.


=head2 exception_object

Exception object. This is used internally.


=head2 native_mortal_stack

Mortal stack used for native calls. This is used internally.

=head2 native_mortal_stack_top

The top position of the mortal stack used for native calls. This is used internally.


=head2 native_mortal_stack_capacity

The amount of mortal stack used for native calls. This is used internally.


=head2 get_basic_type_id

Get the ID of the base type given the name of the base type. If it does not exist, a value less than 0 is returned.


  int32_t (*get_basic_type_id)(SPVM_ENV* env, const char* basic_type_name);


Example:


  int32_t basic_type_id = env->get_basic_type_id(env, "SPVM::Int");


=head2 get_field_id

Get the ID of the field given the package name, field name, and signature. If the field does not exist, a value less than 0 is returned.


  int32_t (*get_field_id)(SPVM_ENV* env, const char* package_name, const char* field_name, const char* signature);


The signature is the same as the field type name.


Example:


  int32_t field_id = env->get_field_id(env, "Foo", "x", "int");


=head2 get_field_offset

Gets the offset of the field given the field ID. The field ID must be a valid field ID obtained with the field_id function.


  int32_t (*get_field_offset)(SPVM_ENV* env, int32_t field_id);


=head2 get_package_var_id

Get the package variable ID given the package name, package variable name and signature. If the package variable does not exist, a value less than 0 is returned.


  int32_t (*get_package_var_id)(SPVM_ENV* env, const char* package_name, const char* package_var_name, const char* signature);


The signature is the same as the package variable type name.


Example:


  int32_t pkgvar_id = env->get_package_var_id(env, "Foo", "$VAR", "int");


=head2 get_sub_id

Get the subroutine ID by specifying the package name, subroutine name, and signature. If no subroutine exists, a value less than 0 is returned.


  int32_t (*get_sub_id)(SPVM_ENV* env, const char* package_name, const char* sub_name, const char* signature);


The signature has the following format: Must not contain white space.


  Return value type name (argument type name 1, argument type name 2, ...)


Example:


  int32_t sub_id = env->get_sub_id(env, "Foo", "func", "int (long, string)");


=head2 get_sub_id_by_object

  int32_t (*get_sub_id_by_object)(SPVM_ENV* env, void* object, const char* method_name, const char* signature);


Get the subroutine ID by specifying the object and method name. If the method does not exist, a value less than 0 is returned.


The signature is the same as the sub_id signature.


Example:


  int32_t sub_id = env->get_sub_id_by_object(env, object, "method", "int(self,long,string)");


=head2 new_object_raw

Generates a new object with a base type ID. The base type ID must be the correct base type ID obtained by the "basic_type_id function".


  void* (*new_object_raw)(SPVM_ENV* env, int32_t basic_type_id);


This function does not add objects to the mortal stack, so use new_object to avoid memory leaks for normal use.

=head2 new_object

Generates and returns a new object with a base type ID. The base type ID must be the correct base type ID obtained in the basic_type_id. Adds a newly generated object to the mortal stack.


  void* (*new_object)(SPVM_ENV* env, int32_t basic_type_id);


Sample:


  int32_t basic_type_id = env-&gt;get_basic_type_id(env,"SPVM::Int");
  void* object = env-&gt;new_object(env, basic_type_id);

=head2 new_byte_array_raw

Generates a new "byte[] type" object by specifying the length of the array. The initial value of all elements is 0.


  void* (*new_byte_array_raw)(SPVM_ENV* env, int32_t length);


This function does not add objects to the mortal stack, so use new_byte_array to avoid memory leaks for normal use.

=head2 new_byte_array

Generates and returns a new "byte[] type" object with the length of the array. The initial value of all elements is 0. Adds a newly generated object to the mortal stack.


  void* (*new_byte_array)(SPVM_ENV* env, int32_t length);


Sample:


  void* byte_array_obj = env-&gt;new_byte_array(env, 100);


=head2 new_short_array_raw

Generates a new "short[] type" object by specifying the length of the array. The initial value of all elements is 0.


  void* (*new_short_array_raw)(SPVM_ENV* env, int32_t length);


This function does not add objects to the mortal stack, so use new_short_array to avoid memory leaks for normal use.


=head2 new_short_array

Generates and returns a new "short[] type" object with the length of the array. The initial value of all elements is 0. Adds a newly generated object to the mortal stack.


  void* (*new_short_array)(SPVM_ENV* env, int32_t length);


Sample:


  void* short_array_obj = env-&gt;new_short_array(env, 100);


=head2 new_int_array_raw

Generates a new "int[] type" object by specifying the length of the array. The initial value of all elements is 0.


  void* (*new_int_array_raw)(SPVM_ENV* env, int32_t length);


This function does not add objects to the mortal stack, so normal use should use new_int_array to avoid memory leaks.


=head2 new_int_array

Generates and returns a new "int[] type" object with the length of the array. The initial value of all elements is 0. Adds a newly generated object to the mortal stack.


  void* (*new_int_array)(SPVM_ENV* env, int32_t length);


Sample:


  void* int_array_obj = env-&gt;new_int_array(env, 100);


=head2 new_long_array_raw

Creates a new "long[] type" object by specifying the length of the array. The initial value of all elements is 0.


  void* (*new_long_array_raw)(SPVM_ENV* env, int32_t length);


This function does not add objects to the mortal stack, so use normal_new_long_array to avoid memory leaks.


=head2 new_long_array

Create a new "long[] type" object by specifying the length of the array and return it. The initial value of all elements is 0. Add the newly created object to the mortal stack.


  void* (*new_long_array)(SPVM_ENV* env, int32_t length);


Example:


  void* long_array_obj = env->new_long_array(env, 100);


=head2 new_float_array_raw

Create a new "float[] type" object by specifying the length of the array. The initial value of all elements is 0.


  void* (*new_float_array_raw)(SPVM_ENV* env, int32_t length);


This function does not add any objects to the mortal stack, so use new_float_array for normal use to avoid memory leaks.


=head2 new_float_array

Create a new "float[] type" object by specifying the length of the array and return it. The initial value of all elements is 0. Add the newly created object to the mortal stack.


  void* (*new_float_array)(SPVM_ENV* env, int32_t length);


Example:


  void* float_array_obj = env->new_float_array(env, 100);


=head2 new_double_array_raw

Creates a new "double[]" object by specifying the length of the array. The initial value of all elements is 0.


  void* (*new_double_array_raw)(SPVM_ENV* env, int32_t length);


This function does not add any objects to the mortal stack, so use normal_new_double_array to avoid memory leaks.


=head2 new_double_array

Generate a new "double[] type" object by specifying the length of the array and return it. The initial value of all elements is 0. Add the newly created object to the mortal stack.


  void* (*new_double_array)(SPVM_ENV* env, int32_t length);


Example:


  void* double_array_obj = env->new_double_array(env, 100);


=head2 new_object_array_raw

Create a new object type array by specifying the basic type ID and array length and return it. The basic type ID must be the correct basic type ID obtained with the "basic_type_id function". The initial value of all elements is null.


  void* (*new_object_array_raw)(SPVM_ENV* env, int32_t basic_type_id, int32_t length);



This function does not add objects to the mortal stack, so use normal_new_object_array to avoid memory leaks.


=head2 new_object_array

Create a new object type array by specifying the basic type ID and array length and return it. The basic type ID must be the correct basic type ID obtained with the "basic_type_id function". The initial value of all elements is null. Add the newly created object to the mortal stack.


  void* (*new_object_array)(SPVM_ENV* env, int32_t basic_type_id, int32_t length);



Example:


  int32_t basic_type_id = env->get_basic_type_id(env, "SPVM::Int");
  void* object_array_obj = env->new_object_array(env, basic_type_id, 100);


=head2 new_muldim_array_raw

Generates and returns a new multidimensional object type array by specifying the basic type ID, element type dimension, and array length. The basic type ID must be the correct basic type ID obtained with the "basic_type_id function". The initial value of all elements is null.


  void* (*new_muldim_array_raw)(SPVM_ENV* env, int32_t basic_type_id, int32_t element_dimension, int32_t length);


This function does not add any objects to the mortal stack, so use new_muldim_array for normal use to avoid memory leaks.


=head2 new_muldim_array

Generates and returns a new multidimensional object type array by specifying the basic type ID, element type dimension, and array length. The basic type ID must be the correct basic type ID obtained with the "basic_type_id function". The initial value of all elements is null. Add the newly created object to the mortal stack.


  void* (*new_muldim_array_raw)(SPVM_ENV* env, int32_t basic_type_id, int32_t element_dimension, int32_t length);


Element type dimensions must be less than 255.


Example:


  // new SPVM::Int[][][100]
  int32_t basic_type_id = env->get_basic_type_id(env, "SPVM::Int");
  void* multi_array_obj = env->new_muldim_array(env, basic_type_id, 2, 100);


=head2 new_mulnum_array_raw

Generate a new multi-numeric array by specifying the basic type ID and array length and return it. The basic type ID must be the correct basic type ID acquired by the "basic_type_id function" and must be valid as a composite numeric type. The initial value of all fields for all elements is 0.


  void* (*new_mulnum_array_raw)(SPVM_ENV* env, int32_t basic_type_id, int32_t length);


This function does not add any objects to the mortal stack, so use new_mulnum_array for normal use to avoid memory leaks.


=head2 new_mulnum_array

Generate a new multi-numeric array by specifying the basic type ID and array length and return it. The basic type ID must be the correct basic type ID acquired by the "basic_type_id function" and must be valid as a composite numeric type. The initial value of all fields for all elements is 0.


  void* (*new_mulnum_array)(SPVM_ENV* env, int32_t basic_type_id, int32_t length);


Example:


  int32_t basic_type_id = env->get_basic_type_id(env, "SPVM::Complex_2d");
  void* value_array_obj = env->new_mulnum_array(env, basic_type_id, 100);


=head2 new_string_nolen_raw

Specify a C language string to generate a string type object and return it. The string must end with "\0".


  void* (*new_string_nolen_raw)(SPVM_ENV* env, const char* bytes);


This function does not add any objects to the mortal stack, so for normal use use new_string to avoid memory leaks.


=head2 new_string_nolen

Specify a C language string to generate a string type object and return it. The string must end with "\0". Add the newly created object to the mortal stack.


  void* (*new_string_nolen)(SPVM_ENV* env, const char* bytes);


Example:


  void* str_obj = env->new_string_nolen(env, "Hello World");


=head2 new_string_raw

Specify a C language string and length to generate a string type object and return it.


  void* (*new_string_raw)(SPVM_ENV* env, const char* bytes, int32_t length);


This function does not add any objects to the mortal stack, so for normal use use new_string to avoid memory leaks.



=head2 new_string

Generates and returns a character string type object by specifying the character string and length in C language. Add the newly created object to the mortal stack.

  void* (*new_string)(SPVM_ENV* env, const char* bytes, int32_t length);


Example:


  void* str_obj = env->new_string(env, "Hello \0World", 11);


=head2 new_pointer_raw

Specify a basic type ID and a C language pointer to create a pointer type object and return it. The basic type ID must be the correct basic type ID acquired by the "basic_type_id function" and valid as a pointer type.



  void* (*new_pointer_raw)(SPVM_ENV* env, int32_t basic_type_id, void* pointer);



This function does not add any objects to the mortal stack, so for normal use use new_pointer to avoid memory leaks.


=head2 new_pointer

Specify a basic type ID and a C language pointer to create a pointer type object and return it. The basic type ID must be the correct basic type ID acquired by the "basic_type_id function" and valid as a pointer type. Add the newly created object to the mortal stack.


  void* (*new_pointer)(SPVM_ENV* env, int32_t basic_type_id, void* pointer);


Example:


  void* pointer = malloc (sizeof (struct tm));
  void* pointer_obj = env->new_pointer(env, "MyTimeInfo", pointer);



See <a href="#native-api-use-pointer-type">Using pointer types</a> for a detailed sample.


=head2 concat_raw

Returns a new byte[] type object that is a concatenation of two byte[] type strings.


  void* (*concat_raw)(SPVM_ENV* env, void* string1, void* string2);



This function does not add objects to the mortal stack, so use concat for normal use to avoid memory leaks.


=head2 concat

Returns a new byte[] type object that is a concatenation of two byte[] type strings. Add the newly created object to the mortal stack.


  void* (*concat)(SPVM_ENV* env, void* string1, void* string2);


=head2 new_stack_trace_raw

If you specify a byte[] type exception message and a package name, subroutine name, file name and line number, the character string of the package name, subroutine name, file name and line number is added to the end of the byte[] type exception message. The added character string will be returned.


  void* (*new_stack_trace_raw)(SPVM_ENV* env, void* exception, const char* package_name, const char* sub_name, const char* file, int32_t line);


This function does not add objects to the mortal stack, use new_stack_trace to avoid memory leaks for normal use.


=head2 new_stack_trace

When a byte[] type exception message and a package name, subroutine name, file name and line number are specified, the string of the package name, subroutine name, file name and line number is added to the end of the string type exception message. Returns a new string type object. Add the newly created object to the mortal stack.


  void* (*new_stack_trace)(SPVM_ENV* env, void* exception, const char* package_name, const char* sub_name, const char* file, int32_t line);


=head2 length

If you specify an array, the length of the array is returned.


  int32_t (*length)(SPVM_ENV*, void* array);


Example:


  int32_t length = env->length(env, array);


=head2 get_elems_byte

If you specify a byte[] type array, the pointer at the beginning of the internally stored C language int8_t[] type array is returned.  

  int8_t* (*get_elems_byte)(SPVM_ENV* env, void* array);


Example:


  int8_t* values = env->get_elems_byte(env, array);
  values[3] = 5;


=head2 get_elems_short

If a short[] type array is specified, the pointer at the beginning of the internally stored C language int16_t[] type array is returned.


  int16_t* (*get_elems_short)(SPVM_ENV* env, void* array);


Example:


  int16_t* values = env->get_elems_short(env, array);
  values[3] = 5;


=head2 get_elems_int

When an int[] type array is specified, the pointer at the beginning of the internally stored C language int32_t[] type array is returned.


  int32_t* (*get_elems_int)(SPVM_ENV* env, void* array);


Example:


  int32_t* values = env->get_elems_int(env, array);
  values[3] = 5;


=head2 get_elems_long

When a long[] type array is specified, the pointer at the beginning of the internally stored C language int64_t[] type array is returned.


  int64_t* (*get_elems_long)(SPVM_ENV* env, void* array);


Example:


  int64_t* values = env->get_elems_long(env, array);
  values[3] = 5;


=head2 get_elems_float

When a float[] type array is specified, the pointer at the beginning of the C language float[] type array internally held is returned.


  float* (*get_elems_float)(SPVM_ENV* env, void* array);


Example:


  float* values = env->get_elems_float(env, array);
  values[3] = 1.5f;


=head2 get_elems_double

If a double[] type array is specified, the pointer at the beginning of the internally stored C double[] type array is returned.


  double* (*get_elems_double)(SPVM_ENV* env, void* array);


Example:


  double* values = env->get_elems_double(env, array);
  values[3] = 1.5;


=head2 get_elem_object

Gets an object of an element given an array of object types and a subscript. If the element is a weak reference, the weak reference is removed.


  void* (*get_elem_object)(SPVM_ENV* env, void* array, int32_t index);


Example:


  void* object = env->get_elem_object(env, array, 3);

=head2 set_elem_object

If you specify an array of object type and subscript and element objects, the element object is assigned to the corresponding subscript position. If the element's object has a weak reference, the weak reference is removed. The reference count of the originally assigned object is decremented by 1.


  void (*set_elem_object)(SPVM_ENV* env, void* array, int32_t index, void* value);


Example:


  env->get_elem_object(env, array, 3, object);

=head2 get_field_byte

If an object and field ID are specified, the byte field value will be returned as a C language int8_t type value. The field ID must be a valid field ID obtained with the field_id function.


  int8_t (*get_field_byte)(SPVM_ENV* env, void* object, int32_t field_id);


Example:


  int32_t field_id = env->get_field_id(env, "Foo", "x", "byte");
  int8_t field_value = env->get_field_byte(env, object, field_id);


=head2 get_field_short

If you specify the object and field ID, the value of the short type field will be returned as the int16_t type value of C language. The field ID must be a valid field ID obtained with the field_id function.


  int16_t (*get_field_short)(SPVM_ENV* env, void* object, int32_t field_id);


Example:


  int32_t field_id = env->get_field_id(env, "Foo", "x", "short");
  int16_t field_value = env->get_field_short(env, object, field_id);


=head2 get_field_int

If an object and a field ID are specified, the value of the int type field will be returned as a C language int32_t type value. The field ID must be a valid field ID obtained with the field_id function.


  int32_t (*get_field_int)(SPVM_ENV* env, void* object, int32_t field_id);


Example:


  int32_t field_id = env->get_field_id(env, "Foo", "x", "int");
  int32_t field_value = env->get_field_int(env, object, field_id);


=head2 get_field_long

If you specify the object and field ID, the value of the long type field will be returned as the value of int64_t type of C language. The field ID must be a valid field ID obtained with the field_id function.


  int64_t (*get_field_long)(SPVM_ENV* env, void* object, int32_t field_id);


Example:


  int32_t field_id = env->get_field_id(env, "Foo", "x", "long");
  int64_t field_value = env->get_field_long(env, object, field_id);


=head2 get_field_float

If you specify the object and field ID, the value of the float type field will be returned as a C language float type value. The field ID must be a valid field ID obtained with the field_id function.


  float (*get_field_float)(SPVM_ENV* env, void* object, int32_t field_id);


Example:


  int32_t field_id = env->get_field_id(env, "Foo", "x", "float");
  float field_value = env->get_field_float(env, object, field_id);


=head2 get_field_double

If you specify the object and field ID, the value of the double type field will be returned as a double type value in C language. The field ID must be a valid field ID obtained with the field_id function.


  double (*get_field_double)(SPVM_ENV* env, void* object, int32_t field_id);


Example:


  int32_t field_id = env->get_field_id(env, "Foo", "x", "double");
  double field_value = env->get_field_double(env, object, field_id);


=head2 get_field_object

If you specify the object and field ID, the value of the object type field is returned as a void* type value in C language. The field ID must be a valid field ID obtained with the field_id function. If the field is a weak reference, it will be removed.


  void* (*get_field_object)(SPVM_ENV* env, void* object, int32_t field_id);


  int32_t field_id = env->get_field_id(env, "Foo", "x", "SPVM::Int");
  void* field_value = env->get_field_object(env, object, field_id);


=head2 set_field_byte

If you specify the object and field ID and the value of the field, the value is set to the byte type field. The field ID must be a valid field ID obtained with the field_id function.


  void (*set_field_byte)(SPVM_ENV* env, void* object, int32_t field_id, int8_t value);


Example:


  int32_t field_id = env->get_field_id(env, "Foo", "x", "byte");
  int8_t field_value = 5;
  env->set_field_byte(env, object, field_id, field_value);


=head2 set_field_short

If you specify the object and field ID and the value of the field, the value is set to the short type field. The field ID must be a valid field ID obtained with the field_id function.


  void (*set_field_short)(SPVM_ENV* env, void* object, int32_t field_id, int16_t value);


Example:


  int32_t field_id = env->get_field_id(env, "Foo", "x", "short");
  int16_t field_value = 5;
  env->set_field_short(env, object, field_id, field_value);


=head2 set_field_int

If you specify the object and field ID and the value of the field, the value is set to the int type field. The field ID must be a valid field ID obtained with the field_id function.


  void (*set_field_int)(SPVM_ENV* env, void* object, int32_t field_id, int32_t value);


Example:


  int32_t field_id = env->get_field_id(env, "Foo", "x", "int");
  int32_t field_value = 5;
  env->set_field_int(env, object, field_id, field_value);


=head2 set_field_long

If you specify the object and field ID and the value of the field, the value is set to the long type field. The field ID must be a valid field ID obtained with the field_id function.


  void (*set_field_long)(SPVM_ENV* env, void* object, int32_t field_id, int64_t value);


Example:


  int32_t field_id = env->get_field_id(env, "Foo", "x", "long");
  int64_t field_value = 5;
  env->set_field_long(env, object, field_id, field_value);


=head2 set_field_float

If you specify the object and field ID and the value of the field, the value is set to the float type field. The field ID must be a valid field ID obtained with the field_id function.


  void (*set_field_float)(SPVM_ENV* env, void* object, int32_t field_id, float value);


Example:


  int32_t field_id = env->get_field_id(env, "Foo", "x", "float");
  float field_value = 1.5f;
  env->set_field_float(env, object, field_id, field_value);


=head2 set_field_double

If you specify the object and field ID and the value of the field, the value is set to the double type field. The field ID must be a valid field ID obtained with the field_id function.


  void (*set_field_double)(SPVM_ENV* env, void* object, int32_t field_id, double value);


Example:


  int32_t field_id = env->get_field_id(env, "Foo", "x", "double");
  double field_value = 1.55;
  env->set_field_double(env, object, field_id, field_value);


=head2 set_field_object

Object and field Specify the ID and the value of the field and set the value to the object type field. The field ID must be a valid field ID obtained with the field_id function. After setting, the reference count is incremented by 1. The original value has the reference count decremented by 1.


  void (*set_field_object)(SPVM_ENV* env, void* object, int32_t field_id, void* value);


Example:


  int32_t field_id = env->get_field_id(env, "Foo", "x", "SPVM::Int");
  int32_t basic_type_id = env->get_basic_type_id(env, "SPVM::Int");
  void* object = env->new_object(env, basic_type_id);
  env->set_field_object(env, object, field_id, object);


=head2 get_package_var_byte

If an object and a package variable ID are specified, the value of the byte type package variable is returned as a C language int8_t type value. The package variable ID must be a valid package variable ID obtained with the field_id function.


  int8_t (*get_package_var_byte)(SPVM_ENV* env, int32_t pkgvar_id);


Example:


  int32_t pkgvar_id = env->get_package_var_id(env, "Foo", "$VAR", "byte");
  int8_t pkgvar_value = env->get_package_var_byte(env, object, pkgvar_id);


=head2 get_package_var_short

If an object and a package variable ID are specified, the value of the short type package variable will be returned as a C language int16_t type value. The package variable ID must be a valid package variable ID obtained with the field_id function.


  int16_t (*get_package_var_short)(SPVM_ENV* env, int32_t pkgvar_id);


Example:


  int32_t pkgvar_id = env->get_package_var_id(env, "Foo", "$VAR", "short");
  int16_t pkgvar_value = env->get_package_var_short(env, object, pkgvar_id);


=head2 get_package_var_int

If an object and a package variable ID are specified, the value of the int type package variable will be returned as a C language int32_t type value. The package variable ID must be a valid package variable ID obtained with the field_id function.


  int32_t (*get_package_var_int)(SPVM_ENV* env, int32_t pkgvar_id);


Example:


  int32_t pkgvar_id = env->get_package_var_id(env, "Foo", "$VAR", "int");
  int32_t pkgvar_value = env->get_package_var_int(env, object, pkgvar_id);


=head2 get_package_var_long

If an object and a package variable ID are specified, the value of the long type package variable will be returned as a C language int64_t type value. The package variable ID must be a valid package variable ID obtained with the field_id function.


  int64_t (*get_package_var_long)(SPVM_ENV* env, int32_t pkgvar_id);


Example:


  int32_t pkgvar_id = env->get_package_var_id(env, "Foo", "$VAR", "long");
  int64_t pkgvar_value = env->get_package_var_long(env, object, pkgvar_id);


=head2 get_package_var_float

If an object and a package variable ID are specified, the value of the float type package variable will be returned as a C language float type value. The package variable ID must be a valid package variable ID obtained with the field_id function.


  float (*get_package_var_float)(SPVM_ENV* env, int32_t pkgvar_id);


Example:


  int32_t pkgvar_id = env->get_package_var_id(env, "Foo", "$VAR", "float");
  float pkgvar_value = env->get_package_var_float(env, object, pkgvar_id);


=head2 get_package_var_double

If you specify an object and a package variable ID, the value of the double type package variable is returned as a C type double type value. The package variable ID must be a valid package variable ID obtained with the field_id function.


  double (*get_package_var_double)(SPVM_ENV* env, int32_t pkgvar_id);


Example:


  int32_t pkgvar_id = env->get_package_var_id(env, "Foo", "$VAR", "double");
  double pkgvar_value = env->get_package_var_double(env, object, pkgvar_id);


=head2 get_package_var_object

When an object and a package variable ID are specified, the value of the object type package variable is returned as a C language void* type value. The package variable ID must be a valid package variable ID obtained with the field_id function.


  void* (*get_package_var_object)(SPVM_ENV* env, int32_t pkgvar_id);


Example:


  int32_t pkgvar_id = env->get_package_var_id(env, "Foo", "$VAR", "SPVM::Int");
  void* pkgvar_value = env->get_package_var_byte(env, object, pkgvar_id);


=head2 set_package_var_byte

If you specify the object and field ID and the value of the field, the value is set to the byte type field. The field ID must be a valid field ID obtained with the field_id function.


  void (*set_package_var_byte)(SPVM_ENV* env, int32_t pkgvar_id, int8_t value);


Example:


  int32_t pkgvar_id = env->get_package_var_id(env, "Foo", "$VAR", "byte");
  int8_t pkgvar_value = 5;
  env->set_package_var_byte(env, pkgvar_id, pkgvar_value);


=head2 set_package_var_short

If you specify the object and field ID and the value of the field, the value is set to the short type field. The field ID must be a valid field ID obtained with the field_id function.


  void (*set_package_var_short)(SPVM_ENV* env, int32_t pkgvar_id, int16_t value);


Example:


  int32_t pkgvar_id = env->get_package_var_id(env, "Foo", "$VAR", "short");
  int16_t pkgvar_value = 5;
  env->set_package_var_short(env, pkgvar_id, pkgvar_value);


=head2 set_package_var_int

If you specify the object and field ID and the value of the field, the value is set to the int type field. The field ID must be a valid field ID obtained with the field_id function.


  void (*set_package_var_int)(SPVM_ENV* env, int32_t pkgvar_id, int32_t value);


Example:


  int32_t pkgvar_id = env->get_package_var_id(env, "Foo", "$VAR", "int");
  int32_t pkgvar_value = 5;
  env->set_package_var_int(env, pkgvar_id, pkgvar_value);


=head2 set_package_var_long

If you specify the object and field ID and the value of the field, the value is set to the long type field. The field ID must be a valid field ID obtained with the field_id function.


  void (*set_package_var_long)(SPVM_ENV* env, int32_t pkgvar_id, int64_t value);


Example:


  int32_t pkgvar_id = env->get_package_var_id(env, "Foo", "$VAR", "long");
  int64_t pkgvar_value = 5;
  env->set_package_var_long(env, pkgvar_id, pkgvar_value);


=head2 set_package_var_float

If you specify the object and field ID and the value of the field, the value is set to the float type field. The field ID must be a valid field ID obtained with the field_id function.


  void (*set_package_var_float)(SPVM_ENV* env, int32_t pkgvar_id, float value);


Example:


  int32_t pkgvar_id = env->get_package_var_id(env, "Foo", "$VAR", "float");
  float pkgvar_value = 5;
  env->set_package_var_float(env, pkgvar_id, pkgvar_value);


=head2 set_package_var_double

If you specify the object and field ID and the value of the field, the value is set to the double type field. The field ID must be a valid field ID obtained with the field_id function.


  void (*set_package_var_double)(SPVM_ENV* env, int32_t pkgvar_id, double value);


Example:


  int32_t pkgvar_id = env->get_package_var_id(env, "Foo", "$VAR", "double");
  double pkgvar_value = 5;
  env->set_package_var_double(env, pkgvar_id, pkgvar_value);


=head2 set_package_var_object

Object and field Specify the ID and the value of the field and set the value to the object type field. The field ID must be a valid field ID obtained with the field_id function. After setting, the reference count is incremented by 1. The original value has the reference count decremented by 1.


  void (*set_package_var_object)(SPVM_ENV* env, int32_t pkgvar_id, void* value);


Example:


  int32_t pkgvar_id = env->get_package_var_id(env, "Foo", "$VAR", "SPVM::Int");
  int32_t basic_type_id = env->get_basic_type_id(env, "SPVM::Int");
  void* object = env->new_object(env, basic_type_id);
  env->set_package_var_object(env, pkgvar_id, pkgvar_value);


=head2 get_pointer

Specify a pointer type object and return the C language pointer stored inside the object.


  void* (*get_pointer)(SPVM_ENV* env, void* pointer_object);



Example:


  strcut tm* tm_ptr = (struct tm*) env->get_pointer(env, tm_obj);


See <a href="#native-api-use-pointer-type">Using pointer types</a> for a detailed sample.


=head2 set_pointer

If you specify a pointer type object and a C language pointer, the C language pointer is saved in the internal data of the pointer type object.


  void (*set_pointer)(SPVM_ENV* env, void* pointer_object, void* pointer);


=head2 call_sub

Call the subroutine by specifying the subroutine ID and argument. The return value is non-zero when an exception occurs in the subroutine, 0 is returned when the exception does not occur.


  int32_t (*call_sub)(SPVM_ENV* env, int32_t sub_id, SPVM_VALUE* args);


The return value of the subroutine is set to "args[0]".


=head2 get_exception

Returns the byte[] type object saved as an exception.


  void* (*get_exception)(SPVM_ENV* env);


=head2 set_exception

If you specify an object of type byte[], it will be saved as an exception.


  void (*set_exception)(SPVM_ENV* env, void* exception);


=head2 get_ref_count


  int32_t (*get_ref_count)(SPVM_ENV* env, void* object);


=head2 inc_ref_count

Specifying an object increments the reference count of the object.


  void (*inc_ref_count)(SPVM_ENV* env, void* object);


Use this method only if you have a specific reason to use it. Normally, the reference count is managed automatically.


=head2 dec_ref_count

Specifying an object decrements the object's reference count by 1. When the reference count reaches 0, the object is released.


  void (*dec_ref_count)(SPVM_ENV* env, void* object);


Use this method only if you have a specific reason to use it. Normally, the reference count is managed automatically.


=head2 enter_scope

Create a new scope and return the scope ID.


  int32_t (*enter_scope)(SPVM_ENV* env);


=head2 push_mortal

Add an object to the mortal stack.


  int32_t (*push_mortal)(SPVM_ENV* env, void* object);


If this method succeed, return 0.

If this method don't alloc memory for new mortal information, return 1.

=head2 leave_scope

Specify a scope ID to exit that scope and decrement the object's reference count stored in the mortal stack. Objects with a reference count of 0 are released. The scope ID must be the ID obtained by the enter_scope function.


  void (*leave_scope)(SPVM_ENV* env, int32_t scope_id);


=head2 remove_mortal

Given a scope ID and an object, delete the specified object from the mortal stack.


  int32_t (*remove_mortal)(SPVM_ENV* env, int32_t scope_id, void* remove_object);


=head2 is_type

Given an object and a base type ID and a type dimension, returns a nonzero value if the object matches both the base type ID and the type dimension, and 0 otherwise.


  int32_t (*is_type)(SPVM_ENV* env, void* object, int32_t basic_type_id, int32_t type_dimension);


=head2 has_callback

Given a base type id for the object and the callback type, returns a non-zero value if the object conforms to the callback type, and zero otherwise.


  int32_t (*has_callback)(SPVM_ENV* env, void* object, int32_t callback_basic_type_id);


=head2 get_object_basic_type_id

Gets the base type ID of the object.


  int32_t (*get_object_basic_type_id)(SPVM_ENV* env, void* object);


=head2 get_object_type_dimension

Gets the dimension of the type of object.


  int32_t (*get_object_type_dimension)(SPVM_ENV* env, void* object);


=head2 weaken


  int32_t (*weaken)(SPVM_ENV* env, void** object_address);


Create weak reference to the object which is specified by object address.

The reference count of the object is decrimented by 1 and weaken flag is added to the object address.

If the reference count is 1, "dec_ref_count" is called to the object.

If object_address is NULL, this method do nothing.

If the object is already weaken, this method do nothing.

This method allocate memory internally to add the back reference from the object to the object address.

This method success return 0.

If failing memory allocation of back reference, return 1.

=head2 isweak 
Given the address of an object, returns non-zero if the object is a weak reference, 0 otherwise.


  int32_t (*isweak()SPVM_ENV* env, void** object);


=head2 unweaken

Specifying the address of the object releases the weak reference to the object.


  void (*unweaken)(SPVM_ENV* env, void** object_address);


=head2 alloc_memory_block_zero


  void* (*alloc_memory_block_zero)(SPVM_ENV* env, int64_t byte_size);



If you specify the size in bytes, the memory block is allocated and the pointer of the allocated memory block is returned. If fail to alloc memory, return NULL. If success, all bits in the memory block are initialized with 0 and the memory block count (memory_blocks_count)is incremented by 1.


=head2 free_memory_block


  void (*free_memory_block)(SPVM_ENV* env, void* block);


If block is not NULL, free the memory and memory blocks count(memory_blocks_count) is decremented by 1.

=head2 get_memory_blocks_count

Returns the current number of memory blocks.


  int32_t (*get_memory_blocks_count)(SPVM_ENV* env);


The memory block is increased by 1 when an object is created, when the alloc_memory_block_zero function is called, and when a back reference is added by the weaken function.


=head2 get_type_name_raw

If you specify an object, a new byte[] type object that stores the type name is returned.


  void* (*get_type_name_raw)(SPVM_ENV* env, void* object);


This function does not add objects to the mortal stack, so use type_name for normal use to avoid memory leaks.


=head2 get_type_name

If you specify an object, a new byte[] type object that stores the type name is returned. Add the newly created object to the mortal stack.


  void* (*get_type_name)(SPVM_ENV* env, void* object);

=head2 new_env

Create a new execution environment based on the current execution environment.


  SPVM_ENV* (*new_env)(SPVM_ENV* env);


Create a new SPVM runtime environment.


The exception object and mortal stack information will be initialized.


Share the package variables with the original execution environment.


The number of memory blocks is shared with the original execution environment.


If thie method can't allocate memory for SPVM runtime environment, return NULL.

=head2 free_env

Release the execution environment.


  void (*free_env)(SPVM_ENV* env);


=head2 memory_blocks_count

Memory blocks count. This is used internally.


  void* memory_blocks_count;


=head2 get_chars

Get characters pointer in the string object.


  const char* (*get_chars)(SPVM_ENV* env, void* string_object);


Example:


  const char* bytes = env->get_chars(env, string_object);


=head2 die


  int32_t (*die)(SPVM_ENV* env, const char* message, ...);


=head2 new_object_by_name


  void* (*new_object_by_name)(SPVM_ENV* env, const char* package_name, int32_t* exception_flag, const char* file, int32_t line);


=head2 new_pointer_by_name


  void* (*new_pointer_by_name)(SPVM_ENV* env, const char* package_name, void* pointer, int32_t* exception_flag, const char* file, int32_t line);


=head2 set_field_byte_by_name


  void (*set_field_byte_by_name)(SPVM_ENV* env, void* object, const char* package_name, const char* field_name, int8_t value,
    int32_t* exception_flag, const char* file, int32_t line);


=head2 set_field_short_by_name


  void (*set_field_short_by_name)(SPVM_ENV* env, void* object, const char* package_name, const char* field_name, int16_t value,
    int32_t* exception_flag, const char* file, int32_t line);


=head2 set_field_int_by_name


  void (*set_field_int_by_name)(SPVM_ENV* env, void* object, const char* package_name, const char* field_name, int32_t value,
    int32_t* exception_flag, const char* file, int32_t line);


=head2 set_field_long_by_name


  void (*set_field_long_by_name)(SPVM_ENV* env, void* object, const char* package_name, const char* field_name, int64_t value,
    int32_t* exception_flag, const char* file, int32_t line);


=head2 set_field_float_by_name


  void (*set_field_float_by_name)(SPVM_ENV* env, void* object, const char* package_name, const char* field_name, float value,
    int32_t* exception_flag, const char* file, int32_t line);


=head2 set_field_double_by_name


  void (*set_field_double_by_name)(SPVM_ENV* env, void* object, const char* package_name, const char* field_name, double value,
    int32_t* exception_flag, const char* file, int32_t line);


=head2 set_field_object_by_name


  void (*set_field_object_by_name)(SPVM_ENV* env, void* object, const char* package_name, const char* field_name, const char* signature, void* value,
    int32_t* exception_flag, const char* file, int32_t line);


=head2 get_field_byte_by_name


  int8_t (*get_field_byte_by_name)(SPVM_ENV* env, void* object, const char* package_name, const char* field_name,
    int32_t* exception_flag, const char* file, int32_t line);


=head2 get_field_short_by_name


  int16_t (*get_field_short_by_name)(SPVM_ENV* env, void* object, const char* package_name, const char* field_name,
    int32_t* exception_flag, const char* file, int32_t line);


=head2 get_field_int_by_name


  int32_t (*get_field_int_by_name)(SPVM_ENV* env, void* object, const char* package_name, const char* field_name,
    int32_t* exception_flag, const char* file, int32_t line);


=head2 get_field_long_by_name


  int64_t (*get_field_long_by_name)(SPVM_ENV* env, void* object, const char* package_name, const char* field_name,
    int32_t* exception_flag, const char* file, int32_t line);


=head2 get_field_float_by_name


  float (*get_field_float_by_name)(SPVM_ENV* env, void* object, const char* package_name, const char* field_name,
    int32_t* exception_flag, const char* file, int32_t line);


=head2 get_field_double_by_name


  double (*get_field_double_by_name)(SPVM_ENV* env, void* object, const char* package_name, const char* field_name,
    int32_t* exception_flag, const char* file, int32_t line);


=head2 get_field_object_by_name


  void* (*get_field_object_by_name)(SPVM_ENV* env, void* object, const char* package_name, const char* field_name, const char* signature,
    int32_t* exception_flag, const char* file, int32_t line);


=head2 set_package_var_byte_by_name


  void (*set_package_var_byte_by_name)(SPVM_ENV* env, const char* package_name, const char* package_var_name, int8_t value,
    int32_t* exception_flag, const char* file, int32_t line);


=head2 set_package_var_short_by_name


  void (*set_package_var_short_by_name)(SPVM_ENV* env, const char* package_name, const char* package_var_name, int16_t value,
    int32_t* exception_flag, const char* file, int32_t line);


=head2 set_package_var_int_by_name


  void (*set_package_var_int_by_name)(SPVM_ENV* env, const char* package_name, const char* package_var_name, int32_t value,
    int32_t* exception_flag, const char* file, int32_t line);


=head2 set_package_var_long_by_name


  void (*set_package_var_long_by_name)(SPVM_ENV* env, const char* package_name, const char* package_var_name, int64_t value,
    int32_t* exception_flag, const char* file, int32_t line);


=head2 set_package_var_float_by_name


  void (*set_package_var_float_by_name)(SPVM_ENV* env, const char* package_name, const char* package_var_name, float value,
    int32_t* exception_flag, const char* file, int32_t line);


=head2 set_package_var_double_by_name


  void (*set_package_var_double_by_name)(SPVM_ENV* env, const char* package_name, const char* package_var_name, double value,
    int32_t* exception_flag, const char* file, int32_t line);


=head2 set_package_var_object_by_name


  void (*set_package_var_object_by_name)(SPVM_ENV* env, const char* package_name, const char* package_var_name, const char* signature, void* value,
    int32_t* exception_flag, const char* file, int32_t line);


=head2 get_package_var_byte_by_name


  int8_t (*get_package_var_byte_by_name)(SPVM_ENV* env, const char* package_name, const char* package_var_name,
    int32_t* exception_flag, const char* file, int32_t line);


=head2 get_package_var_short_by_name


  int16_t (*get_package_var_short_by_name)(SPVM_ENV* env, const char* package_name, const char* package_var_name,
    int32_t* exception_flag, const char* file, int32_t line);


=head2 get_package_var_int_by_name


  int32_t (*get_package_var_int_by_name)(SPVM_ENV* env, const char* package_name, const char* package_var_name,
    int32_t* exception_flag, const char* file, int32_t line);


=head2 get_package_var_long_by_name


  int64_t (*get_package_var_long_by_name)(SPVM_ENV* env, const char* package_name, const char* package_var_name,
    int32_t* exception_flag, const char* file, int32_t line);


=head2 get_package_var_float_by_name


  float (*get_package_var_float_by_name)(SPVM_ENV* env, const char* package_name, const char* package_var_name,
    int32_t* exception_flag, const char* file, int32_t line);


=head2 get_package_var_double_by_name


  double (*get_package_var_double_by_name)(SPVM_ENV* env, const char* package_name, const char* package_var_name,
    int32_t* exception_flag, const char* file, int32_t line);


=head2 get_package_var_object_by_name


  void* (*get_package_var_object_by_name)(SPVM_ENV* env, const char* package_name, const char* package_var_name, const char* signature,
    int32_t* exception_flag, const char* file, int32_t line);


=head2 call_sub_by_name


  int32_t (*call_sub_by_name)(SPVM_ENV* env, const char* package_name, const char* sub_name, const char* signature, SPVM_VALUE* stack,
    const char* file, int32_t line);


=head2 call_poly_sub_by_name


  int32_t (*call_poly_sub_by_name)(SPVM_ENV* env, void* object, const char* sub_name, const char* signature, SPVM_VALUE* stack,
    const char* file, int32_t line);


=head2 get_field_string_chars_by_name


  const char* (*get_field_string_chars_by_name)(SPVM_ENV* env, void* obj, const char* package_name, const char* field_name,
    int32_t* exception_flag, const char* file, int32_t line);


=head2 any_object_basic_type_id

  void* any_object_basic_type_id;

=head2 dump_raw

  void* (*dump_raw)(SPVM_ENV* env, void* object);

=head2 any_object_basic_type_id

  void* (*dump)(SPVM_ENV* env, void* object);

=head1 Native API indexes

Native APIs have indexes which correspond to the names. These indexes are permanently same for the binary compatibility. When a new Native API is added, it will be added to the end.

  0 package_vars_heap
  1 object_header_byte_size
  2 object_weaken_backref_head_offset
  3 object_ref_count_offset
  4 object_basic_type_id_offset
  5 object_type_dimension_offset
  6 object_type_category_offset
  7 object_flag_offset
  8 object_length_offset
  9 byte_object_basic_type_id
  10 short_object_basic_type_id
  11 int_object_basic_type_id
  12 long_object_basic_type_id
  13 float_object_basic_type_id
  14 double_object_basic_type_id
  15 compiler
  16 exception_object
  17 native_mortal_stack
  18 native_mortal_stack_top
  19 native_mortal_stack_capacity
  20 get_basic_type_id
  21 get_field_id
  22 get_field_offset
  23 get_package_var_id
  24 get_sub_id
  25 get_sub_id_by_object
  26 new_object_raw
  27 new_object
  28 new_byte_array_raw
  29 new_byte_array
  30 new_short_array_raw
  31 new_short_array
  32 new_int_array_raw
  33 new_int_array
  34 new_long_array_raw
  35 new_long_array
  36 new_float_array_raw
  37 new_float_array
  38 new_double_array_raw
  39 new_double_array
  40 new_object_array_raw
  41 new_object_array
  42 new_muldim_array_raw
  43 new_muldim_array
  44 new_mulnum_array_raw
  45 new_mulnum_array
  46 new_string_nolen_raw
  47 new_string_nolen
  48 new_string_raw
  49 new_string
  50 new_pointer_raw
  51 new_pointer
  52 concat_raw
  53 concat
  54 new_stack_trace_raw
  55 new_stack_trace
  56 length
  57 get_elems_byte
  58 get_elems_short
  59 get_elems_int
  60 get_elems_long
  61 get_elems_float
  62 get_elems_double
  63 get_elem_object
  64 set_elem_object
  65 get_field_byte
  66 get_field_short
  67 get_field_int
  68 get_field_long
  69 get_field_float
  70 get_field_double
  71 get_field_object
  72 set_field_byte
  73 set_field_short
  74 set_field_int
  75 set_field_long
  76 set_field_float
  77 set_field_double
  78 set_field_object
  79 get_package_var_byte
  80 get_package_var_short
  81 get_package_var_int
  82 get_package_var_long
  83 get_package_var_float
  84 get_package_var_double
  85 get_package_var_object
  86 set_package_var_byte
  87 set_package_var_short
  88 set_package_var_int
  89 set_package_var_long
  90 set_package_var_float
  91 set_package_var_double
  92 set_package_var_object
  93 get_pointer
  94 set_pointer
  95 call_sub
  96 get_exception
  97 set_exception
  98 get_ref_count
  99 inc_ref_count
  100 dec_ref_count
  101 enter_scope
  102 push_mortal
  103 leave_scope
  104 remove_mortal
  105 is_type
  106 has_callback
  107 get_object_basic_type_id
  108 get_object_type_dimension
  109 weaken
  110 isweak
  111 unweaken
  112 alloc_memory_block_zero
  113 free_memory_block
  114 get_memory_blocks_count
  115 get_type_name_raw
  116 get_type_name
  117 new_env
  118 free_env
  119 memory_blocks_count
  120 get_chars
  121 die
  122 new_object_by_name
  123 new_pointer_by_name
  124 set_field_byte_by_name
  125 set_field_short_by_name
  126 set_field_int_by_name
  127 set_field_long_by_name
  128 set_field_float_by_name
  129 set_field_double_by_name
  130 set_field_object_by_name
  131 get_field_byte_by_name
  132 get_field_short_by_name
  133 get_field_int_by_name
  134 get_field_long_by_name
  135 get_field_float_by_name
  136 get_field_double_by_name
  137 get_field_object_by_name
  138 set_package_var_byte_by_name
  139 set_package_var_short_by_name
  140 set_package_var_int_by_name
  141 set_package_var_long_by_name
  142 set_package_var_float_by_name
  143 set_package_var_double_by_name
  144 set_package_var_object_by_name
  145 get_package_var_byte_by_name
  146 get_package_var_short_by_name
  147 get_package_var_int_by_name
  148 get_package_var_long_by_name
  149 get_package_var_float_by_name
  150 get_package_var_double_by_name
  151 get_package_var_object_by_name
  152 call_sub_by_name
  153 call_poly_sub_by_name
  154 get_field_string_chars_by_name
  155 any_object_basic_type_id
  156 dump_raw
  157 dump

=head1 Examples

=over 2

=item * L<Examples using SPVM Native APIs|https://github.com/yuki-kimoto/SPVM/tree/master/examples/native>

=back


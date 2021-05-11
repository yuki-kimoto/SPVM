=head1 NAME

SPVM::Document::NativeAPI - SPVM Native API

=head1 DESCRIPTION

SPVM Native API is C APIs used in APIs SPVM Native Subroutine.

=head1 SPVM NATIVE API

=begin html

<h2>SPVM Native API</h2>

SPVM Native API is C API which can be used in SPVM Native Subroutine. SPVM Native API is a part of SPVM Specification.

<ul class="toc">
  <li><a href="#native-api-summary">What is SPVM Native API</a></li>
  <li><a href="#native-api-native-sub-declaration">SPVM Native Subroutine Declaration</a></li>
  <li><a href="#native-api-native-configuration">SPVM Native Config File</a></li>
  <li><a href="#native-api-native-sub-definition">SPVM Native Subroutine Definition</a></li>
  <li><a href="#native-api-native-sub-compile">Compile Native Subroutine</a></li>
  <li><a href="#native-api-native-sub-get-arg">Arguments of Native Subroutine</a></li>
  <li><a href="#native-api-native-sub-set-retval">Return Value of Native Subroutine</a></li>
  <li><a href="#native-api-native-call-sub">Call SPVM Subroutine</a></li>
  <li><a href="#native-api-native-sub-scope">Native Subroutine Scope</a></li>
  <li><a href="#native-api-native-sub-exception">Exception of Native Subroutine</a></li>
  <li><a href="#native-api-use-pointer-type">Pointer Type</a></li>
  <li><a href="#native-api-list">List of Native APIs</a></li>
</ul>
  
<h3 id="native-api-summary">What is the SPVM Native API?</h3>

<b>SPVM Native API</b> is C API which can be used in SPVM Native Subroutine.

<ul>
  <li><a href="#native-api-list">List of SPVM Native APIs</a></li>
</ul>

In this document, in addition to SPVM Native API, <a href="#native-api-native-sub-declaration">SPVM Native Subroutine Declaration</a>, <a href="#native-api-native-sub-definition">SPVM Native Subroutine Definition</a>, How to receive Arguments, How to return value is described.

<h3 id="native-api-native-sub-declaration">SPVM Native Subroutine Declaration</h3>

<b>SPVM Native Subroutine Declaration</b> is written using Subroutine Descriptor "native" in SPVM module file.

<pre>
# Foo/Bar.spvm
package Foo::Bar {
  native sub sum : int ($num1 : int, $num2 : int);
}
</pre>

SPVM Native Subroutine Declaration ends with a semicolon without Sobroutine Block.

Multiple Native Subroutines can be declared. Normal Subroutine can be defined with Native Subroutine.

<pre>
# Foo/Bar.spvm
package Foo::Bar {
  native sub sum : int ($num1 : int, $num2 : int);
  
  natvie sub native_foo : long ($num : long);
  
  sub bar : int ($num : int) {
    return $num * 2;
  }
}
</pre>

<h3 id="native-api-native-configuration">SPVM Native Config File</h3>

<b>SPVM Native Config File</b> must be created for SPVM Native Subroutine. The base name of native configuration file is same as SPVM module file. the extesion is ".config".

<pre>
# Native configuration file for Foo::Bar module
Foo/Bar.config
</pre>

If native configuration file does not exist, an exception is raised.

Native Config File is Perl source code. Native Config File must return properly <a href="https://metacpan.org/pod/SPVM::Builder::Config">SPVM::Builder:Config</a> object, otherwise an exception occurs.

<b>1. C99 SPVM Native Config File Example</b>

An example native source code written by C (C99 is SPVM default).
 
<pre>
# C99 SPVM Native Config File
use strict;
use warnings;

use SPVM::Builder::Config;
my $bconf = SPVM::Builder::Config->new_c99;

$bconf;
</pre>

<b>2. C11 SPVM Native Config File Example</b>

<pre>
# C11 SPVM Native Config File
use strict;
use warnings;

use SPVM::Builder::Config;
my $bconf = SPVM::Builder::Config->new_c;

$bconf->set_std('c11');

$bconf;
</pre>

<b>3. C++ SPVM Native Config File Example</b>

<pre>
# C++ SPVM Native Config File
use strict;
use warnings;

use SPVM::Builder::Config;
my $bconf = SPVM::Builder::Config->new_cpp;

$bconf;
</pre>

<b>4. C++11 SPVM Native Config File Example</b>

<pre>
# C++11 SPVM Native Config File
use strict;
use warnings;

use SPVM::Builder::Config;
my $bconf = SPVM::Builder::Config->new_cpp;

$bconf->set_std('c++11');

$bconf;
</pre>

<b>5. CUDA/nvcc SPVM Native Config File Example</b>

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

<h3 id="native-api-native-sub-definition">Native Subroutine Definition</h3>

Native Subroutine Definition is written in native source file. native source file is basically C language source file which extension is ".c". This extension can be changed to ".cpp" for C++ source file, to ".cu" for CUDA source file, etc.

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

<h4>Include spvm_native.h</h4>

Include "spvm_native.h" at the beginning of the native source file. This header file defines SPVM Native APIs and data structures for Native API and useful macro functions.

See <a href="#native-api-list">List of SPVM Native APIs</a> about included SPVM Native APIs by this header.

spvm_native.h include the following data structures.

<pre>
SPVM_ENV
SPVM_VALUE
</pre>

See <a href="#native-api-list">List of SPVM Native APIs</a> about included SPVM Native APIs by this header.

See <a href="#native-api-list">List of SPVM Native APIs</a> about included SPVM Native APIs by this header.

<h4>Return Value</h4>

The return type is "int32_t". If the subroutine raises an exception, "1" is returned, otherwise "0" is returned.

<h4>Function Name</h4>

Native Subroutine Definition is a simple C language function such as

<pre>
SPNATIVE__Foo__Bar__sum
</pre>

The function name starts with "SPNATIVE__".

Followed by package name "Foo__Bar", which is replaced "::" in Foo::Bar.

Followed by "__".

Followed by subroutine name "sum".

If Native Subroutine Name is invalid, a compile error will occur.


  <p>
    There are two arguments, the first argument is "SPVM_ENV* env" which has the information of the execution environment, and the second argument is "SPVM_VALUE* stack" which is used for the argument and return value.
  </p>
  <p>
  </p>
  <p>
    In the above sample, it takes two int type arguments of SPVM, calculates the sum, and returns the return value.
  </p>
  
  <h3 id="native-api-native-sub-compile">Compile Native Subroutine</h3>
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
    If you want to use SPVM Native Subroutine from Perl, create a "~/.spvm_build" directory in the directory where the executed Perl script exists.
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

  <h3 id="native-api-native-sub-get-arg">Arguments</h3>
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
  
<h4 href = "# native-api-native-sub-get-arg-stack">Arguments and Stack</h4>
  <p>
    The stack is the "SPVM_VALUE* stack" passed as the second argument in the definition of the Native Subroutine, and the arguments are stored in this.
  </p>
<pre>
int32_t SPNATIVE__Foo__Bar__sum(SPVM_ENV* env, SPVM_VALUE* stack) {

}
</pre>
  <p>
    SPVM_VALUE is a C language union for storing SPVM values. You can save numeric, object, and reference values.
  </p>
  <p>
    Pointer to the beginning of the "SPVM_VALUE type array" of "SPVM_VALUE* stack". The value of the argument of the Native Subroutine called from SPVM side is set in this array.
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

<h4 id="native-api-native-sub-get-arg-byte">Get byte type argument</h4>
  <p>
    To get the SPVM byte argument, access the bval field. Assign to the C language int8_t type.
  </p>
<pre>
int8_t args0 = stack[0].bval;
</pre>

<h4 id="native-api-native-sub-get-arg-short">Get short type argument</h4>
  <p>
    To get the short argument of SPVM, access the sval field. Assign it to the C language int16_t type.
  </p>
<pre>
int16_t args0 = stack[0].sval;
</pre>

<h4 id="native-api-native-sub-get-arg-int">Get int type argument</h4>
  <p>
    To get the SPVM int type argument, access the ival field. Assign to the C language int32_t type.
  </p>
<pre>
int32_t args0 = stack[0].ival;
</pre>

<h4 id="native-api-native-sub-get-arg-long">Get long type argument</h4>
  <p>
    To get the long argument of SPVM, access the lval field. Assign to the C language int64_t type.
  </p>
<pre>
int64_t args0 = stack[0].lval;
</pre>

<h4 id="native-api-native-sub-get-arg-float">Get float type argument</h4>
  <p>
    To get the SPVM float type argument, access the fval field. Assign to float type of C language.
  </p>
<pre>
float args0 = stack[0].fval;
</pre>

<h4 id="native-api-native-sub-get-arg-double">Get double type argument</h4>
  <p>
    To get the SPVM double argument, access the dval field. Assign to the C language double type.
  </p>
<pre>
double args0 = stack[0].dval;
</pre>

<h4 id="native-api-native-sub-get-arg-object">Get object type argument</h4>
  <p>
    To get the SPVM object type argument, access the oval field. Assign it to void* type in C language.
  </p>
<pre>
void* args0 = stack[0].oval;
</pre>

<h4 id="native-api-native-sub-get-arg-byte-ref">Get byte Reference Type Argument</h4>

If you get SPVM byte Reference Type argument, use "bref" field. it can be assinged to the value of C language int8_t* type.

<pre>
int8_t* args0 = stack[0].bref;
</pre>

<h4 id="native-api-native-sub-get-arg-short">Get short Reference Type Argument</h4>

If you get SPVM short Reference Type argument, use "sref" field. it can be assinged to the value of C language int16_t* type.

<pre>
int16_t* args0 = stack[0].sref;
</pre>

<h4 id="native-api-native-sub-get-arg-int">Get int Reference Type Argument</h4>

If you get SPVM int Reference Type argument, use "iref" field. it can be assinged to the value of C language int32_t* type.

<pre>
int32_t* args0 = stack[0].iref;
</pre>

<h4 id="native-api-native-sub-get-arg-long">Get long Reference Type Argument</h4>

If you get SPVM long Reference Type argument, use "lref" field. it can be assinged to the value of C language int64_t* type.

<pre>
int64_t* args0 = stack[0].lref;
</pre>

<h4 id="native-api-native-sub-get-arg-float">Get float Reference Type Argument</h4>

If you get SPVM float Reference Type argument, use "fref" field. it can be assinged to the value of C language float* type.

<pre>
float* args0 = stack[0].fref;
</pre>

<h4 id="native-api-native-sub-get-arg-double">Get double Reference Type Argument</h4>

If you get SPVM double Reference Type Argument, use "dref" field. it can be assinged to the value of C language double* type.

<pre>
double* args0 = stack[0].dref;
</pre>

<h4 id="native-api-native-sub-get-arg-mulnum">Get multiple numeric type arguments</h4>
  <p>
    In a Native Subroutine, multiple numeric type arguments are assigned to multiple arguments.
  </p>
  <p>
    For example, in the case of the argument of SPVM::Complex_2d type, it gets from two arguments. Note that you cannot access it by field name.
  </p>
<pre>
double args_re = stack[0].dval;
double args_im = stack[1].dval;
</pre>

  <h3 id="native-api-native-sub-set-retval">Return Value</h3>
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
  
<h4 id="native-api-native-sub-set-retval-stack">Return value and stack</h4>
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

<h4 id="native-api-native-sub-set-retval-byte">Set return value of byte type</h4>
  <p>
    To set the SPVM byte return value, assign it to the bval field. Assigns a value of type int8_t in C language.
  </p>
<pre>
int8_t retval;
stack[0].bval = retval;
</pre>

<h4 id="native-api-native-sub-set-retval-short">Set return value of short type</h4>
  <p>
    To set the SPVM short return value, assign it to the sval field. Assigns a C language int16_t type value.
  </p>
<pre>
int16_t retval;
stack[0].sval = retval;
</pre>

<h4 id="native-api-native-sub-set-retval-int">Set return value of int type</h4>
  <p>
    To set the SPVM int return value, assign it to the ival field. Assigns a C language int32_t type value.
  </p>
<pre>
int32_t retval;
stack[0].ival = retval;
</pre>

<h4 id="native-api-native-sub-set-retval-long">Set long type return value</h4>
  <p>
    To set the SPVM long return value, assign it to the lval field. Assigns a value of C language int64_t type.
  </p>
<pre>
int64_t retval;
stack[0].lval = retval;
</pre>

<h4 id="native-api-native-sub-set-retval-float">Set return value of float type</h4>
  <p>
    To set the SPVM float return value, assign it to the fval field. Substitutes a C type float type value.
  </p>
<pre>
float retval;
stack[0].fval = retval;
</pre>

<h4 id="native-api-native-sub-set-retval-double">Set return value of double type</h4>
  <p>
    To set the SPVM double return value, assign it to the dval field. Assigns a C type double value.
  </p>
<pre>
double retval;
</pre>

<h4 id="native-api-native-sub-set-retval-object">Set return value of object type</h4>
  <p>
    To set the return value of the SPVM object type, assign it to the oval field. Assign a value of void* type in C language.
  </p>
<pre>
void* retval;
stack[0].oval = retval;
</pre>

<h4 id="native-api-native-sub-set-retval-mulnum">Set multiple numeric return value</h4>
  <p>
    In a Native Subroutine, multiple numeric return values assigned to multiple return values.
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

  <h3 id="native-api-native-call-sub">Call SPVM Subroutine</h3>
  <p>
    To call the SPVM subroutine, first use the <a href="#native-api-native-sub-api-sub_id">sub_id</a> function or the <a href = "# native-api-native- Get the ID of the subroutine using the sub-api-method_sub_id ">method_sub_id</a> function
  </p>
<pre>
// For a subroutine that is not a method
int32_t sub_id = env->get_sub_id(env, "Foo", "sum", "int (int, int)");

// For method
int32_t sub_id = env->get_method_sub_id(env, object, "sum", "int (self, int, int)");
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

  <h3 id="native-api-native-sub-scope">Native Subroutine Scope</h3>
  <p>
    Native subroutine are entirely enclosed in scope.
  </p>
  <p>
    Objects added to the mortal stack will automatically have their reference count decremented by 1 when the Native Subroutine ends. When the reference count reaches 0, it is released.
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

  <h3 id="native-api-native-sub-exception">Exception in Native Subroutine</h3>
  <p>
    In the Native Subroutine, it is the return value that indicates whether an exception has occurred.
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

  <h3 id="native-api-use-pointer-type">Pointer Type</h3>
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
    It defines a new constructor, a method that takes seconds information called sec, and a destructor called DESTROY. These are Native Subroutine.
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

  <h3 id="native-api-index">Native API index</h3>
  <p>
    The Native API has an index that corresponds to the name. This number is permanently maintained for binary compatibility with Native Subroutine. When adding a new API, it will be added at the end.
  </p>

<pre>
0 package_vars_heap
1 object_header_byte_size
2 object_weaken_backref_head_offset
3 object_ref_count_offset
4 object_basic_type_id_offset
5 object_type_dimension_offset
6 object_runtime_type_category_offset
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
25 get_method_sub_id
26 new_object_raw
27 new_object
28 new_byte_array_raw
29 new_byte_array
30 new_short_array_raw
31 new_short_array
32 new_int_array_raw
33 new_int_array
34 new_long_array_raw
35 new_long_array36    new_float_array_raw
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
119 memry_blocks_count
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
154 get_field_string_chars_by_name
155 any_object_basic_type_id
</pre>

  <h3 id="native-api-call">Call Native API</h3>
  <p>
    Native API can be called from "SPVM_ENV* env" passed as an argument. Note that you have to pass env as the first argument.
  </p>
<pre>
int32_t basic_type_id = env->get_basic_type_id(env, "SPVM::Int");
</pre>
  
  <h3 id="native-api-list">List of Native APIs</h3>
  <ul>
    <li><a href="#native-api-native-sub-api-runtime_package_vars_heap_offset">package_vars_heap</a></li>
    <li><a href="#native-api-native-sub-api-object_header_byte_size">object_header_byte_size</a></li>
    <li><a href="#native-api-native-sub-api-object_weaken_backref_head_offset">object_weaken_backref_head_offset</a></li>
    <li><a href="#native-api-native-sub-api-object_ref_count_offset">object_ref_count_offset</a></li>
    <li><a href="#native-api-native-sub-api-object_basic_type_id_offset">object_basic_type_id_offset</a></li>
    <li><a href="#native-api-native-sub-api-object_type_dimension_offset">object_type_dimension_offset</a></li>
    <li><a href="#native-api-native-sub-api-object_runtime_type_category_offset">object_runtime_type_category_offset</a></li>
    <li><a href="#native-api-native-sub-api-object_flag_offset">object_flag_offset</a></li>
    <li><a href="#native-api-native-sub-api-object_length_offset">object_length_offset</a></li>
    <li><a href="#native-api-native-sub-api-byte_object_basic_type_id">byte_object_basic_type_id</a></li>
    <li><a href="#native-api-native-sub-api-short_object_basic_type_id">short_object_basic_type_id</a></li>
    <li><a href="#native-api-native-sub-api-int_object_basic_type_id">int_object_basic_type_id</a></li>
    <li><a href="#native-api-native-sub-api-long_object_basic_type_id">long_object_basic_type_id</a></li>
    <li><a href="#native-api-native-sub-api-float_object_basic_type_id">float_object_basic_type_id</a></li>
    <li><a href="#native-api-native-sub-api-double_object_basic_type_id">double_object_basic_type_id</a></li>
    <li><a href="#native-api-native-sub-api-compiler">compiler</a></li>
    <li><a href="#native-api-native-sub-api-exception_object">exception_object</a></li>
    <li><a href="#native-api-native-sub-api-native_mortal_stack">native_mortal_stack</a></li>
    <li><a href="#native-api-native-sub-api-native_mortal_stack_top">native_mortal_stack_top</a></li>
    <li><a href="#native-api-native-sub-api-native_mortal_stack_capacity">native_mortal_stack_capacity</a></li>
    <li><a href="#native-api-native-sub-api-get_basic_type_id">get_basic_type_id</a></li>
    <li><a href="#native-api-native-sub-api-get_field_id">get_field_id</a></li>
    <li><a href="#native-api-native-sub-api-get_field_offset">get_field_offset</a></li>
    <li><a href="#native-api-native-sub-api-get_package_var_id">get_package_var_id</a></li>
    <li><a href="#native-api-native-sub-api-get_sub_id">get_sub_id</a></li>
    <li><a href="#native-api-native-sub-api-get_method_sub_id">get_method_sub_id</a></li>
    <li><a href="#native-api-native-sub-api-new_object_raw">new_object_raw</a></li>
    <li><a href="#native-api-native-sub-api-new_object">new_object</a></li>
    <li><a href="#native-api-native-sub-api-new_byte_array_raw">new_byte_array_raw</a></li>
    <li><a href="#native-api-native-sub-api-new_byte_array">new_byte_array</a></li>
    <li><a href="#native-api-native-sub-api-new_short_array_raw">new_short_array_raw</a></li>
    <li><a href="#native-api-native-sub-api-new_short_array">new_short_array</a></li>
    <li><a href="#native-api-native-sub-api-new_int_array_raw">new_int_array_raw</a></li>
    <li><a href="#native-api-native-sub-api-new_int_array">new_int_array</a></li>
    <li><a href="#native-api-native-sub-api-new_long_array_raw">new_long_array_raw</a></li>
    <li><a href="#native-api-native-sub-api-new_long_array">new_long_array</a></li>
    <li><a href="#native-api-native-sub-api-new_float_array_raw">new_float_array_raw</a></li>
    <li><a href="#native-api-native-sub-api-new_float_array">new_float_array</a></li>
    <li><a href="#native-api-native-sub-api-new_double_array_raw">new_double_array_raw</a></li>
    <li><a href="#native-api-native-sub-api-new_double_array">new_double_array</a></li>
    <li><a href="#native-api-native-sub-api-new_object_array_raw">new_object_array_raw</a></li>
    <li><a href="#native-api-native-sub-api-new_object_array">new_object_array</a></li>
    <li><a href="#native-api-native-sub-api-new_muldim_array_raw">new_muldim_array_raw</a></li>
    <li><a href="#native-api-native-sub-api-new_muldim_array">new_muldim_array</a></li>
    <li><a href="#native-api-native-sub-api-new_mulnum_array_raw">new_mulnum_array_raw</a></li>
    <li><a href="#native-api-native-sub-api-new_mulnum_array">new_mulnum_array</a></li>
    <li><a href="#native-api-native-sub-api-new_string_nolen_raw">new_string_nolen_raw</a></li>
    <li><a href="#native-api-native-sub-api-new_string_nolen">new_string_nolen</a></li>
    <li><a href="#native-api-native-sub-api-new_string_raw">new_string_raw</a></li>
    <li><a href="#native-api-native-sub-api-new_string">new_string</a></li>
    <li><a href="#native-api-native-sub-api-new_pointer_raw">new_pointer_raw</a></li>
    <li><a href="#native-api-native-sub-api-new_pointer">new_pointer</a></li>
    <li><a href="#native-api-native-sub-api-concat_raw">concat_raw</a></li>
    <li><a href="#native-api-native-sub-api-concat">concat</a></li>
    <li><a href="#native-api-native-sub-api-new_stack_trace_raw">new_stack_trace_raw</a></li>
    <li><a href="#native-api-native-sub-api-new_stack_trace">new_stack_trace</a></li>
    <li><a href="#native-api-native-sub-api-length">length</a></li>
    <li><a href="#native-api-native-sub-api-get_elems_byte">get_elems_byte</a></li>
    <li><a href="#native-api-native-sub-api-get_elems_short">get_elems_short</a></li>
    <li><a href="#native-api-native-sub-api-get_elems_int">get_elems_int</a></li>
    <li><a href="#native-api-native-sub-api-get_elems_long">get_elems_long</a></li>
    <li><a href="#native-api-native-sub-api-get_elems_float">get_elems_float</a></li>
    <li><a href="#native-api-native-sub-api-get_elems_double">get_elems_double</a></li>
    <li><a href="#native-api-native-sub-api-get_elem_object">get_elem_object</a></li>
    <li><a href="#native-api-native-sub-api-set_elem_object">set_elem_object</a></li>
    <li><a href="#native-api-native-sub-api-get_field_byte">get_field_byte</a></li>
    <li><a href="#native-api-native-sub-api-get_field_short">get_field_short</a></li>
    <li><a href="#native-api-native-sub-api-get_field_int">get_field_int</a></li>
    <li><a href="#native-api-native-sub-api-get_field_long">get_field_long</a></li>
    <li><a href="#native-api-native-sub-api-get_field_float">get_field_float</a></li>
    <li><a href="#native-api-native-sub-api-get_field_double">get_field_double</a></li>
    <li><a href="#native-api-native-sub-api-get_field_object">get_field_object</a></li>
    <li><a href="#native-api-native-sub-api-set_field_byte">set_field_byte</a></li>
    <li><a href="#native-api-native-sub-api-set_field_short">set_field_short</a></li>
    <li><a href="#native-api-native-sub-api-set_field_int">set_field_int</a></li>
    <li><a href="#native-api-native-sub-api-set_field_long">set_field_long</a></li>
    <li><a href="#native-api-native-sub-api-set_field_float">set_field_float</a></li>
    <li><a href="#native-api-native-sub-api-set_field_double">set_field_double</a></li>
    <li><a href="#native-api-native-sub-api-set_field_object">set_field_object</a></li>
    <li><a href="#native-api-native-sub-api-get_package_var_byte">get_package_var_byte</a></li>
    <li><a href="#native-api-native-sub-api-get_package_var_short">get_package_var_short</a></li>
    <li><a href="#native-api-native-sub-api-get_package_var_int">get_package_var_int</a></li>
    <li><a href="#native-api-native-sub-api-get_package_var_long">get_package_var_long</a></li>
    <li><a href="#native-api-native-sub-api-get_package_var_float">get_package_var_float</a></li>
    <li><a href="#native-api-native-sub-api-get_package_var_double">get_package_var_double</a></li>
    <li><a href="#native-api-native-sub-api-get_package_var_object">get_package_var_object</a></li>
    <li><a href="#native-api-native-sub-api-set_package_var_byte">set_package_var_byte</a></li>
    <li><a href="#native-api-native-sub-api-set_package_var_short">set_package_var_short</a></li>
    <li><a href="#native-api-native-sub-api-set_package_var_int">set_package_var_int</a></li>
    <li><a href="#native-api-native-sub-api-set_package_var_long">set_package_var_long</a></li>
    <li><a href="#native-api-native-sub-api-set_package_var_float">set_package_var_float</a></li>
    <li><a href="#native-api-native-sub-api-set_package_var_double">set_package_var_double</a></li>
    <li><a href="#native-api-native-sub-api-set_package_var_object">set_package_var_object</a></li>
    <li><a href="#native-api-native-sub-api-get_pointer">get_pointer</a></li>
    <li><a href="#native-api-native-sub-api-set_pointer">set_pointer</a></li>
    <li><a href="#native-api-native-sub-api-call_sub">call_sub</a></li>
    <li><a href="#native-api-native-sub-api-get_exception">get_exception</a></li>
    <li><a href="#native-api-native-sub-api-set_exception">set_exception</a></li>
    <li><a href="#native-api-native-sub-api-get_ref_count">get_ref_count</a></li>
    <li><a href="#native-api-native-sub-api-inc_ref_count">inc_ref_count</a></li>
    <li><a href="#native-api-native-sub-api-dec_ref_count">dec_ref_count</a></li>
    <li><a href="#native-api-native-sub-api-enter_scope">enter_scope</a></li>
    <li><a href="#native-api-native-sub-api-push_mortal">push_mortal</a></li>
    <li><a href="#native-api-native-sub-api-leave_scope">leave_scope</a></li>
    <li><a href="#native-api-native-sub-api-remove_mortal">remove_mortal</a></li>
    <li><a href="#native-api-native-sub-api-is_type">is_type</a></li>
    <li><a href="#native-api-native-sub-api-has_callback">has_callback</a></li>
    <li><a href="#native-api-native-sub-api-get_object_basic_type_id">get_object_basic_type_id</a></li>
    <li><a href="#native-api-native-sub-api-get_object_type_dimension">get_object_type_dimension</a></li>
    <li><a href="#native-api-native-sub-api-weaken">weaken</a></li>
    <li><a href="#native-api-native-sub-api-isweak">isweak</a></li>
    <li><a href="#native-api-native-sub-api-unweaken">unweaken</a></li>
    <li><a href="#native-api-native-sub-api-alloc_memory_block_zero">alloc_memory_block_zero</a></li>
    <li><a href="#native-api-native-sub-api-free_memory_block">free_memory_block</a></li>
    <li><a href="#native-api-native-sub-api-get_memory_blocks_count">get_memory_blocks_count</a></li>
    <li><a href="#native-api-native-sub-api-get_type_name_raw">get_type_name_raw</a></li>
    <li><a href="#native-api-native-sub-api-get_type_name">get_type_name</a></li>
    <li><a href="#native-api-native-sub-api-new_env">new_env</a></li>
    <li><a href="#native-api-native-sub-api-free_env">free_env</a></li>
    <li><a href="#native-api-native-sub-api-memry_blocks_count">memry_blocks_count</a></li>
    <li><a href="#native-api-native-sub-api-get_chars">get_chars</a></li>
    <li><a href="#native-api-native-sub-api-die">die</a></li>
    <li><a href="#native-api-native-sub-api-new_object_by_name">new_object_by_name</a></li>
    <li><a href="#native-api-native-sub-api-new_pointer_by_name">new_pointer_by_name</a></li>
    <li><a href="#native-api-native-sub-api-set_field_byte_by_name">set_field_byte_by_name</a></li>
    <li><a href="#native-api-native-sub-api-set_field_short_by_name">set_field_short_by_name</a></li>
    <li><a href="#native-api-native-sub-api-set_field_int_by_name">set_field_int_by_name</a></li>
    <li><a href="#native-api-native-sub-api-set_field_long_by_name">set_field_long_by_name</a></li>
    <li><a href="#native-api-native-sub-api-set_field_float_by_name">set_field_float_by_name</a></li>
    <li><a href="#native-api-native-sub-api-set_field_double_by_name">set_field_double_by_name</a></li>
    <li><a href="#native-api-native-sub-api-set_field_object_by_name">set_field_object_by_name</a></li>
    <li><a href="#native-api-native-sub-api-get_field_byte_by_name">get_field_byte_by_name</a></li>
    <li><a href="#native-api-native-sub-api-get_field_short_by_name">get_field_short_by_name</a></li>
    <li><a href="#native-api-native-sub-api-get_field_int_by_name">get_field_int_by_name</a></li>
    <li><a href="#native-api-native-sub-api-get_field_long_by_name">get_field_long_by_name</a></li>
    <li><a href="#native-api-native-sub-api-get_field_float_by_name">get_field_float_by_name</a></li>
    <li><a href="#native-api-native-sub-api-get_field_double_by_name">get_field_double_by_name</a></li>
    <li><a href="#native-api-native-sub-api-get_field_object_by_name">get_field_object_by_name</a></li>
    <li><a href="#native-api-native-sub-api-set_package_var_byte_by_name">set_package_var_byte_by_name</a></li>
    <li><a href="#native-api-native-sub-api-set_package_var_short_by_name">set_package_var_short_by_name</a></li>
    <li><a href="#native-api-native-sub-api-set_package_var_int_by_name">set_package_var_int_by_name</a></li>
    <li><a href="#native-api-native-sub-api-set_package_var_long_by_name">set_package_var_long_by_name</a></li>
    <li><a href="#native-api-native-sub-api-set_package_var_float_by_name">set_package_var_float_by_name</a></li>
    <li><a href="#native-api-native-sub-api-set_package_var_double_by_name">set_package_var_double_by_name</a></li>
    <li><a href="#native-api-native-sub-api-set_package_var_object_by_name">set_package_var_object_by_name</a></li>
    <li><a href="#native-api-native-sub-api-get_package_var_byte_by_name">get_package_var_byte_by_name</a></li>
    <li><a href="#native-api-native-sub-api-get_package_var_short_by_name">get_package_var_short_by_name</a></li>
    <li><a href="#native-api-native-sub-api-get_package_var_int_by_name">get_package_var_int_by_name</a></li>
    <li><a href="#native-api-native-sub-api-get_package_var_long_by_name">get_package_var_long_by_name</a></li>
    <li><a href="#native-api-native-sub-api-get_package_var_float_by_name">get_package_var_float_by_name</a></li>
    <li><a href="#native-api-native-sub-api-get_package_var_double_by_name">get_package_var_double_by_name</a></li>
    <li><a href="#native-api-native-sub-api-get_package_var_object_by_name">get_package_var_object_by_name</a></li>
    <li><a href="#native-api-native-sub-api-call_sub_by_name">call_sub_by_name</a></li>
    <li><a href="#native-api-native-sub-api-call_poly_sub_by_name">call_poly_sub_by_name</a></li>
    <li><a href="#native-api-native-sub-api-get_field_string_chars_by_name">get_field_string_chars_by_name</a></li>
    <li><a href="#native-api-native-sub-api-any_object_basic_type_id">any_object_basic_type_id</a></li>
  </ul>
<h4 id="native-api-native-sub-api-package_vars_heap">package_vars_heap</h4>
  <p>
    the pointer to the storage area of the package variables. It is used internally.
  </p>
  
<h4 id="native-api-native-sub-api-object_header_byte_size">object_header_byte_size</h4>
  <p>
    The byte size of the object's header. It is used internally.
  </p>
  
<h4 id="native-api-native-sub-api-object_weaken_backref_head_offset">object_weaken_backref_head_offset</h4>
  <p>
    Offset to a pointer to the back reference of the weak reference in the object structure. It is used internally.
  </p>
  
<h4 id="native-api-native-sub-api-object_ref_count_offset">object_ref_count_offset</h4>
  <p>
    Reference count offset in the object structure. It is used internally.
  </p>
  
<h4 id="native-api-native-sub-api-object_basic_type_id_offset">object_basic_type_id_offset</h4>
  <p>
    Offset of basic type ID in object structure. It is used internally.
  </p>
  
<h4 id="native-api-native-sub-api-object_type_dimension_offset">object_type_dimension_offset</h4>
  <p>
    Offset of type dimension in object structure. It is used internally.
  </p>
  
<h4 id="native-api-native-sub-api-object_runtime_type_category_offset">object_runtime_type_category_offset</h4>
  <p>
    Offset of runtime type category in object structure. It is used internally.
  </p>
  
<h4 id="native-api-native-sub-api-object_flag_offset">object_flag_offset</h4>
  <p>
    Offset of flag in object structure. It is used internally.
  </p>
  
<h4 id="native-api-native-sub-api-object_length_offset">object_length_offset</h4>
  <p>
    The length offset in the object structure. It is used internally.
  </p>
  
<h4 id="native-api-native-sub-api-byte_object_basic_type_id">byte_object_basic_type_id</h4>
  <p>
    Basic type ID of SPVM::Byte type. It is used internally.
  </p>
  
<h4 id="native-api-native-sub-api-short_object_basic_type_id">short_object_basic_type_id</h4>
  <p>
    ID of the base type of SPVM::Short type. It is used internally.
  </p>
  
<h4 id="native-api-native-sub-api-int_object_basic_type_id">int_object_basic_type_id</h4>
  <p>
    ID of the base type of SPVM::Int type. It is used internally.
  </p>
  
<h4 id="native-api-native-sub-api-long_object_basic_type_id">long_object_basic_type_id</h4>
  <p>
    ID of the base type of SPVM::Long type. It is used internally.
  </p>
  
<h4 id="native-api-native-sub-api-float_object_basic_type_id">float_object_basic_type_id</h4>
  <p>
    ID of the base type of SPVM::Float type. It is used internally.
  </p>
  
<h4 id="native-api-native-sub-api-double_object_basic_type_id">double_object_basic_type_id</h4>
  <p>
    ID of the base type of SPVM::Double type. It is used internally.
  </p>
  
<h4 id="native-api-native-sub-api-compiler">compiler</h4>
  <p>
    A pointer to the SPVM compiler. It is used internally.
  </p>
  
<h4 id="native-api-native-sub-api-exception_object">exception_object</h4>
  <p>
    Exception object. It is used internally.
  </p>
<p>
<h4 id="native-api-native-sub-api-native_mortal_stack">native_mortal_stack</h4>
  <p>
     Mortal stack used for native calls. It is used internally.
</p>
<h4 id="native-api-native-sub-api-native_mortal_stack_top">native_mortal_stack_top</h4>
  <p>
    The top position of the mortal stack used for native calls. It is used internally.
  </p>
  
<h4 id="native-api-native-sub-api-native_mortal_stack_capacity">native_mortal_stack_capacity</h4>
  <p>
    The amount of mortal stack used for native calls. It is used internally.
  </p>
  
<h4 id="native-api-native-sub-api-get_basic_type_id">get_basic_type_id</h4>
  <p>
    Get the ID of the base type given the name of the base type. If it does not exist, a value less than 0 is returned.
  </p>
<pre>
int32_t (*get_basic_type_id)(SPVM_ENV* env, const char* basic_type_name);
</pre>
  <p>
    Example:
  </p>
<pre>
int32_t basic_type_id = env->get_basic_type_id(env, "SPVM::Int");
</pre>

<h4 id="native-api-native-sub-api-get_field_id">get_field_id</h4>
  <p>
    Get the ID of the field given the package name, field name, and signature. If the field does not exist, a value less than 0 is returned.
  </p>
<pre>
int32_t (*get_field_id)(SPVM_ENV* env, const char* package_name, const char* field_name, const char* signature);
</pre>
  <p>
    The signature is the same as the field type name.
  </p>
  <p>
    Example:
  </p>
<pre>
int32_t field_id = env->get_field_id(env, "Foo", "x", "int");
</pre>
  
<h4 id="native-api-native-sub-api-get_field_offset">get_field_offset</h4>
  <p>
    Gets the offset of the field given the field ID. The field ID must be a valid field ID obtained with the field_id function.
  </p>
<pre>
int32_t (*get_field_offset)(SPVM_ENV* env, int32_t field_id);
</pre>

<h4 id="native-api-native-sub-api-get_package_var_id">get_package_var_id</h4>
  <p>
    Get the package variable ID given the package name, package variable name and signature. If the package variable does not exist, a value less than 0 is returned.
  </p>
<pre>
int32_t (*get_package_var_id)(SPVM_ENV* env, const char* package_name, const char* package_var_name, const char* signature);
</pre>
  <p>
    The signature is the same as the package variable type name.
  </p>
  <p>
    Example:
  </p>
<pre>
int32_t pkgvar_id = env->get_package_var_id(env, "Foo", "$VAR", "int");
</pre>

<h4 id="native-api-native-sub-api-get_sub_id">get_sub_id</h4>
  <p>
    Get the subroutine ID by specifying the package name, subroutine name, and signature. If no subroutine exists, a value less than 0 is returned.
  </p>
<pre>
int32_t (*get_sub_id)(SPVM_ENV* env, const char* package_name, const char* sub_name, const char* signature);
</pre>
  <p>
    The signature has the following format: Must not contain white space.
  </p>
<pre>
Return value type name (argument type name 1, argument type name 2, ...)
</pre>
  <p>
    Example:
  </p>
<pre>
int32_t sub_id = env->get_sub_id(env, "Foo", "func", "int (long, string)");
</pre>

<h4 id="native-api-native-sub-api-get_method_sub_id">get_method_sub_id</h4>
<pre>
int32_t (*get_method_sub_id)(SPVM_ENV* env, void* object, const char* method_name, const char* signature);
</pre>
  <p>
    Get the subroutine ID by specifying the object and method name. If the method does not exist, a value less than 0 is returned.
  </p>
  <p>
    The signature is the same as the sub_id signature.
  </p>
  <p>
    Example:
  </p>
<pre>
int32_t sub_id = env->get_method_sub_id(env, object, "method", "int(self,long,string)");
</pre>

   <h4 id="native-api-native-sub-api-new_object_raw">new_object_raw</h4>
      <p>
        Generates a new object with a base type ID. The base type ID must be the correct base type ID obtained by the "basic_type_id function".
      </p>
<pre>
void* (*new_object_raw)(SPVM_ENV* env, int32_t basic_type_id);
</pre>
      <p>
        This function does not add objects to the mortal stack, so use new_object to avoid memory leaks for normal use.
      </p>
    <h4 id="native-api-native-sub-api-new_object">new_object</h4>
      <p>
        Generates and returns a new object with a base type ID. The base type ID must be the correct base type ID obtained in the basic_type_id. Adds a newly generated object to the mortal stack.
      </p>
<pre>
void* (*new_object)(SPVM_ENV* env, int32_t basic_type_id);
</pre>
      <p>
        Sample:
      </p>
<pre>
int32_t basic_type_id = env-&gt;get_basic_type_id(env,"SPVM::Int");
void* object = env-&gt;new_object(env, basic_type_id);
</pre>
    <h4 id="native-api-native-sub-api-new_byte_array_raw">new_byte_array_raw</h4>
      <p>
        Generates a new "byte[] type" object by specifying the length of the array. The initial value of all elements is 0.
      </p>
<pre>
void* (*new_byte_array_raw)(SPVM_ENV* env, int32_t length);
</pre>
      <p>
        This function does not add objects to the mortal stack, so use new_byte_array to avoid memory leaks for normal use.
      </p>
    <h4 id="native-api-native-sub-api-new_byte_array">new_byte_array</h4>
      <p>
        Generates and returns a new "byte[] type" object with the length of the array. The initial value of all elements is 0. Adds a newly generated object to the mortal stack.
      </p>
<pre>
void* (*new_byte_array)(SPVM_ENV* env, int32_t length);
</pre>
      <p>
        Sample:
      </p>
<pre>
void* byte_array_obj = env-&gt;new_byte_array(env, 100);
</pre>
      
<h4 id="native-api-native-sub-api-new_short_array_raw">new_short_array_raw</h4>
      <p>
        Generates a new "short[] type" object by specifying the length of the array. The initial value of all elements is 0.
      </p>
<pre>
void* (*new_short_array_raw)(SPVM_ENV* env, int32_t length);
</pre>
      <p>
        This function does not add objects to the mortal stack, so use new_short_array to avoid memory leaks for normal use.
      </p>
      
<h4 id="native-api-native-sub-api-new_short_array">new_short_array</h4>
      <p>
        Generates and returns a new "short[] type" object with the length of the array. The initial value of all elements is 0. Adds a newly generated object to the mortal stack.
      </p>
<pre>
void* (*new_short_array)(SPVM_ENV* env, int32_t length);
</pre>
      <p>
        Sample:
      </p>
<pre>
void* short_array_obj = env-&gt;new_short_array(env, 100);
</pre>
      
<h4 id="native-api-native-sub-api-new_int_array_raw">new_int_array_raw</h4>
      <p>
        Generates a new "int[] type" object by specifying the length of the array. The initial value of all elements is 0.
      </p>
<pre>
void* (*new_int_array_raw)(SPVM_ENV* env, int32_t length);
</pre>
      <p>
        This function does not add objects to the mortal stack, so normal use should use new_int_array to avoid memory leaks.
      </p>
      
<h4 id="native-api-native-sub-api-new_int_array">new_int_array</h4>
      <p>
        Generates and returns a new "int[] type" object with the length of the array. The initial value of all elements is 0. Adds a newly generated object to the mortal stack.
      </p>
<pre>
void* (*new_int_array)(SPVM_ENV* env, int32_t length);
</pre>
      <p>
        Sample:
      </p>
<pre>
void* int_array_obj = env-&gt;new_int_array(env, 100);
</pre>

<h4 id="native-api-native-sub-api-new_long_array_raw">new_long_array_raw</h4>
  <p>
    Creates a new "long[] type" object by specifying the length of the array. The initial value of all elements is 0.
  </p>
<pre>
void* (*new_long_array_raw)(SPVM_ENV* env, int32_t length);
</pre>
  <p>
    This function does not add objects to the mortal stack, so use normal_new_long_array to avoid memory leaks.
  </p>
  
<h4 id="native-api-native-sub-api-new_long_array">new_long_array</h4>
  <p>
    Create a new "long[] type" object by specifying the length of the array and return it. The initial value of all elements is 0. Add the newly created object to the mortal stack.
  </p>
<pre>
void* (*new_long_array)(SPVM_ENV* env, int32_t length);
</pre>
  <p>
    Example:
  </p>
<pre>
void* long_array_obj = env->new_long_array(env, 100);
</pre>
  
<h4 id="native-api-native-sub-api-new_float_array_raw">new_float_array_raw</h4>
  <p>
    Create a new "float[] type" object by specifying the length of the array. The initial value of all elements is 0.
  </p>
<pre>
void* (*new_float_array_raw)(SPVM_ENV* env, int32_t length);
</pre>
  <p>
    This function does not add any objects to the mortal stack, so use new_float_array for normal use to avoid memory leaks.
  </p>
  
<h4 id="native-api-native-sub-api-new_float_array">new_float_array</h4>
  <p>
    Create a new "float[] type" object by specifying the length of the array and return it. The initial value of all elements is 0. Add the newly created object to the mortal stack.
  </p>
<pre>
void* (*new_float_array)(SPVM_ENV* env, int32_t length);
</pre>
  <p>
    Example:
  </p>
<pre>
void* float_array_obj = env->new_float_array(env, 100);
</pre>
  
<h4 id="native-api-native-sub-api-new_double_array_raw">new_double_array_raw</h4>
  <p>
    Creates a new "double[]" object by specifying the length of the array. The initial value of all elements is 0.
  </p>
<pre>
void* (*new_double_array_raw)(SPVM_ENV* env, int32_t length);
</pre>
  <p>
    This function does not add any objects to the mortal stack, so use normal_new_double_array to avoid memory leaks.
  </p>
  
<h4 id="native-api-native-sub-api-new_double_array">new_double_array</h4>
  <p>
    Generate a new "double[] type" object by specifying the length of the array and return it. The initial value of all elements is 0. Add the newly created object to the mortal stack.
  </p>
<pre>
void* (*new_double_array)(SPVM_ENV* env, int32_t length);
</pre>
  <p>
    Example:
  </p>
<pre>
void* double_array_obj = env->new_double_array(env, 100);
</pre>
  
<h4 id="native-api-native-sub-api-new_object_array_raw">new_object_array_raw</h4>
  <p>
    Create a new object type array by specifying the basic type ID and array length and return it. The basic type ID must be the correct basic type ID obtained with the "basic_type_id function". The initial value of all elements is null.
  </p>
<pre>
void* (*new_object_array_raw)(SPVM_ENV* env, int32_t basic_type_id, int32_t length);
</pre>

  <p>
    This function does not add objects to the mortal stack, so use normal_new_object_array to avoid memory leaks.
  </p>

<h4 id="native-api-native-sub-api-new_object_array">new_object_array</h4>
  <p>
    Create a new object type array by specifying the basic type ID and array length and return it. The basic type ID must be the correct basic type ID obtained with the "basic_type_id function". The initial value of all elements is null. Add the newly created object to the mortal stack.
  </p>
<pre>
void* (*new_object_array)(SPVM_ENV* env, int32_t basic_type_id, int32_t length);
</pre>

  <p>
    Example:
</p>
<pre>
int32_t basic_type_id = env->get_basic_type_id(env, "SPVM::Int");
void* object_array_obj = env->new_object_array(env, basic_type_id, 100);
</pre>
  
<h4 id="native-api-native-sub-api-new_muldim_array_raw">new_muldim_array_raw</h4>
  <p>
    Generates and returns a new multidimensional object type array by specifying the basic type ID, element type dimension, and array length. The basic type ID must be the correct basic type ID obtained with the "basic_type_id function". The initial value of all elements is null.
  </p>
<pre>
void* (*new_muldim_array_raw)(SPVM_ENV* env, int32_t basic_type_id, int32_t element_dimension, int32_t length);
</pre>
  <p>
    This function does not add any objects to the mortal stack, so use new_muldim_array for normal use to avoid memory leaks.
  </p>
  
<h4 id="native-api-native-sub-api-new_muldim_array">new_muldim_array</h4>
  <p>
    Generates and returns a new multidimensional object type array by specifying the basic type ID, element type dimension, and array length. The basic type ID must be the correct basic type ID obtained with the "basic_type_id function". The initial value of all elements is null. Add the newly created object to the mortal stack.
  </p>
<pre>
void* (*new_muldim_array_raw)(SPVM_ENV* env, int32_t basic_type_id, int32_t element_dimension, int32_t length);
</pre>
  <p>
    Element type dimensions must be less than 255.
  </p>
  <p>
    Example:
  </p>
<pre>
// new SPVM::Int[][][100]
int32_t basic_type_id = env->get_basic_type_id(env, "SPVM::Int");
void* multi_array_obj = env->new_muldim_array(env, basic_type_id, 2, 100);
</pre>
  
<h4 id="native-api-native-sub-api-new_mulnum_array_raw">new_mulnum_array_raw</h4>
  <p>
    Generate a new multi-numeric array by specifying the basic type ID and array length and return it. The basic type ID must be the correct basic type ID acquired by the "basic_type_id function" and must be valid as a composite numeric type. The initial value of all fields for all elements is 0.
  </p>
<pre>
void* (*new_mulnum_array_raw)(SPVM_ENV* env, int32_t basic_type_id, int32_t length);
</pre>
  <p>
    This function does not add any objects to the mortal stack, so use new_mulnum_array for normal use to avoid memory leaks.
  </p>
  
<h4 id="native-api-native-sub-api-new_mulnum_array">new_mulnum_array</h4>
  <p>
    Generate a new multi-numeric array by specifying the basic type ID and array length and return it. The basic type ID must be the correct basic type ID acquired by the "basic_type_id function" and must be valid as a composite numeric type. The initial value of all fields for all elements is 0.
  </p>
<pre>
void* (*new_mulnum_array)(SPVM_ENV* env, int32_t basic_type_id, int32_t length);
</pre>
  <p>
    Example:
  </p>
<pre>
int32_t basic_type_id = env->get_basic_type_id(env, "SPVM::Complex_2d");
void* value_array_obj = env->new_mulnum_array(env, basic_type_id, 100);
</pre>
  
<h4 id="native-api-native-sub-api-new_string_nolen_raw">new_string_nolen_raw</h4>
  <p>
    Specify a C language string to generate a string type object and return it. The string must end with "\0".
  </p>
<pre>
void* (*new_string_nolen_raw)(SPVM_ENV* env, const char* bytes);
</pre>
  <p>
    This function does not add any objects to the mortal stack, so for normal use use new_string to avoid memory leaks.
  </p>

<h4 id="native-api-native-sub-api-new_string_nolen">new_string_nolen</h4>
  <p>
    Specify a C language string to generate a string type object and return it. The string must end with "\0". Add the newly created object to the mortal stack.
  </p>
<pre>
void* (*new_string_nolen)(SPVM_ENV* env, const char* bytes);
</pre>
  <p>
    Example:
  </p>
<pre>
void* str_obj = env->new_string_nolen(env, "Hello World");
</pre>
  
<h4 id="native-api-native-sub-api-new_string_raw">new_string_raw</h4>
  <p>
    Specify a C language string and length to generate a string type object and return it.
  </p>
<pre>
void* (*new_string_raw)(SPVM_ENV* env, const char* bytes, int32_t length);
</pre>
  <p>
    This function does not add any objects to the mortal stack, so for normal use use new_string to avoid memory leaks.
  </p>
  

<h4 id="native-api-native-sub-api-new_string">new_string</h4>
<P> Generates and returns a character string type object by specifying the character string and length in C language. Add the newly created object to the mortal stack.
  </p>
<pre>
void* (*new_string)(SPVM_ENV* env, const char* bytes, int32_t length);
</pre>
  <p>
    Example:
  </p>
<pre>
void* str_obj = env->new_string(env, "Hello \0World", 11);
</pre>
  
<h4 id="native-api-native-sub-api-new_pointer_raw">new_pointer_raw</h4>
  <p>
    Specify a basic type ID and a C language pointer to create a pointer type object and return it. The basic type ID must be the correct basic type ID acquired by the "basic_type_id function" and valid as a pointer type.
  </p>

<pre>
void* (*new_pointer_raw)(SPVM_ENV* env, int32_t basic_type_id, void* pointer);
</pre>

  <p>
    This function does not add any objects to the mortal stack, so for normal use use new_pointer to avoid memory leaks.
  </p>
  
<h4 id="native-api-native-sub-api-new_pointer">new_pointer</h4>
  <p>
    Specify a basic type ID and a C language pointer to create a pointer type object and return it. The basic type ID must be the correct basic type ID acquired by the "basic_type_id function" and valid as a pointer type. Add the newly created object to the mortal stack.
  </p>
<pre>
void* (*new_pointer)(SPVM_ENV* env, int32_t basic_type_id, void* pointer);
</pre>
  <p>
    Example:
  </p>
<pre>
void* pointer = malloc (sizeof (struct tm));
void* pointer_obj = env->new_pointer(env, "MyTimeInfo", pointer);
</pre>

  <p>
    See <a href="#native-api-use-pointer-type">Using pointer types</a> for a detailed sample.
  </p>
  
<h4 id="native-api-native-sub-api-concat_raw">concat_raw</h4>
  <p>
    Returns a new byte[] type object that is a concatenation of two byte[] type strings.
  </p>
<pre>
void* (*concat_raw)(SPVM_ENV* env, void* string1, void* string2);
</pre>

  <p>
    This function does not add objects to the mortal stack, so use concat for normal use to avoid memory leaks.
  </p>
  
<h4 id="native-api-native-sub-api-concat">concat</h4>
  <p>
    Returns a new byte[] type object that is a concatenation of two byte[] type strings. Add the newly created object to the mortal stack.
  </p>
<pre>
void* (*concat)(SPVM_ENV* env, void* string1, void* string2);
</pre>
  
<h4 id="native-api-native-sub-api-new_stack_trace_raw">new_stack_trace_raw</h4>
  <p>
    If you specify a byte[] type exception message and a package name, subroutine name, file name and line number, the character string of the package name, subroutine name, file name and line number is added to the end of the byte[] type exception message. The added character string will be returned.
  </p>
<pre>
void* (*new_stack_trace_raw)(SPVM_ENV* env, void* exception, const char* package_name, const char* sub_name, const char* file, int32_t line);
</pre>
  <p>
    This function does not add objects to the mortal stack, use new_stack_trace to avoid memory leaks for normal use.
  </p>
  
<h4 id="native-api-native-sub-api-new_stack_trace">new_stack_trace</h4>
  <p>
    When a byte[] type exception message and a package name, subroutine name, file name and line number are specified, the string of the package name, subroutine name, file name and line number is added to the end of the string type exception message. Returns a new string type object. Add the newly created object to the mortal stack.
  </p>
<pre>
void* (*new_stack_trace)(SPVM_ENV* env, void* exception, const char* package_name, const char* sub_name, const char* file, int32_t line);
</pre>
  
<h4 id="native-api-native-sub-api-length">length</h4>
  <p>
    If you specify an array, the length of the array is returned.
  </p>
<pre>
int32_t (*length)(SPVM_ENV*, void* array);
</pre>
  <p>
    Example:
  </p>
<pre>
int32_t length = env->length(env, array);
</pre>

<h4 id="native-api-native-sub-api-get_elems_byte">get_elems_byte</h4>
  <p>
    If you specify a byte[] type array, the pointer at the beginning of the internally stored C language int8_t[] type array is returned.  </p>
<pre>
int8_t* (*get_elems_byte)(SPVM_ENV* env, void* array);
</pre>
  <p>
    Example:
  </p>
<pre>
int8_t* values = env->get_elems_byte(env, array);
values[3] = 5;
</pre>

<h4 id="native-api-native-sub-api-get_elems_short">get_elems_short</h4>
  <p>
    If a short[] type array is specified, the pointer at the beginning of the internally stored C language int16_t[] type array is returned.
  </p>
<pre>
int16_t* (*get_elems_short)(SPVM_ENV* env, void* array);
</pre>
  <p>
    Example:
  </p>
<pre>
int16_t* values = env->get_elems_short(env, array);
values[3] = 5;
</pre>

<h4 id="native-api-native-sub-api-get_elems_int">get_elems_int</h4>
  <p>
    When an int[] type array is specified, the pointer at the beginning of the internally stored C language int32_t[] type array is returned.
  </p>
<pre>
int32_t* (*get_elems_int)(SPVM_ENV* env, void* array);
</pre>
  <p>
    Example:
  </p>
<pre>
int32_t* values = env->get_elems_int(env, array);
values[3] = 5;
</pre>

<h4 id="native-api-native-sub-api-get_elems_long">get_elems_long</h4>
  <p>
    When a long[] type array is specified, the pointer at the beginning of the internally stored C language int64_t[] type array is returned.
  </p>
<pre>
int64_t* (*get_elems_long)(SPVM_ENV* env, void* array);
</pre>
  <p>
    Example:
  </p>
<pre>
int64_t* values = env->get_elems_long(env, array);
values[3] = 5;
</pre>

<h4 id="native-api-native-sub-api-get_elems_float">get_elems_float</h4>
  <p>
    When a float[] type array is specified, the pointer at the beginning of the C language float[] type array internally held is returned.
  </p>
<pre>
float* (*get_elems_float)(SPVM_ENV* env, void* array);
</pre>
  <p>
    Example:
  </p>
<pre>
float* values = env->get_elems_float(env, array);
values[3] = 1.5f;
</pre>

<h4 id="native-api-native-sub-api-get_elems_double">get_elems_double</h4>
  <p>
    If a double[] type array is specified, the pointer at the beginning of the internally stored C double[] type array is returned.
  </p>
<pre>
double* (*get_elems_double)(SPVM_ENV* env, void* array);
</pre>
  <p>
    Example:
  </p>
<pre>
double* values = env->get_elems_double(env, array);
values[3] = 1.5;
</pre>

<h4 id="native-api-native-sub-api-get_elem_object">get_elem_object</h4>
  <p>
    Gets an object of an element given an array of object types and a subscript. If the element is a weak reference, the weak reference is removed.
  </p>
<pre>
void* (*get_elem_object)(SPVM_ENV* env, void* array, int32_t index);
</pre>
  <p>
    Example:
  </p>
<pre>
void* object = env->get_elem_object(env, array, 3);
</pre>
<h4 id="native-api-native-sub-api-set_elem_object">set_elem_object</h4>
<p>
    If you specify an array of object type and subscript and element objects, the element object is assigned to the corresponding subscript position. If the element's object has a weak reference, the weak reference is removed. The reference count of the originally assigned object is decremented by 1.
  </p>
<pre>
void (*set_elem_object)(SPVM_ENV* env, void* array, int32_t index, void* value);
</pre>
  <p>
    Example:
  </p>
<pre>
env->get_elem_object(env, array, 3, object);
</pre>
<h4 id="native-api-native-sub-api-get_field_byte">get_field_byte</h4>
  <p>
    If an object and field ID are specified, the byte field value will be returned as a C language int8_t type value. The field ID must be a valid field ID obtained with the field_id function.
  </p>
<pre>
int8_t (*get_field_byte)(SPVM_ENV* env, void* object, int32_t field_id);
</pre>
  <p>
    Example:
  </p>
<pre>
int32_t field_id = env->get_field_id(env, "Foo", "x", "byte");
int8_t field_value = env->get_field_byte(env, object, field_id);
</pre>

<h4 id="native-api-native-sub-api-get_field_short">get_field_short</h4>
  <p>
    If you specify the object and field ID, the value of the short type field will be returned as the int16_t type value of C language. The field ID must be a valid field ID obtained with the field_id function.
  </p>
<pre>
int16_t (*get_field_short)(SPVM_ENV* env, void* object, int32_t field_id);
</pre>
  <p>
    Example:
  </p>
<pre>
int32_t field_id = env->get_field_id(env, "Foo", "x", "short");
int16_t field_value = env->get_field_short(env, object, field_id);
</pre>

<h4 id="native-api-native-sub-api-get_field_int">get_field_int</h4>
  <p>
    If an object and a field ID are specified, the value of the int type field will be returned as a C language int32_t type value. The field ID must be a valid field ID obtained with the field_id function.
  </p>
<pre>
int32_t (*get_field_int)(SPVM_ENV* env, void* object, int32_t field_id);
</pre>
  <p>
    Example:
  </p>
<pre>
int32_t field_id = env->get_field_id(env, "Foo", "x", "int");
int32_t field_value = env->get_field_int(env, object, field_id);
</pre>

<h4 id="native-api-native-sub-api-get_field_long">get_field_long</h4>
  <p>
    If you specify the object and field ID, the value of the long type field will be returned as the value of int64_t type of C language. The field ID must be a valid field ID obtained with the field_id function.
  </p>
<pre>
int64_t (*get_field_long)(SPVM_ENV* env, void* object, int32_t field_id);
</pre>
  <p>
    Example:
  </p>
<pre>
int32_t field_id = env->get_field_id(env, "Foo", "x", "long");
int64_t field_value = env->get_field_long(env, object, field_id);
</pre>

<h4 id="native-api-native-sub-api-get_field_float">get_field_float</h4>
  <p>
    If you specify the object and field ID, the value of the float type field will be returned as a C language float type value. The field ID must be a valid field ID obtained with the field_id function.
  </p>
<pre>
float (*get_field_float)(SPVM_ENV* env, void* object, int32_t field_id);
</pre>
  <p>
    Example:
  </p>
<pre>
int32_t field_id = env->get_field_id(env, "Foo", "x", "float");
float field_value = env->get_field_float(env, object, field_id);
</pre>

<h4 id="native-api-native-sub-api-get_field_double">get_field_double</h4>
  <p>
    If you specify the object and field ID, the value of the double type field will be returned as a double type value in C language. The field ID must be a valid field ID obtained with the field_id function.
  </p>
<pre>
double (*get_field_double)(SPVM_ENV* env, void* object, int32_t field_id);
</pre>
  <p>
    Example:
  </p>
<pre>
int32_t field_id = env->get_field_id(env, "Foo", "x", "double");
double field_value = env->get_field_double(env, object, field_id);
</pre>

<h4 id="native-api-native-sub-api-get_field_object">get_field_object</h4>
  <p>
    If you specify the object and field ID, the value of the object type field is returned as a void* type value in C language. The field ID must be a valid field ID obtained with the field_id function. If the field is a weak reference, it will be removed.
  </p>
<pre>
void* (*get_field_object)(SPVM_ENV* env, void* object, int32_t field_id);
</pre>
<pre>
int32_t field_id = env->get_field_id(env, "Foo", "x", "SPVM::Int");
void* field_value = env->get_field_object(env, object, field_id);
</pre>

<h4 id="native-api-native-sub-api-set_field_byte">set_field_byte</h4>
  <p>
    If you specify the object and field ID and the value of the field, the value is set to the byte type field. The field ID must be a valid field ID obtained with the field_id function.
  </p>
<pre>
void (*set_field_byte)(SPVM_ENV* env, void* object, int32_t field_id, int8_t value);
</pre>
  <p>
    Example:
  </p>
<pre>
int32_t field_id = env->get_field_id(env, "Foo", "x", "byte");
int8_t field_value = 5;
env->set_field_byte(env, object, field_id, field_value);
</pre>

<h4 id="native-api-native-sub-api-set_field_short">set_field_short</h4>
  <p>
    If you specify the object and field ID and the value of the field, the value is set to the short type field. The field ID must be a valid field ID obtained with the field_id function.
  </p>
<pre>
void (*set_field_short)(SPVM_ENV* env, void* object, int32_t field_id, int16_t value);
</pre>
  <p>
    Example:
  </p>
<pre>
int32_t field_id = env->get_field_id(env, "Foo", "x", "short");
int16_t field_value = 5;
env->set_field_short(env, object, field_id, field_value);
</pre>

<h4 id="native-api-native-sub-api-set_field_int">set_field_int</h4>
  <p>
    If you specify the object and field ID and the value of the field, the value is set to the int type field. The field ID must be a valid field ID obtained with the field_id function.
  </p>
<pre>
void (*set_field_int)(SPVM_ENV* env, void* object, int32_t field_id, int32_t value);
</pre>
  <p>
    Example:
  </p>
<pre>
int32_t field_id = env->get_field_id(env, "Foo", "x", "int");
int32_t field_value = 5;
env->set_field_int(env, object, field_id, field_value);
</pre>

<h4 id="native-api-native-sub-api-set_field_long">set_field_long</h4>
  <p>
    If you specify the object and field ID and the value of the field, the value is set to the long type field. The field ID must be a valid field ID obtained with the field_id function.
  </p>
<pre>
void (*set_field_long)(SPVM_ENV* env, void* object, int32_t field_id, int64_t value);
</pre>
  <p>
    Example:
  </p>
<pre>
int32_t field_id = env->get_field_id(env, "Foo", "x", "long");
int64_t field_value = 5;
env->set_field_long(env, object, field_id, field_value);
</pre>

<h4 id="native-api-native-sub-api-set_field_float">set_field_float</h4>
  <p>
    If you specify the object and field ID and the value of the field, the value is set to the float type field. The field ID must be a valid field ID obtained with the field_id function.
  </p>
<pre>
void (*set_field_float)(SPVM_ENV* env, void* object, int32_t field_id, float value);
</pre>
  <p>
    Example:
  </p>
<pre>
int32_t field_id = env->get_field_id(env, "Foo", "x", "float");
float field_value = 1.5f;
env->set_field_float(env, object, field_id, field_value);
</pre>

<h4 id="native-api-native-sub-api-set_field_double">set_field_double</h4>
  <p>
    If you specify the object and field ID and the value of the field, the value is set to the double type field. The field ID must be a valid field ID obtained with the field_id function.
  </p>
<pre>
void (*set_field_double)(SPVM_ENV* env, void* object, int32_t field_id, double value);
</pre>
  <p>
    Example:
  </p>
<pre>
int32_t field_id = env->get_field_id(env, "Foo", "x", "double");
double field_value = 1.55;
env->set_field_double(env, object, field_id, field_value);
</pre>

<h4 id="native-api-native-sub-api-set_field_object">set_field_object</h4>
  <p>
    Object and field Specify the ID and the value of the field and set the value to the object type field. The field ID must be a valid field ID obtained with the field_id function. After setting, the reference count is incremented by 1. The original value has the reference count decremented by 1.
  </p>
<pre>
void (*set_field_object)(SPVM_ENV* env, void* object, int32_t field_id, void* value);
</pre>
  <p>
    Example:
  </p>
<pre>
int32_t field_id = env->get_field_id(env, "Foo", "x", "SPVM::Int");
int32_t basic_type_id = env->get_basic_type_id(env, "SPVM::Int");
void* object = env->new_object(env, basic_type_id);
env->set_field_object(env, object, field_id, object);
</pre>

<h4 id="native-api-native-sub-api-get_package_var_byte">get_package_var_byte</h4>
  <p>
    If an object and a package variable ID are specified, the value of the byte type package variable is returned as a C language int8_t type value. The package variable ID must be a valid package variable ID obtained with the field_id function.
  </p>
<pre>
int8_t (*get_package_var_byte)(SPVM_ENV* env, int32_t pkgvar_id);
</pre>
  <p>
    Example:
  </p>
<pre>
int32_t pkgvar_id = env->get_package_var_id(env, "Foo", "$VAR", "byte");
int8_t pkgvar_value = env->get_package_var_byte(env, object, pkgvar_id);
</pre>

<h4 id="native-api-native-sub-api-get_package_var_short">get_package_var_short</h4>
  <p>
    If an object and a package variable ID are specified, the value of the short type package variable will be returned as a C language int16_t type value. The package variable ID must be a valid package variable ID obtained with the field_id function.
  </p>
<pre>
int16_t (*get_package_var_short)(SPVM_ENV* env, int32_t pkgvar_id);
</pre>
  <p>
    Example:
  </p>
<pre>
int32_t pkgvar_id = env->get_package_var_id(env, "Foo", "$VAR", "short");
int16_t pkgvar_value = env->get_package_var_short(env, object, pkgvar_id);
</pre>

<h4 id="native-api-native-sub-api-get_package_var_int">get_package_var_int</h4>
  <p>
    If an object and a package variable ID are specified, the value of the int type package variable will be returned as a C language int32_t type value. The package variable ID must be a valid package variable ID obtained with the field_id function.
  </p>
<pre>
int32_t (*get_package_var_int)(SPVM_ENV* env, int32_t pkgvar_id);
</pre>
  <p>
    Example:
  </p>
<pre>
int32_t pkgvar_id = env->get_package_var_id(env, "Foo", "$VAR", "int");
int32_t pkgvar_value = env->get_package_var_int(env, object, pkgvar_id);
</pre>

<h4 id="native-api-native-sub-api-get_package_var_long">get_package_var_long</h4>
  <p>
    If an object and a package variable ID are specified, the value of the long type package variable will be returned as a C language int64_t type value. The package variable ID must be a valid package variable ID obtained with the field_id function.
  </p>
<pre>
int64_t (*get_package_var_long)(SPVM_ENV* env, int32_t pkgvar_id);
</pre>
  <p>
    Example:
  </p>
<pre>
int32_t pkgvar_id = env->get_package_var_id(env, "Foo", "$VAR", "long");
int64_t pkgvar_value = env->get_package_var_long(env, object, pkgvar_id);
</pre>

<h4 id="native-api-native-sub-api-get_package_var_float">get_package_var_float</h4>
  <p>
    If an object and a package variable ID are specified, the value of the float type package variable will be returned as a C language float type value. The package variable ID must be a valid package variable ID obtained with the field_id function.
  </p>
<pre>
float (*get_package_var_float)(SPVM_ENV* env, int32_t pkgvar_id);
</pre>
  <p>
    Example:
  </p>
<pre>
int32_t pkgvar_id = env->get_package_var_id(env, "Foo", "$VAR", "float");
float pkgvar_value = env->get_package_var_float(env, object, pkgvar_id);
</pre>

<h4 id="native-api-native-sub-api-get_package_var_double">get_package_var_double</h4>
  <p>
    If you specify an object and a package variable ID, the value of the double type package variable is returned as a C type double type value. The package variable ID must be a valid package variable ID obtained with the field_id function.
  </p>
<pre>
double (*get_package_var_double)(SPVM_ENV* env, int32_t pkgvar_id);
</pre>
  <p>
    Example:
  </p>
<pre>
int32_t pkgvar_id = env->get_package_var_id(env, "Foo", "$VAR", "double");
double pkgvar_value = env->get_package_var_double(env, object, pkgvar_id);
</pre>

<h4 id="native-api-native-sub-api-get_package_var_object">get_package_var_object</h4>
  <p>
    When an object and a package variable ID are specified, the value of the object type package variable is returned as a C language void* type value. The package variable ID must be a valid package variable ID obtained with the field_id function.
  </p>
<pre>
void* (*get_package_var_object)(SPVM_ENV* env, int32_t pkgvar_id);
</pre>
  <p>
    Example:
  </p>
<pre>
int32_t pkgvar_id = env->get_package_var_id(env, "Foo", "$VAR", "SPVM::Int");
void* pkgvar_value = env->get_package_var_byte(env, object, pkgvar_id);
</pre>

<h4 id="native-api-native-sub-api-set_package_var_byte">set_package_var_byte</h4>
  <p>
    If you specify the object and field ID and the value of the field, the value is set to the byte type field. The field ID must be a valid field ID obtained with the field_id function.
  </p>
<pre>
void (*set_package_var_byte)(SPVM_ENV* env, int32_t pkgvar_id, int8_t value);
</pre>
  <p>
    Example:
  </p>
<pre>
int32_t pkgvar_id = env->get_package_var_id(env, "Foo", "$VAR", "byte");
int8_t pkgvar_value = 5;
env->set_package_var_byte(env, pkgvar_id, pkgvar_value);
</pre>

<h4 id="native-api-native-sub-api-set_package_var_short">set_package_var_short</h4>
  <p>
    If you specify the object and field ID and the value of the field, the value is set to the short type field. The field ID must be a valid field ID obtained with the field_id function.
  </p>
<pre>
void (*set_package_var_short)(SPVM_ENV* env, int32_t pkgvar_id, int16_t value);
</pre>
  <p>
    Example:
  </p>
<pre>
int32_t pkgvar_id = env->get_package_var_id(env, "Foo", "$VAR", "short");
int16_t pkgvar_value = 5;
env->set_package_var_short(env, pkgvar_id, pkgvar_value);
</pre>

<h4 id="native-api-native-sub-api-set_package_var_int">set_package_var_int</h4>
  <p>
    If you specify the object and field ID and the value of the field, the value is set to the int type field. The field ID must be a valid field ID obtained with the field_id function.
  </p>
<pre>
void (*set_package_var_int)(SPVM_ENV* env, int32_t pkgvar_id, int32_t value);
</pre>
  <p>
    Example:
  </p>
<pre>
int32_t pkgvar_id = env->get_package_var_id(env, "Foo", "$VAR", "int");
int32_t pkgvar_value = 5;
env->set_package_var_int(env, pkgvar_id, pkgvar_value);
</pre>

<h4 id="native-api-native-sub-api-set_package_var_long">set_package_var_long</h4>
  <p>
    If you specify the object and field ID and the value of the field, the value is set to the long type field. The field ID must be a valid field ID obtained with the field_id function.
  </p>
<pre>
void (*set_package_var_long)(SPVM_ENV* env, int32_t pkgvar_id, int64_t value);
</pre>
  <p>
    Example:
  </p>
<pre>
int32_t pkgvar_id = env->get_package_var_id(env, "Foo", "$VAR", "long");
int64_t pkgvar_value = 5;
env->set_package_var_long(env, pkgvar_id, pkgvar_value);
</pre>

<h4 id="native-api-native-sub-api-set_package_var_float">set_package_var_float</h4>
  <p>
    If you specify the object and field ID and the value of the field, the value is set to the float type field. The field ID must be a valid field ID obtained with the field_id function.
  </p>
<pre>
void (*set_package_var_float)(SPVM_ENV* env, int32_t pkgvar_id, float value);
</pre>
  <p>
    Example:
  </p>
<pre>
int32_t pkgvar_id = env->get_package_var_id(env, "Foo", "$VAR", "float");
float pkgvar_value = 5;
env->set_package_var_float(env, pkgvar_id, pkgvar_value);
</pre>

<h4 id="native-api-native-sub-api-set_package_var_double">set_package_var_double</h4>
  <p>
    If you specify the object and field ID and the value of the field, the value is set to the double type field. The field ID must be a valid field ID obtained with the field_id function.
  </p>
<pre>
void (*set_package_var_double)(SPVM_ENV* env, int32_t pkgvar_id, double value);
</pre>
  <p>
    Example:
  </p>
<pre>
int32_t pkgvar_id = env->get_package_var_id(env, "Foo", "$VAR", "double");
double pkgvar_value = 5;
env->set_package_var_double(env, pkgvar_id, pkgvar_value);
</pre>

<h4 id="native-api-native-sub-api-set_package_var_object">set_package_var_object</h4>
  <p>
    Object and field Specify the ID and the value of the field and set the value to the object type field. The field ID must be a valid field ID obtained with the field_id function. After setting, the reference count is incremented by 1. The original value has the reference count decremented by 1.
  </p>
<pre>
void (*set_package_var_object)(SPVM_ENV* env, int32_t pkgvar_id, void* value);
</pre>
  <p>
    Example:
  </p>
<pre>
int32_t pkgvar_id = env->get_package_var_id(env, "Foo", "$VAR", "SPVM::Int");
int32_t basic_type_id = env->get_basic_type_id(env, "SPVM::Int");
void* object = env->new_object(env, basic_type_id);
env->set_package_var_object(env, pkgvar_id, pkgvar_value);
</pre>

<h4 id="native-api-native-sub-api-get_pointer">get_pointer</h4>
  <p>
    Specify a pointer type object and return the C language pointer stored inside the object.
  </p>
<pre>
void* (*get_pointer)(SPVM_ENV* env, void* pointer_object);
</pre>

  <p>
    Example:
  </p>
<pre>
strcut tm* tm_ptr = (struct tm*) env->get_pointer(env, tm_obj);
</pre>
  <p>
    See <a href="#native-api-use-pointer-type">Using pointer types</a> for a detailed sample.
  </p>

<h4 id="native-api-native-sub-api-set_pointer">set_pointer</h4>
  <p>
    If you specify a pointer type object and a C language pointer, the C language pointer is saved in the internal data of the pointer type object.
  </p>
<pre>
void (*set_pointer)(SPVM_ENV* env, void* pointer_object, void* pointer);
</pre>
  
<h4 id="native-api-native-sub-api-call_sub">call_sub</h4>
  <p>
    Call the subroutine by specifying the subroutine ID and argument. The return value is non-zero when an exception occurs in the subroutine, 0 is returned when the exception does not occur.
  </p>
<pre>
int32_t (*call_sub)(SPVM_ENV* env, int32_t sub_id, SPVM_VALUE* args);
</pre>
  <p>
    The return value of the subroutine is set to "args[0]".
  </p>

<h4 id="native-api-native-sub-api-get_exception">get_exception</h4>
  <p>
    Returns the byte[] type object saved as an exception.
  </p>
<pre>
void* (*get_exception)(SPVM_ENV* env);
</pre>
  
<h4 id="native-api-native-sub-api-set_exception">set_exception</h4>
  <p>
    If you specify an object of type byte[], it will be saved as an exception.
  </p>
<pre>
void (*set_exception)(SPVM_ENV* env, void* exception);
</pre>
  
<h4 id="native-api-native-sub-api-get_ref_count">get_ref_count</h4>
</p>
<pre>
int32_t (*get_ref_count)(SPVM_ENV* env, void* object);
</pre>

<h4 id="native-api-native-sub-api-inc_ref_count">inc_ref_count</h4>
  <p>
    Specifying an object increments the reference count of the object.
  </p>
<pre>
void (*inc_ref_count)(SPVM_ENV* env, void* object);
</pre>
  <p>
    Use this method only if you have a specific reason to use it. Normally, the reference count is managed automatically.
  </p>
  
<h4 id="native-api-native-sub-api-dec_ref_count">dec_ref_count</h4>
  <p>
    Specifying an object decrements the object's reference count by 1. When the reference count reaches 0, the object is released.
  </p>
<pre>
void (*dec_ref_count)(SPVM_ENV* env, void* object);
</pre>
  <p>
    Use this method only if you have a specific reason to use it. Normally, the reference count is managed automatically.
  </p>
  
<h4 id="native-api-native-sub-api-enter_scope">enter_scope</h4>
  <p>
    Create a new scope and return the scope ID.
  </p>
<pre>
int32_t (*enter_scope)(SPVM_ENV* env);
</pre>

<h4 id="native-api-native-sub-api-push_mortal">push_mortal</h4>
  <p>
    Add an object to the mortal stack.
  </p>
<pre>
int32_t (*push_mortal)(SPVM_ENV* env, void* object);
</pre>

If this method succeed, return 0.

If this method don't alloc memory for new mortal information, return 1.

<h4 id="native-api-native-sub-api-leave_scope">leave_scope</h4>
  <p>
    Specify a scope ID to exit that scope and decrement the object's reference count stored in the mortal stack. Objects with a reference count of 0 are released. The scope ID must be the ID obtained by the enter_scope function.
  </p>
<pre>
void (*leave_scope)(SPVM_ENV* env, int32_t scope_id);
</pre>

<h4 id="native-api-native-sub-api-remove_mortal">remove_mortal</h4>
  <p>
    Given a scope ID and an object, delete the specified object from the mortal stack.
  </p>
<pre>
int32_t (*remove_mortal)(SPVM_ENV* env, int32_t scope_id, void* remove_object);
</pre>

<h4 id="native-api-native-sub-api-is_type">is_type</h4>
  <p>
    Given an object and a base type ID and a type dimension, returns a nonzero value if the object matches both the base type ID and the type dimension, and 0 otherwise.
  </p>
<pre>
int32_t (*is_type)(SPVM_ENV* env, void* object, int32_t basic_type_id, int32_t type_dimension);
</pre>

<h4 id="native-api-native-sub-api-has_callback">has_callback</h4>
  <p>
    Given a base type id for the object and the callback type, returns a non-zero value if the object conforms to the callback type, and zero otherwise.
  </p>
<pre>
int32_t (*has_callback)(SPVM_ENV* env, void* object, int32_t callback_basic_type_id);
</pre>

<h4 id="native-api-native-sub-api-get_object_basic_type_id">get_object_basic_type_id</h4>
  <p>
    Gets the base type ID of the object.
  </p>
<pre>
int32_t (*get_object_basic_type_id)(SPVM_ENV* env, void* object);
</pre>

<h4 id="native-api-native-sub-api-get_object_type_dimension">get_object_type_dimension</h4>
  <p>
    Gets the dimension of the type of object.
  </p>
<pre>
int32_t (*get_object_type_dimension)(SPVM_ENV* env, void* object);
</pre>

<h4 id="native-api-native-sub-api-weaken">weaken</h4>

<pre>
int32_t (*weaken)(SPVM_ENV* env, void** object_address);
</pre>

Create weak reference to the object which is specified by object address.

The reference count of the object is decrimented by 1 and weaken flag is added to the object address.

If the reference count is 1, "dec_ref_count" is called to the object.

If object_address is NULL, this method do nothing.

If the object is already weaken, this method do nothing.

This method allocate memory internally to add the back reference from the object to the object address.

This method success return 0.

If failing memory allocation of back reference, return 1.

<h4 id="native-api-native-sub-api-isweak">isweak</h4> <p>
    Given the address of an object, returns non-zero if the object is a weak reference, 0 otherwise.
  </p>
<pre>
int32_t (*isweak()SPVM_ENV* env, void** object);
</pre>

<h4 id="native-api-native-sub-api-unweaken">unweaken</h4>
  <p>
    Specifying the address of the object releases the weak reference to the object.
  </p>
<pre>
void (*unweaken)(SPVM_ENV* env, void** object_address);
</pre>
  
<h4 id="native-api-native-sub-api-alloc_memory_block_zero">alloc_memory_block_zero</h4>

<pre>
void* (*alloc_memory_block_zero)(SPVM_ENV* env, int64_t byte_size);
</pre>

  <p>
    If you specify the size in bytes, the memory block is allocated and the pointer of the allocated memory block is returned. If fail to alloc memory, return NULL. If success, all bits in the memory block are initialized with 0 and the memory block count (memory_blocks_count)is incremented by 1.
  </p>

<h4 id="native-api-native-sub-api-free_memory_block">free_memory_block</h4>

<pre>
void (*free_memory_block)(SPVM_ENV* env, void* block);
</pre>

If block is not NULL, free the memory and memory blocks count(memory_blocks_count) is decremented by 1.

<h4 id="native-api-native-sub-api-get_memory_blocks_count">get_memory_blocks_count</h4>
  <p>
    Returns the current number of memory blocks.
  </p>
<pre>
int32_t (*get_memory_blocks_count)(SPVM_ENV* env);
</pre>
  <p>
    The memory block is increased by 1 when an object is created, when the alloc_memory_block_zero function is called, and when a back reference is added by the weaken function.
  </p>

<h4 id="native-api-native-sub-api-get_type_name_raw">get_type_name_raw</h4>
  <p>
    If you specify an object, a new byte[] type object that stores the type name is returned.
  </p>
<pre>
void* (*get_type_name_raw)(SPVM_ENV* env, void* object);
</pre>
  <p>
    This function does not add objects to the mortal stack, so use type_name for normal use to avoid memory leaks.
  </p>

<h4 id="native-api-native-sub-api-get_type_name">get_type_name</h4>
  <p>
    If you specify an object, a new byte[] type object that stores the type name is returned. Add the newly created object to the mortal stack.
  </p>
<pre>
void* (*get_type_name)(SPVM_ENV* env, void* object);
</pre>
<h4 id="native-api-native-sub-api-new_env">new_env</h4>
  <p>
    Create a new execution environment based on the current execution environment.
  </p>
<pre>
SPVM_ENV* (*new_env)(SPVM_ENV* env);
</pre>
  <p>
    Create a new SPVM runtime environment.
  </p>
  <p>
    The exception object and mortal stack information will be initialized.
  </p>
  <p>
    Share the package variables with the original execution environment.
  </p>
  <p>
    The number of memory blocks is shared with the original execution environment.
  </p>

If thie method can't allocate memory for SPVM runtime environment, return NULL.

<h4 id="native-api-native-sub-api-free_env">free_env</h4>
  <p>
    Release the execution environment.
  </p>
<pre>
void (*free_env)(SPVM_ENV* env);
</pre>

<h4 id="native-api-native-sub-api-memory_blocks_count">memory_blocks_count</h4>
  <p>
    Memory blocks count. It is used internally.
  </p>
<pre>
void* memory_blocks_count;
</pre>

<h4 id="native-api-native-sub-api-get_chars">get_chars</h4>

Get characters pointer in the string object.

<pre>
const char* (*get_chars)(SPVM_ENV* env, void* string_object);
</pre>

Example:

<pre>
const char* bytes = env->get_chars(env, string_object);
</pre>

<h4 id="native-api-native-sub-api-die">die</h4>

<pre>
int32_t (*die)(SPVM_ENV* env, const char* message, ...);
</pre>

<h4 id="native-api-native-sub-api-new_object_by_name">new_object_by_name</h4>

<pre>
void* (*new_object_by_name)(SPVM_ENV* env, const char* package_name, int32_t* exception_flag, const char* file, int32_t line);
</pre>

<h4 id="native-api-native-sub-api-new_pointer_by_name">new_pointer_by_name</h4>

<pre>
void* (*new_pointer_by_name)(SPVM_ENV* env, const char* package_name, void* pointer, int32_t* exception_flag, const char* file, int32_t line);
</pre>

<h4 id="native-api-native-sub-api-set_field_byte_by_name">set_field_byte_by_name</h4>

<pre>
void (*set_field_byte_by_name)(SPVM_ENV* env, void* object, const char* package_name, const char* field_name, int8_t value,
  int32_t* exception_flag, const char* file, int32_t line);
</pre>

<h4 id="native-api-native-sub-api-set_field_short_by_name">set_field_short_by_name</h4>

<pre>
void (*set_field_short_by_name)(SPVM_ENV* env, void* object, const char* package_name, const char* field_name, int16_t value,
  int32_t* exception_flag, const char* file, int32_t line);
</pre>

<h4 id="native-api-native-sub-api-set_field_int_by_name">set_field_int_by_name</h4>

<pre>
void (*set_field_int_by_name)(SPVM_ENV* env, void* object, const char* package_name, const char* field_name, int32_t value,
  int32_t* exception_flag, const char* file, int32_t line);
</pre>

<h4 id="native-api-native-sub-api-set_field_long_by_name">set_field_long_by_name</h4>

<pre>
void (*set_field_long_by_name)(SPVM_ENV* env, void* object, const char* package_name, const char* field_name, int64_t value,
  int32_t* exception_flag, const char* file, int32_t line);
</pre>

<h4 id="native-api-native-sub-api-set_field_float_by_name">set_field_float_by_name</h4>

<pre>
void (*set_field_float_by_name)(SPVM_ENV* env, void* object, const char* package_name, const char* field_name, float value,
  int32_t* exception_flag, const char* file, int32_t line);
</pre>

<h4 id="native-api-native-sub-api-set_field_double_by_name">set_field_double_by_name</h4>

<pre>
void (*set_field_double_by_name)(SPVM_ENV* env, void* object, const char* package_name, const char* field_name, double value,
  int32_t* exception_flag, const char* file, int32_t line);
</pre>

<h4 id="native-api-native-sub-api-set_field_object_by_name">set_field_object_by_name</h4>

<pre>
void (*set_field_object_by_name)(SPVM_ENV* env, void* object, const char* package_name, const char* field_name, const char* signature, void* value,
  int32_t* exception_flag, const char* file, int32_t line);
</pre>

<h4 id="native-api-native-sub-api-get_field_byte_by_name">get_field_byte_by_name</h4>

<pre>
int8_t (*get_field_byte_by_name)(SPVM_ENV* env, void* object, const char* package_name, const char* field_name,
  int32_t* exception_flag, const char* file, int32_t line);
</pre>

<h4 id="native-api-native-sub-api-get_field_short_by_name">get_field_short_by_name</h4>

<pre>
int16_t (*get_field_short_by_name)(SPVM_ENV* env, void* object, const char* package_name, const char* field_name,
  int32_t* exception_flag, const char* file, int32_t line);
</pre>

<h4 id="native-api-native-sub-api-get_field_int_by_name">get_field_int_by_name</h4>

<pre>
int32_t (*get_field_int_by_name)(SPVM_ENV* env, void* object, const char* package_name, const char* field_name,
  int32_t* exception_flag, const char* file, int32_t line);
</pre>

<h4 id="native-api-native-sub-api-get_field_long_by_name">get_field_long_by_name</h4>

<pre>
int64_t (*get_field_long_by_name)(SPVM_ENV* env, void* object, const char* package_name, const char* field_name,
  int32_t* exception_flag, const char* file, int32_t line);
</pre>

<h4 id="native-api-native-sub-api-get_field_float_by_name">get_field_float_by_name</h4>

<pre>
float (*get_field_float_by_name)(SPVM_ENV* env, void* object, const char* package_name, const char* field_name,
  int32_t* exception_flag, const char* file, int32_t line);
</pre>

<h4 id="native-api-native-sub-api-get_field_double_by_name">get_field_double_by_name</h4>

<pre>
double (*get_field_double_by_name)(SPVM_ENV* env, void* object, const char* package_name, const char* field_name,
  int32_t* exception_flag, const char* file, int32_t line);
</pre>

<h4 id="native-api-native-sub-api-get_field_object_by_name">get_field_object_by_name</h4>

<pre>
void* (*get_field_object_by_name)(SPVM_ENV* env, void* object, const char* package_name, const char* field_name, const char* signature,
  int32_t* exception_flag, const char* file, int32_t line);
</pre>

<h4 id="native-api-native-sub-api-set_package_var_byte_by_name">set_package_var_byte_by_name</h4>

<pre>
void (*set_package_var_byte_by_name)(SPVM_ENV* env, const char* package_name, const char* package_var_name, int8_t value,
  int32_t* exception_flag, const char* file, int32_t line);
</pre>

<h4 id="native-api-native-sub-api-set_package_var_short_by_name">set_package_var_short_by_name</h4>

<pre>
void (*set_package_var_short_by_name)(SPVM_ENV* env, const char* package_name, const char* package_var_name, int16_t value,
  int32_t* exception_flag, const char* file, int32_t line);
</pre>

<h4 id="native-api-native-sub-api-set_package_var_int_by_name">set_package_var_int_by_name</h4>

<pre>
void (*set_package_var_int_by_name)(SPVM_ENV* env, const char* package_name, const char* package_var_name, int32_t value,
  int32_t* exception_flag, const char* file, int32_t line);
</pre>

<h4 id="native-api-native-sub-api-set_package_var_long_by_name">set_package_var_long_by_name</h4>

<pre>
void (*set_package_var_long_by_name)(SPVM_ENV* env, const char* package_name, const char* package_var_name, int64_t value,
  int32_t* exception_flag, const char* file, int32_t line);
</pre>

<h4 id="native-api-native-sub-api-set_package_var_float_by_name">set_package_var_float_by_name</h4>

<pre>
void (*set_package_var_float_by_name)(SPVM_ENV* env, const char* package_name, const char* package_var_name, float value,
  int32_t* exception_flag, const char* file, int32_t line);
</pre>

<h4 id="native-api-native-sub-api-set_package_var_double_by_name">set_package_var_double_by_name</h4>

<pre>
void (*set_package_var_double_by_name)(SPVM_ENV* env, const char* package_name, const char* package_var_name, double value,
  int32_t* exception_flag, const char* file, int32_t line);
</pre>

<h4 id="native-api-native-sub-api-set_package_var_object_by_name">set_package_var_object_by_name</h4>

<pre>
void (*set_package_var_object_by_name)(SPVM_ENV* env, const char* package_name, const char* package_var_name, const char* signature, void* value,
  int32_t* exception_flag, const char* file, int32_t line);
</pre>

<h4 id="native-api-native-sub-api-get_package_var_byte_by_name">get_package_var_byte_by_name</h4>

<pre>
int8_t (*get_package_var_byte_by_name)(SPVM_ENV* env, const char* package_name, const char* package_var_name,
  int32_t* exception_flag, const char* file, int32_t line);
</pre>

<h4 id="native-api-native-sub-api-get_package_var_short_by_name">get_package_var_short_by_name</h4>

<pre>
int16_t (*get_package_var_short_by_name)(SPVM_ENV* env, const char* package_name, const char* package_var_name,
  int32_t* exception_flag, const char* file, int32_t line);
</pre>

<h4 id="native-api-native-sub-api-get_package_var_int_by_name">get_package_var_int_by_name</h4>

<pre>
int32_t (*get_package_var_int_by_name)(SPVM_ENV* env, const char* package_name, const char* package_var_name,
  int32_t* exception_flag, const char* file, int32_t line);
</pre>

<h4 id="native-api-native-sub-api-get_package_var_long_by_name">get_package_var_long_by_name</h4>

<pre>
int64_t (*get_package_var_long_by_name)(SPVM_ENV* env, const char* package_name, const char* package_var_name,
  int32_t* exception_flag, const char* file, int32_t line);
</pre>

<h4 id="native-api-native-sub-api-get_package_var_float_by_name">get_package_var_float_by_name</h4>

<pre>
float (*get_package_var_float_by_name)(SPVM_ENV* env, const char* package_name, const char* package_var_name,
  int32_t* exception_flag, const char* file, int32_t line);
</pre>

<h4 id="native-api-native-sub-api-get_package_var_double_by_name">get_package_var_double_by_name</h4>

<pre>
double (*get_package_var_double_by_name)(SPVM_ENV* env, const char* package_name, const char* package_var_name,
  int32_t* exception_flag, const char* file, int32_t line);
</pre>

<h4 id="native-api-native-sub-api-get_package_var_object_by_name">get_package_var_object_by_name</h4>

<pre>
void* (*get_package_var_object_by_name)(SPVM_ENV* env, const char* package_name, const char* package_var_name, const char* signature,
  int32_t* exception_flag, const char* file, int32_t line);
</pre>

<h4 id="native-api-native-sub-api-call_sub_by_name">call_sub_by_name</h4>

<pre>
int32_t (*call_sub_by_name)(SPVM_ENV* env, const char* package_name, const char* sub_name, const char* signature, SPVM_VALUE* stack,
  const char* file, int32_t line);
</pre>

<h4 id="native-api-native-sub-api-call_poly_sub_by_name">call_poly_sub_by_name</h4>

<pre>
int32_t (*call_poly_sub_by_name)(SPVM_ENV* env, void* object, const char* sub_name, const char* signature, SPVM_VALUE* stack,
  const char* file, int32_t line);
</pre>

<h4 id="native-api-native-sub-api-get_field_string_chars_by_name">get_field_string_chars_by_name</h4>

<pre>
const char* (*get_field_string_chars_by_name)(SPVM_ENV* env, void* obj, const char* package_name, const char* field_name,
  int32_t* exception_flag, const char* file, int32_t line);
</pre>

<h4 id="native-api-native-sub-api-any_object_basic_type_id">any_object_basic_type_id</h4>

<pre>
void* any_object_basic_type_id;
</pre>

=end html

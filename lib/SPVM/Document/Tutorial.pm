=head1 NAME

SPVM::Document::Tutorial - SPVM Performance Tutorial

=head1 DESCRIPTION

SPVM Tutorial

=head1 TUTORIAL

=begin html

<h2>SPVM Installation</h2>

SPMV Installation is described. SPVM is a programing language, but also SPVM is a CPAN module writen by Perl and C language. You can install SPVM from CPAN using cpan or cpanm command.

Install SPVM using <a href="https://metacpan.org/pod/distribution/App-cpanminus/bin/cpanm">cpanm</a> if you has user Perl in user directory using <a href="https://perlbrew.pl/">perlbrew</a> or <a href="https://github.com/tokuhirom/plenv">plenv</a>.

<pre>
cpanm SPVM
</pre>

Install SPVM using cpan command.

<pre>
cpan SPVM
</pre>

<h3>What are the Advantages that SPVM programming language is a CPAN module?</h3>

The Advantages is that you can upgrade by simply installing SPVM from CPAN.

SPVM is a programming language, but also a Perl module, and works with Perl.

Binary compatibility is kept in upgrading unlike Perl in this point.

SPVM has a Native API for operating SPVM in cooperation with C language. In the C language level, SPVM has a way to keep the backward compatibility when upgrading.

<h2>SPVM Getting Started</h2>

Let's take SPVM for the first time. Then, let's improve the performance of the SPVM code.

<h3>First SPVM Program</h3>

Let's take SPVM for the first time. This is a first simple example. Let's calcurate the sum of numbers.

<h4>Create SPVM module</h4>

Create SPVM module. The extension is "spvm". In this example, the name of SPVM module is "SPVM/MyMath.spvm".

Create "SPVM/MyMath.spvm" in the "lib" directory, and you write the following code.

<pre>
# lib/SPVM/MyMath.spvm
class MyMath {
  static method sum : int ($nums : int[]) {
    
    my $total = 0;
    for (my $i = 0; $i < @$nums; $i++) {
      $total += $nums->[$i];
    }
    
    return $total;
  }
}
</pre>

<h4>Class Definition</h4>

Write <b>Class Definition</b> by <b>class</b> keyword. Unlike Perl, SPVM always need class. The whole SPVM grammar is a set of classes.

<pre>
# Class Definition
class MyMath {

}
</pre>

See also <a href="/language.html#language-class">Class - SPVM Language Specification</a> about Class.

<h4>Method Definition</h4>

Write <b>Method Definition</b> by <b>sub</b> keyword. Unlike Perl, SPVM Method Definition have return type and argument types.
  
<pre>
class MyMath {
  # Method Definition
  static method sum : int ($nums : int[]) {
    
  }
}
</pre>

See also <a href="/language.html#language-sub">Method - SPVM Language Specification</a> about Method.

<h4>Numeric Types</h4>

<b>int</b> type in sum return value is signed 32bit integer type. This is same as C99 int32_t.

<pre>
int
</pre>

SPVM has the following types as other numeric types.

<table>
  <tr>
    <th>
      <b>SPVM numric type</b>
    </ th>
    <th>
      <b>C99 type</b>
    </ th>
  </tr>
  <tr>
    <td>
      <b>byte</b>
    </td>
    <td>
      int8_t
    </td>
  </tr>
  <tr>
    <td>
      <b>short</b>
    </td>
    <td>
      int16_t
    </td>
  </tr>
  <tr>
    <td>
      <b>int</b>
    </td>
    <td>
      int32_t
    </td>
  </tr>
  <tr>
    <td>
      <b>long</b>
    </td>
    <td>
      int64_t
    </td>
  </tr>
  <tr>
    <td>
      <b>float</b>
    </td>
    <td>
      float
    </td>
  <tr>
    <td>
      <b>double</b>
    </td>
    <td>
      double
    </td>
  </tr>
</table>

See also <a href="http://59.106.185.196:3000/spvmdoc-public/language.html#language-type">Type - SPVM Language Specification</a> about Type.

<h4>Array Types</h4>

<b>int[]</b> type in sum arguments is array of int type. 

<pre>
int[]
</pre>

The numeric array type guarantees that the values are consecutive in memory.

In this point, unlike Perl where all value are assigned to the dynamic type SV, SPVM has a static type, so it can represent a efficient sequence of numbers.

See also <a href="http://59.106.185.196:3000/spvmdoc-public/language.html#language-type">Type - SPVM Language Specification</a> about Type.

<h4>Local Variable Declaration</h4>

Write <b>Local Variable Declaration</b> by <b>my</b> keyword. You can initialize variables at the same time you declare variables.

<pre>
my $total = 0;
</pre>

The above declaration has the same meaning as:

<pre>
my $total : int = 0;
</pre>

0 on the right side is a signed 32-bit integer, so the type of the variable is automatically determined by type inference.

See also <a href="/language.html#language-local-var">Lexical Variabe - SPVM Language Specification</a> about Lexical Variabe Declaration.

See also <a href="/language.html#language-type-inference">Type Inference - SPVM Language Specification</a> about Type Inference.

<h4>Integer Literal</h4>

0 is Integer Literal. 

<pre>
my $total : int = 0;
</pre>

SPVM has the following Literal.

<ul>
  <li>Integer Literal</li>
  <li>Floating Point Literal</li>
  <li>Charater Literal</li>
  <li>String Literal</li>
</ul>

<pre>
# Integer Literal
123
123_456_789

# Floating Point Literal
1.32
1.32f

# Character Literal
'a'
'c'

# String Literal
"Hello World!"
</pre>

See also <a href="/language.html#language-literal">Literal - SPVM Language Specification</a> about Literal.

<h4>Get Array Length</h4>

Let's look at the part where the sum of the arrays is calculated. 

<pre>
for (my $i = 0; $i < @$nums; $i++) {
  $total += $nums->[$i];
}
</pre>

See @$nums.

<pre>
@$nums
</pre>

@ is Array Length Operator to get array length.

Unlike Perl, which is context sensitive, Array Length Operator of SPVM always returns the length of the array.

Note that SPVM has no context.

See <a href="/language.html#language-operator-array-length">Array Length Operator - SPVM Language Specification</a> about Array Length Operator

<h4>Increment Operator</h4>

Incremental Operator increment the value.

<pre>
$i++
</pre>

See <a href="http://59.106.185.196:3000/spvmdoc-public/language.html#language-operator-inc">Increment Operator - SPVM Language Specification</a> about Incremental Operator.

See <a href="http://59.106.185.196:3000/spvmdoc-public/language.html#language-operator-dec">Decrement Operator - SPVM Language Specification</a> about Decrement Operator.

<h4>Array Access</h4>

Array Access can be done by "->" Arrow Operator.

<pre>
$nums->[$i]
</pre>

See <a href="http://59.106.185.196:3000/spvmdoc-public/language.html#language-array">Array - SPVM Language Specification</a> about Array operation.

<h4>Addition Operator</h4>

See the following code.

<pre>
$total += $nums->[$i];
</pre>

This is same as the following Additon Operator and Assignment Operator.

<pre>
$total = $total + $nums->[$i];
</pre>

SPVM has many operators.

See <a href="/language.html#language-operator">Operator - SPVM Language Specification</a> about Opeartor.

<h4>for Statement</h4>

Next, see for Statement.

<pre>
for (my $i = 0; $i < @$nums; $i++) {
  $total += $nums->[$i];
}
</pre>

See <a href="/language.html#language-statement-for">for Statement - SPVM Language Specification</a> about for Statement.

See <a href="/language.html#language-statement">Statement - SPVM Language Specification</a> about Statement like if Statement, while Statement, and switch Statement.

<h4>return Statement</h4>

At last, return Statement.

<pre>
return $total;
</pre>

See <a href="/language.html#language-statement-return">return Statement - SPVM Language Specification</a> about return Statement.


<h3>Call SPVM Method from Perl</h3>

Create "sum.pl" file  and write the following code. This is Perl program.

<pre>
use strict;
use warnings;
use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'MyMath';

# Call method
my $total = SPVM::MyMath->sum([3, 6, 8, 9]);

print "Total: $total\n";

# Call method with packed data
my $nums_packed = pack('l*', 3, 6, 8, 9);
my $sv_nums = SPVM::new_int_array_from_bin($nums_packed);
my $total_packed = SPVM::MyMath->sum($sv_nums);

print "Total Packed: $total_packed\n";
</pre>

<h4>Add library path</h4>

The followings are the conventions and add current script directry's "lib" directory to library path .
<pre>
use strict;
use warnings;
use FindBin;
use lib "$FindBin::Bin/lib";
</pre>

<h4>use SPVM module</h4>

use SPVM module.

<pre>
use SPVM 'MyMath';
</pre>

In this place, compilation is not done. Collect SPVM modules.

<h4>Call SPVM Method</h4>

Call SPVM Method. It's amazing that SPVM method can be called as Perl method.

<pre>
# Call method
my $total = SPVM::MyMath->sum([3, 6, 8, 9]);
</pre>

Perl array reference is converted to SPVM int array.

See <a href="/exchange-api.html#exchange-api-perl-data-to-spvm-value">Convert Perl Data to SPVM Value - SPVM Exchange API</a> about Conversion of Perl Data to SPVM Value.

SPVM int return value is converted to Perl Scalar.

See <a href="/exchange-api.html#exchange-api-spvm-value-to-perl-data">Converting SPVM Value to Perl Data - SPVM Exchange API</a> about Conversion of Perl Data to SPVM Value.

<h4>Call SPVM Method with packed data</h4>

you can pass packed binary data. SPVM::new_int_array_from_bin create SPVM int array from packed binary data. This is efficient.

<pre>
# Call method with packed data
my $nums_packed = pack('l*', 3, 6, 8, 9);
my $sv_nums = SPVM::new_int_array_from_bin($nums_packed);
my $total_packed = SPVM::MyMath->sum($sv_nums);
</pre>

See <a href="/exchange-api.html">SPVM Exchange API</a> about SPVM Exchange API like SPVM::new_int_array_from_bin.

<h3>How to improve SPVM Performance</h2>

See How to improve SPVM Performance.

If you're searching SPVM for performance reasons, here's what you really want to see.

<ul class="toc">
  <li><a href="/blog/20200702071424.html">How to improve SPVM Performance</a></li>
</ul>


<h2>How to improve SPVM Performance using SPVM Precompile and SPVM Native API</h2>

SPVM Module:

<pre>
# lib/SPVM/MyMath.spvm
class MyMath {
  static method sum : int ($nums : int[]) {
    
    my $total = 0;
    for (my $i = 0; $i < @$nums; $i++) {
      $total += $nums->[$i];
    }
    
    return $total;
  }
}
</pre>

Use SPVM Module from Perl

<pre>
# spvm.pl
use strict;
use warnings;
use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'MyMath';

# Call method
my $total = SPVM::MyMath->sum([3, 6, 8, 9]);

print "Total: $total\n";

# Call method with packed data
my $nums_packed = pack('l*', 3, 6, 8, 9);
my $sv_nums = SPVM::new_int_array_from_bin($nums_packed);
my $total_packed = SPVM::MyMath->sum($sv_nums);

print "Total Packed: $total_packed\n";
</pre>

Precompiled SPVM Method. This means SPVM code is converted to Machine Code:

<pre>
# lib/SPVM/MyMath.spvm
class MyMath : precompile {
  static method sum_precompile : int ($nums : int[]) {
    
    my $total = 0;
    for (my $i = 0; $i < @$nums; $i++) {
      $total += $nums->[$i];
    }
    
    return $total;
  }
}
</pre>

Call SPVM Precompile Method from Perl

<pre>
# spvm.pl
use strict;
use warnings;
use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'MyMath';

# Call precompile method
my $total_precompile = SPVM::MyMath->sum_precompile([3, 6, 8, 9]);

print "Total Precompile: $total_precompile\n";
</pre>

SPVM Native Method. This means SPVM method call C/C++ native method:

<pre>
# lib/SPVM/MyMath.spvm
class MyMath {
  native static method sum_native : int ($nums : int[]);
}

// lib/SPVM/MyMath.c
#include "spvm_native.h"

int32_t SPVM__SPVM__MyMath__sum_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* sv_nums = stack[0].oval;
  
  int32_t length = env->length(env, sv_nums);
  
  int32_t* nums = env->get_elems_int(env, sv_nums);
  
  int32_t total = 0;
  for (int32_t i = 0; i < length; i++) {
    total += nums[i];
  }
  
  stack[0].ival = total;
  
  return 0;
}

# lib/SPVM/MyMath.config

use strict;
use warnings;

use SPVM::Builder::Config;
my $bconf = SPVM::Builder::Config->new_c99;

$bconf;
</pre>

Use SPVM Native Method from Perl

<pre>
# spvm.pl
use strict;
use warnings;
use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'MyMath';

# Call native method
my $total_native = SPVM::MyMath->sum_native([3, 6, 8, 9]);

print "Total Native: $total_native\n";
</pre>

Environment Variable "SPVM_BUILD_DIR" must be set for precompile and native method

<pre>
# bash example
export SPVM_BUILD_DIR=~/.spvm_build
</pre>

<h2>How to Bind C/C++/CUDA Library to SPVM</h2>

The advantage of SPVM is that you can easily bind C/C++/CUDA.

Methods bound with SPVM can be easily called from Perl.

Before reading this page, you need to understand Native API.

<ul>
  <li><a href="/blog/20200702071424.html">How to improve SPVM Performance - Precompile and Native API</a></li>
</ul>

<h3>Binding your own C language library</h3>

First, let's bind our own C library.

The following source code is the completed source code.

I will explain using this source code.

<a href="https://github.com/yuki-kimoto/SPVM/tree/master/examples/native/bind_clib">SPVM Native Example - Bind C Library</a>

Create a C language library for summation and call it from Perl.

<pre>
# bind_clib.pl
use strict;
use warnings;

use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'BindCLib';

my $total = SPVM::BindCLib->sum([1, 2, 3, 4]);

print "Total: $total\n";
</pre>

SPVM Method Definition.

<pre>
# lib/SPVM/BindCLib.spvm
class BindCLib {
  native static method sum : int ($nums : int[]);
}
</pre>

Native Config.

<pre>
# lib/SPVM/BindCLib.config
use strict;
use warnings;

use SPVM::Builder::Config;
my $bconf = SPVM::Builder::Config->new_c99;

$bconf;
</pre>

Call C library from C program.

<pre>
// lib/SPVM/BindCLib.c
#include "spvm_native.h"

#include "bind_clib.h"

int32_t SPVM__SPVM__BindCLib__sum(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* sv_nums = stack[0].oval;
  
  int32_t length = env->length(env, sv_nums);
  
  int32_t* nums = env->get_elems_int(env, sv_nums);
  
  int32_t total = bind_clib_sum(nums, length);
  
  stack[0].ival = total;
  
  return 0;
}
</pre>

Notice the line reading the header.

<pre>
#include "bind_clib.h"
</pre>

This header is included from "lib/SPVM/BindCLib.native/include/bind_clib.h". This is pure C header file.

<pre>
#include <inttypes.h>

int32_t bind_clib_sum(int32_t* nums, int32_t length);
</pre>

SPVM sets the include directory("SPVM/BindCLib.native/include") as the default header file read path.

C library source file is "lib/SPVM/BindCLib.native/src/bind_clib.c". This is pure C source file.

<pre>
#include "bind_clib.h"

int32_t bind_clib_sum(int32_t* nums, int32_t length) {
  
  int32_t total = 0;
  for (int32_t i = 0; i < length; i++) {
    total += nums[i];
  }
  
  return total;
}
</pre>

SPVM compiles all source files in the source directory("SPVM/BindCLib.native/src"). It can contain multiple source files.

<h3>How to bind other C Library to SPVM</h3>

If you want to know more about the bindings of other C libraries, see the example below.

<ul>
  <li><a href="https://github.com/yuki-kimoto/SPVM/tree/master/examples/native/zlib">Bind zlib to SPVM</a></li>
  <li><a href="https://github.com/yuki-kimoto/SPVM/tree/master/examples/native/gsl">Bind GSL to SPVM</a></li>
  <li><a href="https://github.com/yuki-kimoto/SPVM/tree/master/examples/native/openmp">Bind OpenMP to SPVM</a></li>
</ul>

<h3>How to bind C++ Library to SPVM</h3>

If you want to know more about the bindings of C++ libraries to SPVM, see the example below.

<ul>
  <li><a href="https://github.com/yuki-kimoto/SPVM/tree/master/examples/native/eigen">Bind Eigen to SPVM</a></li>
</ul>

<h3>How to bind CUDA to SPVM</h3>

If you want to know more about the bindings of CUDA to SPVM, see the example below.

<ul>
  <li><a href="https://github.com/yuki-kimoto/SPVM/tree/master/examples/native/cuda_add">Bind CUDA to SPVM</a></li>
</ul>


=end html

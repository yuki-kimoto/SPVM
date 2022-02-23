=head1 NAME

SPVM::Document::Tutorial - SPVM Performance Tutorial

=head1 DESCRIPTION

This document is SPVM Tutorial. Describes SPVM basic grammers, how to get more performance, how to bind C/C++ libraries.

=head1 SPVM Installation


SPMV Installation is described. SPVM is a programing language, but also SPVM is a CPAN module writen by Perl and C language. You can install SPVM from CPAN using cpan or cpanm command.

Install SPVM using <a href="https://metacpan.org/pod/distribution/App-cpanminus/bin/cpanm">cpanm</a> if you has user Perl in user directory using <a href="https://perlbrew.pl/">perlbrew</a> or <a href="https://github.com/tokuhirom/plenv">plenv</a>.

  
  cpanm SPVM


Install SPVM using cpan command.

  
  cpan SPVM



=head2 What are the Advantages that SPVM programming language is a CPAN module?


The Advantages is that you can upgrade by simply installing SPVM from CPAN.

SPVM is a programming language, but also a Perl module, and works with Perl.

Binary compatibility is kept in upgrading unlike Perl in this point.

SPVM has a Native API for operating SPVM in cooperation with C language. In the C language level, SPVM has a way to keep the backward compatibility when upgrading.


=head1 SPVM Getting Started


Let's take SPVM for the first time. Then, let's improve the performance of the SPVM code.


=head2 First SPVM Program


Let's take SPVM for the first time. This is a first simple example. Let's calcurate the sum of numbers.


=head3 Create SPVM module


Create SPVM module. The extension is "spvm". In this example, the name of SPVM module is "SPVM/MyMath.spvm".

Create "SPVM/MyMath.spvm" in the "lib" directory, and you write the following code.

  
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



=head3 Class Definition


The C<class> keyword defines a class.

  
  # Class Definition
  class MyMath {
  
  }


See also <a href="/language.html#language-class">Class - SPVM Language Specification</a> about Class.


=head3 Method Definition


The C<method> keyword defines a method. If the method doesn't have the instance, you define a static method using a C<static> descriptor.

  
  class MyMath {
    # Static method definition
    static method sum : int ($nums : int[]) {
      
    }
  }


See also <a href="/language.html#language-method">Method - SPVM Language Specification</a> about Method.


=head3 Numeric Types


C<int> type in sum return value is signed 32bit integer type. This is same as C99 int32_t.

  
  int


SPVM has the following types as other numeric types.

=begin html

<table>
  <tr>
    <th>
      <br>SPVM numric type</br>
    </ th>
    <th>
      <br>C99 type>
    </ th>
  </tr>
  <tr>
    <td>
      <br>byte</br>
    </td>
    <td>
      int8_t
    </td>
  </tr>
  <tr>
    <td>
      <br>short</br>
    </td>
    <td>
      int16_t
    </td>
  </tr>
  <tr>
    <td>
      <br>int</br>
    </td>
    <td>
      int32_t
    </td>
  </tr>
  <tr>
    <td>
      <br>long</br>
    </td>
    <td>
      int64_t
    </td>
  </tr>
  <tr>
    <td>
      <br>float</br>
    </td>
    <td>
      float
    </td>
  <tr>
    <td>
      <br>double</br>
    </td>
    <td>
      double
    </td>
  </tr>
</table>

=end html

See also <a href="http://59.106.185.196:3000/spvmdoc-public/language.html#language-type">Type - SPVM Language Specification</a> about Type.


=head3 Array Types


C<int[]> type in sum arguments is array of int type. 

  
  int[]


The numeric array type guarantees that the values are consecutive in memory.

In this point, unlike Perl where all value are assigned to the dynamic type SV, SPVM has a static type, so it can represent a efficient sequence of numbers.

See also <a href="http://59.106.185.196:3000/spvmdoc-public/language.html#language-type">Type - SPVM Language Specification</a> about Type.


=head3 Local Variable Declaration


Write Local Variable Declaration by C<my> keyword. You can initialize variables at the same time you declare variables.

  
  my $total = 0;


The above declaration has the same meaning as:

  
  my $total : int = 0;


0 on the right side is a signed 32-bit integer, so the type of the variable is automatically determined by type inference.

See also <a href="/language.html#language-local-var">Lexical Variabe - SPVM Language Specification</a> about Lexical Variabe Declaration.

See also <a href="/language.html#language-type-inference">Type Inference - SPVM Language Specification</a> about Type Inference.


=head3 Integer Literal


0 is Integer Literal. 

  
  my $total : int = 0;


SPVM has the following Literal.

=begin html

<ul>
  <li>Integer Literal</li>
  <li>Floating Point Literal</li>
  <li>Charater Literal</li>
  <li>String Literal</li>
</ul>

=end html

  
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


See also <a href="/language.html#language-literal">Literal - SPVM Language Specification</a> about Literal.


=head3 Get Array Length


Let's look at the part where the sum of the arrays is calculated. 

  
  for (my $i = 0; $i < @$nums; $i++) {
    $total += $nums->[$i];
  }


See @$nums.

  
  @$nums


@ is Array Length Operator to get array length.

Unlike Perl, which is context sensitive, Array Length Operator of SPVM always returns the length of the array.

Note that SPVM has no context.

See <a href="/language.html#language-operator-array-length">Array Length Operator - SPVM Language Specification</a> about Array Length Operator


=head3 Increment Operator


Incremental Operator increment the value.

  
  $i++


See <a href="http://59.106.185.196:3000/spvmdoc-public/language.html#language-operator-inc">Increment Operator - SPVM Language Specification</a> about Incremental Operator.

See <a href="http://59.106.185.196:3000/spvmdoc-public/language.html#language-operator-dec">Decrement Operator - SPVM Language Specification</a> about Decrement Operator.


=head3 Array Access


Array Access can be done by "->" Arrow Operator.

  
  $nums->[$i]


See <a href="http://59.106.185.196:3000/spvmdoc-public/language.html#language-array">Array - SPVM Language Specification</a> about Array operation.


=head3 Addition Operator


See the following code.

  
  $total += $nums->[$i];


This is same as the following Additon Operator and Assignment Operator.

  
  $total = $total + $nums->[$i];


SPVM has many operators.

See <a href="/language.html#language-operator">Operator - SPVM Language Specification</a> about Opeartor.


=head3 for Statement


Next, see for Statement.

  
  for (my $i = 0; $i < @$nums; $i++) {
    $total += $nums->[$i];
  }


See <a href="/language.html#language-statement-for">for Statement - SPVM Language Specification</a> about for Statement.

See <a href="/language.html#language-statement">Statement - SPVM Language Specification</a> about Statement like if Statement, while Statement, and switch Statement.


=head3 return Statement


At last, return Statement.

  
  return $total;


See <a href="/language.html#language-statement-return">return Statement - SPVM Language Specification</a> about return Statement.



=head2 Call SPVM Method from Perl


Create "sum.pl" file  and write the following code. This is Perl program.

  
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



=head3 Add library path


The followings are the conventions and add current script directry's "lib" directory to library path .
  
  use strict;
  use warnings;
  use FindBin;
  use lib "$FindBin::Bin/lib";



=head3 use SPVM module


use SPVM module.

  
  use SPVM 'MyMath';


In this place, compilation is not done. Collect SPVM modules.


=head3 Call SPVM Method


Call SPVM Method. It's amazing that SPVM method can be called as Perl method.

  
  # Call method
  my $total = SPVM::MyMath->sum([3, 6, 8, 9]);


Perl array reference is converted to SPVM int array.

See <a href="/exchange-api.html#exchange-api-perl-data-to-spvm-value">Convert Perl Data to SPVM Value - SPVM Exchange API</a> about Conversion of Perl Data to SPVM Value.

SPVM int return value is converted to Perl Scalar.

See <a href="/exchange-api.html#exchange-api-spvm-value-to-perl-data">Converting SPVM Value to Perl Data - SPVM Exchange API</a> about Conversion of Perl Data to SPVM Value.


=head3 Call SPVM Method with packed data


you can pass packed binary data. SPVM::new_int_array_from_bin create SPVM int array from packed binary data. This is efficient.

  
  # Call method with packed data
  my $nums_packed = pack('l*', 3, 6, 8, 9);
  my $sv_nums = SPVM::new_int_array_from_bin($nums_packed);
  my $total_packed = SPVM::MyMath->sum($sv_nums);


See <a href="/exchange-api.html">SPVM Exchange API</a> about SPVM Exchange API like SPVM::new_int_array_from_bin.

<h3>How to improve SPVM Performance</h2>

See How to improve SPVM Performance.

If you're searching SPVM for performance reasons, here's what you really want to see.

=head1 How to improve SPVM Performance using SPVM Precompile and SPVM Native API

SPVM Module:

  
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


Use SPVM Module from Perl

  
  # sum.pl
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


Precompiled SPVM Method. This means SPVM code is converted to Machine Code:

  
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


Call SPVM Precompile Method from Perl

  
  # sum_precompile.pl
  use strict;
  use warnings;
  use FindBin;
  use lib "$FindBin::Bin/lib";
  
  use SPVM 'MyMath';
  
  # Call precompile method
  my $total_precompile = SPVM::MyMath->sum_precompile([3, 6, 8, 9]);
  
  print "Total Precompile: $total_precompile\n";


SPVM Native Method. This means SPVM method call C/C++ native method:

  
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
  my $config = SPVM::Builder::Config->new_gnu99;
  
  $config;


Use SPVM Native Method from Perl

  
  # sum_native.pl
  use strict;
  use warnings;
  use FindBin;
  use lib "$FindBin::Bin/lib";
  
  use SPVM 'MyMath';
  
  # Call native method
  my $total_native = SPVM::MyMath->sum_native([3, 6, 8, 9]);
  
  print "Total Native: $total_native\n";


Environment Variable "SPVM_BUILD_DIR" must be set for precompile and native method

  
  # bash example
  export SPVM_BUILD_DIR=~/.spvm_build



=head1 How to Bind C/C++/CUDA Library to SPVM


The advantage of SPVM is that you can easily bind C/C++/CUDA.

Methods bound with SPVM can be easily called from Perl.

Before reading this page, you need to understand Native API.

=begin html

<ul>
  <li><a href="/blog/20200702071424.html">How to improve SPVM Performance - Precompile and Native API</a></li>
</ul>

=end html


=head2 Binding your own C language library

First, let's bind our own C library.

The following source code is the completed source code.

I will explain using this source code.

<a href="https://github.com/yuki-kimoto/SPVM/tree/master/examples/native/bind_clib">SPVM Native Example - Bind C Library</a>

Create a C language library for summation and call it from Perl.

  
  # bind_clib.pl
  use strict;
  use warnings;
  
  use FindBin;
  use lib "$FindBin::Bin/lib";
  
  use SPVM 'BindCLib';
  
  my $total = SPVM::BindCLib->sum([1, 2, 3, 4]);
  
  print "Total: $total\n";


SPVM Method Definition.

  
  # lib/SPVM/BindCLib.spvm
  class BindCLib {
    native static method sum : int ($nums : int[]);
  }


Native Config.

  
  # lib/SPVM/BindCLib.config
  use strict;
  use warnings;
  
  use SPVM::Builder::Config;
  my $config = SPVM::Builder::Config->new_gnu99;
  
  $config;


Call C library from C program.

  
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


Notice the line reading the header.

  
  #include "bind_clib.h"


This header is included from "lib/SPVM/BindCLib.native/include/bind_clib.h". This is pure C header file.

  
  #include <inttypes.h>
  
  int32_t bind_clib_sum(int32_t* nums, int32_t length);


SPVM sets the include directory("SPVM/BindCLib.native/include") as the default header file read path.

C library source file is "lib/SPVM/BindCLib.native/src/bind_clib.c". This is pure C source file.

  
  #include "bind_clib.h"
  
  int32_t bind_clib_sum(int32_t* nums, int32_t length) {
    
    int32_t total = 0;
    for (int32_t i = 0; i < length; i++) {
      total += nums[i];
    }
    
    return total;
  }


SPVM compiles all source files in the source directory("SPVM/BindCLib.native/src"). It can contain multiple source files.

See L<SPVM:Document::NativeAPI> about the details of the native APIs.

=head2 How to bind other C Library to SPVM


If you want to know more about the bindings of other C libraries, see the example below.

=begin html

<ul>
  <li><a href="https://github.com/yuki-kimoto/SPVM/tree/master/examples/native/zlib">Bind zlib to SPVM</a></li>
  <li><a href="https://github.com/yuki-kimoto/SPVM/tree/master/examples/native/gsl">Bind GSL to SPVM</a></li>
  <li><a href="https://github.com/yuki-kimoto/SPVM/tree/master/examples/native/openmp">Bind OpenMP to SPVM</a></li>
</ul>

=end html


=head2 How to bind C++ Library to SPVM


If you want to know more about the bindings of C++ libraries to SPVM, see the example below.

=begin html

<ul>
  <li><a href="https://github.com/yuki-kimoto/SPVM/tree/master/examples/native/eigen">Bind Eigen to SPVM</a></li>
</ul>

=end html


=head2 How to bind CUDA to SPVM


If you want to know more about the bindings of CUDA to SPVM, see the example below.

=begin html

<ul>
  <li><a href="https://github.com/yuki-kimoto/SPVM/tree/master/examples/native/cuda_add">Bind CUDA to SPVM</a></li>
</ul>

=end html

=head2 Complex Values

L<SPVM::Document::Tutorial::Complex>

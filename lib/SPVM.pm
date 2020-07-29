package SPVM;

use 5.008007;
use strict;
use warnings;

use DynaLoader;
use File::Basename 'basename', 'dirname';

use SPVM::BlessedObject;
use SPVM::BlessedObject::Array;
use SPVM::BlessedObject::Package;
use FindBin;

use SPVM::Builder;
use SPVM::ExchangeAPI;

use Encode 'encode', 'decode';

use Carp 'confess';

our $VERSION = '0.0903';

my $SPVM_INITED;
my $BUILDER;

require XSLoader;
XSLoader::load('SPVM', $VERSION);

my $loaded_spvm_modules = {};

sub import {
  my ($class, $package_name) = @_;
  
  unless ($BUILDER) {
    my $build_dir = $ENV{SPVM_BUILD_DIR};
    $BUILDER = SPVM::Builder->new(build_dir => $build_dir);
  }
  
  # Add package informations
  if (defined $package_name) {
    my ($file, $line) = (caller)[1, 2];
    
    # Compile SPVM source code and create runtime env
    my $compile_success = $BUILDER->compile_spvm($package_name, $file, $line);
    unless ($compile_success) {
      exit(255);
    }
    if ($compile_success) {
      my $added_package_names = $BUILDER->get_added_package_names;
      
      # Build Precompile packages - Compile C source codes and link them to SPVM precompile subroutine
      $BUILDER->build_precompile($added_package_names);
      
      # Build native packages - Compile C source codes and link them to SPVM native subroutine
      $BUILDER->build_native($added_package_names);

      # Bind SPVM subroutine to Perl
      bind_to_perl($BUILDER, $added_package_names);
    }
  }
}

sub init {
  unless ($SPVM_INITED) {
    if (my $builder = $BUILDER) {
      # Call begin blocks
      $builder->_init;
    }
    $SPVM_INITED = 1;
  }
}

my $package_name_h = {};
my $binded_package_name_h = {};
sub bind_to_perl {
  my ($builder, $added_package_names) = @_;
  
  for my $package_name (@$added_package_names) {
    unless ($package_name_h->{$package_name}) {
      
      my $code = "package $package_name; our \@ISA = ('SPVM::BlessedObject::Package');";
      eval $code;
      
      if (my $error = $@) {
        confess $error;
      }
      $package_name_h->{$package_name} = 1;
    }

    my $sub_names = $builder->get_sub_names($package_name);
    
    for my $sub_name (@$sub_names) {
      if ($sub_name eq 'DESTROY') {
        next;
      }
      
      my $sub_abs_name = "${package_name}::$sub_name";
      
      # Define SPVM subroutine
      no strict 'refs';
      
      my ($package_name, $sub_name) = $sub_abs_name =~ /^(?:(.+)::)(.*)/;
      # Declare subroutine
      *{"$sub_abs_name"} = sub {
        SPVM::init() unless $SPVM_INITED;
        
        my $return_value;
        eval { $return_value = SPVM::call_sub($package_name, $sub_name, @_) };
        my $error = $@;
        if ($error) {
          confess $error;
        }
        $return_value;
      };
    }
  }
}

sub get_exception {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::get_exception($BUILDER->{env}, @_);
}
sub set_exception {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::set_exception($BUILDER->{env}, @_);
}
sub get_memory_blocks_count {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::get_memory_blocks_count($BUILDER->{env}, @_);
}
sub call_sub {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::call_sub($BUILDER->{env}, @_);
}
sub new_byte_array {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_byte_array($BUILDER->{env}, @_);
}
sub new_byte_array_from_bin {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_byte_array_from_bin($BUILDER->{env}, @_);
}
sub new_byte_array_from_string {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_byte_array_from_string($BUILDER->{env}, @_);
}
sub new_short_array {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_short_array($BUILDER->{env}, @_);
}
sub new_short_array_from_bin {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_short_array_from_bin($BUILDER->{env}, @_);
}
sub new_int_array {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_int_array($BUILDER->{env}, @_);
}
sub new_int_array_from_bin {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_int_array_from_bin($BUILDER->{env}, @_);
}
sub new_long_array {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_long_array($BUILDER->{env}, @_);
}
sub new_long_array_from_bin {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_long_array_from_bin($BUILDER->{env}, @_);
}
sub new_float_array {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_float_array($BUILDER->{env}, @_);
}
sub new_float_array_from_bin {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_float_array_from_bin($BUILDER->{env}, @_);
}
sub new_double_array {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_double_array($BUILDER->{env}, @_);
}
sub new_double_array_from_bin {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_double_array_from_bin($BUILDER->{env}, @_);
}
sub new_string {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_string($BUILDER->{env}, @_);
}
sub new_string_from_bin {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_string_from_bin($BUILDER->{env}, @_);
}
sub new_object_array {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_object_array($BUILDER->{env}, @_);
}
sub new_mulnum_array {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_mulnum_array($BUILDER->{env}, @_);
}
sub new_mulnum_array_from_bin {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_mulnum_array_from_bin($BUILDER->{env}, @_);
}

1;

=encoding UTF-8

=head1 NAME

SPVM - Static Perl Virtual Machine. Fast Calculation, Fast Array Operation, and Easy C/C++ Binding.

=head1 SYNOPSIS

SPVM Module:

  # lib/MyMath.spvm
  package MyMath {
    sub sum : int ($nums : int[]) {
      
      my $total = 0;
      for (my $i = 0; $i < @$nums; $i++) {
        $total += $nums->[$i];
      }
      
      return $total;
    }
  }

Use SPVM Module from Perl
  
  # spvm.pl
  use strict;
  use warnings;
  use FindBin;
  use lib "$FindBin::Bin/lib";
  
  use SPVM 'MyMath';
  
  # Call subroutine
  my $total = MyMath->sum([3, 6, 8, 9]);

  print "Total: $total\n";
  
  # Call subroutine with packed data
  my $nums_packed = pack('l*', 3, 6, 8, 9);
  my $sv_nums = SPVM::new_int_array_from_bin($nums_packed);
  my $total_packed = MyMath->sum($sv_nums);
  
  print "Total Packed: $total_packed\n";

Precompiled SPVM Subroutine. This means SPVM code is converted to Machine Code:

  # lib/MyMath.spvm
  package MyMath {
    precompile sub sum_precompile : int ($nums : int[]) {
      
      my $total = 0;
      for (my $i = 0; $i < @$nums; $i++) {
        $total += $nums->[$i];
      }
      
      return $total;
    }
  }

Call SPVM Precompile Subroutine from Perl

  # spvm.pl
  use strict;
  use warnings;
  use FindBin;
  use lib "$FindBin::Bin/lib";
  
  use SPVM 'MyMath';
  
  # Call precompile subroutine
  my $total_precompile = MyMath->sum_precompile([3, 6, 8, 9]);
  
  print "Total Precompile: $total_precompile\n";

SPVM Native Subroutine. This means SPVM subroutine call C/C++ native subroutine:

  # lib/MyMath.spvm
  package MyMath {
    native sub sum_native : int ($nums : int[]);
  }
  
  // lib/MyMath.c
  #include "spvm_native.h"
  
  int32_t SPNATIVE__MyMath__sum_native(SPVM_ENV* env, SPVM_VALUE* stack) {
    
    void* sv_nums = stack[0].oval;
    
    int32_t length = env->length(env, sv_nums);
    
    int32_t* nums = env->get_elems_int(env, sv_nums);
    
    int32_t total = 0;
    for (int32_t i = 0; i < length; i++) {
      total += nums[i];
    }
    
    stack[0].ival = total;
    
    return SPVM_SUCCESS;
  }
  
  # lib/MyMath.config

  use strict;
  use warnings;

  use SPVM::Builder::Config;
  my $bconf = SPVM::Builder::Config->new_c99;

  $bconf;

Use SPVM Native Subroutine from Perl
  
  # spvm.pl
  use strict;
  use warnings;
  use FindBin;
  use lib "$FindBin::Bin/lib";
  
  use SPVM 'MyMath';
  
  # Call native subroutine
  my $total_native = MyMath->sum_native([3, 6, 8, 9]);
  
  print "Total Native: $total_native\n";

Environment Variable "SPVM_BUILD_DIR" must be set for precompile and native subroutine
  
  # bash example
  export SPVM_BUILD_DIR=~/.spvm_build

=head1 DESCRIPTION

SPVM is Static Perl Virtual Machine. Provide fast calculation & easy C/C++ Binding.

B<Features:>

=over 4

=item * B<Fast culcuration>, B<Fast array operation>, B<Small memory>

=item * B<Perl syntax>, B<Static typing>, B<Switch syntax>, B<Have language specification>

=item * B<Enum>, B<Type inference>, B<Anon subroutine>, B<Variable captures>

=item * B<Array initialization>, 

=item * B<Reference count GC>, B<Weaken reference>, B<Module system>

=item * B<Exception>, B<Package variable>

=item * B<Object oriented>, B<Inteface>, B<Value type>, B<Value array type>, B<Reference type>

=item * B<Easy way to C/C++ binding>, B<Automatically Perl binding>, B<C99 math functions>

=item * B<Shared Library>, B<Precompile Subroutine into Machine code>

=item * B<Native API(C level api)>, B<C99 standard>

=back

=head1 DOCUMENT

Currently some ports of document are use Automatic translation, so not accurate and maybe difficult to read.

=over 2

=item * L<SPVM Document|https://yuki-kimoto.github.io/spvmdoc-public>

=item * L<SPVM Tutorial|https://yuki-kimoto.github.io/spvmdoc-public/tutorial.html>

=item * L<SPVM Language Specification|https://yuki-kimoto.github.io/spvmdoc-public/language.html>

=item * L<SPVM Exchange API|https://yuki-kimoto.github.io/spvmdoc-public/exchange-api.html>

=item * L<SPVM Native API|https://yuki-kimoto.github.io/spvmdoc-public/native-api.html>

=item * L<SPVM Performance Benchmark|https://yuki-kimoto.github.io/spvmdoc-public/benchmark.html>

=head1 CORE MODULES

SPVM Core Modules.

=over 2

=item * L<SPVM::Byte>

=item * L<SPVM::ByteList>

=item * L<SPVM::Cloner>

=item * L<SPVM::Comparator>

=item * L<SPVM::Complex_2b>

=item * L<SPVM::Complex_2d>

=item * L<SPVM::Complex_2f>

=item * L<SPVM::Complex_2i>

=item * L<SPVM::Complex_2l>

=item * L<SPVM::Complex_2s>

=item * L<SPVM::Double>

=item * L<SPVM::DoubleList>

=item * L<SPVM::EqualityChecker>

=item * L<SPVM::EqualityChecker::SameObject>

=item * L<SPVM::Float>

=item * L<SPVM::FloatList>

=item * L<SPVM::Hash>

=item * L<SPVM::Hash::Entry>

=item * L<SPVM::Int>

=item * L<SPVM::IntList>

=item * L<SPVM::IO::File>

=item * L<SPVM::IO::FileHandle>

=item * L<SPVM::IO::Stderr>

=item * L<SPVM::IO::Stdout>

=item * L<SPVM::Long>

=item * L<SPVM::LongList>

=item * L<SPVM::Math>

=item * L<SPVM::NDArray::Byte>

=item * L<SPVM::NDArray::ComplexByte>

=item * L<SPVM::NDArray::ComplexDouble>

=item * L<SPVM::NDArray::ComplexFloat>

=item * L<SPVM::NDArray::ComplexInt>

=item * L<SPVM::NDArray::ComplexLong>

=item * L<SPVM::NDArray::ComplexShort>

=item * L<SPVM::NDArray::Double>

=item * L<SPVM::NDArray::Float>

=item * L<SPVM::NDArray::Int>

=item * L<SPVM::NDArray::Long>

=item * L<SPVM::NDArray::QuatByte>

=item * L<SPVM::NDArray::QuatDouble>

=item * L<SPVM::NDArray::QuatFloat>

=item * L<SPVM::NDArray::QuatInt>

=item * L<SPVM::NDArray::QuatLong>

=item * L<SPVM::NDArray::QuatShort>

=item * L<SPVM::NDArray::Short>

=item * L<SPVM::NDArray::String>

=item * L<SPVM::ObjectList>

=item * L<SPVM::Quat_4b>

=item * L<SPVM::Quat_4d>

=item * L<SPVM::Quat_4f>

=item * L<SPVM::Quat_4i>

=item * L<SPVM::Quat_4l>

=item * L<SPVM::Quat_4s>

=item * L<SPVM::Regex>

=item * L<SPVM::Regex::Pattern>

=item * L<SPVM::Regex::Replacer>

=item * L<SPVM::Short>

=item * L<SPVM::ShortList>

=item * L<SPVM::Sort>

=item * L<SPVM::StringBuffer>

=item * L<SPVM::Stringer>

=item * L<SPVM::StringList>

=item * L<SPVM::Time>

=item * L<SPVM::Time::Info>

=item * L<SPVM::Unicode>

=item * L<SPVM::Util>

=back

=head1 GETTING STARTED

Get started with SPVM.

At first I will explain how to write for statement in SPVM.

Next, I will explain how to precompile SPVM subroutines so that they run at the same speed as in machine language.

Finally, I will explain how to write SPVM subroutines biding C language.

If you are interested in the SPVM tutorial, see SPVM Tutorial.

L<SPVM Tutorial|https://yuki-kimoto.github.io/spvmdoc-public/tutorial.html>

=head2 How to write SPVM language

This is a simple example using the SPVM for statement.

  # lib/MyMath.spvm
  package MyMath {
    sub sum : int ($nums : int[]) {
      
      my $total = 0;
      for (my $i = 0; $i < @$nums; $i++) {
        $total += $nums->[$i];
      }
      
      return $total;
    }
  }

You create "lib" direcotry and create "MyMath.spvm" file.

The extension of SPVM is ".spvm".

SPVM need package definition.

  package MyMath {

  }

See SPVM subroutine definition.

  package MyMath {
    sub sum : int ($nums : int[]) {
    
    }
  }

"int" after subroutine name "sum" is return value type.

"int" is signed 32bit numeric type.

"int[]" is argument type.

"int[]" is array type that element type is "int".

SPVM is static type language. You must specify subroutine return type and argument type.

See subroutine implementation.

    sub sum : int ($nums : int[]) {
      
      my $total = 0;
      for (my $i = 0; $i < @$nums; $i++) {
        $total += $nums->[$i];
      }
      
      return $total;
    }

"my" is lexical variable declaration. 

  my $total = 0;

There is no type declaration. Type inference is performed using the value on the right side. Same as the description below.

  my $total :int = 0;

See for loop.

      for (my $i = 0; $i < @$nums; $i++) {
        $total += $nums->[$i];
      }

for loop is same as Perl syntax. You can get array length by @. @ is array length operator in all context instead of Perl.

Array access use arrow operator.

  $nums->[$i]

At last, return value.

      return $total;

If you want to know the syntax of SPVM, the SPVM Language Specification has a complete description.

L<SPVM Language Specification|https://yuki-kimoto.github.io/spvmdoc-public/language.html>

=head2 How to call SPVM subroutine from Perl

You may be surprised to know that SPVM subroutines can be called directly from Perl.
  
  use FindBin;
  use lib "$FindBin::Bin/lib";
  
  use SPVM 'MyMath';
  
  # Call subroutine
  my $total = MyMath->sum([3, 6, 8, 9]);
  
  print $total . "\n";

To load an SPVM module from Perl, use the following syntax.

  use SPVM 'MyMath';

Call SPVM subroutine from Perl.

  # Call subroutine
  my $total = MyMath->sum([3, 6, 8, 9]);

Perl array reference is converted to SPVM int array, and call sum method of MyMath, and SPVM int value of return value is converted to Perl Scalar.

If you want to know the rules for calling SPVM subroutines from Perl, and the rules for converting Perl and SPVM values, see the SPVM Exchagne API.

L<SPVM Exchange API|https://yuki-kimoto.github.io/spvmdoc-public/exchange-api.html>

=head2 How to improve performacne using subroutine precompile

See how to speed up SPVM subroutines. SPVM subroutines can be converted into machine code by precompile descriptor.

  # lib/MyMath.spvm
  package MyMath {
    precompile sub sum_precompile : int ($nums : int[]) {
      
      my $total = 0;
      for (my $i = 0; $i < @$nums; $i++) {
        $total += $nums->[$i];
      }
      
      return $total;
    }
  }

Subroutine code is same as non precompile subroutine.

A build directory is required to precompile subroutines.

You set SPVM_BUILD_DIR. The following is bash example.

  # ~/.bashrc
  export SPVM_BUILD_DIR=~/.spvm_build

How fast will it be? See SPVM Peformance Benchmark.

L<SPVM Performance Benchmark|https://yuki-kimoto.github.io/spvmdoc-public/benchmark.html>

=head2 How to improve performacne using native subroutine

If you want, you can native subroutine for performance with native descriptor.

  # lib/MyMath.spvm
  package MyMath {
    native sub sum_native : int ($nums : int[]);
  }

Native subrosutine is binding a function of C langage.
  
  // lib/MyMath.c
  #include "spvm_native.h"
  
  int32_t SPNATIVE__MyMath__sum_native(SPVM_ENV* env, SPVM_VALUE* stack) {
    
    void* sv_nums = stack[0].oval;
    
    int32_t length = env->length(env, sv_nums);
    
    int32_t* nums = env->get_elems_int(env, sv_nums);
    
    int32_t total = 0;
    for (int32_t i = 0; i < length; i++) {
      total += nums[i];
    }
    
    stack[0].ival = total;
    
    return SPVM_SUCCESS;
  }

File name is "MyMath.c". 

At first, include "spvm_native.h". This header provide SPVM Native API.

  #include "spvm_native.h"

See the declaration of C function.

  int32_t SPNATIVE__MyMath__sum_native(SPVM_ENV* env, SPVM_VALUE* stack) {

    return SPVM_SUCCESS;
  }

Return value type is int32_t. The return value indicates that the subroutine did not throw an exception.

SPVM_SUCCESS is macro that value is 0 defined in "spvm_native.h".

C function name start SPNATIVE__. Package name "MyMath" and subroutine name "sum_native" is joined by "__".

If package name contains double colon(Foo::Bar), double colon is replaced by "__".

First argument is a pointer to SPVM_ENV object. This variable has SPVM runtime information.

Second argument is SPVM_VALUE array. stack contains arguments of SPVM subroutine.

And stack is also used to set return value of SPVM subroutine.

See implementation of C function.

  int32_t SPNATIVE__MyMath__sum_native(SPVM_ENV* env, SPVM_VALUE* stack) {
    
    void* sv_nums = stack[0].oval;
    
    int32_t length = env->length(env, sv_nums);
    
    int32_t* nums = env->get_elems_int(env, sv_nums);
    
    int32_t total = 0;
    for (int32_t i = 0; i < length; i++) {
      total += nums[i];
    }
    
    stack[0].ival = total;
    
    return SPVM_SUCCESS;
  }

At first, get first argument of SPVM subroutine.

    void* sv_nums = stack[0].oval;

"int[]" is array type. array type is also object type. You can get a object by C<oval> field.

Get array length.

    int32_t length = env->length(env, sv_nums);

Get numeric int32_t array of C langage. SPVM int type is same as int32_t type of C language.

    int32_t* nums = env->get_elems_int(env, sv_nums);

Calcuration.

    int32_t total = 0;
    for (int32_t i = 0; i < length; i++) {
      total += nums[i];
    }

At last, set return value to the first element of stack as int type. C<ival> filed is used to get or set int32_t value.

    stack[0].ival = total;

Note that you do not return the SPVM return value with the return keyword of C langauge.

return value of C function indicates whether the subroutine throw an exception.

If you write a native subroutine, you must write a configuration file.

The configuration file for native subroutines is a Perl script.

  # lib/MyMath.config

  use strict;
  use warnings;

  use SPVM::Builder::Config;
  my $bconf = SPVM::Builder::Config->new_c99;

  $bconf;

If you write SPVM subroutine using C language, you can use C<new_c99> method of L<SPVM::Builder::Config>.

If you want to see SPVM Native API like length and get_elems_int

    int32_t length = env->length(env, sv_nums);
    
    int32_t* nums = env->get_elems_int(env, sv_nums);

See SPVM Native API.

L<SPVM Native API|https://yuki-kimoto.github.io/spvmdoc-public/native-api.html>

A build directory is required to native subroutines.

You set SPVM_BUILD_DIR. The following is bash example.

  # ~/.bashrc
  export SPVM_BUILD_DIR=~/.spvm_build

How fast will it be? See SPVM Peformance Benchmark.

L<SPVM Performance Benchmark|https://yuki-kimoto.github.io/spvmdoc-public/benchmark.html>

=head1 ENVIRONMENT VARIABLE

=head2 SPVM_BUILD_DIR

SPVM build directory for precompile and native subroutine.

If SPVM_BUILD_DIR environment variable is not set, SPVM can't compile precompile subroutine and native subroutine, and a exception occur. You see error message "SPVM_BUILD_DIR environment variable must be set ...".

In bash, you can set SPVM_BUILD_DIR to the following.

  export SPVM_BUILD_DIR=~/.spvm_build

=head1 CAUTION

This release is beta release before SPVM 1.0. Features is changed without warnings. 

SPVM 1.0 is First Major Release

But Full backward compatibility is not guaranteed because SPVM is not used much in corporate work yet.

If SPVM has fatal bugs in the specification or implementation, the backward compatibility is broken and the bug will be fixed after discussion.

=head1 SUPPORT

If you have problems or find bugs, comment to GitHub Issue.

L<SPVM(GitHub)|https://github.com/yuki-kimoto/SPVM>.

=head1 AUTHOR

Yuki Kimoto E<lt>kimoto.yuki@gmail.com<gt>

=head1 CORE DEVELOPERS

moti<lt>motohiko.ave@gmail.com<gt>

=head1 CONTRIBUTERS

=over 2

=item * Mohammad S Anwar

=item * akinomyoga

=item * NAGAYASU Shinya

=item * Reini Urban

=item * chromatic

=item * Kazutake Hiramatsu

=back

=head1 COPYRIGHT & LICENSE

Copyright 2018-2020 Yuki Kimoto, all rights reserved.

This program is free software; you can redistribute it and/or modify it
under the same terms as Perl itself.

=cut

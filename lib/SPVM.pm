package SPVM;

use 5.008007;
use strict;
use warnings;

use DynaLoader;
use File::Basename 'basename', 'dirname';

use SPVM::Data;
use SPVM::Data::Array;
use SPVM::Data::Package;
use FindBin;

use SPVM::Builder;
use SPVM::ExchangeAPI;

use Encode 'encode', 'decode';

use Carp 'confess';

our $VERSION = '0.0427';

my $SPVM_ENV;
my $BUILDER;

require XSLoader;
XSLoader::load('SPVM', $VERSION);

sub import {
  my ($class, $package_name) = @_;
  
  unless ($BUILDER) {
    my $build_dir;
    if (defined $ENV{SPVM_BUILD_DIR}) {
      $build_dir = $ENV{SPVM_BUILD_DIR};
    }
    else {
      $build_dir = "$FindBin::Bin/spvm_build";
    }
    $BUILDER = SPVM::Builder->new(build_dir => $build_dir);
  }

  # Add package informations
  if (defined $package_name) {
    my ($file, $line) = (caller)[1, 2];
    my $package_info = {
      name => $package_name,
      file => $file,
      line => $line
    };
    push @{$BUILDER->{package_infos}}, $package_info;
  }
}

# Compile SPVM source code just after compile-time of Perl
CHECK {
  if ($BUILDER) {
    my $compile_success = $BUILDER->build_spvm;
    unless ($compile_success) {
      exit(255);
    }
    
    # Set env
    $SPVM_ENV = $BUILDER->{env};
    
    # Call begin blocks
    $BUILDER->call_begin_blocks;
  }
}


sub set_exception_undef { SPVM::ExchangeAPI::set_exception_undef($SPVM_ENV, @_) }
sub memory_blocks_count { SPVM::ExchangeAPI::memory_blocks_count($SPVM_ENV, @_) }
sub call_sub { SPVM::ExchangeAPI::call_sub($SPVM_ENV, @_) }

sub new_barray { SPVM::ExchangeAPI::new_barray($SPVM_ENV, @_) }
sub new_barray_from_bin { SPVM::ExchangeAPI::new_barray_from_bin($SPVM_ENV, @_) }
sub new_barray_from_str { SPVM::ExchangeAPI::new_barray_from_str($SPVM_ENV, @_) }

sub new_sarray { SPVM::ExchangeAPI::new_sarray($SPVM_ENV, @_) }
sub new_sarray_from_bin { SPVM::ExchangeAPI::new_sarray_from_bin($SPVM_ENV, @_) }

sub new_iarray { SPVM::ExchangeAPI::new_iarray($SPVM_ENV, @_) }
sub new_iarray_from_bin { SPVM::ExchangeAPI::new_iarray_from_bin($SPVM_ENV, @_) }

sub new_larray { SPVM::ExchangeAPI::new_larray($SPVM_ENV, @_) }
sub new_larray_from_bin { SPVM::ExchangeAPI::new_larray_from_bin($SPVM_ENV, @_) }

sub new_farray { SPVM::ExchangeAPI::new_farray($SPVM_ENV, @_) }
sub new_farray_from_bin { SPVM::ExchangeAPI::new_farray_from_bin($SPVM_ENV, @_) }

sub new_darray { SPVM::ExchangeAPI::new_darray($SPVM_ENV, @_) }
sub new_darray_from_bin { SPVM::ExchangeAPI::new_darray_from_bin($SPVM_ENV, @_) }

sub new_str { SPVM::ExchangeAPI::new_str($SPVM_ENV, @_) }
sub new_str_from_bin { SPVM::ExchangeAPI::new_str_from_bin($SPVM_ENV, @_) }

sub new_oarray { SPVM::ExchangeAPI::new_oarray($SPVM_ENV, @_) }
sub new_varray { SPVM::ExchangeAPI::new_varray($SPVM_ENV, @_) }
sub new_varray_from_bin { SPVM::ExchangeAPI::new_varray_from_bin($SPVM_ENV, @_) }

1;

=encoding UTF-8

=head1 NAME

SPVM - Static Perl Virtual Machine. Fast calcuration & Easy C/C++ Binding

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
  
  use FindBin;
  use lib "$FindBin::Bin/lib";
  
  use SPVM 'MyMath';
  
  # New int array
  my $sp_nums = SPVM::new_iarray([3, 6, 8, 9]);
  
  # Call subroutine
  my $total = MyMath->sum($sp_nums);
  
  print $total . "\n";

=head1 DESCRIPTION

SPVM is Static Perl Virtual Machine. Provide fast calcuration & easy C/C++ Binding.

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

=item * B<Dynamic linking>, B<Subroutine precompile>, B<AOT compile(create exe file)>

=item * B<Native API(C level api)>, B<C99 standard>

=back

=head1 DOCUMENT

=head2 Standard Functions

  print, warn, time

L<SPVM::CORE> - Standard Functions

=head2 Standard Modules

L<SPVM::Byte>, L<SPVM::Short>, L<SPVM::Int>, L<SPVM::Long>, L<SPVM::Float>, L<SPVM::Double>

=head2 Exchange API

L<SPVM::Document::ExchangeAPI> - Exchange API is perl functions to exchange Perl data to SPVM data, and reverse.

=head2 Native API

L<SPVM::Document::NativeAPI> - Native API is C level functions to manipulate SPVM data.

=head2 Extension

L<SPVM::Document::Extension> - Extension is the way to C/C++ Binding to SPVM

=head2 Language Specification

L<SPVM::Document::Language> - SPVM Language Specification

=head1 EXAMPLES

=head2 How to use SPVM from Perl

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
  
  use FindBin;
  use lib "$FindBin::Bin/lib";
  
  use SPVM 'MyMath';
  
  # New int array
  my $sp_nums = SPVM::new_iarray([3, 6, 8, 9]);
  
  # Call subroutine
  my $total = MyMath->sum($sp_nums);
  
  print $total . "\n";

See also L<SPVM::Document::ExchangeAPI>.

=head2 Package Declaration

Package can contain field declaration, subroutine declaration.

  package Point {
    has x : int;
    has y : int;
    
    sub new : Point ($x : int, $y : int) {
      my $self = new Point;
      
      $self->{x} = $x;
      $self->{y} = $y;
      
      return $self;
    }
    sub clear ($self : self) {
      $self->{x} = 0;
      $self->{y} = 0;
    }
  }

Package can also contain package variable declaration and enumeration declaration and use declaration.

  package Foo {
    use Point;
    
    our $FOO : int;
    our $BAR : int;
    
    enum {
      FLAG1
      FLAG2;
    }
  }

=head2 Use Module

  use Point;

=head2 Field Declaration

  has x : int;
  has y : long;

Field is public by default.

You can make field private by private keyword.

  has x : private int;

=head2 Subroutine Declaration

  sub sub : int ($num1 : int, $num2 : int) {
    return $num1 + $num2;
  }

=head2 Variable Declaration
  
  my $num : int;
  my $nums : int[];

Exmpales:
  
  # Numeric Type
  my $value : byte;
  my $value : short;
  my $value : int;
  my $value : long;
  my $value : float;
  my $value : double;
  my $obj : Point;
  
  # Array Type
  my $values : byte[];
  my $values : short[];
  my $values : int[];
  my $values : long[];
  my $values : float[];
  my $values : double[];
  my $values : Point[];

  # Multiple Dimension Array Type
  my $values : byte[][];
  my $values : short[][];
  my $values : int[][];
  my $values : long[][];
  my $values : float[][];
  my $values : double[][];
  my $values : Point[][];
  
You can initialize variable.

  my $value : int = 1;

You can omit type name if initial value is exists. This is type inference.

  my $value = 1;

=head2 Type Inference

If the Type of right value is known, the type of left value is automatically decided.

  my $num = 2;
  my $obj = new Foo;
  my $values = new int[3];

Above is same as the following.

  my $num : int = 2;
  my $obj : Foo = new Foo;
  my $values : int[3] = new int[3];

=head2 Number Literal

=head3 Int Literal

Int Literal is composed of 

   [+|-][0x][0123456789abcdefABCDEF]...[L|f|d]

For example:

  123
  -123
  0xff
  0xFF
  123L
  123d

Default Number Literal Type is C<int>.
  
  # Type is int
  123

You can use hex number literal by start C<0x>.

C<a>, C<b>, C<c>, C<d>, C<e>, C<f>, C<A>, C<B>, C<C>, C<D>, C<E>, C<F> is used as hex number.

  0xAF
  0xaf

You can use octal number literal by start C<0>.

  0x177
  0x777

You can use binary number literal by start C<0b>.

  0b101
  0b001

You can use under line C<_> in number literal. Under line is meanless, only for visuality.

  123_456
  0xAB_CD

You can use type specifier to specify integer leteral type.

=over 2

=item * L
  
  # Long
  123L

=item * f
  
  # Float
  123f

=item * d

  # Double
  123d

=back

=head3 Floating Point Literal

If you use C<.> in number literal, the number is floating point literal. Default type of floating point value is C<double>.

  1.23
  -1.23

You can use C<E> or C<e> to specify exponential notation.

  1.23E+12
  1.23E-12
  1.23e+12
  1.23e-12

You can use type specifier to specify integer leteral type.

=over 2

=item * f
  
  # Float
  1.23f

=item * d

  # Double
  1.23d

=back

If you know more Type, see L</"Type"> section.

=head2 String length

  my $string_length = length "abc";

=head2 String Literal

String Literal is the following.

  "abc"

Type of String literal is C<const byte[]>.

  my $string : const byte[] = "abc";

C<string> is short name of C<const byte[]>. You can also write the following.

  my $string : string = "abc";

If you use type inference, you can also write the follwoing.

  my $string = "abc";

=head3 Escape Sequences

A character preceded by a backslash (\) is an escape sequence and has special meaning to the compiler. The following table shows the SPVM escape sequences:

  [Escape Sequences]    [Escape Sequence	Description]
  \t                    Insert a tab in the text at this point.
  \b                    Insert a backspace in the text at this point.
  \n                   	Insert a newline in the text at this point.
  \r                    Insert a carriage return in the text at this point.
  \f                    Insert a formfeed in the text at this point.
  \'                    Insert a single quote character in the text at this point.
  \"                    Insert a double quote character in the text at this point.
  \\                    Insert a backslash character in the text at this point.

=head2 Undefined Literal

Undefined Literal is:

  undef

=head2 Type

=head3 Numeric Type

Numeric types are C<byte>, C<short>, C<int>, C<long>, C<float>, C<double>.
  
  [Type]  [Type Description]   [Type Bit Size]
  byte    Integral type        8-bit
  short   Integral type        16-bit
  int     Integral type        32-bit
  long    Integral type        64-bit
  float   floating-point type  32-bit
  double  floating-point type  64-bit

Numeric values do not share state with other numeric values.

The numeric types are the integral types and the floating-point types.

The integral types are byte, short, int, and long, whose values are 8-bit, 16-bit, 32-bit and 64-bit
signed two's-complement integers.

The floating-point types are float, whose values include the 32-bit IEEE 754 floating-point numbers, and double,
whose values include the 64-bit IEEE 754 floating-point numbers.

B<The values of the integral types are integers in the following ranges:>

For byte, from -128 to 127, inclusive

For short, from -32768 to 32767, inclusive

For int, from -2147483648 to 2147483647, inclusive

For long, from -9223372036854775808 to 9223372036854775807, inclusive

B<Varialbe Definition>

Varialbe Definition with Type is the following.

  my $value : byte;
  my $value : short;
  my $value : int;
  my $value : long;
  my $value : float;
  my $value : double;

If you know more Variable Declaration, see L</"Variable Declaration"> section.

=head3 Array Type

Array Type describe multiple values.

  [Type]         [Type Description]
  byte[]         byte array
  short[]        short array
  int[]          int array array
  long[]         long array
  float[]        float array
  doube[]        double array
  PackageName[]  object array

Array Type is a Object Type. You can create Array by C<new> keyword.

  my $values : int[] = new int[3];

If you know more Array Creating, see L</"New Array"> section.

=head3 Multiple Dimention Array Type

Multiple Dimention Array Type is a Array Type.
  
B<Two Dimension Array Type>

  byte[][];
  short[][];
  int[][];
  long[][];
  float[][];
  double[][];
  PackageName[][];
  
B<Three Dimension Array Type>

  byte[][][];
  short[][][];
  int[][][];
  long[][][];
  float[][][];
  double[][][];
  PackageName[][][];
  
Max Dimension is C<255>.

You can create Multiple Dimension Array by C<new> keyword.

  my $values : int[][] = new int[][3];

This mean that Multiple Dimension Array is created, the multiple dimension array have 3 C<int[]> type array.
The elems is initialized by C<undef>.

If you know Multiple Dimension Array Creating, see L</"New Multiple Dimention Array">.

=head3 Package Type

If Package is defined, Package name is used as Type.

  PackageName

If you know more Package Definition, see L</"Package Definition"> section.

You can create Object by C<new> subroutine. This is Default Constructor.

  my $obj : PackageName = PackageName->new;

=head2 New Array

Array is created by new. Elements values is not initialized.

  my $values = new byte[3];
  my $values = new short[3];
  my $values = new int[3];
  my $values = new long[3];
  my $values = new float[3];
  my $values = new double[3];

=head2 Array Initialization

Array Initialization Syntax:

  my $values = new int[] {1, 2, 3};
  my $points = new Point[] {Point->new(), Point->new(), Point->new()};

=head2 Array Manipulation

=head3 Get Array Length

You can use the three ways to get Array Length.

  @$values;
  @{$values};
  len $values;

=head3 Get and Set Array Element

Get Array Element:

  # Get
  $values->[0];

Set Array Element:

  # Set
  $values->[0] = 5;

=head2 Object Manipulation

=head3 Field Access

Get field:

  # Get field
  $object->{foo};

Set field:

  # Set field;
  $object->{foo} = 5;

Field value is private. You can only use Field Access from self package.

=head2 Condition branch

  if (1) {

  }
  elsif (2) {

  }
  else {

  }

=head2 Loop Syntax

=head3 for statement

  my $values = new int[10];
  for (my $i = 0; $i < @$values; $i++) {
    $values->[$i] = 0;
  }

=head3 while statement

  my $values = new int[10];
  my $i = 0;
  while ($i < @$values) {
    $values->[$i] = 0;
  }

=head2 Comment

Comment:

  # Comment

=head2 POD

Pod syntax:

  =pod
    AAAA
    BBBB
  =cut

=head2 __END__

Script Ending:

  __END__

=head2 Exception

=head3 Throw Exception

Throw Exception:

  die "Error";

=head3 Catch Exception

Catch Exception:

  eval {
    die "Error";
  };

=head3 Exception Message

  if (my $error = $@) {
    
  }

Exception message is assigned to $@.

=head2 Constructor

=head3 new operator

Constructor is C<new> operator.

  new Point;

C<new> operator is private. C<new> operator is only used in same package.

=head3 Constructor

If C<new> subroutine is not defined, Default Constructor is defined automatically.

  sub new ($class : class) { return new Point }

This is used from other package.

  my $point = Point->new();

=head2 Destructor

Destructor.
  
  package Foo {
  
    sub DESTROY : void ($self : Foo) {
      
    }
  }

=head2 Enumeration

  package Foo {
    enum {
      ONE,
      TWO,
      THREE
    }
    
    enum {
      FORE = 4,
      FIVE,
    }
  }

Enumeration default value is 0. and up to 1, 2, 3 if value is not specified.

=head2 Weak Reference

  weaken $foo->{bar};
  weaken $foo->[0];

=head2 Extension native function

  package TestCase::Extension {
    native sub sum : int ($num1 : int, $num2 : int);
  }

=head2 Operators

=head3 Assign Operator

  my $foo = 1;

B<Special Assign Operator>

  +=
  -=
  *=
  /=
  &=
  |=
  ^=
  %=
  <<=
  >>=
  >>>=

=head2 Basic Operator

  +
  -
  *
  /
  %

=head3 Comparison Operator

  ==
  !=
  >
  <
  <=
  >=

=head3 Logical Operator

  &&
  ||
  !

=head3 Bit Operator

  <<
  >>
  >>>
  &
  |
  ^
  ~

=head3 Increment/Decrement Operator

  ++
  --

=head2 C Extension using SPVM

SPVM Module:

  # lib/MyMathNative.spvm
  package MyMathNative {
    
    # Sub Declaration
    native sub sum int ($nums : int[]);
  }

C Source File;

  // lib/MyMathNative.native.c
  #include <spvm_native.h>

  int32_t SPNATIVE__MyMathNative__sum(SPVM_ENV* env, SPVM_VALUE* stack) {
    
    // First argument
    void* sp_nums = stack[0].oval;
    
    // Array length
    int32_t length = env->len(env, sp_nums);
    
    // Elements pointer
    int32_t* nums = env->ielems(env, sp_nums);
    
    // Culcurate total
    int32_t total = 0;
    {
      int32_t i;
      for (i = 0; i < length; i++) {
        total += nums[i];
      }
    }
    
    // Return value is set to stack[0]
    stack[0].ival = total;
    
    // If function success, return SPVM_SUCCESS
    return SPVM_SUCCESS;
  }

Use Extension Module from Perl:

  use FindBin;
  use lib "$FindBin::Bin/lib";
  
  # Use SPVM module
  use SPVM 'MyMathNative';
  
  # New SPVM int array
  my $sp_nums = SPVM::new_iarray([3, 6, 8, 9]);
  
  # Call SPVM subroutine
  my $total = MyMathNative->sum($sp_nums);
  
  print $total . "\n";

See also L<SPVM::Document::Extension>, L<SPVM::Document::NativeAPI>.

=head1 ENVIRONMENT VARIABLE

=head2 SPVM_BUILD_DIR

SPVM build directory for precompile and native subroutine.

If SPVM_BUILD_DIR environment variable is not specified, spvm_build directory of script directory is set to build directory.

For exmple, If your script is placed at "/path/app.pl", build directory is "/path/spvm_build".

=head1 NOTE

B<SPVM is before 1.0 under development! I will change implementation and specification without warnings.>

=head1 SUPPORT

If you have problems or find bugs, comment to GitHub Issue.

L<SPVM(GitHub)|https://github.com/yuki-kimoto/SPVM>.

=head1 AUTHOR

Yuki Kimoto E<lt>kimoto.yuki@gmail.com<gt>

=head1 CORE DEVELOPER

moti<lt>motohiko.ave@gmail.com<gt>

=head1 CONTRIBUTERS

akinomyoga, NAGAYASU Shinya, Reini Urban, chromatic, Kazutake Hiramatsu

=head1 COPYRIGHT & LICENSE

MIT License

Copyright (c) [2018] [Yuki Kimoto]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

=cut

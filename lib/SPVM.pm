package SPVM;

use 5.008007;
use strict;
use warnings;

use SPVM::BaseObject;
use SPVM::Object;
use SPVM::Array;
use Encode 'encode';

use Carp 'croak';

my $INT_MAX = 2147483647;

our $VERSION = '0.0222';

our $COMPILER;
our @PACKAGE_INFOS;
our %PACKAGE_SYMTABLE;
our %FIELD_SYMTABLE;
our %SUB_SYMTABLE;
our %TYPE_SYMTABLE;
our $API;

# Compile SPVM source code just after compile-time of Perl
CHECK {
  # Compile SPVM source code
  compile();
  
  # Build resolved type symbol table
  build_type_symtable();
  
  # Build subroutine symbol table
  build_sub_symtable();
  
  # Build package symbol table
  build_package_symtable();
  
  # Build field symbol table
  build_field_symtable();
  
  # Build SPVM subroutine
  build_spvm_subs();
  
  # Build run-time
  build_runtime();
  
  # Free compiler
  free_compiler();
}

sub new_string_raw {
  my $string = shift;
  
  my $array = SPVM::Array->malloc_string_raw($string);
  
  return $array;
}

sub new_string {
  my $string = shift;
  
  $string = Encode::encode('UTF-8', $string);
  
  my $array = SPVM::Array->malloc_string_raw($string);
  
  return $array;
}

sub new_byte_array {
  my $elements = shift;
  
  if (ref $elements ne 'ARRAY') {
    croak "Argument must be array reference";
  }
  
  my $length = @$elements;
  
  my $array = SPVM::Array->malloc_byte_array($length);
  
  $array->set_byte_array_elements($elements);
  
  return $array;
}

sub new_short_array {
  my $elements = shift;
  
  if (ref $elements ne 'ARRAY') {
    croak "Argument must be array reference";
  }
  
  my $length = @$elements;
  
  my $array = SPVM::Array->malloc_short_array($length);
  
  $array->set_short_array_elements($elements);
  
  return $array;
}

sub new_short_array_len {
  my $length = shift;
  
  my $array = SPVM::Array->malloc_short_array($length);
  
  return $array;
}

sub new_int_array {
  my $elements = shift;
  
  if (ref $elements ne 'ARRAY') {
    croak "Argument must be array reference";
  }
  
  my $length = @$elements;
  
  my $array = SPVM::Array->malloc_int_array($length);
  
  $array->set_int_array_elements($elements);
  
  return $array;
}

sub new_int_array_len {
  my $length = shift;
  
  my $array = SPVM::Array->malloc_int_array($length);
  
  return $array;
}

sub new_long_array {
  my $elements = shift;
  
  if (ref $elements ne 'ARRAY') {
    croak "Argument must be array reference";
  }
  
  my $length = @$elements;
  
  my $array = SPVM::Array->malloc_long_array($length);
  
  $array->set_long_array_elements($elements);
  
  return $array;
}

sub new_long_array_len {
  my $length = shift;
  
  my $array = SPVM::Array->malloc_long_array($length);
  
  return $array;
}

sub new_float_array {
  my $elements = shift;
  
  if (ref $elements ne 'ARRAY') {
    croak "Argument must be array reference";
  }
  
  my $length = @$elements;
  
  my $array = SPVM::Array->malloc_float_array($length);
  
  $array->set_float_array_elements($elements);
  
  return $array;
}

sub new_float_array_len {
  my $length = shift;
  
  my $array = SPVM::Array->malloc_float_array($length);
  
  return $array;
}

sub new_double_array {
  my $elements = shift;
  
  if (ref $elements ne 'ARRAY') {
    croak "Argument must be array reference";
  }
  
  my $length = @$elements;
  
  my $array = SPVM::Array->malloc_double_array($length);
  
  $array->set_double_array_elements($elements);
  
  return $array;
}

sub new_double_array_len {
  my $length = shift;
  
  my $array = SPVM::Array->malloc_double_array($length);
  
  return $array;
}

sub new_object {
  my $package_name = shift;
  
  my $object = SPVM::Object->malloc_object($package_name);
  
  return $object;
}

sub import {
  my ($class, $package_name) = @_;
  
  # Add package infomations
  if (defined $package_name) {
    my ($file, $line) = (caller)[1, 2];

    my $package_info = {
      name => $package_name,
      file => $file,
      line => $line
    };
    push @PACKAGE_INFOS, $package_info;
  }
}

sub build_spvm_subs {
  for my $abs_name (keys %SUB_SYMTABLE) {
    
    my $sub;
    $sub .= "sub SPVM::$abs_name {\n";
    $sub .= "  SPVM::call_sub(\"$abs_name\", \@_);\n";
    $sub .= "}";
    
    # Define SPVM subroutine
    eval $sub;
    
    if ($@) {
      croak "Can't define SVPM subroutine \"$abs_name\"\n$sub";
    }
  }
}

require XSLoader;
XSLoader::load('SPVM', $VERSION);

# Preloaded methods go here.

1;
__END__
=encoding UTF-8

=head1 NAME

SPVM - Fast calculation, GC, static typing, VM with perlish syntax

B<SPVM is under development! I will change implementation and specification without warnings.>

=head1 SYNOPSIS

  use FindBin;
  use lib "$FindBin::Bin/lib";

  use SPVM 'MyModule2';

  my $total = SPVM::MyModule2::foo(3, 5);
  print $total . "\n";

Module file

  # lib/SPVM/MyModule1.spvm
  package MyModule1 {
    has x : int;
    has y : int;

    sub sum ($a : int, $b : int) : int {

      my $total = $a + $b;

      return $total;
    }
  }

  # lib/SPVM/MyModule2.spvm
  use MyModule1;
  package MyModule2 {

    sub foo ($a : int, $b : int) : int {

      my $total = ($a * $b) + MyModule1::sum(2, 4);

      return $total;
    }
  }

If you want to know more syntax, see C<solo/SPVM/Test.spvm>.

If you want to know SPVM language, see C<solo/README.md>

=head1 DESCRIPTION

Do you need B<faster Perl>? SPVM provides fast calculation to Perl.

=over 4

=item *

B<Fast calculation> - The Perl's biggest weak point is the calculation performance. SPVM provides fast calculations.

=item *

B<GC> - You don't need to care about freeing memory

=item *

B<Static typing> - Static typing for performance

=item *

B<VM> - Byte codes are generated so that you can run them on SPVM language

=item *

B<Perlish syntax> - SPVM syntax is very similar to Perl

=item *

B<Perl module> - SPVM function can be called from Perl itself (Not yet implemented).

=back

SPVM only work on the Perl which support 64 bit integer.

=head1 SPVM SYNTAX

=head2 Type

=head3 Numeric type

Numeric types are byte, short, int, long, float, double.

  byte    signed integer          1byte
  short   signed integer          2byte
  int     signed integer          4byte
  long    signed integer          8byte
  float   floating-point number   4byte
  double  floating-point number   8byte

Declaration

  my $value : byte;
  my $value : short;
  my $value : int;
  my $value : long;
  my $value : float;
  my $value : double;

=head3 String type

String type is string.

This is same as byte[] at internal data structure.

Declaration

  my $string : string;

=head3 Reference type

Reference types are `array` and `object`.

B<Object type>

    PackageName

Declaration

    my $object : PackageName;

B<Array type>

  byte[]   byte array
  short[]  short array
  int[]    int array array
  long[]   long array
  float[]  float array
  doube[]  double array
  PackageName[] object array

Declaration

  my $values : byte[];
  my $values : short[];
  my $values : int[];
  my $values : long[];
  my $values : float[];
  my $values : double[];
  my $values : PackageName[];

B<Multiple array type>

  my $values : byte[][];
  my $values : short[][];
  my $values : int[][];
  my $values : long[][];
  my $values : float[][];
  my $values : double[][];
  my $values : PackageName[][];

  my $values : byte[][][];
  my $values : short[][][];
  my $values : int[][][];
  my $values : long[][][];
  my $values : float[][][];
  my $values : double[][][];
  my $values : PackageName[][][];

=head2 Type inference

If the type of right value is known, the type of left value is automatically decided.

  # Type of $value2 is byte.
  my $value1 : byte;
  my $value2 = $value1;

  # Type of $values2 is int[]
  my $values1 = malloc int[3];
  my $values2 = $values1;

  # Type of $object2 is PackageName
  my $object1 = malloc PackageName
  my $object2 = $object1;

=head2 Array

=head3 Create array

Array is created by malloc. Elements values is not initialized.

  my $nums = malloc byte[3];
  my $nums = malloc short[3];
  my $nums = malloc int[3];
  my $nums = malloc long[3];
  my $nums = malloc float[3];
  my $nums = malloc double[3];

=head3 Get array length

  my $len = @$nums;
  my $len = @{$nums};

=head3 Get and set array element

  # Get
  my $num = $nums->[0];

  # Set
  $nums->[0] = 5;

=head2 Condition branch

  if (1) {

  }
  elsif (2) {

  }
  else {

  }

=head2 Loop

=head3 for

  my $nums = malloc int[10];
  for (my $i = 0; $i < @$nums; $i++) {
    $nums->[$i] = 0;
  }

=head3 while

  my $nums = malloc int[10];
  my $i = 0;
  while ($i < @$nums) {
    $nums->[$i] = 0;
  }

=head2 Constant

=head3 Constant type

Type of constant default integral value is `int`.

    # int type
    1;
    3;

Type of constant default floating-point value is `double`.

    # double
    1.2
    5.3

Type of constant is specified by type specifier.

    # long
    3L

    # float
    3.2f

    # double
    3.2d

=head2 Name

=head3 Package name

Package name is a combination of alphabets, numbers, and `::`. Numbers should not appear as the first character. `_` can't be used in class name.

    # OK
    Foo
    Foo::Bar
    Foo1::Bar1

    # Not OK
    1Foo
    Foo::2Bar
    Foo_Bar;

=head3 Subroutine name

Subroutine name is a combination of alphabets, numbers, and `_` separators. Continual `_`(For example `__`) can't be used in subroutine name.

    # OK
    foo
    foo1
    foo_bar

    # Not OK
    1foo
    foo__bar

=head3 Field name

Field name is a combination of alphabets, numbers, and `_` separators. Continual `_`(For example `__`) can't be used in field name.

    # OK
    foo
    foo1
    foo_bar

    # Not OK
    1foo
    foo__bar

=head3 Absolute name

Absolute name is combination of package name and subroutine name, or package name and field name.

    PackageName1::foo
    PackageName1::PackageName2::foo_bar

=head2 Limitation

Object can't have object and array of object.

If I have idea to implement weaken reference and implement weaken reference, this limitation is removed.

=head1 FUNCTIONS

=head2 new_byte_array

Create new_byte array

  my $array = SPVM::new_byte_array([1, 2, 3]);

=head2 new_short_array

Create short array

  my $array = SPVM::new_short_array([1, 2, 3]);

=head2 new_int_array

Create int array

  my $array = SPVM::new_int_array([1, 2, 3]);

=head2 new_long_array

Create long array

  my $array = SPVM::new_long_array([1, 2, 3]);

=head2 new_float_array

Create float array

  my $array = SPVM::new_float_array([1, 2, 3]);

=head2 new_double_array

Create double array

  my $array = SPVM::new_double_array([1, 2, 3]);

=head2 new_string_raw

Create byte array from B<not decoded> Perl string.
This function is faster than C<SPVM::string> because copy is not executed.

  my $array = SPVM::new_string_raw("AGTCAGTC");

=head2 new_string

Create byte array from B<decoded> Perl string.

  my $array = SPVM::new_string("Å†Ç¢Å§Ç¶Å®");

=head2 new_object

Create object.

  my $object = SPVM::new_object("Point");

You can set and get value by C<set> and C<get> method.

  $object->set(x => 1);
  my $x = $object->get('x');

=head2 FAQ

=over 4

=item * B<Why SPVM don't support 32 bit Perl>

In many 32 bit Perl, 64 bit integer is not supported. This means that Perl can not express 64 bit integers on source code.

See the following code.

    my $value = 9223372036854775807;

In 32 bit Perl, 64bit integer value is converted to double automatically. The double value can't express long value accurately.

=back

=head1 AUTHOR

Yuki Kimoto E<lt>kimoto.yuki@gmail.com<gt>

=head1 CONTRIBUTERS

=over 4

=item *

L<akinomyoga|https://github.com/akinomyoga> (Koichi Murase)

=item *

L<[NAGAYASU Shinya|https://github.com/nagayasu-shinya>

=item *

L<Reini Urban|https://github.com/rurban>

=item *

L<chromatic|https://github.com/chromatic>

=item *

L<Kazutake Hiramatsu|https://github.com/kazhiramatsu>

=back

=head1 COPYRIGHT AND LICENSE

Copyright (C) 2017 by Yuki Kimoto

This library is free software; you can redistribute it and/or modify
it under the same terms as Perl itself, either Perl version 5.16.3 or,
at your option, any later version of Perl 5 you may have available.

=cut

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

our $VERSION = '0.0438';

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


sub exception { SPVM::ExchangeAPI::exception($SPVM_ENV, @_) }
sub set_exception { SPVM::ExchangeAPI::set_exception($SPVM_ENV, @_) }
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

SPVM - Static Perl Virtual Machine. Fast calculation & Easy C/C++ Binding

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
  
  # Call subroutine
  my $total = MyMath->sum([3, 6, 8, 9]);
  
  print $total . "\n";

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

=item * B<Dynamic linking>, B<Subroutine precompile>, B<AOT compile(create exe file)>

=item * B<Native API(C level api)>, B<C99 standard>

=back

=head1 DOCUMENT

=head2 Core Functions

  print, warn, time

L<SPVM::CORE> - Standard Functions

=head2 Standard Modules

L<SPVM::Byte>, L<SPVM::Short>, L<SPVM::Int>, L<SPVM::Long>, L<SPVM::Float>, L<SPVM::Double>

=head2 Exchange API

SPVM Exchange API Specification

L<http://jp.spvm.info/exchange-api.html>

(Currently only Japanese)

=head2 Native API

L<SPVM::Document::NativeAPI> - Native API is C level functions to manipulate SPVM data.

=head2 Extension

L<SPVM::Document::Extension> - Extension is the way to C/C++ Binding to SPVM

=head2 Language Specification

SPVM Language Specification

L<http://jp.spvm.info/language.html>

(Currently only Japanese)

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
  
  # Call subroutine
  my $total = MyMath->sum([3, 6, 8, 9]);
  
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

Copyright 2018-2019 Yuki Kimoto, all rights reserved.

This program is free software; you can redistribute it and/or modify it
under the same terms as Perl itself.

=cut

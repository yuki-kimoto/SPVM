use lib "t/testlib";
use TestAuto;

use strict;
use warnings;
use utf8;

use SPVM::Builder;

my $test_dir;
my $test_dir_vm;
my $build_dir;

BEGIN {
  $test_dir = $ENV{SPVM_TEST_DIR};
  $test_dir_vm = $ENV{SPVM_TEST_DIR_VM};
  $build_dir = $ENV{SPVM_BUILD_DIR};
}

use lib "$test_dir_vm/lib";
use lib "$test_dir/lib";

use MyTest qw(compile_not_ok_file compile_not_ok);

use Test::More;

# Compilation Errors in spvm_op.c 

# Array Initialization
{
  {
    my $source = 'class MyClass { static method main : void () { {"foo" => 1, "bar"}; } }';
    compile_not_ok($source, qr/\QThe length of the elements in {} of the array initialization must be an even number/);
  }
  
  {
    my $source = [
      'class MyClass { static method main : int () { {"foo"}; }',
    ];
    compile_not_ok($source, q|The length of the elements in {} of the array initialization must be an even number.|);
  }
}

# Reference operator
{
  {
    my $source = 'class MyClass { static method main : void () { \1; } }';
    compile_not_ok($source, qr'The operand of reference operator must be a variable');
  }
}

# Basic Type Name
{
  compile_not_ok_file('CompileError::Class::ClassNameDifferntFromClassFileName', qr/The class name 'ClassNameDifferntFromClassFileNameXXXXXXX' must be 'CompileError::Class::ClassNameDifferntFromClassFileName'/);
}

# Class Descripter
{
  {
    my $source = 'class MyClass : native;';
    compile_not_ok($source, qr/Invalid class attribute 'native'/);
  }
  {
    my $source = 'class MyClass : mulnum_t pointer interface_t;';
    compile_not_ok($source, qr/Only one of class attributes 'mulnum_t', 'pointer' or 'interface_t' can be specified/);
  }
  {
    my $source = 'class MyClass : private public;';
    compile_not_ok($source, qr/Only one of class attributes 'private', 'protected' or 'public' can be specified/);
  }
}

# Class Alias
{
  {
    my $source = 'class MyClass { use Point as point; }';
    compile_not_ok($source, qr/The alias name 'point' must begin with an upper case character/);
  }
  {
    my $source = 'class MyClass { use Point as Po; use Point as Po; }';
    compile_not_ok($source, qr/The alias name 'Po' is already used/);
  }
}

# Multi-Numeric Type Definition
{
  {
    my $source = 'class MyClass : mulnum_t { interface Stringable; }';
    compile_not_ok($source, qr/The interface statement cannnot be used in the definition of the multi-numeric type/);
  }
}

# Class Definition
{
  {
    my $source = 'class MyClass { INIT { } }';
    compile_ok($source);
  }
  
  {
    my $source = 'class MyClass { INIT { } INIT { } }';
    compile_ok($source);
  }
}

# Interface Definition
{
  {
    my $source = 'class MyClass : interface_t {}';
    compile_ok($source);
  }
  
  {
    my $source = 'class MyClass : interface_t { method foo : void (); }';
    compile_ok($source);
  }
  
  {
    my $source = 'class MyClass : interface_t { method foo : void (); method bar : void (); }';
    compile_ok($source);
  }
  
  {
    my $source = 'class MyClass : interface_t { method foo : void () {} }';
    compile_ok($source);
  }
  
  {
    my $source = 'class MyClass : interface_t { our $FOO : int; }';
    compile_not_ok($source, qr/An interface cannnot have class variables/);
  }
  
  {
    my $source = 'class MyClass : interface_t { has foo : int; }';
    compile_not_ok($source, qr/An interface cannnot have fields/);
  }
  
  {
    my $source = 'class MyClass : interface_t { static method foo : void (); }';
    compile_not_ok($source, q|A non-native method must have a block.|);
  }
  
  {
    my $source = 'class MyClass : interface_t { static method foo : void () {} }';
    compile_ok($source);
  }
  
  {
    my $source = 'class MyClass : interface_t { enum { FOO } }';
    compile_ok($source);
  }
  
  {
    my $source = 'class MyClass : interface_t { INIT { } }';
    compile_ok($source);
  }
  
  {
    my $source = 'class MyClass : interface_t { INIT { } INIT { } }';
    compile_ok($source);
  }
  
  {
    my $source = 'class MyClass : interface_t { method DESTROY : void (); }';
    compile_ok($source);
  }
  
  {
    my $source = 'class MyClass : interface_t  { interface MyClass; required method foo : void (); }';
    compile_ok($source);
  }
  
  {
    my $source = 'class MyClass : interface_t { required method foo : void (); required method bar : void (); }';
    compile_ok($source);
  }
  
}

# Multi-Numerci Type Definition
{
  {
    my $source = 'class MyClass_1i : mulnum_t { INIT { } has x : int; }';
    compile_ok($source);
  }
  
  {
    my $source = 'class MyClass_1i { INIT { } INIT { } has x : int; }';
    compile_ok($source);
  }
}

# Pointer Class
{
  {
    my $source = 'class MyClass : pointer { has foo : int; }';
    compile_ok($source);
  }
}

# Method
{
  {
    my $source = 'class MyClass { static method foo : void (); }';
    compile_not_ok($source, qr/A non-native method must have a block/);
  }
  {
    my $source = 'class MyClass { static method foo : void () { static method : int () { } } }';
    compile_not_ok($source, qr/An anon method must be an instance method/);
  }
  {
    my $source = 'class MyClass { required method foo : void () { } }';
    compile_not_ok($source, qr/MyClass#foo method cannnot have the method attribute 'required'/);
  }
  {
    my $source = 'class MyClass { method foo : void () { } method foo : void () { } }';
    compile_not_ok($source, qr/Redeclaration of MyClass#foo method/);
  }
  {
    my $source = 'class MyClass_2d : mulnum_t { has re : double; has im : double; method foo : void () { } }';
    compile_not_ok($source, qr/A multi-numeric type cannnot have instance methods/);
  }
  {
    my $source = 'class MyClass_2d : mulnum_t { has re : double; has im : double; static method foo : void () { } }';
    compile_ok($source);
  }
  {
    my $source = 'class MyClass : mulnum_t { our $FOO : int; }';
    compile_not_ok($source, qr/A multi-numeric type cannnot have class variables/);
  }
  {
    my $source = 'class MyClass : mulnum_t { }';
    compile_not_ok($source, qr/A multi-numeric type must have at least one field/);
  }
  {
    my $source = 'class MyClass : mulnum_t { }';
    compile_not_ok_file('CompileError::MultiNumeric::Fields256', qr/The length of the fields defined in the multi-numeric type must be less than or equal to 255/);
  }
  {
    my $source = 'class MyClass { static method foo : void () { method : void () { method : void () {}; }; } }';
    compile_ok($source);
  }
}

# Class Variable Name
{
  {
    my $source = 'class MyClass { our $MyClass::FOO : int; }';
    compile_not_ok($source, qr/The class varaible name '\$MyClass::FOO' cannnot contain "::"/);
  }
}

# Class Variable Definition
{
  {
    my $source = 'class MyClass { our $FOO : native int; }';
    compile_not_ok($source, qr/Invalid class variable attribute 'native'/);
  }
  {
    my $source = 'class MyClass { our $FOO : ro wo rw int; }';
    compile_not_ok($source, qr/Only one of class variable attributes 'rw', 'ro', 'wo' can be specifed/);
  }
  {
    my $source = 'class MyClass { our $FOO : private public int; }';
    compile_not_ok($source, qr/Only one of class variable attributes 'private', 'protected' or 'public' can be specified/);
  }
}

# Field Name
{
  {
    my $source = 'class MyClass { has MyClass::foo : int; }';
    compile_not_ok($source, qr/The field name 'MyClass::foo' cannnot contain "::"/);
  }
}

# Field Defintion
{
  {
    my $source = 'class MyClass { has foo : native int; }';
    compile_not_ok($source, qr/Invalid field attribute 'native'/);
  }
  {
    my $source = 'class MyClass { has foo : ro wo rw int; }';
    compile_not_ok($source, qr/Only one of field attributes 'rw', 'ro' or 'wo' can be specifed/);
  }
  {
    my $source = 'class MyClass { has foo : private public int; }';
    compile_not_ok($source, qr/Only one of field attributes 'private', 'protected' or 'public' can be specified/);
  }
}

# Method name
{
  {
    my $source = 'class MyClass { method MyClass::foo : void () { } }';
    compile_not_ok($source, qr/The method name 'MyClass::foo' cannnot contain "::"/);
  }
  {
    my $source = 'class MyClass { method INIT : void () { } }';
    compile_not_ok($source, qr/'INIT' cannnot be used as a method name/);
  }
  {
    my $source = 'class MyClass { method END : void () { } }';
    compile_not_ok($source, qr/'END' cannnot be used as a method name/);
  }
  {
    my $source = 'class MyClass { ro method foo : void () { } }';
    compile_not_ok($source, qr/Invalid method attribute 'ro'/);
  }
  {
    my $source = 'class MyClass { native precompile method foo : void () { } }';
    compile_not_ok($source, qr/Only one of method attributes 'native' and 'precompile' can be specified/);
  }
  {
    my $source = 'class MyClass { native method foo : void () { } }';
    compile_not_ok($source, qr/A native method cannnot have its block/);
  }
  {
    my $source = 'class MyClass { method DESTROY : int () { } }';
    compile_not_ok($source, qr/The return type of DESTROY method must be the void type/);
  }
  {
    my $source = 'class MyClass { static method DESTROY : void () { } }';
    compile_not_ok($source, qr/DESTROY method must be an instance method/);
  }
  {
    my $source = 'class MyClass { method DESTROY : void ($var : int) { } }';
    compile_not_ok($source, qr/DESTROY method cannnot have arguments/);
  }
  
}

# Enumeration
{
  {
    my $source = 'class MyClass { enum { FOO = 1L } }';
    compile_not_ok($source, qr/The value of the enumeration must be int type/);
  }
  {
    my $source = 'class MyClass { ro enum { FOO = 1 } }';
    compile_not_ok($source, qr/Invalid enumeration attribute 'ro'/);
  }
  {
    my $source = 'class MyClass { private public enum { FOO = 1 } }';
    compile_not_ok($source, qr/Only one of enumeration attributes 'private', 'protected' or 'public' can be specified/);
  }
}

# Local Variable
{
  {
    my $source = 'class MyClass { static method main : void () { my $MyClass::foo; }; }';
    compile_not_ok($source, qr/The local variable name '\$MyClass::foo' cannnot contain "::"/);
  }
}

# Mutable
{
  {
    my $source = 'class MyClass { static method main : void () { ++1; }; }';
    compile_not_ok($source, qr/\QThe operand of ++ operator must be mutable/);
  }
  {
    my $source = 'class MyClass { static method main : void () { --1; }; }';
    compile_not_ok($source, qr/\QThe operand of -- operator must be mutable/);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 += 1; }; }';
    compile_not_ok($source, qr/The left operand of a special assignment operator must be mutable/);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 = 1; }; }';
    compile_not_ok($source, qr/The left operand of assignment operator must be mutable/);
  }
}

# Version Declaration
{
  {
    my $source = 'class MyClass { version "1.001"; }';
    compile_ok($source);
  }
  {
    my $source = 'class MyClass { version "1"; }';
    compile_ok($source);
  }
  {
    my $source = 'class MyClass { version "10000"; }';
    compile_ok($source);
  }
  {
    my $source = 'class MyClass { version "123456789.123456789123"; }';
    compile_ok($source);
  }
  {
    my $source = 'class MyClass { version "1.001"; version "1.001";}';
    compile_not_ok($source, qr|The version has already been declared|);
  }
  {
    my $source = 'class MyClass { version ".001"; }';
    compile_not_ok($source, qr|A version string must begin with a number|);
  }
  {
    my $source = 'class MyClass { version "1."; }';
    compile_not_ok($source, qr|A version string must end with a number|);
  }
  {
    my $source = 'class MyClass { version "1.0a0"; }';
    compile_not_ok($source, qr|A character in a version string must be a number or "\."|);
  }
  {
    my $source = 'class MyClass { version "1.001.001"; }';
    compile_not_ok($source, qr|The number of '.' in a version string must be less than or equal to 1|);
  }
  {
    my $source = 'class MyClass { version "1.00101"; }';
    compile_not_ok($source, q|The length of characters after '.' in a version string must be divisible by 3|);
  }
  {
    my $source = 'class MyClass { version "1.0011"; }';
    compile_not_ok($source, q|The length of characters after '.' in a version string must be divisible by 3|);
  }
  {
    my $source = 'class MyClass { version 1.001; }';
    compile_not_ok($source,q|The operand type of version statement must be string type.|);
  }
}

# version statement - Version Declaration
{
  {
    my $source = 'class MyClass { version "1.001"; }';
    compile_ok($source);
  }
  {
    my $source = 'class MyClass { version "1"; }';
    compile_ok($source);
  }
  {
    my $source = 'class MyClass { version "10000"; }';
    compile_ok($source);
  }
  {
    my $source = 'class MyClass { version "123456789.123456789123"; }';
    compile_ok($source);
  }
  {
    my $source = 'class MyClass { version "1.001"; version "1.001";}';
    compile_not_ok($source, qr|The version has already been declared|);
  }
  {
    my $source = 'class MyClass { version ".001"; }';
    compile_not_ok($source, qr|A version string must begin with a number|);
  }
  {
    my $source = 'class MyClass { version "1."; }';
    compile_not_ok($source, qr|A version string must end with a number|);
  }
  {
    my $source = 'class MyClass { version "1.0a0"; }';
    compile_not_ok($source, qr|A character in a version string must be a number or "\."|);
  }
  {
    my $source = 'class MyClass { version "1.001.001"; }';
    compile_not_ok($source, qr|The number of '.' in a version string must be less than or equal to 1|);
  }
  {
    my $source = 'class MyClass { version "1.00101"; }';
    compile_not_ok($source, qr|The length of characters after '.' in a version string must be divisible by 3|);
  }
  {
    my $source = 'class MyClass { version "1.0011"; }';
    compile_not_ok($source, qr|The length of characters after '.' in a version string must be divisible by 3|);
  }
  {
    my $source = 'class MyClass { version 1.001; }';
    compile_not_ok($source,q|The operand type of version statement must be string type.|);
  }
}

# version_from statement
{
  {
    my $source = 'class MyClass { version_from Point; }';
    compile_ok($source);
  }
  
  {
    my $source = 'class MyClass { version_from Point; version_from Point;}';
    compile_not_ok($source, qr|version_from has already been declared.|);
  }
  
  {
    my $source = 'class MyClass { version "1"; version_from Point;}';
    compile_not_ok($source, qr|Both version statement and version_from statement cannnot be used at the same time.|);
  }
  
  {
    my $source = 'class MyClass { version_from Point; version "1"; }';
    compile_not_ok($source, qr|Both version statement and version_from statement cannnot be used at the same time.|);
  }
}

# Extra
{
  {
    my $source = 'class MyClass { interface Complex_2d; }';
    compile_not_ok($source);
  }
  {
    my $source = 'class MyClass { INIT {} static method main : void () { &INIT(); } }';
    compile_ok($source);
  }
  {
    my $source = 'class MyClass { method DESTROY : void () {} method main : void () { $self->DESTROY; } }';
    compile_ok($source);
  }
  {
    my $source = 'class MyClass { static method main : void () { &INIT(); } }';
    compile_ok($source);
  }
  
  {
    my $source = 'class MyClass { interface }';
    compile_not_ok($source, qr|Unexpected token|);
  }
  
  {
    # https://github.com/yuki-kimoto/SPVM/issues/570
    my $source = 'class TestCase::Operator::PACKAGE { static method PACKAGE : int () { $anon_result_ref = 0; return 1; }; }';
    compile_not_ok($source);
  }
}

# isa, is_type, is_compile_type
{
  {
    my $source = 'class MyClass { static method main : void () { use List; my $value = "a"; $value is_compile_type List of string; } }';
    compile_ok($source);
  }
  
  {
    my $source = 'class MyClass { static method main : void () { my $value = "a"; $value isa List of string; } }';
    compile_not_ok($source, q|Unexpected token|);
  }
  
  {
    my $source = 'class MyClass { static method main : void () { my $value = "a"; $value is_compile_type string|string[]; } }';
    compile_not_ok($source, q|Unexpected token|);
  }
  
  {
    my $source = 'class MyClass { static method main : void () { my $value = "a"; $value is_compile_type Int of string|string[]; } }';
    compile_not_ok($source, q|The right type must not contain union types.|);
  }
  
  {
    my $source = 'class MyClass { static method main : void () { my $value = "a"; $value is_type string|string[]; } }';
    compile_not_ok($source, q|Unexpected token|);
  }

  {
    my $source = 'class MyClass { static method main : void () { my $value = "a"; $value is_type byte*; } }';
    compile_not_ok($source, q|Unexpected token|);
  }
  
  {
    my $source = 'class MyClass { static method main : void () { my $value = "a"; $value isa byte*; } }';
    compile_not_ok($source, q|Unexpected token|);
  }
  
}

# mutable type
{
  {
    my $source = 'class MyClass { static method main : void () { my $value = (mutable mutable string)undef; } }';
    compile_not_ok($source, qr|Duplicated mutable type modifier.|);
  }
}

# use
{
  {
    my $source = 'class MyClass { static method main : void () { use Point; my $point = Point->new; } }';
    compile_ok($source);
  }
}

done_testing;

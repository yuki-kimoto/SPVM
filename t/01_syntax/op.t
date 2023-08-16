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
    compile_not_ok($source, qr/\QThe lenght of the elements in {} of the array initialization must be an even number/);
  }
}

# Reference operator
{
  {
    my $source = 'class MyClass { static method main : void () { \1; } }';
    compile_not_ok($source, qr'The operand of the reference operator must be a variable');
  }
}

# Basic Type Name
{
  compile_not_ok_file('CompileError::Class::ClassNameDifferntFromClassFileName', qr/The class name "ClassNameDifferntFromClassFileNameXXXXXXX" must be "CompileError::Class::ClassNameDifferntFromClassFileName"/);
}

# Class Descripter
{
  {
    my $source = 'class MyClass : native;';
    compile_not_ok($source, qr/Invalid class attribute "native"/);
  }
  {
    my $source = 'class MyClass : mulnum_t pointer interface_t;';
    compile_not_ok($source, qr/Only one of class attributes "mulnum_t", "pointer" or "interface_t" can be specified/);
  }
  {
    my $source = 'class MyClass : private public;';
    compile_not_ok($source, qr/Only one of class attributes "private", "protected" or "public" can be specified/);
  }
}

# Class Alias
{
  {
    my $source = 'class MyClass { use Point as point; }';
    compile_not_ok($source, qr/The alias name "point" must begin with an upper case character/);
  }
  {
    my $source = 'class MyClass { use Point as Po; use Point as Po; }';
    compile_not_ok($source, qr/The alias name "Po" is already used/);
  }
}

# Multi-Numeric Type Definition
{
  {
    my $source = 'class MyClass : mulnum_t { interface Stringable; }';
    compile_not_ok($source, qr/The interface statement cannnot be used in the definition of the multi-numeric type/);
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
    compile_not_ok($source, qr/The interface cannnot have class variables/);
  }
  
  {
    my $source = 'class MyClass : interface_t { has foo : int; }';
    compile_not_ok($source, qr/The interface cannnot have fields/);
  }
  
  {
    my $source = 'class MyClass : interface_t { static method foo : void (); }';
    compile_not_ok($source, qr/The method defined in the interface must be an instance method/);
  }
  
  {
    my $source = 'class MyClass : interface_t { enum { FOO } }';
    compile_not_ok($source, q|The method defined in the interface must be an instance method.|);
  }
  
  {
    my $source = 'class MyClass : interface_t { INIT { } }';
    compile_not_ok($source, q|The method defined in the interface must be an instance method.|);
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
    compile_not_ok($source, qr/The non-native method must have the block/);
  }
  {
    my $source = 'class MyClass { static method foo : void () { static method : int () { } } }';
    compile_not_ok($source, qr/The anon method must be an instance method/);
  }
  {
    my $source = 'class MyClass { required method foo : void () { } }';
    compile_not_ok($source, qr/The method defined in the class cannnot have the method attribute "required"/);
  }
  {
    my $source = 'class MyClass { method foo : void () { } method foo : void () { } }';
    compile_not_ok($source, qr/Redeclaration of the "foo" method in the "MyClass" class/);
  }
  {
    my $source = 'class MyClass : mulnum_t { method foo : void () { } }';
    compile_not_ok($source, qr/The multi-numeric type cannnot have methods/);
  }
  {
    my $source = 'class MyClass : mulnum_t { our $FOO : int; }';
    compile_not_ok($source, qr/The multi-numeric type cannnot have class variables/);
  }
  {
    my $source = 'class MyClass : mulnum_t { }';
    compile_not_ok($source, qr/The multi-numeric type must have at least one field/);
  }
  {
    my $source = 'class MyClass : mulnum_t { }';
    compile_not_ok_file('CompileError::MultiNumeric::Fields256', qr/The length of the fields defined in the multi-numeric type must be less than or equal to 255/);
  }
}

# Class Variable Name
{
  {
    my $source = 'class MyClass { our $MyClass::FOO : int; }';
    compile_not_ok($source, qr/The class varaible name "\$MyClass::FOO" cannnot contain "::"/);
  }
}

# Class Variable Definition
{
  {
    my $source = 'class MyClass { our $FOO : native int; }';
    compile_not_ok($source, qr/Invalid class variable attribute "native"/);
  }
  {
    my $source = 'class MyClass { our $FOO : ro wo rw int; }';
    compile_not_ok($source, qr/Only one of class variable attributes "rw", "ro", "wo" can be specifed/);
  }
  {
    my $source = 'class MyClass { our $FOO : private public int; }';
    compile_not_ok($source, qr/Only one of class variable attributes "private", "protected" or "public" can be specified/);
  }
}

# Field Name
{
  {
    my $source = 'class MyClass { has MyClass::foo : int; }';
    compile_not_ok($source, qr/The field name "MyClass::foo" cannnot contain "::"/);
  }
}

# Field Defintion
{
  {
    my $source = 'class MyClass { has foo : native int; }';
    compile_not_ok($source, qr/Invalid field attribute "native"/);
  }
  {
    my $source = 'class MyClass { has foo : ro wo rw int; }';
    compile_not_ok($source, qr/Only one of field attributes "rw", "ro" or "wo" can be specifed/);
  }
  {
    my $source = 'class MyClass { has foo : private public int; }';
    compile_not_ok($source, qr/Only one of field attributes "private", "protected" or "public" can be specified/);
  }
}

# Method name
{
  {
    my $source = 'class MyClass { method MyClass::foo : void () { } }';
    compile_not_ok($source, qr/The method name "MyClass::foo" cannnot contain "::"/);
  }
  {
    my $source = 'class MyClass { method INIT : void () { } }';
    compile_not_ok($source, qr/"INIT" cannnot be used as a method name/);
  }
  {
    my $source = 'class MyClass { ro method foo : void () { } }';
    compile_not_ok($source, qr/Invalid method attribute "ro"/);
  }
  {
    my $source = 'class MyClass { native precompile method foo : void () { } }';
    compile_not_ok($source, qr/Only one of method attributes "native" and "precompile" can be specified/);
  }
  {
    my $source = 'class MyClass { native method foo : void () { } }';
    compile_not_ok($source, qr/The native method cannnot have the block/);
  }
  {
    my $source = 'class MyClass { method DESTROY : int () { } }';
    compile_not_ok($source, qr/The return type of the DESTROY destructor method must be the void type/);
  }
  {
    my $source = 'class MyClass { static method DESTROY : void () { } }';
    compile_not_ok($source, qr/The DESTROY destructor method must be an instance method/);
  }
  {
    my $source = 'class MyClass { method DESTROY : void ($var : int) { } }';
    compile_not_ok($source, qr/The DESTROY destructor method cannnot have arguments/);
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
    compile_not_ok($source, qr/Invalid enumeration attribute "ro"/);
  }
  {
    my $source = 'class MyClass { private public enum { FOO = 1 } }';
    compile_not_ok($source, qr/Only one of enumeration attributes "private", "protected" or "public" can be specified/);
  }
}

# Local Variable
{
  {
    my $source = 'class MyClass { static method main : void () { my $MyClass::foo; }; }';
    compile_not_ok($source, qr/The local variable "\$MyClass::foo" cannnot contain "::"/);
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
    compile_not_ok($source, qr/The left operand of the special assign operator must be mutable/);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 = 1; }; }';
    compile_not_ok($source, qr/The left operand of the assign operator must be mutable/);
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
    compile_not_ok($source, qr|The number of "." in a version string must be less than or equal to 1|);
  }
  {
    my $source = 'class MyClass { version "1.00101"; }';
    compile_not_ok($source, qr|The length of characters after "." in a version string must be divisible by 3|);
  }
  {
    my $source = 'class MyClass { version "1.0011"; }';
    compile_not_ok($source, qr|The length of characters after "." in a version string must be divisible by 3|);
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
}

done_testing;

use strict;
use warnings;
use utf8;
use FindBin;

use SPVM::Builder;

use lib "$FindBin::Bin/../default/lib";
use lib "$FindBin::Bin/lib";

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

# Class Name
{
  compile_not_ok_file('CompileError::Class::ClassNameDifferntFromModuleName', qr/The class name "ClassNameDifferntFromModuleNameXXXXXXX" must be "CompileError::Class::ClassNameDifferntFromModuleName"/);
}

# Class Descripter
{
  {
    my $source = 'class MyClass : native;';
    compile_not_ok($source, qr/Invalid class descriptor "native"/);
  }
  {
    my $source = 'class MyClass : mulnum_t pointer_t interface_t;';
    compile_not_ok($source, qr/Only one of class descriptors "mulnum_t", "pointer_t" or "interface_t" can be specified/);
  }
  {
    my $source = 'class MyClass : private public;';
    compile_not_ok($source, qr/Only one of class descriptors "private" or "public" can be specified/);
  }
}

# Class Alias
{
  {
    my $source = 'class MyClass { use Point as point; }';
    compile_not_ok($source, qr/The class alias name "point" must begin with an upper case character/);
  }
  {
    my $source = 'class MyClass { use Point as Po; use Point as Po; }';
    compile_not_ok($source, qr/The class alias name "Po" is already used/);
  }
}

# Multi-Numeric Type Definition
{
  {
    my $source = 'class MyClass : mulnum_t { interface Stringable; }';
    compile_not_ok($source, qr/The interface statement can't be used in the definition of the multi-numeric type/);
  }
}


# Interface Definition
{
  {
    my $source = 'class MyClass : interface_t { our $FOO : int; }';
    compile_not_ok($source, qr/The interface can't have class variables/);
  }
  {
    my $source = 'class MyClass : interface_t { has foo : int; }';
    compile_not_ok($source, qr/The interface can't have fields/);
  }
}

# Pointer Class
{
  {
    my $source = 'class MyClass : pointer_t { has foo : int; }';
    compile_not_ok($source, qr/The pointer class can't have fields/);
  }
}

# Field Definition
{
  {
    my $source = 'class MyClass { has foo : int; has foo : int; }';
    compile_not_ok($source, qr/Redeclaration of the field "foo" in the class "MyClass"/);
  }
}

# Class Variable Definition
{
  {
    my $source = 'class MyClass { our $FOO : int; our $FOO : int;}';
    compile_not_ok($source, qr/Redeclaration of the class variable "\$FOO" in the class "MyClass"/);
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
    my $source = 'class MyClass :interface_t { static method foo : void (); }';
    compile_not_ok($source, qr/The method defined in the interface must be an instance method/);
  }
  {
    my $source = 'class MyClass :interface_t { native method foo : void (); }';
    compile_not_ok($source, qr/The method defined in the interface can't have the method descriptor "native"/);
  }
  {
    my $source = 'class MyClass :interface_t { precompile method foo : void (); }';
    compile_not_ok($source, qr/The method defined in the interface can't have the method descriptor "precompile"/);
  }
  {
    my $source = 'class MyClass { required method foo : void () { } }';
    compile_not_ok($source, qr/The method defined in the class can't have the method descriptor "required"/);
  }
  {
    my $source = 'class MyClass { native method foo : void () { } }';
    compile_not_ok($source, qr/The native method can't have the block/);
  }
  {
    my $source = 'class MyClass { method foo : void () { } method foo : void () { } }';
    compile_not_ok($source, qr/Redeclaration of the method "foo" in the class "MyClass"/);
  }
  {
    my $source = 'class MyClass : interface_t { required method foo : void (); required method bar : void (); }';
    compile_not_ok($source, qr/The interface can't have multiple required methods/);
  }
  {
    my $source = 'class MyClass : interface_t { method foo : void (); }';
    compile_not_ok($source, qr/The interface must have a required method/);
  }
  {
    my $source = 'class MyClass : mulnum_t { method foo : void () { } }';
    compile_not_ok($source, qr/The multi-numeric type can't have methods/);
  }
  {
    my $source = 'class MyClass : mulnum_t { our $FOO : int; }';
    compile_not_ok($source, qr/The multi-numeric type can't have class variables/);
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

# Extra
{
  {
    my $source = 'class MyClass { interface Complex_2d; }';
    compile_not_ok($source, qr/The operand of the interface statement msut be an interface type/);
  }
}

done_testing;

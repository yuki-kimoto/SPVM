use strict;
use warnings;
use utf8;
use FindBin;

use SPVM::Builder;

use lib "$FindBin::Bin/../default/lib";
use lib "$FindBin::Bin/lib";

use MyTest qw(compile_not_ok_file compile_not_ok);

use Test::More;

# Compilation Errors in spvm_op_checker.c 

# Array Initialization
{
  {
    my $source = 'class MyClass { static method main : void () { [undef]; } }';
    compile_not_ok($source, qr'The first element in the array initialization must be defined');
  }
}

# next
{
  {
    my $source = 'class MyClass { static method main : void () { { next; }; } }';
    compile_not_ok($source, qr'The next statement must be in a loop block');
  }
  {
    my $source = 'class MyClass { static method main : void () { if (1) { next; }; } }';
    compile_not_ok($source, qr'The next statement must be in a loop block');
  }
}

# last
{
  {
    my $source = 'class MyClass { static method main : void () { { last; }; } }';
    compile_not_ok($source, qr'The last statement must be in a loop block');
  }
  {
    my $source = 'class MyClass { static method main : void () { if (1) { last; }; } }';
    compile_not_ok($source, qr'The last statement must be in a loop block');
  }
}

# break
{
  {
    my $source = 'class MyClass { static method main : void () { { break; }; } }';
    compile_not_ok($source, qr'The break statement must be in a switch block');
  }
  {
    my $source = 'class MyClass { static method main : void () { if (1) { break; }; } }';
    compile_not_ok($source, qr'The break statement must be in a switch block');
  }
}

# refcnt
{
  {
    my $source = 'class MyClass { static method main : void () { my $num = 0; refcnt $num; } }';
    compile_not_ok($source, qr'The operand of the refcnt operator must be an object type');
  }
}

# ref
{
  {
    my $source = 'class MyClass { static method main : void () { my $num = 0; ref $num; } }';
    compile_not_ok($source, qr'The operand of the ref operator must be an object type');
  }
}

# dump
{
  {
    my $source = 'class MyClass { static method main : void () { my $num = 0; dump $num; } }';
    compile_not_ok($source, qr'The operand of the dump operator must be an object type');
  }
}

# class_id
{
  {
    my $source = 'class MyClass { static method main : void () { class_id NotExists; } }';
    compile_not_ok($source, qr'The operand of the class_id operator must be an existing class type. The class "NotExists" is not found');
  }
}

# set_error_code
{
  {
    my $source = 'class MyClass { static method main : void () { set_error_code 1d; } }';
    compile_not_ok($source, qr'The operand of the set_error_code operator must be the int type');
  }
}

# switch
{
  {
    my $source = 'class MyClass { static method main : void () { switch (1d) { } } }';
    compile_not_ok($source, qr'The condition of the switch statement must be the int type');
  }
  {
    my $source = 'class MyClass { static method main : void () { switch (1) { case Int->new(1): { } } } }';
    compile_not_ok($source, qr'The operand of the case statement must be a constant value');
  }
  {
    my $source = 'class MyClass { static method main : void () { switch (1) { case "foo": { } } } }';
    compile_not_ok($source, qr'The operand of the case statement must be the int type');
  }
  {
    my $source = 'class MyClass { static method main : void () { switch (1) { case 1: { } case 1: { } } } }';
    compile_not_ok($source, qr"The value of the case statement can't be duplicated");
  }
  {
    my $source = 'class MyClass { static method main : void () { switch (1) { case 1: { } default: { } default: { } } } }';
    compile_not_ok($source, qr'Unexpected token "default"');
  }
}

# bool type conversion
{
  {
    my $source = 'class MyClass { static method main : void () { my $var = 0; my $var_ref = \$var; !$var_ref; } }';
    compile_not_ok($source, qr'The operand of the bool type conversion must be one of a numeric type, an object type or the undef type');
  }
}

# ==
{
  {
    my $source = 'class MyClass { static method main : void () { undef == 1; } }';
    compile_not_ok($source, qr'The right operand of the == operator must be an object type');
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 == undef; } }';
    compile_not_ok($source, qr'The left operand of the == operator must be an object type');
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 == Int->new(1); } }';
    compile_not_ok($source, qr'The left and right operands of == operator must be numeric types or object types');
  }
}

done_testing;

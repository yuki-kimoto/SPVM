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

# !=
{
  {
    my $source = 'class MyClass { static method main : void () { undef != 1; } }';
    compile_not_ok($source, qr'The right operand of the != operator must be an object type');
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 != undef; } }';
    compile_not_ok($source, qr'The left operand of the != operator must be an object type');
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 != Int->new(1); } }';
    compile_not_ok($source, qr'The left and right operands of != operator must be numeric types or object types');
  }
}

# >
{
  {
    my $source = 'class MyClass { static method main : void () { "foo" > 1; } }';
    compile_not_ok($source, qr'The left operand of the > operator must be a numeric type');
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 > "foo"; } }';
    compile_not_ok($source, qr'The right operand of the > operator must be a numeric type');
  }
}

# >=
{
  {
    my $source = 'class MyClass { static method main : void () { "foo" >= 1; } }';
    compile_not_ok($source, qr'The left operand of the >= operator must be a numeric type');
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 >= "foo"; } }';
    compile_not_ok($source, qr'The right operand of the >= operator must be a numeric type');
  }
}

# <
{
  {
    my $source = 'class MyClass { static method main : void () { "foo" < 1; } }';
    compile_not_ok($source, qr'The left operand of the < operator must be a numeric type');
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 < "foo"; } }';
    compile_not_ok($source, qr'The right operand of the < operator must be a numeric type');
  }
}

# <=
{
  {
    my $source = 'class MyClass { static method main : void () { "foo" <= 1; } }';
    compile_not_ok($source, qr'The left operand of the <= operator must be a numeric type');
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 <= "foo"; } }';
    compile_not_ok($source, qr'The right operand of the <= operator must be a numeric type');
  }
}

# <=>
{
  {
    my $source = 'class MyClass { static method main : void () { "foo" <=> 1; } }';
    compile_not_ok($source, qr'The left operand of the <=> operator must be a numeric type');
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 <=> "foo"; } }';
    compile_not_ok($source, qr'The right operand of the <=> operator must be a numeric type');
  }
}

# gt
{
  {
    my $source = 'class MyClass { static method main : void () { 1 gt "foo"; } }';
    compile_not_ok($source, 'The left operand of the gt operator must be the string type or the byte[] type');
  }
  {
    my $source = 'class MyClass { static method main : void () { "foo" gt 1; } }';
    compile_not_ok($source, 'The right operand of the gt operator must be the string type or the byte[] type');
  }
}

# ge
{
  {
    my $source = 'class MyClass { static method main : void () { 1 ge "foo"; } }';
    compile_not_ok($source, 'The left operand of the ge operator must be the string type or the byte[] type');
  }
  {
    my $source = 'class MyClass { static method main : void () { "foo" ge 1; } }';
    compile_not_ok($source, 'The right operand of the ge operator must be the string type or the byte[] type');
  }
}

# lt
{
  {
    my $source = 'class MyClass { static method main : void () { 1 lt "foo"; } }';
    compile_not_ok($source, 'The left operand of the lt operator must be the string type or the byte[] type');
  }
  {
    my $source = 'class MyClass { static method main : void () { "foo" lt 1; } }';
    compile_not_ok($source, 'The right operand of the lt operator must be the string type or the byte[] type');
  }
}

# le
{
  {
    my $source = 'class MyClass { static method main : void () { 1 le "foo"; } }';
    compile_not_ok($source, 'The left operand of the le operator must be the string type or the byte[] type');
  }
  {
    my $source = 'class MyClass { static method main : void () { "foo" le 1; } }';
    compile_not_ok($source, 'The right operand of the le operator must be the string type or the byte[] type');
  }
}

# cmp
{
  {
    my $source = 'class MyClass { static method main : void () { 1 cmp "foo"; } }';
    compile_not_ok($source, 'The left operand of the cmp operator must be the string type or the byte[] type');
  }
  {
    my $source = 'class MyClass { static method main : void () { "foo" cmp 1; } }';
    compile_not_ok($source, 'The right operand of the cmp operator must be the string type or the byte[] type');
  }
}

# .
{
  {
    my $source = 'class MyClass { static method main : void () { Int->new(1) . "foo"; } }';
    compile_not_ok($source, 'The left operand of the . operator must be the string type or the byte[] type');
  }
  {
    my $source = 'class MyClass { static method main : void () { "foo" . Int->new(1); } }';
    compile_not_ok($source, 'The right operand of the . operator must be the string type or the byte[] type');
  }
}

# Capture
{
  {
    my $source = 'class MyClass { static method main : void () { [$foo : int] method : void () { }; } }';
    compile_not_ok($source, 'The capture variable "$foo" is not defined');
  }
}

# new
{
  {
    my $source = 'class MyClass { static method main : void () { new int[1L]; } }';
    compile_not_ok($source, 'The array length specified by the new operator must be the int type');
  }
  {
    my $source = 'class MyClass { static method main : void () { new int; } }';
    compile_not_ok($source, q|The operand of the new operator can't be a numeric type|);
  }
  {
    my $source = 'class MyClass { use Stringable; static method main : void () {  new Stringable; } }';
    compile_not_ok($source, q|The operand of the new operator can't be an interface type|);
  }
  {
    my $source = [
      'class MyClass { use MyPoint; static method main : void () { new MyPoint; } }',
      'class MyPoint : pointer_t;',
    ];
    compile_not_ok($source, q|The operand of the new operator can't be a pointer class type|);
  }
  {
    my $source = 'class MyClass { static method main : void () {  new Int; } }';
    compile_not_ok($source, q|The object can't be created from the private class|);
  }
}

# ^
{
  {
    my $source = 'class MyClass { static method main : void () { 1d ^ 1; } }';
    compile_not_ok($source, 'The left and right operand of the ^ operator must be an integral type');
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 ^ 1d; } }';
    compile_not_ok($source, 'The left and right operand of the ^ operator must be an integral type');
  }
}

# TODO SPVM_OP_C_ID_ISA

done_testing;

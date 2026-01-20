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

# Extra
{
  # allow - Hash::Entry class uses allow statement
  use SPVM 'Hash';
}

# Compilation Errors in spvm_check.c 

# Array Initialization
{
  {
    my $source = 'class MyClass { static method main : void () { [undef]; } }';
    compile_not_ok($source, qr'The first element in the array initialization must be defined');
  }
  
  {
    my $source = [
      'class MyClass { static method main : int () { my $options = new object[0]; [(object)$options]; }  }',
    ];
    compile_ok($source);
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

# type_name
{
  {
    my $source = 'class MyClass { static method main : void () { my $num = 0; type_name $num; } }';
    compile_not_ok($source, qr'The operand type of type_name operator must be an object type');
  }
}

# dump
{
  {
    my $source = 'class MyClass { static method main : void () { my $num = 0; dump $num; } }';
    compile_not_ok($source, qr'The operand type of dump operator must be an object type');
  }
}

# new_string_len
{
  {
    my $source = 'class MyClass { static method main : void () { new_string_len 1L; } }';
    compile_not_ok($source, qr|The operand type of new_string_len operator must be an integer type within int|);
  }
}

# basic_type_id
{
  {
    my $source = 'class MyClass { static method main : void () { basic_type_id Error; } }';
    compile_ok($source);
  }
}

# switch
{
  {
    my $source = 'class MyClass { static method main : void () { switch (1d) { } } }';
    compile_not_ok($source, q|The condition of switch statement must be an integer type within int|);
  }
  {
    my $source = 'class MyClass { static method main : void () { switch (1) { case Int->new(1): { } } } }';
    compile_not_ok($source, q|The operand type of case statement must be an integer literal of int type, a character litaral, or an enumeration value.|);
  }
  {
    my $source = 'class MyClass { static method main : void () { switch (1) { case "foo": { } } } }';
    compile_not_ok($source, q|The operand type of case statement must be an integer literal of int type, a character litaral, or an enumeration value.|);
  }
  {
    my $source = 'class MyClass { static method main : void () { switch (1) { case 1: { } case 1: { } } } }';
    compile_not_ok($source, q|The value of case statement cannnot be duplicated|);
  }
  {
    my $source = 'class MyClass { static method main : void () { switch (1) { case 1: { } default: { } default: { } } } }';
    compile_not_ok($source, q|Unexpected token "default"|);
  }
}

# bool type conversion
{
  {
    my $source = 'class MyClass { use Complex_2d; static method main : void () { my $var : Complex_2d; !$var; } }';
    compile_not_ok($source, qr'The operand type of bool type conversion must be a numeric type or an object type or a reference type or undef type');
  }
  {
    my $source = 'class MyClass { static method main : void () { my $var = 0; my $var_ref = \$var; !$var_ref; } }';
    compile_ok($source);
  }
}

# ==
{
  {
    my $source = 'class MyClass { static method main : void () { undef == 1; } }';
    compile_not_ok($source, q|If the left operand type of == operator is the undef type, the right operand type must be an object type, a reference type, or undef type.|);
  }
  
  {
    my $source = 'class MyClass { static method main : void () { 1 == undef; } }';
    compile_not_ok($source, q|If the left operand type of == operator is a numeric type, the right operand type must be a numeric type.|);
  }
  
  {
    my $source = 'class MyClass { static method main : void () { 1 == Int->new(1); } }';
    compile_not_ok($source, q|If the left operand type of == operator is a numeric type, the right operand type must be a numeric type.|);
  }
  
  {
    my $source = 'class MyClass { static method main : void () { my $left = 1; my $right = 2; \$left == \$right; } }';
    compile_ok($source);
  }
  
  {
    my $source = 'class MyClass { static method main : void () { my $left = 1; my $right = 2; \$left == $right; } }';
    compile_not_ok($source, q|If the left operand type of == operator is a reference type, the right operand type must be a reference type or undef type.|);
  }
  
  {
    my $source = 'class MyClass { static method main : void () { my $left = 1; my $right = 2; \$left == undef; } }';
    compile_ok($source);
  }
}

# !=
{
  {
    my $source = 'class MyClass { static method main : void () { undef != 1; } }';
    compile_not_ok($source, q|If the left operand type of != operator is the undef type, the right operand type must be an object type, a reference type, or undef type.|);
  }
  
  {
    my $source = 'class MyClass { static method main : void () { 1 != undef; } }';
    compile_not_ok($source, q|If the left operand type of != operator is a numeric type, the right operand type must be a numeric type.|);
  }
  
  {
    my $source = 'class MyClass { static method main : void () { 1 != Int->new(1); } }';
    compile_not_ok($source, q|If the left operand type of != operator is a numeric type, the right operand type must be a numeric type.|);
  }
  
  {
    my $source = 'class MyClass { static method main : void () { my $left = 1; my $right = 2; \$left != \$right; } }';
    compile_ok($source);
  }
  
  {
    my $source = 'class MyClass { static method main : void () { my $left = 1; my $right = 2; \$left != $right; } }';
    compile_not_ok($source, q|If the left operand type of != operator is a reference type, the right operand type must be a reference type or undef type.|);
  }
  
  {
    my $source = 'class MyClass { static method main : void () { my $left = 1; my $right = 2; \$left != undef; } }';
    compile_ok($source);
  }
}

# >
{
  {
    my $source = 'class MyClass { static method main : void () { "foo" > 1; } }';
    compile_not_ok($source, qr'The left operand type of > operator must be a numeric type');
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 > "foo"; } }';
    compile_not_ok($source, qr'The right operand type of > operator must be a numeric type');
  }
}

# >=
{
  {
    my $source = 'class MyClass { static method main : void () { "foo" >= 1; } }';
    compile_not_ok($source, qr'The left operand type of >= operator must be a numeric type');
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 >= "foo"; } }';
    compile_not_ok($source, qr'The right operand type of >= operator must be a numeric type');
  }
}

# <
{
  {
    my $source = 'class MyClass { static method main : void () { "foo" < 1; } }';
    compile_not_ok($source, qr'The left operand type of < operator must be a numeric type');
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 < "foo"; } }';
    compile_not_ok($source, qr'The right operand type of < operator must be a numeric type');
  }
}

# <=
{
  {
    my $source = 'class MyClass { static method main : void () { "foo" <= 1; } }';
    compile_not_ok($source, qr'The left operand type of <= operator must be a numeric type');
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 <= "foo"; } }';
    compile_not_ok($source, qr'The right operand type of <= operator must be a numeric type');
  }
}

# <=>
{
  {
    my $source = 'class MyClass { static method main : void () { "foo" <=> 1; } }';
    compile_not_ok($source, qr'The left operand type of <=> operator must be a numeric type');
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 <=> "foo"; } }';
    compile_not_ok($source, qr'The right operand type of <=> operator must be a numeric type');
  }
}

# gt
{
  {
    my $source = 'class MyClass { static method main : void () { 1 gt "foo"; } }';
    compile_not_ok($source, 'The left operand type of gt operator must be string type or byte[] type');
  }
  {
    my $source = 'class MyClass { static method main : void () { "foo" gt 1; } }';
    compile_not_ok($source, 'The right operand type of gt operator must be string type or byte[] type');
  }
}

# ge
{
  {
    my $source = 'class MyClass { static method main : void () { 1 ge "foo"; } }';
    compile_not_ok($source, 'The left operand type of ge operator must be string type or byte[] type');
  }
  {
    my $source = 'class MyClass { static method main : void () { "foo" ge 1; } }';
    compile_not_ok($source, 'The right operand type of ge operator must be string type or byte[] type');
  }
}

# lt
{
  {
    my $source = 'class MyClass { static method main : void () { 1 lt "foo"; } }';
    compile_not_ok($source, 'The left operand type of lt operator must be string type or byte[] type');
  }
  {
    my $source = 'class MyClass { static method main : void () { "foo" lt 1; } }';
    compile_not_ok($source, 'The right operand type of lt operator must be string type or byte[] type');
  }
}

# le
{
  {
    my $source = 'class MyClass { static method main : void () { 1 le "foo"; } }';
    compile_not_ok($source, 'The left operand type of le operator must be string type or byte[] type');
  }
  {
    my $source = 'class MyClass { static method main : void () { "foo" le 1; } }';
    compile_not_ok($source, 'The right operand type of le operator must be string type or byte[] type');
  }
}

# cmp
{
  {
    my $source = 'class MyClass { static method main : void () { 1 cmp "foo"; } }';
    compile_not_ok($source, 'The left operand type of cmp operator must be string type or byte[] type');
  }
  {
    my $source = 'class MyClass { static method main : void () { "foo" cmp 1; } }';
    compile_not_ok($source, 'The right operand type of cmp operator must be string type or byte[] type');
  }
}

# .
{
  {
    my $source = 'class MyClass { static method main : void () { Int->new(1) . "foo"; } }';
    compile_not_ok($source, 'The left operand type of . operator must be string type or byte[] type');
  }
  {
    my $source = 'class MyClass { static method main : void () { "foo" . Int->new(1); } }';
    compile_not_ok($source, 'The right operand type of . operator must be string type or byte[] type');
  }
}

# Capture
{
  {
    my $source = 'class MyClass { static method main : void () { [has foo : int = $foo] method : void () { }; } }';
    compile_not_ok($source, '$foo is not found');
  }
}

# new
{
  {
    my $source = 'class MyClass { static method main : void () { new int[1L]; } }';
    compile_not_ok($source, q|The array length specified by new operator must be an integer type within int|);
  }
  {
    my $source = 'class MyClass { static method main : void () { new int; } }';
    compile_not_ok($source, q|The operand type of new operator cannnot be a numeric type|);
  }
  {
    my $source = 'class MyClass { use Stringable; static method main : void () {  new Stringable; } }';
    compile_not_ok($source, q|The operand type of new operator cannnot be an interface type|);
  }
  {
    my $source = [
      'class MyClass { use MyPoint; static method main : void () { new MyPoint; } }',
      'class MyPoint : public pointer;',
    ];
    compile_ok($source);
  }
  {
    my $source = 'class MyClass { static method main : void () {  new Int; } }';
    compile_not_ok($source, q|The object of the protected Int class cannnot be created from the current class MyClass.|);
  }
}

# ^
{
  {
    my $source = 'class MyClass { static method main : void () { 1d ^ 1; } }';
    compile_not_ok($source, 'The left and right operand type of ^ operator must be an integer type');
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 ^ 1d; } }';
    compile_not_ok($source, 'The left and right operand type of ^ operator must be an integer type');
  }
}

# isa
{
  {
    my $source = 'class MyClass { static method main : void () { 1 isa Int; } }';
    compile_not_ok($source, 'The left operand type of isa operator must be an object type.');
  }
}

# isa_error
{
  {
    my $source = 'class MyClass { static method main : void () { (byte)1 isa_error Error; } }';
    compile_ok($source);
  }
  
  {
    my $source = 'class MyClass { static method main : void () { (short)1 isa_error Error; } }';
    compile_ok($source);
  }
  
  {
    my $source = 'class MyClass { static method main : void () { 1 isa_error Error; } }';
    compile_ok($source);
  }
  
  {
    my $source = 'class MyClass { static method main : void () { 1L isa_error Error; } }';
    compile_not_ok($source, 'The operand type of isa_error operator must be an integer type within int.');
  }
  
  {
    my $source = 'class MyClass { static method main : void () { 1 isa_error Error[]; } }';
    compile_not_ok($source, 'The right type of isa_error operator must be a class type.');
  }
  
  {
    my $source = 'class MyClass { static method main : void () { 1 isa_error byte; } }';
    compile_not_ok($source, 'The right type of isa_error operator must be a class type.');
  }
  
  {
    my $source = 'class MyClass { static method main : void () { Int->new(1) isa object; } }';
    compile_not_ok($source, 'The right type of isa operator must not be any object type.');
  }
}

# is_type
{
  {
    my $source = 'class MyClass { static method main : void () { 1 is_type Int; } }';
    compile_not_ok($source, 'The left operand type of is_type operator must be an object type.');
  }
  
  {
    my $source = 'class MyClass { static method main : void () { Int->new(1) is_type object; } }';
    compile_not_ok($source, 'The right type of is_type operator must not be any object type.');
  }
}

# is_error
{
  {
    my $source = 'class MyClass { static method main : void () { (byte)1 is_error Error; } }';
    compile_ok($source);
  }
  
  {
    my $source = 'class MyClass { static method main : void () { (short)1 is_error Error; } }';
    compile_ok($source);
  }
  
  {
    my $source = 'class MyClass { static method main : void () { 1 is_error Error; } }';
    compile_ok($source);
  }
  
  {
    my $source = 'class MyClass { static method main : void () { 1L is_error Error; } }';
    compile_not_ok($source, 'The operand type of is_error operator must be an integer type within int.');
  }
  
  {
    my $source = 'class MyClass { static method main : void () { 1 is_error Error[]; } }';
    compile_not_ok($source, 'The right type of is_error operator must be a class type.');
  }
  
  {
    my $source = 'class MyClass { static method main : void () { 1 is_error byte; } }';
    compile_not_ok($source, 'The right type of is_error operator must be a class type.');
  }
}

# @ - Array Length
{
  {
    my $source = 'class MyClass { static method main : void () { @1; } }';
    compile_not_ok($source, 'The right operand type of @ operator must be an array type');
  }
}

# length
{
  {
    my $source = 'class MyClass { static method main : void () { length new int[3]; } }';
    compile_not_ok($source, 'The operand type of length operator must be string type');
  }
}

# ++,-- Increment, Decrement
{
  {
    my $source = 'class MyClass { static method main : void () { my $var = "foo"; $var++; } }';
    compile_not_ok($source, 'The operand type of increment operator must be a numeric type');
  }
  {
    my $source = 'class MyClass { static method main : void () { my $var = "foo"; ++$var; } }';
    compile_not_ok($source, 'The operand type of increment operator must be a numeric type');
  }
  {
    my $source = 'class MyClass { static method main : void () { my $var = "foo"; $var--; } }';
    compile_not_ok($source, 'The operand type of decrement operator must be a numeric type');
  }
  {
    my $source = 'class MyClass { static method main : void () { my $var = "foo"; --$var; } }';
    compile_not_ok($source, 'The operand type of decrement operator must be a numeric type');
  }
  
}

# = Assignment
{
  {
    my $source = 'class MyClass { static method main : void () { my $var = undef; } }';
    compile_not_ok($source, q|The type of $var local variable cannnot be undef type.|);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $var : byte = "string"; } }';
    compile_not_ok($source, q|string type cannot be assigned to byte type in assignment operator.|);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $var = "string"; $var->[0] = \'a\'; } }';
    compile_not_ok($source, q|Characters cannot be set to non-mutable strings|);
  }
}

# return
{
  {
    my $source = 'class MyClass { static method main : void () { return 1; } }';
    compile_not_ok($source, q|If the return type is void, the method cannnot return the value.|);
  }
  {
    my $source = 'class MyClass { static method main : int () { return; } }';
    compile_not_ok($source, q|If the return type is non-void, the method must return a value.|);
  }
}

# + Unary Plus
{
  {
    my $source = 'class MyClass { static method main : void () { +"foo"; } }';
    compile_not_ok($source, q|The operand type of unary + operator must be a numeric type|);
  }
}

# - Unary Minus
{
  {
    my $source = 'class MyClass { static method main : void () { -"foo"; } }';
    compile_not_ok($source, q|The operand type of unary - operator must be a numeric type|);
  }
}

# copy
{
  {
    my $source = 'class MyClass { static method main : void () { copy "abc"; } }';
    compile_ok($source);
  }
  
  {
    my $source = 'class MyClass { static method main : void () { copy new byte[3]; } }';
    compile_ok($source);
  }
  
  {
    my $source = 'class MyClass { use Complex_2d; static method main : void () { copy new Complex_2d[3]; } }';
    compile_ok($source);
  }
  
  {
    my $source = 'class MyClass { static method main : void () { copy 1; } }';
    compile_not_ok($source, q|The operand type of copy operator must be string type, a numeric type, or a multi-numeric type.|);
  }
  
  {
    my $source = 'class MyClass { use Point;static method main : void () { copy Point->new; } }';
    compile_not_ok($source, q|The operand type of copy operator must be string type, a numeric type, or a multi-numeric type.|);
  }
}

# ~ Bit Not
{
  {
    my $source = 'class MyClass { static method main : void () { ~ 1d; } }';
    compile_not_ok($source, q|The operand type of ~ operator must be an integer type|);
  }
}

# + Addition
{
  {
    my $source = 'class MyClass { static method main : void () { "foo" + 1; } }';
    compile_not_ok($source, q|The left operand type of + operator must be a numeric type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 + "foo"; } }';
    compile_not_ok($source, q|The right operand type of + operator must be a numeric type|);
  }
}

# - Subtract
{
  {
    my $source = 'class MyClass { static method main : void () { "foo" - 1; } }';
    compile_not_ok($source, q|The left operand type of - operator must be a numeric type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 - "foo"; } }';
    compile_not_ok($source, q|The right operand type of - operator must be a numeric type|);
  }
}

# * Multiplication
{
  {
    my $source = 'class MyClass { static method main : void () { "foo" * 1; } }';
    compile_not_ok($source, q|The left operand type of * operator must be a numeric type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 * "foo"; } }';
    compile_not_ok($source, q|The right operand type of * operator must be a numeric type|);
  }
}

# / Division
{
  {
    my $source = 'class MyClass { static method main : void () { "foo" / 1; } }';
    compile_not_ok($source, q|The left operand type of / operator must be a numeric type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 / "foo"; } }';
    compile_not_ok($source, q|The right operand type of / operator must be a numeric type|);
  }
}

# div_uint
{
  {
    my $source = 'class MyClass { static method main : void () { 1L div_uint 1; } }';
    compile_not_ok($source, q|The left operand type of div_uint operator must be int type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 div_uint 1L; } }';
    compile_not_ok($source, q|The right operand type of div_uint operator must be int type|);
  }
}

# div_ulong
{
  {
    my $source = 'class MyClass { static method main : void () { 1 div_ulong 1L; } }';
    compile_not_ok($source, q|The left operand type of div_ulong operator must be long type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1L div_ulong 1; } }';
    compile_not_ok($source, q|The right operand type of div_ulong operator must be long type|);
  }
}

# % Division
{
  {
    my $source = 'class MyClass { static method main : void () { "foo" % 1; } }';
    compile_not_ok($source, q|The left operand type of % operator must be an integer type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 % "foo"; } }';
    compile_not_ok($source, q|The right operand type of % operator must be an integer type|);
  }
}

# mod_uint
{
  {
    my $source = 'class MyClass { static method main : void () { 1L mod_uint 1; } }';
    compile_not_ok($source, q|The left operand type of mod_uint operator must be int type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 mod_uint 1L; } }';
    compile_not_ok($source, q|The right operand type of mod_uint operator must be int type|);
  }
}

# mod_ulong
{
  {
    my $source = 'class MyClass { static method main : void () { 1 mod_ulong 1L; } }';
    compile_not_ok($source, q|The left operand type of mod_ulong operator must be long type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1L mod_ulong 1; } }';
    compile_not_ok($source, q|The right operand type of mod_ulong operator must be long type|);
  }
}

# & Division
{
  {
    my $source = 'class MyClass { static method main : void () { "foo" & 1; } }';
    compile_not_ok($source, q|The left operand type of & operator must be an integer type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 & "foo"; } }';
    compile_not_ok($source, q|The right operand type of & operator must be an integer type|);
  }
}

# | Division
{
  {
    my $source = 'class MyClass { static method main : void () { "foo" | 1; } }';
    compile_not_ok($source, q|The left operand type of \| operator must be an integer type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 | "foo"; } }';
    compile_not_ok($source, q|The right operand type of \| operator must be an integer type|);
  }
}

# << Left Shift
{
  {
    my $source = 'class MyClass { static method main : void () { "foo" << 1; } }';
    compile_not_ok($source, q|The left operand type of << operator must be an integer type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 << 1d; } }';
    compile_not_ok($source, q|The right operand type of << operator must be int type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 << 1L; } }';
    compile_not_ok($source, q|The right operand type of << operator must be int type|);
  }
}

# >> Right Arithmetic Shift
{
  {
    my $source = 'class MyClass { static method main : void () { "foo" >> 1; } }';
    compile_not_ok($source, q|The left operand type of >> operator must be an integer type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 >> 1d; } }';
    compile_not_ok($source, q|The right operand type of >> operator must be int type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 >> 1L; } }';
    compile_not_ok($source, q|The right operand type of >> operator must be int type|);
  }
}

# >>> Right Logical Shift
{
  {
    my $source = 'class MyClass { static method main : void () { "foo" >>> 1; } }';
    compile_not_ok($source, q|The left operand type of >>> operator must be an integer type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 >>> 1d; } }';
    compile_not_ok($source, q|The right operand type of >>> operator must be int type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 >>> 1L; } }';
    compile_not_ok($source, q|The right operand type of >>> operator must be int type|);
  }
}

# die
{
  {
    my $source = 'class MyClass { static method main : void () { die; } }';
    compile_ok($source);
  }
  
  {
    my $source = 'class MyClass { static method main : void () { die undef; } }';
    compile_ok($source);
  }
  
  {
    my $source = 'class MyClass { static method main : void () { die Int->new(1); } }';
    compile_not_ok($source, q|Int type cannot be assigned to string type in assignment operator.|);
  }
  {
    my $source = 'class MyClass { static method main : void () { die byte; } }';
    compile_not_ok($source, q|The error class of die statement must be a class type|);
  }
}

# warn
{
  {
    my $source = 'class MyClass { static method main : void () { warn; } }';
    compile_ok($source);
  }
  
  {
    my $source = 'class MyClass { static method main : void () { my $num = 1; my $num_ref = \$num; warn $num_ref; } }';
    compile_ok($source);
  }
  {
    my $source = 'class MyClass { static method main : void () { warn undef; } }';
    compile_not_ok($source, q|The operand type of warn operator must be a numeric type, an object type, or a reference type.|);
  }
}

# print
{
  {
    my $source = 'class MyClass { static method main : void () { print Int->new(1); } }';
    compile_not_ok($source, q|The operand type of print operator must be string type|);
  }
}

# make_read_only
{
  {
    my $source = 'class MyClass { static method main : void () { make_read_only 1; } }';
    compile_not_ok($source, q|The operand type of make_read_only operator must be string type|);
  }
}

# is_read_only
{
  {
    my $source = 'class MyClass { static method main : void () { is_read_only 1; } }';
    compile_not_ok($source, q|The operand type of is_read_only operator must be string type|);
  }
}

# Reference
{
  {
    my $source = 'class MyClass { static method main : void () { my $var = "foo"; \$var; } }';
    compile_not_ok($source, q|The operand type of refernece operator must be a numeric type or a multi-numeric type|);
  }
}

# Dereference
{
  {
    my $source = 'class MyClass { static method main : void () { my $var = "foo"; $$var; } }';
    compile_not_ok($source, q|The operand type of dereference operaotr must be a numeric reference type or a multi-numeric reference type|);
  }
}

# Variable
{
  {
    my $source = 'class MyClass { static method main : void () { my $var = 0; my $var = 0; } }';
    compile_not_ok($source, q|Redeclaration of $var variable|);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $var; } }';
    compile_not_ok($source, q|The type of $var variable is not detected.|);
  }
  {
    my $source = 'class MyClass { static method main : void () { $var; } }';
    compile_not_ok($source, q|$var is not found|);
  }
  {
    my $source = 'class MyClass { static method main : void () { $MyClass::FOO; } }';
    compile_not_ok($source, q|$MyClass::FOO is not found|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 && (my $var = 0); } }';
    compile_ok($source);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $var = 0; 1 && (my $var = 0); } }';
    compile_not_ok($source, q|Redeclaration of $var variable.|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 || (my $var = 0); } }';
    compile_ok($source);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $var = 0; 1 || (my $var = 0); } }';
    compile_not_ok($source, q|Redeclaration of $var variable.|);
  }
  {
    my $source = 'class MyClass { static method main : void () { !(my $var = 0); } }';
    compile_ok($source);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $var = 0; !(my $var = 0); } }';
    compile_not_ok($source, q|Redeclaration of $var variable.|);
  }
  
  {
    my $source = 'class MyClass { static method main : void () { $_; } }';
    compile_not_ok($source, q|$_ is not found.|);
  }
}

# Method call
{
  {
    my $source = [
      'class MyClass { use MyClass2; static method main : void () { MyClass2->foo();  } }',
      'class MyClass2 { static private method foo : void () {} }'
    ];
    compile_not_ok($source, q|The private MyClass2#foo method cannnot be called from the current class MyClass|);
  }
  {
    my $source = 'class MyClass { static method main : void () { &foo(); } static method foo : void ($arg0 : int, $arg1 : int = 0) { } }';
    compile_not_ok($source, q|Too few arguments are passed to MyClass#foo method|);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $object = new MyClass; $object->foo(); } method foo : void ($arg0 : int, $arg1 : int = 0) { } }';
    compile_not_ok($source, q|Too few arguments are passed to MyClass#foo method|);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $object = new MyClass; $object->foo(1, 2, 3); } method foo : void ($arg0 : int, $arg1 : int = 0) { } }';
    compile_not_ok($source, q|Too many arguments are passed to MyClass#foo method|);
  }
  
  {
    my $source = 'class MyClass { static method main : void () { &foo(1); } static method foo : void () { } }';
    compile_not_ok($source, q|Too many arguments are passed to MyClass#foo method|);
  }
  
}

# Class Variable Access
{
  {
    my $source = [
      'class MyClass { use MyClass2; static method main : void () { $MyClass2::FOO;  } }',
      'class MyClass2 { our $FOO : private int; }'
    ];
    compile_not_ok($source, q|The private $MyClass2::FOO class variable cannnot be accessed from the current class MyClass.|);
  }
  
  {
    my $source = [
      'class MyClass { our $X : int get {}; }',
    ];
    compile_not_ok($source, q|A class variable attribute of either 'ro' or 'rw' must be specified when the getter is defined.|);
  }
  
  {
    my $source = [
      'class MyClass { our $X : int set {}; }',
    ];
    compile_not_ok($source, q|A class variable attribute of either 'wo' or 'rw' must be specified when the setter is defined.|);
  }
  
  {
    my $source = [
      'class MyClass { our $X : virtual int; static method main : void () { $X; } }',
    ];
    compile_not_ok($source, q|$X is not found.|);
  }
  
  {
    my $source = [
      'class MyClass { our $X : wo int get : MyClass; }',
    ];
    compile_not_ok($source, q|Unexpected token|);
  }
  
  {
    my $source = [
      'class MyClass { our $X : wo int get : MyClass {} }',
    ];
    compile_not_ok($source, q|Unexpected token|);
  }
  
  {
    my $source = [
      'class MyClass { our $X : wo int get : MyClass ($_ : int) {} }',
    ];
    compile_not_ok($source, q|Unexpected token|);
  }
  
  {
    my $source = [
      'class MyClass { our $X : wo int set : MyClass; }',
    ];
    compile_not_ok($source, q|A return type cannot be specified for a class variable setter.|);
  }
  
}

# Class Variable Definition
{
  {
    my $source = 'class MyClass { our $FOO : int; our $FOO : int;}';
    compile_not_ok($source, qr/Redeclaration of MyClass#\$FOO class variable/);
  }
}

# Element Access
{
  {
    my $source = 'class MyClass { static method main : void () { my $var = 1; $var->[0]; } }';
    compile_not_ok($source, q|The invocant of the element access must be an array type, string type, a class type, or an interface type.|);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $var = new int[1]; $var->[1L]; } }';
    compile_not_ok($source, q|The index of the element access must be int type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $var = new int[1]; $var->["foo"]; } }';
    compile_not_ok($source, q|The index of the element access must be int type|);
  }
}

# Field Access
{
  {
    my $source = 'class MyClass { static method main : void () { my $var = 1; $var->{x}; } }';
    compile_not_ok($source, q|The invocant of the field access must be a class type, or a multi-numeric type, or a multi-numeric reference type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $object = new MyClass; $object->{foo}; } }';
    compile_not_ok($source, q|foo field is not found in MyClass class or its super classes|);
  }
  {
    my $source = 'class MyClass { has x : int; static method main : void () { my $object = new MyClass; weaken $object->{x}; } }';
    compile_not_ok($source, q|MyClass#x field operated by weaken operator must be an object type|);
  }
  {
    my $source = 'class MyClass { use Complex_2d; has x : int; static method main : void () { my $value = Complex_2d->new; weaken $value->{re}; } }';
    compile_not_ok($source, q|Invalid use of weaken operator: the incovant of the field access Complex_2d#re must be a class type.|);
  }
  {
    my $source = 'class MyClass { use Complex_2d; has x : int; static method main : void () { my $value = Complex_2d->new; unweaken $value->{re}; } }';
    compile_not_ok($source, q|Invalid use of unweaken operator: the incovant of the field access Complex_2d#re must be a class type.|);
  }
  {
    my $source = 'class MyClass { has x : int; static method main : void () { my $object = new MyClass; unweaken $object->{x}; } }';
    compile_not_ok($source, q|MyClass#x field operated by unweaken operator must be an object type|);
  }
  {
    my $source = 'class MyClass { use Complex_2d; has x : int; static method main : void () { my $value = Complex_2d->new; exists $value->{re}; } }';
    compile_not_ok($source, q|Invalid use of exists operator: the incovant of the field access Complex_2d#re must be a class type.|);
  }
  {
    my $source = 'class MyClass { use Complex_2d; has x : int; static method main : void () { my $value = Complex_2d->new; delete $value->{re}; } }';
    compile_not_ok($source, q|Invalid use of delete operator: the incovant of the field access Complex_2d#re must be a class type.|);
  }
  {
    my $source = 'class MyClass { use Complex_2d; has x : int; static method main : void () { my $value = Complex_2d->new; isweak $value->{re}; } }';
    compile_not_ok($source, q|Invalid use of isweak operator: the incovant of the field access Complex_2d#re must be a class type.|);
  }
  {
    my $source = 'class MyClass { has x : int; static method main : void () { my $object = new MyClass; isweak $object->{x}; } }';
    compile_not_ok($source, q|MyClass#x field operated by isweak operator must be an object type|);
  }
  {
    my $source = [
      'class MyClass { use MyClass2; static method main : void () { my $object = new MyClass2; $object->{x};  } }',
      'class MyClass2 : public { has x : private int; }'
    ];
    compile_not_ok($source, q|The private MyClass2#x field cannnot be accessed from the current class MyClass|);
  }
  {
    my $source = [
      'class MyClass { use MyClass2; static method main : void () { my $object = new MyClass2; $object->{x};  } }',
      'class MyClass2 : public { has x : protected int; }'
    ];
    compile_not_ok($source, q|The protected MyClass2#x field cannnot be accessed from the current class MyClass|);
  }
  {
    my $source = [
      'class MyClass extends MyClass2 { use MyClass2; static method main : void () { my $object = new MyClass2; $object->{x};  } }',
      'class MyClass2 : protected { has x : protected int; }'
    ];
    compile_ok($source);
  }
  {
    my $source = [
      'class MyClass extends MyClass2 { use MyClass2; static method main : void () { my $object = new MyClass; $object->{x};  } }',
      'class MyClass2 { has x : protected int; }'
    ];
    compile_ok($source);
  }
  
  {
    my $source = 'class MyClass { has x : int; method foo : void () { [has this : MyClass = $self] method : void () { $self->{this}->{x}; }; } }';
    compile_ok($source);
  }
  
  {
    my $source = 'class MyClass { has x : int; method foo : void () { [has this : MyClass = $self] method : void () { $self->{this}->{x}; [has this : MyClass = $self->{this}] method : void () { $self->{this}->{x}; }; }; } }';
    compile_ok($source);
  }
  
  {
    my $source = [
      'class MyClass { use MyClass2; has x : protected int; }',
      'class MyClass2 extends MyClass { method foo : void () { [has this : MyClass2 = $self] method : void () { $self->{this}->{x}; }; } }',
    ];
    compile_ok($source);
  }
  
  {
    my $source = 'class MyClass { use Fn as FUNC; method foo : void () { method : void () { FUNC->INT_MAX; }; } }';
    compile_ok($source);
  }
  
  {
    my $source = [
      'class MyClass { has x : int get {}; }',
    ];
    compile_not_ok($source, q|A field attribute of either 'ro' or 'rw' must be specified when the getter is defined.|);
  }
  
  {
    my $source = [
      'class MyClass { has x : int set {}; }',
    ];
    compile_not_ok($source, q|A field attribute of either 'wo' or 'rw' must be specified when the setter is defined.|);
  }
  
  {
    my $source = [
      'class MyClass { has x : virtual int; static method main : void () { my $object = new MyClass; $object->{x}; } }',
    ];
    compile_not_ok($source, q|x field is not found in MyClass class or its super classes.|);
  }
  
}

# Hash Value Access
{
  {
    my $source = 'class MyClass { static method main : void () { use Hash; my $hash = 1; $hash->{1}; } }';
    compile_not_ok($source, q|The invocant of the hash value access must be a class type or an interface type.|);
  }
  
  {
    my $source = 'class MyClass { static method main : void () { use Hash; my $hash = Hash->new; $hash->{1}; } }';
    compile_not_ok($source, q|The key of the hash value access must be string type.|);
  }
}

# Field Definition
{
  {
    my $source = 'class MyClass { has foo : int; has foo : int; }';
    compile_not_ok($source, qr/Redeclaration of MyClass#foo field/);
  }
  
  # Field - Reference
  {
    {
      my $source = 'class MyClass  { has foo : int*; }';
      compile_not_ok($source, q|The reference type cannnot used in the definition of the field.|);
    }
    
  }
  
}

# copy_fields
{
  {
    my $source = 'class MyClass { use Point; static method main : void () { my $point = Point->new; my $point2 = Point->new; copy_fields $point, $point, int; } }';
    compile_not_ok($source, q|The operand type of copy_fields operator must be a class type.|);
  }
}

# can
{
  {
    my $source = 'class MyClass { use Point; static method main : void () { my $point = Point->new; $point can x; } }';
    compile_ok($source);
  }
  {
    my $source = 'class MyClass { use Point; static method main : void () { my $anon = method : void () {}; $anon can ""; } }';
    compile_ok($source);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $var = 0; $var can x; } }';
    compile_not_ok($source, q|he invocant of can operator must be a class type or an interface type|);
  }
  {
    my $source = 'class MyClass { use Point; static method main : void () { my $point = Point->new; $point can not_defined; } }';
    compile_not_ok($source, q|Point#not_defined method, the operand type of can operator, must be defined|);
  }
  {
    my $source = 'class MyClass { use Point; static method main : void () { my $anon = method : void () {}; $anon can "a"; } }';
    compile_not_ok($source, qr|If the right operand of can operator is a constant value, it must be an empty string ""|);
  }
}

# Type Cast/Type Conversion
{
  {
    my $source = 'class MyClass { static method main : void () { (Int)"foo"; } }';
    compile_not_ok($source, q|The type cast from string to Int is not allowed|);
  }
  
  {
    my $source = 'class MyClass { static method main : void () { my $nums = new byte[1]; $nums->[0] = 1; } }';
    compile_ok($source);
  }
  
  {
    my $source = 'class MyClass { static method main : void () { my $num : float = 1.0; } }';
    compile_ok($source);
  }
  
  {
    my $source = 'class MyClass { static method main : void () { my $num : float = 1.0; } }';
    compile_ok($source);
  }
  
  {
    my $source = 'class MyClass { static method main : void () { my $num : float = 1.1111111111111111111111111111111111111111111111; } }';
    compile_ok($source);
  }
  
  {
    my $source = 'class MyClass { static method main : void () { my $num : float = 0.3; } }';
    compile_ok($source);
  }
  
  {
    my $source = 'class MyClass { static method main : void () { my $nums = new float[2]; $nums->[0] = 1.2; } }';
    compile_ok($source);
  }
  
  {
    my $source = 'class MyClass { static method main : void () { my $nums = [(float)1.2, 0.3]; } }';
    compile_ok($source);
  }
}

# Type requirement
{
  {
    my $source = q|class MyClass { static method main : void () { my $ret = &main(); } }|;
    compile_not_ok($source, q|The void type cannnot be assigned in assignment operator|);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $string : mutable string = "abc"; } }';
    compile_not_ok($source, q|string type cannot be assigned to mutable string type in assignment operator.|);
  }
  {
    my $source = 'class MyClass { static method main : mutable string () { return "abc"; } }';
    compile_not_ok($source, q|string type cannot be assigned to mutable string type in return statement.|);
  }
  {
    my $source = 'class MyClass { static method main : void () { &foo("abc"); } static method foo : int ($string : mutable string) { }}';
    compile_not_ok($source, q|string type cannot be assigned to mutable string type in the 1th argument of MyClass#foo method.|);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $object = new MyClass; $object->foo("abc"); } method foo : int ($string : mutable string) { }}';
    compile_not_ok($source, q|string type cannot be assigned to mutable string type in the 1th argument of MyClass#foo method.|);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $var : int = "foo"; } }';
    compile_not_ok($source, q|string type cannot be assigned to int type in assignment operator.|);
  }
}

# Resolve types
{
  {
    my $source = 'class MyClass { static method main : void () { new NotFound; } }';
    compile_not_ok($source, q|NotFound class is not found|);
  }
  {
    my $source = 'class MyClass { static method main : void ($arg : Int*) {} }';
    compile_not_ok($source, q|The reference type must be a numeric refernce type or a multi-numeric reference type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $var : mutable int;} }';
    compile_not_ok($source, q|The type qualifier 'mutable' is only allowed in string type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $var : object[][];} }';
    compile_not_ok($source, q|The multi dimensional array of any object is not allowed|);
  }
  {
    my $source = 'class MyClass { static method main : void () { [(object[])undef]; } }';
    compile_not_ok($source, q|The creation of a multi dimensional array of any object is not allowed.|);
  }
}

# Method call - resolve
{
  {
    my $source = 'class MyClass { static method main : void () { MyClass->not_defined; } }';
    compile_not_ok($source, q|MyClass#not_defined method is not found|);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $var = Int->new(1); $var->not_defined; } }';
    compile_not_ok($source, q|not_defined method is not found in Int class or its super classes|);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $var = 1; $var->new; } }';
    compile_not_ok($source, q|The invocant of new method must be a class type or an interface type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $point = Point->new; } }';
    compile_not_ok($source, q|Point class is not found.|);
  }
  {
    my $source = 'class MyClass { use Point; static method main : void () { my $point = Point->not_defined; } }';
    compile_not_ok($source, q|Point#not_defined method is not found|);
  }
  {
    my $source = 'class MyClass { use Point; static method main : void () { my $point = Point->new; $point->Point::not_found; } }';
    compile_not_ok($source, q|Point::not_found method called as a static instance method call is not found.|);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $var = Int->new(1); $var->new; } }';
    compile_not_ok($source, q|Int#new method called as an instance method call is found, but it must be an instance method.|);
  }
  {
    my $source = [
      'class MyClass { use MyClass2; static method main : void () { my $object = new MyClass2; $object->foo; } }',
      'class MyClass2 extends MyClass : public { static method foo : void () {} }',
    ];
    compile_not_ok($source, q|MyClass2#foo method called as an instance method call is found, but it must be an instance method.|);
  }
  {
    my $source = 'class MyClass { use Stringable; use Point3D; static method main : void () { my $point3d = Point3D->new; $point3d->Stringable::to_string; } }';
    compile_ok($source);
  }
  {
    my $source = 'class MyClass { use Stringable; use Point3D; static method main : void () { my $stringable = (Stringable)Point3D->new; $stringable->SUPER::clear; } }';
    compile_not_ok($source, q|SUPER::clear method called as a static instance method call is not found.|);
  }
  {
    my $source = 'class MyClass { use Stringable; use Point3D; static method main : void () { my $stringable = (Stringable)Point3D->new; $stringable->NOT_FOUND::clear; } }';
    compile_not_ok($source, q|NOT_FOUND class used in the static instance method call is not found.|);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $var = Int->new(1); $var->not_defined; } }';
    compile_not_ok($source, q|not_defined method is not found in Int class or its super classes|);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $var = Int->new(1); $var->not_defined; } }';
    compile_not_ok($source, q|not_defined method is not found in Int class or its super classes|);
  }
  {
    my $source = [
      'class MyClass { use MySockaddrIn; static method main : void () { my $result_address = new MySockaddrIn; $result_address->port;} }',
      'class MySockaddrIn extends MySockaddr : public;',
      'class MySockaddr : public;',
    ];
    compile_not_ok($source, q|port method is not found in MySockaddrIn class or its super classes|);
  }
  
  {
    my $source = 'class MyClass { static method main : void () { my $self = new MyClass; $self->MyClass::foo; } method foo : void () { } }';
    compile_ok($source);
  }
  
  {
    my $source = 'class MyClass { static method main : void () { my $self = new MyClass; $self->MyClass::foo; } static method foo : void () { } }';
    compile_not_ok($source, q|MyClass::foo method called as a static instance method call is found, but it must be an instance method.|);
  }
  
  {
    my $source = 'class MyClass { static method main : void () { MyClass->foo; } method foo : void () { } }';
    compile_not_ok($source, q|MyClass#foo method called as a class method call is found, but it must be a class method.|);
  }
  
}

# Multi-Numeric Type
{
  {
    my $source = 'class MyClass_1i : mulnum_t { has x : object; }';
    compile_not_ok($source, q|The multi-numeric type must have the only fields of numeric types|);
  }
  {
    my $source = 'class MyClass_2i : mulnum_t { has x : int; has y : long; }';
    compile_not_ok($source, q|The fields of the multi-numeric type must be of the same type|);
  }
  {
    my $source = 'class MyClass : mulnum_t { has x : int; has y : int; }';
    compile_not_ok($source, q|The name of the multi-numeric type MyClass must end with with _2i.|);
  }
  {
    my $source = 'class MyClass { use Complex_2d; our $FOO : Complex_2d; }';
    compile_not_ok($source, q|The multi-numeric type cannnot used in the definition of the class variable|);
  }
  {
    my $source = 'class MyClass { use Complex_2d; has foo : Complex_2d; }';
    compile_not_ok($source, q|The multi-numeric type cannnot used in the definition of the field|);
  }
}

# Optional Argument
{
  {
    my $source = 'class MyClass {  static method main : void ($arg1 : int = Int->new(1)) { } }';
    compile_not_ok($source, q|The default value of the optional argument $arg1 must be a constant value|);
  }
  {
    my $source = 'class MyClass {  static method main : void ($arg1 : byte = 1000) { } }';
    compile_not_ok($source, q|The default value of the optional argument $arg1 must be able to be assigned to the argument|);
  }
  {
    my $source = 'class MyClass { use Complex_2d; static method main : void ($arg1 : Complex_2d = 0) { } }';
    compile_not_ok($source, q|The optional argument $arg1 is not allowed. The type must be a numeric type, an object type, or a reference type.|);
  }
  {
    my $source = 'class MyClass { static method main : void ($arg1 : int* = 0) { } }';
    compile_not_ok($source, q|The default value of the optional argument $arg1 must be undef.|);
  }
  {
    my $source = 'class MyClass { static method main : void ($arg1 : int* = 0) { } }';
    compile_not_ok($source, q|The default value of the optional argument $arg1 must be undef.|);
  }
  {
    my $source = 'class MyClass { static method main : void ($arg1 : int* = undef) { } }';
    compile_ok($source);
  }
  {
    my $source = 'class MyClass { use Complex_2d; static method main : void ($arg1 : Complex_2d* = undef) { } }';
    compile_ok($source);
  }
  {
    my $source = 'class MyClass { static method main : void ($arg1 : int = 0, $arg2 : int) { } }';
    compile_not_ok($source, q|Optional arguments must be placed at the end of the arguments.|);
  }
  compile_not_ok_file('CompileError::Method::TooManyArguments', qr/The width of the arguments must be less than or equal to 255/);
  compile_not_ok_file('CompileError::Method::TooManyArgumentsMulnum', qr/The width of the arguments must be less than or equal to 255/);
  
  {
    my $source = 'class MyClass { use Complex_2d; static method main : void ($arg1 : int = 0.0) { } }';
    compile_not_ok($source, q|The default value of the optional argument $arg1 must be able to be assigned to the argument.|);
  }
  
  {
    my $source = 'class MyClass { use Complex_2d; static method main : void ($arg1 : float = 0.0) { } }';
    compile_ok($source);
  }
  
  {
    my $source = 'class MyClass { use Complex_2d; static method main : void ($arg1 : int = -2147483648L) { } }';
    compile_ok($source);
  }
  
  {
    my $source = 'class MyClass { use Complex_2d; static method main : void ($arg1 : int = -2147483649L) { } }';
    compile_not_ok($source, q|The default value of the optional argument $arg1 must be able to be assigned to the argument.|);
  }
  {
    my $source = 'class MyClass {  static method main : void ($arg1 : Int = undef) { } }';
    compile_ok($source);
  }
  {
    my $source = 'class MyClass {  static method main : void ($arg1 : Int = Int->new(1)) { } }';
    compile_not_ok($source, q|The default value of the optional argument $arg1 must be undef.|);
  }
}

# Return type
{
  {
    my $source = 'class MyClass { static method main : int* () { } }';
    compile_not_ok($source, q|The return type cannnot be a reference|);
  }
}

# Inheritance
{
  {
    my $source = 'class MyClass extends Stringable {}';
    compile_not_ok($source, q|The parant class must be a class type|);
  }
  {
    my $source = [
      'class MyClass extends MyClass2 {}',
      'class MyClass2 : pointer;',
    ];
    compile_ok($source);
  }
  {
    my $source = 'class MyClass extends MyClass {}';
    compile_not_ok($source, q|The name of the parant class must be different from the name of the class|);
  }
  {
    my $source = 'class MyClass extends Point : interface_t { required method foo : void (); }';
    compile_not_ok($source, q|The current class must be a class type when the class becomes a child class|);
  }
  {
    my $source = 'class MyClass extends Point : pointer { }';
    compile_ok($source);
  }
  {
    my $source = 'class MyClass : interface_t { method foo : void (); }';
    compile_ok($source);
  }
  {
    my $source = [
      'class MyClass extends MyClass2 { static method new : void ($arg1 : int) {} }',
      'class MyClass2 { method new : void () {} }'
    ];
    compile_not_ok($source, q|MyClass#new method must be an instance method because its interface method is defined in MyClass2 class.|);
  }
  {
    my $source = [
      'class MyClass extends MyClass2 { static method new : void ($arg1 : int) {} }',
      'class MyClass2 { static method new : void () {} }'
    ];
    compile_ok($source);
  }
  {
    my $source = [
      'class MyClass2 extends MyClass { use Point; use Point3D; method main : void ($point : Point3D) {} }',
      'class MyClass { use Point; use Point3D; method main : void ($point : Point) {} }',
    ];
    compile_ok($source);
  }
  
  {
    my $source = [
      'class MyClass2 extends MyClass { use Point; use Point3D; method main : void ($point : Point) {} }',
      'class MyClass { use Point; use Point3D; method main : void ($point : Point3D) {} }',
    ];
    compile_not_ok($source, q|The 1th argument(Point type) of MyClass2#main method must be able to be assigned to the 1th argument(Point3D type) of MyClass#main method.|);
  }
  
  {
    my $source = [
      'class MyClass extends MyClassParent : public { method main : void () { my $my_class = new MyClass; $my_class->{foo}; } }',
      'class MyClassParent { has foo : private int; }',
    ];
    compile_not_ok($source, q|The private MyClassParent#foo field cannnot be accessed from the current class MyClass.|);
  }
  
  {
    my $source = [
      'class MyClass extends MyClassParent : public { method main : void () { my $my_class = new MyClass; $my_class->{foo}; } }',
      'class MyClassParent { has foo : int; }',
    ];
    compile_ok($source);
  }
  
  {
    my $source = [
      'class MyClass extends MyClassParent { method main : void () { $MyClassParent::FOO; } }',
      'class MyClassParent { our $FOO : int; }',
    ];
    compile_ok($source);
  }
  
  {
    my $source = [
      'class MyClass extends MyClassParent { method main : void () { $MyClassParent::FOO; } }',
      'class MyClassParent { our $FOO : private int; }',
    ];
    compile_not_ok($source, q|The private $MyClassParent::FOO class variable cannnot be accessed from the current class MyClass.|);
  }
  
  {
    my $source = [
      'class MyClass extends MyClassParent { method main : void () { my $my_class = new MyClass; $my_class->{foo}; } }',
      'class MyClassParent { has foo : protected int; }',
    ];
    compile_ok($source);
  }
  
  {
    my $source = [
      'class MyClass extends MyClassParent { method main : void () { my $my_class = new MyClass; $my_class->{foo}; } }',
      'class MyClassParent { has foo : public int; }',
    ];
    compile_ok($source);
  }
  
  {
    my $source = [
      'class MyClass extends MyClassParent { method main : void () { new MyClassParent; } }',
      'class MyClassParent { }',
    ];
    compile_ok($source);
  }
  
  {
    my $source = [
      'class MyClass extends MyClassParent { method main : void () { new MyClassParent; } }',
      'class MyClassParent : private { }',
    ];
    compile_not_ok($source, q|The object of the private MyClassParent class cannnot be created from the current class MyClass.|);
  }
  
}

# interface Statement
{
  {
    my $source = 'class MyClass  { interface Point; }';
    compile_not_ok($source, q|The interface specified by interface statement must be an interface type|);
  }
  {
    my $source = 'class MyClass  { interface Stringable; method to_string : string ($arg : int) {} }';
    compile_not_ok($source, q|The length of the arguments of Stringable#to_string method must be greater than or equal to the length of the required arguments of MyClass#to_string method.|);
  }
  {
    my $source = 'class MyClass  { interface Stringable; static method to_string : string ($self : Stringable) {} }';
    compile_not_ok($source, q|MyClass#to_string method must be an instance method because its interface method is defined in Stringable interface.|);
  }
  {
    my $source = [
      'class MyClass { interface MyInterface; method foo : void ($arg1 : int, $arg2 : long) {} }',
      'class MyInterface : interface_t { required method foo : void ($arg1 : int, $arg2 : int); }',
    ];
    compile_not_ok($source, q|The 2th argument(long type) of MyClass#foo method must be able to be assigned to the 2th argument(int type) of MyInterface#foo method.|);
  }
  {
    my $source = [
      'class MyClass { interface MyInterface; method foo : MyClass () {} }',
      'class MyInterface : interface_t { required method foo : object (); }',
    ];
    compile_ok($source);
  }
  {
    my $source = [
      'class MyClass { interface MyInterface; method foo : object () {} }',
      'class MyInterface : interface_t { required method foo : MyClass  (); }',
    ];
    compile_not_ok($source, q|The return type(object type) of MyClass#foo method must be able to be assigned to the return type(MyClass type) of MyInterface#foo method.|);
  }
  {
    my $source = [
      'class MyClass { use Point; use Point3D; interface MyInterface; method foo : Point3D () {} }',
      'class MyInterface : interface_t { required method foo : Point (); }',
    ];
    compile_ok($source);
  }
  {
    my $source = [
      'class MyClass { use Point; use Point3D; interface MyInterface; method foo : Point () {} }',
      'class MyInterface : interface_t { required method foo : Point3D  (); }',
    ];
    compile_not_ok($source, q|The return type(Point type) of MyClass#foo method must be able to be assigned to the return type(Point3D type) of MyInterface#foo method.|);
  }

  {
    my $source = [
      'class MyClass { use Point; use Point3D; interface MyInterface; method foo : int () {} }',
      'class MyInterface : interface_t { required method foo : long  (); }',
    ];
    compile_not_ok($source, q|The return type(int type) of MyClass#foo method must be able to be assigned to the return type(long type) of MyInterface#foo method.|);
  }
  {
    {
      my $source = [
        'class MyClass extends MyClass::Parent { method foo : long ($num : int) { return 0; } }',
        'class MyClass::Parent { interface MyClass::Interface; method has_interfaces : int () { return 1; } }',
        'class MyClass::Interface : interface_t { required method has_interfaces : int (); method foo : long ($num : int); }',
      ];
      compile_ok($source);
    }
  }
  {
    {
      my $source = [
        'class MyClass extends MyClass::Parent { method foo : long ($num : int, $num2 : int) { return 0; } }',
        'class MyClass::Parent { interface MyClass::Interface; method has_interfaces : int () { return 1; } }',
        'class MyClass::Interface : interface_t { required method has_interfaces : int (); method foo : long ($num : int); }',
      ];
      compile_not_ok($source, qr|The length of the arguments of MyClass::Interface#foo method must be greater than or equal to the length of the required arguments of MyClass#foo method.|);
    }
  }
  {
    {
      my $source = [
        'class MyClass extends MyClass::Parent { method foo : long ($num : int, $num2 : int = 0) { return 0; } }',
        'class MyClass::Parent { interface MyClass::Interface; method has_interfaces : int () { return 1; } }',
        'class MyClass::Interface : interface_t { required method has_interfaces : int (); method foo : long ($num : int); }',
      ];
      compile_ok($source);
    }
  }
  {
    {
      my $source = [
        'class MyClass extends MyClass::Parent { method foo : long ($num : int) { return 0; } }',
        'class MyClass::Parent { interface MyClass::Interface; method has_interfaces : int () { return 1; } }',
        'class MyClass::Interface : interface_t { required method has_interfaces : int (); method foo : long ($num : int, $num2 : int = 0); }',
      ];
      compile_ok($source);
    }
  }
  
  {
    my $source = 'class MyClass : interface_t { static method foo : void () { new MyClass; } }';
    compile_not_ok($source, q|The operand type of new operator cannnot be an interface type.|);
  }
}

# Duck Typing
{
  {
    my $source = [
      'class MyClass  { use Stringable; method to_string : string () {} static method main : void () { my $stringable : Stringable = new MyClass; } }',
    ];
    compile_ok($source);
  }
}

# Inheritance
{
  {
    my $source = [
      'class MyClass extends MyClass2;',
      'class MyClass2 extends MyClass3;',
      'class MyClass3 extends MyClass;',
    ];
    compile_not_ok($source, q|Recursive inheritance. Found the current class MyClass in a super class|);
  }
  {
    my $source = [
      'class MyClass extends MyClass2 { has x : int; }',
      'class MyClass2 { has x : int; }',
    ];
    compile_ok($source);
  }
  {
    my $source = [
      'class MyClass extends MyClass2 { has x : long; }',
      'class MyClass2 { has x : int; }',
    ];
    compile_not_ok($source, 'x field cannot be defined in MyClass class. This field is already defined with a different type in the super class.');
  }
  {
    my $source = [
      'class MyClass extends MyClass2 { has x : int; }',
      'class MyClass2 extends MyClass3 {  }',
      'class MyClass3 { has x : int; }',
    ];
    compile_ok($source);
  }
  {
    my $source = [
      'class MyClass extends MyClass2 { has x : long; }',
      'class MyClass2 extends MyClass3 {  }',
      'class MyClass3 { has x : int; }',
    ];
    compile_not_ok($source, 'x field cannot be defined in MyClass class. This field is already defined with a different type in the super class.');
  }
  {
    my $source = [
      'class MyClass extends MyClass2 { method x : int ($args : int) {} }',
      'class MyClass2 { method x : int () {} }',
    ];
    compile_not_ok($source, qr|The length of the arguments of MyClass2#x method must be greater than or equal to the length of the required arguments of MyClass#x method.|);
  }
  {
    my $source = [
      'class MyClass extends MyClass2 { method x : int ($args : int) {} }',
      'class MyClass2 extends MyClass3 { }',
      'class MyClass3 { method x : int () {} }',
    ];
    compile_not_ok($source, qr|The length of the arguments of MyClass3#x method must be greater than or equal to the length of the required arguments of MyClass#x method.|);
  }
  {
    my $source = [
      'class MyClass extends MyClass2 { static method new : MyClass ($args : int) {} }',
      'class MyClass2 { static method new : MyClass2 ($args : long) {} }',
    ];
    compile_ok($source);
  }
  {
    my $source = [
      'class MyClass extends MyClass2 { method x : int ($args : int) { die "Not Implemented"; } }',
      'class MyClass2 { method x : int ($args : int) { return 1;} }',
    ];
    compile_ok($source);
  }
}

# Defined-or
{
  {
    my $source = 'class MyClass  { static method main : void () { 1 // 2; } }';
    compile_not_ok($source, qr|The left operand type of defined-or operator // must be an object type.|);
  }
  
  {
    my $source = 'class MyClass  { static method main : void () { 1 // "false"; } }';
    compile_not_ok($source);
  }
}

# Ternary operator
{
  {
    my $source = 'class MyClass  { static method main : void () { 0 ? (double)1.5 : 1; } }';
    compile_not_ok($source, qr|The types of the left and right operands of ternary operator must be the same type.|);
  }
  
}

# enable_options
{
  {
    my $source = 'class MyClass  { static method main : void () { my $num = 1; enable_options $num; } }';
    compile_not_ok($source, qr|The operand type of enable_options operator must be an object type.|);
  }
}

# disable_options
{
  {
    my $source = 'class MyClass  { static method main : void () { my $num = 1; disable_options $num; } }';
    compile_not_ok($source, qr|The operand type of disable_options operator must be an object type.|);
  }
}

# is_options
{
  {
    my $source = 'class MyClass  { static method main : void () { my $num = 1; is_options $num; } }';
    compile_not_ok($source, qr|The operand type of is_options operator must be an object type.|);
  }
}

# Variable length arguments - object...
{
  {
    my $source = 'class MyClass  { static method main : void () { &varargs("abc", 1); } static method varargs : void ($args : object...) { } }';
    compile_ok($source);
  }
  
  {
    my $source = 'class MyClass  { static method main : void () { &varargs(1, "abc", 1); } static method varargs : void ($arg1 : int, $args : object...) { } }';
    compile_ok($source);
  }
  
  {
    my $source = 'class MyClass  { static method main : void () { (new MyClass)->varargs("abc", 1); } method varargs : void ($args : object...) { } }';
    compile_ok($source);
  }
  
  {
    my $source = 'class MyClass  { static method main : void () { &varargs(1, "abc", 1); } static method varargs : void ($args : string...) { } }';
    compile_not_ok($source, q|The use of variable length arguments is restricted to object[] type.|);
  }
  
  {
    my $source = 'class MyClass  { static method main : void () { &varargs("abc", 1); } static method varargs : void ($args : object..., $arg2 : int) { } }';
    compile_not_ok($source, q|The use of variable length arguments must be the last argument.|);
  }
  
  {
    my $source = 'class MyClass  { static method main : void () { &varargs("abc", 1); } static method varargs : void ($args : object... = undef) { } }';
    compile_not_ok($source, q|The use of variable length arguments cannot have a default value.|);
  }
  
}


# Extra
{
  {
    my $source = [
      'class MyClass { use Point; static method main : int () { my $point = Point->new; warn "AAA " . type_name $point . " " . $point can splitpath; } }',
    ];
    compile_not_ok($source, 'The right operand type of . operator must be string type or byte[] type');
  }
  
  {
  
    my $source = <<'EOS';
class MyClass { 
  static method main : int () { 
    my $array = 1;
    for my $element (@$array) {
      
    }
  }
  
  
}
EOS
    
    compile_not_ok($source, q|line 4|);
  }
  
  {
    my $source = [
      'class MyClass { use Point; static method main : int () { 1 && my $x = 3; } }',
    ];
    compile_not_ok($source, q|The left operand of assignment operator must be mutable|);
  }
  
  {
    my $source = [
      'class MyClass { use Point; static method main : int () { 1 && (my $x = 3); } }',
    ];
    compile_ok($source);
  }
  
  {
    my $class_name_x = 'X' x 200;
    my $class_name_y = 'Y' x 200;
    my $source = [
      qq|class $class_name_x { use $class_name_y; static method main : int () { my \$foo : $class_name_y = new $class_name_x; } }|,
      qq|class $class_name_y { }|,
    ];
    compile_not_ok($source, 'XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX type cannot be assigned to YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY type in assignment operator.');
  }
  
  {
    my $source = [
      'class MyClass { static method main : int () { my $options = new object[0]; [(object)$options]; }  }',
    ];
    compile_ok($source);
  }
  
  # https://github.com/yuki-kimoto/SPVM/issues/603
  {
    my $class_name_x = 'X' x 200;
    my $class_name_y = 'Y' x 200;
    my $source = [
      qq|class $class_name_x { interface $class_name_y; method foo : object () {} }|,
      qq|class $class_name_y : interface_t { required method foo : $class_name_x  (); }|,
    ];
    compile_not_ok($source, q|The return type(object type) of XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX#foo method must be able to be assigned to the return type(XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX type) of YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY#foo method.|);
  }
  
  {
    my $source = [
      'class MyClass { use MyClass2; static method main : int () { method : void () { MyClass2->foo; }; } }',
      'class MyClass2 { allow MyClass; private static method foo : void () {} }',
    ];
    compile_ok($source);
  }
  
}
done_testing;

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
  # allow - Hash::Entry class uses the allow statement
  use SPVM 'Hash';
}

# Compilation Errors in spvm_ast_checker.c 

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

# type_name
{
  {
    my $source = 'class MyClass { static method main : void () { my $num = 0; type_name $num; } }';
    compile_not_ok($source, qr'The operand of the type_name operator must be an object type');
  }
}

# dump
{
  {
    my $source = 'class MyClass { static method main : void () { my $num = 0; dump $num; } }';
    compile_not_ok($source, qr'The operand of the dump operator must be an object type');
  }
}

# new_string_len
{
  {
    my $source = 'class MyClass { static method main : void () { new_string_len 1L; } }';
    compile_not_ok($source, qr|The operand of the new_string_len operator must be an integer type within int|);
  }
}

# class_id
{
  {
    my $source = 'class MyClass { static method main : void () { class_id NotExists; } }';
    compile_not_ok($source, qr'The operand of the class_id operator must be an existing class type. The "NotExists" class is not found');
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
    compile_not_ok($source, q|The condition of the switch statement must be an integer type within int|);
  }
  {
    my $source = 'class MyClass { static method main : void () { switch (1) { case Int->new(1): { } } } }';
    compile_not_ok($source, q|The operand of the case statement must be an integer literal of the int type, a character litaral, or an enumeration value|);
  }
  {
    my $source = 'class MyClass { static method main : void () { switch (1) { case "foo": { } } } }';
    compile_not_ok($source, q|The operand of the case statement must be an integer literal of the int type, a character litaral, or an enumeration value|);
  }
  {
    my $source = 'class MyClass { static method main : void () { switch (1) { case 1: { } case 1: { } } } }';
    compile_not_ok($source, q|The value of the case statement cannnot be duplicated|);
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
    compile_not_ok($source, qr'The operand of the bool type conversion must be a numeric type or an object type or the reference type or the undef type');
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
    compile_not_ok($source, qr'The right operand of the == operator must be an object type');
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 == undef; } }';
    compile_not_ok($source, qr'The left operand of the == operator must be an object type');
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 == Int->new(1); } }';
    compile_not_ok($source, qr'The left and right operands of the == operator must be numeric types or object types or reference types');
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
    compile_not_ok($source, qr'The left and right operands of the != operator must be numeric types or object types or reference types');
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
    my $source = 'class MyClass { static method main : void () { [has foo : int = $foo] method : void () { }; } }';
    compile_not_ok($source, 'The variable "$foo" is not found');
  }
}

# new
{
  {
    my $source = 'class MyClass { static method main : void () { new int[1L]; } }';
    compile_not_ok($source, q|The array length specified by the new operator must be an integer type within int|);
  }
  {
    my $source = 'class MyClass { static method main : void () { new int; } }';
    compile_not_ok($source, q|The operand of the new operator cannnot be a numeric type|);
  }
  {
    my $source = 'class MyClass { use Stringable; static method main : void () {  new Stringable; } }';
    compile_not_ok($source, q|The operand of the new operator cannnot be an interface type|);
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
    compile_not_ok($source, q|The object of the private "Int" class cannnot be created from the current class "MyClass"|);
  }
}

# ^
{
  {
    my $source = 'class MyClass { static method main : void () { 1d ^ 1; } }';
    compile_not_ok($source, 'The left and right operand of the ^ operator must be an integer type');
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 ^ 1d; } }';
    compile_not_ok($source, 'The left and right operand of the ^ operator must be an integer type');
  }
}

# isa
{
  {
    my $source = 'class MyClass { static method main : void () { 1 isa Int; } }';
    compile_not_ok($source, 'The left operand of the isa operator must be an object type');
  }
}

# is_type
{
  {
    my $source = 'class MyClass { static method main : void () { 1 is_type Int; } }';
    compile_not_ok($source, 'The left operand of the is_type operator must be an object type');
  }
  {
    my $source = 'class MyClass { static method main : void () { Int->new(1) is_type int; } }';
    compile_not_ok($source, 'The right type of the is_type operator must be an object type');
  }
  {
    my $source = 'class MyClass { static method main : void () { Int->new(1) is_type object; } }';
    compile_not_ok($source, q|The right type of the is_type operator cannnot be the any object type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { Int->new(1) is_type object[]; } }';
    compile_not_ok($source, q|The right type of the is_type operator cannnot be the any object array type|);
  }
  {
    my $source = 'class MyClass { use Stringable; static method main : void () { Int->new(1) is_type Stringable; } }';
    compile_not_ok($source, q|The right type of the is_type operator cannnot be an interface type|);
  }
}

# @ - Array Length
{
  {
    my $source = 'class MyClass { static method main : void () { @1; } }';
    compile_not_ok($source, 'The right operand of the @ operator must be an array type');
  }
}

# length
{
  {
    my $source = 'class MyClass { static method main : void () { length new int[3]; } }';
    compile_not_ok($source, 'The operand of the length operator must be the string type');
  }
}

# ++,-- Increment, Decrement
{
  {
    my $source = 'class MyClass { static method main : void () { my $var = "foo"; $var++; } }';
    compile_not_ok($source, 'The operand of the increment operator must be a numeric type');
  }
  {
    my $source = 'class MyClass { static method main : void () { my $var = "foo"; ++$var; } }';
    compile_not_ok($source, 'The operand of the increment operator must be a numeric type');
  }
  {
    my $source = 'class MyClass { static method main : void () { my $var = "foo"; $var--; } }';
    compile_not_ok($source, 'The operand of the decrement operator must be a numeric type');
  }
  {
    my $source = 'class MyClass { static method main : void () { my $var = "foo"; --$var; } }';
    compile_not_ok($source, 'The operand of the decrement operator must be a numeric type');
  }
  
}

# = Assignment
{
  {
    my $source = 'class MyClass { static method main : void () { my $var = undef; } }';
    compile_not_ok($source, q|The type of "$var" cannnot be detected|);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $var : byte = "string"; } }';
    compile_not_ok($source, q|The implicite type conversion from "string" to "byte" in the assignment operator is not allowed|);
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
    compile_not_ok($source, q|The void method cannnot return the value|);
  }
  {
    my $source = 'class MyClass { static method main : int () { return; } }';
    compile_not_ok($source, q|The non-void method must return a value|);
  }
}

# + Unary Plus
{
  {
    my $source = 'class MyClass { static method main : void () { +"foo"; } }';
    compile_not_ok($source, q|The operand of the unary + operator must be a numeric type|);
  }
}

# - Unary Minus
{
  {
    my $source = 'class MyClass { static method main : void () { -"foo"; } }';
    compile_not_ok($source, q|The operand of the unary - operator must be a numeric type|);
  }
}

# copy
{
  {
    my $source = 'class MyClass { static method main : void () { copy 1; } }';
    compile_not_ok($source, q|The operand of the copy operator must be an object type|);
  }
}

# ~ Bit Not
{
  {
    my $source = 'class MyClass { static method main : void () { ~ 1d; } }';
    compile_not_ok($source, q|The operand of the ~ operator must be an integer type|);
  }
}

# + Addition
{
  {
    my $source = 'class MyClass { static method main : void () { "foo" + 1; } }';
    compile_not_ok($source, q|The left operand of the + operator must be a numeric type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 + "foo"; } }';
    compile_not_ok($source, q|The right operand of the + operator must be a numeric type|);
  }
}

# - Subtract
{
  {
    my $source = 'class MyClass { static method main : void () { "foo" - 1; } }';
    compile_not_ok($source, q|The left operand of the - operator must be a numeric type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 - "foo"; } }';
    compile_not_ok($source, q|The right operand of the - operator must be a numeric type|);
  }
}

# * Multiplication
{
  {
    my $source = 'class MyClass { static method main : void () { "foo" * 1; } }';
    compile_not_ok($source, q|The left operand of the * operator must be a numeric type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 * "foo"; } }';
    compile_not_ok($source, q|The right operand of the * operator must be a numeric type|);
  }
}

# / Division
{
  {
    my $source = 'class MyClass { static method main : void () { "foo" / 1; } }';
    compile_not_ok($source, q|The left operand of the / operator must be a numeric type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 / "foo"; } }';
    compile_not_ok($source, q|The right operand of the / operator must be a numeric type|);
  }
}

# divui
{
  {
    my $source = 'class MyClass { static method main : void () { 1L divui 1; } }';
    compile_not_ok($source, q|The left operand of the divui operator must be the int type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 divui 1L; } }';
    compile_not_ok($source, q|The right operand of the divui operator must be the int type|);
  }
}

# divul
{
  {
    my $source = 'class MyClass { static method main : void () { 1 divul 1L; } }';
    compile_not_ok($source, q|The left operand of the divul operator must be the long type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1L divul 1; } }';
    compile_not_ok($source, q|The right operand of the divul operator must be the long type|);
  }
}

# % Division
{
  {
    my $source = 'class MyClass { static method main : void () { "foo" % 1; } }';
    compile_not_ok($source, q|The left operand of the % operator must be an integer type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 % "foo"; } }';
    compile_not_ok($source, q|The right operand of the % operator must be an integer type|);
  }
}

# remui
{
  {
    my $source = 'class MyClass { static method main : void () { 1L remui 1; } }';
    compile_not_ok($source, q|The left operand of the remui operator must be the int type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 remui 1L; } }';
    compile_not_ok($source, q|The right operand of the remui operator must be the int type|);
  }
}

# remul
{
  {
    my $source = 'class MyClass { static method main : void () { 1 remul 1L; } }';
    compile_not_ok($source, q|The left operand of the remul operator must be the long type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1L remul 1; } }';
    compile_not_ok($source, q|The right operand of the remul operator must be the long type|);
  }
}

# & Division
{
  {
    my $source = 'class MyClass { static method main : void () { "foo" & 1; } }';
    compile_not_ok($source, q|The left operand of the & operator must be an integer type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 & "foo"; } }';
    compile_not_ok($source, q|The right operand of the & operator must be an integer type|);
  }
}

# | Division
{
  {
    my $source = 'class MyClass { static method main : void () { "foo" | 1; } }';
    compile_not_ok($source, q|The left operand of the \| operator must be an integer type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 | "foo"; } }';
    compile_not_ok($source, q|The right operand of the \| operator must be an integer type|);
  }
}

# << Left Shift
{
  {
    my $source = 'class MyClass { static method main : void () { "foo" << 1; } }';
    compile_not_ok($source, q|The left operand of the << operator must be an integer type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 << 1d; } }';
    compile_not_ok($source, q|The right operand of the << operator must be the int type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 << 1L; } }';
    compile_not_ok($source, q|The right operand of the << operator must be the int type|);
  }
}

# >> Right Arithmetic Shift
{
  {
    my $source = 'class MyClass { static method main : void () { "foo" >> 1; } }';
    compile_not_ok($source, q|The left operand of the >> operator must be an integer type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 >> 1d; } }';
    compile_not_ok($source, q|The right operand of the >> operator must be the int type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 >> 1L; } }';
    compile_not_ok($source, q|The right operand of the >> operator must be the int type|);
  }
}

# >>> Right Logical Shift
{
  {
    my $source = 'class MyClass { static method main : void () { "foo" >>> 1; } }';
    compile_not_ok($source, q|The left operand of the >>> operator must be an integer type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 >>> 1d; } }';
    compile_not_ok($source, q|The right operand of the >>> operator must be the int type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 >>> 1L; } }';
    compile_not_ok($source, q|The right operand of the >>> operator must be the int type|);
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
    compile_not_ok($source, q|The implicite type conversion from "Int" to "string" in the assignment operator is not allowed|);
  }

  {
    my $source = 'class MyClass { static method main : void () { die Error "Foo"; } }';
    compile_ok($source);
  }
  
  {
    my $source = 'class MyClass { static method main : void () { die Error; } }';
    compile_ok($source);
  }
}

# warn
{
  {
    my $source = 'class MyClass { static method main : void () { warn; } }';
    compile_ok($source);
  }
  
  {
    my $source = 'class MyClass { static method main : void () { warn Int->new(1); } }';
    compile_not_ok($source, q|The operand of the warn operator must be the string type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { warn undef; } }';
    compile_ok($source);
  }
}

# print
{
  {
    my $source = 'class MyClass { static method main : void () { print Int->new(1); } }';
    compile_not_ok($source, q|The operand of the print operator must be the string type|);
  }
}

# make_read_only
{
  {
    my $source = 'class MyClass { static method main : void () { make_read_only 1; } }';
    compile_not_ok($source, q|The operand of the make_read_only operator must be the string type|);
  }
}

# is_read_only
{
  {
    my $source = 'class MyClass { static method main : void () { is_read_only 1; } }';
    compile_not_ok($source, q|The operand of the is_read_only operator must be the string type|);
  }
}

# Reference
{
  {
    my $source = 'class MyClass { static method main : void () { my $var = "foo"; \$var; } }';
    compile_not_ok($source, q|The operand of the refernece operator must be a numeric type or a multi-numeric type|);
  }
}

# Dereference
{
  {
    my $source = 'class MyClass { static method main : void () { my $var = "foo"; $$var; } }';
    compile_not_ok($source, q|The operand of the dereference operaotr must be a numeric reference type or a multi-numeric reference type|);
  }
}

# Variable
{
  {
    my $source = 'class MyClass { static method main : void () { my $var = 0; my $var = 0; } }';
    compile_not_ok($source, q|Redeclaration of the variable "$var"|);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $var; } }';
    compile_not_ok($source, q|The type of the variable "$var" must be defined|);
  }
  {
    my $source = 'class MyClass { static method main : void () { $var; } }';
    compile_not_ok($source, q|The variable "$var" is not found|);
  }
  {
    my $source = 'class MyClass { static method main : void () { $MyClass::FOO; } }';
    compile_not_ok($source, q|The variable "$MyClass::FOO" is not found|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 && (my $var = 0); } }';
    compile_ok($source);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $var = 0; 1 && (my $var = 0); } }';
    compile_not_ok($source, q|Redeclaration of the variable "$var"|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 || (my $var = 0); } }';
    compile_ok($source);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $var = 0; 1 || (my $var = 0); } }';
    compile_not_ok($source, q|Redeclaration of the variable "$var"|);
  }
  {
    my $source = 'class MyClass { static method main : void () { !(my $var = 0); } }';
    compile_ok($source);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $var = 0; !(my $var = 0); } }';
    compile_not_ok($source, q|Redeclaration of the variable "$var"|);
  }
}

# Method Call
{
  {
    my $source = [
      'class MyClass { use MyClass2; static method main : void () { MyClass2->foo();  } }',
      'class MyClass2 { static private method foo : void () {} }'
    ];
    compile_not_ok($source, q|The private "foo" method of the "MyClass2" class cannnot be called from the current class "MyClass"|);
  }
  {
    my $source = 'class MyClass { static method main : void () { &foo(); } static method foo : void ($arg0 : int, $arg1 : int = 0) { } }';
    compile_not_ok($source, q|Too few arguments are passed to the "foo" method in the "MyClass" class|);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $object = new MyClass; $object->foo(); } method foo : void ($arg0 : int, $arg1 : int = 0) { } }';
    compile_not_ok($source, q|Too few arguments are passed to the "foo" method in the "MyClass" class|);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $object = new MyClass; $object->foo(1, 2, 3); } method foo : void ($arg0 : int, $arg1 : int = 0) { } }';
    compile_not_ok($source, q|Too many arguments are passed to the "foo" method in the "MyClass" class|);
  }
}

# Class Variable Access
{
  {
    my $source = [
      'class MyClass { use MyClass2; static method main : void () { $MyClass2::FOO;  } }',
      'class MyClass2 { our $FOO : private int; }'
    ];
    compile_not_ok($source, q|The private "$FOO" class variable of the "MyClass2" class cannnot be accessed from the current class "MyClass"|);
  }
}

# Array Access
{
  {
    my $source = 'class MyClass { static method main : void () { my $var = 1; $var->[0]; } }';
    compile_not_ok($source, q|The invocant of the array access must be an array type or the string type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $var = new int[1]; $var->[1L]; } }';
    compile_not_ok($source, q|The index of the array access must be the int type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $var = new int[1]; $var->["foo"]; } }';
    compile_not_ok($source, q|The index of the array access must be the int type|);
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
    compile_not_ok($source, q|The "foo" field is not found in the "MyClass" class or its super classes|);
  }
  {
    my $source = 'class MyClass { has x : int; static method main : void () { my $object = new MyClass; weaken $object->{x}; } }';
    compile_not_ok($source, q|The "x" field in the "MyClass" class operated by the weaken operator must be an object type|);
  }
  {
    my $source = 'class MyClass { has x : int; static method main : void () { my $object = new MyClass; unweaken $object->{x}; } }';
    compile_not_ok($source, q|The "x" field in the "MyClass" class operated by the unweaken operator must be an object type|);
  }
  {
    my $source = 'class MyClass { has x : int; static method main : void () { my $object = new MyClass; isweak $object->{x}; } }';
    compile_not_ok($source, q|The "x" field in the "MyClass" class operated by the isweak operator must be an object type|);
  }
  {
    my $source = [
      'class MyClass { use MyClass2; static method main : void () { my $object = new MyClass2; $object->{x};  } }',
      'class MyClass2 : public { has x : private int; }'
    ];
    compile_not_ok($source, q|The private "x" field in the "MyClass2" class cannnot be accessed from the current class "MyClass"|);
  }
  {
    my $source = [
      'class MyClass { use MyClass2; static method main : void () { my $object = new MyClass2; $object->{x};  } }',
      'class MyClass2 : public { has x : protected int; }'
    ];
    compile_not_ok($source, q|The protected "x" field in the "MyClass2" class cannnot be accessed from the current class "MyClass"|);
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
    compile_not_ok($source, q|he invocant of the can operator must be a class type or an interface type|);
  }
  {
    my $source = 'class MyClass { use Point; static method main : void () { my $point = Point->new; $point can not_defined; } }';
    compile_not_ok($source, q|The "not_defined" method in the "Point" class checked by the can operator must be defined|);
  }
  {
    my $source = 'class MyClass { use Point; static method main : void () { my $anon = method : void () {}; $anon can "a"; } }';
    compile_not_ok($source, qr|If the right operand of the can operator is a constant value, it must be an empty string ""|);
  }
}

# Type Case
{
  {
    my $source = 'class MyClass { static method main : void () { (Int)"foo"; } }';
    compile_not_ok($source, q|The type cast from "string" to "Int" is not allowed|);
  }
}

# Assignability
{
  {
    my $source = q|class MyClass { static method main : void () { my $ret = &main(); } }|;
    compile_not_ok($source, q|The void type cannnot be assigned in the assignment operator|);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $string : mutable string = "abc"; } }';
    compile_not_ok($source, q|The implicite type conversion from "string" to "mutable string" in the assignment operator is not allowed|);
  }
  {
    my $source = 'class MyClass { static method main : mutable string () { return "abc"; } }';
    compile_not_ok($source, q|The implicite type conversion from "string" to "mutable string" in the return statement is not allowed|);
  }
  {
    my $source = 'class MyClass { static method main : void () { &foo("abc"); } static method foo : int ($string : mutable string) { }}';
    compile_not_ok($source, q|The implicite type conversion from "string" to "mutable string" in the 1th argument of the "foo" method in the "MyClass" class is not allowed|);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $object = new MyClass; $object->foo("abc"); } method foo : int ($string : mutable string) { }}';
    compile_not_ok($source, q|The implicite type conversion from "string" to "mutable string" in the 1th argument of the "foo" method in the "MyClass" class is not allowed|);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $var : int = "foo"; } }';
    compile_not_ok($source, q|The implicite type conversion from "string" to "int" in the assignment operator is not allowed|);
  }
}

# Resove types
{
  {
    my $source = 'class MyClass { static method main : void () { new NotFound; } }';
    compile_not_ok($source, q|The "NotFound" class is not yet loaded|);
  }
  {
    my $source = 'class MyClass { static method main : void ($arg : Int*) {} }';
    compile_not_ok($source, q|The reference type must be a numeric refernce type or a multi-numeric reference type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $var : mutable int;} }';
    compile_not_ok($source, q|The type qualifier "mutable" is only allowed in the string type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $var : object[][];} }';
    compile_not_ok($source, q|The multi dimensional array of any object is not allowed|);
  }
}

# Resove method call
{
  {
    my $source = 'class MyClass { static method main : void () { MyClass->not_defined; } }';
    compile_not_ok($source, q|The "not_defined" method in the "MyClass" class is not found|);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $var = Int->new(1); $var->not_defined; } }';
    compile_not_ok($source, q|The "not_defined" method is not found in the "Int" class or its super classes|);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $var = 1; $var->new; } }';
    compile_not_ok($source, q|The invocant of the "new" method must be a class type or an interface type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $point = Point->new; } }';
    compile_not_ok($source, q|The "Point" class is not yet loaded|);
  }
  {
    my $source = 'class MyClass { use Point; static method main : void () { my $point = Point->not_defined; } }';
    compile_not_ok($source, q|The "not_defined" method in the "Point" class is not found|);
  }
  {
    my $source = 'class MyClass { use Point; static method main : void () { my $point = Point->new; $point->Point::not_found; } }';
    compile_not_ok($source, q|The "Point::not_found" method is not found|);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $var = Int->new(1); $var->new; } }';
    compile_not_ok($source, q|The "new" method in the "Int" class is found, but this is not an instance method|);
  }
  {
    my $source = [
      'class MyClass { use MyClass2; static method main : void () { my $object = new MyClass2; $object->foo; } }',
      'class MyClass2 extends MyClass : public { static method foo : void () {} }',
    ];
    compile_not_ok($source, q|The "foo" method in the "MyClass2" class is found, but this is not an instance method|);
  }
  {
    my $source = 'class MyClass { use Stringable; use Point3D; static method main : void () { my $stringable = (Stringable)Point3D->new; $stringable->SUPER::clear; } }';
    compile_not_ok($source, q|The "SUPER::clear" method is not found|);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $var = Int->new(1); $var->not_defined; } }';
    compile_not_ok($source, q|The "not_defined" method is not found in the "Int" class or its super classes|);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $var = Int->new(1); $var->not_defined; } }';
    compile_not_ok($source, q|The "not_defined" method is not found in the "Int" class or its super classes|);
  }
  {
    my $source = [
      'class MyClass { use MySockaddrIn; static method main : void () { my $result_address = new MySockaddrIn; $result_address->port;} }',
      'class MySockaddrIn extends MySockaddr : public;',
      'class MySockaddr : public;',
    ];
    compile_not_ok($source, q|The "port" method is not found in the "MySockaddrIn" class or its super classes|);
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
    compile_not_ok($source, q|The type name for the int multi-numeric with the field length of 2 must end with "_2i"|);
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
    compile_not_ok($source, q|The default value of the optional argument "$arg1" must be a constant value|);
  }
  {
    my $source = 'class MyClass {  static method main : void ($arg1 : byte = 1000) { } }';
    compile_not_ok($source, q|The default value of the optional argument "$arg1" must be able to be assigned to the argument|);
  }
  {
    my $source = 'class MyClass { use Complex_2d; static method main : void ($arg1 : Complex_2d = 0) { } }';
    compile_not_ok($source, q|The types other than the numeric type and the object type cannnot be used in the optional argument|);
  }
  {
    my $source = 'class MyClass { use Complex_2d; static method main : void ($arg1 : int* = 0) { } }';
    compile_not_ok($source, q|The types other than the numeric type and the object type cannnot be used in the optional argument|);
  }
  {
    my $source = 'class MyClass { use Complex_2d; static method main : void ($arg1 : int* = 0) { } }';
    compile_not_ok($source, q|The types other than the numeric type and the object type cannnot be used in the optional argument|);
  }
  {
    my $source = 'class MyClass { use Complex_2d; static method main : void ($arg1 : int = 0, $arg2 : int) { } }';
    compile_not_ok($source, q|Arguments after optional arguments must be optional arguments|);
  }
  compile_not_ok_file('CompileError::Method::TooManyArguments', qr/The stack length of arguments must be less than or equal to 255/);
  compile_not_ok_file('CompileError::Method::TooManyArgumentsMulnum', qr/The stack length of arguments must be less than or equal to 255/);
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
}

# interface Statement
{
  {
    my $source = 'class MyClass  { interface Point; }';
    compile_not_ok($source, q|The interface specified by the interface statement must be an interface type|);
  }
  {
    my $source = 'class MyClass  { interface Stringable; }';
    compile_not_ok($source, q|The "MyClass" class must have the "to_string" method that is defined as a required method in the "Stringable" interface|);
  }
  {
    my $source = 'class MyClass  { interface Stringable; method to_string : string ($arg : int) {} }';
    compile_not_ok($source, q|The length of the required arguments of the "to_string" method in the "MyClass" class must be equal to the length of the required arguments of the "to_string" method in the "Stringable" interface|);
  }
  {
    my $source = 'class MyClass  { interface Stringable; static method to_string : string ($self : Stringable) {} }';
    compile_not_ok($source, q|The "to_string" method in the "MyClass" class must an instance method because the "to_string" method is defined as an instance method in the "Stringable" interface|);
  }
  {
    my $source = [
      'class MyClass { interface MyInterface; method foo : void ($arg1 : int, $arg2 : long) {} }',
      'class MyInterface : interface_t { required method foo : void ($arg1 : int, $arg2 : int); }',
    ];
    compile_not_ok($source, q|The type of the 2th argument of the "foo" method in the "MyClass" class must be equal to the type of the 2th argument of the "foo" method in the "MyInterface" interface|);
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
    compile_not_ok($source, q|The return type of the "foo" method in the "MyClass" class must be able to be assigned to the return type of the "foo" method in the "MyInterface" interface|);
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
    compile_not_ok($source, q|The return type of the "foo" method in the "MyClass" class must be able to be assigned to the return type of the "foo" method in the "MyInterface" interface|);
  }

  {
    my $source = [
      'class MyClass { use Point; use Point3D; interface MyInterface; method foo : int () {} }',
      'class MyInterface : interface_t { required method foo : long  (); }',
    ];
    compile_not_ok($source, q|The return type of the "foo" method in the "MyClass" class must be able to be assigned without an implicite type conversion to the return type of the "foo" method in the "MyInterface" interface|);
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
      compile_not_ok($source, qr|The length of the required arguments of the "foo" method in the "MyClass" class must be equal to the length of the required arguments of the "foo" method in the "MyClass::Interface" interface|);
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
      compile_not_ok($source, qr|The length of the arguments of the "foo" method in the "MyClass" class must be greather than or equal to the length of the arguments of the "foo" method in the "MyClass::Interface|);
    }
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
    compile_not_ok($source, q|Recursive inheritance. Found the current class "MyClass" in a super class|);
  }
  {
    my $source = [
      'class MyClass extends MyClass2 { has x : int; }',
      'class MyClass2 { has x : int; }',
    ];
    compile_not_ok($source, qr|The field in the "MyClass" class with the same name as the "x" field in the parent class cannot be defined|);
  }
  {
    my $source = [
      'class MyClass extends MyClass2 { has x : int; }',
      'class MyClass2 extends MyClass3 {  }',
      'class MyClass3 { has x : int; }',
    ];
    compile_not_ok($source, qr|The field in the "MyClass" class with the same name as the "x" field in the parent class cannot be defined|);
  }
  {
    my $source = [
      'class MyClass extends MyClass2 { method x : int ($args : int) {} }',
      'class MyClass2 { method x : int () {} }',
    ];
    compile_not_ok($source, qr|The length of the required arguments of the "x" method in the "MyClass" class must be equal to the length of the required arguments of the "x" method in the "MyClass2" class|);
  }
  {
    my $source = [
      'class MyClass extends MyClass2 { method x : int ($args : int) {} }',
      'class MyClass2 extends MyClass3 { }',
      'class MyClass3 { method x : int () {} }',
    ];
    compile_not_ok($source, qr|The length of the required arguments of the "x" method in the "MyClass" class must be equal to the length of the required arguments of the "x" method in the "MyClass3" class|);
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

# Extra
{
   {
    my $source = [
      'class MyClass { use Point; static method main : int () { my $point = Point->new; warn "AAA " . type_name $point . " " . $point can splitpath; } }',
    ];
    compile_not_ok($source, 'The right operand of the . operator must be the string type or the byte[] type');
  }
}
done_testing;

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

# Compilation Errors in spvm_toke.c 

# Line number
{
  compile_not_ok_file('CompileError::Syntax::LineNumber', qr/our.*\b8:3\b/is);
}

# Exception Message Format
{
  {
    my $source = 'class myclass;';
    compile_not_ok($source, qr|\.\n  at .+ line |s);
  }
}

# Class Name
{
  {
    my $source = 'class myclass;';
    compile_not_ok($source, qr|The class name "myclass" must begin with an upper case character|);
  }
  {
    my $source = 'class Myclass::foo;';
    compile_not_ok($source, qr|The part names of the "Myclass::foo" class must begin with an upper case character|);
  }
  {
    my $source = 'class Myclass::Foo::bar;';
    compile_not_ok($source, qr|The part names of the "Myclass::Foo::bar" class must begin with an upper case character|);
  }
  {
    my $source = 'class Myclass__Foo;';
    compile_not_ok($source, qr|The class name "Myclass__Foo" cannnot constain "__"|);
  }
  {
    my $source = 'class Myclass::;';
    compile_not_ok($source, qr|The class name "Myclass::" cannnot end with "::"|);
  }
  {
    my $source = 'class MyClass::::Foo;';
    compile_not_ok($source, qr|The class name "MyClass::::Foo" cannnot contains "::::"|);
  }
  {
    my $source = 'class ::MyClass;';
    compile_not_ok($source, qr|The class name "::MyClass" cannnot begin with "::"|);
  }
  {
    my $source = 'class 6MyClass;';
    compile_not_ok($source, qr|The class name "6MyClass" cannnot begin with a number|);
  }
}

# Loading Class
{
  {
    my $source = 'class MyClass { use NotFoundClass; }';
    compile_not_ok($source, qr|\QFailed to load the "NotFoundClass" class. The class file "NotFoundClass.spvm" is not found|);
  }
}

# Literal
{
  # Caharater literal
  {
    {
      my $source = q|class MyClass { static method main : void () { ''; } }|;
      compile_not_ok($source, qr/The character literal cannnot be empty/);
    }
    {
      my $source = q|class MyClass { static method main : void () { '\xG'; } }|;
      compile_not_ok($source, qr/\QOne or tow hexadecimal numbers must be followed by "\x" of the hexadecimal escape character/);
    }
    {
      my $source = q|class MyClass { static method main : void () { '\xg'; } }|;
      compile_not_ok($source, qr/\QOne or tow hexadecimal numbers must be followed by "\x" of the hexadecimal escape character/);
    }
    {
      my $source = q|class MyClass { static method main : void () { '\x{a'; } }|;
      compile_not_ok($source, qr/The hexadecimal escape character is not closed by "}"/);
    }
    {
      my $source = q|class MyClass { static method main : void () { '\A'; } }|;
      compile_not_ok($source, qr/\Q"\A" is the invalid charater literal escape character/);
    }
    {
      my $source = q|class MyClass { static method main : void () { '\xa; } }|;
      compile_not_ok($source, qr/The character literal must ends with "'"/);
    }

    # Syntax
    {
      compile_not_ok_file('CompileError::Class::NotClosed');
      {
        my $source = 'class MyClass { static method main : void () {} } class MyClass2 { static method main : void () {} }';
        compile_not_ok($source, qr/Unexpected token "class"/);
      }
    }
    
    # Extra
    {
      compile_not_ok_file('CompileError::Literal::Character::InvalidCharacterLiteralEmpty');
      compile_not_ok_file('CompileError::Literal::Character::InvalidCharacterLiteral');
      compile_not_ok_file('CompileError::Literal::Character::NotEnd');
      compile_not_ok_file('CompileError::Literal::Character::InvalidHexAscii1');
      compile_not_ok_file('CompileError::Literal::Character::InvalidHexAscii2');
    }
  }
  
  # Octal Caharater literal
  {
    {
      my $source = q|class MyClass { static method main : void () { '\o{}'; } }|;
      compile_not_ok($source, qr|At least one octal number must be followed by "\\o\{" of the octal escape character|);
    }
    {
      my $source = q|class MyClass { static method main : void () { '\o{400}'; } }|;
      compile_not_ok($source, qr|The maxmum number of the octal escape charcater is 377|);
    }
    {
      my $source = q|class MyClass { static method main : void () { '\o{1111}'; } }|;
      compile_not_ok($source, qr|The octal escape character is not closed by "}"|);
    }
  }
  
  # String literal
  {
    {
      my $source = q|class Tmp { static method main : void () { "Foo \xg Bar" } }|;
      compile_not_ok($source, qr/\QOne or tow hexadecimal numbers must be followed by "\x" of the hexadecimal escape character/);
    }
    {
      my $source = q|class Tmp { static method main : void () { "Foo \x{a Bar" } }|;
      compile_not_ok($source, qr/The hexadecimal escape character is not closed by "}"/);
    }
    {
      my $source = q|class Tmp { static method main : void () { "\u" }|;
      compile_not_ok($source, qr/Invalid string literal escape character "\\u"/);
    }
    
    # Unicode escape character
    {
      {
        my $source = q|class Tmp { static method main : void () { "\N{U+}" }|;
        compile_not_ok($source, qr/One or more than one hexadecimal numbers must be followed by "\\N\{U\+" of the Unicode escape character/);
      }
      {
        my $source = q|class Tmp { static method main : void () { "\N{U+FFFFFFFFA}" }|;
        compile_not_ok($source, qr/Too big Unicode escape character/);
      }
      {
        my $source = q|class Tmp { static method main : void () { "\N{U+DFFF}" }|;
        compile_not_ok($source, qr/The code point of Unicode escape character must be a Unicode scalar value/);
      }
      {
        my $source = q|class Tmp { static method main : void () { "\N{U+DFFF}" }|;
        compile_not_ok($source, qr/The code point of Unicode escape character must be a Unicode scalar value/);
      }
      {
        my $source = q|class Tmp { static method main : void () { "\N{U+D800}" }|;
        compile_not_ok($source, qr/The code point of Unicode escape character must be a Unicode scalar value/);
      }
    }
    {
      my $source = q|class Tmp { static method main : void () { " } }|;
      compile_not_ok($source, qr/The string literal must be end with '"'/);
    }
    {
      my $source = q|class Tmp { static method main : void () { "$foo->{foo-" }|;
      compile_not_ok($source, qr/The getting field in a string literal must be closed with "}"/);
    }
    {
      my $source = q|class Tmp { static method main : void () { "$foo->[3-" }|;
      compile_not_ok($source, qr/The getting array element in a string literal must be closed with "]"/);
    }
    {
      my $source = q|class Tmp { static method main : void () { "$foo->bar" }|;
      compile_not_ok($source, qr/\QThe character after "->" in a string literal must be "[" or "{"/);
    }
  }
  # Integer literal
  {
    # Integer literal decimal notation
    {
      compile_not_ok_file('CompileError::Literal::Integer::IntOutOfRange', qr/The numeric literal "8232624535311216194" is out of range of maximum and minimum values of int type/);
      {
        # Greater than int max value
        my $source = 'class Tmp { static method main : void () { 2147483648; } }';
        compile_not_ok($source, qr/The numeric literal "2147483648" is out of range of maximum and minimum values of int type/);
      }
      {
        # Less than int minimal value
        my $source = 'class Tmp { static method main : void () { -2147483649; } }';
        compile_not_ok($source, qr/The numeric literal "-2147483649" is out of range of maximum and minimum values of int type/);
      }
      {
        # Greater than long max value
        my $source = 'class Tmp { static method main : void () { 9223372036854775808L; } }';
        compile_not_ok($source, qr/The numeric literal "9223372036854775808L" is out of range of maximum and minimum values of long type/);
      }
      {
        # Less than long minimal value
        my $source = 'class Tmp { static method main : void () { -9223372036854775809L; } }';
        compile_not_ok($source, qr/The numeric literal "-9223372036854775809L" is out of range of maximum and minimum values of long type/);
      }
      {
        # Invalid "_"
        my $source = 'class Tmp { static method main : void () { _-123; } }';
        compile_not_ok($source, qr/Unexpected token "-123"/);
      }
      {
        # Invalid "_"
        my $source = 'class Tmp { static method main : void () { -_123; } }';
        compile_not_ok($source, qr/Unexpected token ";"/);
      }
      {
        # Invalid "_"
        my $source = 'class Tmp { static method main : void () { 123L_; } }';
        compile_not_ok($source, qr/Unexpected token "_"/);
      }
    }

    # Integer literal hexadecimal notation
    {
      {
        # Greater than int max value
        my $source = 'class Tmp { static method main : void () { 0x100000000; } }';
        compile_not_ok($source, qr/The numeric literal "0x100000000" is out of range of maximum and minimum values of int type/);
      }
      {
        # Greater than long max value
        my $source = 'class Tmp { static method main : void () { 0x10000000000000000L; } }';
        compile_not_ok($source, qr/The numeric literal "0x10000000000000000L" is out of range of maximum and minimum values of long type/);
      }
      {
        # Invalid "_"
        my $source = 'class Tmp { static method main : void () { _-0xFF; } }';
        compile_not_ok($source, qr/Unexpected token "-0xFF"/);
      }
      {
        # Invalid "_"
        my $source = 'class Tmp { static method main : void () { -0_xFF; } }';
        compile_not_ok($source, qr/Unexpected token "xFF"/);
      }
      {
        # Invalid "_"
        my $source = 'class Tmp { static method main : void () { 0xFFL_; } }';
        compile_not_ok($source, qr/Unexpected token "_"/);
      }
    }

    # Integer literal octal notation
    {
      {
        # Greater than int max value
        my $source = 'class Tmp { static method main : void () { 040000000000; } }';
        compile_not_ok($source, qr/The numeric literal "040000000000" is out of range of maximum and minimum values of int type/);
      }
      {
        # Greater than long max value
        my $source = 'class Tmp { static method main : void () { 0x2000000000000000000000L; } }';
        compile_not_ok($source, qr/The numeric literal "0x2000000000000000000000L" is out of range of maximum and minimum values of long type/);
      }
      {
        # Invalid "_"
        my $source = 'class Tmp { static method main : void () { _-077; } }';
        compile_not_ok($source, qr/Unexpected token "-077"/);
      }
      {
        # Invalid "_"
        my $source = 'class Tmp { static method main : void () { 0x77L_; } }';
        compile_not_ok($source, qr/Unexpected token "_"/);
      }
    }

    # Integer literal binary notation
    {
      {
        # Greater than int max value
        my $source = 'class Tmp { static method main : void () { 0b100000000000000000000000000000000; } }';
        compile_not_ok($source, qr/The numeric literal "0b100000000000000000000000000000000" is out of range of maximum and minimum values of int type/);
      }
      {
        # Greater than long max value
        my $source = 'class Tmp { static method main : void () { 0b10000000000000000000000000000000000000000000000000000000000000000L; } }';
        compile_not_ok($source, qr/The numeric literal "0b10000000000000000000000000000000000000000000000000000000000000000L" is out of range of maximum and minimum values of long type/);
      }
      {
        # Invalid "_"
        my $source = 'class Tmp { static method main : void () { _-0b11; } }';
        compile_not_ok($source, qr/Unexpected token "-0b11"/);
      }
      {
        # Invalid "_"
        my $source = 'class Tmp { static method main : void () { -0_b11; } }';
        compile_not_ok($source, qr/Unexpected token "b11"/);
      }
      {
        # Invalid "_"
        my $source = 'class Tmp { static method main : void () { 0b11L_; } }';
        compile_not_ok($source, qr/Unexpected token "_"/);
      }
    }
  }
  
  # Floating point literal
  {
    # Floating point literal decimal notation
    {
      {
        # Invalid "_"
        my $source = 'class Tmp { static method main : void () { _-1.23; } }';
        compile_not_ok($source, qr/Unexpected token "-1.23"/);
      }
      {
        # Invalid "_"
        my $source = 'class Tmp { static method main : void () { -_1.23; } }';
        compile_not_ok($source, qr/Unexpected token "."/);
      }
      {
        # Invalid "_"
        my $source = 'class Tmp { static method main : void () { 1.23f_; } }';
        compile_not_ok($source, qr/Unexpected token "_"/);
      }
    }

    # Floating point literal dexadecimal notation
    {
      {
        # Invalid "_"
        my $source = 'class Tmp { static method main : void () { _-0xFF.FF; } }';
        compile_not_ok($source, qr/Unexpected token "-0xFF.FF"/);
      }
      {
        # Invalid "_"
        my $source = 'class Tmp { static method main : void () { -0_xFF.FF; } }';
        compile_not_ok($source, qr/Unexpected token "xFF"/);
      }
      {
        # Invalid "_"
        my $source = 'class Tmp { static method main : void () { 0xFF.FFp5F_; } }';
        compile_not_ok($source, qr/Unexpected token "_"/);
      }
    }
  }
}

# Symbol Name
{
  # Variable name
  {
    # Local variable name
    {
      {
        my $source = 'class MyClass { static method main : void () { my ${name : int; } }';
        compile_not_ok($source, qr/The variable name is not closed by "}"/);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $Foo::name : int; } }';
        compile_not_ok($source, qr/The local variable "\$Foo::name" cannnot contain "::"/);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $foo__bar : int; } }';
        compile_not_ok($source, qr/The variable name "\$foo__bar" cannnot contain "__"/);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $::foo : int; } }';
        compile_not_ok($source, qr/The variable name "\$::foo" cannnot begin with "\$::"/);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $foo:: : int; } }';
        compile_not_ok($source, qr/The variable name "\$foo::" cannnot end with "::"/);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $foo::::bar : int; } }';
        compile_not_ok($source, qr/The variable name "\$foo::::bar" cannnot contain "::::"/);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $3foo : int; } }';
        compile_not_ok($source, qr/The symbol name part of the variable name "\$3foo" cannnot begin with a number/);
      }
    }
    
    # Extra
    {
      compile_not_ok_file('CompileError::LocalVar::LocalVarNameStartDigit');
      compile_not_ok_file('CompileError::LocalVar::LocalVarNameInvalidColon');
      compile_not_ok_file('CompileError::LocalVar::LocalVarNameEndColon2');
      compile_not_ok_file('CompileError::LocalVar::LocalVarNameColon2Twice');
    }
  }

  # Symbol name
  {
    # A symbol name cannnot conatain "__"
    {
      my $source = 'class MyClass { use Int as Foo__Bar; static method main : void () { } }';
      compile_not_ok($source, qr/\QThe symbol name "Foo__Bar" cannnot constain "__"/);
    }

    # A symbol name cannnot end with "::"
    {
      my $source = 'class MyClass { use Int as Foo::; static method main : void () { } }';
      compile_not_ok($source, qr/\QThe symbol name "Foo::" cannnot end with "::"/);
    }

    # A symbol name cannnot contains "::::".
    {
      my $source = 'class MyClass { use Int as Foo::::Bar; static method main : void () { } }';
      compile_not_ok($source, qr/\QThe symbol name "Foo::::Bar" cannnot contains "::::"/);
    }
  }
}

# Fat comma
{
  # The string literal of the left operand of the fat camma cannnot contains "::".
  {
    my $source = 'class MyClass { static method main : void () { {Foo::Bar => 1}; } }';
    compile_not_ok($source, qr/\QThe string literal "Foo::Bar" of the left operand of the fat camma cannnot contains "::"/);
  }
}

# Block
{
  {
    my $source = q|class Tmp { static method main : void () { {} }|;
    compile_not_ok($source, qr/Unexpected token "}"/);
  }
}

# pointer
{
  {
    my $source = q|class MyClass : pointer { }|;
    compile_ok($source);
  }
}

# Extra
{
  {
    my $source = q|class MyClass { static method main : void () { eval {} } }|;
    compile_ok($source);
  }
  
  # Unexpected token contains \n  at
  {
    # Invalid "_"
    my $source = 'class Tmp { static method main : void () { _-123; } }';
    compile_not_ok($source, qr/\n  at .+ line /);
  }
}

done_testing;

use strict;
use warnings;
use utf8;
use FindBin;

use SPVM::Builder;

use lib "$FindBin::Bin/../default/lib";
use lib "$FindBin::Bin/lib";

use MyTest qw(compile_not_ok_file compile_not_ok);

use Test::More;

# Class Name
{
  {
    my $source = 'class myclass;';
    compile_not_ok($source, qr|The class name "myclass" must begin with an upper case character|);
  }
  {
    my $source = 'class Myclass::foo;';
    compile_not_ok($source, qr|The part names of the class "Myclass::foo" must begin with an upper case character|);
  }
  {
    my $source = 'class Myclass::Foo::bar;';
    compile_not_ok($source, qr|The part names of the class "Myclass::Foo::bar" must begin with an upper case character|);
  }
  {
    my $source = 'class Myclass__Foo;';
    compile_not_ok($source, qr|The class name "Myclass__Foo" can't constain "__"|);
  }
  {
    my $source = 'class Myclass::;';
    compile_not_ok($source, qr|The class name "Myclass::" can't end with "::"|);
  }
  {
    my $source = 'class MyClass::::Foo;';
    compile_not_ok($source, qr|The class name "MyClass::::Foo" can't contains "::::"|);
  }
  {
    my $source = 'class ::MyClass;';
    compile_not_ok($source, qr|The class name "::MyClass" can't begin with "::"|);
  }
  {
    my $source = 'class 6MyClass;';
    compile_not_ok($source, qr|The class name "6MyClass" can't begin with a number|);
  }
}

# Loading Class
{
  {
    my $source = 'class MyClass { use NotFoundClass; }';
    compile_not_ok($source, qr|\QFailed to load the class "NotFoundClass". The module file "NotFoundClass.spvm" is not found|);
  }
}

# Caharater Literal
{
  {
    my $source = q|class MyClass { static method main : void () { ''; } }|;
    compile_not_ok($source, qr/The character literal can't be empty/);
  }
  {
    my $source = q|class MyClass { static method main : void () { '\xG'; } }|;
    compile_not_ok($source, qr/\QOne or tow hexadecimal numbers must be follow by "\x" of the hexadecimal escape character/);
  }
  {
    my $source = q|class MyClass { static method main : void () { '\xg'; } }|;
    compile_not_ok($source, qr/\QOne or tow hexadecimal numbers must be follow by "\x" of the hexadecimal escape character/);
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
}

# String literal
{
  {
    my $source = q|class Tmp { static method main : void () { "Foo \xg Bar" } }|;
    compile_not_ok($source, qr/\QOne or tow hexadecimal numbers must be follow by "\x" of the hexadecimal escape character/);
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

done_testing;

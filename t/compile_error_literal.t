use strict;
use warnings;
use utf8;
use Data::Dumper;
use File::Basename 'basename';
use FindBin;
use File::Temp ();

use SPVM::Builder;

use Test::More;

my $file = 't/' . basename $0;

use FindBin;
use lib "$FindBin::Bin/default/lib";

sub compile_not_ok_file {
  my ($class_name, $error_message_re, $options) = @_;
  
  unless ($options) {
    $options = {};
  }
  
  my $module_dir = $options->{module_dir};
  
  my (undef, $caller_file, $caller_line) = caller;
  
  my $file;
  if (defined $options->{file}) {
    $file = $options->{file};
  }
  else {
    $file = $caller_file;
  }

  my $line;
  if (defined $options->{line}) {
    $line = $options->{line};
  }
  else {
    $line = $caller_line;
  }
  
  my $builder = SPVM::Builder->new;
  if (defined $module_dir) {
    unshift @{$builder->module_dirs}, $module_dir;
  }
  
  my $success = $builder->compile_spvm($class_name, $file, $line);
  ok($success == 0);
  unless ($success == 0) {
    warn "  at $file line $line\n";
  }
  my $error_messages = $builder->get_error_messages;
  my $first_error_message = $error_messages->[0];
  if ($error_message_re) {
    like($first_error_message, $error_message_re);
  }
}

sub compile_not_ok {
  my ($source, $error_message_re) = @_;
  
  my (undef, $file, $line) = caller;
  
  my $builder = SPVM::Builder->new;
  
  my $class_name;
  if ($source =~ /\bclass\s+([\w+:]+)\s*/) {
    $class_name = $1;
  }
  unless (defined $class_name) {
    die "Can't find class name in the source";
  }
  
  my $tmp_module_dir = File::Temp->newdir;
  
  my $module_file = "$tmp_module_dir/$class_name.spvm";
  $module_file =~ s|::|/|g;
  
  if (open my $module_fh, '>', $module_file) {
    print $module_fh $source;
    close $module_fh;
  }
  
  compile_not_ok_file($class_name, $error_message_re, {module_dir => "$tmp_module_dir", file => $file, line => $line});
}

sub print_error_messages {
  my ($builder) = @_;
  
  my $error_messages = $builder->get_error_messages;
  
  for my $error_message (@$error_messages) {
    print STDERR "[CompileError]$error_message\n";
  }
}

# Literal
{
  # Integer literal
  {
    # Integer literal decimal notation
    {
      compile_not_ok_file('TestCase::CompileError::Literal::Integer::IntOutOfRange', qr/The numeric literal "8232624535311216194" is out of range of maximum and minimum values of int type/);
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
        compile_not_ok($source, qr/The numeric literal "0x100000000" is out of range of maximum and minimum values of int type at/);
      }
      {
        # Greater than long max value
        my $source = 'class Tmp { static method main : void () { 0x10000000000000000L; } }';
        compile_not_ok($source, qr/The numeric literal "0x10000000000000000L" is out of range of maximum and minimum values of long type at/);
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
        compile_not_ok($source, qr/The numeric literal "040000000000" is out of range of maximum and minimum values of int type at/);
      }
      {
        # Greater than long max value
        my $source = 'class Tmp { static method main : void () { 0x2000000000000000000000L; } }';
        compile_not_ok($source, qr/The numeric literal "0x2000000000000000000000L" is out of range of maximum and minimum values of long type at/);
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
        compile_not_ok($source, qr/The numeric literal "0b100000000000000000000000000000000" is out of range of maximum and minimum values of int type at/);
      }
      {
        # Greater than long max value
        my $source = 'class Tmp { static method main : void () { 0b10000000000000000000000000000000000000000000000000000000000000000L; } }';
        compile_not_ok($source, qr/The numeric literal "0b10000000000000000000000000000000000000000000000000000000000000000L" is out of range of maximum and minimum values of long type at/);
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

  # Caharater literal
  {
    compile_not_ok_file('TestCase::CompileError::Literal::Character::InvalidCharacterLiteralEmpty', qr/A character literal can't be empty/);
    compile_not_ok_file('TestCase::CompileError::Literal::Character::InvalidCharacterLiteral', qr/\QInvalid charater literal escape character "\A"/);
    compile_not_ok_file('TestCase::CompileError::Literal::Character::NotEnd', qr/A character literal must ends with "'"/);
    compile_not_ok_file('TestCase::CompileError::Literal::Character::InvalidHexAscii1', qr/\QAfter "\x" of the hexadecimal escape character, one or tow hexadecimal numbers must follow/);
    compile_not_ok_file('TestCase::CompileError::Literal::Character::InvalidHexAscii2', qr/A character literal must ends with "'"/);
    {
      my $source = q|class Tmp { static method main : void () { '\x{a' } }|;
      compile_not_ok($source, qr/The hexadecimal escape character that has the opening "\{" must have the closing "\}"/);
    }
    {
      my $source = q|class Tmp { static method main : void () { '\xaz' } }|;
      compile_not_ok($source, qr/A character literal must ends with "'"/);
    }
  }

  # String literal
  {
    {
      my $source = q|class Tmp { static method main : void () { "Foo \xg Bar" } }|;
      compile_not_ok($source, qr/\QAfter "\x" of the hexadecimal escape character, one or tow hexadecimal numbers must follow/);
    }
    {
      my $source = q|class Tmp { static method main : void () { "Foo \x{a Bar" } }|;
      compile_not_ok($source, qr/The hexadecimal escape character that has the opening "\{" must have the closing "\}"/);
    }
    {
      my $source = q|class Tmp { static method main : void () { "\u" }|;
      compile_not_ok($source, qr/Invalid string literal escape character "\\u"/);
    }
    
    # Unicode escape character
    {
      {
        my $source = q|class Tmp { static method main : void () { "\N{U+}" }|;
        compile_not_ok($source, qr/After "\\N\{U\+" of the Unicode escape character, one or more than one hexadecimal numbers must follow/);
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
      compile_not_ok($source, qr/A string literal must be end with '"'/);
    }
    {
      my $source = q|class Tmp { static method main : void () { "$foo->{foo-" }|;
      compile_not_ok($source, qr/Getting field in a string literal must be closed with "}"/);
    }
    {
      my $source = q|class Tmp { static method main : void () { "$foo->[3-" }|;
      compile_not_ok($source, qr/Getting array element in a string literal must be closed with "]"/);
    }
    {
      my $source = q|class Tmp { static method main : void () { "$foo->bar" }|;
      compile_not_ok($source, qr/\QThe character after "->" in a string literal must be "[" or "{"/);
    }
  }
  
  # Block
  {
    {
      my $source = q|class Tmp { static method main : void () { {} }|;
      compile_not_ok($source, qr/Unexpected token "}"/);
    }
  }
}

done_testing;

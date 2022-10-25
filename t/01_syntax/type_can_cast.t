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

# Compilation errors of the type assignability in spvm_type.c 

# Dist type is numeric type
{
  # Source type is numeric type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $source : short; my $dist = (byte)$source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $source : short; my $dist = (double)$source; } }';
      compile_ok($source);
    }
  }
  # Source type is numeric object type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $source : Byte; my $dist = (byte)$source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $source : Byte; my $dist = (short)$source; } }';
      compile_not_ok($source, qr|type cast|);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $source : Double; my $dist = (double)$source; } }';
      compile_ok($source);
    }
  }
  
  # Source type is any object type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $source : object; my $dist = (double)$source; } }';
      compile_ok($source);
    }
  }

  # The source type is other types
  {
    {
      my $source = 'class MyClass { static method main : void () { my $source : int[]; my $dist = (int)$source; } }';
      compile_not_ok($source, q|type cast|);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $source : int*; my $dist = (int)$source; } }';
      compile_not_ok($source, q|type cast|);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $source : string; my $dist = (byte)$source; } }';
      compile_not_ok($source, qr|type cast|);
    }
  }
}

# The dist type is the multi-numeric type
{
  # The source type is the multi-numeric type
  {
    {
      my $source = 'class MyClass { use Complex_2d; static method main : void () { my $source : Complex_2d; my $dist = (Complex_2d)$source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { use Complex_2d; use Complex_2f; static method main : void () { my $source : Complex_2d; my $dist = (Complex_2f)$source; } }';
      compile_not_ok($source, q|type cast|);
    }
  }
  # The source type is not multi-numeric type
  {
    {
      my $source = 'class MyClass { use Complex_2d; static method main : void () { my $source : Complex_2d; my $dist = (double)$source; } }';
      compile_not_ok($source, q|type cast|);
    }
  }
}

# The dist type is the reference type
{
  # The source type is the reference type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $source : int*; my $dist = (int*)$source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { use Complex_2d; static method main : void () { my $source : Complex_2d*; my $dist : Complex_2d* = $source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { use Complex_2d; use Complex_2f; static method main : void () { my $source : int*; my $dist = (long*)$source; } }';
      compile_not_ok($source, q|type cast|);
    }
  }
  # The source type is not the reference type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $source : int*; my $dist = (int)$source; } }';
      compile_not_ok($source, q|type cast|);
    }
  }
}

done_testing;

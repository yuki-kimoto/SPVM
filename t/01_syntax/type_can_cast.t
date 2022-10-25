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

  # Source type is other types
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

# Dist type is the multi-numeric type
{
  # Source type is the multi-numeric type
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
  # Source type is not multi-numeric type
  {
    {
      my $source = 'class MyClass { use Complex_2d; static method main : void () { my $source : Complex_2d; my $dist = (double)$source; } }';
      compile_not_ok($source, q|type cast|);
    }
  }
}

# Dist type is the reference type
{
  # Source type is the reference type
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
  # Source type is not the reference type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $source : int*; my $dist = (int)$source; } }';
      compile_not_ok($source, q|type cast|);
    }
  }
}

# Dist type is string type
{
  # Source type is the string type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $source : string; my $dist = (string)$source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $source : mutable string; my $dist = (string)$source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $source : string; my $dist = (mutable string)$source; } }';
      compile_ok($source);
    }
  }
  
  # Source type is the numeric type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $source : byte; my $dist = (string)$source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $source : short; my $dist = (string)$source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $source : int; my $dist = (string)$source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $source : long; my $dist = (string)$source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $source : float; my $dist = (string)$source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $source : double; my $dist = (string)$source; } }';
      compile_ok($source);
    }
  }
  
  # Source type is byte array type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $source : byte[]; my $dist = (string)$source; } }';
      compile_ok($source);
    }
  }

  # Source type is any object type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $source : object; my $dist = (string)$source; } }';
      compile_ok($source);
    }
  }
  
  
  # Source type is undef
  {
    {
      my $source = 'class MyClass { static method main : void () { my $dist = (string)undef; } }';
      compile_ok($source);
    }
  }
  
  # Source type is ohter type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $source : Byte; my $dist = (string)$source; } }';
      compile_not_ok($source, q|type cast|);
    }
  }
}

# Dist type is the numeric object type
{
  # Source type is the correspoint numeric type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $source : byte; my $dist = (Byte)$source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $source : short; my $dist = (Short)$source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $source : int; my $dist = (Int)$source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $source : long; my $dist = (Long)$source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $source : float; my $dist = (Float)$source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $source : double; my $dist = (Double)$source; } }';
      compile_ok($source);
    }
  }
  
  # Source type is not the correspoint numeric type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $source : byte; my $dist = (Double)$source; } }';
      compile_not_ok($source, q|type cast|);
    }
  }

  # Source type is any object type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $source : object; my $dist = (Byte)$source; } }';
      compile_ok($source);
    }
  }
  
  # Source type is undef type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $dist = (Byte)undef; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $dist = (Short)undef; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $dist = (Int)undef; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $dist = (Long)undef; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $dist = (Float)undef; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $dist = (Double)undef; } }';
      compile_ok($source);
    }
  }
  
  # Source type is ohter type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $source : int*; my $dist = (Int)$source; } }';
      compile_not_ok($source, q|type cast|);
    }
    {
      my $source = 'class MyClass { use Complex_2d; static method main : void () { my $source : Complex_2d; my $dist = (Int)$source; } }';
      compile_not_ok($source, q|type cast|);
    }
    {
      my $source = 'class MyClass { use Point; static method main : void () { my $source : Point; my $dist = (Int)$source; } }';
      compile_not_ok($source, q|type cast|);
    }
  }
}


done_testing;

use strict;
use warnings;
use utf8;
use FindBin;

use SPVM::Builder;

use lib "$FindBin::Bin/../default/lib";
use lib "$FindBin::Bin/lib";

use MyTest qw(compile_not_ok_file compile_not_ok);

use Test::More;

# Compilation errors of the type assignability in spvm_type.c 

# Dist type is numeric type
{
  # Source type is numeric type
  {
    # Dist type is same as source type
    {
      {
        my $source = 'class MyClass { static method main : void () { my $source : byte; my $dist : byte = $source; } }';
        compile_ok($source);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : short; my $dist : short = $source; } }';
        compile_ok($source);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : int; my $dist : int = $source; } }';
        compile_ok($source);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : long; my $dist : long = $source; } }';
        compile_ok($source);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : float; my $dist : float = $source; } }';
        compile_ok($source);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : double; my $dist : double = $source; } }';
        compile_ok($source);
      }
    }
    
    # Dist type is more wide than source type
    {
      {
        my $source = 'class MyClass { static method main : void () { my $source : byte; my $dist : short = $source; } }';
        compile_ok($source);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : short; my $dist : int = $source; } }';
        compile_ok($source);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : int; my $dist : long = $source; } }';
        compile_ok($source);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : long; my $dist : float = $source; } }';
        compile_ok($source);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : float; my $dist : double = $source; } }';
        compile_ok($source);
      }
    }
    
    # Dist type is norraw than source type
    {
      {
        my $source = 'class MyClass { static method main : void () { my $dist : byte = -128; } }';
        compile_ok($source);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $dist : byte = -129; } }';
        compile_not_ok($source, q|The implicite narrowing conversion from "int" to "byte" in the assignment operator is not allowed|);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $dist : short = -32768; } }';
        compile_ok($source);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $dist : short = -32769; } }';
        compile_not_ok($source, q|The implicite narrowing conversion from "int" to "short" in the assignment operator is not allowed|);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $dist : int = -2147483648L; } }';
        compile_ok($source);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $dist : int = -2147483649L; } }';
        compile_not_ok($source, q|The implicite narrowing conversion from "long" to "int" in the assignment operator is not allowed|);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : short; my $dist : byte = $source; } }';
        compile_not_ok($source, q|The implicite narrowing conversion from "short" to "byte" in the assignment operator is not allowed|);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : int; my $dist : short = $source; } }';
        compile_not_ok($source, q|The implicite narrowing conversion from "int" to "short" in the assignment operator is not allowed|);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : long; my $dist : int = $source; } }';
        compile_not_ok($source, q|The implicite narrowing conversion from "long" to "int" in the assignment operator is not allowed|);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : float; my $dist : long = $source; } }';
        compile_not_ok($source, q|The implicite narrowing conversion from "float" to "long" in the assignment operator is not allowed|);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : double; my $dist : float = $source; } }';
        compile_not_ok($source, q|The implicite narrowing conversion from "double" to "float" in the assignment operator is not allowed|);
      }
    }
  }

  # The source type is an object type
  {
    # The source type is the corresponding numeric object type
    {
      {
        my $source = 'class MyClass { static method main : void () { my $source : Byte; my $dist : byte = $source; } }';
        compile_ok($source);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : Short; my $dist : short = $source; } }';
        compile_ok($source);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : Int; my $dist : int = $source; } }';
        compile_ok($source);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : Long; my $dist : long = $source; } }';
        compile_ok($source);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : Float; my $dist : float = $source; } }';
        compile_ok($source);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : Double; my $dist : double = $source; } }';
        compile_ok($source);
      }
    }
    
    # The source type is the any object type
    {
      {
        my $source = 'class MyClass { static method main : void () { my $source : object; my $dist : byte = $source; } }';
        compile_ok($source);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : object; my $dist : short = $source; } }';
        compile_ok($source);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : object; my $dist : int = $source; } }';
        compile_ok($source);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : object; my $dist : long = $source; } }';
        compile_ok($source);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : object; my $dist : float = $source; } }';
        compile_ok($source);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : object; my $dist : double = $source; } }';
        compile_ok($source);
      }
    }
    
    # The source type is not the corresponding numeric object type
    {
      {
        my $source = 'class MyClass { static method main : void () { my $source : Byte; my $dist : short = $source; } }';
        compile_not_ok($source, q|The implicite type conversion from "Byte" to "short" in the assignment operator is not allowed|);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : Short; my $dist : int = $source; } }';
        compile_not_ok($source, q|The implicite type conversion from "Short" to "int" in the assignment operator is not allowed|);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : Int; my $dist : long = $source; } }';
        compile_not_ok($source, q|The implicite type conversion from "Int" to "long" in the assignment operator is not allowed|);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : Long; my $dist : float = $source; } }';
        compile_not_ok($source, q|The implicite type conversion from "Long" to "float" in the assignment operator is not allowed|);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : Float; my $dist : double = $source; } }';
        compile_not_ok($source, q|The implicite type conversion from "Float" to "double" in the assignment operator is not allowed|);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : Double; my $dist : byte = $source; } }';
        compile_not_ok($source, q|The implicite type conversion from "Double" to "byte" in the assignment operator is not allowed|);
      }
    }
    # The source type is other types
    {
      {
        my $source = 'class MyClass { static method main : void () { my $source : int[]; my $dist : int = $source; } }';
        compile_not_ok($source, q|The implicite type conversion from "int[]" to "int" in the assignment operator is not allowed|);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : int*; my $dist : int = $source; } }';
        compile_not_ok($source, q|The implicite type conversion from "int*" to "int" in the assignment operator is not allowed|);
      }
      {
        my $source = 'class MyClass { use Complex_2d; static method main : void () { my $source : Complex_2d; my $dist : int = $source; } }';
        compile_not_ok($source, q|The implicite type conversion from "Complex_2d" to "int" in the assignment operator is not allowed|);
      }
    }
  }
}

# The dist type is the multi-numeric type
{
  # The source type is the multi-numeric type
  {
    {
      my $source = 'class MyClass { use Complex_2d; static method main : void () { my $source : Complex_2d; my $dist : Complex_2d = $source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { use Complex_2d; use Complex_2f; static method main : void () { my $source : Complex_2d; my $dist : Complex_2f = $source; } }';
      compile_not_ok($source, q|The implicite type conversion from "Complex_2d" to "Complex_2f" in the assignment operator is not allowed|);
    }
  }
  # The source type is not multi-numeric type
  {
    {
      my $source = 'class MyClass { use Complex_2d; static method main : void () { my $source : Complex_2d; my $dist : double = $source; } }';
      compile_not_ok($source, q|The implicite type conversion from "Complex_2d" to "double" in the assignment operator is not allowed|);
    }
  }
}

# The dist type is the reference type
{
  # The source type is the reference type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $source : int*; my $dist : int* = $source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { use Complex_2d; static method main : void () { my $source : Complex_2d*; my $dist : Complex_2d* = $source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { use Complex_2d; use Complex_2f; static method main : void () { my $source : int*; my $dist : long* = $source; } }';
      compile_not_ok($source, q|The implicite type conversion from "int*" to "long*" in the assignment operator is not allowed|);
    }
  }
  # The source type is not the reference type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $source : int*; my $dist : int = $source; } }';
      compile_not_ok($source, q|The implicite type conversion from "int*" to "int" in the assignment operator is not allowed|);
    }
  }
}

=pod

  # The source type is an object type
  {
    {
      {
        my $source = 'class MyClass { static method main : void () { my $source : byte; my $dist : Byte = $source; } }';
        compile_ok($source);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : short; my $dist : Short = $source; } }';
        compile_ok($source);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : int; my $dist : Int = $source; } }';
        compile_ok($source);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : long; my $dist : Long = $source; } }';
        compile_ok($source);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : float; my $dist : Float = $source; } }';
        compile_ok($source);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : double; my $dist : Double = $source; } }';
        compile_ok($source);
      }
    }

    {
      {
        my $source = 'class MyClass { static method main : void () { my $source : byte; my $dist : Short = $source; } }';
        compile_not_ok($source, q|The implicite type conversion from "byte" to "Short" in the assignment operator is not allowed|);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : short; my $dist : Int = $source; } }';
        compile_not_ok($source, q|The implicite type conversion from "short" to "Int" in the assignment operator is not allowed|);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : int; my $dist : Long = $source; } }';
        compile_not_ok($source, q|The implicite type conversion from "int" to "Long" in the assignment operator is not allowed|);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : long; my $dist : Float = $source; } }';
        compile_not_ok($source, q|The implicite type conversion from "long" to "Float" in the assignment operator is not allowed|);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : float; my $dist : Double = $source; } }';
        compile_not_ok($source, q|The implicite type conversion from "float" to "Double" in the assignment operator is not allowed|);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : double; my $dist : Byte = $source; } }';
        compile_not_ok($source, q|The implicite type conversion from "double" to "Byte" in the assignment operator is not allowed|);
      }
    }
  }

=cut

done_testing;

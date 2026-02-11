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

# Compilation errors of the type requirement in spvm_type.c 

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
        compile_not_ok($source, q|int type cannot be assigned to byte type in assignment operator.|);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $dist : short = -32768; } }';
        compile_ok($source);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $dist : short = -32769; } }';
        compile_not_ok($source, q|int type cannot be assigned to short type in assignment operator.|);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $dist : int = -2147483648L; } }';
        compile_ok($source);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $dist : int = -2147483649L; } }';
        compile_not_ok($source, q|long type cannot be assigned to int type in assignment operator.|);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : short; my $dist : byte = $source; } }';
        compile_not_ok($source, q|short type cannot be assigned to byte type in assignment operator.|);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : int; my $dist : short = $source; } }';
        compile_not_ok($source, q|int type cannot be assigned to short type in assignment operator.|);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : long; my $dist : int = $source; } }';
        compile_not_ok($source, q|long type cannot be assigned to int type in assignment operator.|);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : float; my $dist : long = $source; } }';
        compile_not_ok($source, q|float type cannot be assigned to long type in assignment operator.|);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : double; my $dist : float = $source; } }';
        compile_not_ok($source, q|double type cannot be assigned to float type in assignment operator.|);
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
        compile_not_ok($source, q|Byte type cannot be assigned to short type in assignment operator.|);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : Short; my $dist : int = $source; } }';
        compile_not_ok($source, q|Short type cannot be assigned to int type in assignment operator.|);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : Int; my $dist : long = $source; } }';
        compile_not_ok($source, q|Int type cannot be assigned to long type in assignment operator.|);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : Long; my $dist : float = $source; } }';
        compile_not_ok($source, q|Long type cannot be assigned to float type in assignment operator.|);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : Float; my $dist : double = $source; } }';
        compile_not_ok($source, q|Float type cannot be assigned to double type in assignment operator.|);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : Double; my $dist : byte = $source; } }';
        compile_not_ok($source, q|Double type cannot be assigned to byte type in assignment operator.|);
      }
    }
    # The source type is other types
    {
      {
        my $source = 'class MyClass { static method main : void () { my $source : int[]; my $dist : int = $source; } }';
        compile_not_ok($source, q|int[] type cannot be assigned to int type in assignment operator.|);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : int*; my $dist : int = $source; } }';
        compile_not_ok($source, q|int* type cannot be assigned to int type in assignment operator.|);
      }
      {
        my $source = 'class MyClass { use Complex_2d; static method main : void () { my $source : Complex_2d; my $dist : int = $source; } }';
        compile_not_ok($source, q|Complex_2d type cannot be assigned to int type in assignment operator.|);
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
      compile_not_ok($source, q|Complex_2d type cannot be assigned to Complex_2f type in assignment operator.|);
    }
  }
  # The source type is not multi-numeric type
  {
    {
      my $source = 'class MyClass { use Complex_2d; static method main : void () { my $source : Complex_2d; my $dist : double = $source; } }';
      compile_not_ok($source, q|Complex_2d type cannot be assigned to double type in assignment operator.|);
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
      compile_not_ok($source, q|int* type cannot be assigned to long* type in assignment operator.|);
    }
  }
  
  # The source type is undef type
  {
    my $source = [
      'class MyClass { static method main : int () { my $ref : int* = undef; }  }',
    ];
    compile_ok($source);
  }
  
  # The source type is not the reference type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $source : int*; my $dist : int = $source; } }';
      compile_not_ok($source, q|int* type cannot be assigned to int type in assignment operator.|);
    }
  }
}

# The dist type is string type
{
  # The source type is string type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $source : string; my $dist : string = $source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $source : mutable string; my $dist : string = $source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $source : string; my $dist : mutable string = $source; } }';
      compile_not_ok($source, q|string type cannot be assigned to mutable string type in assignment operator.|);
    }
  }
  
  # The source type is the numeric type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $source : byte; my $dist : string = $source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $source : short; my $dist : string = $source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $source : int; my $dist : string = $source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $source : long; my $dist : string = $source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $source : float; my $dist : string = $source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $source : double; my $dist : string = $source; } }';
      compile_ok($source);
    }
  }
  
  # The source type is undef
  {
    {
      my $source = 'class MyClass { static method main : void () { my $dist : string = undef; } }';
      compile_ok($source);
    }
  }
  
  # The source type is ohters
  {
    {
      my $source = 'class MyClass { static method main : void () { my $source : Byte; my $dist : string = $source; } }';
      compile_not_ok($source, q|Byte type cannot be assigned to string type in assignment operator.|);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $source : byte[]; my $dist : string = $source; } }';
      compile_not_ok($source, q|byte[] type cannot be assigned to string type in assignment operator.|);
    }
  }
}

# The dist type is the numeric object type
{
  # The source type is the correspoint numeric type
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
  
  # The source type is not the correspoint numeric type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $source : byte; my $dist : Short = $source; } }';
      compile_not_ok($source, q|byte type cannot be assigned to Short type in assignment operator.|);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $source : short; my $dist : Int = $source; } }';
      compile_not_ok($source, q|short type cannot be assigned to Int type in assignment operator.|);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $source : int; my $dist : Long = $source; } }';
      compile_not_ok($source, q|int type cannot be assigned to Long type in assignment operator.|);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $source : long; my $dist : Float = $source; } }';
      compile_not_ok($source, q|long type cannot be assigned to Float type in assignment operator.|);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $source : float; my $dist : Double = $source; } }';
      compile_not_ok($source, q|float type cannot be assigned to Double type in assignment operator.|);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $source : double; my $dist : Byte = $source; } }';
      compile_not_ok($source, q|double type cannot be assigned to Byte type in assignment operator.|);
    }
  }

  # The source type is the same numeric object type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $source : Byte; my $dist : Byte = $source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $source : Short; my $dist : Short = $source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $source : Int; my $dist : Int = $source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $source : Long; my $dist : Long = $source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $source : Float; my $dist : Float = $source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $source : Double; my $dist : Double = $source; } }';
      compile_ok($source);
    }
  }
  # The source type is undef type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $dist : Byte = undef; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $dist : Short = undef; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $dist : Int = undef; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $dist : Long = undef; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $dist : Float = undef; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $dist : Double = undef; } }';
      compile_ok($source);
    }
  }
  
  # The source type is ohters
  {
    {
      my $source = 'class MyClass { static method main : void () { my $source : int*; my $dist : Int = $source; } }';
      compile_not_ok($source, q|int* type cannot be assigned to Int type in assignment operator.|);
    }
    {
      my $source = 'class MyClass { use Complex_2d; static method main : void () { my $source : Complex_2d; my $dist : Int = $source; } }';
      compile_not_ok($source, q|Complex_2d type cannot be assigned to Int type in assignment operator.|);
    }
    {
      my $source = 'class MyClass { use Point; static method main : void () { my $source : Point; my $dist : Int = $source; } }';
      compile_not_ok($source, q|Point type cannot be assigned to Int type in assignment operator.|);
    }
  }
}

# The dist type is the class type
{
  # The source type is the same class type
  {
    {
      my $source = 'class MyClass { use Point; static method main : void () { my $source : Point; my $dist : Point = $source; } }';
      compile_ok($source);
    }
  }
  # The source type is the child class type
  {
    {
      my $source = 'class MyClass { use Point; use Point3D; static method main : void () { my $source : Point3D; my $dist : Point = $source; } }';
      compile_ok($source);
    }
  }
  # The source type is the parent class type
  {
    {
      my $source = 'class MyClass { use Point; use Point3D; static method main : void () { my $source : Point; my $dist : Point3D = $source; } }';
      compile_not_ok($source, q|Point type cannot be assigned to Point3D type in assignment operator.|);
    }
  }
  # The source type is undef type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $dist : MyClass = undef; } }';
      compile_ok($source);
    }
  }
  # The source type is ohters
  {
    {
      my $source = 'class MyClass { use Point; static method main : void () { my $source : MyClass; my $dist : Point = $source; } }';
      compile_not_ok($source, q|MyClass type cannot be assigned to Point type in assignment operator.|);
    }
    {
      my $source = 'class MyClass { use Point; static method main : void () { my $source : MyClass; my $dist : int = $source; } }';
      compile_not_ok($source, q|MyClass type cannot be assigned to int type in assignment operator.|);
    }
  }
}

# The dist type is the interface type
{
  # The source type is the interface type
  {
    {
      my $source = 'class MyClass { use Stringable; static method main : void () { my $source : Stringable; my $dist : Stringable = $source; } }';
      compile_ok($source);
    }
    {
      my $source = [
        'class MyClass { use Stringable; use MyInterface; static method main : void () { my $source : MyInterface; my $dist : Stringable = $source; } }',
        'class MyInterface : interface_t { interface Stringable; required method to_string : string (); }',
      ];
      compile_ok($source);
    }
    {
      my $source = [
        'class MyClass { use Stringable; use MyInterface; static method main : void () { my $source : MyInterface; my $dist : Stringable = $source; } }',
        'class MyInterface : interface_t { required method to_string : string (); }',
      ];
      compile_ok($source);
    }
    {
      my $source = [
        'class MyClass { use Stringable; use MyInterface; static method main : void () { my $source : MyInterface; my $dist : Stringable = $source; } }',
        'class MyInterface : interface_t { required method foo : string (); }',
      ];
      compile_not_ok($source, q|MyInterface interface must define to_string method because its interface method is defined as a required method in Stringable interface.|);
    }
  }
}

# Dist type is any object type
{
  # Source type is object type
  {
    {
      my $source = 'class MyClass { use Point; static method main : void () { my $source : Point; my $dist : object = $source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { use Stringable; static method main : void () { my $source : Stringable; my $dist : object = $source; } }';
      compile_ok($source);
    }
  }
  # Source type is numeric type
  {
    {
      my $source = 'class MyClass { use Point; static method main : void () { my $source : byte; my $dist : object = $source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { use Point; static method main : void () { my $source : double; my $dist : object = $source; } }';
      compile_ok($source);
    }
  }
  # Source type is undef type
  {
    {
      my $source = 'class MyClass { use Point; static method main : void () { my $dist : object = undef; } }';
      compile_ok($source);
    }
  }
  # Source type is other type
  {
    {
      my $source = 'class MyClass { use Point; static method main : void () { my $source : int*; my $dist : object = $source; } }';
      compile_not_ok($source, , q|int* type cannot be assigned to object type in assignment operator.|);
    }
    {
      my $source = 'class MyClass { use Complex_2d; static method main : void () { my $source : Complex_2d; my $dist : object = $source; } }';
      compile_not_ok($source, , q|Complex_2d type cannot be assigned to object type in assignment operator.|);
    }
  }
}

# Dist type is undef type
{
  # Source type is object type
  {
    {
      my $source = 'class MyClass { use Point; static method main : void () { my $source : Point; undef = $source; } }';
      compile_not_ok($source, qr|mutable|);
    }
  }
}

# Dist type is numeric array type
{
  # Source type is numeric array type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $source : byte[]; my $dist : byte[] = $source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $source : double[]; my $dist : double[] = $source; } }';
      compile_ok($source);
    }
  }
  
  # Source type is undef type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $dist : double[] = undef; } }';
      compile_ok($source);
    }
  }
  
  # 
  {
    {
      my $source = 'class MyClass { static method main : void () { my $source : byte[]; my $dist : short[] = $source; } }';
      compile_not_ok($source, , q|byte[] type cannot be assigned to short[] type in assignment operator.|);
    }
  }
}

# Dist type is multi-numeric array type
{
  # Source type is multi-numeric array type
  {
    {
      my $source = 'class MyClass { use Complex_2d; static method main : void () { my $source : Complex_2d[]; my $dist : Complex_2d[] = $source; } }';
      compile_ok($source);
    }
  }
  # Source type is undef type
  {
    {
      my $source = 'class MyClass { use Complex_2d; static method main : void () { my $dist : Complex_2d[] = undef; } }';
      compile_ok($source);
    }
  }
  # Source type is other type
  {
    {
      my $source = 'class MyClass { use Complex_2d; use Complex_2f; static method main : void () { my $source : Complex_2d[]; my $dist : Complex_2f[] = $source; } }';
      compile_not_ok($source, , q|Complex_2d[] type cannot be assigned to Complex_2f[] type in assignment operator.|);
    }
  }
}

# Dist type is string array type
{
  # Source type is string array type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $source : string[]; my $dist : string[] = $source; } }';
      compile_ok($source);
    }
  }
  # Source type is undef type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $dist : string[] = undef; } }';
      compile_ok($source);
    }
  }
  # Source type is other type
  {
    {
      my $source = 'class MyClass {use Complex_2f; static method main : void () { my $source : byte[]; my $dist : string[] = $source; } }';
      compile_not_ok($source, , q|byte[] type cannot be assigned to string[] type in assignment operator.|);
    }
  }
}

# Dist type is class array type
{
  # Source type is class array type
  {
    {
      my $source = 'class MyClass { use Point; use Point3D; static method main : void () { my $source : Point[]; my $dist : Point[] = $source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { use Point; use Point3D; static method main : void () { my $source : Point3D[]; my $dist : Point[] = $source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { use Point; use Point3D; static method main : void () { my $source : Point[]; my $dist : Point3D[] = $source; } }';
      compile_not_ok($source, , q|Point[] type cannot be assigned to Point3D[] type in assignment operator.|);
    }
  }
  # Source type is undef type
  {
    {
      my $source = 'class MyClass { use Point; use Point3D; static method main : void () { my $dist : Point[] = undef; } }';
      compile_ok($source);
    }
  }
  # Source type is other type
  {
    {
      my $source = 'class MyClass { use Point; use Point3D;  static method main : void () { my $source : Point[]; my $dist : Int[] = $source; } }';
      compile_not_ok($source, , q|Point[] type cannot be assigned to Int[] type in assignment operator.|);
    }
  }
}

# Dist type is interface array type
{
  # Source type is interface array type
  {
    {
      my $source = 'class MyClass { use Stringable; use Point; use Point3D; static method main : void () { my $source : Stringable[]; my $dist : Stringable[] = $source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { use Stringable; use Cloneable; static method main : void () { my $source : Stringable[]; my $dist : Cloneable[] = $source; } }';
      compile_not_ok($source, , q|Stringable interface must define clone method because its interface method is defined as a required method in Cloneable interface.|);
    }
    {
      my $source = [
        'class MyClass { use Stringable; use Stringable2; use Point; use Point3D; static method main : void () { my $source : Stringable2[]; my $dist : Stringable[] = $source; } }',
        'class Stringable2 : interface_t { interface Stringable; required method to_string : string (); }',
      ];
      compile_ok($source);
    }
  }

  # Source type is class array type
  {
    {
      my $source = 'class MyClass { use Stringable; use Point; use Point3D; static method main : void () { my $source : Point[]; my $dist : Stringable[] = $source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { use Cloneable; static method main : void () { my $source : Error[]; my $dist : Cloneable[] = $source; } }';
      compile_not_ok($source, , q|Error class must define clone method because its interface method is defined as a required method in Cloneable interface.|);
    }
  }
  
  # Source type is undef type
  {
    {
      my $source = 'class MyClass { use Stringable; static method main : void () { my $dist : Stringable[] = undef; } }';
      compile_ok($source);
    }
  }
  # Source type is other type
  {
    {
      my $source = 'class MyClass { use Stringable; static method main : void () { my $source : Error[]; my $dist : Stringable[] = $source; } }';
      compile_not_ok($source, , q|Error class must define to_string method because its interface method is defined as a required method in Stringable interface.|);
    }
  }
}

# Dist type is any object array
{
  # Source type is object array type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $source : string[]; my $dist : object[] = $source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $source : string[][]; my $dist : object[] = $source; } }';
      compile_ok($source);
    }
  }
  # Source type is undef type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $dist : object[] = undef; } }';
      compile_ok($source);
    }
  }
  # Source type is other type
  {
    {
      my $source = 'class MyClass {use Complex_2f; static method main : void () { my $source : object; my $dist : object[] = $source; } }';
      compile_not_ok($source, , q|object type cannot be assigned to object[] type in assignment operator.|);
    }
    {
      my $source = 'class MyClass {use Complex_2f; static method main : void () { my $source : int[]; my $dist : object[] = $source; } }';
      compile_not_ok($source, , q|int[] type cannot be assigned to object[] type in assignment operator.|);
    }
  }
}

# Dist type is multi-dimensional array type
{
  # Source type is multi-dimensional array type
  {
    {
      my $source = 'class MyClass { use Stringable; use Point; use Point3D; static method main : void () { my $source : int[][]; my $dist : int[][] = $source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { use Stringable; use Point; use Point3D; static method main : void () { my $source : Point[][]; my $dist : Point[][] = $source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { use Stringable; use Point; use Point3D; static method main : void () { my $source : Stringable[][]; my $dist : Stringable[][] = $source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { use Stringable; use Point; use Point3D; static method main : void () { my $source : Point[]; my $dist : Point[][] = $source; } }';
      compile_not_ok($source, , q|Point[] type cannot be assigned to Point[][] type in assignment operator.|);
    }
    {
      my $source = 'class MyClass { use Stringable; use Point; use Point3D; static method main : void () { my $source : Point[][]; my $dist : Stringable[][] = $source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { use Stringable; use Point; use Point3D; static method main : void () { my $source : Point3D[][]; my $dist : Point[][] = $source; } }';
      compile_ok($source);
    }
    {
      my $source = [
        'class MyClass { use Stringable; use Stringable2; use Point; use Point3D; static method main : void () { my $source : Stringable2[][]; my $dist : Stringable[][] = $source; } }',
        'class Stringable2 : interface_t { interface Stringable; required method to_string : string (); }',
      ];
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { use Stringable; use Point; use Point3D; static method main : void () { my $source : Point[][]; my $dist : Point3D[][] = $source; } }';
      compile_not_ok($source, , q|Point[][] type cannot be assigned to Point3D[][] type in assignment operator.|);
    }
  }
  # Source type is undef type
  {
    {
      my $source = 'class MyClass { use Point; static method main : void () { my $dist : Point[][] = undef; } }';
      compile_ok($source);
    }
  }
  # Source type is other type
  {
    {
      my $source = 'class MyClass {use Complex_2f; static method main : void () { my $source : int; my $dist : int[][] = $source; } }';
      compile_not_ok($source, , q|int type cannot be assigned to int[][] type in assignment operator.|);
    }
  }
}


# Extra
{
  {
    my $source = [
      'class MyClass { use MyIn_addr;use MySockaddrIn; static method main : void ($in_addr : MyIn_addr) { my $sin_addr = new MySockaddrIn; my $status = &main($sin_addr); } }',
      'class MySockaddrIn extends MySockaddr : public;',
      'class MySockaddr : public;',
      'class MyIn_addr : public;',
    ];
    compile_not_ok($source, q|MySockaddrIn type cannot be assigned to MyIn_addr type in the 1th argument of MyClass#main method.|);
  }
  
}

done_testing;

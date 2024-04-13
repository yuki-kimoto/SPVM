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
        compile_not_ok($source, q|The "int" type cannot be assigned to the "byte" type in the assignment operator.|);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $dist : short = -32768; } }';
        compile_ok($source);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $dist : short = -32769; } }';
        compile_not_ok($source, q|The "int" type cannot be assigned to the "short" type in the assignment operator.|);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $dist : int = -2147483648L; } }';
        compile_ok($source);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $dist : int = -2147483649L; } }';
        compile_not_ok($source, q|The "long" type cannot be assigned to the "int" type in the assignment operator.|);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : short; my $dist : byte = $source; } }';
        compile_not_ok($source, q|The "short" type cannot be assigned to the "byte" type in the assignment operator.|);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : int; my $dist : short = $source; } }';
        compile_not_ok($source, q|The "int" type cannot be assigned to the "short" type in the assignment operator.|);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : long; my $dist : int = $source; } }';
        compile_not_ok($source, q|The "long" type cannot be assigned to the "int" type in the assignment operator.|);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : float; my $dist : long = $source; } }';
        compile_not_ok($source, q|The "float" type cannot be assigned to the "long" type in the assignment operator.|);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : double; my $dist : float = $source; } }';
        compile_not_ok($source, q|The "double" type cannot be assigned to the "float" type in the assignment operator.|);
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
        compile_not_ok($source, q|The "Byte" type cannot be assigned to the "short" type in the assignment operator.|);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : Short; my $dist : int = $source; } }';
        compile_not_ok($source, q|The "Short" type cannot be assigned to the "int" type in the assignment operator.|);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : Int; my $dist : long = $source; } }';
        compile_not_ok($source, q|The "Int" type cannot be assigned to the "long" type in the assignment operator.|);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : Long; my $dist : float = $source; } }';
        compile_not_ok($source, q|The "Long" type cannot be assigned to the "float" type in the assignment operator.|);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : Float; my $dist : double = $source; } }';
        compile_not_ok($source, q|The "Float" type cannot be assigned to the "double" type in the assignment operator.|);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : Double; my $dist : byte = $source; } }';
        compile_not_ok($source, q|The "Double" type cannot be assigned to the "byte" type in the assignment operator.|);
      }
    }
    # The source type is other types
    {
      {
        my $source = 'class MyClass { static method main : void () { my $source : int[]; my $dist : int = $source; } }';
        compile_not_ok($source, q|The "int[]" type cannot be assigned to the "int" type in the assignment operator.|);
      }
      {
        my $source = 'class MyClass { static method main : void () { my $source : int*; my $dist : int = $source; } }';
        compile_not_ok($source, q|The "int*" type cannot be assigned to the "int" type in the assignment operator.|);
      }
      {
        my $source = 'class MyClass { use Complex_2d; static method main : void () { my $source : Complex_2d; my $dist : int = $source; } }';
        compile_not_ok($source, q|The "Complex_2d" type cannot be assigned to the "int" type in the assignment operator.|);
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
      compile_not_ok($source, q|The "Complex_2d" type cannot be assigned to the "Complex_2f" type in the assignment operator.|);
    }
  }
  # The source type is not multi-numeric type
  {
    {
      my $source = 'class MyClass { use Complex_2d; static method main : void () { my $source : Complex_2d; my $dist : double = $source; } }';
      compile_not_ok($source, q|The "Complex_2d" type cannot be assigned to the "double" type in the assignment operator.|);
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
      compile_not_ok($source, q|The "int*" type cannot be assigned to the "long*" type in the assignment operator.|);
    }
  }
  # The source type is not the reference type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $source : int*; my $dist : int = $source; } }';
      compile_not_ok($source, q|The "int*" type cannot be assigned to the "int" type in the assignment operator.|);
    }
  }
}

# The dist type is string type
{
  # The source type is the string type
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
      compile_not_ok($source, q|The "string" type cannot be assigned to the "mutable string" type in the assignment operator.|);
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
      compile_not_ok($source, q|The "Byte" type cannot be assigned to the "string" type in the assignment operator.|);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $source : byte[]; my $dist : string = $source; } }';
      compile_not_ok($source, q|The "byte[]" type cannot be assigned to the "string" type in the assignment operator.|);
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
      compile_not_ok($source, q|The "byte" type cannot be assigned to the "Short" type in the assignment operator.|);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $source : short; my $dist : Int = $source; } }';
      compile_not_ok($source, q|The "short" type cannot be assigned to the "Int" type in the assignment operator.|);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $source : int; my $dist : Long = $source; } }';
      compile_not_ok($source, q|The "int" type cannot be assigned to the "Long" type in the assignment operator.|);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $source : long; my $dist : Float = $source; } }';
      compile_not_ok($source, q|The "long" type cannot be assigned to the "Float" type in the assignment operator.|);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $source : float; my $dist : Double = $source; } }';
      compile_not_ok($source, q|The "float" type cannot be assigned to the "Double" type in the assignment operator.|);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $source : double; my $dist : Byte = $source; } }';
      compile_not_ok($source, q|The "double" type cannot be assigned to the "Byte" type in the assignment operator.|);
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
      compile_not_ok($source, q|The "int*" type cannot be assigned to the "Int" type in the assignment operator.|);
    }
    {
      my $source = 'class MyClass { use Complex_2d; static method main : void () { my $source : Complex_2d; my $dist : Int = $source; } }';
      compile_not_ok($source, q|The "Complex_2d" type cannot be assigned to the "Int" type in the assignment operator.|);
    }
    {
      my $source = 'class MyClass { use Point; static method main : void () { my $source : Point; my $dist : Int = $source; } }';
      compile_not_ok($source, q|The "Point" type cannot be assigned to the "Int" type in the assignment operator.|);
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
      compile_not_ok($source, q|The "Point" type cannot be assigned to the "Point3D" type in the assignment operator.|);
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
      compile_not_ok($source, q|The "MyClass" type cannot be assigned to the "Point" type in the assignment operator.|);
    }
    {
      my $source = 'class MyClass { use Point; static method main : void () { my $source : MyClass; my $dist : int = $source; } }';
      compile_not_ok($source, q|The "MyClass" type cannot be assigned to the "int" type in the assignment operator.|);
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
      compile_not_ok($source, q|The "MyInterface" interface must define the "to_string" method because its interface method is defined as a required method in the "Stringable" interface.|);
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
      compile_not_ok($source, , q|The "int*" type cannot be assigned to the "object" type in the assignment operator.|);
    }
    {
      my $source = 'class MyClass { use Complex_2d; static method main : void () { my $source : Complex_2d; my $dist : object = $source; } }';
      compile_not_ok($source, , q|The "Complex_2d" type cannot be assigned to the "object" type in the assignment operator.|);
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
      compile_not_ok($source, , q|The "byte[]" type cannot be assigned to the "short[]" type in the assignment operator.|);
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
      compile_not_ok($source, , q|The "Complex_2d[]" type cannot be assigned to the "Complex_2f[]" type in the assignment operator.|);
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
      compile_not_ok($source, , q|The "byte[]" type cannot be assigned to the "string[]" type in the assignment operator.|);
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
      compile_not_ok($source, , q|The "Point[]" type cannot be assigned to the "Point3D[]" type in the assignment operator.|);
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
      compile_not_ok($source, , q|The "Point[]" type cannot be assigned to the "Int[]" type in the assignment operator.|);
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
      compile_not_ok($source, , q|The "Stringable" interface must define the "clone" method because its interface method is defined as a required method in the "Cloneable" interface.|);
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
      my $source = 'class MyClass { use Cloneable; static method main : void () { my $source : Int[]; my $dist : Cloneable[] = $source; } }';
      compile_not_ok($source, , q|The "Int" class must define the "clone" method because its interface method is defined as a required method in the "Cloneable" interface.|);
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
      my $source = 'class MyClass { use Stringable; static method main : void () { my $source : Int[]; my $dist : Stringable[] = $source; } }';
      compile_not_ok($source, , q|The "Int" class must define the "to_string" method because its interface method is defined as a required method in the "Stringable" interface.|);
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
      compile_not_ok($source, , q|The "object" type cannot be assigned to the "object[]" type in the assignment operator.|);
    }
    {
      my $source = 'class MyClass {use Complex_2f; static method main : void () { my $source : int[]; my $dist : object[] = $source; } }';
      compile_not_ok($source, , q|The "int[]" type cannot be assigned to the "object[]" type in the assignment operator.|);
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
      compile_not_ok($source, , q|The "Point[]" type cannot be assigned to the "Point[][]" type in the assignment operator.|);
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
      compile_not_ok($source, , q|The "Point[][]" type cannot be assigned to the "Point3D[][]" type in the assignment operator.|);
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
      compile_not_ok($source, , q|The "int" type cannot be assigned to the "int[][]" type in the assignment operator.|);
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
    compile_not_ok($source, q|The "MySockaddrIn" type cannot be assigned to the "MyIn_addr" type in the 1th argument of the "main" method in the "MyClass" class.|);
  }
  
}

done_testing;

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
    # Numeric object classes
    my @obj_classes = qw(Byte Short Int Long Float Double);
    
    # Primitive types
    my @types = qw(byte short int long float double);
    
    for my $obj_class (@obj_classes) {
      for my $type (@types) {
        # Test explicit cast from numeric object to primitive type
        my $source = "class MyClass { static method main : void () { my \$source : $obj_class; my \$dist = ($type)\$source; } }";
        compile_ok($source);
      }
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
      compile_ok($source, qr|type cast|);
    }
    
    {
      my $source = 'class MyClass { static method main : void () { my $source : string; my $dist = (short)$source; } }';
      compile_ok($source, qr|type cast|);
    }
    
    {
      my $source = 'class MyClass { static method main : void () { my $source : string; my $dist = (int)$source; } }';
      compile_ok($source, qr|type cast|);
    }
    
    {
      my $source = 'class MyClass { static method main : void () { my $source : string; my $dist = (long)$source; } }';
      compile_ok($source, qr|type cast|);
    }
    
    {
      my $source = 'class MyClass { static method main : void () { my $source : string; my $dist = (float)$source; } }';
      compile_ok($source, qr|type cast|);
    }
    
    {
      my $source = 'class MyClass { static method main : void () { my $source : string; my $dist = (double)$source; } }';
      compile_ok($source, qr|type cast|);
    }
    
  }
}

# Dist type is multi-numeric type
{
  # Source type is multi-numeric type
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

# Dist type is reference type
{
  # Source type is reference type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $source : int*; my $dist = (int*)$source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { use Complex_2d; static method main : void () { my $source : Complex_2d*; my $dist = (Complex_2d*)$source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { use Complex_2d; use Complex_2f; static method main : void () { my $source : int*; my $dist = (long*)$source; } }';
      compile_not_ok($source, q|type cast|);
    }
  }
  
  # Source type is undef type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $dist = (int*)undef; } }';
      compile_ok($source);
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
  # Source type is string type
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
  
  # Source type is numeric type
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
  
  # Source type is numeric object
  {
    # Byte object to string
    {
      my $source = 'class MyClass { static method main : void () { my $source : Byte; my $dist = (string)$source; } }';
      compile_ok($source);
    }
    # Short object to string
    {
      my $source = 'class MyClass { static method main : void () { my $source : Short; my $dist = (string)$source; } }';
      compile_ok($source);
    }
    # Int object to string
    {
      my $source = 'class MyClass { static method main : void () { my $source : Int; my $dist = (string)$source; } }';
      compile_ok($source);
    }
    # Long object to string
    {
      my $source = 'class MyClass { static method main : void () { my $source : Long; my $dist = (string)$source; } }';
      compile_ok($source);
    }
    # Float object to string
    {
      my $source = 'class MyClass { static method main : void () { my $source : Float; my $dist = (string)$source; } }';
      compile_ok($source);
    }
    # Double object to string
    {
      my $source = 'class MyClass { static method main : void () { my $source : Double; my $dist = (string)$source; } }';
      compile_ok($source);
    }
  }
  
  # Source type is ohter type
  {
    {
      my $source = 'class MyClass { use Point; static method main : void () { my $source : Point; my $dist = (string)$source; } }';
      compile_not_ok($source, q|type cast|);
    }
  }
}

# Dist type is numeric object type
{
  # Source type is correspoint numeric type
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

# Dist type is class type
{
  # Source type is class type
  {
    {
      {
        my $source = 'class MyClass { use Point; static method main : void () { my $source : Point; my $dist = (Point)$source; } }';
        compile_ok($source);
      }
    }
    # Source type is child class type
    {
      {
        my $source = 'class MyClass { use Point; use Point3D; static method main : void () { my $source : Point3D; my $dist = (Point)$source; } }';
        compile_ok($source);
      }
    }
    # Source type is parent class type
    {
      {
        my $source = 'class MyClass { use Point; use Point3D; static method main : void () { my $source : Point; my $dist = (Point3D)$source; } }';
        compile_ok($source);
      }
    }
    # Source type is other type
    {
      {
        my $source = 'class MyClass { use Point; use Point3D; static method main : void () { my $source : Int; my $dist = (Point)$source; } }';
        compile_not_ok($source, q|type cast|);
      }
    }
  }

  # Source type is interface type
  {
    {
      my $source = 'class MyClass { use Stringable; use Point; use Point3D; static method main : void () { my $source : Stringable; my $dist = (Point)$source; } }';
      compile_ok($source, q|type cast|);
    }
    {
      my $source = 'class MyClass { use Fn;use Stringable; use Point; use Point3D; static method main : void () { my $source : Stringable; my $dist = (Fn)$source; } }';
      compile_not_ok($source, q|Fn class must define to_string method because its interface method is defined as a required method in Stringable interface.|);
    }
  }

  # Source type is any object type
  {
    {
      my $source = 'class MyClass { use Stringable; use Point; use Point3D; static method main : void () { my $source : object; my $dist = (Point)$source; } }';
      compile_ok($source, q|The "to_string" class must define the "Fn" method. This is defined as a required interface method in the "Stringable" interface.|);
    }
  }
  
  # Source type is undef type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $dist = (MyClass)undef; } }';
      compile_ok($source);
    }
  }
  # Source type is ohter type
  {
    {
      my $source = 'class MyClass { use Point; static method main : void () { my $source : MyClass; my $dist = (Point)$source; } }';
      compile_not_ok($source, q|type cast|);
    }
  }
}

# Dist type is interface type
{
  # Source type is class type
  {
    {
      my $source = 'class MyClass { use Stringable; use Point; static method main : void () { my $source : Point; my $dist = (Stringable)$source; } }';
      compile_ok($source);
    }
  }
  
  # Source type is interface type
  {
    {
      my $source = 'class MyClass { use Stringable; static method main : void () { my $source : Stringable; my $dist = (Stringable)$source; } }';
      compile_ok($source);
    }
    {
      my $source = [
        'class MyClass { use Stringable; use MyInterface; static method main : void () { my $source : MyInterface; my $dist = (Stringable)$source; } }',
        'class MyInterface : interface_t { interface Stringable; required method to_string : string (); }',
      ];
      compile_ok($source);
    }
  }
  # Source type is any object type
  {
    {
      my $source = 'class MyClass { use Stringable; use Point; static method main : void () { my $source : object; my $dist = (Stringable)$source; } }';
      compile_ok($source);
    }
  }
  # Source type is undef type
  {
    {
      my $source = 'class MyClass { use Stringable; use Point; static method main : void () { my $dist = (Stringable)undef; } }';
      compile_ok($source);
    }
  }
  # Source type is other type
  {
    {
      my $source = 'class MyClass { use Fn; use Stringable; static method main : void () { my $source : Fn; my $dist = (Stringable)$source; } }';
      compile_not_ok($source, q|Fn class must define to_string method because its interface method is defined as a required method in Stringable interface.|);
    }
    {
      my $source = 'class MyClass { use Stringable; static method main : void () { my $source : Stringable[]; my $dist = (Stringable)$source; } }';
      compile_not_ok($source, q|type cast|);
    }
  }
}

# Dist type is any object type
{
  # Source type is numeric type
  {
    {
      my $source = 'class MyClass { use Point; static method main : void () { my $source : byte; my $dist = (object)$source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { use Point; static method main : void () { my $source : double; my $dist = (object)$source; } }';
      compile_ok($source);
    }
  }
  # Source type is object type
  {
    {
      my $source = 'class MyClass { use Point; static method main : void () { my $source : Point; my $dist = (object)$source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { use Stringable; static method main : void () { my $source : Stringable; my $dist = (object)$source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { use Stringable; static method main : void () { my $source : object; my $dist = (object)$source; } }';
      compile_ok($source);
    }
  }
  # Source type is undef type
  {
    {
      my $source = 'class MyClass { use Point; static method main : void () { my $dist = (object)undef; } }';
      compile_ok($source);
    }
  }
  # Source type is other type
  {
    {
      my $source = 'class MyClass { use Point; static method main : void () { my $source : int*; my $dist = (object)$source; } }';
      compile_not_ok($source, q|type cast|);
    }
    {
      my $source = 'class MyClass { use Complex_2d; static method main : void () { my $source : Complex_2d; my $dist = (object)$source; } }';
      compile_not_ok($source, q|type cast|);
    }
  }
}

# Dist type is undef type
{
  # Source type is object type
  {
    {
      my $source = 'class MyClass { use Point; static method main : void () { my $source : Point; my $dist = (undef)$source; } }';
      compile_not_ok($source, qr|Unexpected token|);
    }
  }
}

# Dist type is byte array type
{
  # Source type is string type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $source : string; my $dist = (byte[])$source; } }';
      compile_ok($source);
    }
  }
  # Source type is byte array type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $source : byte[]; my $dist = (byte[])$source; } }';
      compile_ok($source);
    }
  }
  # Source type is any object type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $source : object; my $dist = (byte[])$source; } }';
      compile_ok($source);
    }
  }
  
  # Source type is undef type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $dist = (byte[])undef; } }';
      compile_ok($source);
    }
  }
  
  # Source type is other type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $source : double[]; my $dist = (byte[])$source; } }';
      compile_not_ok($source, q|type cast|);
    }
  }
}

# Dist type is numeric array type(except for byte array)
{
  # Source type is numeric array type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $source : short[]; my $dist = (short[])$source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $source : double[]; my $dist = (double[])$source; } }';
      compile_ok($source);
    }
  }
  
  # Source type is any object type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $source : object; my $dist = (short[])$source; } }';
      compile_ok($source);
    }
  }
  # Source type is undef type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $dist = (double[])undef; } }';
      compile_ok($source);
    }
  }
  
  # Source type is other type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $source : byte[]; my $dist = (short[])$source; } }';
      compile_not_ok($source, q|type cast|);
    }
  }
}

# Dist type is multi-numeric array type
{
  # Source type is multi-numeric array type
  {
    {
      my $source = 'class MyClass { use Complex_2d; static method main : void () { my $source : Complex_2d[]; my $dist = (Complex_2d[])$source; } }';
      compile_ok($source);
    }
  }

  # Source type is any object type
  {
    {
      my $source = 'class MyClass { use Complex_2d; static method main : void () { my $source : object; my $dist = (Complex_2d[])$source; } }';
      compile_ok($source);
    }
  }
  # Source type is undef type
  {
    {
      my $source = 'class MyClass { use Complex_2d; static method main : void () { my $dist = (Complex_2d[])undef; } }';
      compile_ok($source);
    }
  }
  # Source type is other type
  {
    {
      my $source = 'class MyClass { use Complex_2d; use Complex_2f; static method main : void () { my $source : Complex_2d[]; my $dist = (Complex_2f[])$source; } }';
      compile_not_ok($source, q|type cast|);
    }
  }
}

# Dist type is string array type
{
  # Source type is string array type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $source : string[]; my $dist = (string[])$source; } }';
      compile_ok($source);
    }
  }
  # Source type is any object type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $source : object; my $dist = (string[])$source; } }';
      compile_ok($source);
    }
  }
  # Source type is any object type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $source : object[]; my $dist = (string[])$source; } }';
      compile_ok($source);
    }
  }
  # Source type is undef type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $dist = (string[])undef; } }';
      compile_ok($source);
    }
  }
  # Source type is other type
  {
    {
      my $source = 'class MyClass {use Complex_2f; static method main : void () { my $source : byte[]; my $dist = (string[])$source; } }';
      compile_not_ok($source, q|type cast|);
    }
  }
}

# Dist type is class array type
{
  # Source type is class array type
  {
    {
      my $source = 'class MyClass { use Point; use Point3D; static method main : void () { my $source : Point[]; my $dist = (Point[])$source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { use Point; use Point3D; static method main : void () { my $source : Point3D[]; my $dist = (Point[])$source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { use Point; use Point3D; static method main : void () { my $source : Point[]; my $dist = (Point3D[])$source; } }';
      compile_ok($source);
    }
  }
  # Source type is any object type
  {
    {
      my $source = 'class MyClass { use Point; use Point3D; static method main : void () { my $source : object; my $dist = (Point[])$source; } }';
      compile_ok($source);
    }
  }
  # Source type is any object array type
  {
    {
      my $source = 'class MyClass { use Point; use Point3D; static method main : void () { my $source : object[]; my $dist = (Point[])$source; } }';
      compile_ok($source);
    }
  }
  # Source type is undef type
  {
    {
      my $source = 'class MyClass { use Point; use Point3D; static method main : void () { my $dist = (Point[])undef; } }';
      compile_ok($source);
    }
  }
  # Source type is other type
  {
    {
      my $source = 'class MyClass { use Point; use Point3D;  static method main : void () { my $source : Point[]; my $dist = (Int[])$source; } }';
      compile_not_ok($source, q|type cast|);
    }
  }
}

# Dist type is interface array type
{
  # Source type is class array type
  {
    {
      my $source = 'class MyClass { use Stringable; use Point; use Point3D; static method main : void () { my $source : Point[]; my $dist = (Stringable[])$source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { use Cloneable; static method main : void () { my $source : Error[]; my $dist = (Cloneable[])$source; } }';
      compile_not_ok($source);
    }
  }
  
  # Source type is interface array type
  {
    {
      my $source = 'class MyClass { use Stringable; use Point; use Point3D; static method main : void () { my $source : Stringable[]; my $dist = (Stringable[])$source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { use Stringable; use Cloneable; static method main : void () { my $source : Stringable[]; my $dist = (Cloneable[])$source; } }';
      compile_not_ok($source);
    }
    {
      my $source = [
        'class MyClass { use Stringable; use Stringable2; use Point; use Point3D; static method main : void () { my $source : Stringable2[]; my $dist = (Stringable[])$source; } }',
        'class Stringable2 : interface_t { interface Stringable; required method to_string : string (); }',
      ];
      compile_ok($source);
    }
    {
      my $source = [
        'class MyClass { use Stringable; use Stringable2; use Point; use Point3D; static method main : void () { my $source : Stringable[]; my $dist = (Stringable2[])$source; } }',
        'class Stringable2 : interface_t { interface Stringable; required method to_string : string (); }',
      ];
      compile_ok($source);
    }
  }
  # Source type is any object type
  {
    {
      my $source = 'class MyClass { use Stringable; use Point; use Point3D; static method main : void () { my $source : object; my $dist = (Stringable[])$source; } }';
      compile_ok($source);
    }
  }
  # Source type is any object array type
  {
    {
      my $source = 'class MyClass { use Stringable; use Point; use Point3D; static method main : void () { my $source : object[]; my $dist = (Stringable[])$source; } }';
      compile_ok($source);
    }
  }
  
  # Source type is undef type
  {
    {
      my $source = 'class MyClass { use Stringable; static method main : void () { my $dist = (Stringable[])undef; } }';
      compile_ok($source);
    }
  }
  # Source type is other type
  {
    {
      my $source = 'class MyClass { use Stringable; static method main : void () { my $source : Error[]; my $dist = (Stringable[])$source; } }';
      compile_not_ok($source, q|Error class must define to_string method because its interface method is defined as a required method in Stringable interface.|);
    }
  }
}

# Dist type is any object array
{
  # Source type is any object type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $source : object; my $dist = (object[])$source; } }';
      compile_ok($source);
    }
  }
  # Source type is object array type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $source : object[]; my $dist = (object[])$source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $source : string[]; my $dist = (object[])$source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $source : string[][]; my $dist = (object[])$source; } }';
      compile_ok($source);
    }
  }
  # Source type is undef type
  {
    {
      my $source = 'class MyClass { static method main : void () { my $dist = (object[])undef; } }';
      compile_ok($source);
    }
  }
  # Source type is other type
  {
    {
      my $source = 'class MyClass {use Complex_2f; static method main : void () { my $source : int[]; my $dist = (object[])$source; } }';
      compile_not_ok($source);
    }
    {
      my $source = 'class MyClass {use Complex_2f; static method main : void () { my $source : Int; my $dist = (object[])$source; } }';
      compile_not_ok($source, q|type cast|);
    }
  }
}

# Dist type is multi-dimensional array type
{
  # Source type is multi-dimensional array type
  {
    {
      my $source = 'class MyClass { use Stringable; use Point; use Point3D; static method main : void () { my $source : int[][]; my $dist = (int[][])$source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { use Stringable; use Point; use Point3D; static method main : void () { my $source : Point[][]; my $dist = (Point[][])$source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { use Stringable; use Point; use Point3D; static method main : void () { my $source : Stringable[][]; my $dist = (Stringable[][])$source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { use Stringable; use Point; use Point3D; static method main : void () { my $source : Point[]; my $dist = (Point[][])$source; } }';
      compile_not_ok($source, q|type cast|);
    }
    {
      my $source = 'class MyClass { use Stringable; use Point; use Point3D; static method main : void () { my $source : Point[][]; my $dist = (Stringable[][])$source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { use Stringable; use Point; use Point3D; static method main : void () { my $source : Point3D[][]; my $dist = (Point[][])$source; } }';
      compile_ok($source);
    }
    {
      my $source = 'class MyClass { use Stringable; use Point; use Point3D; static method main : void () { my $source : Point[][]; my $dist = (Point3D[][])$source; } }';
      compile_ok($source);
    }
    {
      my $source = [
        'class MyClass { use Stringable; use Stringable2; use Point; use Point3D; static method main : void () { my $source : Stringable2[][]; my $dist = (Stringable[][])$source; } }',
        'class Stringable2 : interface_t { interface Stringable; required method to_string : string (); }',
      ];
      compile_ok($source);
    }
    {
      my $source = [
        'class MyClass { use Stringable; use Stringable2; use Point; use Point3D; static method main : void () { my $source : Stringable[][]; my $dist = (Stringable2[][])$source; } }',
        'class Stringable2 : interface_t { interface Stringable; required method to_string : string (); }',
      ];
      compile_ok($source);
    }
  }
  # Source type is any object type
  {
    {
      my $source = 'class MyClass { use Stringable; use Point; use Point3D; static method main : void () { my $source : object; my $dist = (int[][])$source; } }';
      compile_ok($source);
    }
  }
  # Source type is any object array type
  {
    {
      my $source = 'class MyClass { use Stringable; use Point; use Point3D; static method main : void () { my $source : object[]; my $dist = (int[][])$source; } }';
      compile_ok($source);
    }
  }
  # Source type is undef type
  {
    {
      my $source = 'class MyClass { use Point; static method main : void () { my $dist = (Point[][])undef; } }';
      compile_ok($source);
    }
  }
  # Source type is other type
  {
    {
      my $source = 'class MyClass {use Complex_2f; static method main : void () { my $source : int; my $dist = (int[][])$source; } }';
      compile_not_ok($source, q|type cast|);
    }
    {
      my $source = 'class MyClass {use Complex_2f; static method main : void () { my $source : int[]; my $dist = (int[][])$source; } }';
      compile_not_ok($source, q|type cast|);
    }
    {
      my $source = 'class MyClass {use Complex_2f; static method main : void () { my $source : Int; my $dist = (Int[][])$source; } }';
      compile_not_ok($source, q|type cast|);
    }
    {
      my $source = 'class MyClass {use Complex_2f; static method main : void () { my $source : Int[]; my $dist = (Int[][])$source; } }';
      compile_not_ok($source, q|type cast|);
    }
  }
}

done_testing;

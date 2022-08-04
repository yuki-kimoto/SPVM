use strict;
use warnings;
use utf8;
use FindBin;

use SPVM::Builder;

use lib "$FindBin::Bin/../default/lib";
use lib "$FindBin::Bin/lib";

use MyTest qw(compile_not_ok_file compile_not_ok);

use Test::More;

# Syntax
{
  compile_not_ok_file('CompileError::Syntax::LineNumber', qr/our.*\b8:3\b/i);
}

# Symbol name
{
  # A symbol name can't conatain "__"
  {
    my $source = 'class MyClass { use Int as Foo__Bar; static method main : void () { } }';
    compile_not_ok($source, qr/\QThe symbol name "Foo__Bar" can't constain "__"/);
  }

  # A symbol name can't end with "::"
  {
    my $source = 'class MyClass { use Int as Foo::; static method main : void () { } }';
    compile_not_ok($source, qr/\QThe symbol name "Foo::" can't end with "::"/);
  }

  # A symbol name can't contains "::::".
  {
    my $source = 'class MyClass { use Int as Foo::::Bar; static method main : void () { } }';
    compile_not_ok($source, qr/\QThe symbol name "Foo::::Bar" can't contains "::::"/);
  }
}

# Fat comma
{
  # The string literal of the left operand of the fat camma can't contains "::".
  {
    my $source = 'class MyClass { static method main : void () { {Foo::Bar => 1}; } }';
    compile_not_ok($source, qr/\QThe string literal "Foo::Bar" of the left operand of the fat camma can't contains "::"/);
  }
}

# Class
{
  # Syntax
  {
    compile_not_ok_file('CompileError::Class::NotClosed');
    {
      my $source = 'class MyClass { static method main : void () {} } class MyClass2 { static method main : void () {} }';
      compile_not_ok($source, qr/Unexpected token "class"/);
    }
  }
  
  # Class descriptor
  {
    {
      my $source = 'class MyClass : pointer_t { has x : int; }';
      compile_not_ok($source, qr|The pointer class can't have fields|);
    }
  }
  
  # use
  {
    compile_not_ok_file('CompileError::Use::ImportMethodNotFound');
    compile_not_ok_file('CompileError::Use::AliasStartsLowerCase');
    compile_not_ok_file('CompileError::Use::AliasDuplication');
  }

  # Interface
  {
    compile_not_ok_file('CompileError::Interface::HaveBlock', qr/interface.+block/i);
    compile_not_ok_file('CompileError::Interface::NativeMethod', qr/interface.+native/i);
    compile_not_ok_file('CompileError::Interface::StaticMethod', qr/interface.+instance/i);
    compile_not_ok_file('CompileError::Interface::ArrayElementCantAssign', qr/The implicite type conversion from "List" to "Stringable" in the assignment operator is not allowed/i);
    compile_not_ok_file('CompileError::Interface::NotHaveInterfaceMethod', qr/CompileError::Interface::NotHaveInterfaceMethod.+to_string.+interface.+Stringable/i);
    compile_not_ok_file('CompileError::Interface::NoMethods', qr/The interface must have a required method/i);
    compile_not_ok_file('CompileError::Interface::MultiRequiredMethods', qr/multiple required method/i);
    compile_not_ok_file('CompileError::Interface::HasImplNotFound', qr/interface.+TestCase::Pointable.+the method declaration.+not_found/i);
  }
  # Class variable difinition
  {
    # Access control
    compile_not_ok_file('CompileError::ClassVar::Private');
    
    # Inheritance - extends syntax
    {
      {
        my $source = 'class MyClass extends Stringable {}';
        compile_not_ok($source, qr/The parant class must be a class type/);
      }
      {
        my $source = ['class MyClass extends PointerType {}', 'class PointerType : pointer_t {}'];
        compile_not_ok($source, qr/The parant class must be a non-pointer type/);
      }
      {
        my $source = 'class MyClass extends MyClass {}';
        compile_not_ok($source, qr/The name of the parant class must be different from the name of the class/);
      }
      {
        my $source = ['class MyClass extends MyClass2 {}', 'class MyClass2 extends MyClass {}'];
        compile_not_ok($source, qr/The all super classes must be different from its own class. Recursive inheritance isn't allowed/);
      }
      {
        my $source = ['class MyClass extends MyParentClass { has x : int; }', 'class MyParentClass { has x : int; }'];
        compile_not_ok($source, qr/The field that name is the same as the field of the super class can't be defined/);
      }
    }
  }

  
  # Field definition
  {
    # mulnum_t
    {
      compile_not_ok_file('CompileError::MultiNumeric::FieldsZero');
      compile_not_ok_file('CompileError::MultiNumeric::Fields17');
      {
        my $source = 'class MyClass_2i : mulnum_t { static method foo : void () {} }';
        compile_not_ok($source, qr|The multi-numeric type can't have methods|);
      }
      {
        my $source = 'class MyClass_2i : mulnum_t { our $foo : int; }';
        compile_not_ok($source, qr|The multi-numeric type can't have class variables|);
      }
      {
        my $source = 'class MyClass_2i : mulnum_t { }';
        compile_not_ok($source, qr|The multi-numeric type must have at least one field|);
      }
    }
    # Access control
    {
      compile_not_ok_file('CompileError::Field::Private');
    }
    
    # Field name
    {
      compile_not_ok_file('CompileError::Field::HasFieldNameContainsUnderScoreTwice', qr/The symbol name "Foo__Bar" can't constain "__"/);
      compile_not_ok_file('CompileError::Field::HasFieldNameStartDigit',qr/Unexpected token "3f"/);
      {
        my $source = 'class MyClass { has foo::x : int; }';
        compile_not_ok($source, qr/The field name "foo::x" can't contain "::"/);
      }
    }
  }

  # Method definition
  {
    compile_not_ok_file('CompileError::Method::INIT', qr/"INIT" can't be used as a method name/);
    compile_not_ok_file('CompileError::Method::TooManyArguments', qr/Too many arguments/i);
    compile_not_ok_file('CompileError::Method::TooManyArgumentsMulnum'. qr/Too many arguments/i);
    
    # Method name
    {
      compile_not_ok_file('CompileError::Method::MethodNameStartDigit', qr/Unexpected token "3f"/);
      compile_not_ok_file('CompileError::Method::MethodNameContainsUnderScoreTwice', qr/The symbol name "Foo__Bar" can't constain "__"/);
      {
        my $source = 'class MyClass { static method foo::main : void () { } }';
        compile_not_ok($source, qr/The method name "foo::main" can't contain "::"/);
      }
    }
    {
      my $source = 'class MyClass { static method main : void (); }';
      compile_not_ok($source, qr/The non-native method must have the block/);
    }

    # Destructor(DESTORY)
    {
      {
        my $source = 'class MyClass { static method DESTROY : void () { } }';
        compile_not_ok($source, qr/\QThe DESTROY destructor method must be an instance method/);
      }
      {
        my $source = 'class MyClass { method DESTROY : int () { } }';
        compile_not_ok($source, qr/\QThe return type of the DESTROY destructor method must be the void type/);
      }
      {
        my $source = 'class MyClass { method DESTROY : void ($num : int) { } }';
        compile_not_ok($source, qr/\QThe DESTROY destructor method can't have arguments/);
      }
    }

    # Optional argument
    {
      {
        my $source = 'class MyClass { static method foo : void ($args0 = Int->new(1) : int) { } }';
        compile_not_ok($source, qr/The default value of the optional argument "\$args0" must be a constant value/);
      }
      {
        my $source = 'class MyClass { static method foo : void ($args0 = 0.3 : float) { } }';
        compile_not_ok($source, qr/The default value of the optional argument "\$args0" must be able to assigned to its argument/);
      }
      {
        my $source = 'class MyClass { static method foo : void ($args0 = "abc" : object) { } }';
        compile_not_ok($source, qr/The default value of the optional argument "\$args0" must be undef/);
      }
      {
        my $source = 'class MyClass { static method foo : void ($args0 = undef : int*) { } }';
        compile_not_ok($source, qr/The types other than the numeric type and the object type can't be an optional argument/);
      }
      {
        my $source = 'class MyClass { use Complex_2d; static method foo : void ($args0 = 0 : Complex_2d) { } }';
        compile_not_ok($source, qr/The types other than the numeric type and the object type can't be an optional argument/);
      }
      {
        my $source = 'class MyClass { static method foo : void ($args0 = 0 : int, $args1 : int) { } }';
        compile_not_ok($source, qr/The argument after optional arguments must be an optional argument/);
      }
    }
  }

  # Enumeration definition
  {
    compile_not_ok_file('CompileError::Enum::PrivateAccess', qr/Can't call the private method "TestCase::Enum->PRIVATE_VALUE"/);
    {
      my $source = q|class MyClass { interface_t enum { ONE } }|;
      compile_not_ok($source, qr/Invalid enumeration descriptor "interface_t"/);
    }
    {
      my $source = q|class MyClass { public private enum { ONE } }|;
      compile_not_ok($source, qr/Only one of enumeration descriptors "private" or "public" can be specified/);
    }
  }
}

done_testing;

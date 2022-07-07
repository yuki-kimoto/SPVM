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
  
  # Class name
  {
    compile_not_ok_file('CompileError::Class::ClassNameDifferntFromModuleName', qr/The class name "ClassNameDifferntFromModuleNameXXXXXXX" must be "CompileError::Class::ClassNameDifferntFromModuleName"/);
    compile_not_ok_file('CompileError::Class::classPartNameStartWithLowerCase', qr/The part names of the class "CompileError::Class::classPartNameStartWithLowerCase" must begin with a upper case character/);
    compile_not_ok_file('foo', qr/The class name "foo" must begin with a upper case character/);
    compile_not_ok_file('4foo', qr/The class name "4foo" can't begin with a number/);
    {
      my $source = 'class MyClass:: { static method main : void () {} }';
      compile_not_ok($source, qr|The class name "MyClass::" can't end with "::"|);
    }
    {
      my $source = 'class ::MyClass { static method main : void () {} }';
      compile_not_ok($source, qr|The class name "::MyClass" can't begin with "::"|);
    }
    {
      my $source = 'class MyClass::::Foo { static method main : void () {} }';
      compile_not_ok($source, qr|The class name "MyClass::::Foo" can't contains "::::"|);
    }
  }
  
  # Class descriptor
  {
    {
      my $source = 'class MyClass : pointer_t { has x : int; }';
      compile_not_ok($source, qr|The class that has "pointer_t" descriptor can't have its fields|);
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
    compile_not_ok_file('CompileError::Interface::ArrayElementCantAssign', qr/List to Stringable/i);
    compile_not_ok_file('CompileError::Interface::NotHaveInterfaceMethod', qr/CompileError::Interface::NotHaveInterfaceMethod.+to_string.*string\(self\).+interface.+Stringable/i);
    compile_not_ok_file('CompileError::Interface::NoMethods', qr/one required method/i);
    compile_not_ok_file('CompileError::Interface::MultiRequiredMethods', qr/multiple required method/i);
    compile_not_ok_file('CompileError::Interface::HasImplNotFound', qr/interface.+TestCase::Pointable.+the method declaration.+not_found/i);
  }

  # Class variable difinition
  {
    # Access control
    compile_not_ok_file('CompileError::ClassVar::Private');
    
    # Class variable name
    {
      compile_not_ok_file('CompileError::ClassVar::OurClassVarNameStartDigit', qr/The symbol name part of the variable name "\$3foo" can't begin with a number/);
      compile_not_ok_file('CompileError::ClassVar::OurClassVarNameInvalidColon', qr/Unexpected token ":"/);
      compile_not_ok_file('CompileError::ClassVar::OurClassVarNameEndColon2', qr/The variable name "\$FOO::" can't end with "::"/);
      compile_not_ok_file('CompileError::ClassVar::OurClassVarNameContainsUnderScoreTwice', qr/The variable name "\$Foo__Bar" can't contain "__"/);
      compile_not_ok_file('CompileError::ClassVar::OurClassVarNameColon2Twice', qr/The variable name "\$FOO::::BAR" can't contain "::::"/);
      {
        my $source = 'class MyClass { our $NAME : int; static method main : void () { ${NAME = 1; } }';
        compile_not_ok($source, qr/Need a closing brace "}" at the end of the variable name/);
      }
      {
        my $source = 'class MyClass { our $MyClass::NAME : int; static method main : void () {  } }';
        compile_not_ok($source, qr/The class varaible name "\$MyClass::NAME" in the class variable definition can't contain "::"/);
      }
      {
        my $source = 'class MyClass { our $FOO : required int; }';
        compile_not_ok($source, qr/Invalid class variable descriptor "required"/);
      }
      {
        my $source = 'class MyClass { our $FOO : public private int; }';
        compile_not_ok($source, qr/Only one of "private" or "public" class variable descriptors can be specified/);
      }
      {
        my $source = 'class MyClass { our $FOO : int; our $FOO : int; }';
        compile_not_ok($source, qr/Redeclaration of the class variable "\$FOO" in the class "MyClass"/);
      }
    }
    
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
        compile_not_ok($source, qr|The class that has the "mulnum_t" class descriptor can't have methods|);
      }
      {
        my $source = 'class MyClass_2i : mulnum_t { our $foo : int; }';
        compile_not_ok($source, qr|The class that has the "mulnum_t" class descriptor can't have class variables|);
      }
      {
        my $source = 'class MyClass_2i : mulnum_t { }';
        compile_not_ok($source, qr|The class that has the "mulnum_t" class descriptor must have at least one field|);
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
    compile_not_ok_file('CompileError::Method::INIT');
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
      compile_not_ok($source, qr/Non-native method must have its block/);
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
      compile_not_ok($source, qr/Only one of "private" or "public" enumeration descriptors can be specified/);
    }
  }
}

# Local variable
{
  # Local variable name
  {
    compile_not_ok_file('CompileError::LocalVar::LocalVarNameStartDigit', qr/The symbol name part of the variable name "\$3foo" can't begin with a number/);
    compile_not_ok_file('CompileError::LocalVar::LocalVarNameInvalidColon', qr/Unknown class "BAR"/);
    compile_not_ok_file('CompileError::LocalVar::LocalVarNameEndColon2', qr/The variable name "\$FOO::" can't end with "::"/);
    compile_not_ok_file('CompileError::LocalVar::LocalVarNameContainsUnderScoreTwice', qr/The variable name "\$Foo__Bar" can't contain "__"/);
    compile_not_ok_file('CompileError::LocalVar::LocalVarNameColon2Twice', qr/The variable name "\$FOO::::BAR" can't contain "::::"/);
    {
      my $source = 'class MyClass { static method main : void () { my ${name : int; } }';
      compile_not_ok($source, qr/Need a closing brace "}"/);
    }
    {
      my $source = 'class MyClass { static method main : void () { my $Foo::name : int; } }';
      compile_not_ok($source, qr/The local variable "\$Foo::name" can't contain "::"/);
    }
  }
}

done_testing;

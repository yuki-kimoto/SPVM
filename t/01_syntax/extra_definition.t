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

# Class
{
  # Module attribute
  {
    {
      my $source = 'class MyClass : pointer { has x : int; }';
      compile_ok($source);
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
    compile_ok_file('CompileError::Interface::HaveBlock');
    compile_ok_file('CompileError::Interface::NativeMethod');
    compile_ok_file('CompileError::Interface::StaticMethod');
    compile_not_ok_file('CompileError::Interface::ArrayElementCantAssign');
    compile_ok_file('CompileError::Interface::NoMethods');
    compile_not_ok_file('CompileError::Interface::HasImplNotFound');
  }
  # Class variable difinition
  {
    # Access control
    compile_not_ok_file('CompileError::ClassVar::Private');
    
    # Inheritance - extends syntax
    {
      {
        my $source = 'class MyClass extends Stringable {}';
        compile_not_ok($source);
      }
      {
        my $source = ['class MyClass extends PointerType {}', 'class PointerType : pointer {}'];
        compile_ok($source);
      }
      {
        my $source = 'class MyClass extends MyClass {}';
        compile_not_ok($source);
      }
      {
        my $source = ['class MyClass extends MyClass2 {}', 'class MyClass2 extends MyClass {}'];
        compile_not_ok($source);
      }
      {
        my $source = ['class MyClass extends MyParentClass { has x : long; }', 'class MyParentClass { has x : int; }'];
        compile_not_ok($source);
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
        compile_not_ok($source);
      }
      {
        my $source = 'class MyClass_2i : mulnum_t { our $foo : int; }';
        compile_not_ok($source);
      }
      {
        my $source = 'class MyClass_2i : mulnum_t { }';
        compile_not_ok($source);
      }
    }
    # Access control
    {
      compile_not_ok_file('CompileError::Field::Private');
    }
    
    # Field name
    {
      compile_not_ok_file('CompileError::Field::HasFieldNameContainsUnderScoreTwice');
      compile_not_ok_file('CompileError::Field::HasFieldNameStartDigit');
      {
        my $source = 'class MyClass { has foo::x : int; }';
        compile_not_ok($source);
      }
    }
  }

  # Method definition
  {
    compile_not_ok_file('CompileError::Method::INIT');
    compile_not_ok_file('CompileError::Method::TooManyArguments');
    compile_not_ok_file('CompileError::Method::TooManyArgumentsMulnum');
    
    # Method name
    {
      compile_not_ok_file('CompileError::Method::MethodNameStartDigit');
      compile_not_ok_file('CompileError::Method::MethodNameContainsUnderScoreTwice');
      {
        my $source = 'class MyClass { static method foo::main : void () { } }';
        compile_not_ok($source);
      }
    }
    {
      my $source = 'class MyClass { static method main : void (); }';
      compile_not_ok($source);
    }
    # Destructor(DESTORY)
    {
      {
        my $source = 'class MyClass { static method DESTROY : void () { } }';
        compile_not_ok($source);
      }
      {
        my $source = 'class MyClass { method DESTROY : int () { } }';
        compile_not_ok($source);
      }
      {
        my $source = 'class MyClass { method DESTROY : void ($num : int) { } }';
        compile_not_ok($source);
      }
    }

    # Optional argument
    {
      {
        my $source = 'class MyClass { static method foo : void ($args0 : int = Int->new(1)) { } }';
        compile_not_ok($source);
      }
      
      {
        my $source = 'class MyClass { static method foo : void ($args0 : float = 0.3) { } }';
        compile_ok($source);
      }
      {
        my $source = 'class MyClass { static method foo : void ($args0 : object = "abc") { } }';
        compile_not_ok($source);
      }
      {
        my $source = 'class MyClass { static method foo : void ($args0 : int* = undef) { } }';
        compile_not_ok($source);
      }
      {
        my $source = 'class MyClass { use Complex_2d; static method foo : void ($args0 : Complex_2d = 0) { } }';
        compile_not_ok($source);
      }
      {
        my $source = 'class MyClass { static method foo : void ($args0 : int = 0, $args1 : int) { } }';
        compile_not_ok($source);
      }
    }
  }

  # Enumeration definition
  {
    compile_not_ok_file('CompileError::Enum::PrivateAccess');
    {
      my $source = q|class MyClass { interface_t enum { ONE } }|;
      compile_not_ok($source);
    }
    {
      my $source = q|class MyClass { public private enum { ONE } }|;
      compile_not_ok($source);
    }
  }

  # Inherit the interface of the parent class
  {
    {
      {
        my $source = [
          'class MyClass extends MyClass::Parent {}',
          'class MyClass::Parent { interface MyClass::Interface; method has_interfaces : int () { return 1; } }',
          'class MyClass::Interface : interface_t { required method has_interfaces : int (); }',
        ];
        compile_ok($source);
      }
    }
  }

  # Search the non-existant parent field
  {
    {
      {
        my $source = [
          'class MyClass extends MyClass::Parent { static method main : int () { my $self = new MyClass; $self->{foo}; }}',
          'class MyClass::Parent { }',
        ];
        compile_not_ok($source);
      }
    }
  }

  # Search the non-existant parent method
  {
    {
      {
        my $source = [
          'class MyClass::Socket::INET extends MyClass::Socket {static method new : MyClass::Socket::INET ($optMyClassns : object[] = undef) { my $self = new MyClass::Socket::INET; $self->blocking; }}',
          'class MyClass::Socket extends MyClass::Handle {}',
          'class MyClass::Handle { has blocking : ro int;}',
        ];
        compile_ok($source);
      }
      {
        my $source = [
          'class MyClass::Socket::INET extends MyClass::Socket {static method new : MyClass::Socket::INET ($optMyClassns : object[] = undef) { my $self = new MyClass::Socket::INET; $self->blocking; }}',
          'class MyClass::Socket extends MyClass::Handle {}',
          'class MyClass::Handle { }',
        ];
        compile_not_ok($source);
      }
    }
  }
  
  # Segmentation fault https://github.com/yuki-kimoto/SPVM/issues/305, but Segmentation fault doesn't occur by this code.
  {
    my $source = [
      'class MyClass { static method main : int () { my $test_dir = "test"; my $sep = (string)undef; if (1) { $sep = "\\\\"; } else { $sep = "/"; } my $file = "$test_dir$sepfoo.txt"; } }',
    ];
    compile_not_ok($source);
  }

  # Segmentation fault https://github.com/yuki-kimoto/SPVM/issues/303, but Segmentation fault doesn't occur by this code.
  {
    my $source = [
      'class MyClass { use Point; static method main : int () { Point->not_found; } }',
    ];
    compile_not_ok($source);
  }
}

done_testing;

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
  
  my $status_code = $builder->compile_spvm($class_name, $file, $line);
  ok($status_code == 0);
  my $error_messages = $builder->get_error_messages;
  my $first_error_message = $error_messages->[0];
  my $message_ok;
  if ($error_message_re) {
    $message_ok = like($first_error_message, $error_message_re);
  }
  
  if ($status_code != 0 || ($error_message_re && !$message_ok)) {
    warn "  at $file line $line\n";
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

# Syntax
{
  compile_not_ok_file('TestCase::CompileError::Syntax::LineNumber', qr/our.*\b8:3\b/i);
}

# Symbol name
{
  # A symbol name can't conatain "__"
  {
    my $source = 'class Tmp { use Int as Foo__Bar; static method main : void () { } }';
    compile_not_ok($source, qr/\QThe symbol name "Foo__Bar" can't constain "__"/);
  }

  # A symbol name can't end with "::"
  {
    my $source = 'class Tmp { use Int as Foo::; static method main : void () { } }';
    compile_not_ok($source, qr/\QThe symbol name "Foo::" can't end with "::"/);
  }

  # A symbol name can't contains "::::".
  {
    my $source = 'class Tmp { use Int as Foo::::Bar; static method main : void () { } }';
    compile_not_ok($source, qr/\QThe symbol name "Foo::::Bar" can't contains "::::"/);
  }
}

# Fat comma
{
  # The string literal of the left operand of the fat camma can't contains "::".
  {
    my $source = 'class Tmp { static method main : void () { {Foo::Bar => 1}; } }';
    compile_not_ok($source, qr/\QThe string literal "Foo::Bar" of the left operand of the fat camma can't contains "::"/);
  }
}

# Class
{
  # Syntax
  {
    compile_not_ok_file('TestCase::CompileError::Class::NotClosed');
    {
      my $source = 'class Tmp { static method main : void () {} } class Tmp2 { static method main : void () {} }';
      compile_not_ok($source, qr/Unexpected token "class"/);
    }
  }
  
  # Class name
  {
    compile_not_ok_file('TestCase::CompileError::Class::ClassNameDifferntFromModuleName', qr/The class name "ClassNameDifferntFromModuleNameXXXXXXX" must be "TestCase::CompileError::Class::ClassNameDifferntFromModuleName"/);
    compile_not_ok_file('TestCase::CompileError::Class::classPartNameStartWithLowerCase', qr/The part names of the class "TestCase::CompileError::Class::classPartNameStartWithLowerCase" must begin with a upper case character/);
    compile_not_ok_file('foo', qr/The class name "foo" must begin with a upper case character/);
    compile_not_ok_file('4foo', qr/The class name "4foo" can't begin with a number/);
    {
      my $source = 'class Tmp:: { static method main : void () {} }';
      compile_not_ok($source, qr|The class name "Tmp::" can't end with "::"|);
    }
    {
      my $source = 'class ::Tmp { static method main : void () {} }';
      compile_not_ok($source, qr|The class name "::Tmp" can't begin with "::"|);
    }
    {
      my $source = 'class Tmp::::Foo { static method main : void () {} }';
      compile_not_ok($source, qr|The class name "Tmp::::Foo" can't contains "::::"|);
    }
  }
  
  # Class descriptor
  {
    {
      my $source = 'class Tmp : pointer_t { has x : int; }';
      compile_not_ok($source, qr|The class that has "pointer_t" descriptor can't have its fields|);
    }
  }
  
  # use
  {
    compile_not_ok_file('TestCase::CompileError::Use::ImportMethodNotFound');
    compile_not_ok_file('TestCase::CompileError::Use::AliasStartsLowerCase');
    compile_not_ok_file('TestCase::CompileError::Use::AliasDuplication');
  }

  # Interface
  {
    compile_not_ok_file('TestCase::CompileError::Interface::HaveBlock', qr/interface.+block/i);
    compile_not_ok_file('TestCase::CompileError::Interface::NativeMethod', qr/interface.+native/i);
    compile_not_ok_file('TestCase::CompileError::Interface::StaticMethod', qr/interface.+instance/i);
    compile_not_ok_file('TestCase::CompileError::Interface::ArrayElementCantAssign', qr/List to Stringable/i);
    compile_not_ok_file('TestCase::CompileError::Interface::NotHaveInterfaceMethod', qr/TestCase::CompileError::Interface::NotHaveInterfaceMethod.+to_string.*string\(self\).+interface.+Stringable/i);
    compile_not_ok_file('TestCase::CompileError::Interface::NoMethods', qr/one required method/i);
    compile_not_ok_file('TestCase::CompileError::Interface::MultiRequiredMethods', qr/multiple required method/i);
    compile_not_ok_file('TestCase::CompileError::Interface::HasImplNotFound', qr/interface.+TestCase::Pointable.+the method declaration.+not_found/i);
  }

  # Class variable difinition
  {
    # Access control
    compile_not_ok_file('TestCase::CompileError::ClassVar::Private');
    
    # Class variable name
    {
      compile_not_ok_file('TestCase::CompileError::ClassVar::OurClassVarNameStartDigit', qr/The symbol name part of the variable name "\$3foo" can't begin with a number/);
      compile_not_ok_file('TestCase::CompileError::ClassVar::OurClassVarNameInvalidColon', qr/Unexpected token ":"/);
      compile_not_ok_file('TestCase::CompileError::ClassVar::OurClassVarNameEndColon2', qr/The variable name "\$FOO::" can't end with "::"/);
      compile_not_ok_file('TestCase::CompileError::ClassVar::OurClassVarNameContainsUnderScoreTwice', qr/The variable name "\$Foo__Bar" can't contain "__"/);
      compile_not_ok_file('TestCase::CompileError::ClassVar::OurClassVarNameColon2Twice', qr/The variable name "\$FOO::::BAR" can't contain "::::"/);
      {
        my $source = 'class Tmp { our $NAME : int; static method main : void () { ${NAME = 1; } }';
        compile_not_ok($source, qr/Need a closing brace "}" at the end of the variable name/);
      }
      {
        my $source = 'class Tmp { our $Tmp::NAME : int; static method main : void () {  } }';
        compile_not_ok($source, qr/The class varaible name "\$Tmp::NAME" in the class variable definition can't contain "::"/);
      }
      {
        my $source = 'class Tmp { our $FOO : required int; }';
        compile_not_ok($source, qr/Invalid class variable descriptor "required"/);
      }
      {
        my $source = 'class Tmp { our $FOO : public private int; }';
        compile_not_ok($source, qr/Only one of "private", "protected", or "public" class variable descriptors can be specified/);
      }
      {
        my $source = 'class Tmp { our $FOO : int; our $FOO : int; }';
        compile_not_ok($source, qr/Redeclaration of the class variable "\$FOO" in the class "Tmp"/);
      }
    }
  }

  
  # Field definition
  {
    # mulnum_t
    {
      compile_not_ok_file('TestCase::CompileError::MultiNumeric::FieldsZero');
      compile_not_ok_file('TestCase::CompileError::MultiNumeric::Fields17');
      {
        my $source = 'class Tmp_2i : mulnum_t { static method foo : void () {} }';
        compile_not_ok($source, qr|The class that has the "mulnum_t" class descriptor can't have methods|);
      }
      {
        my $source = 'class Tmp_2i : mulnum_t { our $foo : int; }';
        compile_not_ok($source, qr|The class that has the "mulnum_t" class descriptor can't have class variables|);
      }
      {
        my $source = 'class Tmp_2i : mulnum_t { }';
        compile_not_ok($source, qr|The class that has the "mulnum_t" class descriptor must have at least one field|);
      }
    }
    # Access control
    {
      compile_not_ok_file('TestCase::CompileError::Field::Private');
    }
    
    # Field name
    {
      compile_not_ok_file('TestCase::CompileError::Field::HasFieldNameContainsUnderScoreTwice', qr/The symbol name "Foo__Bar" can't constain "__"/);
      compile_not_ok_file('TestCase::CompileError::Field::HasFieldNameStartDigit',qr/Unexpected token "3f"/);
      {
        my $source = 'class Tmp { has foo::x : int; }';
        compile_not_ok($source, qr/The field name "foo::x" can't contain "::"/);
      }
    }
  }

  # Method definition
  {
    compile_not_ok_file('TestCase::CompileError::Method::INIT');
    compile_not_ok_file('TestCase::CompileError::Method::TooManyArguments', qr/Too many arguments/i);
    compile_not_ok_file('TestCase::CompileError::Method::TooManyArgumentsMulnum'. qr/Too many arguments/i);
    
    # Method name
    {
      compile_not_ok_file('TestCase::CompileError::Method::MethodNameStartDigit', qr/Unexpected token "3f"/);
      compile_not_ok_file('TestCase::CompileError::Method::MethodNameContainsUnderScoreTwice', qr/The symbol name "Foo__Bar" can't constain "__"/);
      {
        my $source = 'class Tmp { static method foo::main : void () { } }';
        compile_not_ok($source, qr/The method name "foo::main" can't contain "::"/);
      }
    }
  }

  # Enumeration definition
  {
    compile_not_ok_file('TestCase::CompileError::Enum::PrivateAccess', qr/Can't call the private method "TestCase::Enum->PRIVATE_VALUE"/);
    {
      my $source = q|class Tmp { interface_t enum { ONE } }|;
      compile_not_ok($source, qr/Invalid enumeration descriptor "interface_t"/);
    }
    {
      my $source = q|class Tmp { public private enum { ONE } }|;
      compile_not_ok($source, qr/Only one of "private", "protected", or "public" enumeration descriptors can be specified/);
    }
  }
}

# Local variable
{
  # Local variable name
  {
    compile_not_ok_file('TestCase::CompileError::LocalVar::LocalVarNameStartDigit', qr/The symbol name part of the variable name "\$3foo" can't begin with a number/);
    compile_not_ok_file('TestCase::CompileError::LocalVar::LocalVarNameInvalidColon', qr/Unknown class "BAR"/);
    compile_not_ok_file('TestCase::CompileError::LocalVar::LocalVarNameEndColon2', qr/The variable name "\$FOO::" can't end with "::"/);
    compile_not_ok_file('TestCase::CompileError::LocalVar::LocalVarNameContainsUnderScoreTwice', qr/The variable name "\$Foo__Bar" can't contain "__"/);
    compile_not_ok_file('TestCase::CompileError::LocalVar::LocalVarNameColon2Twice', qr/The variable name "\$FOO::::BAR" can't contain "::::"/);
    {
      my $source = 'class Tmp { static method main : void () { my ${name : int; } }';
      compile_not_ok($source, qr/Need a closing brace "}"/);
    }
    {
      my $source = 'class Tmp { static method main : void () { my $Foo::name : int; } }';
      compile_not_ok($source, qr/The local variable "\$Foo::name" can't contain "::"/);
    }
  }
}

done_testing;

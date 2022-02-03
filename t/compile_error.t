use strict;
use warnings;
use utf8;
use Data::Dumper;
use File::Basename 'basename';
use FindBin;

use SPVM::Builder;

use Test::More;

my $file = 't/' . basename $0;

use FindBin;
use lib "$FindBin::Bin/default/lib";

# SPVM compile error
{
  my $command = "$^X -Mblib $FindBin::Bin/compile_error.pl 2>&1";
  my $output = `$command 2>&1`;
  like($output, qr/CompileError/);
}

# SPVM dist compile error
{
  my $command = "$^X -Mblib $FindBin::Bin/compile_error_dist.pl 2>&1";
  my $output = `$command 2>&1`;
  like($output, qr/CompileError/);
}

sub print_error_messages {
  my ($builder) = @_;
  
  my $error_messages = $builder->get_error_messages;
  
  for my $error_message (@$error_messages) {
    print STDERR "[CompileError]$error_message\n";
  }
}

# Class
{
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::Class::ClassNameDifferntFromModuleName', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::Class::classPartNameStartWithLowerCase', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('foo', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('4foo', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
}

# Pakcage name must start SPVM::
{
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('ClassNameCompileError', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
}

# use
{
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::Use::ImportMethodNotFound', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::Use::AliasStartsLowerCase', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::Use::AliasDuplication', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
}

# Logical operator
{
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::LogicalOperator::AndNotExpression', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::LogicalOperator::OrNotExpression', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::LogicalOperator::NotNotExpression', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
}

# oarray
{
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::OArray::AssignNumeric', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::OArray::AssignNumericArray', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
}

# Literal
{
  # Caharater
  {
    {
      
      my $builder = SPVM::Builder->new;
      my $success = $builder->compile_spvm('TestCase::CompileError::Literal::Character::InvalidCharacterLiteralEmpty', __FILE__, __LINE__);
      ok($success == 0);
    print_error_messages($builder);
    }
    {
      
      my $builder = SPVM::Builder->new;
      my $success = $builder->compile_spvm('TestCase::CompileError::Literal::Character::InvalidCharacterLiteral', __FILE__, __LINE__);
      ok($success == 0);
    print_error_messages($builder);
    }
    {
      my $builder = SPVM::Builder->new;
      my $success = $builder->compile_spvm('TestCase::CompileError::Literal::Character::NotEnd', __FILE__, __LINE__);
      ok($success == 0);
    print_error_messages($builder);
    }
    {
      my $builder = SPVM::Builder->new;
      my $success = $builder->compile_spvm('TestCase::CompileError::Literal::Character::InvalidHexAscii1', __FILE__, __LINE__);
      ok($success == 0);
    print_error_messages($builder);
    }
    {
      my $builder = SPVM::Builder->new;
      my $success = $builder->compile_spvm('TestCase::CompileError::Literal::Character::InvalidHexAscii2', __FILE__, __LINE__);
      ok($success == 0);
    print_error_messages($builder);
    }
  }
  # Integer
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::Literal::Integer::IntOutOfRange', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
}

# Lexcarl Variable
{
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::LexVar::LexVarNameStartDigit', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::LexVar::LexVarNameInvalidColon', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::LexVar::LexVarNameEndColon2', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::LexVar::LexVarNameContainsUnderScoreTwice', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::LexVar::LexVarNameColon2Twice', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
}

# Class Variable
{
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::ClassVar::Private', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::ClassVar::OurClassVarNameStartDigit', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::ClassVar::OurClassVarNameInvalidColon', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::ClassVar::OurClassVarNameEndColon2', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::ClassVar::OurClassVarNameContainsUnderScoreTwice', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::ClassVar::OurClassVarNameColon2Twice', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
}

# Method
{
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::Method::Begin', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::Method::MethodNameStartDigit', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::Method::MethodNameContainsUnderScoreTwice', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
}

# Field
{
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::Field::Private', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::Field::HasFieldNameContainsUnderScoreTwice', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::Field::HasFieldNameStartDigit', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
}


# Enum
{
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::Enum::PrivateAccess', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
}

# Call sub
{
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::Switch::NoLastBreak', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
}

# Value
{
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::Value::FieldsZero', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }

  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::Value::Fields17', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
}

# Call method
{
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::CallMethod::NotFound', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::CallMethod::ClassNotFound', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
}

# Assign
{
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::Assign::StringToBytArray', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }

  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::Assign::DifferentObject', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::Assign::ConstToNoConst', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::Assign::NotNumericToNumeric', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::Assign::NarrwoingConvertionIntToByte', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::Assign::NarrwoingConvertionIntToShort', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::Assign::NarrwoingConvertionLongToByte', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::Assign::NarrwoingConvertionLongToInt', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::Assign::NarrwoingConvertionLongToShort', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::Assign::UnboxingDifferentType', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::Assign::BoxingDifferentType', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
}

# Remainder
{
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::Remainder::RightIsNotIntegral', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::Remainder::LeftIsNotIntegral', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
}

# String
{
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::String::CharacterAssign', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }

  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::String::AssignNonMutableToMutable', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
}
# Weaken
{
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::Weaken::HashNotObject', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::Weaken::ArrayNotObject', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
}
# Comparison operator
{
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::ComparisonOperator::GtNotNumeric', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::ComparisonOperator::GeNotNumeric', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::ComparisonOperator::LtNotNumeric', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::ComparisonOperator::LeNotNumeric', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
}

# Bool
{
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::Bool::NotNumericObject', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
}

# isa
{
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::Isa::LeftIsNotObject', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
}

{
  my $builder = SPVM::Builder->new;
  my $success = $builder->compile_spvm('TestCase::CompileError::InvalidType', __FILE__, __LINE__);
  ok($success == 0);
    print_error_messages($builder);
}

{
  my $builder = SPVM::Builder->new;
  my $success = $builder->compile_spvm('TestCase::CompileError::TypeCantBeDetectedUndef', __FILE__, __LINE__);
  ok($success == 0);
    print_error_messages($builder);
}

{
  my $builder = SPVM::Builder->new;
  my $success = $builder->compile_spvm('TestCase::CompileError::TypeCantBeDetectedUndefDefault', __FILE__, __LINE__);
  ok($success == 0);
    print_error_messages($builder);
}

{
  my $builder = SPVM::Builder->new;
  my $success = $builder->compile_spvm('TestCase::CompileError::New::Private', __FILE__, __LINE__);
  ok($success == 0);
    print_error_messages($builder);
}

# Convert
{
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::Convert::ConvertFromByteArrayToString', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::Convert::ConvertFromStringToByteArray', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::Convert::ConvertToRef', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }

  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::Convert::ConvertFromRef', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }

  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::Convert::ConvertFromValueType', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
}

# Concat
{
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::Concat::RightIsNotString', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
  {
    my $builder = SPVM::Builder->new;
    my $success = $builder->compile_spvm('TestCase::CompileError::Concat::LeftIsNotString', __FILE__, __LINE__);
    ok($success == 0);
    print_error_messages($builder);
  }
}

done_testing;

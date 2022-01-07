use strict;
use warnings;
use utf8;
use Data::Dumper;
use File::Basename 'basename';
use FindBin;

use SPVM::Builder;

use Test::More 'no_plan';

my $file = 't/' . basename $0;

use FindBin;
use lib "$FindBin::Bin/lib";

# Class
{
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::Class::ClassNameDifferntFromModuleName', __FILE__, __LINE__);
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::Class::classPartNameStartWithLowerCase', __FILE__, __LINE__);
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('foo', __FILE__, __LINE__);
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('4foo', __FILE__, __LINE__);
    ok($success == 0);
  }
}

# Pakcage name must start SPVM::
{
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('ClassNameCompileError', __FILE__, __LINE__);
    ok($success == 0);
  }
}

# use
{
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::Use::ImportMethodNotFound', __FILE__, __LINE__);
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::Use::AliasStartsLowerCase', __FILE__, __LINE__);
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::Use::AliasDuplication', __FILE__, __LINE__);
    ok($success == 0);
  }
}

# Logical operator
{
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::LogicalOperator::AndNotExpression', __FILE__, __LINE__);
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::LogicalOperator::OrNotExpression', __FILE__, __LINE__);
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::LogicalOperator::NotNotExpression', __FILE__, __LINE__);
    ok($success == 0);
  }
}

# oarray
{
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::OArray::AssignNumeric', __FILE__, __LINE__);
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::OArray::AssignNumericArray', __FILE__, __LINE__);
    ok($success == 0);
  }
}

# Literal
{
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::Literal::Character::InvalidCharacterLiteralEmpty', __FILE__, __LINE__);
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::Literal::Character::InvalidCharacterLiteral', __FILE__, __LINE__);
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::Literal::Integer::IntOutOfRange', __FILE__, __LINE__);
    ok($success == 0);
  }
}


# Lexcarl Variable
{
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::LexVar::LexVarNameStartDigit', __FILE__, __LINE__);
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::LexVar::LexVarNameInvalidColon', __FILE__, __LINE__);
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::LexVar::LexVarNameEndColon2', __FILE__, __LINE__);
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::LexVar::LexVarNameContainsUnderScoreTwice', __FILE__, __LINE__);
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::LexVar::LexVarNameColon2Twice', __FILE__, __LINE__);
    ok($success == 0);
  }
}

# Class Variable
{
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::ClassVar::Private', __FILE__, __LINE__);
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::ClassVar::OurClassVarNameStartDigit', __FILE__, __LINE__);
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::ClassVar::OurClassVarNameInvalidColon', __FILE__, __LINE__);
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::ClassVar::OurClassVarNameEndColon2', __FILE__, __LINE__);
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::ClassVar::OurClassVarNameContainsUnderScoreTwice', __FILE__, __LINE__);
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::ClassVar::OurClassVarNameColon2Twice', __FILE__, __LINE__);
    ok($success == 0);
  }
}

# Method
{
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::Method::Begin', __FILE__, __LINE__);
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::Method::MethodNameStartDigit', __FILE__, __LINE__);
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::Method::MethodNameContainsUnderScoreTwice', __FILE__, __LINE__);
    ok($success == 0);
  }
}

# Field
{
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::Field::Private', __FILE__, __LINE__);
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::Field::HasFieldNameContainsUnderScoreTwice', __FILE__, __LINE__);
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::Field::HasFieldNameStartDigit', __FILE__, __LINE__);
    ok($success == 0);
  }
}


# Enum
{
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::Enum::PrivateAccess', __FILE__, __LINE__);
    ok($success == 0);
  }
}

# Call sub
{
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::Switch::NoLastBreak', __FILE__, __LINE__);
    ok($success == 0);
  }
}

# Value
{
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::Value::FieldsZero', __FILE__, __LINE__);
    ok($success == 0);
  }

  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::Value::Fields17', __FILE__, __LINE__);
    ok($success == 0);
  }
}

# Call method
{
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::CallMethod::NotFound', __FILE__, __LINE__);
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::CallMethod::ClassNotFound', __FILE__, __LINE__);
    ok($success == 0);
  }
}

# Assign
{
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::Assign::StringToBytArray', __FILE__, __LINE__);
    ok($success == 0);
  }

  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::Assign::DifferentObject', __FILE__, __LINE__);
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::Assign::ConstToNoConst', __FILE__, __LINE__);
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::Assign::NotNumericToNumeric', __FILE__, __LINE__);
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::Assign::NarrwoingConvertionIntToByte', __FILE__, __LINE__);
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::Assign::NarrwoingConvertionIntToShort', __FILE__, __LINE__);
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::Assign::NarrwoingConvertionLongToByte', __FILE__, __LINE__);
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::Assign::NarrwoingConvertionLongToInt', __FILE__, __LINE__);
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::Assign::NarrwoingConvertionLongToShort', __FILE__, __LINE__);
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::Assign::UnboxingDifferentType', __FILE__, __LINE__);
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::Assign::BoxingDifferentType', __FILE__, __LINE__);
    ok($success == 0);
  }
}

# Remainder
{
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::Remainder::RightIsNotIntegral', __FILE__, __LINE__);
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::Remainder::LeftIsNotIntegral', __FILE__, __LINE__);
    ok($success == 0);
  }
}

# String
{
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::String::CharacterAssign', __FILE__, __LINE__);
    ok($success == 0);
  }
}
# Weaken
{
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::Weaken::HashNotObject', __FILE__, __LINE__);
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::Weaken::ArrayNotObject', __FILE__, __LINE__);
    ok($success == 0);
  }
}
# Comparison operator
{
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::ComparisonOperator::GtNotNumeric', __FILE__, __LINE__);
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::ComparisonOperator::GeNotNumeric', __FILE__, __LINE__);
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::ComparisonOperator::LtNotNumeric', __FILE__, __LINE__);
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::ComparisonOperator::LeNotNumeric', __FILE__, __LINE__);
    ok($success == 0);
  }
}

# Bool
{
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::Bool::NotNumericObject', __FILE__, __LINE__);
    ok($success == 0);
  }
}

# isa
{
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::Isa::LeftIsNotObject', __FILE__, __LINE__);
    ok($success == 0);
  }
}

{
  my $build = SPVM::Builder->new;
  my $success = $build->compile_spvm('TestCase::CompileError::InvalidType', __FILE__, __LINE__);
  ok($success == 0);
}

{
  my $build = SPVM::Builder->new;
  my $success = $build->compile_spvm('TestCase::CompileError::TypeCantBeDetectedUndef', __FILE__, __LINE__);
  ok($success == 0);
}

{
  my $build = SPVM::Builder->new;
  my $success = $build->compile_spvm('TestCase::CompileError::TypeCantBeDetectedUndefDefault', __FILE__, __LINE__);
  ok($success == 0);
}

{
  my $build = SPVM::Builder->new;
  my $success = $build->compile_spvm('TestCase::CompileError::New::Private', __FILE__, __LINE__);
  ok($success == 0);
}

# Convert
{
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::Convert::ConvertFromByteArrayToString', __FILE__, __LINE__);
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::Convert::ConvertFromStringToByteArray', __FILE__, __LINE__);
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::Convert::ConvertToRef', __FILE__, __LINE__);
    ok($success == 0);
  }

  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::Convert::ConvertFromRef', __FILE__, __LINE__);
    ok($success == 0);
  }

  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::Convert::ConvertFromValueType', __FILE__, __LINE__);
    ok($success == 0);
  }
}

# Concat
{
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::Concat::RightIsNotString', __FILE__, __LINE__);
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    my $success = $build->compile_spvm('TestCase::CompileError::Concat::LeftIsNotString', __FILE__, __LINE__);
    ok($success == 0);
  }
}

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

# Package
{
  {
    my $build = SPVM::Builder->new;
    $build->use('foo');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    $build->use('4foo');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
}

# Sub
{
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::Sub::Begin');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::Sub::SubNameStartDigit');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::Sub::SubNameContainsUnderScoreTwice');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
}

# Field
{
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::Field::Private');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::Field::HasFieldNameContainsUnderScoreTwice');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::Field::HasFieldNameStartDigit');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
}

# Literal
{
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::Literal::InvalidCharacterLiteral');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::Literal::IntOutOfRange');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
}

# Enum
{
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::Enum::PrivateAccess');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
}

# Call sub
{
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::Switch::NoLastBreak');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
}

# Value
{
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::Value::FieldsZero');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }

  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::Value::Fields17');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
}

# Call sub
{
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::CallSub::NotFound');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
}

# Assign
{
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::Assign::StringToBytArray');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }

  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::Assign::DifferentObject');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::Assign::ConstToNoConst');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::Assign::NotNumericToNumeric');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::Assign::NarrwoingConvertionIntToByte');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::Assign::NarrwoingConvertionIntToShort');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::Assign::NarrwoingConvertionLongToByte');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::Assign::NarrwoingConvertionLongToInt');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::Assign::NarrwoingConvertionLongToShort');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::Assign::UnboxingDifferentType');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::Assign::BoxingDifferentType');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
}

# Remainder
{
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::Remainder::LeftIsNotNumeric');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
}

# String
{
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::String::CharacterAssign');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
}
# Weaken
{
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::Weaken::HashNotObject');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::Weaken::ArrayNotObject');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
}
# Comparison operator
{
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::ComparisonOperator::GtNotNumeric');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::ComparisonOperator::GeNotNumeric');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::ComparisonOperator::LtNotNumeric');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::ComparisonOperator::LeNotNumeric');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
}

# Bool
{
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::Bool::NotNumericObject');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
}

# isa
{
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::Isa::LeftIsNotObject');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
}

{
  my $build = SPVM::Builder->new;
  $build->use('TestCase::CompileError::InvalidType');
  my $success = $build->compile_spvm();
  ok($success == 0);
}

{
  my $build = SPVM::Builder->new;
  $build->use('TestCase::CompileError::TypeCantBeDetectedUndef');
  my $success = $build->compile_spvm();
  ok($success == 0);
}

{
  my $build = SPVM::Builder->new;
  $build->use('TestCase::CompileError::TypeCantBeDetectedUndefDefault');
  my $success = $build->compile_spvm();
  ok($success == 0);
}

{
  my $build = SPVM::Builder->new;
  $build->use('TestCase::CompileError::PackageVar::Private');
  my $success = $build->compile_spvm();
  ok($success == 0);
}

{
  my $build = SPVM::Builder->new;
  $build->use('TestCase::CompileError::New::Private');
  my $success = $build->compile_spvm();
  ok($success == 0);
}

# Convert
{
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::Convert::ConvertToRef');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }

  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::Convert::ConvertFromRef');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }

  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::Convert::ConvertFromValueType');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
}

# Concat
{
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::Concat::RightIsNotString');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::Concat::LeftIsNotString');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
}

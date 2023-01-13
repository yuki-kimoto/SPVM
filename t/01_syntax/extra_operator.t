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
# Call method
{
  compile_not_ok_file('CompileError::CallMethod::NotFound');
  compile_not_ok_file('CompileError::CallMethod::ClassNotFound',);
  {
    my $source = 'class Tmp { static method main : int () { my $num = 1; $num->foo; }  }';
    compile_not_ok($source);
  }
  {
    my $source = 'class Tmp { static method main : int () { &foo; } method foo : void () {} }';
    compile_not_ok($source);
  }
  {
    my $source = 'class Tmp { static method main : int () { my $object = new Tmp; $object->foo; } static method foo : void () {} }';
    compile_not_ok($source);
  }
}

# Assign
{
  compile_not_ok_file('CompileError::Assign::StringToBytArray');
  compile_not_ok_file('CompileError::Assign::DifferentObject');
  compile_not_ok_file('CompileError::Assign::ConstToNoConst');
  compile_not_ok_file('CompileError::Assign::NotNumericToNumeric');
  compile_not_ok_file('CompileError::Assign::NarrwoingConvertionIntToByte');
  compile_not_ok_file('CompileError::Assign::NarrwoingConvertionIntToShort');
  compile_not_ok_file('CompileError::Assign::NarrwoingConvertionLongToByte');
  compile_not_ok_file('CompileError::Assign::NarrwoingConvertionLongToInt');
  compile_not_ok_file('CompileError::Assign::NarrwoingConvertionLongToShort');
  compile_not_ok_file('CompileError::Assign::UnboxingDifferentType');
  compile_not_ok_file('CompileError::Assign::BoxingDifferentType');
}

# Remainder
{
  compile_not_ok_file('CompileError::Remainder::RightIsNotIntegral');
  compile_not_ok_file('CompileError::Remainder::LeftIsNotIntegral');
}


# isa
{
  compile_not_ok_file('CompileError::Isa::LeftIsNotObject');
}

# Convert
{
  compile_not_ok_file('CompileError::Convert::ConvertFromByteArrayToString');
  compile_not_ok_file('CompileError::Convert::ConvertFromStringToByteArray');
  compile_not_ok_file('CompileError::Convert::ConvertToRef');
  compile_not_ok_file('CompileError::Convert::ConvertFromRef');
  compile_not_ok_file('CompileError::Convert::ConvertFromMultiNumericType');
}

# Concat
{
  compile_not_ok_file('CompileError::Concat::RightIsNotString');
  compile_not_ok_file('CompileError::Concat::LeftIsNotString');
}

# Divide - Compile Error
{
  compile_not_ok_file('CompileError::Divide::LeftIsNotNumeric');
  compile_not_ok_file('CompileError::Divide::RightIsNotNumeric');
  compile_not_ok_file('CompileError::Divide::DivuiLeftIsNotInt');
  compile_not_ok_file('CompileError::Divide::DivuiRightIsNotInt');
  compile_not_ok_file('CompileError::Divide::DivulLeftIsNotLong');
  compile_not_ok_file('CompileError::Divide::DivulRightIsNotLong');
}


# Remainder - Compile Error
{
  compile_not_ok_file('CompileError::Remainder::LeftIsNotIntegral', qr/left.+%.+integer/);
  compile_not_ok_file('CompileError::Remainder::RightIsNotIntegral', qr/right.+%.+integer/);
  compile_not_ok_file('CompileError::Remainder::RemuiLeftIsNotInt', qr/left.+remui.+int/);
  compile_not_ok_file('CompileError::Remainder::RemuiRightIsNotInt', qr/right.+remui.+int/);
  compile_not_ok_file('CompileError::Remainder::RemulLeftIsNotLong', qr/left.+remul.+long/);
  compile_not_ok_file('CompileError::Remainder::RemulRightIsNotLong', qr/right.+remul.+long/);
}

# Weaken
{
  compile_not_ok_file('CompileError::Weaken::IsweakFieldNotObjectType', qr/isweak.*object/);
  compile_not_ok_file('CompileError::Weaken::UnweakenFieldNotObjectType', qr/unweaken.*object/);
  compile_not_ok_file('CompileError::Weaken::WeakenFieldNotObjectType', qr/weaken.*object/);
}

# Subtraction Operator
{
  # The beginning of the number is an integer literal
  {
    {
      my $source = 'class Tmp { static method main : void () { my $num = 0; $num-2; } }';
      compile_not_ok($source, qr/Unexpected token "-2"/);
    }
  }
}

# Comparison operator
{
  compile_not_ok_file('CompileError::ComparisonOperator::GtNotNumeric');
  compile_not_ok_file('CompileError::ComparisonOperator::GeNotNumeric');
  compile_not_ok_file('CompileError::ComparisonOperator::LtNotNumeric');
  compile_not_ok_file('CompileError::ComparisonOperator::LeNotNumeric');
}

# Add
{
  compile_not_ok_file('CompileError::Add::LeftIsNotNumeric');
  compile_not_ok_file('CompileError::Add::RightIsNotNumeric');
}

# Multiply
{
  compile_not_ok_file('CompileError::Multiply::LeftIsNotNumeric');
  compile_not_ok_file('CompileError::Multiply::RightIsNotNumeric');
}

# Subtract
{
  compile_not_ok_file('CompileError::Subtract::LeftIsNotNumeric');
  compile_not_ok_file('CompileError::Subtract::RightIsNotNumeric');
}


# Unary minus
{
  compile_not_ok_file('CompileError::UnaryMinus::NotNumeric');
}

# Unary plus
{
  compile_not_ok_file('CompileError::UnaryPlus::NotNumeric');
}

# New operator - new
{
  compile_not_ok_file('CompileError::New::Private');
}

# New operator - new
{
  compile_not_ok_file('CompileError::BitOperator::NotIntegral');
}

done_testing;

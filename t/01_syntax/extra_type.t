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

# Array of any object - object[]
{
  compile_not_ok_file('CompileError::OArray::AssignNumeric');
  compile_not_ok_file('CompileError::OArray::AssignNumericArray');
}

# String
{
  compile_not_ok_file('CompileError::String::CharacterAssign');
  compile_not_ok_file('CompileError::String::AssignNonMutableToMutable');
}

# Bool
{
  compile_not_ok_file('CompileError::Bool::NotNumericObject');
}
{
  compile_not_ok_file('CompileError::InvalidType');
}

{
  compile_not_ok_file('CompileError::TypeCantBeDetectedUndef');
}

{
  compile_not_ok_file('CompileError::TypeCantBeDetectedUndefDefault');
}

# Type
{
  compile_not_ok_file('CompileError::Type::MutableNoStringCaseStringArray');
  compile_not_ok_file('CompileError::Type::MutableNoStringCaseInt');
  compile_not_ok_file('CompileError::Type::MultiDimensionalAnyObject', qr/Multi dimensional array of any object/i);
}

# Type comment
{
  compile_not_ok_file('CompileError::TypeComment::NotExistType', qr/NotExists::XXXX/);
}


done_testing;

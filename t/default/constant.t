use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Constant';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

{
  ok(SPVM::TestCase::Constant->load_constant_char);
}

# constant int
{
  is(SPVM::TestCase::Constant->load_constant_int_min(), -2147483648);
  is(SPVM::TestCase::Constant->load_constant_int_m32769(), -32769);
  is(SPVM::TestCase::Constant->load_constant_int_m32768(), -32768);
  is(SPVM::TestCase::Constant->load_constant_int_m129(), -129);
  is(SPVM::TestCase::Constant->load_constant_int_m128(), -128);
  is(SPVM::TestCase::Constant->load_constant_int_m2(), -2);
  is(SPVM::TestCase::Constant->load_constant_int_m1(), -1);
  is(SPVM::TestCase::Constant->load_constant_int_0(), 0);
  is(SPVM::TestCase::Constant->load_constant_int_1(), 1);
  is(SPVM::TestCase::Constant->load_constant_int_2(), 2);
  is(SPVM::TestCase::Constant->load_constant_int_3(), 3);
  is(SPVM::TestCase::Constant->load_constant_int_4(), 4);
  is(SPVM::TestCase::Constant->load_constant_int_5(), 5);
  is(SPVM::TestCase::Constant->load_constant_int_6(), 6);
  is(SPVM::TestCase::Constant->load_constant_int_max(), 2147483647);
}

# constant long
{
  is(SPVM::TestCase::Constant->load_constant_long_min(), -9223372036854775808);
  is(SPVM::TestCase::Constant->load_constant_long_m32769(), -32769);
  is(SPVM::TestCase::Constant->load_constant_long_m32768(), -32768);
  is(SPVM::TestCase::Constant->load_constant_long_m129(), -129);
  is(SPVM::TestCase::Constant->load_constant_long_m128(), -128);
  is(SPVM::TestCase::Constant->load_constant_long_m2(), -2);
  is(SPVM::TestCase::Constant->load_constant_long_m1(), -1);
  is(SPVM::TestCase::Constant->load_constant_long_0(), 0);
  is(SPVM::TestCase::Constant->load_constant_long_1(), 1);
  is(SPVM::TestCase::Constant->load_constant_long_2(), 2);
  is(SPVM::TestCase::Constant->load_constant_long_3(), 3);
  is(SPVM::TestCase::Constant->load_constant_long_4(), 4);
  is(SPVM::TestCase::Constant->load_constant_long_5(), 5);
  is(SPVM::TestCase::Constant->load_constant_long_6(), 6);
  is(SPVM::TestCase::Constant->load_constant_long_127(), 127);
  is(SPVM::TestCase::Constant->load_constant_long_128(), 128);
  is(SPVM::TestCase::Constant->load_constant_long_32767(), 32767);
  is(SPVM::TestCase::Constant->load_constant_long_32768(), 32768);
  is(SPVM::TestCase::Constant->load_constant_long_max(), 9223372036854775807);
}

# constant float
{
  is(SPVM::TestCase::Constant->load_constant_float_0(), 0.0);
  is(SPVM::TestCase::Constant->load_constant_float_1(), 1.0);
  is(SPVM::TestCase::Constant->load_constant_float_0_5(), 0.5);
  is(SPVM::TestCase::Constant->load_constant_float_exponent_E_plus(), 0.5E+3);
  is(SPVM::TestCase::Constant->load_constant_float_exponent_e_plus(), 0.5e+3);
  is(SPVM::TestCase::Constant->load_constant_float_exponent_E_minus(), 62.5E-3);
  is(SPVM::TestCase::Constant->load_constant_float_exponent_e_minus(), 62.5e-3);
  is(SPVM::TestCase::Constant->load_constant_double_exponent_E_plus(), 0.5E+3);
  is(SPVM::TestCase::Constant->load_constant_double_exponent_e_plus(), 0.5e+3);
  is(SPVM::TestCase::Constant->load_constant_double_exponent_E_minus(), 62.5E-3);
  is(SPVM::TestCase::Constant->load_constant_double_exponent_e_minus(), 62.5e-3);
}

# constant double
{
  is(SPVM::TestCase::Constant->load_constant_double_0(), 0.0);
  is(SPVM::TestCase::Constant->load_constant_double_1(), 1.0);
  is(SPVM::TestCase::Constant->load_constant_double_0_5(), 0.5);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;

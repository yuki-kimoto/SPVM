use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Lib::SPVM::NDArray';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# SPVM::NDArray
{
  ok(TestCase::Lib::SPVM::NDArray->ndarray_byte());
  ok(TestCase::Lib::SPVM::NDArray->ndarray_short());
  ok(TestCase::Lib::SPVM::NDArray->ndarray_int());
  ok(TestCase::Lib::SPVM::NDArray->ndarray_long());
  ok(TestCase::Lib::SPVM::NDArray->ndarray_float());
  ok(TestCase::Lib::SPVM::NDArray->ndarray_double());
  ok(TestCase::Lib::SPVM::NDArray->ndarray_string());

  ok(TestCase::Lib::SPVM::NDArray->ndarray_byte_complex());
  ok(TestCase::Lib::SPVM::NDArray->ndarray_short_complex());
  ok(TestCase::Lib::SPVM::NDArray->ndarray_int_complex());
  ok(TestCase::Lib::SPVM::NDArray->ndarray_long_complex());
  ok(TestCase::Lib::SPVM::NDArray->ndarray_float_complex());
  ok(TestCase::Lib::SPVM::NDArray->ndarray_double_complex());

  ok(TestCase::Lib::SPVM::NDArray->ndarray_byte_quat());
  ok(TestCase::Lib::SPVM::NDArray->ndarray_short_quat());
  ok(TestCase::Lib::SPVM::NDArray->ndarray_int_quat());
  ok(TestCase::Lib::SPVM::NDArray->ndarray_long_quat());
  ok(TestCase::Lib::SPVM::NDArray->ndarray_float_quat());
  ok(TestCase::Lib::SPVM::NDArray->ndarray_double_quat());
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

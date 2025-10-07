use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Operator::TypeDefaultValue';

# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# init
{
  {
    ok(SPVM::TestCase::Operator::TypeDefaultValue->init_byte);
    ok(SPVM::TestCase::Operator::TypeDefaultValue->init_short);
    ok(SPVM::TestCase::Operator::TypeDefaultValue->init_int);
    ok(SPVM::TestCase::Operator::TypeDefaultValue->init_long);
    ok(SPVM::TestCase::Operator::TypeDefaultValue->init_float);
    ok(SPVM::TestCase::Operator::TypeDefaultValue->init_double);
    ok(SPVM::TestCase::Operator::TypeDefaultValue->init_mulnum_byte);
    ok(SPVM::TestCase::Operator::TypeDefaultValue->init_mulnum_short);
    ok(SPVM::TestCase::Operator::TypeDefaultValue->init_mulnum_int);
    ok(SPVM::TestCase::Operator::TypeDefaultValue->init_mulnum_long);
    ok(SPVM::TestCase::Operator::TypeDefaultValue->init_mulnum_float);
    ok(SPVM::TestCase::Operator::TypeDefaultValue->init_mulnum_double);
    ok(SPVM::TestCase::Operator::TypeDefaultValue->init_object);
  }
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);



done_testing;

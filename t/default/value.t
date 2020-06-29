use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Value';

UNITCHECK { SPVM::init() }

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

ok(TestCase::Value->value_max_fields_byte);
ok(TestCase::Value->value_max_fields_short);
ok(TestCase::Value->value_max_fields_int);
ok(TestCase::Value->value_max_fields_long);
ok(TestCase::Value->value_max_fields_float);
ok(TestCase::Value->value_max_fields_double);

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

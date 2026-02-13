use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Operator::Unsigned';

my $api = SPVM::api();

# Start objects count
my $start_memory_blocks_count = $api->get_memory_blocks_count;

ok(SPVM::TestCase::Operator::Unsigned->byte_object_signed);
ok(SPVM::TestCase::Operator::Unsigned->byte_object_unsigned);

ok(SPVM::TestCase::Operator::Unsigned->short_object_signed);
ok(SPVM::TestCase::Operator::Unsigned->short_object_unsigned);

ok(SPVM::TestCase::Operator::Unsigned->int_object_signed);
ok(SPVM::TestCase::Operator::Unsigned->int_object_unsigned);

ok(SPVM::TestCase::Operator::Unsigned->long_object_signed);
ok(SPVM::TestCase::Operator::Unsigned->long_object_unsigned);

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;

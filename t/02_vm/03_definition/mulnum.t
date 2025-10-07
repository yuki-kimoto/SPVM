use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Mulnum';



# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

ok(SPVM::TestCase::Mulnum->mulnum_max_fields_byte);
ok(SPVM::TestCase::Mulnum->mulnum_max_fields_short);
ok(SPVM::TestCase::Mulnum->mulnum_max_fields_int);
ok(SPVM::TestCase::Mulnum->mulnum_max_fields_long);
ok(SPVM::TestCase::Mulnum->mulnum_max_fields_float);
ok(SPVM::TestCase::Mulnum->mulnum_max_fields_double);

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;

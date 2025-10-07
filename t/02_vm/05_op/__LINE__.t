use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::LINEN';
use SPVM 'TestCase::LINER';
use SPVM 'TestCase::LINERN';



# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

ok(SPVM::TestCase::LINEN->line);
ok(SPVM::TestCase::LINER->line);
ok(SPVM::TestCase::LINERN->line);

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;

use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Destroy';

# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count();

# Destructor
{
  ok(SPVM::TestCase::Destroy->destroy);
  ok(SPVM::TestCase::Destroy->destroy_exception_no_override);
  ok(SPVM::TestCase::Destroy->inheritance);
}

# All object is freed
$api->set_exception(undef);
my $end_memory_blocks_count = $api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;

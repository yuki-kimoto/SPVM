use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Interface';



# Start objects count
my $start_memory_blocks_count = SPVM::api->get_memory_blocks_count();

{
  ok(SPVM::TestCase::Interface->basic);
  ok(SPVM::TestCase::Interface->interface_array);
  ok(SPVM::TestCase::Interface->interface_muldim_array);
  ok(SPVM::TestCase::Interface->can);
}

# All object is freed
my $end_memory_blocks_count = SPVM::api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);


done_testing;

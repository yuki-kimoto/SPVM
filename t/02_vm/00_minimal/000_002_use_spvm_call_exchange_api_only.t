use strict;
use warnings;

use Test::More;

use SPVM;

SPVM::api->get_memory_blocks_count();

ok(1);

done_testing;

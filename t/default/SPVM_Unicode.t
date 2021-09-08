use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'SPVM::TestCase::Lib::Unicode';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

{
  ok(SPVM::TestCase::Lib::Unicode->uchar);
  ok(SPVM::TestCase::Lib::Unicode->uchar_to_utf8);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

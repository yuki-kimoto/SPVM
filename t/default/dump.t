use lib "t/lib";
use TestAuto;

use strict;
use warnings;
use Devel::Peek;

use Test::More 'no_plan';


use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'TestCase::Dump';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# dump
{
  is(TestCase::Dump->dump_string, '"Hello"');
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

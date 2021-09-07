use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';


use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'SPVM::TestCase::FatCamma';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Spec tests
{
  # Add - Operation
  {
    ok(SPVM::TestCase::FatCamma->fat_camma);
  }
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);



use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;


use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'TestCase::Return';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Optional tests
{
  {
    ok(SPVM::TestCase::Return->return_implicite_convertion);
  }
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);


done_testing;

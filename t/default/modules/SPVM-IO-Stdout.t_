use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Lib::SPVM::IO::Stdout';

use TestFile;

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

{
  # print
  {
    ok(TestCase::Lib::SPVM::IO::Stdout->test_print);
  }

  # set_binmode
  {
    ok(TestCase::Lib::SPVM::IO::Stdout->test_set_binmode);
  }
}


# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

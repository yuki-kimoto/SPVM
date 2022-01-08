use lib "t/lib";
use TestAuto;

use strict;
use warnings;
use utf8;

use Test::More;

use SPVM 'TestCase::Literal::Undef';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

{
  ok(SPVM::TestCase::Literal::Undef->undef_test);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;

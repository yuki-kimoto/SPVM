use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Lib::SPVM::Sort';

UNITCHECK { SPVM::init() }

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# sort
{
  # sortb
  ok(TestCase::Lib::SPVM::Sort->test_sortb);

  # sorts
  ok(TestCase::Lib::SPVM::Sort->test_sorts);

  # sorti
  ok(TestCase::Lib::SPVM::Sort->test_sorti);

  # sortl
  ok(TestCase::Lib::SPVM::Sort->test_sortl);

  # sortf
  ok(TestCase::Lib::SPVM::Sort->test_sortf);

  # sortd
  ok(TestCase::Lib::SPVM::Sort->test_sortd);

  # sorto
  ok(TestCase::Lib::SPVM::Sort->test_sorto);

  # sortstr
  ok(TestCase::Lib::SPVM::Sort->test_sortstr);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

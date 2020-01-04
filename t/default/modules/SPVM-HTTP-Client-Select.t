use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Lib::SPVM::HTTP::Client::Select';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Select
{
  ok(TestCase::Lib::SPVM::HTTP::Client::Select->add);
  ok(TestCase::Lib::SPVM::HTTP::Client::Select->remove);
  ok(TestCase::Lib::SPVM::HTTP::Client::Select->exists);
  if ($^O ne 'MSWin32') {
    ok(TestCase::Lib::SPVM::HTTP::Client::Select->can_read);
    ok(TestCase::Lib::SPVM::HTTP::Client::Select->can_write);
    ok(TestCase::Lib::SPVM::HTTP::Client::Select->has_exception);
  }
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

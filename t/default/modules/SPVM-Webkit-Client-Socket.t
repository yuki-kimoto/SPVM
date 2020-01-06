use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Lib::SPVM::Webkit::Client::Socket';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Socket
{
  ok(TestCase::Lib::SPVM::Webkit::Client::Socket->basic);
  ok(TestCase::Lib::SPVM::Webkit::Client::Socket->basic_auto_close);
  ok(TestCase::Lib::SPVM::Webkit::Client::Socket->fileno);
}


# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

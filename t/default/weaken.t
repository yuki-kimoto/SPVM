use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Weaken';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Weaken field
{
  {
    my $start_memory_blocks_count = SPVM::get_memory_blocks_count();
    {
      ok(TestCase::Weaken->weaken_target4_weaken_object_assign());
    }
    my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
    is($end_memory_blocks_count, $start_memory_blocks_count);
  }
  {
    my $start_memory_blocks_count = SPVM::get_memory_blocks_count();
    {
      ok(TestCase::Weaken->weaken_target4());
    }
    my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
    is($end_memory_blocks_count, $start_memory_blocks_count);
  }
  {
    my $start_memory_blocks_count = SPVM::get_memory_blocks_count();
    {
      ok(TestCase::Weaken->weaken_weaken_object_undef());
    }
    my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
    is($end_memory_blocks_count, $start_memory_blocks_count);
  }
  {
    my $start_memory_blocks_count = SPVM::get_memory_blocks_count();
    {
      ok(TestCase::Weaken->weaken_target_object_undef());
    }
    my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
    is($end_memory_blocks_count, $start_memory_blocks_count);
  }
  {
    my $start_memory_blocks_count = SPVM::get_memory_blocks_count();
    {
      TestCase::Weaken->weaken_recursive3();
    }
    my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
    is($end_memory_blocks_count, $start_memory_blocks_count);
  }
  {
    my $start_memory_blocks_count = SPVM::get_memory_blocks_count();
    {
      TestCase::Weaken->weaken_recursive_again();
    }
    my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
    is($end_memory_blocks_count, $start_memory_blocks_count);
  }
  {
    my $start_memory_blocks_count = SPVM::get_memory_blocks_count();
    {
      ok(TestCase::Weaken->weaken_recursive());
    }
    my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
    is($end_memory_blocks_count, $start_memory_blocks_count);
  }
  {
    my $start_memory_blocks_count = SPVM::get_memory_blocks_count();
    {
      ok(TestCase::Weaken->weaken_reference_count1_object());
    }
    my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
    is($end_memory_blocks_count, $start_memory_blocks_count);
  }
  {
    my $start_memory_blocks_count = SPVM::get_memory_blocks_count();
    {
      ok(TestCase::Weaken->weaken_self_recuresive());
    }
    my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
    is($end_memory_blocks_count, $start_memory_blocks_count);
  }
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

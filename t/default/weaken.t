use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Weaken';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

# Weaken field
{
  {
    my $start_memory_blocks_count = SPVM::memory_blocks_count();
    {
      ok(TestCase::Weaken->weaken_field_cross_reference());
    }
    my $end_memory_blocks_count = SPVM::memory_blocks_count();
    is($end_memory_blocks_count, $start_memory_blocks_count);
  }
  {
    my $start_memory_blocks_count = SPVM::memory_blocks_count();
    {
      TestCase::Weaken->weaken_field_cross_reference_weaken_twice();
    }
    my $end_memory_blocks_count = SPVM::memory_blocks_count();
    is($end_memory_blocks_count, $start_memory_blocks_count);
  }
  
  {
    my $start_memory_blocks_count = SPVM::memory_blocks_count();
    {
      TestCase::Weaken->weaken_field_cross_reference_weaken_both();
    }
    my $end_memory_blocks_count = SPVM::memory_blocks_count();
    is($end_memory_blocks_count, $start_memory_blocks_count);
  }
  {
    my $start_memory_blocks_count = SPVM::memory_blocks_count();
    {
      ok(TestCase::Weaken->weaken_field_self_reference());
    }
    my $end_memory_blocks_count = SPVM::memory_blocks_count();
    is($end_memory_blocks_count, $start_memory_blocks_count);
  }
  {
    my $start_memory_blocks_count = SPVM::memory_blocks_count();
    {
      ok(TestCase::Weaken->weaken_field_weaken_ref_count1_object());
    }
    my $end_memory_blocks_count = SPVM::memory_blocks_count();
    is($end_memory_blocks_count, $start_memory_blocks_count);
  }
  {
    my $start_memory_blocks_count = SPVM::memory_blocks_count();
    {
      TestCase::Weaken->weaken_field_circular_reference();
    }
    my $end_memory_blocks_count = SPVM::memory_blocks_count();
    is($end_memory_blocks_count, $start_memory_blocks_count);
  }
  {
    my $start_memory_blocks_count = SPVM::memory_blocks_count();
    {
      TestCase::Weaken->weaken_field_circular_reference_weaken_twice();
    }
    my $end_memory_blocks_count = SPVM::memory_blocks_count();
    is($end_memory_blocks_count, $start_memory_blocks_count);
  }
  {
    my $start_memory_blocks_count = SPVM::memory_blocks_count();
    {
      TestCase::Weaken->weaken_field_circular_reference_weaken_triple();
    }
    my $end_memory_blocks_count = SPVM::memory_blocks_count();
    is($end_memory_blocks_count, $start_memory_blocks_count);
  }
  {
    my $start_memory_blocks_count = SPVM::memory_blocks_count();
    {
      ok(TestCase::Weaken->weaken_field_assign_undef_to_weakened_field());
    }
    my $end_memory_blocks_count = SPVM::memory_blocks_count();
    is($end_memory_blocks_count, $start_memory_blocks_count);
  }
  {
    my $start_memory_blocks_count = SPVM::memory_blocks_count();
    {
      ok(TestCase::Weaken->weaken_field_assign_undef_to_assinged_object());
    }
    my $end_memory_blocks_count = SPVM::memory_blocks_count();
    is($end_memory_blocks_count, $start_memory_blocks_count);
  }
  {
    my $start_memory_blocks_count = SPVM::memory_blocks_count();
    {
      ok(TestCase::Weaken->weaken_field_undef());
    }
    my $end_memory_blocks_count = SPVM::memory_blocks_count();
    is($end_memory_blocks_count, $start_memory_blocks_count);
  }
  {
    my $start_memory_blocks_count = SPVM::memory_blocks_count();
    {
      ok(TestCase::Weaken->weaken_field_cross_reference_assign_var());
    }
    my $end_memory_blocks_count = SPVM::memory_blocks_count();
    is($end_memory_blocks_count, $start_memory_blocks_count);
  }
  {
    my $start_memory_blocks_count = SPVM::memory_blocks_count();
    {
      ok(TestCase::Weaken->weaken_array_element_cross_reference());
    }
    my $end_memory_blocks_count = SPVM::memory_blocks_count();
    is($end_memory_blocks_count, $start_memory_blocks_count);
  }
  {
    my $start_memory_blocks_count = SPVM::memory_blocks_count();
    {
      ok(TestCase::Weaken->weaken_array_element_circular_reference_with_many_cases);
    }
    my $end_memory_blocks_count = SPVM::memory_blocks_count();
    is($end_memory_blocks_count, $start_memory_blocks_count);
  }
  {
    my $start_memory_blocks_count = SPVM::memory_blocks_count();
    {
      ok(TestCase::Weaken->weaken_array_element_object_array);
    }
    my $end_memory_blocks_count = SPVM::memory_blocks_count();
    is($end_memory_blocks_count, $start_memory_blocks_count);
  }
}

# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

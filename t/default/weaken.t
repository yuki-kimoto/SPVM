use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Weaken';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# weaken
{
  {
    my $start_memory_blocks_count = SPVM::get_memory_blocks_count();
    
    {
      ok(SPVM::TestCase::Weaken->weaken_field_cross_reference());
    }
    my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
    is($end_memory_blocks_count, $start_memory_blocks_count);
  }
  {
    my $start_memory_blocks_count = SPVM::get_memory_blocks_count();
    {
      SPVM::TestCase::Weaken->weaken_field_cross_reference_weaken_twice();
    }
    my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
    is($end_memory_blocks_count, $start_memory_blocks_count);
  }
  
  {
    my $start_memory_blocks_count = SPVM::get_memory_blocks_count();
    {
      SPVM::TestCase::Weaken->weaken_field_cross_reference_weaken_both();
    }
    my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
    is($end_memory_blocks_count, $start_memory_blocks_count);
  }
  {
    my $start_memory_blocks_count = SPVM::get_memory_blocks_count();
    {
      ok(SPVM::TestCase::Weaken->weaken_field_self_reference());
    }
    my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
    is($end_memory_blocks_count, $start_memory_blocks_count);
  }
  {
    my $start_memory_blocks_count = SPVM::get_memory_blocks_count();
    {
      ok(SPVM::TestCase::Weaken->weaken_field_weaken_ref_count1_object());
    }
    my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
    is($end_memory_blocks_count, $start_memory_blocks_count);
  }
  {
    my $start_memory_blocks_count = SPVM::get_memory_blocks_count();
    {
      SPVM::TestCase::Weaken->weaken_field_circular_reference();
    }
    my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
    is($end_memory_blocks_count, $start_memory_blocks_count);
  }
  {
    my $start_memory_blocks_count = SPVM::get_memory_blocks_count();
    {
      SPVM::TestCase::Weaken->weaken_field_circular_reference_weaken_twice();
    }
    my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
    is($end_memory_blocks_count, $start_memory_blocks_count);
  }
  {
    my $start_memory_blocks_count = SPVM::get_memory_blocks_count();
    {
      SPVM::TestCase::Weaken->weaken_field_circular_reference_weaken_triple();
    }
    my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
    is($end_memory_blocks_count, $start_memory_blocks_count);
  }
  {
    my $start_memory_blocks_count = SPVM::get_memory_blocks_count();
    {
      ok(SPVM::TestCase::Weaken->weaken_field_assign_undef_to_weakened_field());
    }
    my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
    is($end_memory_blocks_count, $start_memory_blocks_count);
  }
  {
    my $start_memory_blocks_count = SPVM::get_memory_blocks_count();
    {
      ok(SPVM::TestCase::Weaken->weaken_field_assign_undef_to_assinged_object());
    }
    my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
    is($end_memory_blocks_count, $start_memory_blocks_count);
  }
  {
    my $start_memory_blocks_count = SPVM::get_memory_blocks_count();
    {
      ok(SPVM::TestCase::Weaken->weaken_field_undef());
    }
    my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
    is($end_memory_blocks_count, $start_memory_blocks_count);
  }
  {
    my $start_memory_blocks_count = SPVM::get_memory_blocks_count();
    {
      ok(SPVM::TestCase::Weaken->weaken_field_cross_reference_assign_var());
    }
    my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
    is($end_memory_blocks_count, $start_memory_blocks_count);
  }
}

# isweak
{
  ok(SPVM::TestCase::Weaken->isweak_test);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;

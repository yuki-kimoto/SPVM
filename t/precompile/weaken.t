use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase';

# Start objects count
my $start_objects_count = SPVM::get_objects_count();

# Weaken
{
  {
    my $start_objects_count = SPVM::get_objects_count();
    {
      ok(TestCase->weaken_target4_weaken_object_assign());
    }
    my $end_objects_count = SPVM::get_objects_count();
    is($end_objects_count, $start_objects_count);
  }
  {
    my $start_objects_count = SPVM::get_objects_count();
    {
      ok(TestCase->weaken_target4());
    }
    my $end_objects_count = SPVM::get_objects_count();
    is($end_objects_count, $start_objects_count);
  }
  {
    my $start_objects_count = SPVM::get_objects_count();
    {
      ok(TestCase->weaken_weaken_object_undef());
    }
    my $end_objects_count = SPVM::get_objects_count();
    is($end_objects_count, $start_objects_count);
  }
  {
    my $start_objects_count = SPVM::get_objects_count();
    {
      ok(TestCase->weaken_target_object_undef());
    }
    my $end_objects_count = SPVM::get_objects_count();
    is($end_objects_count, $start_objects_count);
  }
  {
    my $start_objects_count = SPVM::get_objects_count();
    {
      TestCase->weaken_recursive3();
    }
    my $end_objects_count = SPVM::get_objects_count();
    is($end_objects_count, $start_objects_count);
  }
  {
    my $start_objects_count = SPVM::get_objects_count();
    {
      TestCase->weaken_recursive_again();
    }
    my $end_objects_count = SPVM::get_objects_count();
    is($end_objects_count, $start_objects_count);
  }
  {
    my $start_objects_count = SPVM::get_objects_count();
    {
      ok(TestCase->weaken_recursive());
    }
    my $end_objects_count = SPVM::get_objects_count();
    is($end_objects_count, $start_objects_count);
  }
  {
    my $start_objects_count = SPVM::get_objects_count();
    {
      ok(TestCase->weaken_reference_count1_object());
    }
    my $end_objects_count = SPVM::get_objects_count();
    is($end_objects_count, $start_objects_count);
  }
  {
    my $start_objects_count = SPVM::get_objects_count();
    {
      ok(TestCase->weaken_self_recuresive());
    }
    my $end_objects_count = SPVM::get_objects_count();
    is($end_objects_count, $start_objects_count);
  }
}

# All object is freed
my $end_objects_count = SPVM::get_objects_count();
is($end_objects_count, $start_objects_count);

use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Switch';

# Start objects count
my $start_objects_count = SPVM::get_objects_count();

# Switch
{
  ok(TestCase::Switch->switch_nest());
  ok(TestCase::Switch->switch_lookup_switch());
  ok(TestCase::Switch->switch_table_switch());
}


# All object is freed
my $end_objects_count = SPVM::get_objects_count();
is($end_objects_count, $start_objects_count);

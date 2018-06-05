use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase';

# Start objects count
my $start_objects_count = SPVM::get_objects_count();

# Switch
{
  ok(TestCase->switch_nest());
  ok(TestCase->switch_lookup_switch());
  ok(TestCase->switch_table_switch());
}


# All object is freed
my $end_objects_count = SPVM::get_objects_count();
is($end_objects_count, $start_objects_count);

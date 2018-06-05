use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Short';

# Start objects count
my $start_objects_count = SPVM::get_objects_count();

# SPVM::Short
{
  ok(TestCase::Short->basic());
}


# All object is freed
my $end_objects_count = SPVM::get_objects_count();
is($end_objects_count, $start_objects_count);

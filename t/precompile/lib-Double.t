use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Double';

# Start objects count
my $start_objects_count = SPVM::get_objects_count();

# SPVM::Double
{
  ok(SPVM::TestCase::Double->basic());
}

# All object is freed
my $end_objects_count = SPVM::get_objects_count();
is($end_objects_count, $start_objects_count);

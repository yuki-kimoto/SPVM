use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Loop';

# Start objects count
my $start_objects_count = SPVM::get_objects_count();

# for
{
  ok(TestCase::Loop->for_basic());
  ok(TestCase::Loop->next_statement());
}


# All object is freed
my $end_objects_count = SPVM::get_objects_count();
is($end_objects_count, $start_objects_count);

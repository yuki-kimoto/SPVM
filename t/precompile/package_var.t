use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase';

# Start objects count
my $start_objects_count = SPVM::get_objects_count();

# Package variable relative name
{
  my $start_objects_count = SPVM::get_objects_count();
  ok(TestCase->package_var_rel_name());
  my $end_objects_count = SPVM::get_objects_count();
  is($start_objects_count, $end_objects_count);
}

# Package variable
{
  my $start_objects_count = SPVM::get_objects_count();
  ok(TestCase->package_var());
  ok(TestCase->package_var_other_package());
  my $end_objects_count = SPVM::get_objects_count();
  is($start_objects_count, $end_objects_count);
}

# All object is freed
my $end_objects_count = SPVM::get_objects_count();
is($end_objects_count, $start_objects_count);

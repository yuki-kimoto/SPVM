use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::SpecialAssign';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Special assign add
{
  ok(TestCase::SpecialAssign->special_assign_add_var);
  ok(TestCase::SpecialAssign->special_assign_add_array_access_constant_index);
  ok(TestCase::SpecialAssign->special_assign_add_array_access_var_index);
  ok(TestCase::SpecialAssign->special_assign_add_field_access);
  ok(TestCase::SpecialAssign->special_assign_add_deref);
  ok(TestCase::SpecialAssign->special_assign_add_package_var_access);
  ok(TestCase::SpecialAssign->special_assign_add_array_field_access_constant_index);
  
  ok(TestCase::SpecialAssign->special_assign_add_array_access_invocant_not_var);
  ok(TestCase::SpecialAssign->special_assign_add_array_field_access_invocant_not_var);
  ok(TestCase::SpecialAssign->special_assign_add_field_access_invocant_not_var);
}



# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

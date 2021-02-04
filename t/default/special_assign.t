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

# Special assign subtract
{
  ok(TestCase::SpecialAssign->special_assign_subtract_var);
}

# Special assign multiply
{
  ok(TestCase::SpecialAssign->special_assign_multiply_var);
}

# Special assign divide
{
  ok(TestCase::SpecialAssign->special_assign_divide_var);
}
# Special assign remainder
{
  ok(TestCase::SpecialAssign->special_assign_remainder_var);
}

# Special assign bit and
{
  ok(TestCase::SpecialAssign->special_assign_bit_and_var);
}

# Special assign bit or
{
  ok(TestCase::SpecialAssign->special_assign_bit_or_var);
}

# Special assign bit xor
{
  ok(TestCase::SpecialAssign->special_assign_bit_xor_var);
}

# Special assign left shift
{
  ok(TestCase::SpecialAssign->special_assign_left_shift_var);
}

# Special assign right shift
{
  ok(TestCase::SpecialAssign->special_assign_right_shift_var);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

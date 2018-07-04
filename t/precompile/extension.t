use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Extension';
use SPVM 'TestCase::Extension2';
use SPVM 'TestCase::Pointer';

# Start objects count
my $start_objects_count = SPVM::get_objects_count();

# Native Exception
{
  ok(TestCase::Extension->native_use_strlen_test);
  ok(TestCase::Extension->call_void_sub_exception);
}

# Check mortal API
{
  ok(TestCase::Extension->mortal_api);
  ok(TestCase::Extension->enter_scope_leave_scope);
}

# env->call_sub
{
  ok(TestCase::Extension->native_call_sub);
}

# Native Exception
{
  is(TestCase::Extension2->mul(2, 3), 6);
  is(TestCase::Extension2->one(), 1);
  ok(TestCase::Extension2->spvm_extension2());
  ok(TestCase::Extension2->spvm_extension2_binding());
}

# Pointer
{
  ok(TestCase::Pointer->struct_test());
}

# Clear exception
SPVM::set_exception_undef();

# All object is freed
my $end_objects_count = SPVM::get_objects_count();
is($end_objects_count, $start_objects_count);

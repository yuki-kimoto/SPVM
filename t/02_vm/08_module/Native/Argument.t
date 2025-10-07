use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::Native::Argument';



# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

{
  ok(SPVM::TestCase::Module::Native::Argument->get_index);
  ok(SPVM::TestCase::Module::Native::Argument->get_basic_type);
  ok(SPVM::TestCase::Module::Native::Argument->get_type_dimension);
  ok(SPVM::TestCase::Module::Native::Argument->get_type_flag);
  ok(SPVM::TestCase::Module::Native::Argument->is_optional);
  ok(SPVM::TestCase::Module::Native::Argument->get_default_value_byte);
  ok(SPVM::TestCase::Module::Native::Argument->get_default_value_short);
  ok(SPVM::TestCase::Module::Native::Argument->get_default_value_int);
  ok(SPVM::TestCase::Module::Native::Argument->get_default_value_long);
  ok(SPVM::TestCase::Module::Native::Argument->get_default_value_float);
  ok(SPVM::TestCase::Module::Native::Argument->get_default_value_double);
  ok(SPVM::TestCase::Module::Native::Argument->get_default_value_object);
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;

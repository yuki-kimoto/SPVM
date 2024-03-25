use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Operator::Isa';
use SPVM 'TestCase::Operator::IsType';
use SPVM 'TestCase::Operator::IsCompileType';

my $api = SPVM::api();

# Start objects count
my $start_memory_blocks_count = $api->get_memory_blocks_count();

# isa
{
  ok(SPVM::TestCase::Operator::Isa->isa);
  ok(SPVM::TestCase::Operator::Isa->isa_any_object_type);
  ok(SPVM::TestCase::Operator::Isa->isa_numeric_type);
  ok(SPVM::TestCase::Operator::Isa->isa_multi_numeric_type);
  ok(SPVM::TestCase::Operator::Isa->isa_match_class);
  ok(SPVM::TestCase::Operator::Isa->isa_not_match_class);
  ok(SPVM::TestCase::Operator::Isa->isa_match_array);
  ok(SPVM::TestCase::Operator::Isa->isa_not_match_class_undef);
  ok(SPVM::TestCase::Operator::Isa->isa_match_callback);
  ok(SPVM::TestCase::Operator::Isa->isa_not_match_callback_undef);
  ok(SPVM::TestCase::Operator::Isa->isa_error);
  ok(SPVM::TestCase::Operator::Isa->isa_extra);
}

# is_type
{
  ok(SPVM::TestCase::Operator::IsType->is_type);
  ok(SPVM::TestCase::Operator::IsType->is_error);
}

# is_compile_type
{
  ok(SPVM::TestCase::Operator::IsCompileType->is_compile_type);
}

# is_compile_type
{
  ok(SPVM::TestCase::Operator::IsCompileType->is_compile_type);
}

# All object is freed
my $end_memory_blocks_count = $api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;

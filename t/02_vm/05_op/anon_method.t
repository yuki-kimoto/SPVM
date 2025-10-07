use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Operator::AnonMethod';

my $api = SPVM::api();

# Start objects count
my $start_memory_blocks_count = $api->get_memory_blocks_count;

{
  ok(SPVM::TestCase::Operator::AnonMethod->basic);
  ok(SPVM::TestCase::Operator::AnonMethod->callback_array);
  ok(SPVM::TestCase::Operator::AnonMethod->comparator);
  ok(SPVM::TestCase::Operator::AnonMethod->anon_method_field);
}

# Check the precompile source
{
  if ($ENV{SPVM_TEST_PRECOMPILE}) {
    my $callback_precompile_source_file = "$ENV{SPVM_BUILD_DIR}/work/src/SPVM/TestCase/Operator/AnonMethod.precompile.c";
    my $content = do { open my $fh, '<', $callback_precompile_source_file; local $/; <$fh>; };
    like($content, qr/TestCase__Operator__AnonMethod__anon_method__\d+__\d+/);
  }
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;

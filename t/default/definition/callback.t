use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Callback';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

{
  ok(SPVM::TestCase::Callback->basic);
  ok(SPVM::TestCase::Callback->callback_array);
  ok(SPVM::TestCase::Callback->comparator);
  ok(SPVM::TestCase::Callback->capture);
  ok(SPVM::TestCase::Callback->capture_var_high_precidence_than_class_var);
}

# Check the precompile source
{
  if ($ENV{SPVM_TEST_PRECOMPILE}) {
    my $callback_precompile_source_file = "$ENV{SPVM_BUILD_DIR}/work/src/SPVM/TestCase/Callback.precompile.c";
    my $content = do { open my $fh, '<', $callback_precompile_source_file; local $/; <$fh>; };
    like($content, qr/TestCase__Callback__anon__\d+__\d+/);
  }
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);


done_testing;

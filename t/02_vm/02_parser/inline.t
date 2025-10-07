use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::InlineExpansion';



# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# Inline constant sub
{
  ok(SPVM::TestCase::InlineExpansion->constant_method);
  ok(SPVM::TestCase::InlineExpansion->constant_method_return_double == 0.25);
}

# Inline new
{
  ok(SPVM::TestCase::InlineExpansion->new_inline);
  ok(SPVM::TestCase::InlineExpansion->new);
  isa_ok(SPVM::TestCase::InlineExpansion->new, "SPVM::BlessedObject::Class");
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;

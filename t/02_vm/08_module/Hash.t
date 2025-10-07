use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::Hash';

# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# SPVM::Hash
{
  ok(SPVM::TestCase::Module::Hash->rehash);
  ok(SPVM::TestCase::Module::Hash->get_byte);
  ok(SPVM::TestCase::Module::Hash->get_short);
  ok(SPVM::TestCase::Module::Hash->get_int);
  ok(SPVM::TestCase::Module::Hash->get_long);
  ok(SPVM::TestCase::Module::Hash->get_float);
  ok(SPVM::TestCase::Module::Hash->get_double);
  ok(SPVM::TestCase::Module::Hash->get_string);
  ok(SPVM::TestCase::Module::Hash->set_byte);
  ok(SPVM::TestCase::Module::Hash->set_short);
  ok(SPVM::TestCase::Module::Hash->set_int);
  ok(SPVM::TestCase::Module::Hash->set_long);
  ok(SPVM::TestCase::Module::Hash->set_float);
  ok(SPVM::TestCase::Module::Hash->set_double);
  ok(SPVM::TestCase::Module::Hash->set_string);
  ok(SPVM::TestCase::Module::Hash->murmur_hash);
  ok(SPVM::TestCase::Module::Hash->set);
  ok(SPVM::TestCase::Module::Hash->set_do_not_refer_caller_key);
  ok(SPVM::TestCase::Module::Hash->get);
  ok(SPVM::TestCase::Module::Hash->exists);
  ok(SPVM::TestCase::Module::Hash->delete);
  ok(SPVM::TestCase::Module::Hash->keys);
  ok(SPVM::TestCase::Module::Hash->has_keys);
  ok(SPVM::TestCase::Module::Hash->values);
  ok(SPVM::TestCase::Module::Hash->copy);
  ok(SPVM::TestCase::Module::Hash->clone);
  ok(SPVM::TestCase::Module::Hash->new);
  ok(SPVM::TestCase::Module::Hash->to_array);
  ok(SPVM::TestCase::Module::Hash->to_options);
  ok(SPVM::TestCase::Module::Hash->get_or_default);
  ok(SPVM::TestCase::Module::Hash->delete_or_default);
  ok(SPVM::TestCase::Module::Hash->weaken);
  ok(SPVM::TestCase::Module::Hash->unweaken);
  ok(SPVM::TestCase::Module::Hash->isweak);
  ok(SPVM::TestCase::Module::Hash->extra);
  ok(SPVM::TestCase::Module::Hash->new_from_keys);
  ok(SPVM::TestCase::Module::Hash->merge);
  ok(SPVM::TestCase::Module::Hash->merge_options);
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;

use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::Native::Compiler';

my $api = SPVM::api;

# Start objects count
my $start_memory_blocks_count = $api->get_memory_blocks_count();

{
  ok(SPVM::TestCase::Module::Native::Compiler->compile);
  ok(SPVM::TestCase::Module::Native::Compiler->compile_anon_class);
  ok(SPVM::TestCase::Module::Native::Compiler->eval_string);
}

# All object is freed
my $end_memory_blocks_count = $api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;

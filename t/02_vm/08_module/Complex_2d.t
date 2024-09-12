use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::Complex_2d';

my $api = SPVM::api();

# Start objects count
my $start_memory_blocks_count = $api->get_memory_blocks_count();

# SPVM::Int
{
  ok(SPVM::TestCase::Module::Complex_2d->new);
  ok(SPVM::TestCase::Module::Complex_2d->new_array_from_pairs);
  ok(SPVM::TestCase::Module::Complex_2d->new_array_from_re_array);
  ok(SPVM::TestCase::Module::Complex_2d->new_array_from_im_array);
  ok(SPVM::TestCase::Module::Complex_2d->to_re_array);
  ok(SPVM::TestCase::Module::Complex_2d->to_im_array);
  ok(SPVM::TestCase::Module::Complex_2d->to_string);
}

$api->set_exception(undef);

# All object is freed
my $end_memory_blocks_count = $api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;

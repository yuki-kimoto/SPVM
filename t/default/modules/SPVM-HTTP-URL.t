use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Lib::SPVM::HTTP::URL';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# SPVM::HTTP::URL
{
  ok(TestCase::Lib::SPVM::HTTP::URL->test_parse_escape_all);
  ok(TestCase::Lib::SPVM::HTTP::URL->test_parse_host);
  ok(TestCase::Lib::SPVM::HTTP::URL->test_parse_host_path);
  ok(TestCase::Lib::SPVM::HTTP::URL->test_parse_host_params);
  ok(TestCase::Lib::SPVM::HTTP::URL->test_parse_host_fragment);
  ok(TestCase::Lib::SPVM::HTTP::URL->test_parse_host_path_fragment);
  ok(TestCase::Lib::SPVM::HTTP::URL->test_not_found_scheme_separator);
  ok(TestCase::Lib::SPVM::HTTP::URL->test_amazon_path_escaped);
  ok(TestCase::Lib::SPVM::HTTP::URL->test_host_is_not_for_url);
  ok(TestCase::Lib::SPVM::HTTP::URL->test_trailing_slash);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

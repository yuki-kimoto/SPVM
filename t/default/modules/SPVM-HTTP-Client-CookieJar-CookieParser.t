use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Lib::SPVM::HTTP::Client::CookieJar::CookieParser';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# SPVM::HTTP::Client::CookieJar::CookieParser
{
  ok(TestCase::Lib::SPVM::HTTP::Client::CookieJar::CookieParser->test_parse_only_key_value);
  # TODO: Implement 'locale' in strptime.
  #ok(TestCase::Lib::SPVM::HTTP::Client::CookieJar::CookieParser->test_parse_expires);
  ok(TestCase::Lib::SPVM::HTTP::Client::CookieJar::CookieParser->test_parse_max_age);
  ok(TestCase::Lib::SPVM::HTTP::Client::CookieJar::CookieParser->test_parse_domain);
  ok(TestCase::Lib::SPVM::HTTP::Client::CookieJar::CookieParser->test_parse_path);
  ok(TestCase::Lib::SPVM::HTTP::Client::CookieJar::CookieParser->test_parse_secure);
  ok(TestCase::Lib::SPVM::HTTP::Client::CookieJar::CookieParser->test_parse_http_only);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

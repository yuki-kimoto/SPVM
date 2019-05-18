use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Lib::SPVM::HTTP::Client::CookieJar';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

# SPVM::HTTP::Client::CookieJar
{
  ok(TestCase::Lib::SPVM::HTTP::Client::CookieJar->test_add_key_value);
  ok(TestCase::Lib::SPVM::HTTP::Client::CookieJar->test_add_expires);
  ok(TestCase::Lib::SPVM::HTTP::Client::CookieJar->test_add_max_age);
  ok(TestCase::Lib::SPVM::HTTP::Client::CookieJar->test_add_prioritize_max_age_over_expires);
  ok(TestCase::Lib::SPVM::HTTP::Client::CookieJar->test_add_expires_infinity);
  ok(TestCase::Lib::SPVM::HTTP::Client::CookieJar->test_add_domain);
  ok(TestCase::Lib::SPVM::HTTP::Client::CookieJar->test_add_domain_use_host_only_when_no_domain);
  ok(TestCase::Lib::SPVM::HTTP::Client::CookieJar->test_add_domain_use_host_only_when_no_domain_request_root_path);
  ok(TestCase::Lib::SPVM::HTTP::Client::CookieJar->test_add_domain_not_host_only_even_if_same_as_request_domain);
  ok(TestCase::Lib::SPVM::HTTP::Client::CookieJar->test_add_domain_ignore_cookie_when_different_domain);
  ok(TestCase::Lib::SPVM::HTTP::Client::CookieJar->test_add_path_last_is_dir_when_no_path_attr);
  ok(TestCase::Lib::SPVM::HTTP::Client::CookieJar->test_add_path_last_is_file_when_no_path_attr);
  ok(TestCase::Lib::SPVM::HTTP::Client::CookieJar->test_add_path_use_default_path_when_broken_root);
  ok(TestCase::Lib::SPVM::HTTP::Client::CookieJar->test_add_path_prioritize_path_attr_over_request_path);
  ok(TestCase::Lib::SPVM::HTTP::Client::CookieJar->test_add_secure);
  ok(TestCase::Lib::SPVM::HTTP::Client::CookieJar->test_add_http_only);
  ok(TestCase::Lib::SPVM::HTTP::Client::CookieJar->test_add_update_cookie);
  ok(TestCase::Lib::SPVM::HTTP::Client::CookieJar->test_cookies_for);
  ok(TestCase::Lib::SPVM::HTTP::Client::CookieJar->test_cookies_for_returning_value_order);
  ok(TestCase::Lib::SPVM::HTTP::Client::CookieJar->test_cookie_header);
}

# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

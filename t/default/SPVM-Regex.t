use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Lib::SPVM::Regex';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# SPVM::Regex
{
  ok(TestCase::Lib::SPVM::Regex->replace_all_cb);
  ok(TestCase::Lib::SPVM::Regex->replace_all);
  ok(TestCase::Lib::SPVM::Regex->replace);
  ok(TestCase::Lib::SPVM::Regex->replace_cb);
  ok(TestCase::Lib::SPVM::Regex->match_start_and_end);
  ok(TestCase::Lib::SPVM::Regex->match_capture);
  ok(TestCase::Lib::SPVM::Regex->match_char_class_range);
  ok(TestCase::Lib::SPVM::Regex->match_char_class);
  ok(TestCase::Lib::SPVM::Regex->match_char_class_negate);
  ok(TestCase::Lib::SPVM::Regex->match_not_space);
  ok(TestCase::Lib::SPVM::Regex->match_space);
  ok(TestCase::Lib::SPVM::Regex->match_not_word);
  ok(TestCase::Lib::SPVM::Regex->match_word);
  ok(TestCase::Lib::SPVM::Regex->match_number);
  ok(TestCase::Lib::SPVM::Regex->match_not_number);
  ok(TestCase::Lib::SPVM::Regex->invalid_regex);
  ok(TestCase::Lib::SPVM::Regex->match_end);
  ok(TestCase::Lib::SPVM::Regex->match_start);
  ok(TestCase::Lib::SPVM::Regex->match_quantifier);
  ok(TestCase::Lib::SPVM::Regex->match_one_or_zero);
  ok(TestCase::Lib::SPVM::Regex->match_zero_more);
  ok(TestCase::Lib::SPVM::Regex->match_one_more);
  ok(TestCase::Lib::SPVM::Regex->match_offset);
  ok(TestCase::Lib::SPVM::Regex->match);
  ok(TestCase::Lib::SPVM::Regex->compile);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

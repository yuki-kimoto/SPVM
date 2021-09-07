use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'SPVM::TestCase::Lib::SPVM::Regex';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# SPVM::Regex
{
  ok(SPVM::TestCase::Lib::SPVM::Regex->replace_all_cb);
  ok(SPVM::TestCase::Lib::SPVM::Regex->replace_all);
  ok(SPVM::TestCase::Lib::SPVM::Regex->replace);
  ok(SPVM::TestCase::Lib::SPVM::Regex->replace_cb);
  ok(SPVM::TestCase::Lib::SPVM::Regex->match_start_and_end);
  ok(SPVM::TestCase::Lib::SPVM::Regex->match_capture);
  ok(SPVM::TestCase::Lib::SPVM::Regex->match_char_class_range);
  ok(SPVM::TestCase::Lib::SPVM::Regex->match_char_class);
  ok(SPVM::TestCase::Lib::SPVM::Regex->match_char_class_negate);
  ok(SPVM::TestCase::Lib::SPVM::Regex->match_not_space);
  ok(SPVM::TestCase::Lib::SPVM::Regex->match_space);
  ok(SPVM::TestCase::Lib::SPVM::Regex->match_not_word);
  ok(SPVM::TestCase::Lib::SPVM::Regex->match_word);
  ok(SPVM::TestCase::Lib::SPVM::Regex->match_number);
  ok(SPVM::TestCase::Lib::SPVM::Regex->match_not_number);
  ok(SPVM::TestCase::Lib::SPVM::Regex->invalid_regex);
  ok(SPVM::TestCase::Lib::SPVM::Regex->match_end);
  ok(SPVM::TestCase::Lib::SPVM::Regex->match_start);
  ok(SPVM::TestCase::Lib::SPVM::Regex->match_quantifier);
  ok(SPVM::TestCase::Lib::SPVM::Regex->match_one_or_zero);
  ok(SPVM::TestCase::Lib::SPVM::Regex->match_zero_more);
  ok(SPVM::TestCase::Lib::SPVM::Regex->match_one_more);
  ok(SPVM::TestCase::Lib::SPVM::Regex->match_offset);
  ok(SPVM::TestCase::Lib::SPVM::Regex->match);
  ok(SPVM::TestCase::Lib::SPVM::Regex->compile);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

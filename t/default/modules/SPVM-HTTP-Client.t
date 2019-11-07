use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';
use TestFile;

use SPVM 'TestCase::Lib::SPVM::HTTP::Client';

# Copy test_files to test_files_tmp with replacing os newline
TestFile::copy_test_files_tmp_replace_newline();

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# SPVM::HTTP::Client
{
  ok(TestCase::Lib::SPVM::HTTP::Client->test_get);
  ok(TestCase::Lib::SPVM::HTTP::Client->test_head);
  ok(TestCase::Lib::SPVM::HTTP::Client->test_post);
  ok(TestCase::Lib::SPVM::HTTP::Client->test_post_form);
  ok(TestCase::Lib::SPVM::HTTP::Client->test_post_form_syntax_sugar);
  ok(TestCase::Lib::SPVM::HTTP::Client->test_get_chunk_small);
  ok(TestCase::Lib::SPVM::HTTP::Client->test_get_chunk_large);
}


# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

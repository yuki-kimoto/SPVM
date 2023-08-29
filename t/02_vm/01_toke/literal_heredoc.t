use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Literal::String';
use SPVM 'TestCase::Literal::StringCRLF';



# Start objects count
my $start_memory_blocks_count = SPVM::api->get_memory_blocks_count();

# String literal
{
  ok(SPVM::TestCase::Literal::String->characters);
  ok(SPVM::TestCase::Literal::String->escape_character);
  ok(SPVM::TestCase::Literal::String->octal_escape_character);
  ok(SPVM::TestCase::Literal::String->hexadecimal_escape_character);
  ok(SPVM::TestCase::Literal::String->unicode_escape_character);
  ok(SPVM::TestCase::Literal::String->raw_escape_character);
  ok(SPVM::TestCase::Literal::String->var_expansion);
  ok(SPVM::TestCase::Literal::String->heredoc_like_lf);
  ok(SPVM::TestCase::Literal::StringCRLF->heredoc_like_crlf);
  ok(SPVM::TestCase::Literal::String->string_literal_extra);
}

# All object is freed
my $end_memory_blocks_count = SPVM::api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;

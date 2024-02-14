use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Literal::StringSingleQuote';
use SPVM 'TestCase::Literal::StringSingleQuoteCRLF';



# Start objects count
my $start_memory_blocks_count = SPVM::api->get_memory_blocks_count();

# StringSingleQuote literal
{
  ok(SPVM::TestCase::Literal::StringSingleQuote->characters);
  ok(SPVM::TestCase::Literal::StringSingleQuote->escape_character);
  ok(SPVM::TestCase::Literal::StringSingleQuoteCRLF->heredoc_like_crlf);
}

# All object is freed
my $end_memory_blocks_count = SPVM::api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;

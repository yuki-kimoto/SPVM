use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Literal::Heredoc';
use SPVM 'TestCase::Literal::HeredocCRLF';



# Start objects count
my $start_memory_blocks_count = SPVM::api->get_memory_blocks_count();

# String literal
{
  ok(SPVM::TestCase::Literal::Heredoc->heredoc);
  ok(SPVM::TestCase::Literal::HeredocCRLF->heredoc);
}

# All object is freed
my $end_memory_blocks_count = SPVM::api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;

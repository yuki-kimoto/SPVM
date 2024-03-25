use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::MulnumArray';



# Start objects count
my $start_memory_blocks_count = SPVM::api->get_memory_blocks_count();

ok(SPVM::TestCase::MulnumArray->mulnum_array_max_fields_byte);
ok(SPVM::TestCase::MulnumArray->mulnum_array_max_fields_short);
ok(SPVM::TestCase::MulnumArray->mulnum_array_max_fields_int);
ok(SPVM::TestCase::MulnumArray->mulnum_array_max_fields_long);
ok(SPVM::TestCase::MulnumArray->mulnum_array_max_fields_float);
ok(SPVM::TestCase::MulnumArray->mulnum_array_max_fields_double);

# All object is freed
my $end_memory_blocks_count = SPVM::api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;

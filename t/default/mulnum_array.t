use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::MulnumArray';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

ok(SPVM::TestCase::MulnumArray->value_array_max_fields_byte);
ok(SPVM::TestCase::MulnumArray->value_array_max_fields_short);
ok(SPVM::TestCase::MulnumArray->value_array_max_fields_int);
ok(SPVM::TestCase::MulnumArray->value_array_max_fields_long);
ok(SPVM::TestCase::MulnumArray->value_array_max_fields_float);
ok(SPVM::TestCase::MulnumArray->value_array_max_fields_double);

ok(SPVM::TestCase::MulnumArray->array_field_byte);
ok(SPVM::TestCase::MulnumArray->array_field_short);
ok(SPVM::TestCase::MulnumArray->array_field_int);
ok(SPVM::TestCase::MulnumArray->array_field_long);
ok(SPVM::TestCase::MulnumArray->array_field_float);
ok(SPVM::TestCase::MulnumArray->array_field_double);

ok(SPVM::TestCase::MulnumArray->array_byte);
ok(SPVM::TestCase::MulnumArray->array_short);
ok(SPVM::TestCase::MulnumArray->array_int);
ok(SPVM::TestCase::MulnumArray->array_long);
ok(SPVM::TestCase::MulnumArray->array_float);
ok(SPVM::TestCase::MulnumArray->array_double);

ok(SPVM::TestCase::MulnumArray->move_byte);
ok(SPVM::TestCase::MulnumArray->move_short);
ok(SPVM::TestCase::MulnumArray->move_int);
ok(SPVM::TestCase::MulnumArray->move_long);
ok(SPVM::TestCase::MulnumArray->move_float);
ok(SPVM::TestCase::MulnumArray->move_double);


# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;

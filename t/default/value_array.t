use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::ValueArray';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

ok(TestCase::ValueArray->value_array_max_fields_byte);
ok(TestCase::ValueArray->value_array_max_fields_short);
ok(TestCase::ValueArray->value_array_max_fields_int);
ok(TestCase::ValueArray->value_array_max_fields_long);
ok(TestCase::ValueArray->value_array_max_fields_float);
ok(TestCase::ValueArray->value_array_max_fields_double);

ok(TestCase::ValueArray->array_field_byte);
ok(TestCase::ValueArray->array_field_short);
ok(TestCase::ValueArray->array_field_int);
ok(TestCase::ValueArray->array_field_long);
ok(TestCase::ValueArray->array_field_float);
ok(TestCase::ValueArray->array_field_double);

ok(TestCase::ValueArray->array_byte);
ok(TestCase::ValueArray->array_short);
ok(TestCase::ValueArray->array_int);
ok(TestCase::ValueArray->array_long);
ok(TestCase::ValueArray->array_float);
ok(TestCase::ValueArray->array_double);

ok(TestCase::ValueArray->move_byte);
ok(TestCase::ValueArray->move_short);
ok(TestCase::ValueArray->move_int);
ok(TestCase::ValueArray->move_long);
ok(TestCase::ValueArray->move_float);
ok(TestCase::ValueArray->move_double);


# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

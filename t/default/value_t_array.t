use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::ValueTArray';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

ok(TestCase::ValueTArray->array_field_byte);
ok(TestCase::ValueTArray->array_field_short);
ok(TestCase::ValueTArray->array_field_int);
ok(TestCase::ValueTArray->array_field_long);
ok(TestCase::ValueTArray->array_field_float);
ok(TestCase::ValueTArray->array_field_double);

ok(TestCase::ValueTArray->array_byte);
ok(TestCase::ValueTArray->array_short);
ok(TestCase::ValueTArray->array_int);
ok(TestCase::ValueTArray->array_long);
ok(TestCase::ValueTArray->array_float);
ok(TestCase::ValueTArray->array_double);

ok(TestCase::ValueTArray->move_byte);
ok(TestCase::ValueTArray->move_short);
ok(TestCase::ValueTArray->move_int);
ok(TestCase::ValueTArray->move_long);
ok(TestCase::ValueTArray->move_float);
ok(TestCase::ValueTArray->move_double);

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

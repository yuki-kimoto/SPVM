use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::ValueTArray';

# Start objects count
my $start_objects_count = SPVM::get_objects_count();

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

# All object is freed
my $end_objects_count = SPVM::get_objects_count();
is($end_objects_count, $start_objects_count);

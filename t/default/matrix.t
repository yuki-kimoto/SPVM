use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';


use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'TestCase::Lib::SPVM::Matrix';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

ok(TestCase::Lib::SPVM::Matrix->matrix_float);
ok(TestCase::Lib::SPVM::Matrix->matrix_double);

ok(TestCase::Lib::SPVM::Matrix->matrix_add_float);
ok(TestCase::Lib::SPVM::Matrix->matrix_add_double);

ok(TestCase::Lib::SPVM::Matrix->matrix_sub_float);
ok(TestCase::Lib::SPVM::Matrix->matrix_sub_double);

ok(TestCase::Lib::SPVM::Matrix->matrix_scamul_float);
ok(TestCase::Lib::SPVM::Matrix->matrix_scamul_double);

ok(TestCase::Lib::SPVM::Matrix->matrix_new_zero_float);
ok(TestCase::Lib::SPVM::Matrix->matrix_new_zero_double);

ok(TestCase::Lib::SPVM::Matrix->matrix_new_ident_float);
ok(TestCase::Lib::SPVM::Matrix->matrix_new_ident_double);

ok(TestCase::Lib::SPVM::Matrix->matrix_mul_float);
ok(TestCase::Lib::SPVM::Matrix->matrix_mul_double);

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);



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

ok(TestCase::Lib::SPVM::Matrix->matrix_byte);
ok(TestCase::Lib::SPVM::Matrix->matrix_short);
ok(TestCase::Lib::SPVM::Matrix->matrix_int);
ok(TestCase::Lib::SPVM::Matrix->matrix_long);
ok(TestCase::Lib::SPVM::Matrix->matrix_float);
ok(TestCase::Lib::SPVM::Matrix->matrix_double);

ok(TestCase::Lib::SPVM::Matrix->matrix_add_byte);

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);



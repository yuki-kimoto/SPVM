use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';


use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'TestCase::UnaryPlus';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

# Unary plus
{
  ok(TestCase::UnaryPlus->unary_plus_byte);
  ok(TestCase::UnaryPlus->unary_plus_short);
  ok(TestCase::UnaryPlus->unary_plus_int);
  ok(TestCase::UnaryPlus->unary_plus_long);
  ok(TestCase::UnaryPlus->unary_plus_float);
  ok(TestCase::UnaryPlus->unary_plus_double);
}

# Compile Error
{
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::UnaryPlus::NotNumeric');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
}

=cut

# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);


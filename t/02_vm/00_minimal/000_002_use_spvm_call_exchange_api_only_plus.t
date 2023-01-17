use strict;
use warnings;

use Test::More;

use SPVM;

SPVM::get_memory_blocks_count();

my $obj_int = SPVM::ExchangeAPI::call_method(SPVM::GET_ENV(), SPVM::GET_STACK(), "Int", "new", 1);
my $value = $obj_int->value;

is($value, 1);

done_testing;

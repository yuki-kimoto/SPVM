use strict;
use warnings;

use Test::More;

use SPVM;

SPVM::get_memory_blocks_count();

my $obj_int = SPVM::ExchangeAPI::call_method(SPVM::api(), "Int", "new", 1);

my $value = SPVM::ExchangeAPI::call_method(SPVM::api(), $obj_int, "value");
is($value, 1);

is($obj_int->value, 1);

done_testing;

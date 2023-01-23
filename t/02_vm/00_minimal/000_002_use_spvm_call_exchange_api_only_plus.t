use strict;
use warnings;

use Test::More;

use SPVM;

SPVM::api->get_memory_blocks_count();

my $api = SPVM::api();

my $obj_int = $api->call_method("Int", "new", 1);

my $value = $obj_int->value;
is($value, 1);

is($obj_int->value, 1);

done_testing;

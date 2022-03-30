use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'MinimalMethod';

SPVM::MinimalMethod->foo;

ok(1);

done_testing;

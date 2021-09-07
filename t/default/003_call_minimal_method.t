use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More tests => 1;

use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'SPVM::MinimalMethod';

SPVM::MinimalMethod->foo;

ok(1);

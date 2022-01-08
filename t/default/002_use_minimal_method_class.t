use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More tests => 1;

use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'MinimalMethod';

ok(1);

done_testing;

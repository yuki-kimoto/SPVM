use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More tests => 1;

use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'EmptyClass';

ok(1);

done_testing;

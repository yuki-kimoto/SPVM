use lib "t/lib";
use TestAuto;
use TestUtil::MyLib;
use TestUtil;

use strict;
use warnings;

use Test::More;

use Config;

use SPVM 'MinimalMethod';

my $build_dir = $ENV{SPVM_BUILD_DIR};

SPVM::MinimalMethod->foo;

ok(1);

done_testing;

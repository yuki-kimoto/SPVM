use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use FindBin;
use lib "$FindBin::Bin/lib";
use Config;

use SPVM 'MinimalMethod';

SPVM::MinimalMethod->foo;

# Check precompile module file
my $precompile_module_file = "$FindBin::Bin/.spvm_build/work/lib/SPVM/MinimalMethod.precompile.$Config{dlext}";
if ($ENV{SPVM_TEST_PRECOMPILE}) {
  ok(-f $precompile_module_file);
}
else {
  warn $precompile_module_file;
  ok(!-f $precompile_module_file);
}

ok(1);

done_testing;

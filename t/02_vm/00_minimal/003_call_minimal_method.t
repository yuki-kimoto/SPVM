use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use Config;

use SPVM 'MinimalMethod';

my $build_dir = $ENV{SPVM_BUILD_DIR};

SPVM::MinimalMethod->foo;

# Check precompile module file
my $precompile_module_file = "$build_dir/work/lib/SPVM/MinimalMethod.precompile.$Config{dlext}";
if ($ENV{SPVM_TEST_PRECOMPILE}) {
  ok(-f $precompile_module_file);
}
else {
  ok(!-f $precompile_module_file);
}

ok(1);

done_testing;

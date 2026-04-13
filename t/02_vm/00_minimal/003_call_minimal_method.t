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

# Check precompile class file
my ($precompile_class_file) = glob "$build_dir/work/lib/*/*/SPVM/MinimalMethod.precompile.$Config{dlext}";
if (TestUtil::is_in_precompile_test) {
  ok(defined $precompile_class_file);
}
else {
  ok(!defined $precompile_class_file);
}

ok(1);

done_testing;

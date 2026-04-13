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

# Check JIT class file
# Use glob to find precompile class files. 
# Since process ID isolation is used in JIT mode, multiple directories may exist 
# during parallel testing. We check that at least one such file (ideally our own) is found.
my @precompile_class_files = glob "$build_dir/work/lib/*/*/SPVM/MinimalMethod.precompile.$Config{dlext}";
if (TestUtil::is_in_precompile_test) {
  ok(scalar @precompile_class_files);
}

ok(1);

done_testing;

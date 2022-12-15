use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use Config;

use SPVM::Builder::Util;

use SPVM 'MinimalMethod';

my $build_dir = $ENV{SPVM_BUILD_DIR};

SPVM::MinimalMethod->foo;

# Check precompile module file
my $precompile_module_file = SPVM::Builder::Util::convert_module_file_to_dynamic_lib_file("$build_dir/work/lib/SPVM/MinimalMethod.spvm", 'precompile');
if ($ENV{SPVM_TEST_PRECOMPILE}) {
  ok(-f $precompile_module_file);
}
else {
  ok(!-f $precompile_module_file);
}

ok(1);

done_testing;

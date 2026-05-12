use strict;
use warnings;

use Test::More;

use lib "t/lib";
use TestAuto;
use TestUtil;
use TestUtil::MyLib;

use utf8;
use Config;
use File::Basename 'basename';
use File::Path 'mkpath', 'rmtree';
use File::Spec;
use File::Temp;
use Config;
use SPVM::Builder;
use SPVM::Builder::Util;

# TODO:
# This test is currently skipped when ASan is enabled because it causes 
# an initialization order failure (AddressSanitizer CHECK failed: real___cxa_throw != 0).
# This happens because the dynamic library loaded via DynaLoader attempts to 
# intercept C++ exceptions before the environment is fully ready.
# This should be fixed in the future, but GitHub Actions CI with --asan takes priority.
if ($ENV{LD_PRELOAD}) {
  plan skip_all => "Skip spvmcc dll test under ASan to prioritize CI stability.";
}

my $devnull = File::Spec->devnull;

my $inc_dir = "$FindBin::Bin/lib";
my $spvm_script_dir = 't/08_spvmcc/script';
my $build_dir = $ENV{SPVM_BUILD_DIR};

my $tmp_dir = File::Temp->newdir;

{
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -B $build_dir -I $inc_dir --mode dll --quiet -o $tmp_dir/myapp $spvm_script_dir/myapp.spvm);
    system($spvmcc_cmd) == 0
      or die "Can't execute spvmcc command $spvmcc_cmd:$!";
    
    ok(-f "$tmp_dir/myapp.$Config{dlext}");
    ok(-f "$tmp_dir/myapp.pl");
    
    my $execute_cmd = "$^X $tmp_dir/myapp.pl";
    my $execute_cmd_with_args = "$execute_cmd args0";
    my $output = `$execute_cmd_with_args`;
    chomp $output;
    is($output, 1);
  }
}

done_testing;

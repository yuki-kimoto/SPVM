BEGIN { $ENV{SPVM_BUILD_DIR} = '.spvm_build' }

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

use SPVM::Builder;
use SPVM::Builder::Util;

my $devnull = File::Spec->devnull;

my $inc_dir = "$FindBin::Bin/lib";
my $spvm_script_dir = 't/08_spvmcc/script';
my $build_dir = $ENV{SPVM_BUILD_DIR};

my $tmp_dir = File::Temp->newdir;

{
  # Basic
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -B $build_dir -I $inc_dir --mode msvc -o $tmp_dir/myapp $spvm_script_dir/myapp.spvm);
    system($spvmcc_cmd) == 0
      or die "Can't execute spvmcc command $spvmcc_cmd:$!";
    
    my $execute_cmd = TestUtil::to_os_specific_path("$tmp_dir/myapp");
    my $execute_cmd_with_args = "$execute_cmd args1 args2";
    my $output = `$execute_cmd_with_args`;
    chomp $output;
    my $output_expect = "AAA $execute_cmd 3 1 1 7 25 args1 args2 1";
    is($output, $output_expect);
  }
}

done_testing;

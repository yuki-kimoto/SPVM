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
use Config;
use SPVM::Builder;
use SPVM::Builder::Util;

my $devnull = File::Spec->devnull;

my $inc_dir = "$FindBin::Bin/lib";
my $spvm_script_dir = 't/08_spvmcc/script';
my $build_dir = $ENV{SPVM_BUILD_DIR};

my $tmp_dir = File::Temp->newdir;

{
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -B $build_dir -I $inc_dir --mode dll -o $tmp_dir/myapp $spvm_script_dir/myapp.spvm);
    system($spvmcc_cmd) == 0
      or die "Can't execute spvmcc command $spvmcc_cmd:$!";
    
    ok(-f "$tmp_dir/myapp.$Config{dlext}");
    ok(-f "$tmp_dir/myapp.pl");
  }
}

done_testing;

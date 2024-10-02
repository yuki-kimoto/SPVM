use lib "t/testlib";
use TestAuto;

use Test::More;
use strict;
use warnings;
use utf8;
use Data::Dumper;
use File::Basename 'basename';
use Config;
use File::Path 'mkpath', 'rmtree';
use File::Spec;
use SPVM::Builder::Util;

use SPVM::Builder;
use File::Spec;

my $devnull = File::Spec->devnull;

my $test_dir = $ENV{SPVM_TEST_DIR};
my $build_dir = $ENV{SPVM_BUILD_DIR};

my @build_dir_parts = split('/', $build_dir);
my $exe_dir = "$build_dir/work/exe";

rmtree "$build_dir/work";

my $dev_null = File::Spec->devnull;

# spvm - Execute solo test.
{
  {
    my $spvm_cmd = qq($^X -Mblib blib/script/spvm -I solo/lib/SPVM MyExe foo bar);
    system($spvm_cmd) == 0
     or die "Can't execute spvmcc command $spvm_cmd:$!";
    
    ok(1);
  }
  
  {
    my $spvm_cmd = qq($^X -Mblib blib/script/spvm -B $build_dir -I solo/lib/SPVM MyExe foo bar);
    system($spvm_cmd) == 0
     or die "Can't execute spvmcc command $spvm_cmd:$!";
    
    ok(1);
  }
  
  # -B
  {
    my $spvm_cmd = qq($^X -Mblib blib/script/spvm -B $build_dir -I solo/lib/SPVM MyExe foo bar);
    system($spvm_cmd) == 0
     or die "Can't execute spvmcc command $spvm_cmd:$!";
    
    ok(1);
  }
  
  # --build-dir
  {
    my $spvm_cmd = qq($^X -Mblib blib/script/spvm --build-dir $build_dir -I solo/lib/SPVM -e "warn q'[Test Output]spvmcc -e option';" MyExe);
    system($spvm_cmd) == 0
     or die "Can't execute spvmcc command $spvm_cmd:$!";
    
    ok(1);
  }
  
  # -e, -M
  {
    my $spvm_cmd = qq($^X -Mblib blib/script/spvm -I solo/lib/SPVM -M Fn -M StringBuffer -e "Fn->INT_MAX; StringBuffer->new;warn q'[Test Output]spvmcc -e and -M option';");
    system($spvm_cmd) == 0
     or die "Can't execute spvmcc command $spvm_cmd:$!";
    
    ok(1);
  }
}

done_testing;

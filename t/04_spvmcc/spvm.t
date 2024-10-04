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
use FindBin;

use SPVM::Builder;
use File::Spec;

my $devnull = File::Spec->devnull;

my $test_dir = $ENV{SPVM_TEST_DIR};
my $build_dir = $ENV{SPVM_BUILD_DIR};

my @build_dir_parts = split('/', $build_dir);
my $exe_dir = "$build_dir/work/exe";

rmtree "$build_dir/work";

my $dev_null = File::Spec->devnull;

# Failed to parse options.
{
  {
    my $spvm_cmd = qq($^X -Mblib blib/script/spvm --not-exist t/04_spvmcc/script/myapp.spvm);
    my $status = system($spvm_cmd);
    isnt($status, 0);
  }
}

{
  {
    my $spvm_cmd = qq($^X -Mblib blib/script/spvm -I solo/lib/SPVM solo/script/myapp.spvm foo bar);
    system($spvm_cmd) == 0
     or die "Can't execute spvm command $spvm_cmd:$!";
    
    ok(1);
  }
  
  {
    my $spvm_cmd = qq($^X -Mblib blib/script/spvm -B $build_dir -I solo/lib/SPVM solo/script/myapp.spvm foo bar);
    system($spvm_cmd) == 0
     or die "Can't execute spvm command $spvm_cmd:$!";
    
    ok(1);
  }
  
  # -B
  {
    my $spvm_cmd = qq($^X -Mblib blib/script/spvm -B $build_dir -I solo/lib/SPVM solo/script/myapp.spvm foo bar);
    system($spvm_cmd) == 0
     or die "Can't execute spvm command $spvm_cmd:$!";
    
    ok(1);
  }
  
  
  # -E
  {
    my $spvm_cmd = qq($^X -Mblib blib/script/spvm -I solo/lib/SPVM -E "class { static method main : void () { warn q'[Test Output]spvm -E option'; } }");
    system($spvm_cmd) == 0
     or die "Can't execute spvm command $spvm_cmd:$!";
    
    ok(1);
  }
  
  # --build-dir and -e
  {
    my $spvm_cmd = qq($^X -Mblib blib/script/spvm --build-dir $build_dir -I solo/lib/SPVM -e "warn q'[Test Output]spvm -e option';");
    system($spvm_cmd) == 0
     or die "Can't execute spvm command $spvm_cmd:$!";
    
    ok(1);
  }
  
  # -e, -M
  {
    my $spvm_cmd = qq($^X -Mblib blib/script/spvm -I solo/lib/SPVM -M Fn -M StringBuffer -e "Fn->INT_MAX; StringBuffer->new;warn q'[Test Output]spvm -e and -M option';");
    system($spvm_cmd) == 0
     or die "Can't execute spvm command $spvm_cmd:$!";
    
    ok(1);
  }
  
  # basic
  {
    my $spvm_cmd = qq($^X -Mblib blib/script/spvm $FindBin::Bin/script/basic.spvm);
    system($spvm_cmd) == 0
     or die "Can't execute spvm command $spvm_cmd:$!";
    
    ok(1);
  }
  
  # prcompile
  {
    my $spvm_cmd = qq($^X -Mblib blib/script/spvm -I t/04_spvmcc/lib/SPVM $FindBin::Bin/script/precompile.spvm);
    system($spvm_cmd) == 0
     or die "Can't execute spvm command $spvm_cmd:$!";
    
    ok(1);
  }
  
  {
    my $spvm_cmd = qq($^X -Mblib blib/script/spvm t/04_spvmcc/script/program_name.spvm);
    my $spvm_output = `$spvm_cmd`;
    like($spvm_output, qr|t/04_spvmcc/script/program_name\.spvm|);
  }
  
}


done_testing;

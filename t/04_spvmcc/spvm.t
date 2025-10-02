use lib "t/testlib";
use TestAuto;

use Test::More;
use strict;
use warnings;
use utf8;
use Data::Dumper;
use File::Basename 'basename', 'dirname';
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

my $dev_null = File::Spec->devnull;

# -c option
{
  {
    my $spvm_cmd = "$^X -Mblib blib/script/spvm -c -I solo/lib/SPVM solo/script/myapp.spvm foo bar";
    my $output = `$spvm_cmd`;
    
    is($output, '');
  }
  
  {
    my $spvm_cmd = "$^X -Mblib blib/script/spvm -c -I solo/lib/SPVM solo/script/myapp.spvm foo bar 2>&1";
    my $output = `$spvm_cmd`;
    
    is($output, "syntax OK\n");
  }
}

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
  
  # -w
  {
    my $spvm_cmd = qq($^X -Mblib blib/script/spvm -w -I solo/lib/SPVM solo/script/myapp.spvm foo bar);
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
  
  # lib directive
  {
    my $spvm_cmd = qq($^X -Mblib blib/script/spvm $FindBin::Bin/script/use-class.spvm);
    my $output = `$spvm_cmd`;
    like($output, qr/3000/);
  }
  
  # shebang
  if ($^O eq 'MSWin32') {
    warn "[Test Output]A test for shebang is skipped.";
  }
  else {
    local $ENV{PATH} = "blib/script:$ENV{PATH}";
    local $ENV{PERL5LIB} = "blib/lib:blib/arch:$ENV{PERL5LIB}";
    my $spvm_cmd = qq($FindBin::Bin/script/use-class.spvm);
    my $output = `$spvm_cmd`;
    like($output, qr/3000/);
  }
  
  # prcompile
  {
    my $spvm_cmd = qq($^X -Mblib blib/script/spvm -I t/04_spvmcc/lib/SPVM $FindBin::Bin/script/precompile.spvm);
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
  
  # anon method
  {
    my $spvm_cmd = qq($^X -Mblib blib/script/spvm $FindBin::Bin/script/anon_method.spvm);
    my $output = `$spvm_cmd`;
    like($output, qr/OK/);
  }
  
}


done_testing;

use lib "t/lib";
use TestAuto;
use TestUtil::MyLib;

use Test::More;

use strict;
use warnings;
use utf8;
use Config;
use File::Basename 'basename';
use File::Path 'mkpath', 'rmtree';
use File::Spec;

use SPVM::Builder;
use SPVM::Builder::Util;

my $devnull = File::Spec->devnull;

my $test_dir = "$FindBin::Bin";
my $test_script_dir = 't/04_spvmcc/script';
my $build_dir = $ENV{SPVM_BUILD_DIR};

my $exe_dir = "$build_dir/.tmp/exe";
my $external_object_dir = "$build_dir/.tmp/external_object";

rmtree "$build_dir/work";

mkpath $exe_dir;
mkpath $external_object_dir;

my $dev_null = File::Spec->devnull;

sub to_cmd {
  my ($path) = @_;
  
  my $cmd = File::Spec->catfile(split("/", $path));
  
  return $cmd;
}

{
  # Basic
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -B $build_dir -I $test_dir/lib/SPVM -o $exe_dir/myapp $test_script_dir/myapp.spvm);
    system($spvmcc_cmd) == 0
      or die "Can't execute spvmcc command $spvmcc_cmd:$!";
    
    my $execute_cmd = &to_cmd("$exe_dir/myapp");
    my $execute_cmd_with_args = "$execute_cmd args1 args2";
    my $output = `$execute_cmd_with_args`;
    chomp $output;
    my $output_expect = "AAA $execute_cmd 3 1 1 7 25 args1 args2 1";
    is($output, $output_expect);
    
    # Check -B option
    {
      ok(-f "$exe_dir/myapp$Config{exe_ext}");
    }
    {
      ok(-d "$build_dir/spvmcc/myapp");
    }
  }

  # Compile and link cached
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -B $build_dir -I $test_dir/lib/SPVM -o $exe_dir/myapp $test_script_dir/myapp.spvm);
    my $spvmcc_output = `$spvmcc_cmd 2>&1 1>$dev_null`;
    if (length $spvmcc_output == 0) {
      ok(1);
    }
    else {
      ok(0);
      warn "[Test Failed]$spvmcc_output";
    }
  }
}

# END block
{
  my $spvm_script = "$test_script_dir/end-block.spvm";
  my $exe_file = "$exe_dir/end-block";
  
  # Compile with --no-config
  my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -q --no-config -B $build_dir -I $test_dir/lib/SPVM -o $exe_file $spvm_script);
  system($spvmcc_cmd) == 0 or die "Can't execute spvmcc command $spvmcc_cmd:$!";
  
  # Execute and check
  my $output = `$exe_file`;
  is($output, "END 1\n", "END block execution");
}

{
  # lib directive
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -q --build-dir $build_dir -o $exe_dir/use-class $test_script_dir/use-class.spvm);
    system($spvmcc_cmd) == 0
      or die "Can't execute spvmcc command $spvmcc_cmd:$!";
    
    my $execute_cmd = &to_cmd("$exe_dir/use-class");
    my $output = `$execute_cmd`;
    chomp $output;
    like($output, qr/3000/);
  }
}

# External objects
{
  my $cc_cmd = qq($Config{cc} -c -o $external_object_dir/external.o t/04_spvmcc/lib/SPVM/external.c);
  system($cc_cmd) == 0
    or die "Can't execute cc command $cc_cmd:$!";
  
  # --object-file
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc --quiet -B $build_dir -I $test_dir/lib/SPVM --object-file $external_object_dir/external.o -o $exe_dir/external $test_script_dir/external.spvm);
    system($spvmcc_cmd) == 0
      or die "Can't execute spvmcc command $spvmcc_cmd:$!";
    
    my $execute_cmd = &to_cmd("$exe_dir/external");
    my $output = `$execute_cmd`;
    chomp $output;
    my $output_expect = "40";
    is($output, $output_expect);
  }
  
}

{
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -B $build_dir -I $test_dir/lib/SPVM -o $exe_dir/myapp $test_script_dir/myapp.spvm);
    system($spvmcc_cmd) == 0
      or die "Can't execute spvmcc command $spvmcc_cmd:$!";

    my $execute_cmd = &to_cmd("$exe_dir/myapp");
    my $execute_cmd_with_args = "$execute_cmd args1 args2";
    my $output = `$execute_cmd_with_args`;
    chomp $output;
    my $output_expect = "AAA $execute_cmd 3 1 1 7 25 args1 args2 1";
    is($output, $output_expect);
    
    # Check -B option
    {
      ok(-f "$exe_dir/myapp$Config{exe_ext}");
    }
  }
}

# -h, --help
{
  {
    my $spvmdist_cmd = qq($^X -Mblib blib/script/spvmcc -h);
    my $output = `$spvmdist_cmd`;
    like($output, qr/\QUsage: spvmcc [OPTIONS] SCRIPT_NAME/);
  }
  {
    my $spvmdist_cmd = qq($^X -Mblib blib/script/spvmcc --help);
    my $output = `$spvmdist_cmd`;
    like($output, qr/\QUsage: spvmcc [OPTIONS] SCRIPT_NAME/);
  }
}

{
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc --quiet -B $build_dir -o $exe_dir/program_name $test_script_dir/program_name.spvm);
    system($spvmcc_cmd) == 0
      or die "Can't execute spvmcc command $spvmcc_cmd:$!";
    
    my $execute_cmd = &to_cmd("$exe_dir/program_name");
    my $execute_cmd_with_args = "$execute_cmd args1 args2";
    my $output = `$execute_cmd_with_args`;
    chomp $output;
    my $output_expect = "$execute_cmd";
    is($output, $output_expect);
  }
  
  # debug config -O0 -g
  {
    my $mode = 'debug';
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -f -B $build_dir -I $test_dir/lib/SPVM -o $exe_dir/myapp --mode debug $test_script_dir/myapp.spvm);
    my $spvmcc_output = `$spvmcc_cmd`;
    like($spvmcc_output, qr/NativeAPI2\.o/);
    like($spvmcc_output, qr/NativeAPI2\.precompile\.o/);
    like($spvmcc_output, qr/\Q-O0 -g3/);
    like($spvmcc_output, qr/-L\./);
    like($spvmcc_output, qr/-lm\b/);
    like($spvmcc_output, qr/-std=c99/);
    
    # Note: Arguments of the link command(these contain -l flags) must be
    # after object file names for resolving symbol names properly
    like($spvmcc_output, qr/NativeAPI2\.o.+-L\..+-lm\b/);
    
    my $execute_cmd = &to_cmd("$exe_dir/myapp");
    my $execute_cmd_with_args = "$execute_cmd args1 args2";
    my $output = `$execute_cmd_with_args`;
    chomp $output;
    my $output_expect = "AAA $execute_cmd 3 1 1 7 25 args1 args2 1";
    is($output, $output_expect);
    
    {
      ok(-d "$build_dir/spvmcc/myapp.$mode");
    }
  }

}

done_testing;

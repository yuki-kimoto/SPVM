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

my $dev_null = File::Spec->devnull;

my $tmp_dir = File::Temp->newdir;

my $external_object_dir = "$tmp_dir/external_object";

mkpath $external_object_dir;

{
  # Basic
  # build_type - Release
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -B $build_dir -I $inc_dir --quiet -o $tmp_dir/myapp $spvm_script_dir/myapp.spvm);
    system($spvmcc_cmd) == 0
      or die "Can't execute spvmcc command $spvmcc_cmd:$!";
    
    my $execute_cmd = TestUtil::to_os_specific_path("$tmp_dir/myapp");
    my $execute_cmd_with_args = "$execute_cmd";
    my $output = `$execute_cmd_with_args`;
    chomp $output;
    is($output, 1);
    
    # Check -B option
    {
      ok(-f "$tmp_dir/myapp$Config{exe_ext}");
    }
  }

  # Compile and link cached
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -B $build_dir -I $inc_dir -o $tmp_dir/myapp $spvm_script_dir/myapp.spvm);
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
  my $spvm_script = "$spvm_script_dir/end-block.spvm";
  my $exe_file = "$tmp_dir/end-block";
  
  # Compile with --no-config
  my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -q --no-config -B $build_dir -I $inc_dir --quiet -o $exe_file $spvm_script);
  system($spvmcc_cmd) == 0 or die "Can't execute spvmcc command $spvmcc_cmd:$!";
  
  # Execute and check
  my $output = `$exe_file`;
  is($output, "END 1\n", "END block execution");
}

{
  # lib directive
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -q --build-dir $build_dir --quiet -o $tmp_dir/use-class $spvm_script_dir/use-class.spvm);
    system($spvmcc_cmd) == 0
      or die "Can't execute spvmcc command $spvmcc_cmd:$!";
    
    my $execute_cmd = TestUtil::to_os_specific_path("$tmp_dir/use-class");
    my $output = `$execute_cmd`;
    chomp $output;
    like($output, qr/3000/);
  }
}

# External objects
{
  my $cc_cmd = qq($Config{cc} -c -o $external_object_dir/external.o t/08_spvmcc/lib/SPVM/external.c);
  system($cc_cmd) == 0
    or die "Can't execute cc command $cc_cmd:$!";
  
  # --object-file
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc --quiet -B $build_dir -I $inc_dir --object-file $external_object_dir/external.o --quiet -o $tmp_dir/external $spvm_script_dir/external.spvm);
    system($spvmcc_cmd) == 0
      or die "Can't execute spvmcc command $spvmcc_cmd:$!";
    
    my $execute_cmd = TestUtil::to_os_specific_path("$tmp_dir/external");
    my $output = `$execute_cmd`;
    chomp $output;
    my $output_expect = "40";
    is($output, $output_expect);
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
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc --quiet -B $build_dir --quiet -o $tmp_dir/program_name $spvm_script_dir/program_name.spvm);
    system($spvmcc_cmd) == 0
      or die "Can't execute spvmcc command $spvmcc_cmd:$!";
    
    my $execute_cmd = TestUtil::to_os_specific_path("$tmp_dir/program_name");
    my $execute_cmd_with_args = "$execute_cmd args1 args2";
    my $output = `$execute_cmd_with_args`;
    chomp $output;
    my $output_expect = "$execute_cmd";
    is($output, $output_expect);
  }
}

{
  # Varaiout tests
  # build_type - Release
  {
    my $tmp_dir = File::Temp->newdir;
    
    my $mode = 'debug';
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -B $tmp_dir -I $inc_dir -o $tmp_dir/myapp --mode test $spvm_script_dir/myapp.spvm 2>&1);
    my $spvmcc_output = `$spvmcc_cmd`;
    like($spvmcc_output, qr/NativeAPI2\.o/);
    like($spvmcc_output, qr/NativeAPI2\.precompile\.o/);
    like($spvmcc_output, qr/\Q-g /);
    like($spvmcc_output, qr/-L\./);
    like($spvmcc_output, qr/-lm\b/);
    like($spvmcc_output, qr/-std=c99/);
    
    like($spvmcc_output, qr/NativeAPI2\.o.+-L\..+-lm\b/);
    
    my $execute_cmd = TestUtil::to_os_specific_path("$tmp_dir/myapp");
    my $execute_cmd_with_args = "$execute_cmd";
    my $output = `$execute_cmd_with_args`;
    chomp $output;
    is($output, 1);
  }
}

# build_type
{
  # build_type - Release
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -B $build_dir -I $inc_dir --mode Release --quiet -o $tmp_dir/myapp $spvm_script_dir/myapp.spvm);
    system($spvmcc_cmd) == 0
      or die "Can't execute spvmcc command $spvmcc_cmd:$!";
    
    my $execute_cmd = TestUtil::to_os_specific_path("$tmp_dir/myapp");
    my $execute_cmd_with_args = "$execute_cmd";
    my $output = `$execute_cmd_with_args`;
    chomp $output;
    is($output, 1);
  }
  
  # build_type - Debug
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -B $build_dir -I $inc_dir --mode Debug --quiet -o $tmp_dir/myapp $spvm_script_dir/myapp.spvm);
    system($spvmcc_cmd) == 0
      or die "Can't execute spvmcc command $spvmcc_cmd:$!";
    
    my $execute_cmd = TestUtil::to_os_specific_path("$tmp_dir/myapp");
    my $execute_cmd_with_args = "$execute_cmd";
    my $output = `$execute_cmd_with_args`;
    chomp $output;
    is($output, 1);
  }
  
  # build_type - RelWithDebInfo
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -B $build_dir -I $inc_dir --mode RelWithDebInfo --quiet -o $tmp_dir/myapp $spvm_script_dir/myapp.spvm);
    system($spvmcc_cmd) == 0
      or die "Can't execute spvmcc command $spvmcc_cmd:$!";
    
    my $execute_cmd = TestUtil::to_os_specific_path("$tmp_dir/myapp");
    my $execute_cmd_with_args = "$execute_cmd";
    my $output = `$execute_cmd_with_args`;
    chomp $output;
    is($output, 1);
  }
  
  # build_type - MinSizeRel
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -B $build_dir -I $inc_dir --mode MinSizeRel --quiet -o $tmp_dir/myapp $spvm_script_dir/myapp.spvm);
    system($spvmcc_cmd) == 0
      or die "Can't execute spvmcc command $spvmcc_cmd:$!";
    
    my $execute_cmd = TestUtil::to_os_specific_path("$tmp_dir/myapp");
    my $execute_cmd_with_args = "$execute_cmd";
    my $output = `$execute_cmd_with_args`;
    chomp $output;
    is($output, 1);
  }
}

done_testing;

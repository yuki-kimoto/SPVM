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

my $test_dir = $ENV{SPVM_TEST_DIR};
my $build_dir = $ENV{SPVM_BUILD_DIR};

my @build_dir_parts = split('/', $build_dir);
my $exe_dir = "$build_dir/work/exe";

rmtree "$build_dir/work";

my $dev_null = File::Spec->devnull;

# -h, --help
{
  {
    my $spvmdist_cmd = qq($^X -Mblib blib/scrip$test_dir -h);
    my $output = `$spvmdist_cmd`;
    like($output, qr/\Qusage: spvmcc [<options>] <class_name>/);
  }
  {
    my $spvmdist_cmd = qq($^X -Mblib blib/scrip$test_dir --help);
    my $output = `$spvmdist_cmd`;
    like($output, qr/\Qusage: spvmcc [<options>] <class_name>/);
  }
}

{
  mkpath $exe_dir;

  # --print-dependent-resources, -p
  for my $option ('--print-dependent-resources', '-p'){
    my $spvmcc_cmd = qq($^X -Mblib blib/scrip$test_dir -I $test_dir/lib/SPVM -I t/default/lib/SPVM $option MyExe);
    my @lines = `$spvmcc_cmd`;
    is($lines[0], '{class_name:"TestCase::NativeAPI2",resource_class_name:"TestCase::Resource::Mylib1::V1_0_0",resource_mode:"mode1",resource_args:["args1","args2"]}' . "\n");
    is($lines[1], '{class_name:"TestCase::NativeAPI2",resource_class_name:"TestCase::Resource::Mylib2::V1_0_0",resource_mode:undefined,resource_args:[]}' . "\n");
  }
  
  # Basic
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/scrip$test_dir -B $build_dir -I $test_dir/lib/SPVM -o $exe_dir/myexe -c $test_dir/myexe.config MyExe);
    system($spvmcc_cmd) == 0
      or die "Can't execute spvmcc command $spvmcc_cmd:$!";

    my $execute_cmd = File::Spec->catfile(@build_dir_parts, qw/work exe myexe/);
    my $execute_cmd_with_args = "$execute_cmd args1 args2";
    system($execute_cmd_with_args) == 0
      or die "Can't execute command:$execute_cmd_with_args:$!";
    
    my $output = `$execute_cmd_with_args`;
    chomp $output;
    my $output_expect = "AAA $execute_cmd 3 1 1 7 args1 args2";
    is($output, $output_expect);
    
    # Check -B option
    {
      ok(-f "$build_dir/work/exe/myexe$Config{exe_ext}");
    }
  }

  # Compile and link cached
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/scrip$test_dir --build-dir $build_dir -I $test_dir/lib/SPVM -o $exe_dir/myexe -c $test_dir/myexe.config MyExe);
    my $spvmcc_output = `$spvmcc_cmd 2>&1 1>$dev_null`;
    ok(length $spvmcc_output == 0);
  }
  
  # debug config -O0 -g
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/scrip$test_dir -f -B $build_dir -I $test_dir/lib/SPVM -o $exe_dir/myexe --config $test_dir/myexe.debug.config MyExe);
    my $spvmcc_output = `$spvmcc_cmd 2>&1 1>$dev_null`;
    like($spvmcc_output, qr/\Q-O0 -g/);
    like($spvmcc_output, qr/-lm\b/);
    like($spvmcc_output, qr/-L\./);
    like($spvmcc_output, qr/-std=gnu99/);
    like($spvmcc_output, qr/NativeAPI2\.o/);
    like($spvmcc_output, qr/NativeAPI2\.precompile\.o/);
    
    warn "$spvmcc_output";

    my $execute_cmd = File::Spec->catfile(@build_dir_parts, qw/work exe myexe/);
    my $execute_cmd_with_args = "$execute_cmd args1 args2";
    system($execute_cmd_with_args) == 0
      or die "Can't execute command: $execute_cmd_with_args:$!";

    my $output = `$execute_cmd_with_args`;
    chomp $output;
    my $output_expect = "AAA $execute_cmd 3 1 1 7 args1 args2";
    is($output, $output_expect);
  }

  # no_precompile
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/scrip$test_dir -f -B $build_dir -I $test_dir/lib/SPVM -o $exe_dir/myexe_no_precompile -c $test_dir/myexe.no_precompile.config MyExe);
    system($spvmcc_cmd) == 0
      or die "Can't execute spvmcc command $spvmcc_cmd:$!";

    my $execute_cmd = File::Spec->catfile(@build_dir_parts, qw/work exe myexe_no_precompile/);
    my $execute_cmd_with_args = "$execute_cmd args1 args2";
    system($execute_cmd_with_args) == 0
      or die "Can't execute command:$execute_cmd_with_args:$!";
    
    my $output = `$execute_cmd_with_args`;
    chomp $output;
    my $output_expect = "AAA $execute_cmd 3 1 1 7 args1 args2";
    is($output, $output_expect);
    
    # No precompile source
    my $myexe_bootstarp_source_file = "$build_dir/work/src/SPVM/MyExe.boot.c";
    my $myexe_bootstarp_source_content = SPVM::Builder::Util::slurp_binary($myexe_bootstarp_source_file);
    unlike($myexe_bootstarp_source_content, qr/SPVMPRECOMPILE/);
  }

  # no_precompile, no_compiler_api
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/scrip$test_dir -f -B $build_dir -I $test_dir/lib/SPVM -o $exe_dir/myexe_no_precompile_no_compiler_api -c $test_dir/myexe.no_precompile_no_compiler_api.config MyExe);
    system($spvmcc_cmd) == 0
      or die "Can't execute spvmcc command $spvmcc_cmd:$!";

    my $execute_cmd = File::Spec->catfile(@build_dir_parts, qw/work exe myexe_no_precompile_no_compiler_api/);
    my $execute_cmd_with_args = "$execute_cmd args1 args2";
    system($execute_cmd_with_args) == 0
      or die "Can't execute command:$execute_cmd_with_args:$!";
    
    my $output = `$execute_cmd_with_args`;
    chomp $output;
    my $output_expect = "AAA $execute_cmd 3 1 1 7 args1 args2";
    is($output, $output_expect);
    
    # No precompile source
    my $myexe_bootstarp_source_file = "$build_dir/work/src/SPVM/MyExe.boot.c";
    my $myexe_bootstarp_source_content = SPVM::Builder::Util::slurp_binary($myexe_bootstarp_source_file);
    unlike($myexe_bootstarp_source_content, qr/SPVMPRECOMPILE/);
  }

}

# SPVM script
{
  $ENV{SPVM_BUILD_DIR} = $build_dir;
  
  my $spvm_script = File::Spec->catfile(qw/t spvmcc myexe.pl/);
  my $execute_cmd = qq($^X -Mblib -I $test_dir/lib -I t/default/lib $spvm_script);
  my $execute_cmd_with_args = "$execute_cmd args1 args2";
  system($execute_cmd_with_args) == 0
    or die "Can't execute SPVM script: $execute_cmd_with_args:$!";

  my $output = `$execute_cmd_with_args`;
  chomp $output;
  my $output_expect = "AAA $spvm_script 3 1 1 7 args1 args2";
  is($output, $output_expect);
}

ok(1);
done_testing;

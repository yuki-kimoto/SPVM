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

# Compilation Error
{
  my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -I t/04_spvmcc/lib/SPVM -o $exe_dir/myexe_compile_error --no-config MyExeCompileError);
  my $status = system($spvmcc_cmd);
  ok($status != 0);
  
  my $error = `$spvmcc_cmd 2>&1 1>$devnull`;
  like($error, qr|CompileError|);
}

# Runtime error
{
  {
    
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -B $build_dir -I $test_dir/lib/SPVM -o $exe_dir/myexe_runtime_error --no-config MyExeCompileError::MainInstantMethod);
    my $status = system($spvmcc_cmd);
    ok($status == 0);
    
    my $execute_cmd = File::Spec->catfile(@build_dir_parts, qw/work exe myexe_runtime_error/);
    my $execute_cmd_with_args = "$execute_cmd args1 args2";
    
    my $error = `$execute_cmd_with_args 2>&1 1>$devnull`;
    like($error, qr|The "main" method in the "MyExeCompileError::MainInstantMethod" class must be a class method|);
  }
  
  sleep 1;
  
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -B $build_dir -I $test_dir/lib/SPVM -o $exe_dir/myexe_runtime_error --no-config MyExeCompileError::MainHasArguments);
    my $status = system($spvmcc_cmd);
    ok($status == 0);
    
    my $execute_cmd = File::Spec->catfile(@build_dir_parts, qw/work exe myexe_runtime_error/);
    my $execute_cmd_with_args = "$execute_cmd args1 args2";
    
    my $error = `$execute_cmd_with_args 2>&1 1>$devnull`;
    like($error, qr|The length of the arguments of the "main" method in the "MyExeCompileError::MainHasArguments" class must be 0|);
  }
  
  sleep 1;
  
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -B $build_dir -I $test_dir/lib/SPVM -o $exe_dir/myexe_runtime_error --no-config MyExeCompileError::MainNotFound);
    my $status = system($spvmcc_cmd);
    ok($status == 0);
    
    my $execute_cmd = File::Spec->catfile(@build_dir_parts, qw/work exe myexe_runtime_error/);
    my $execute_cmd_with_args = "$execute_cmd args1 args2";
    
    my $error = `$execute_cmd_with_args 2>&1 1>$devnull`;
    like($error, qr|The "main" method in the "MyExeCompileError::MainNotFound" class must be defined|);
  }
}

{
  # Basic
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -B $build_dir -I $test_dir/lib/SPVM -o $exe_dir/myexe MyExe);
    system($spvmcc_cmd) == 0
      or die "Can't execute spvmcc command $spvmcc_cmd:$!";

    my $execute_cmd = File::Spec->catfile(@build_dir_parts, qw/work exe myexe/);
    my $execute_cmd_with_args = "$execute_cmd args1 args2";
    system($execute_cmd_with_args) == 0
      or die "Can't execute command:$execute_cmd_with_args:$!";
    
    my $output = `$execute_cmd_with_args`;
    chomp $output;
    my $output_expect = "AAA $execute_cmd 3 1 1 7 args1 args2 1";
    is($output, $output_expect);
    
    # Check -B option
    {
      ok(-f "$build_dir/work/exe/myexe$Config{exe_ext}");
    }
  }
}

{
  # --optimize="-O0 -g"
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc --optimize="-O0 -g" -B $build_dir -I $test_dir/lib/SPVM -o $exe_dir/myexe MyExe);
    system($spvmcc_cmd) == 0
      or die "Can't execute spvmcc command $spvmcc_cmd:$!";

    my $execute_cmd = File::Spec->catfile(@build_dir_parts, qw/work exe myexe/);
    my $execute_cmd_with_args = "$execute_cmd args1 args2";
    system($execute_cmd_with_args) == 0
      or die "Can't execute command:$execute_cmd_with_args:$!";
    
    my $output = `$execute_cmd_with_args`;
    chomp $output;
    my $output_expect = "AAA $execute_cmd 3 1 1 7 args1 args2 1";
    is($output, $output_expect);
    
    # Check -B option
    {
      ok(-f "$build_dir/work/exe/myexe$Config{exe_ext}");
    }
  }
}

# -h, --help
{
  {
    my $spvmdist_cmd = qq($^X -Mblib blib/script/spvmcc -h);
    my $output = `$spvmdist_cmd`;
    like($output, qr/\Qusage: spvmcc [<options>] <class name>/);
  }
  {
    my $spvmdist_cmd = qq($^X -Mblib blib/script/spvmcc --help);
    my $output = `$spvmdist_cmd`;
    like($output, qr/\Qusage: spvmcc [<options>] <class name>/);
  }
}

{
  mkpath $exe_dir;

  # --required-resources, -r
  for my $option ('--required-resources', '-r'){
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -I $test_dir/lib/SPVM --include-dir t/02_vm/lib/SPVM $option --no-config MyExe);
    my @lines = `$spvmcc_cmd`;
    is($lines[0], '{"argv":["args1","args2"],"class_name":"TestCase::Resource::Mylib1","mode":"mode1","resource_loader_class_name":"TestCase::NativeAPI2"}' . "\n");
    is($lines[1], '{"class_name":"TestCase::Resource::Mylib2","resource_loader_class_name":"TestCase::NativeAPI2"}' . "\n");
  }
  
  # Basic
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -B $build_dir -I $test_dir/lib/SPVM -o $exe_dir/myexe MyExe);
    system($spvmcc_cmd) == 0
      or die "Can't execute spvmcc command $spvmcc_cmd:$!";

    my $execute_cmd = File::Spec->catfile(@build_dir_parts, qw/work exe myexe/);
    my $execute_cmd_with_args = "$execute_cmd args1 args2";
    system($execute_cmd_with_args) == 0
      or die "Can't execute command:$execute_cmd_with_args:$!";
    
    my $output = `$execute_cmd_with_args`;
    chomp $output;
    my $output_expect = "AAA $execute_cmd 3 1 1 7 args1 args2 1";
    is($output, $output_expect);
    
    # Check -B option
    {
      ok(-f "$build_dir/work/exe/myexe$Config{exe_ext}");
    }
  }

  # Compile and link cached
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc --build-dir $build_dir -I $test_dir/lib/SPVM -o $exe_dir/myexe --no-config MyExe);
    my $spvmcc_output = `$spvmcc_cmd 2>&1 1>$dev_null`;
    if (length $spvmcc_output == 0) {
      ok(1);
    }
    else {
      ok(0);
      warn "[Test Failed]$spvmcc_output";
    }
  }
  
  # debug config -O0 -g
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -f -B $build_dir -I $test_dir/lib/SPVM -o $exe_dir/myexe --mode debug MyExe);
    my $spvmcc_output = `$spvmcc_cmd 2>&1 1>$dev_null`;
    like($spvmcc_output, qr/NativeAPI2\.o/);
    like($spvmcc_output, qr/NativeAPI2\.precompile\.o/);
    like($spvmcc_output, qr/\Q-O0 -g/);
    like($spvmcc_output, qr/-L\./);
    like($spvmcc_output, qr/-lm\b/);
    like($spvmcc_output, qr/-std=gnu99/);
    
    # Note: Arguments of the link command(these contain -l flags) must be
    # after object file names for resolving symbol names properly
    like($spvmcc_output, qr/NativeAPI2\.o.+-L\..+-lm\b/);
    
    warn "$spvmcc_output";

    my $execute_cmd = File::Spec->catfile(@build_dir_parts, qw/work exe myexe/);
    my $execute_cmd_with_args = "$execute_cmd args1 args2";
    system($execute_cmd_with_args) == 0
      or die "Can't execute command: $execute_cmd_with_args:$!";

    my $output = `$execute_cmd_with_args`;
    chomp $output;
    my $output_expect = "AAA $execute_cmd 3 1 1 7 args1 args2 1";
    is($output, $output_expect);
  }
}

# SPVM script
{
  $ENV{SPVM_BUILD_DIR} = $build_dir;
  
  my $spvm_script = File::Spec->catfile(qw/t 04_spvmcc myexe.pl/);
  my $execute_cmd = qq($^X -Mblib -I $test_dir/lib -I t/02_vm/lib $spvm_script);
  my $execute_cmd_with_args = "$execute_cmd args1 args2";
  system($execute_cmd_with_args) == 0
    or die "Can't execute SPVM script: $execute_cmd_with_args:$!";

  my $output = `$execute_cmd_with_args`;
  chomp $output;
  my $output_expect = "AAA $spvm_script 3 1 1 7 args1 args2 1";
  is($output, $output_expect);
}

# Execute solo test. This is described in DEVELOPMENT.txt
{
  my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -I solo/lib/SPVM -o $exe_dir/myexe_solo MyExe);
  system($spvmcc_cmd) == 0
   or die "Can't execute spvmcc command $spvmcc_cmd:$!";

  my $execute_cmd = File::Spec->catfile(@build_dir_parts, qw/work exe myexe_solo/);
  my $execute_cmd_with_args = "$execute_cmd foo bar";
  system($execute_cmd_with_args) == 0
    or die "Can't execute command:$execute_cmd_with_args:$!";
  
  ok(1);
}

ok(1);
done_testing;

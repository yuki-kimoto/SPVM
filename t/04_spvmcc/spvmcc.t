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

# Failed to parse options.
{
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc --not-exist t/04_spvmcc/script/myapp.spvm);
    my $status = system($spvmcc_cmd);
    isnt($status, 0);
  }
}

{
  # --resource-info
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -B $build_dir -I $test_dir/lib/SPVM -I t/02_vm/lib/SPVM --resource-info t/04_spvmcc/script/myapp.spvm);
    my $output = `$spvmcc_cmd`;
    like($output, qr|\Q[TestCase::NativeAPI2]|);
    like($output, qr|TestCase::Resource::Mylib1|);
    like($output, qr|TestCase::Resource::Mylib2|);
    like($output, qr|\Q[TestCase::Precompile]|);
  }
}

{
  # --dependency
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -B $build_dir -I $test_dir/lib/SPVM -I t/02_vm/lib/SPVM --dependency t/04_spvmcc/script/myapp.spvm);
    my $output = `$spvmcc_cmd`;
    
    unlike($output, qr|^SPVM [\.\d]+$|m);
    like($output, qr|^TestCase::NativeAPI2 1\.002$|m);
    like($output, qr|^TestCase::Precompile 2\.005$|m);
    like($output, qr|^Byte$|m);
    like($output, qr|\x0A$|s);
    
    warn $output;
  }
}

{
  # --dependency-cpan
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -B $build_dir -I $test_dir/lib/SPVM -I t/02_vm/lib/SPVM --dependency-cpan t/04_spvmcc/script/myapp.spvm);
    my $output = `$spvmcc_cmd`;
    
    like($output, qr|^SPVM [\.\d]+$|m);
    like($output, qr|^SPVM::TestCase::NativeAPI2 1\.002$|m);
    like($output, qr|^SPVM::TestCase::Precompile 2\.005$|m);
    like($output, qr|^SPVM::Byte$|m);
    like($output, qr|\x0A$|s);
  }
}

# Compilation Error
{
  my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -o $exe_dir/myapp_compile_error --no-config t/04_spvmcc/script/myapp_compile_error.spvm);
  my $status = system($spvmcc_cmd);
  ok($status != 0);
  
  my $error = `$spvmcc_cmd 2>&1 1>$devnull`;
  like($error, qr|Compilation Error|);
}

# Runtime error
{
  {
    
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -o $exe_dir/myapp_runtime_error --no-config t/04_spvmcc/script/myapp_compile_error/main_instant_method.spvm);
    my $status = system($spvmcc_cmd);
    ok($status == 0);
    
    my $execute_cmd = File::Spec->catfile(@build_dir_parts, qw/work exe myapp_runtime_error/);
    my $execute_cmd_with_args = "$execute_cmd args1 args2";
    
    my $error = `$execute_cmd_with_args 2>&1 1>$devnull`;
    like($error, qr|The "main" method in the ".+" class must be a class method|);
  }
  
  sleep 1;
  
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -o $exe_dir/myapp_runtime_error --no-config t/04_spvmcc/script/myapp_compile_error/main_has_arguments.spvm);
    my $status = system($spvmcc_cmd);
    ok($status == 0);
    
    my $execute_cmd = File::Spec->catfile(@build_dir_parts, qw/work exe myapp_runtime_error/);
    my $execute_cmd_with_args = "$execute_cmd args1 args2";
    
    my $error = `$execute_cmd_with_args 2>&1 1>$devnull`;
    like($error, qr|The length of the arguments of the "main" method in the ".+" class must be 0|);
  }
  
  sleep 1;
  
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -o $exe_dir/myapp_runtime_error --no-config t/04_spvmcc/script/myapp_compile_error/main_not_found.spvm);
    my $status = system($spvmcc_cmd);
    ok($status == 0);
    
    my $execute_cmd = File::Spec->catfile(@build_dir_parts, qw/work exe myapp_runtime_error/);
    my $execute_cmd_with_args = "$execute_cmd args1 args2";
    
    my $error = `$execute_cmd_with_args 2>&1 1>$devnull`;
    like($error, qr|The "main" method in the ".+" class must be defined|);
  }
}

{
  # --optimize="-O0 -g"
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc --optimize="-O0 -g" -B $build_dir -I $test_dir/lib/SPVM -o $exe_dir/myapp t/04_spvmcc/script/myapp.spvm);
    system($spvmcc_cmd) == 0
      or die "Can't execute spvmcc command $spvmcc_cmd:$!";

    my $execute_cmd = File::Spec->catfile(@build_dir_parts, qw/work exe myapp/);
    my $execute_cmd_with_args = "$execute_cmd args1 args2";
    system($execute_cmd_with_args) == 0
      or die "Can't execute command:$execute_cmd_with_args:$!";
    
    my $output = `$execute_cmd_with_args`;
    chomp $output;
    my $output_expect = "AAA $execute_cmd 3 1 1 7 args1 args2 1";
    is($output, $output_expect);
    
    # Check -B option
    {
      ok(-f "$build_dir/work/exe/myapp$Config{exe_ext}");
    }
  }
}

# -h, --help
{
  {
    my $spvmdist_cmd = qq($^X -Mblib blib/script/spvmcc -h);
    my $output = `$spvmdist_cmd`;
    like($output, qr/\Qusage: spvmcc [<options>] </);
  }
  {
    my $spvmdist_cmd = qq($^X -Mblib blib/script/spvmcc --help);
    my $output = `$spvmdist_cmd`;
    like($output, qr/\Qusage: spvmcc [<options>] </);
  }
}

{
  mkpath $exe_dir;
  
  # Basic
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -B $build_dir -I $test_dir/lib/SPVM -o $exe_dir/myapp t/04_spvmcc/script/myapp.spvm);
    system($spvmcc_cmd) == 0
      or die "Can't execute spvmcc command $spvmcc_cmd:$!";
    
    my $execute_cmd = File::Spec->catfile(@build_dir_parts, qw/work exe myapp/);
    my $execute_cmd_with_args = "$execute_cmd args1 args2";
    system($execute_cmd_with_args) == 0
      or die "Can't execute command:$execute_cmd_with_args:$!";
    
    my $output = `$execute_cmd_with_args`;
    chomp $output;
    my $output_expect = "AAA $execute_cmd 3 1 1 7 args1 args2 1";
    is($output, $output_expect);
    
    # Check -B option
    {
      ok(-f "$build_dir/work/exe/myapp$Config{exe_ext}");
    }
  }

  # Compile and link cached
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc --build-dir $build_dir -I $test_dir/lib/SPVM -o $exe_dir/myapp --no-config t/04_spvmcc/script/myapp.spvm);
    my $spvmcc_output = `$spvmcc_cmd 2>&1 1>$dev_null`;
    if (length $spvmcc_output == 0) {
      ok(1);
    }
    else {
      ok(0);
      warn "[Test Failed]$spvmcc_output";
    }
  }
  
  # debug config -O0 -g, --config-argv, --config-argv-option
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -f -B $build_dir -I $test_dir/lib/SPVM -o $exe_dir/myapp --mode debug --config-argv ARG0 --config-argv ARG1 --config-argv-option NAME=VALUE t/04_spvmcc/script/myapp.spvm);
    my $spvmcc_output = `$spvmcc_cmd 2>&1 1>$dev_null`;
    like($spvmcc_output, qr/NativeAPI2\.o/);
    like($spvmcc_output, qr/NativeAPI2\.precompile\.o/);
    like($spvmcc_output, qr/\Q-O0 -g/);
    like($spvmcc_output, qr/-L\./);
    like($spvmcc_output, qr/-lm\b/);
    like($spvmcc_output, qr/-std=gnu99/);
    like($spvmcc_output, qr/ARG0 ARG1 NAME VALUE/);
    
    # Note: Arguments of the link command(these contain -l flags) must be
    # after object file names for resolving symbol names properly
    like($spvmcc_output, qr/NativeAPI2\.o.+-L\..+-lm\b/);
    
    warn "$spvmcc_output";

    my $execute_cmd = File::Spec->catfile(@build_dir_parts, qw/work exe myapp/);
    my $execute_cmd_with_args = "$execute_cmd args1 args2";
    system($execute_cmd_with_args) == 0
      or die "Can't execute command: $execute_cmd_with_args:$!";

    my $output = `$execute_cmd_with_args`;
    chomp $output;
    my $output_expect = "AAA $execute_cmd 3 1 1 7 args1 args2 1";
    is($output, $output_expect);
  }
}

{
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -B $build_dir -o $exe_dir/myapp --no-config t/04_spvmcc/script/program_name.spvm);
    system($spvmcc_cmd) == 0
      or die "Can't execute spvmcc command $spvmcc_cmd:$!";
    
    my $execute_cmd = File::Spec->catfile(@build_dir_parts, qw/work exe myapp/);
    my $execute_cmd_with_args = "$execute_cmd args1 args2";
    system($execute_cmd_with_args) == 0
      or die "Can't execute command:$execute_cmd_with_args:$!";
    
    my $output = `$execute_cmd_with_args`;
    chomp $output;
    my $output_expect = "$execute_cmd";
    is($output, $output_expect);
  }
}

# Execute solo test. This is described in DEVELOPMENT.txt
{
  my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -I solo/lib/SPVM -o $exe_dir/myapp_solo --no-config solo/script/myapp.spvm foo bar);
  system($spvmcc_cmd) == 0
   or die "Can't execute spvmcc command $spvmcc_cmd:$!";

  my $execute_cmd = File::Spec->catfile(@build_dir_parts, qw/work exe myapp_solo/);
  my $execute_cmd_with_args = "$execute_cmd foo bar";
  system($execute_cmd_with_args) == 0
    or die "Can't execute command:$execute_cmd_with_args:$!";
  
  ok(1);
}

ok(1);
done_testing;

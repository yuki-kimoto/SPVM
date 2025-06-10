use lib "t/testlib";
use TestAuto;

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

my $test_dir = $ENV{SPVM_TEST_DIR};
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

# Failed to parse options.
{
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc --optimize=-O0 --quiet --not-exist t/04_spvmcc/script/myapp.spvm);
    my $status = system($spvmcc_cmd);
    isnt($status, 0);
  }
}

# Compilation Error
{
  my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc --optimize=-O0 --quiet -o $exe_dir/myapp_compile_error --no-config t/04_spvmcc/script/myapp_compile_error.spvm);
  my $status = system($spvmcc_cmd);
  ok($status != 0);
  
  my $error = `$spvmcc_cmd 2>&1 1>$devnull`;
  like($error, qr|Compilation Error|);
}

# Runtime error
{
  {
    
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc --optimize=-O0 --quiet -o $exe_dir/myapp_runtime_error --no-config t/04_spvmcc/script/myapp_compile_error/main_instant_method.spvm);
    my $status = system($spvmcc_cmd);
    ok($status == 0);
    
    my $execute_cmd = &to_cmd("$exe_dir/myapp_runtime_error");
    my $execute_cmd_with_args = "$execute_cmd args1 args2";
    
    my $error = `$execute_cmd_with_args 2>&1 1>$devnull`;
    like($error, qr|.+#main method must be a class method|);
  }
  
  sleep 1;
  
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc --optimize=-O0 --quiet -o $exe_dir/myapp_runtime_error --no-config t/04_spvmcc/script/myapp_compile_error/main_has_arguments.spvm);
    my $status = system($spvmcc_cmd);
    ok($status == 0);
    
    my $execute_cmd = &to_cmd("$exe_dir/myapp_runtime_error");
    my $execute_cmd_with_args = "$execute_cmd args1 args2";
    
    my $error = `$execute_cmd_with_args 2>&1 1>$devnull`;
    like($error, qr|The length of the arguments of .+#main method must be 0|);
  }
  
  sleep 1;
  
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc --optimize=-O0 --quiet -o $exe_dir/myapp_runtime_error --no-config t/04_spvmcc/script/myapp_compile_error/main_not_found.spvm);
    my $status = system($spvmcc_cmd);
    ok($status == 0);
    
    my $execute_cmd = &to_cmd("$exe_dir/myapp_runtime_error");
    my $execute_cmd_with_args = "$execute_cmd args1 args2";
    
    my $error = `$execute_cmd_with_args 2>&1 1>$devnull`;
    like($error, qr|.+#main method must be defined|);
  }
}

done_testing;

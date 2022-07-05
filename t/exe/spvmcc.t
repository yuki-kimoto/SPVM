use Test::More;
use strict;
use warnings;
use utf8;
use Data::Dumper;
use File::Basename 'basename';
use FindBin;
use Config;
use File::Path 'mkpath', 'rmtree';
use File::Spec;
use SPVM::Builder::Util;

use SPVM::Builder;

my $file = 't/' . basename $0;

use FindBin;
use lib "$FindBin::Bin/exe/lib";

my $build_dir = 't/exe/.spvm_build';
my @build_dir_parts = split('/', $build_dir);
my $exe_dir = "$build_dir/work/exe";

rmtree "$build_dir/work";

{
  mkpath $exe_dir;

  # --print-dependent-resources, -p
  for my $option ('--print-dependent-resources', '-p'){
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -I t/exe/lib/SPVM -I t/default/lib/SPVM $option MyExe);
    my @lines = `$spvmcc_cmd`;
    is($lines[0], '{class_name:"TestCase::NativeAPI2",resource_class_name:"TestCase::Resource::Mylib1::V1_0_0",resource_mode:"mode1",resource_args:["args1","args2"]}' . "\n");
    is($lines[1], '{class_name:"TestCase::NativeAPI2",resource_class_name:"TestCase::Resource::Mylib2::V1_0_0",resource_mode:undefined,resource_args:[]}' . "\n");
  }
  
  # Basic
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -B $build_dir -I t/exe/lib/SPVM -o $exe_dir/myexe -c t/exe/myexe.config MyExe);
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
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc --build-dir $build_dir -I t/exe/lib/SPVM -o $exe_dir/myexe -c t/exe/myexe.config MyExe);
    my $spvmcc_output = `$spvmcc_cmd 2>&1 1>/dev/null`;
    ok(length $spvmcc_output == 0);
  }
  
  # debug config -O0 -g
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -f -B $build_dir -I t/exe/lib/SPVM -o $exe_dir/myexe --config t/exe/myexe.debug.config MyExe);
    my $spvmcc_output = `$spvmcc_cmd 2>&1 1>/dev/null`;
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
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -f -B $build_dir -I t/exe/lib/SPVM -o $exe_dir/myexe_no_precompile -c t/exe/myexe.no_precompile.config MyExe);
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
    my $myexe_bootstarp_source_file = "$FindBin::Bin/.spvm_build/work/src/SPVM/MyExe.boot.c";
    my $myexe_bootstarp_source_content = SPVM::Builder::Util::slurp_binary($myexe_bootstarp_source_file);
    unlike($myexe_bootstarp_source_content, qr/SPVMPRECOMPILE/);
  }

  # no_precompile, no_compiler_api
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -f -B $build_dir -I t/exe/lib/SPVM -o $exe_dir/myexe_no_precompile_no_compiler_api -c t/exe/myexe.no_precompile_no_compiler_api.config MyExe);
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
    my $myexe_bootstarp_source_file = "$FindBin::Bin/.spvm_build/work/src/SPVM/MyExe.boot.c";
    my $myexe_bootstarp_source_content = SPVM::Builder::Util::slurp_binary($myexe_bootstarp_source_file);
    unlike($myexe_bootstarp_source_content, qr/SPVMPRECOMPILE/);
  }

}

# SPVM script
{
  $ENV{SPVM_BUILD_DIR} = $build_dir;
  
  my $spvm_script = File::Spec->catfile(qw/t exe myexe.pl/);
  my $execute_cmd = qq($^X -Mblib -I t/exe/lib -I t/default/lib $spvm_script);
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

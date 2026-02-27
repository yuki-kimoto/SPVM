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
use SPVM::Builder::Config::Exe::MSVC;

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

{
  # Basic
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -B $build_dir -I $test_dir/lib/SPVM -o $exe_dir/myapp t/04_spvmcc/script/myapp.spvm);
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

  # Compile and link cached
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -B $build_dir -I $test_dir/lib/SPVM -o $exe_dir/myapp t/04_spvmcc/script/myapp.spvm);
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
  my $spvm_script = "t/04_spvmcc/script/end-block.spvm";
  my $exe_file = "$exe_dir/end-block";
  
  # Compile with --no-config
  my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc --optimize=-O0 -q --no-config -B $build_dir -I $test_dir/lib/SPVM -o $exe_file $spvm_script);
  system($spvmcc_cmd) == 0 or die "Can't execute spvmcc command $spvmcc_cmd:$!";
  
  # Execute and check
  my $output = `$exe_file`;
  is($output, "END 1\n", "END block execution");
}

{
  # lib directive
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc --optimize=-O0 -q --build-dir $build_dir -o $exe_dir/use-class --no-config t/04_spvmcc/script/use-class.spvm);
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
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc --optimize=-O0 --quiet -B $build_dir -I $test_dir/lib/SPVM --object-file $external_object_dir/external.o -o $exe_dir/external --no-config t/04_spvmcc/script/external.spvm);
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
  # --optimize="-O0 -g"
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc --optimize="-O0 -g" -B $build_dir -I $test_dir/lib/SPVM -o $exe_dir/myapp t/04_spvmcc/script/myapp.spvm);
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
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc --optimize=-O0 --quiet -B $build_dir -o $exe_dir/program_name --no-config t/04_spvmcc/script/program_name.spvm);
    system($spvmcc_cmd) == 0
      or die "Can't execute spvmcc command $spvmcc_cmd:$!";
    
    my $execute_cmd = &to_cmd("$exe_dir/program_name");
    my $execute_cmd_with_args = "$execute_cmd args1 args2";
    my $output = `$execute_cmd_with_args`;
    chomp $output;
    my $output_expect = "$execute_cmd";
    is($output, $output_expect);
  }
  
  # debug config -O0 -g and many options
  {
    my @compiler_options = qw(
      --ccflag=-DCC_001
      --ccflag-spvm=-DCC_002
      --ccflag-native=-DCC_003
      --ccflag-native-class=NativeAPI2@-DCC_004
      --ccflag-precompile=-DCC_005
      --ccflag=-DCC_001
      --ccflag-spvm=-DCC_002
      --ccflag-native=-DCC_003
      --ccflag-native-class=NativeAPI2@-DCC_004
      --ccflag-precompile=-DCC_005
      --define=DEF_001
      --define-spvm=DEF_002
      --define-native=DEF_003
      --define-native-class=NativeAPI2@DEF_004
      --define-precompile=DEF_005
      --define=DEF_001
      --define-spvm=DEF_002
      --define-native=DEF_003
      --define-native-class=NativeAPI2@DEF_004
      --define-precompile=DEF_005
      --optimize="-O0 -g"
      --optimize-spvm="-O0 -g"
      --optimize-native="-O0 -g"
      --optimize-native-class="NativeAPI2@-O0 -g"
      --optimize-precompile="-O0 -g"
      --include-dir=./INC_001
      --include-dir-spvm=./INC_002
      --include-dir-native=./INC_003
      --include-dir-native-class=NativeAPI2@./INC_004
      --include-dir-precompile=./INC_005
      --include-dir=./INC_001
      --include-dir-spvm=./INC_002
      --include-dir-native=./INC_003
      --include-dir-native-class=NativeAPI2@./INC_004
      --include-dir-precompile=./INC_005
    );
    
    my $compiler_options_string = join(' ', @compiler_options);
    
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc --optimize=-O0 -f -B $build_dir -I $test_dir/lib/SPVM -o $exe_dir/myapp --mode debug $compiler_options_string t/04_spvmcc/script/myapp.spvm);
    my $spvmcc_output = `$spvmcc_cmd`;
    like($spvmcc_output, qr/NativeAPI2\.o/);
    like($spvmcc_output, qr/NativeAPI2\.precompile\.o/);
    like($spvmcc_output, qr/\Q-O0 -g/);
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
      ok(-d 't/04_spvmcc/.spvm_build/spvmcc/myapp/src');
      ok(-d 't/04_spvmcc/.spvm_build/spvmcc/myapp/object');
    }
    
    {
      my $bootstrap_file = 't/04_spvmcc/.spvm_build/spvmcc/myapp/src/bootstrap/myapp.c';
      open my $fh, '<', $bootstrap_file
        or die "Cannot open file \"$bootstrap_file\":$!";
      
      my $bootstrap_content = do { $/ = undef; <$fh> };
      
      like($bootstrap_content, qr|mode:debug|);
      like($bootstrap_content, qr|ccflags_global:-DCC_001,-DCC_001|);
      like($bootstrap_content, qr|ccflags_spvm:-DCC_002,-DCC_002|);
      like($bootstrap_content, qr|ccflags_native:-DCC_003,-DCC_003|);
      like($bootstrap_content, qr|ccflags_native_class:NativeAPI2\@-DCC_004,NativeAPI2\@-DCC_004|);
      like($bootstrap_content, qr|ccflags_precompile:-DCC_005,-DCC_005|);
      like($bootstrap_content, qr|defines_global:DEF_001,DEF_001|);
      like($bootstrap_content, qr|defines_spvm:DEF_002,DEF_002|);
      like($bootstrap_content, qr|defines_native:DEF_003,DEF_003|);
      like($bootstrap_content, qr|defines_native_class:NativeAPI2\@DEF_004,NativeAPI2\@DEF_004|);
      like($bootstrap_content, qr|defines_precompile:DEF_005,DEF_005|);
      like($bootstrap_content, qr|optimize_global:-O0 -g|);
      like($bootstrap_content, qr|optimize_spvm:-O0 -g|);
      like($bootstrap_content, qr|optimize_native:-O0 -g|);
      like($bootstrap_content, qr|optimize_native_class:NativeAPI2\@-O0 -g|);
      like($bootstrap_content, qr|optimize_precompile:-O0 -g|);
      
    }
  }

}

done_testing;

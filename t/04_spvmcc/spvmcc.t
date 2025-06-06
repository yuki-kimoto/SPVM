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
use Archive::Tar;

use SPVM::Builder;
use File::Spec;

my $devnull = File::Spec->devnull;

my $test_dir = $ENV{SPVM_TEST_DIR};
my $build_dir = $ENV{SPVM_BUILD_DIR};

my @build_dir_parts = split('/', $build_dir);
my $exe_dir = "$build_dir/work/exe";
my $external_object_dir = "$build_dir/work/external_object";

rmtree "$build_dir/work";

mkpath $exe_dir;
mkpath $external_object_dir;

my $dev_null = File::Spec->devnull;

# External objects
{
  my $cc_cmd = qq($Config{cc} -c -o $external_object_dir/external.o t/04_spvmcc/lib/SPVM/external.c);
  system($cc_cmd) == 0
    or die "Can't execute cc command $cc_cmd:$!";
  
  # --object-file
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -B $build_dir -I $test_dir/lib/SPVM --optimize=-O0 --object-file $external_object_dir/external.o -o $exe_dir/external --no-config t/04_spvmcc/script/external.spvm);
    system($spvmcc_cmd) == 0
      or die "Can't execute spvmcc command $spvmcc_cmd:$!";
    
    my $execute_cmd = File::Spec->catfile(@build_dir_parts, qw/work exe external/);
    my $output = `$execute_cmd`;
    chomp $output;
    my $output_expect = "40";
    is($output, $output_expect);
  }
  
  # --load-spvm-archive
  {
    my $tar = Archive::Tar->new;
    
    my $cwd = Cwd::getcwd;
    
    chdir $external_object_dir
      or die;
    
    my @tar_files = (
      "external.o",
    );
    $tar->add_files(@tar_files)
      or die $tar->error;
    
    chdir $cwd
      or die;
    
    my $spvm_archive = "$external_object_dir.tar.gz";
    $tar->write($spvm_archive, COMPRESS_GZIP)
      or die $tar->error;
    
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -B $build_dir -I $test_dir/lib/SPVM --optimize=-O0 --load-spvm-archive $spvm_archive -o $exe_dir/external --no-config t/04_spvmcc/script/external.spvm);
    system($spvmcc_cmd) == 0
      or die "Can't execute spvmcc command $spvmcc_cmd:$!";
    
    my $execute_cmd = File::Spec->catfile(@build_dir_parts, qw/work exe external/);
    my $output = `$execute_cmd`;
    chomp $output;
    my $output_expect = "40";
    is($output, $output_expect);
  }
  
}

# Failed to parse options.
{
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc --not-exist --optimize=-O0 t/04_spvmcc/script/myapp.spvm);
    my $status = system($spvmcc_cmd);
    isnt($status, 0);
  }
}

# Compilation Error
{
  my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -o $exe_dir/myapp_compile_error --no-config --optimize=-O0 t/04_spvmcc/script/myapp_compile_error.spvm);
  my $status = system($spvmcc_cmd);
  ok($status != 0);
  
  my $error = `$spvmcc_cmd 2>&1 1>$devnull`;
  like($error, qr|Compilation Error|);
}

# Runtime error
{
  {
    
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -o $exe_dir/myapp_runtime_error --no-config --optimize=-O0 t/04_spvmcc/script/myapp_compile_error/main_instant_method.spvm);
    my $status = system($spvmcc_cmd);
    ok($status == 0);
    
    my $execute_cmd = File::Spec->catfile(@build_dir_parts, qw/work exe myapp_runtime_error/);
    my $execute_cmd_with_args = "$execute_cmd args1 args2";
    
    my $error = `$execute_cmd_with_args 2>&1 1>$devnull`;
    like($error, qr|.+#main method must be a class method|);
  }
  
  sleep 1;
  
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -o $exe_dir/myapp_runtime_error --no-config --optimize=-O0 t/04_spvmcc/script/myapp_compile_error/main_has_arguments.spvm);
    my $status = system($spvmcc_cmd);
    ok($status == 0);
    
    my $execute_cmd = File::Spec->catfile(@build_dir_parts, qw/work exe myapp_runtime_error/);
    my $execute_cmd_with_args = "$execute_cmd args1 args2";
    
    my $error = `$execute_cmd_with_args 2>&1 1>$devnull`;
    like($error, qr|The length of the arguments of .+#main method must be 0|);
  }
  
  sleep 1;
  
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -o $exe_dir/myapp_runtime_error --no-config --optimize=-O0 t/04_spvmcc/script/myapp_compile_error/main_not_found.spvm);
    my $status = system($spvmcc_cmd);
    ok($status == 0);
    
    my $execute_cmd = File::Spec->catfile(@build_dir_parts, qw/work exe myapp_runtime_error/);
    my $execute_cmd_with_args = "$execute_cmd args1 args2";
    
    my $error = `$execute_cmd_with_args 2>&1 1>$devnull`;
    like($error, qr|.+#main method must be defined|);
  }
}

{
  # --optimize="-O0 -g"
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc --optimize="-O0 -g" -B $build_dir -I $test_dir/lib/SPVM -o $exe_dir/myapp --optimize=-O0 t/04_spvmcc/script/myapp.spvm);
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
    like($output, qr/\QUsage: spvmcc [OPTIONS] SCRIPT_NAME/);
  }
  {
    my $spvmdist_cmd = qq($^X -Mblib blib/script/spvmcc --help);
    my $output = `$spvmdist_cmd`;
    like($output, qr/\QUsage: spvmcc [OPTIONS] SCRIPT_NAME/);
  }
}

{
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
  
  # lib directive
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc --build-dir $build_dir -o $exe_dir/use-class --no-config --optimize=-O0 t/04_spvmcc/script/use-class.spvm);
    system($spvmcc_cmd) == 0
      or die "Can't execute spvmcc command $spvmcc_cmd:$!";
    
    my $execute_cmd = File::Spec->catfile(@build_dir_parts, qw/work exe use-class/);
    my $output = `$execute_cmd`;
    chomp $output;
    like($output, qr/3000/);
  }
  
}

{
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -B $build_dir -o $exe_dir/program_name --no-config --optimize=-O0 t/04_spvmcc/script/program_name.spvm);
    system($spvmcc_cmd) == 0
      or die "Can't execute spvmcc command $spvmcc_cmd:$!";
    
    my $execute_cmd = File::Spec->catfile(@build_dir_parts, qw/work exe program_name/);
    my $execute_cmd_with_args = "$execute_cmd args1 args2";
    system($execute_cmd_with_args) == 0
      or die "Can't execute command:$execute_cmd_with_args:$!";
    
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
    
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -f -B $build_dir -I $test_dir/lib/SPVM -o $exe_dir/myapp --mode debug $compiler_options_string t/04_spvmcc/script/myapp.spvm);
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
    
    my $execute_cmd = File::Spec->catfile(@build_dir_parts, qw/work exe myapp/);
    my $execute_cmd_with_args = "$execute_cmd args1 args2";
    system($execute_cmd_with_args) == 0
      or die "Can't execute command: $execute_cmd_with_args:$!";

    my $output = `$execute_cmd_with_args`;
    chomp $output;
    my $output_expect = "AAA $execute_cmd 3 1 1 7 args1 args2 1";
    is($output, $output_expect);
    
    {
      ok(-d 't/04_spvmcc/.spvm_build/work/src');
      ok(-d 't/04_spvmcc/.spvm_build/work/object');
    }
    
    {
      my $bootstrap_file = 't/04_spvmcc/.spvm_build/work/src/bootstrap/myapp.c';
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

# Execute solo test. This is described in DEVELOPMENT.txt
{
  my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -I solo/lib/SPVM -o $exe_dir/myapp_solo --no-config --optimize=-O0 solo/script/myapp.spvm foo bar);
  system($spvmcc_cmd) == 0
   or die "Can't execute spvmcc command $spvmcc_cmd:$!";

  my $execute_cmd = File::Spec->catfile(@build_dir_parts, qw/work exe myapp_solo/);
  my $execute_cmd_with_args = "$execute_cmd foo bar";
  system($execute_cmd_with_args) == 0
    or die "Can't execute command:$execute_cmd_with_args:$!";
  
  ok(1);
}

done_testing;

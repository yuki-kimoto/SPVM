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
use SPVM::Builder::Config::Exe::MSVC;

my $devnull = File::Spec->devnull;

my $inc_dir = "$FindBin::Bin/lib";
my $spvm_script_dir = 't/08_spvmcc/script';
my $build_dir = $ENV{SPVM_BUILD_DIR};

my $tmp_dir = File::Temp->newdir;

my $has_msvc;
eval {
  local %ENV = %ENV;
  my $global_config = SPVM::Builder::Config::Exe::MSVC->new;
  $global_config->hint_cc(undef);
  $global_config->setup_env;
  my $hint_cc = $global_config->hint_cc;
  $has_msvc = defined $hint_cc;
};

if ($@) {
  warn $@;
}

unless ($has_msvc) {
  plan skip_all => '[Test Skip]Do not have MSVC compiler and linker.' ;
}

{
  # Basic
  # build_type - Release
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -B $build_dir -I $inc_dir --mode msvc -o $tmp_dir/myapp $spvm_script_dir/myapp.spvm);
    system($spvmcc_cmd) == 0
      or die "Can't execute spvmcc command $spvmcc_cmd:$!";
    
    my $execute_cmd = TestUtil::to_os_specific_path("$tmp_dir/myapp");
    my $execute_cmd_with_args = "$execute_cmd args1 args2";
    my $output = `$execute_cmd_with_args`;
    chomp $output;
    is($output, 1);
  }
}

# build_type
{
  # build_type - Release
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -B $build_dir -I $inc_dir --mode msvc-Release -o $tmp_dir/myapp $spvm_script_dir/myapp.spvm);
    system($spvmcc_cmd) == 0
      or die "Can't execute spvmcc command $spvmcc_cmd:$!";
    
    my $execute_cmd = TestUtil::to_os_specific_path("$tmp_dir/myapp");
    my $execute_cmd_with_args = "$execute_cmd args1 args2";
    my $output = `$execute_cmd_with_args`;
    chomp $output;
    is($output, 1);
  }
  
  # build_type - Debug
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -B $build_dir -I $inc_dir --mode msvc-Debug -o $tmp_dir/myapp $spvm_script_dir/myapp.spvm);
    system($spvmcc_cmd) == 0
      or die "Can't execute spvmcc command $spvmcc_cmd:$!";
    
    my $execute_cmd = TestUtil::to_os_specific_path("$tmp_dir/myapp");
    my $execute_cmd_with_args = "$execute_cmd args1 args2";
    my $output = `$execute_cmd_with_args`;
    chomp $output;
    is($output, 1);
  }
  
  # build_type - RelWithDebInfo
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -B $build_dir -I $inc_dir --mode msvc-RelWithDebInfo -o $tmp_dir/myapp $spvm_script_dir/myapp.spvm);
    system($spvmcc_cmd) == 0
      or die "Can't execute spvmcc command $spvmcc_cmd:$!";
    
    my $execute_cmd = TestUtil::to_os_specific_path("$tmp_dir/myapp");
    my $execute_cmd_with_args = "$execute_cmd args1 args2";
    my $output = `$execute_cmd_with_args`;
    chomp $output;
    is($output, 1);
  }
  
  # build_type - MinSizeRel
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -B $build_dir -I $inc_dir --mode msvc-MinSizeRel -o $tmp_dir/myapp $spvm_script_dir/myapp.spvm);
    system($spvmcc_cmd) == 0
      or die "Can't execute spvmcc command $spvmcc_cmd:$!";
    
    my $execute_cmd = TestUtil::to_os_specific_path("$tmp_dir/myapp");
    my $execute_cmd_with_args = "$execute_cmd args1 args2";
    my $output = `$execute_cmd_with_args`;
    chomp $output;
    is($output, 1);
  }
}

done_testing;

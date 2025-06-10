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

# Execute solo test. This is described in DEVELOPMENT.txt
{
  my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc --optimize=-O0 --quiet -I solo/lib/SPVM -o $exe_dir/myapp_solo --no-config solo/script/myapp.spvm foo bar);
  system($spvmcc_cmd) == 0
   or die "Can't execute spvmcc command $spvmcc_cmd:$!";

  my $execute_cmd = &to_cmd("$exe_dir/myapp_solo");
  my $execute_cmd_with_args = "$execute_cmd foo bar";
  system("$execute_cmd_with_args > $dev_null 2>&1") == 0
    or die "Can't execute command:$execute_cmd_with_args:$!";
  
  ok(1);
}

done_testing;

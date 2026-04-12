use strict;
use warnings;

use Test::More;

use lib "t/lib";
use TestUtil::MyLib;

use File::Spec;
use File::Temp;

use SPVM::Builder;
use SPVM::Builder::Util;

my $build_dir = $ENV{SPVM_BUILD_DIR};

my $dev_null = File::Spec->devnull;

sub to_cmd {
  my ($path) = @_;
  
  my $cmd = File::Spec->catfile(split("/", $path));
  
  return $cmd;
}

# Execute solo test. This is described in DEVELOPMENT.txt
{
  my $tmp_dir = File::Temp->newdir;
  my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc --quiet -I solo/lib/SPVM -o $tmp_dir/myapp_solo solo/script/myapp.spvm foo bar);
  system($spvmcc_cmd) == 0
   or die "Can't execute spvmcc command $spvmcc_cmd:$!";

  my $execute_cmd = &to_cmd("$tmp_dir/myapp_solo");
  my $execute_cmd_with_args = "$execute_cmd foo bar";
  system("$execute_cmd_with_args > $dev_null 2>&1") == 0
    or die "Can't execute command:$execute_cmd_with_args:$!";
  
  ok(1);
}

done_testing;

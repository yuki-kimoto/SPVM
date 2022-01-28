use Test::More;
use strict;
use warnings;
use utf8;
use Data::Dumper;
use File::Basename 'basename';
use FindBin;
use Config;
use File::Path 'mkpath';
use File::Spec;

use SPVM::Builder;

my $file = 't/' . basename $0;

use FindBin;
use lib "$FindBin::Bin/exe/lib";

my $output_expect = 'AAA t/exe/myexe.pl 3 1 1 7 args1 args2';

my $build_dir = 't/exe/.spvm_build';

{
  my $exe_dir = 't/exe/.spvm_build/work/exe';
  mkpath $exe_dir;
  
  # Basic
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -B $build_dir -I t/exe/lib/SPVM -o $build_dir/work/exe/myexe -c t/exe/myexe.config MyExe);
    system($spvmcc_cmd) == 0
      or die "Can't execute spvmcc command $spvmcc_cmd:$!";

    my $execute_cmd = File::Spec->catfile(qw/t exe .spvm_build work exe myexe/);
    my $execute_cmd_with_args = "$execute_cmd args1 args2";
    system($execute_cmd_with_args) == 0
      or die "Can't execute command:$execute_cmd_with_args:$!";
    
    my $output = `$execute_cmd_with_args`;
    chomp $output;
    my $output_expect = "AAA $execute_cmd 3 1 1 7 args1 args2";
    is($output, $output_expect);
  }
  
  # -O, -f,  --ccflags, --lddlflags
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -f -O "-O0 -g" -B $build_dir -I t/exe/lib/SPVM -o $build_dir/work/exe/myexe --config t/exe/myexe.config MyExe);
    system($spvmcc_cmd) == 0
      or die "Can't execute spvmcc command $spvmcc_cmd:$!";

    my $execute_cmd = File::Spec->catfile(qw/t exe .spvm_build work exe myexe/);
    my $execute_cmd_with_args = "$execute_cmd args1 args2";
    system($execute_cmd_with_args) == 0
      or die "Can't execute command: $execute_cmd_with_args:$!";

    my $output = `$execute_cmd_with_args`;
    chomp $output;
    my $output_expect = "AAA $execute_cmd 3 1 1 7 args1 args2";
    is($output, $output_expect);
  }
}

# SPVM script
{
  $ENV{SPVM_BUILD_DIR} = $build_dir;
  
  my $spvm_script = File::Spec->catfile(qw/t exe myexe.pl/);
  my $execute_cmd = qq($^X -Mblib -I t/exe/lib $spvm_script);
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

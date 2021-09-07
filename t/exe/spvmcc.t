use Test::More 'no_plan';
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

{
  my $exe_dir = 't/.spvm_build/work/exe';
  mkpath $exe_dir;
  
  # Basic
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -B t/exe/.spvm_build -I t/exe/lib -o t/.spvm_build/work/exe/myexe SPVM::MyExe);
    system($spvmcc_cmd) == 0
      or die "Can't execute spvmcc command $spvmcc_cmd:$!";

    my $execute_cmd = File::Spec->catfile(qw/t .spvm_build work exe myexe/);
    system($execute_cmd) == 0
      or die "Can't execute exe file $execute_cmd:$!";
  }
  
  # -O, -f,  --ccflags, --lddlflags
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc -f --ccflags "-DSOMETHING_MACRO" --lddlflags "-L/foo/bar/baz" -O "-O0 -g" -B t/exe/.spvm_build -I t/exe/lib -o t/.spvm_build/work/exe/myexe SPVM::MyExe);
    system($spvmcc_cmd) == 0
      or die "Can't execute spvmcc command $spvmcc_cmd:$!";

    my $execute_cmd = File::Spec->catfile(qw/t .spvm_build work exe myexe/);
    system($execute_cmd) == 0
      or die "Can't execute exe file $execute_cmd:$!";
  }
}

ok(1);
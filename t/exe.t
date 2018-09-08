use strict;
use warnings;
use utf8;
use Data::Dumper;
use File::Basename 'basename';
use FindBin;

use SPVM::Builder;

my $file = 't/' . basename $0;

use FindBin;
use lib "$FindBin::Bin/default/lib";

{
  my $spvmcc_cmd = 'perl -Mblib -- blib/script/spvmcc -q -I t/default/lib TestCase::MyExe';
  my $execute_cmd = 'env LD_LIBRARY_PATH=spvm_build/exe spvm_build/exe/TestCase__MyExe';
  
  system($spvmcc_cmd) == 0
    or die "Can't execute comman $spvmcc_cmd:$!";

  system($execute_cmd) == 0
    or die "Can't execute comman $execute_cmd:$!";
}

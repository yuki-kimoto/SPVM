use strict;
use warnings;
use utf8;
use Data::Dumper;
use File::Basename 'basename';
use FindBin;
use Config;

use SPVM::Builder;

my $file = 't/' . basename $0;

use FindBin;
use lib "$FindBin::Bin/default/lib";

{
  $ENV{PERL5LIB} = "blib/arch$Config{path_sep}blib/lib";
  $ENV{PATH} = "blib/script$Config{path_sep}$ENV{PATH}";
  
  my $spvmcc_cmd = 'spvmcc -I t/default/lib TestCase::MyExe';
  system($spvmcc_cmd) == 0
    or die "Can't execute command $spvmcc_cmd:$!";

  my $execute_cmd = 'spvm_build/work/exe/TestCase__MyExe';
  system($execute_cmd) == 0
    or die "Can't execute command $spvmcc_cmd:$!";
}

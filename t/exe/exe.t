use strict;
use warnings;
use utf8;
use Data::Dumper;
use File::Basename 'basename';
use FindBin;
use Config;
use File::Path 'mkpath';

use SPVM::Builder;

my $file = 't/' . basename $0;

use FindBin;
use lib "$FindBin::Bin/default/lib";

{
  $ENV{PERL5LIB} = "blib/arch$Config{path_sep}blib/lib";
  $ENV{PATH} = "blib/script$Config{path_sep}$ENV{PATH}";

  my $exe_dir = 't/spvm_build/work/exe';
  mkpath $exe_dir;
  
  my $spvmcc_cmd = 'spvmcc -B t/exe/spvm_build -I t/default/lib -o t/spvm_build/work/exe/myexe TestCase::MyExe';
  system($spvmcc_cmd) == 0
    or die "Can't execute command $spvmcc_cmd:$!";

  my $execute_cmd = 't/spvm_build/work/exe/myexe';
  system($execute_cmd) == 0
    or die "Can't execute command $spvmcc_cmd:$!";
}

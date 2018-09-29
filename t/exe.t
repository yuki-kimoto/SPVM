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
  my $library_path = 'spvm_build/exe';
  {
    # Windows MinGW
    $ENV{LIBRARY_PATH} = $library_path;
  
    # Linux, macOS
    $ENV{LD_LIBRARY_PATH} = $library_path;
  }
  
  $ENV{PERL5LIB} = "blib/arch$Config{path_sep}blib/lib";
  
  my $spvmcc_cmd = 'blib/script/spvmcc -q -I t/default/lib TestCase::MyExe';
  system($spvmcc_cmd) == 0
    or die "Can't execute comman $spvmcc_cmd:$!";

  my $execute_cmd = 'spvm_build/exe/TestCase__MyExe';
  system($execute_cmd) == 0
    or die "Can't execute comman $spvmcc_cmd:$!";
}

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
  
  # Library path
  {
    my $library_path = 'spvm_build/exe';
    
    # Linux, macOS
    $ENV{LD_LIBRARY_PATH} = $library_path;
    
    # Windows MinGW
    $ENV{LIBRARY_PATH} = $library_path;
  }
  
  my $execute_cmd = 'spvm_build/exe/TestCase__MyExe';
  
  system($spvmcc_cmd) == 0
    or die "Can't execute comman $spvmcc_cmd:$!";

  system($execute_cmd) == 0
    or die "Can't execute comman $spvmcc_cmd:$!";
  
}

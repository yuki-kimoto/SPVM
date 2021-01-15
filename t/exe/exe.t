use strict;
use warnings;
use utf8;
use Data::Dumper;
use File::Basename 'basename';
use FindBin;
use Config;
use File::Path 'mkpath';
use File::Spec;

use SPVM::Builder::Exe;

my $file = 't/' . basename $0;

use FindBin;

{
  my $exe_dir = 't/spvm_build/work/exe';
  mkpath $exe_dir;
  
  my $package_name = 'MyExe';
  my $build_dir = 't/exe/.spvm_build';
  my $module_include_dir = 't/exe/lib';
  my $exe_name = 't/spvm_build/work/exe/myexe';
  
  unshift @INC, $module_include_dir;
  
  my $builder_exe = SPVM::Builder::Exe->new(
    package_name => $package_name,
    exe_name => $exe_name,
    build_dir => $build_dir,
  );
  
  $builder_exe->build_exe_file;
}

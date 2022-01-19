use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More;

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
  my $exe_dir = 't/.spvm_build/work/exe';
  mkpath $exe_dir;
  
  my $class_name = 'MyExe';
  my $build_dir = 't/exe/.spvm_build';
  my $module_dirs = ['t/exe/lib', @INC];
  my $output_file = "$build_dir/work/myexe";

  my $builder_exe = SPVM::Builder::Exe->new(
    class_name => $class_name,
    output_file => $output_file,
    build_dir => $build_dir,
    module_dirs => $module_dirs,
  );
  
  $builder_exe->build_exe_file;
}

# Exe name contain sub directory
{
  my $exe_dir = 't/.spvm_build/work/exe';
  mkpath $exe_dir;
  
  my $class_name = 'MyExe::Foo::Bar';
  my $build_dir = 't/exe/.spvm_build';
  my $module_dirs = ['t/exe/lib', @INC];
  my $output_file = "$build_dir/work/myexe";

  my $builder_exe = SPVM::Builder::Exe->new(
    class_name => $class_name,
    output_file => $output_file,
    build_dir => $build_dir,
    module_dirs => $module_dirs,
  );
  
  $builder_exe->build_exe_file;
}

ok(1);

done_testing;

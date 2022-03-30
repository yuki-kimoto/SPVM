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
  my $exe_dir = 't/exe/.spvm_build/work/exe';
  mkpath $exe_dir;
  
  my $class_name = 'MyExe';
  my $build_dir = 't/exe/.spvm_build';
  my $module_dirs = [map { "$_/SPVM" } 't/exe/lib', @INC];
  my $output_file = "$build_dir/work/myexe";
  my $config_file = 't/exe/myexe.config';

  my $builder_exe = SPVM::Builder::Exe->new(
    class_name => $class_name,
    output_file => $output_file,
    build_dir => $build_dir,
    module_dirs => $module_dirs,
    config_file => $config_file,
  );
  
  $builder_exe->build_exe_file;

  {
    no warnings 'once';
    my $link_info = $main::MYEXE_LINK_INFO;
    
    my $config = SPVM::Builder::Config->new_gnu99;
    
    ok($link_info->class_name, 'TestCase::NativeAPI2');
    ok($link_info->ld, $config->ld);
    ok($link_info->ldflags, $config->ldflags);
    like($link_info->output_file, qr|t/exe/.spvm_build/work/myexe$Config{exe_ext}|);
    my $is_object_file_infos = 1;
    for my $object_file_info (@{$link_info->object_file_infos}) {
      unless ($object_file_info->isa('SPVM::Builder::ObjectFileInfo')) {
        $is_object_file_infos = 0;
      }
    }
    ok($is_object_file_infos);
  }
}

# Exe name contain sub directory
{
  my $exe_dir = 't/exe/.spvm_build/work/exe';
  mkpath $exe_dir;
  
  my $class_name = 'MyExe::Foo::Bar';
  my $build_dir = 't/exe/.spvm_build';
  my $module_dirs = [map { "$_/SPVM" } 't/exe/lib', @INC];
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

BEGIN { $ENV{SPVM_BUILD_DIR} = '.spvm_build' }

use strict;
use warnings;

use Test::More;
use Config;
use File::Temp;

use SPVM::Builder::Exe;

use lib "t/lib";
use TestUtil::MyLib;

my $test_dir = "$FindBin::Bin";
my $build_dir = $ENV{SPVM_BUILD_DIR};

{
  my $tmp_dir = File::Temp->newdir;
  my $script_name = 't/08_spvmcc/script/myapp.spvm';
  my $output_file = "$tmp_dir/myapp";

  my $builder_exe = SPVM::Builder::Exe->new(
    script_name => $script_name,
    output_file => $output_file,
    build_dir => $build_dir,
  );
  
  $builder_exe->build_exe_file;
  
  {
    no warnings 'once';
    my $link_info = $main::MYEXE_LINK_INFO;
    
    my $config = SPVM::Builder::Config->new_c99;
    
    ok($link_info->config->ld, $config->ld);
    ok($link_info->config->ldflags, $config->ldflags);
    like($link_info->config->output_file, qr/\Q$tmp_dir\/myapp$Config{exe_ext}\E/);
    my $is_object_files = 1;
    for my $object_file_info (@{$link_info->object_file_infos}) {
      unless ($object_file_info->isa('SPVM::Builder::ObjectFileInfo')) {
        $is_object_files = 0;
      }
    }
    ok($is_object_files);
  }
  
  {
    no warnings 'once';
    my $compile_info = $main::MYEXE_COMPILE_INFO_BEFORE_COMPILE;
    ok(ref $compile_info eq 'SPVM::Builder::CompileInfo');
  }
  
  {
    no warnings 'once';
    my $compile_info = $main::MYEXE_COMPILE_INFO_GLOBAL_BEFORE_COMPILE;
    ok(ref $compile_info eq 'SPVM::Builder::CompileInfo');
  }
  
}

# Exe name contain sub directory
{
  my $tmp_dir = File::Temp->newdir;
  my $script_name = 't/08_spvmcc/script/myapp/foo/bar.spvm';
  my $output_file = "$tmp_dir/work/myapp";
  
  my $builder_exe = SPVM::Builder::Exe->new(
    script_name => $script_name,
    output_file => $output_file,
    build_dir => $build_dir,
    allow_no_config_file => 1,
  );
  
  $builder_exe->build_exe_file;
}

ok(1);

done_testing;

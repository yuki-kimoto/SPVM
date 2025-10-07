use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use Config;
use Errno;

use SPVM 'TestCase::NativeAPILinkInfo';

my $build_dir = $ENV{SPVM_BUILD_DIR};

# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

{
  my $link_info = $main::NATIVE_API_LINK_INFO;
  
  my $config = SPVM::Builder::Config->new_gnu99;
  
  ok($link_info->config->class_name, 'TestCase::NativeAPILinkInfo');
  ok($link_info->config->ld, $config->ld);
  ok($link_info->config->ldflags, $config->ldflags);
  like($link_info->config->output_file, qr|TestCase/NativeAPILinkInfo\.$Config{dlext}|);
  my $is_object_files = 1;
  for my $object_file (@{$link_info->object_files}) {
    unless ($object_file->isa('SPVM::Builder::ObjectFileInfo')) {
      $is_object_files = 0;
    }
  }
  ok($is_object_files);
}

# Clear exception
$api->destroy_runtime_permanent_vars;

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;

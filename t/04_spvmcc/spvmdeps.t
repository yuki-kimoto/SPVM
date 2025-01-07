use lib "t/testlib";
use TestAuto;

use Test::More;
use strict;
use warnings;
use utf8;
use Data::Dumper;
use File::Basename 'basename';
use Config;
use File::Path 'mkpath', 'rmtree';
use File::Spec;
use SPVM::Builder::Util;

use SPVM::Builder;
use File::Spec;

my $devnull = File::Spec->devnull;

my $test_dir = $ENV{SPVM_TEST_DIR};
my $build_dir = $ENV{SPVM_BUILD_DIR};

my @build_dir_parts = split('/', $build_dir);
my $exe_dir = "$build_dir/work/exe";

rmtree "$build_dir/work";

my $dev_null = File::Spec->devnull;

# Failed to parse options.
{
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmdeps --not-exist t/04_spvmcc/script/myapp.spvm);
    my $status = system($spvmcc_cmd);
    isnt($status, 0);
  }
}

{
  # --resource-info
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmdeps -I $test_dir/lib/SPVM -I t/02_vm/lib/SPVM --resource-info t/04_spvmcc/script/myapp.spvm);
    my $output = `$spvmcc_cmd`;
    like($output, qr|\Q[TestCase::NativeAPI2]|);
    like($output, qr|TestCase::Resource::Mylib1|);
    like($output, qr|TestCase::Resource::Mylib2|);
    like($output, qr|\Q[TestCase::Precompile]|);
  }
}

{
  # --dependency
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmdeps -I $test_dir/lib/SPVM -I t/02_vm/lib/SPVM --dependency t/04_spvmcc/script/myapp.spvm);
    my $output = `$spvmcc_cmd`;
    
    like($output, qr|^SPVM [\.\d]+$|m);
    like($output, qr|^TestCase::NativeAPI2 1\.002$|m);
    like($output, qr|^TestCase::Precompile 2\.005$|m);
    like($output, qr|^Byte$|m);
    like($output, qr|\x0A$|s);
    
    warn $output;
  }
}

{
  # --dependency-cpan
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmdeps -I $test_dir/lib/SPVM -I t/02_vm/lib/SPVM --dependency-cpan t/04_spvmcc/script/myapp.spvm);
    my $output = `$spvmcc_cmd`;
    
    like($output, qr|^SPVM [\.\d]+$|m);
    like($output, qr|^SPVM::TestCase::NativeAPI2 1\.002$|m);
    like($output, qr|^SPVM::TestCase::Precompile 2\.005$|m);
    like($output, qr|^SPVM::Byte$|m);
    like($output, qr|\x0A$|s);
  }
}

done_testing;

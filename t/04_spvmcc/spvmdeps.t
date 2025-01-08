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

# Basic
{
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmdeps -I $test_dir/lib/SPVM -I t/02_vm/lib/SPVM t/04_spvmcc/script/myapp.spvm);
    my $output = `$spvmcc_cmd`;
    
    like($output, qr|^SPVM$|m);
    like($output, qr|^TestCase::NativeAPI2$|m);
    like($output, qr|^TestCase::Precompile$|m);
    like($output, qr|^Byte$|m);
    like($output, qr|\x0A$|s);
    
    warn $output;
  }
  
  # --with-version
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmdeps -I $test_dir/lib/SPVM -I t/02_vm/lib/SPVM --with-version t/04_spvmcc/script/myapp.spvm);
    my $output = `$spvmcc_cmd`;
    
    like($output, qr|^SPVM [\.\d]+$|m);
    like($output, qr|^TestCase::NativeAPI2 1\.002$|m);
    like($output, qr|^TestCase::Precompile 2\.005$|m);
    like($output, qr|^Byte$|m);
    like($output, qr|\x0A$|s);
    
    warn $output;
  }
}

# --cpanm
{
  # --cpanm
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmdeps -I $test_dir/lib/SPVM -I t/02_vm/lib/SPVM --cpanm t/04_spvmcc/script/myapp.spvm);
    my $output = `$spvmcc_cmd`;
    
    like($output, qr|^cpanm SPVM$|m);
    like($output, qr|^cpanm SPVM::TestCase::NativeAPI2$|m);
    like($output, qr|^cpanm SPVM::TestCase::Precompile$|m);
    like($output, qr|^cpanm SPVM::Byte$|m);
    like($output, qr|\x0A$|s);
  }
  
  # --cpanm, --with-version
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmdeps -I $test_dir/lib/SPVM -I t/02_vm/lib/SPVM --cpanm --with-version t/04_spvmcc/script/myapp.spvm);
    my $output = `$spvmcc_cmd`;
    
    like($output, qr|^cpanm SPVM\@[\.\d]+$|m);
    like($output, qr|^cpanm SPVM::TestCase::NativeAPI2\@1\.002$|m);
    like($output, qr|^cpanm SPVM::TestCase::Precompile\@2\.005$|m);
    like($output, qr|^cpanm SPVM::Byte$|m);
    like($output, qr|\x0A$|s);
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

done_testing;

use lib "t/testlib";
use TestAuto;

use Test::More;

use strict;
use warnings;
use utf8;
use Config;
use File::Basename 'basename';
use File::Path 'mkpath', 'rmtree';
use File::Spec;
use Archive::Tar;
use JSON::PP;

use SPVM::Builder;
use SPVM::Builder::Util;

my $devnull = File::Spec->devnull;

my $test_dir = $ENV{SPVM_TEST_DIR};
my $build_dir = $ENV{SPVM_BUILD_DIR};

my $exe_dir = "$build_dir/.tmp/exe";
my $external_object_dir = "$build_dir/.tmp/external_object";

rmtree "$build_dir/work";

mkpath $exe_dir;
mkpath $external_object_dir;

my $dev_null = File::Spec->devnull;

sub to_cmd {
  my ($path) = @_;
  
  my $cmd = File::Spec->catfile(split("/", $path));
  
  return $cmd;
}

{
  # --build-spvm-archive
  {
    mkpath "t/04_spvmcc/script/.tmp";
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc --optimize=-O0 --quiet -B $build_dir -I $test_dir/lib/SPVM -o t/04_spvmcc/script/.tmp/myapp.spvm-archive.tar.gz --build-spvm-archive t/04_spvmcc/script/myapp.spvm);
    system($spvmcc_cmd) == 0
      or die "Can't execute spvmcc command $spvmcc_cmd:$!";
    
    ok(-f "t/04_spvmcc/script/.tmp/myapp.spvm-archive.tar.gz");
    ok(-s "t/04_spvmcc/script/.tmp/myapp.spvm-archive.tar.gz" > 1_000);
    my $tar = Archive::Tar->new;
    my $success = $tar->read("t/04_spvmcc/script/.tmp/myapp.spvm-archive.tar.gz");
    ok($success);
    
    my $spvm_archive_json = $tar->get_content("spvm-archive.json");
    my $spvmcc_info = JSON::PP->new->decode($spvm_archive_json);
    is($spvmcc_info->{app_name}, "myapp");
    ok(!$spvmcc_info->{mode});
    ok(!$spvmcc_info->{version});
    my $classes_h = {map { $_->{name} => $_ } @{$spvmcc_info->{classes}}};
    is($classes_h->{'TestCase::NativeAPI2'}{name}, 'TestCase::NativeAPI2');
    is($classes_h->{'TestCase::NativeAPI2'}{native}, 1);
    is($classes_h->{'TestCase::NativeAPI2'}{precompile}, 1);
    ok($classes_h->{'TestCase::Precompile'});
    ok($classes_h->{'TestCase::Resource::Mylib1'});
    ok($classes_h->{'TestCase::Resource::Mylib2'});
    my @tar_files = $tar->list_files;
    my $tar_files_h = {map { $_ => 1} @tar_files};
    ok($tar_files_h->{'object/SPVM/TestCase/NativeAPI2.o'});
    ok($tar_files_h->{'object/SPVM/TestCase/NativeAPI2.native/foo.o'});
    ok($tar_files_h->{'object/SPVM/TestCase/Resource/Mylib1.native/mylib1_source1.o'});
    ok($tar_files_h->{'object/SPVM/TestCase/Resource/Mylib2.native/mylib2_source1.o'});
    ok($tar_files_h->{'SPVM/TestCase/NativeAPI2.spvm'});
    ok($tar_files_h->{'SPVM/TestCase/Precompile.spvm'});
  }
  
  # use_spvm_archive
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc --optimize=-O0 --quiet -B $build_dir -I $test_dir/lib2/SPVM -o $exe_dir/spvm-archive t/04_spvmcc/script/spvm-archive.spvm);
    system($spvmcc_cmd) == 0
      or die "Can't execute spvmcc command $spvmcc_cmd:$!";
    
    my $execute_cmd = &to_cmd("$exe_dir/spvm-archive");
    my $output = `$execute_cmd`;
    chomp $output;
    my $output_expect = "spvm-archive 74,skip_class:1,api3:60";
    is($output, $output_expect);
  }
  
  # use_spvm_archive and --build-spvm-archive
  {
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc --optimize=-O0 --quiet -B $build_dir -I $test_dir/lib2/SPVM -o t/04_spvmcc/script/.tmp/myapp-with-archive.spvm-archive.tar.gz --build-spvm-archive --mode linux-64bit t/04_spvmcc/script/spvm-archive.spvm);
    system($spvmcc_cmd) == 0
      or die "Can't execute spvmcc command $spvmcc_cmd:$!";
    
    ok(-f "t/04_spvmcc/script/.tmp/myapp-with-archive.spvm-archive.tar.gz");
    my $tar = Archive::Tar->new;
    my $success = $tar->read("t/04_spvmcc/script/.tmp/myapp-with-archive.spvm-archive.tar.gz");
    ok($success);
    
    my $spvm_archive_json = $tar->get_content("spvm-archive.json");
    my $spvmcc_info = JSON::PP->new->decode($spvm_archive_json);
    is($spvmcc_info->{app_name}, "spvm-archive");
    is($spvmcc_info->{mode}, "linux-64bit");
    is($spvmcc_info->{version}, "1.005");
    my $classes_h = {map { $_->{name} => $_ } @{$spvmcc_info->{classes}}};
    is($classes_h->{'TestCase::NativeAPI2'}{name}, 'TestCase::NativeAPI2');
    is($classes_h->{'TestCase::NativeAPI2'}{native}, 1);
    is($classes_h->{'TestCase::NativeAPI2'}{precompile}, 1);
    is($classes_h->{'TestCase::NativeAPI3'}{name}, 'TestCase::NativeAPI3');
    is($classes_h->{'TestCase::NativeAPI3'}{native}, 1);
    ok(!$classes_h->{'TestCase::Precompile'});
    ok($classes_h->{'TestCase::Resource::Mylib1'});
    ok($classes_h->{'TestCase::Resource::Mylib2'});
    my @tar_files = $tar->list_files;
    my $tar_files_h = {map { $_ => 1} @tar_files};
    ok($tar_files_h->{'object/SPVM/TestCase/NativeAPI2.o'});
    ok($tar_files_h->{'object/SPVM/TestCase/NativeAPI2.native/foo.o'});
    ok($tar_files_h->{'object/SPVM/TestCase/Resource/Mylib1.native/mylib1_source1.o'});
    ok($tar_files_h->{'object/SPVM/TestCase/Resource/Mylib2.native/mylib2_source1.o'});
    ok($tar_files_h->{'SPVM/TestCase/NativeAPI2.spvm'});
    ok(!$tar_files_h->{'SPVM/TestCase/Precompile.spvm'});
    ok($tar_files_h->{'SPVM/TestCase/Resource/Mylib1.spvm'});
    ok($tar_files_h->{'SPVM/TestCase/Resource/Mylib2.spvm'});
  }
  
}

done_testing;

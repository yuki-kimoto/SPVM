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
    my $archive_dir = "t/04_spvmcc/script/.tmp/spvm-archive-myapp";
    File::Path::rmtree $archive_dir if -e $archive_dir; # Clean up
    File::Path::mkpath "t/04_spvmcc/script/.tmp";
    
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc --optimize=-O0 --quiet -B $build_dir -I $test_dir/lib/SPVM -o $archive_dir --build-spvm-archive t/04_spvmcc/script/myapp.spvm);
    system($spvmcc_cmd) == 0
      or die "Can't execute spvmcc command $spvmcc_cmd:$!";
    
    ok(-d $archive_dir, "Archive directory exists");
    
    # Check JSON metadata
    my $json_file = "$archive_dir/spvm-archive.json";
    ok(-f $json_file, "Metadata file exists");
    my $json_content = do { local $/; open my $fh, '<', $json_file or die $!; <$fh> };
    my $spvmcc_info = JSON::PP->new->decode($json_content);
    
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
    
    # Check physical files
    ok(-f "$archive_dir/object/SPVM/TestCase/NativeAPI2.o");
    ok(-f "$archive_dir/object/SPVM/TestCase/NativeAPI2.native/foo.o");
    ok(-f "$archive_dir/object/SPVM/TestCase/Resource/Mylib1.native/mylib1_source1.o");
    ok(-f "$archive_dir/object/SPVM/TestCase/Resource/Mylib2.native/mylib2_source1.o");
    ok(-f "$archive_dir/SPVM/TestCase/NativeAPI2.spvm");
    ok(-f "$archive_dir/SPVM/TestCase/Precompile.spvm");
  }
  
  # use_spvm_archive (Linking test)
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
    my $archive_output_dir = "t/04_spvmcc/script/.tmp/spvm-archive-myapp-extend";
    File::Path::rmtree $archive_output_dir if -e $archive_output_dir;
    
    # 1. Prepare dummy library files in the build directory before running spvmcc
    # The builder searches $build_dir/lib during the archive process
    my $lib_dir_in_build = "t/04_spvmcc/script/.tmp/spvm-archive-myapp/lib";
    File::Path::mkpath $lib_dir_in_build;
    my @dummy_libs = ("$lib_dir_in_build/foo.a", "$lib_dir_in_build/foo.lib");
    for my $dummy_lib (@dummy_libs) {
      open my $fh, '>', $dummy_lib or die "Can't create $dummy_lib: $!";
      binmode $fh;
      print $fh "dummy library content";
      close $fh;
    }
    
    # 2. Execute spvmcc
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc --optimize=-O0 --quiet -B $build_dir -I $test_dir/lib2/SPVM -o $archive_output_dir --build-spvm-archive --mode linux-64bit t/04_spvmcc/script/spvm-archive.spvm);
    system($spvmcc_cmd) == 0
      or die "Can't execute spvmcc command $spvmcc_cmd:$!";
    
    ok(-d $archive_output_dir, "Archive directory exists");
    
    my $json_file = "$archive_output_dir/spvm-archive.json";
    my $json_content = do { local $/; open my $fh, '<', $json_file or die $!; <$fh> };
    my $spvmcc_info = JSON::PP->new->decode($json_content);
    
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
    
    # Check files in merged archive
    ok(-f "$archive_output_dir/object/SPVM/TestCase/NativeAPI2.o");
    ok(-f "$archive_output_dir/object/SPVM/TestCase/Resource/Mylib1.native/mylib1_source1.o");
    ok(-f "$archive_output_dir/SPVM/TestCase/NativeAPI2.spvm");
    ok(!-f "$archive_output_dir/SPVM/TestCase/Precompile.spvm"); # Should be skipped
    ok(-f "$archive_output_dir/SPVM/TestCase/Resource/Mylib1.spvm");

    # 3. Check if library files are correctly copied from build_dir/lib to archive_dir/lib
    ok(-f "$archive_output_dir/lib/foo.a", "Static library foo.a is copied to the archive");
    ok(-f "$archive_output_dir/lib/foo.lib", "Static library foo.lib is copied to the archive");
  }
  
}

done_testing;

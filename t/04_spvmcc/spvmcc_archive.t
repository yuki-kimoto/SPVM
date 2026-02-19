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
  my $archive_dir = "t/04_spvmcc/script/.tmp/spvm-archive-myapp";
  {
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
  
  # Add files to SPVM archive
  {
    use Config;
    my $lib_dir_in_spvm_archive = "$archive_dir/lib";
    my $include_dir_in_spvm_archive = "$archive_dir/include";
    my $tmp_build_dir = "t/04_spvmcc/.spvm_build/.tmp";
    
    File::Path::mkpath $lib_dir_in_spvm_archive;
    File::Path::mkpath $include_dir_in_spvm_archive;
    File::Path::mkpath $tmp_build_dir;

    # 1. Real Build: spvmcc_archive_test.h and its real static library
    my $header_file = "$include_dir_in_spvm_archive/spvmcc_archive_test.h";
    {
      open my $fh, '>', $header_file or die "Can't create $header_file: $!";
      print $fh "int spvmcc_archive_test_foo(void);\n";
      close $fh;
    }

    my $src_file = "$tmp_build_dir/spvmcc_archive_test.c";
    {
      open my $fh, '>', $src_file or die "Can't create $src_file: $!";
      print $fh qq(#include "spvmcc_archive_test.h"\n);
      print $fh "int spvmcc_archive_test_foo(void) { return 1; }\n";
      close $fh;
    }

    my $cc = $Config{cc};
    my $ccflags = "$Config{ccflags} $Config{optimize}";
    my $obj_ext = $Config{obj_ext};
    my $lib_ext = $Config{lib_ext};
    my $is_msvc = $^O eq 'MSWin32' && $cc =~ /cl/i;

    # Compile spvmcc_archive_test.c -> object
    my $obj_file = "$tmp_build_dir/spvmcc_archive_test$obj_ext";
    my @cc_cmd_lib = $is_msvc 
      ? ($cc, (split /\s+/, $ccflags), '-c', "-Fo$obj_file", "-I$include_dir_in_spvm_archive", $src_file)
      : ($cc, (split /\s+/, $ccflags), '-c', '-o', $obj_file, "-I$include_dir_in_spvm_archive", $src_file);
    system(@cc_cmd_lib) == 0 or die "Failed to compile $src_file";

    # Create real static library (only for current OS extension)
    my $lib_file = "$lib_dir_in_spvm_archive/spvmcc_archive_test$lib_ext";
    my @ar_cmd = $is_msvc
      ? ('lib', '-nologo', "-out:$lib_file", $obj_file)
      : ($Config{ar} || 'ar', 'rc', $lib_file, $obj_file);
    system(@ar_cmd) == 0 or die "Failed to create static library $lib_file";

    # 2. Real Build: bar.c -> bar.o (Depends on spvmcc_archive_test.h)
    my $bar_c_file = "$tmp_build_dir/bar.c";
    {
      open my $fh, '>', $bar_c_file or die "Can't create $bar_c_file: $!";
      print $fh qq(#include "spvmcc_archive_test.h"\n);
      print $fh "int bar(void) { return spvmcc_archive_test_foo(); }\n";
      close $fh;
    }
    my $bar_o_file = "$tmp_build_dir/bar$obj_ext";
    my @cc_cmd_bar = $is_msvc
      ? ($cc, (split /\s+/, $ccflags), '-c', "-Fo$bar_o_file", "-I$include_dir_in_spvm_archive", $bar_c_file)
      : ($cc, (split /\s+/, $ccflags), '-c', '-o', $bar_o_file, "-I$include_dir_in_spvm_archive", $bar_c_file);
    system(@cc_cmd_bar) == 0 or die "Failed to compile $bar_c_file";

    # 3. Dummy Files: bar.lib (0 bytes) and bar.hpp (0 bytes)
    # Regardless of OS, we create bar.lib as a dummy to satisfy the test
    my $dummy_lib = "$lib_dir_in_spvm_archive/bar.lib";
    open my $fh_l, '>', $dummy_lib; close $fh_l;

    my $dummy_header = "$include_dir_in_spvm_archive/bar.hpp";
    open my $fh_h, '>', $dummy_header; close $fh_h;
    
    # Optional: If your test also checks for .a on Windows, you might need a dummy .a too?
    # But for now, I've stuck strictly to your instruction.
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
  
  # use_spvm_archive with include and lib
  {
    use Config;
    my $spvmcc_cmd = qq($^X -Mblib blib/script/spvmcc --optimize=-O0 --quiet -B $build_dir -I $test_dir/lib2/SPVM --object-file t/04_spvmcc/.spvm_build/.tmp/bar$Config{obj_ext} -o $exe_dir/spvm-archive t/04_spvmcc/script/spvm-archive.spvm);
    system($spvmcc_cmd) == 0
      or die "Can't execute spvmcc command $spvmcc_cmd:$!";
    
    my $execute_cmd = &to_cmd("$exe_dir/spvm-archive");
    my $output = `$execute_cmd`;
    chomp $output;
    my $output_expect = "spvm-archive 74,skip_class:1,api3:60";
    is($output, $output_expect);
  }
  
  # --build-spvm-archive with use_spvm_archive
  {
    my $archive_output_dir = "t/04_spvmcc/script/.tmp/spvm-archive-myapp-extend";
    File::Path::rmtree $archive_output_dir if -e $archive_output_dir;
    
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

    # 3. Check libraries
    ok(-f "$archive_output_dir/lib/spvmcc_archive_test.a");
    ok(-f "$archive_output_dir/lib/bar.lib");
    
    # 4. Check headers
    ok(-f "$archive_output_dir/include/spvmcc_archive_test.h");
    ok(-f "$archive_output_dir/include/bar.hpp");
  }
  
}

done_testing;

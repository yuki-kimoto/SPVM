use lib "t/lib";
use TestAuto;
use TestUtil::MyLib;

use strict;
use warnings;
use Config;
use FindBin;
use Test::More;
use File::Temp 'tempdir';
use File::Path 'make_path', 'rmtree';
use SPVM::Builder::Util;
use File::Basename 'dirname';
use SPVM;

# Prepare temporary directory
my $tmp_dir = File::Temp->newdir;
my $build_dir = $ENV{SPVM_BUILD_DIR};

my $lib_dir = "$tmp_dir/lib/SPVM/TestCase";
my $native_include_dir = "$lib_dir/BuildCache.native/include";
my $native_src_dir     = "$lib_dir/BuildCache.native/src/baz";

make_path($lib_dir);
make_path($native_include_dir . "/baz");
make_path($native_src_dir);

# Define file paths
my $spvm_class_file = "$lib_dir/BuildCache.spvm";
my $config_file = "$lib_dir/BuildCache.config";
my $native_class_file = "$lib_dir/BuildCache.c";
my $native_header_file = "$native_include_dir/baz/baz.h";
my $native_source_file = "$native_src_dir/baz.c";

# Create initial files
{
  my $content = "class TestCase::BuildCache {\n  native static method test : int ();\n}\n";
  SPVM::Builder::Util::spurt_binary($spvm_class_file, $content);
}

# .config file (Faithfully following the provided sample style)
{
  my $content = <<'EOS';
use strict;
use warnings;
use SPVM::Builder::Config;
use File::Basename 'dirname';

my $config = SPVM::Builder::Config->new_c99;

my $dir = dirname(__FILE__);

$config->add_source_file("baz/baz.c");

$config;
EOS

  SPVM::Builder::Util::spurt_binary($config_file, $content);
}

{
  my $content = "#define BAZ_VALUE 1\n";
  SPVM::Builder::Util::spurt_binary($native_header_file, $content);
}

{
  my $content = <<'EOS';
#include "baz/baz.h"
int get_baz() { return BAZ_VALUE; }
EOS
  
  SPVM::Builder::Util::spurt_binary($native_source_file, $content);
}

{
  my $content = <<'EOS';
#include <spvm_native.h>
#include "baz/baz.h"
int get_baz();
int32_t SPVM__TestCase__BuildCache__test(SPVM_ENV* env, SPVM_VALUE* stack) {
  stack[0].ival = get_baz();
  return 0;
}
EOS

  SPVM::Builder::Util::spurt_binary($native_class_file, $content);
}

# Helper to compile
my $compile_cmd = "$^X -I$tmp_dir/lib -Mblib -e \"use SPVM 'TestCase::BuildCache';\"";

my $native_class_object_file_glob_pattern = "$build_dir/work/object/*/*/SPVM/TestCase/BuildCache.o";
my $native_source_baz_object_file_glob_pattern = "$build_dir/work/object/*/*/SPVM/TestCase/BuildCache.native/src/baz/baz.o";

my @current_native_class_object_files;
my @current_native_source_baz_object_files;

# First build
{
  system($compile_cmd) == 0 or die "First build failed";
  
  use File::Find;
  
  print "--- [Test Output]Build Directory Contents ---\n";
  find({
    wanted => sub {
      my $file = $File::Find::name;
      if (-f $file) {
        print STDERR "Found: $file\n";
      }
    },
    no_chdir => 1,
  }, $build_dir);
  print "--------------------------------\n";
  
  @current_native_class_object_files = glob $native_class_object_file_glob_pattern;
  @current_native_source_baz_object_files = glob $native_source_baz_object_file_glob_pattern;
  
  my $native_class_object_file = $current_native_class_object_files[0];
  my $native_source_baz_object_file = $current_native_source_baz_object_files[0];
  ok(-f $native_class_object_file, "Main object file exists");
  ok(-f $native_source_baz_object_file, "Secondary source object file exists");
}

# Second build without changes (Should be cached)
{
  system($compile_cmd) == 0 or die "Second build failed";
  
  @current_native_class_object_files = glob $native_class_object_file_glob_pattern;
  @current_native_source_baz_object_files = glob $native_source_baz_object_file_glob_pattern;
  
  my $native_class_object_file = $current_native_class_object_files[0];
  my $native_source_baz_object_file = $current_native_source_baz_object_files[0];
  ok(-f $native_class_object_file, "Main object file exists");
  ok(-f $native_source_baz_object_file, "Secondary source object file exists");
  
  is(@current_native_class_object_files, 1);
  is(@current_native_source_baz_object_files, 1);
}

{
  # Update native class file
  {
    my $content = SPVM::Builder::Util::slurp_binary($native_class_file);
    $content .= "\n// modification\n";
    
    SPVM::Builder::Util::spurt_binary($native_class_file, $content);
  }
  
  
  # Re-build
  system($compile_cmd) == 0 or die;
  
  my @old_native_class_object_files = @current_native_class_object_files;
  my @old_native_source_baz_object_files = @current_native_source_baz_object_files;
  
  @current_native_class_object_files = glob $native_class_object_file_glob_pattern;
  @current_native_source_baz_object_files = glob $native_source_baz_object_file_glob_pattern;
  
  is(@current_native_class_object_files, @old_native_class_object_files + 1);
  is(@current_native_source_baz_object_files, @old_native_source_baz_object_files);
}

{
  # Update native source file
  {
    my $content = SPVM::Builder::Util::slurp_binary($native_source_file);
    $content .= "\n// modification\n";
    
    SPVM::Builder::Util::spurt_binary($native_source_file, $content);
  }
  
  # Re-build
  system($compile_cmd) == 0 or die;
  
  my @old_native_class_object_files = @current_native_class_object_files;
  my @old_native_source_baz_object_files = @current_native_source_baz_object_files;
  
  @current_native_class_object_files = glob $native_class_object_file_glob_pattern;
  @current_native_source_baz_object_files = glob $native_source_baz_object_file_glob_pattern;
  
  is(@current_native_class_object_files, @old_native_class_object_files);
  is(@current_native_source_baz_object_files, @old_native_source_baz_object_files + 1);
}

{
  # Update native header file (Both objects should be re-compiled)
  {
    my $content = SPVM::Builder::Util::slurp_binary($native_header_file);
    $content .= "\n// modification for header\n";
    
    SPVM::Builder::Util::spurt_binary($native_header_file, $content);
  }
  
  # Re-build
  system($compile_cmd) == 0 or die;
  
  my @old_native_class_object_files = @current_native_class_object_files;
  my @old_native_source_baz_object_files = @current_native_source_baz_object_files;
  
  @current_native_class_object_files = glob $native_class_object_file_glob_pattern;
  @current_native_source_baz_object_files = glob $native_source_baz_object_file_glob_pattern;
  
  # Both should be incremented
  is(@current_native_class_object_files, @old_native_class_object_files + 1, "Main object re-compiled after header change");
  is(@current_native_source_baz_object_files, @old_native_source_baz_object_files + 1, "baz.o re-compiled after header change");
}

done_testing;


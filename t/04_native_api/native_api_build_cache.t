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
  open my $spvm_fh, '>', $spvm_class_file or die $!;
  print $spvm_fh "class TestCase::BuildCache {\n  native static method test : int ();\n}\n";
}

# .config file (Faithfully following the provided sample style)
{
  open my $config_fh, '>', $config_file or die $!;
  print $config_fh <<'EOS';
use strict;
use warnings;
use SPVM::Builder::Config;
use File::Basename 'dirname';

my $config = SPVM::Builder::Config->new_c99;

my $dir = dirname(__FILE__);

$config->add_source_file("baz/baz.c");

$config;
EOS
}

{
  open my $h_fh, '>', $native_header_file or die $!;
  print $h_fh "#define BAZ_VALUE 1\n";
}

{
  open my $src_fh, '>', $native_source_file or die $!;
  print $src_fh "#include \"baz/baz.h\"\n";
  print $src_fh "int get_baz() { return BAZ_VALUE; }\n";
}

{
  open my $c_fh, '>', $native_class_file or die $!;
  print $c_fh <<'EOS';
#include <spvm_native.h>
#include "baz/baz.h"
int get_baz();
int32_t SPVM__TestCase__BuildCache__test(SPVM_ENV* env, SPVM_VALUE* stack) {
  stack[0].ival = get_baz();
  return 0;
}
EOS
}

# Helper to compile
my $compile_cmd = "$^X -I$tmp_dir/lib -Mblib -e \"use SPVM 'TestCase::BuildCache';\"";

# First build
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

my ($obj_file) = glob "$build_dir/work/object/*/*/SPVM/TestCase/BuildCache.o";
my ($baz_obj_file) = glob "$build_dir/work/object/*/*/SPVM/TestCase/BuildCache.native/src/baz/baz.o";
ok(-f $obj_file, "Main object file exists");
ok(-f $baz_obj_file, "Secondary source object file exists");

my $start_mtime = (stat $obj_file)[9];
my $start_baz_mtime = (stat $baz_obj_file)[9];

# Second build without changes (Should be cached)
system($compile_cmd) == 0 or die "Second build failed";
is((stat $obj_file)[9], $start_mtime, "Main object is cached");
is((stat $baz_obj_file)[9], $start_baz_mtime, "baz.o is cached");

# Clear cache
rmtree "$build_dir/work";
ok(!-d "$build_dir/work", "work directory cleared");

# Re-build
system($compile_cmd) == 0 or die "Build after baz.h update failed";
my ($obj_file_3) = glob "$build_dir/work/object/*/*/SPVM/TestCase/BuildCache.o";
ok(-f $obj_file_3, "Main object re-generated");

# Update baz.c and clear work directory
{
  open my $src_fh_upd, '>>', $native_source_file or die $!;
  print $src_fh_upd "\n// modification\n";
}

# Clear cache
rmtree "$build_dir/work";
ok(!-d "$build_dir/work", "work directory cleared again");

# Re-build
system($compile_cmd) == 0 or die "Build after baz.c update failed";
my ($baz_obj_file_3) = glob "$build_dir/work/object/*/*/SPVM/TestCase/BuildCache.native/src/baz/baz.o";
ok(-f $baz_obj_file_3, "baz.o re-generated");

done_testing;

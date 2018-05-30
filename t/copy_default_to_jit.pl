use strict;
use warnings;
use File::Copy 'copy';
use File::Basename 'basename', 'dirname';
use File::Path 'mkpath', 'rmtree';

# remove and copy test files for Precompile
my @old_precompile_test_files = glob 't/precompile/*';
for my $old_precompile_test_file (@old_precompile_test_files) {
  if (-f $old_precompile_test_file) {
    unlink $old_precompile_test_file
      or die "Can't delete $old_precompile_test_file";
  }
}
my @default_test_files = glob 't/default/*';
for my $default_test_file (@default_test_files) {
  my $new_precompile_test_file = 't/precompile/' . basename $default_test_file;
  if (-f $default_test_file) {
    copy $default_test_file, $new_precompile_test_file
      or die "Can't copy $default_test_file to $new_precompile_test_file";
  }
}

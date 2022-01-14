use strict;
use warnings;
use File::Copy 'copy';
use File::Basename 'basename', 'dirname';
use File::Path 'mkpath', 'rmtree';
use File::Find;

mkpath 't/precompile';

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

# remove and edit and copy lib file for JIT
my $test_default_dir = 't/default/lib';
my $test_precompile_dir = 't/precompile/lib';
rmtree $test_precompile_dir;
mkdir $test_precompile_dir;
find(
  {
    wanted => sub {
      my $file = $File::Find::name;
      my $to_dir = dirname $file;
      $to_dir =~ s|t/default/lib|t/precompile/lib|;
      my $to_file = $file;
      $to_file =~ s|t/default/lib|t/precompile/lib|;
      
      if (-f $file) {
        
        my ($file_atime, $file_mtime) = (stat $file)[8, 9];
        
        open my $fh, '<', $file
          or die "Can't open $file: $!";
        
        my $content = do { local $/; <$fh> };
        
        $content =~ s/class\s+([\w:]+)\s*\{/class $1 : precompile {/g;
        
        mkpath $to_dir;
        
        open my $to_fh, '>', $to_file
          or die "Can't open $to_file: $!";
        
        print $to_fh $content;
        
        close $to_fh;
        
        # Copy time stamp
        utime $file_atime, $file_mtime, $to_file
          or die;
      }
    },
    no_chdir => 1,
  },
  $test_default_dir
);

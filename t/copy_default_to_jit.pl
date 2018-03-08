use strict;
use warnings;
use File::Copy 'copy';
use File::Basename 'basename', 'dirname';
use File::Find;
use File::Path 'mkpath', 'rmtree';

# remove and copy test files for JIT
my @old_jit_test_files = glob 't/jit/*';
for my $old_jit_test_file (@old_jit_test_files) {
  if (-f $old_jit_test_file) {
    unlink $old_jit_test_file
      or die "Can't delete $old_jit_test_file";
  }
}
my @default_test_files = glob 't/default/*';
for my $default_test_file (@default_test_files) {
  my $new_jit_test_file = 't/jit/' . basename $default_test_file;
  if (-f $default_test_file) {
    copy $default_test_file, $new_jit_test_file
      or die "Can't copy $default_test_file to $new_jit_test_file";
  }
}

# remove and edit and copy lib file for JIT
my $test_default_dir = 't/default/lib';
my $test_jit_dir = 't/jit/lib';
rmtree $test_jit_dir;
mkdir $test_jit_dir;
find(
  {
    wanted => sub {
      my $file = $File::Find::name;
      my $to_dir = dirname $file;
      $to_dir =~ s|t/default/lib|t/jit/lib|;
      my $to_file = $file;
      $to_file =~ s|t/default/lib|t/jit/lib|;
      
      if (-f $file) {
        
        open my $fh, '<', $file
          or die "Can't open $file: $!";
        
        my $content = do { local $/; <$fh> };
        
        $content =~ s/^(\s+)sub/${1}jit sub/mg;
        
        mkpath $to_dir;
        
        open my $to_fh, '>', $to_file
          or die "Can't open $to_file: $!";
        
        print $to_fh $content;
        
        close $to_fh;
      }
    },
    no_chdir => 1,
  },
  $test_default_dir
);

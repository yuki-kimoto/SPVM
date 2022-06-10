package TestFile;

use strict;
use warnings;
use File::Basename 'basename';
use File::Path 'mkpath';

# Copy test_files to test_files_tmp
sub copy_test_files_tmp {

  my $test_files_dir = 't/test_files';
  my $test_files_tmp_dir = 't/test_files_tmp';
  
  mkpath $test_files_tmp_dir;
  
  my @test_files = glob "$test_files_dir/*";
  
  for my $file (@test_files) {
    my $file_base = basename $file;
    my $file_tmp = "$test_files_tmp_dir/$file_base";
    
    open my $in_fh, '<', $file
      or die "Can't open file $file: $!";
    
    my $content = do { local $/; <$in_fh> };
    
    open my $out_fh, '>', $file_tmp
      or die "Can't open file $file: $!";
    
    binmode $out_fh;
    
    print $out_fh $content;
  }
}

1;

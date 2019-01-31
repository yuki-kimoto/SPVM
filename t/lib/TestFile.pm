package TestFile;

use strict;
use warnings;
use File::Basename 'basename';
use File::Path 'mkpath';

my $os_newline;
if ($^O eq 'MSWin32') {
  $os_newline = "\x0D\x0A";
}
else {
  $os_newline = "\x0A";
}

# Copy test_files to test_files_tmp with replacing os newline
sub copy_test_files_tmp_replace_newline {

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
    
    # Replace with os newline
    $content =~ s/\x0D\x0A|\x0D|\x0A/$os_newline/g;
    
    open my $out_fh, '>', $file_tmp
      or die "Can't open file $file: $!";
    
    binmode $out_fh;
    local $/ = $os_newline;
    
    print $out_fh $content;
  }
}

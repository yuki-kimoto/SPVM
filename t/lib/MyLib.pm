package MyLib;

use strict;
use warnings;

use FindBin;

sub import {
  my $dir = $FindBin::Bin;
  my $test_lib_dir;

  # (Comment: Traverse up to 10 levels to find the lib directory)
  for (1..10) {
    # (Comment: Stop if Makefile.PL is found at this level, as this marks the project root)
    if (-f "$dir/Makefile.PL") {
      last;
    }
    
    # (Comment: Check for lib directory at the current level)
    if (-d "$dir/lib") {
      $test_lib_dir = "$dir/lib";
      last;
    }
    
    $dir .= "/..";
  }

  if ($test_lib_dir) {
    # (Comment: Add the found lib directory to @INC if it's not already present)
    unshift @INC, $test_lib_dir unless grep { $_ eq $test_lib_dir } @INC;
  }
}

1;


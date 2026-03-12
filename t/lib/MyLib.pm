package MyLib;

use strict;
use warnings;

use FindBin;

sub import {

  my $dir = $FindBin::Bin;
  my $test_lib_dir;

  # (Comment: Traverse up to 5 levels to find the lib directory)
  for (1..5) {
    if (-d "$dir/lib") {
      $test_lib_dir = "$dir/lib";
      last;
    }
    $dir .= "/..";
  }
  
  if ($test_lib_dir) {
    # (Comment: Add found lib directory to @INC)
    unshift @INC, $test_lib_dir;
  }

}

1;

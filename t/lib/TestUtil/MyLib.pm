package TestUtil::MyLib;

use strict;
use warnings;

use FindBin;
use Cwd 'abs_path';

sub import {
  my $current_dir = abs_path($FindBin::Bin);
  my @test_lib_dirs;
  my $found_project_root;

  # (Comment: Traverse up to 100 levels to find lib directories)
  for (1..100) {
    # (Comment: If lib directory exists at this level, add it to the list)
    if (-d "$current_dir/lib") {
      push @test_lib_dirs, "$current_dir/lib";
    }
    
    # (Comment: Stop if Makefile.PL is found)
    if (-f "$current_dir/Makefile.PL") {
      $found_project_root = 1;
      last;
    }
    
    # (Comment: Get parent directory)
    my $parent_dir = abs_path("$current_dir/..");
    
    # (Comment: Stop if the parent directory is the same as current directory, meaning root is reached)
    if ($parent_dir eq $current_dir) {
      last;
    }
    
    $current_dir = $parent_dir;
  }

  # (Comment: Throw an exception if the project root was not found)
  unless ($found_project_root) {
    die "The project root (Makefile.PL) could not be found. Reached the system root or 100 levels from $FindBin::Bin.";
  }

  # (Comment: Just unshift everything found)
  unshift @INC, @test_lib_dirs;
}

1;

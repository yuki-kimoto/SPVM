BEGIN { $ENV{SPVM_CC_OPTIMIZE} = '-O0 -g3'; }

use lib "t/lib";
use TestAuto;
use TestUtil::MyLib;

use strict;
use warnings;
use Config;
use File::Find;
use File::Path 'mkpath';
use File::Basename 'dirname';
use File::Copy 'copy';
use Config;
use FindBin;

# Choose classes that is shared for performance
use SPVM 'TestCase';
use SPVM 'TestCase::Minimal';
use SPVM 'TestCase::Simple';

copy_dlls_from_build_dir_to_lib($ENV{SPVM_BUILD_DIR});

sub copy_dlls_from_build_dir_to_lib {
  my ($build_dir) = @_;
  
  # (Comment: Use absolute path to ensure regex matches correctly)
  my $work_lib_dir = File::Spec->rel2abs("$build_dir/work/lib");
  return unless -d $work_lib_dir;

  my $script_lib_dir = "$FindBin::Bin/lib";
  my $dlext = $Config{dlext};

  find(sub {
    if (/\.$dlext$/) {
      my $src_file = File::Spec->rel2abs($File::Find::name);
      
      # (Comment: More robust way to get relative path)
      my $rel_path = $src_file;
      $rel_path =~ s|^\Q$work_lib_dir\E[/\\ ]*||; # (Comment: Support both / and \)
      
      my $dest_file = "$script_lib_dir/$rel_path";
      
      # (Comment: Create destination directory before copy)
      my $dest_dir = dirname($dest_file);
      unless (-d $dest_dir) {
        mkpath($dest_dir) or die "Can't mkpath $dest_dir: $!";
      }
      
      copy($src_file, $dest_file) or die "Can't copy $src_file to $dest_file: $!";
    }
  }, $work_lib_dir);
}


use strict;
use warnings;
use File::Copy 'copy';
use File::Basename 'basename', 'dirname';
use File::Path 'mkpath', 'rmtree';
use File::Find;


mkpath 't/precompile';

# remove and edit and copy lib file for JIT
my $test_default_dir = 't/default';
my $test_precompile_dir = 't/precompile';
rmtree $test_precompile_dir;
mkdir $test_precompile_dir;
find(
  {
    wanted => sub {
      my $file = $File::Find::name;
      my $to_dir = dirname $file;
      $to_dir =~ s|t/default|t/precompile|;
      my $to_file = $file;
      $to_file =~ s|t/default|t/precompile|;
      
      if (-f $file) {
        
        return if $file =~ /[\/\\]\./;
        
        my ($file_atime, $file_mtime) = (stat $file)[8, 9];
        
        open my $fh, '<', $file
          or die "Can't open $file: $!";
        
        my $content = do { local $/; <$fh> };
        
        $content =~ s/class +([\w:]+) *\{/class $1 : precompile {/g;
        
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

# Add the time stamp file for Makefile
my $time_stamp_file = "$test_precompile_dir/time_stamp.txt";
open my $time_stamp_fh, '>', $time_stamp_file
  or die "Can't open file \"$time_stamp_file\": $!";

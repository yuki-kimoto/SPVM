use lib "t/testlib";
use TestAuto;

use strict;
use warnings;
use File::Copy 'copy';
use File::Basename 'basename', 'dirname';
use File::Path 'mkpath', 'rmtree';
use File::Find;

my $test_dir_vm_base = $ENV{SPVM_TEST_DIR_VM_BASE};
my $test_dir_vm = $ENV{SPVM_TEST_DIR_VM};
my $test_dir_precompile_base = $ENV{SPVM_TEST_DIR_PRECOMPILE_BASE};
my $test_dir_precompile = $ENV{SPVM_TEST_DIR_PRECOMPILE};

mkpath $test_dir_precompile;

# remove and edit and copy lib file for JIT
rmtree $test_dir_precompile;
mkdir $test_dir_precompile;
find(
  {
    wanted => sub {
      my $file = $File::Find::name;
      my $to_dir = dirname $file;
      $to_dir =~ s|t/$test_dir_vm_base|t/$test_dir_precompile_base|;
      my $to_file = $file;
      $to_file =~ s|t/$test_dir_vm_base|t/$test_dir_precompile_base|;
      
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
  $test_dir_vm
);

# Add the time stamp file for Makefile
my $time_stamp_file = "$test_dir_precompile/time_stamp.txt";
open my $time_stamp_fh, '>', $time_stamp_file
  or die "Can't open file \"$time_stamp_file\": $!";

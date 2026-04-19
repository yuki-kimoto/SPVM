use strict;
use warnings;
use File::Copy 'copy';
use File::Basename 'basename', 'dirname';
use File::Path 'mkpath', 'rmtree';
use File::Find;

my $test_dir_vm_base = '02_vm';
my $test_dir_vm = "t/$test_dir_vm_base";
my $test_dir_precompile_base = '03_precompile';
my $test_dir_precompile = "t/$test_dir_precompile_base";

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
        
        binmode $fh;
        
        my $content = do { local $/; <$fh> };
        
        if ($file =~ /\.spvm$/) {
          # Edit only the first class definition in the file
          $content =~ s/{/ : precompile {/;
          $content =~ s/:\s*([a-z][\w:]*)\s*:\s*precompile/: $1 precompile/g;
        }
        
        # Inject SPVM_CC_OPTIMIZE for .t files
        if ($file =~ /\.t$/) {
          # Set environment variables at the beginning of the test
          my $env_settings = '';
          $env_settings .= "BEGIN { \$ENV{SPVM_CC_OPTIMIZE} = '-O0 -g'; }\n";
          
          # Parallel testing on Windows occasionally fails due to permission denied loading of DLLs,
          # object files, and C language source files.
          # I worked towards resolving this, but concluded that it was impossible due to OS limitations. 
          # Rather than leaving a large number of correct workarounds,
          # I decided to remove it entirely and not use parallel testing with shared build directories on Windows.
          
          unless ($^O eq 'MSWin32') {
            $env_settings .= "BEGIN { \$ENV{SPVM_BUILD_DIR} = '.spvm_build'; }\n";
          }
          
          $content = $env_settings . $content;
        }
        
        mkpath $to_dir;
        
        open my $to_fh, '>', $to_file
          or die "Can't open $to_file: $!";
        
        binmode $to_fh;
        
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

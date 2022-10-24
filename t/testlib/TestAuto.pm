package TestAuto;

use strict;
use warnings;

use FindBin;
use lib "t/testlib";
use File::Find;
use File::Basename 'basename', 'dirname';

sub import {
  my $test_dir;
  if ($FindBin::Bin =~ /\/precompile$/) {
    $test_dir = 't/precompile';
    
    # Set build directory
    my $test_lib_dir = "$test_dir/lib";
    my $test_lib_dir_re = quotemeta($test_lib_dir);
    
    find(
      {
        wanted => sub {
          my $class_name = $File::Find::name;
          if ($class_name =~ /\.spvm$/) {
            $class_name =~ s|$test_lib_dir_re||;
            $class_name =~ s|^/SPVM/||;
            $class_name =~ s|/|::|g;
            $class_name =~ s|\.spvm$||;
            
            SPVM::Precompile->import($class_name);
          }
        },
        no_chdir => 1,
      },
      $test_lib_dir
    );

    $ENV{SPVM_TEST_PRECOMPILE} = 1;
  }
  else {
    $test_dir = 't/default';
  }
  
  my $test_lib_dir = "$test_dir/lib";
  unshift @INC, $test_lib_dir;
  
  $ENV{SPVM_TEST_DIR} = $test_dir;
  $ENV{SPVM_BUILD_DIR} = "$test_dir/.spvm_build";
}

1;

=pod

=DESCRITPION

if test scritp file is in precompile directory, precompile test is automatically on.

package TestAuto;

use strict;
use warnings;

use FindBin;
use lib "t/lib";
use File::Find;
use File::Basename 'basename', 'dirname';

sub import {
  if ($FindBin::Bin =~ /\/precompile$/) {
    # Set build directory
    my $test_precompile_dir = 't/precompile/lib';
    my $test_precompile_dir_re = quotemeta($test_precompile_dir);
    
    find(
      {
        wanted => sub {
          my $package_name = $File::Find::name;
          if ($package_name =~ /\.spvm$/) {
            $package_name =~ s|$test_precompile_dir_re||;
            $package_name =~ s|^/SPVM/||;
            $package_name =~ s|/|::|g;
            $package_name =~ s|\.spvm$||;
            
            SPVM::Precompile->import($package_name);
          }
        },
        no_chdir => 1,
      },
      $test_precompile_dir
    );

    $ENV{SPVM_TEST_LIB_DIR} = "$test_precompile_dir";
    $ENV{SPVM_BUILD_DIR} = 't/precompile/.spvm_build';
  }
  else {
    # Set build directory
    $ENV{SPVM_TEST_LIB_DIR} = "t/default/lib";
    $ENV{SPVM_BUILD_DIR} = 't/default/.spvm_build';
  }
  
  push @INC, $ENV{SPVM_TEST_LIB_DIR};
}

1;

=pod

=DESCRITPION

if test scritp file is in precompile directory, precompile test is automatically on.

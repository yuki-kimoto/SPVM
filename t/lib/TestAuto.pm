package TestAuto;

use strict;
use warnings;

use FindBin;
use lib "t/lib";
use File::Find;
use File::Basename 'basename', 'dirname';

require SPVM::Precompile;
require SPVM::Native;

sub import {
  if ($FindBin::Bin =~ /\/precompile$/) {
    my $test_precompile_dir = 't/lib';
    
    find(
      {
        wanted => sub {
          my $package_name = $File::Find::name;
          if ($package_name =~ /\.spvm$/) {
            $package_name =~ s|t/lib||;
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
  }
  my @inline_modules = qw(SPVM::TestCase::Extension SPVM::TestCase::Extension2);
  
  SPVM::Native->import($_) for @inline_modules;
  
  $ENV{SPVM_BUILD_DIR} = 't/spvm_build';
  $ENV{SPVM_TEST_LIB_DIR} = "t/lib";
  push @INC, $ENV{SPVM_TEST_LIB_DIR};
}

1;

=pod

=DESCRITPION

if test scritp file is in precompile directory, precompile test is automatically on.

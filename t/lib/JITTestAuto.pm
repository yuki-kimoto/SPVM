package JITTestAuto;

use strict;
use warnings;

use FindBin;
use lib "t/lib";
use File::Find;
use File::Basename 'basename', 'dirname';

require SPVM::JIT;
require SPVM::Inline;

sub import {
  if ($FindBin::Bin =~ /\/jit$/) {
    my $test_jit_dir = 't/lib';
    
    find(
      {
        wanted => sub {
          my $package_name = $File::Find::name;
          if ($package_name =~ /\.spvm$/) {
            $package_name =~ s|t/lib||;
            $package_name =~ s|^/SPVM/||;
            $package_name =~ s|/|::|g;
            $package_name =~ s|\.spvm$||;
            
            SPVM::JIT->import($package_name);
          }
        },
        no_chdir => 1,
      },
      $test_jit_dir
    );
  }
  my @inline_modules = qw(SPVM::TestCase::Extension SPVM::TestCase::Extension2);
  
  SPVM::Inline->import($_) for @inline_modules;
  
  $ENV{SPVM_BUILD_DIR} = 'spvm_build';
  $ENV{SPVM_TEST_LIB_DIR} = "t/lib";
  push @INC, $ENV{SPVM_TEST_LIB_DIR};
}

1;

=pod

=DESCRITPION

if test scritp file is in jit directory, jit test is automatically on.

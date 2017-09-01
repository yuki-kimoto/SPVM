package SPVM::Inline;

use SPVM();

use base 'SPVM';

sub import {
  my ($class, $package_name) = @_;
  
  my $package_info = $class->SUPER::import($package_name);
  
  if (defined $package_info) {
    push @SPVM::PACKAGE_INFOS_INLINE, $package_info;
  }
}

1;

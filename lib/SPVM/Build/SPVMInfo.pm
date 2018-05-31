package SPVM::Build::SPVMInfo;

use strict;
use warnings;

sub get_precompile_subs_from_package_id {
  my ($package_id) = @_;
  
  my $subs = get_subs_from_package_id($package_id);
  $subs = [grep { !$_->{have_native_desc} && !$_->{is_enum} } @$subs];
  
  return $subs;
}

sub get_native_packages {
  my $packages = SPVM::Build::SPVMInfo::get_packages();
  my $native_packages = [];
  for my $package (@$packages) {
    if ($package->{have_native_desc} && !$package->{is_interface}) {
      push @$native_packages, $package;
    }
  }
  
  return $native_packages;
}

1;

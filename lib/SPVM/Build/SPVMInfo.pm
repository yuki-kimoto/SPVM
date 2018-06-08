package SPVM::Build::SPVMInfo;

use strict;
use warnings;

sub get_precompile_subs_from_package_name {
  my ($compiler, $package_name) = @_;
  
  my $subs = get_subs_from_package_name($compiler, $package_name);
  $subs = [grep { $_->{have_compile_desc} } @$subs];
  
  return $subs;
}

sub get_native_subs_from_package_name {
  my ($compiler, $package_name) = @_;
  
  my $subs = get_subs_from_package_name($compiler, $package_name);
  $subs = [grep { $_->{have_native_desc} } @$subs];
  
  return $subs;
}

1;

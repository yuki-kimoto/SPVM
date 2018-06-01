package SPVM::Build::SPVMInfo;

use strict;
use warnings;

sub get_precompile_subs_from_package_id {
  my ($package_id) = @_;
  
  my $subs = get_subs_from_package_id($package_id);
  $subs = [grep { !$_->{have_compile_desc} && !$_->{is_enum} } @$subs];
  
  return $subs;
}

sub get_native_subs_from_package_id {
  my ($package_id) = @_;
  
  my $subs = get_subs_from_package_id($package_id);
  $subs = [grep { $_->{have_native_desc} } @$subs];
  
  return $subs;
}

1;

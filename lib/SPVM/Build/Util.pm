package SPVM::Build::Util;

use strict;
use warnings;

# SPVM::Build::tUtil is used from Makefile.PL and SPVM::Build, SPVM::Build::Precompile, SPVM::Build::Native
# so this module must be wrote as pure per script, not contain XS and don't use any other SPVM modules.

sub get_shared_lib_func_address {
  my ($shared_lib_file, $shared_lib_func_name) = @_;
  
  my $native_address;
  
  if ($shared_lib_file) {
    my $dll_libref = DynaLoader::dl_load_file($shared_lib_file);
    if ($dll_libref) {
      $native_address = DynaLoader::dl_find_symbol($dll_libref, $shared_lib_func_name);
    }
    else {
      return;
    }
  }
  else {
    return;
  }
  
  return $native_address;
}

1;


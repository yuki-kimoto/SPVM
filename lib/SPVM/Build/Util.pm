package SPVM::Build::Util;

use strict;
use warnings;
use Carp 'croak';
use Config;
use File::Basename 'dirname', 'basename';

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

sub convert_module_path_to_shared_lib_path {
  my ($module_path, $category) = @_;
  
  my $module_dir = dirname $module_path;
  my $base_name = basename $module_path;
  $base_name =~ s/\.[^.]+$//;
  
  my $shared_lib_path .= "$module_dir/$base_name.$category/$base_name.$Config{dlext}";
  
  return $shared_lib_path;
}

sub get_native_sub_names_from_module_file {
  my ($module_file) = @_;
  
  open my $module_fh, '<', $module_file
    or croak "Can't open $module_file: $!";
  
  my $src = do { local $/; <$module_fh> };
  
  my $native_sub_names = [];
  while ($src =~ /native\b(.*?)\bsub\s+([^\s]+)\s/g) {
    my $sub_name = $1;
    push @$native_sub_names, $sub_name;
  }
  
  return $native_sub_names;
}

sub get_precompile_sub_names_from_module_file {
  my ($module_file) = @_;
  
  open my $module_fh, '<', $module_file
    or croak "Can't open $module_file: $!";
  
  my $src = do { local $/; <$module_fh> };
  
  my $native_sub_names = [];
  while ($src =~ /compile\b(.*?)\bsub\s+([^\s]+)\s/g) {
    my $sub_name = $1;
    push @$native_sub_names, $sub_name;
  }
  
  return $native_sub_names;
}

sub convert_module_name_to_shared_lib_rel_dir {
  my ($module_name, $category) = @_;
  
  my $module_base_name = $module_name;
  $module_base_name =~ s/^.+:://;
  
  my $shared_lib_rel_dir = $module_name;
  $shared_lib_rel_dir =~ s/::/\//g;
  $shared_lib_rel_dir = "$shared_lib_rel_dir.$category";
  
  return $shared_lib_rel_dir;
}


1;


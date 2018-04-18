package SPVM::Build;

use strict;
use warnings;

use Config;
use Carp 'confess';

use SPVM::Build::ExtUtil;
use SPVM::Build::JIT;
use SPVM::Build::Inline;

sub compile_spvm {
  
  # Compile SPVM source code
  my $compile_success = compile();
  
  if ($compile_success) {
    # Build opcode
    build_opcode();
    
    # Build run-time
    build_runtime();
    
    # Bind native subroutines
    bind_native_subs();
    
    # Build SPVM subroutines
    build_spvm_subs();
  }
  
  return $compile_success;
}

my $package_name_h = {};

sub build_spvm_subs {
  my $sub_names = get_sub_names();
  
  for my $abs_name (@$sub_names) {
    # Define SPVM subroutine
    no strict 'refs';
    
    # Declare package
    my ($package_name, $sub_name) = $abs_name =~ /^(?:(.+)::)(.+)/;
    $package_name = "SPVM::$package_name";
    unless ($package_name_h->{$package_name}) {
      
      my $code = "package $package_name; our \@ISA = ('SPVM::Perl::Object::Package');";
      eval $code;
      
      if (my $error = $@) {
        confess $error;
      }
      $package_name_h->{$package_name} = 1;
    }
    
    # Declare subroutine
    *{"SPVM::$abs_name"} = sub {
      
      my $return_value;
      eval { $return_value = SPVM::call_sub("$abs_name", @_) };
      my $error = $@;
      if ($error) {
        confess $error;
      }
      $return_value;
    };
  }
}

sub get_shared_lib_file {
  my $package_name = shift;
  
  my $package_name2 = $package_name;
  $package_name2 =~ s/SPVM:://;
  my @package_name_parts = split(/::/, $package_name2);
  my $package_load_path = get_package_load_path($package_name2);
  my $dll_file = $package_load_path;
  $dll_file =~ s/\.[^.]+$//;
  $dll_file .= ".native/$package_name_parts[-1].$Config{dlext}";
  
  return $dll_file;
}

sub bind_native_subs {
  my $native_func_names = get_native_sub_names();
  for my $native_func_name (@$native_func_names) {
    my $native_func_name_spvm = "SPVM::$native_func_name";
    my $native_address = get_sub_native_address($native_func_name_spvm);
    unless ($native_address) {
      my $native_func_name_c = $native_func_name_spvm;
      $native_func_name_c =~ s/:/_/g;
      confess "Can't find native address of $native_func_name_spvm(). Native function name must be $native_func_name_c";
    }
    bind_native_sub($native_func_name, $native_address);
  }
}

sub get_sub_native_address {
  my $sub_abs_name = shift;
  
  my $package_name;
  my $sub_name;
  if ($sub_abs_name =~ /^(?:(.+)::)(.+)$/) {
    $package_name = $1;
    $sub_name = $2;
  }
  
  my $dll_package_name = $package_name;
  my $shared_lib_file = get_shared_lib_file($dll_package_name);
  
  my $shared_lib_func_name = $sub_abs_name;
  $shared_lib_func_name =~ s/:/_/g;
  my $native_address = search_shared_lib_func_address($shared_lib_file, $shared_lib_func_name);
  
  # Try inline compile
  unless ($native_address) {
    
    my $module_name = $package_name;
    $module_name =~ s/^SPVM:://;
    my $module_dir = get_package_load_path($module_name);
    $module_dir =~ s/\.spvm$//;
    
    my $module_name_slash = $package_name;
    $module_name_slash =~ s/::/\//g;
    
    $module_dir =~ s/$module_name_slash$//;
    $module_dir =~ s/\/$//;
    
    my $shared_lib_file;
    
    my $tmp_dir = File::Temp->newdir;
    eval {
      $shared_lib_file = $SPVM::SPVM_BUILD->build_shared_lib(
        module_dir => $module_dir,
        module_name => "SPVM::$module_name",
        object_dir => $tmp_dir->dirname,
        inline => 1
      );
    };
    
    if ($@) {
      return;
    }
    else {
      $native_address = search_shared_lib_func_address($shared_lib_file, $shared_lib_func_name);
    }
  }
  
  return $native_address;
}

sub search_shared_lib_func_address {
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

package SPVM::Builder::Runtime;

use strict;
use warnings;
use Carp 'confess';
use File::Path 'mkpath';
use File::Basename 'dirname', 'basename';

sub bind_methods {
  my ($class, $runtime, $dynamic_lib_file, $class_name, $category) = @_;

  my $method_names = SPVM::Builder::Runtime->get_method_names($runtime, $class_name, $category);
  if (@$method_names) {
    my $method_infos = [];
    for my $method_name (@$method_names) {
      my $method_info = {};
      $method_info->{class_name} = $class_name;
      $method_info->{method_name} = $method_name;
      push @$method_infos, $method_info;
    }
    
    # Add anon class sub names if precompile
    if ($category eq 'precompile') {
      my $anon_class_names = SPVM::Builder::Runtime->get_anon_class_names($runtime, $class_name);
      for my $anon_class_name (@$anon_class_names) {
        my $method_info = {};
        $method_info->{class_name} = $anon_class_name;
        $method_info->{method_name} = "";
        push @$method_infos, $method_info;
      }
    }
    
    for my $method_info (@$method_infos) {
      my $class_name = $method_info->{class_name};
      my $method_name = $method_info->{method_name};

      my $cfunc_address;
      if ($dynamic_lib_file) {
        my $dynamic_lib_libref = DynaLoader::dl_load_file($dynamic_lib_file);
        
        if ($dynamic_lib_libref) {

          my $cfunc_name = SPVM::Builder::Util::create_cfunc_name($class_name, $method_name, $category);
          $cfunc_address = DynaLoader::dl_find_symbol($dynamic_lib_libref, $cfunc_name);
          unless ($cfunc_address) {
            my $dl_error = DynaLoader::dl_error();
            my $error = <<"EOS";
Can't find native function \"$cfunc_name\" corresponding to ${class_name}->$method_name in \"$dynamic_lib_file\"

You must write the following definition.
--------------------------------------------------
#include <spvm_native.h>

int32_t $cfunc_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  return 0;
}
--------------------------------------------------

$dl_error
EOS
            confess $error;
          }
        }
        else {
          my $dl_error = DynaLoader::dl_error();
          confess "The DynaLoader::dl_load_file function failed:Can't load the \"$dynamic_lib_file\" file for the $category methods in the $class_name class: $dl_error";
        }
      }
      else {
        confess "DLL file is not specified";
      }
      
      if ($category eq 'native') {
        SPVM::Builder::Runtime->set_native_method_address($runtime, $class_name, $method_name, $cfunc_address);
      }
      elsif ($category eq 'precompile') {
        SPVM::Builder::Runtime->set_precompile_method_address($runtime, $class_name, $method_name, $cfunc_address);
      }
    }
  }
}

sub get_dynamic_lib_file_dist {
  my ($class, $runtime, $class_name, $category) = @_;

  my $module_module_file = SPVM::Builder::Runtime->get_module_file($runtime, $class_name);
  
  my $dynamic_lib_file = SPVM::Builder::Util::convert_module_file_to_dynamic_lib_file($module_module_file, $category);
  
  return $dynamic_lib_file;
}

sub create_dl_func_list {
  my ($class, $runtime, $class_name, $options) = @_;
  
  $options ||= {};
  
  my $category = $options->{category};
  
  # dl_func_list
  # This option is needed Windows DLL file
  my $dl_func_list = [];
  my $method_names = SPVM::Builder::Runtime->get_method_names($runtime, $class_name, $category);
  for my $method_name (@$method_names) {
    my $cfunc_name = SPVM::Builder::Util::create_cfunc_name($class_name, $method_name, $category);
    push @$dl_func_list, $cfunc_name;
  }
  
  if ($category eq 'precompile') {
    # Add anon class sub names to dl_func_list
    my $anon_class_names = SPVM::Builder::Runtime->get_anon_class_names($runtime, $class_name);
    
    for my $anon_class_name (@$anon_class_names) {
      my $anon_method_cfunc_name = SPVM::Builder::Util::create_cfunc_name($anon_class_name, "", $category);
      push @$dl_func_list, $anon_method_cfunc_name;
    }
  }

  # This is bad hack to suppress boot strap function error.
  unless (@$dl_func_list) {
    push @$dl_func_list, '';
  }

  return $dl_func_list;
}

1;

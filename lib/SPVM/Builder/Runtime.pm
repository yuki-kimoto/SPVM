package SPVM::Builder::Runtime;

use strict;
use warnings;

sub load_dynamic_libs {
  my ($self) = @_;

  my $class_names = SPVM::Builder::Runtime->get_class_names($self);

  # Set addresses of native methods
  for my $class_name (@$class_names) {
    my $category = 'native';
    my $method_names = SPVM::Builder::Runtime->get_method_names($self, $class_name, $category);
    
    if (@$method_names) {
      # Build classs - Compile C source codes and link them to SPVM precompile method
      # Shared library which is already installed in distribution directory
      my $module_file = SPVM::Builder::Runtime->get_module_file($self, $class_name);
      my $dynamic_lib_file = SPVM::Builder::Util::get_dynamic_lib_file_dist($module_file, $category);
      
      if (-f $dynamic_lib_file) {
        my $method_addresses = SPVM::Builder::Util::get_method_addresses($dynamic_lib_file, $class_name, $method_names, [], $category);
        
        for my $method_name (sort keys %$method_addresses) {
          my $cfunc_address = $method_addresses->{$method_name};
          SPVM::Builder::Runtime->set_native_method_address($self, $class_name, $method_name, $cfunc_address);
        }
      }
    }
  }
}

1;

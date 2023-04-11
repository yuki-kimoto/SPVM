package SPVM::Builder::Runtime;

use strict;
use warnings;

sub load_dynamic_libs {
  my ($self) = @_;

  my $class_names = $self->get_class_names;

  # Set addresses of native methods
  for my $class_name (@$class_names) {
    my $category = 'native';
    my $method_names = $self->get_method_names($class_name, $category);
    
    if (@$method_names) {
      # Build classs - Compile C source codes and link them to SPVM precompile method
      # Shared library which is already installed in distribution directory
      my $class_file = $self->get_class_file($class_name);
      my $dynamic_lib_file = SPVM::Builder::Util::get_dynamic_lib_file_dist($class_file, $category);
      
      if (-f $dynamic_lib_file) {
        my $method_addresses = SPVM::Builder::Util::get_method_addresses($dynamic_lib_file, $class_name, $method_names, [], $category);
        
        for my $method_name (sort keys %$method_addresses) {
          my $cfunc_address = $method_addresses->{$method_name};
          $self->set_native_method_address($class_name, $method_name, $cfunc_address);
        }
      }
    }
  }
}

1;

=head1 Name

SPVM::Builder::Runtime - SPVM Builder Runtime

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

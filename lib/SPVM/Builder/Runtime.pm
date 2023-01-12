package SPVM::Builder::Runtime;

use strict;
use warnings;

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

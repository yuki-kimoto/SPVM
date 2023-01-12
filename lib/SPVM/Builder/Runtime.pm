package SPVM::Builder::Runtime;

use strict;
use warnings;
use Carp 'confess';
use File::Path 'mkpath';
use File::Basename 'dirname', 'basename';

sub get_dynamic_lib_file_dist {
  my ($class, $runtime, $class_name, $category) = @_;

  my $module_module_file = SPVM::Builder::Runtime->get_module_file($runtime, $class_name);
  
  my $dynamic_lib_file = SPVM::Builder::Util::convert_module_file_to_dynamic_lib_file($module_module_file, $category);
  
  return $dynamic_lib_file;
}

sub build_precompile_class_source_file {
  my ($class, $runtime, $class_name, $options) = @_;
  
  # Force
  my $force = $options->{force};
  
  # Output - Precompile C source file
  my $output_dir = $options->{output_dir};
  my $source_rel_file = SPVM::Builder::Util::convert_class_name_to_rel_file($class_name, 'precompile.c');
  my $source_file = "$output_dir/$source_rel_file";
  
  # Check if generating is needed
  my $module_file = SPVM::Builder::Runtime->get_module_file($runtime, $class_name);
  my $spvm_module_dir = $INC{'SPVM/Builder.pm'};
  $spvm_module_dir =~ s/\.pm$//;
  $spvm_module_dir .= '/src';
  my $spvm_precompile_soruce_file = "$spvm_module_dir/spvm_precompile.c";
  unless (-f $spvm_precompile_soruce_file) {
    confess "Can't find $spvm_precompile_soruce_file";
  }
  my $need_generate = SPVM::Builder::Util::need_generate({
    force => $force,
    output_file => $source_file,
    input_files => [$module_file, $spvm_precompile_soruce_file],
  });
  
  # Generate precompile C source file
  if ($need_generate) {
    my $precompile_source = SPVM::Builder::Runtime->build_precompile_class_source($runtime, $class_name);
    mkpath dirname $source_file;
    open my $fh, '>', $source_file
      or die "Can't create $source_file";
    print $fh $precompile_source;
    close $fh;
  }
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

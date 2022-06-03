package SPVM::Builder::Generator::Dist;

use strict;
use warnings;
use Carp 'confess';

use File::Copy 'copy', 'move';
use File::Path 'mkpath';
use File::Find 'find';
use File::Basename 'dirname', 'basename';
use SPVM::Builder::Util;
use Getopt::Long 'GetOptions';

# Fields
sub force {
  my $self = shift;
  if (@_) {
    $self->{force} = $_[0];
    return $self;
  }
  else {
    return $self->{force};
  }
}

sub class_name {
  my $self = shift;
  if (@_) {
    $self->{class_name} = $_[0];
    return $self;
  }
  else {
    return $self->{class_name};
  }
}

sub output_dir {
  my $self = shift;
  if (@_) {
    $self->{output_dir} = $_[0];
    return $self;
  }
  else {
    return $self->{output_dir};
  }
}

sub native {
  my $self = shift;
  if (@_) {
    $self->{native} = $_[0];
    return $self;
  }
  else {
    return $self->{native};
  }
}

sub precompile {
  my $self = shift;
  if (@_) {
    $self->{precompile} = $_[0];
    return $self;
  }
  else {
    return $self->{precompile};
  }
}

sub new {
  my $class = shift;
  
  my $self = {@_};
  
  bless $self, $class;
  
  unless (defined $self->output_dir) {
    my $default_output_dir = 'lib';
    $self->output_dir($default_output_dir);
  }
  
  unless (defined $self->class_name) {
    confess "Class name must be specified";
  }
  
  my $native = $self->native;
  if (defined $native && !($native eq 'c' || $native eq 'c++')) {
    confess "Can't support native \"$native\"";
  }
  
  return $self;
}

sub generate_lib {
  my ($self) = @_;
  
  my $force = $self->force;
  
  my $class_name = $self->class_name;
  
  my $native = $self->native;
  
  my $class_name_rel_file = $class_name;
  $class_name_rel_file =~ s|::|/|g;
  
  my $native_module_ext;
  if (defined $native) {
    if ($native eq 'c') {
      $native_module_ext = 'c';
    }
    elsif ($native eq 'c++') {
      $native_module_ext = 'cpp';
    }
  }
  
  # Create lib directory
  unless (defined $self->output_dir) {
    my $default_output_dir = 'lib/SPVM';
    $self->output_dir($default_output_dir);
  }
  my $output_dir = $self->output_dir;
  
  my $spvm_print_hello_world;
  my $spvm_print_hello_world_method;
  if (defined $native) {
    $spvm_print_hello_world = '&print_hello_world();';
    $spvm_print_hello_world_method = 'native static method print_hello_world : void ();';
  }
  else {
    $spvm_print_hello_world = 'print "Hello World!\n;"';
    $spvm_print_hello_world_method = '';
  }
  
  # Create the module file
  my $module_file = "$output_dir/$class_name_rel_file.spvm";
  if ($force || !-f $module_file) {
    mkpath dirname $module_file;
    
    my $module_content = <<"EOS";
class $class_name {
  static method main : int (\$start_file : string, \$args : string[]) {
    
    $spvm_print_hello_world
    
    return 0;
  }
  
  $spvm_print_hello_world_method
}
EOS
    SPVM::Builder::Util::spurt_binary($module_file, $module_content);
  }
  else {
    warn "Module file \"$module_file\" already exists";
  }
  
  # Create the config file
  my $config_file = "$output_dir/$class_name_rel_file.config";
  if (defined $native ) {
    if ($force || !-f $config_file) {
      mkpath dirname $config_file;
      
      my $new_method;
      if ($native eq 'c') {
        $new_method = 'new_gnu99';
      }
      elsif ($native eq 'c++') {
        $new_method = 'new_cpp';
      }
      
      my $add_source_files = '';
      
      my $config_content = <<"EOS";
use strict;
use warnings;
use SPVM::Builder::Config;

my \$config = SPVM::Builder::Config->$new_method;

$add_source_files;

\$config;
EOS
      SPVM::Builder::Util::spurt_binary($config_file, $config_content);
    }
    else {
      warn "Config file \"$config_file\" already exists";
    }
  }
  
  # Create the native module file
  my $extern_c_start;
  my $extern_c_end;
  if (defined $native) {
    if ($native eq 'c++') {
      $extern_c_start = qq(extern "C" {);
      $extern_c_end = "}";
    }
    else {
      $extern_c_start = '';
      $extern_c_end = '';
    }
    
    my $include_native_header;
    my $print_hello_world;
    $include_native_header = '';
    $print_hello_world = 'printf("Hello World!\n");';
    
    my $native_module_file = "$output_dir/$class_name_rel_file.$native_module_ext";
    
    if ($native) {
      if ($force || !-f $native_module_file) {
        mkpath dirname $native_module_file;
        
        my $native_class_name = $class_name;
        $native_class_name =~ s/::/__/g;
        
        my $native_module_content = <<"EOS";
#include "spvm_native.h"
$include_native_header

$extern_c_start

int32_t SPVM__${native_class_name}__print_hello_world(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  $print_hello_world
  
  return 0;
}

$extern_c_end
EOS
        
        SPVM::Builder::Util::spurt_binary($native_module_file, $native_module_content);
      }
      else {
        warn "Native module file \"$native_module_file\" already exists";
      }
    }
  }
}

1;

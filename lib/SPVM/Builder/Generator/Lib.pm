package SPVM::Builder::Generator::Lib;

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

sub script_file {
  my $self = shift;
  if (@_) {
    $self->{script_file} = $_[0];
    return $self;
  }
  else {
    return $self->{script_file};
  }
}

sub native_lib_name {
  my $self = shift;
  if (@_) {
    $self->{native_lib_name} = $_[0];
    return $self;
  }
  else {
    return $self->{native_lib_name};
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

sub module_dir {
  my $self = shift;
  if (@_) {
    $self->{module_dir} = $_[0];
    return $self;
  }
  else {
    return $self->{module_dir};
  }
}

sub language {
  my $self = shift;
  if (@_) {
    $self->{language} = $_[0];
    return $self;
  }
  else {
    return $self->{language};
  }
}

sub new {
  my $class = shift;
  
  my $self = {@_};
  
  bless $self, $class;
  
  unless (defined $self->module_dir) {
    my $default_module_dir = 'lib';
    $self->module_dir($default_module_dir);
  }
  
  unless (defined $self->class_name) {
    confess "Class name must be specified";
  }
  
  my $language = $self->language;
  if (defined $language) {
    unless ($language eq 'c' || $language eq 'c++') {
      confess "Can't support language \"$language\"";
    }
  }
  else {
    $self->language('c');
  }
  
  return $self;
}

sub generate_lib {
  my ($self) = @_;
  
  my $force = $self->force;
  
  my $class_name = $self->class_name;
  
  my $language = $self->language;
  
  my $class_name_rel_file = $class_name;
  $class_name_rel_file =~ s|::|/|g;
  
  my $native_lib_name = $self->native_lib_name;

  my $native_module_ext;
  if ($language eq 'c') {
    $native_module_ext = 'c';
  }
  elsif ($language eq 'c++') {
    $native_module_ext = 'c++';
  }
  
  # Create lib directory
  unless (defined $self->module_dir) {
    my $default_module_dir = 'lib/SPVM';
    $self->module_dir($default_module_dir);
  }
  my $module_dir = $self->module_dir;
  
  # Create the module file
  my $module_file = "$module_dir/$class_name_rel_file.spvm";
  if ($force || !-f $module_file) {
    mkpath dirname $module_file;
    
    my $module_content = <<"EOS";
class $class_name {
  native static method sum : int (\$num0 : int, \$num1 : int);
}
EOS
    SPVM::Builder::Util::spurt_binary($module_file, $module_content);
  }
  else {
    warn "Module file \"$module_file\" already exists";
  }
  
  # Create the config file
  my $config_file = "$module_dir/$class_name_rel_file.config";
  if ($force || !-f $config_file) {
    mkpath dirname $config_file;
    
    my $new_method;
    if ($language eq 'c') {
      $new_method = 'new_gnu99';
    }
    elsif ($language eq 'c++') {
      $new_method = 'new_cpp';
    }
    
    my $add_source_files = '';
    if (defined $native_lib_name) {
      $add_source_files = "\$config->add_source_files('$native_lib_name.$native_module_ext');"
    }
    
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
  
  # Create the native module file
  my $extern_c_start;
  my $extern_c_end;
  if ($native_module_ext eq 'c++') {
    $extern_c_start = qq(extern "C" {);
    $extern_c_end = "}";
  }
  else {
    $extern_c_start = '';
    $extern_c_end = '';
  }
  
  my $include_native_header;
  my $calcurate_total;
  if (defined $native_lib_name) {
    $include_native_header = qq(#include "$native_lib_name.h");
    $calcurate_total = "${native_lib_name}_sum(num0, num1)";
  }
  else {
    $include_native_header = '';
    $calcurate_total = 'num0 + num1';
  }
  
  my $native_module_file = "$module_dir/$class_name_rel_file.$native_module_ext";
  if ($force || !-f $native_module_file) {
    mkpath dirname $native_module_file;
    
    my $native_class_name = $class_name;
    $native_class_name =~ s/::/__/g;
    
    my $native_module_content = <<"EOS";
#include "spvm_native.h"
$include_native_header

$extern_c_start

int32_t SPVM__${native_class_name}__sum(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  int32_t num0 = stack[0].ival;
  int32_t num1 = stack[1].ival;
  
  int32_t total = $calcurate_total;
  
  stack[0].ival = total;
  
  return 0;
}

$extern_c_end
EOS

    
    SPVM::Builder::Util::spurt_binary($native_module_file, $native_module_content);
  }
  else {
    warn "Native module file \"$native_module_file\" already exists";
  }
  
  if (defined $native_lib_name) {
    my $native_header_file = "$module_dir/$class_name_rel_file.native/include/$native_lib_name.h";
    if ($force || !-f $native_header_file) {
      mkpath dirname $native_header_file;
      
      my $native_header_content = <<"EOS";
#include <stdint.h>

int32_t ${native_lib_name}_sum(int32_t num0, int32_t num1);
EOS
      SPVM::Builder::Util::spurt_binary($native_header_file, $native_header_content);
    }
    else {
      warn "Native header file \"$native_header_file\" already exists";
    }

    my $native_source_file = "$module_dir/$class_name_rel_file.native/src/$native_lib_name.$native_module_ext";
    if ($force || !-f $native_source_file) {
      mkpath dirname $native_source_file;
      
      my $native_source_content = <<"EOS";
#include <stdint.h>
#include <${native_lib_name}.h>

int32_t ${native_lib_name}_sum(int32_t num0, int32_t num1) {
  int32_t total = num0 + num1;
  
  return total;
}
EOS
      SPVM::Builder::Util::spurt_binary($native_source_file, $native_source_content);
    }
    else {
      warn "Native source file \"$native_source_file\" already exists";
    }
  }

  # Create the script file
  my $script_file = $self->script_file;
  if ($force || !-f $script_file) {
    mkpath dirname $script_file;
    
    my $perl_module_dir = $module_dir;
    $perl_module_dir =~ s/[\\\/]SPVM$//;
    
    my $script_content = <<"EOS";
use strict;
use warnings;
use FindBin;
use lib '$perl_module_dir';
use SPVM '$class_name';

my \$total = SPVM::$class_name->sum(1, 2);

print "\$total\n";
EOS
    SPVM::Builder::Util::spurt_binary($script_file, $script_content);
  }
  else {
    warn "Module file \"$script_file\" already exists";
  }
}

1;

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

sub create_path {
  my ($self, $file_base_name) = @_;
  
  my $output_dir = $self->output_dir;
  
  my $path;
  if (defined $output_dir) {
    $path = "$output_dir/$file_base_name";
  }
  else {
    $path = $file_base_name;
  }
  
  return $path;
}

sub new {
  my $class = shift;
  
  my $self = {@_};
  
  bless $self, $class;
  
  unless (defined $self->class_name) {
    confess "Class name must be specified";
  }
  
  if (defined $self->output_dir) {
    # Remove tailing / or \
    my $output_dir = $self->output_dir;
    $output_dir =~ s|[/\\]$||;
    $self->output_dir($output_dir);
  }
  else {
    my $default_output_dir = $class_name;
    $default_output_dir =~ s/::/-/g;
    $self->output_dir($default_output_dir);
  }
  
  my $native = $self->native;
  if (defined $native && !($native eq 'c' || $native eq 'c++')) {
    confess "Can't support native \"$native\"";
  }

  return $self;
}

sub generate_spvm_module_file {
  my ($self) = @_;
  
  my $class_name = $self->class_name;

  my $spvm_module_file_base = SPVM::Builder::Util::convert_class_name_to_rel_file($class_name, 'spvm');

  # Create SPVM module file
  my $spvm_module_file = $self->create_path("lib/$spvm_module_file_base");
  mkpath dirname $spvm_module_file;
  
  my $module_content = <<"EOS";
class $class_name {

}
EOS
  SPVM::Builder::Util::spurt_binary($spvm_module_file, $spvm_module_content);
}

sub generate_perl_module_file {
  my ($self) = @_;
  
  my $class_name = $self->class_name;

  my $perl_module_file_base = SPVM::Builder::Util::convert_class_name_to_rel_file($class_name, 'pm');

  # Create SPVM module file
  my $perl_module_file = $self->create_path("lib/$perl_module_file_base");
  mkpath dirname $perl_module_file;
  
  my $module_content = <<"EOS";
package SPVM::$class_name;

our $VERSION = '0.01';

1;

=head1 NAME

SPVM::$class_name - $class_name is a SPVM module

=head1 SYNOPSYS

  use $class_name;
  
=head1 DESCRIPTION

$class_name is a SPVM module.

=head1 STATIC METHODS



=head1 INSTANCE METHODS



=head1 REPOSITORY



=head1 BUG REPORT



=head1 SUPPORT



=head1 AUTHOR



=head1 COPYRIGHT & LICENSE

Copyright YYYY-YYYY AUTHOR_NAME, all rights reserved.

This program is free software; you can redistribute it and/or modify it
under the same terms as Perl itself.

EOS
  SPVM::Builder::Util::spurt_binary($perl_module_file, $spvm_module_content);
}

sub generate_native_config_file {
  my ($self) = @_;

  my $class_name = $self->class_name;

  my $native_native_config_file_base = SPVM::Builder::Util::convert_class_name_to_rel_file($class_name, 'native_config');

  # Generate native native_config file
  my $native_config_file = $self->($native_config_file_base);
  mkpath dirname $native_config_file;
  
  my $new_method;
  if ($native eq 'c') {
    $new_method = 'new_gnu99';
  }
  elsif ($native eq 'c++') {
    $new_method = 'new_cpp';
  }
  
  my $add_source_files = '';
  
  my $native_config_content = <<"EOS";
use strict;
use warnings;
use SPVM::Builder::Config;

my \$native_config = SPVM::Builder::Config->$new_method;

$add_source_files;

\$native_config;
EOS
  SPVM::Builder::Util::spurt_binary($native_config_file, $native_config_content);
}

sub generate_native_module_file {
  my ($self) = @_;
  
  my $native_module_ext;
  if (defined $native) {
    if ($native eq 'c') {
      $native_module_ext = 'c';
    }
    elsif ($native eq 'c++') {
      $native_module_ext = 'cpp';
    }
  }
  
  # Create native module file
  my $extern_c_start;
  my $extern_c_end;
  if ($native eq 'c++') {
    $extern_c_start = qq(extern "C" {);
    $extern_c_end = "}";
  }
  else {
    $extern_c_start = '';
    $extern_c_end = '';
  }
  
  my $native_module_file = SPVM::Builder::Util::convert_class_name_to_rel_file($class_name, $native_module_ext);
  
  mkpath dirname $native_module_file;
  
  my $native_class_name = $class_name;
  $native_class_name =~ s/::/__/g;
  
  my $native_module_content = <<"EOS";
#include "spvm_native.h"

$extern_c_start

int32_t SPVM__${native_class_name}__foo(SPVM_ENV* env, SPVM_VALUE* stack) {
(void)env;
(void)stack;

return 0;
}

$extern_c_end
EOS
  
  SPVM::Builder::Util::spurt_binary($native_module_file, $native_module_content);
}

sub generate_gitignore_file {
  my ($self) = @_;
  
  # Create ,gitignoree file
  my $gitignore_file = $self->create_path('.gitignore');
  
  my $gitignore_content = <<"EOS";
blib/*
Makefile
Makefile.old
MYMETA.yml
MYMETA.json
pm_to_blib
.spvm_build
t/.spvm_build
core.*
core
SPVM-*
*.bak
*.BAK
*.tmp
EOS

  SPVM::Builder::Util::spurt_binary($gitignore_file, $gitignore_content);
}

sub generate_manifest_skip_file {
  my ($self) = @_;
  
  # Create ,manifest_skipe file
  my $manifest_skip_file = $self->create_path('MANIFEST.SKIP');
  
  my $manifest_skip_content = <<"EOS";
^blib/
^Makefile$
^Makefile\.old$
^MYMETA.yml$
^MYMETA.json$
^pm_to_blib$
^\.spvm_build$
^t/\.spvm_build$
^SPVM-
^core\.
^core#
\.bak$
\.tmp$
\.BAK$
^\.git/
EOS

  SPVM::Builder::Util::spurt_binary($manifest_skip_file, $manifest_skip_content);
}

sub generate_changes_file {
  my ($self) = @_;
  
  # Create ,manifest_skipe file
  my $manifest_skip_file = $self->create_path('Changes');
  
  my $manifest_skip_content = <<"EOS";
0.01  YYYY-MM-DD
EOS

  SPVM::Builder::Util::spurt_binary($manifest_skip_file, $manifest_skip_content);
}

sub generate_readme_markdown_file {
  my ($self) = @_;

  my $class_name = $self->class_name;

  # Create ,readme_markdowne file
  my $readme_markdown_file = $self->create_path('README.md');
  
  my $readme_markdown_content = <<"EOS";
# SPVM::$class_name

SPVM::$class_name is a SPVM module.

EOS

  SPVM::Builder::Util::spurt_binary($readme_markdown_file, $readme_markdown_content);
}

sub generate_dist {
  my ($self) = @_;
  
  my $force = $self->force;
  
  my $class_name = $self->class_name;
  
  my $native = $self->native;
  
  my $class_name_rel_file = $class_name;
  $class_name_rel_file =~ s|::|/|g;
  
  # Generate output directory
  my $output_dir = $self->output_dir;
  if ($force || !-f $spvm_module_file) {
    mkpath $output_dir;
  }
  else {
    confess "\"$output_dir\" already exists";
  }
  
  # Generate SPVM module file
  $self->generate_spvm_module_file;

  # Generate Perl module file
  $self->generate_perl_module_file;

  # Generate .gitignore file
  $self->generate_gitignore_file;

  # Generate MANIFEST.SKIP file
  $self->generate_manifest_skip_file;

  # Generate Changes file
  $self->generate_changes_file;

  # Generate README.md file
  $self->generate_readme_markdown_file;
  
  # Generate native config file
  if ($native) {
    $self->generate_native_config_file
    $self->generate_native_module_file
  }
}

1;

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

sub generate_file {
  my ($self, $rel_file, $content) = @_;
  
  # Create "t/basic.t" file
  my $file = $self->create_path($rel_file);
  mkpath dirname $file;
  SPVM::Builder::Util::spurt_binary($file, $content);
}

sub new {
  my $class = shift;
  
  my $self = {@_};
  
  bless $self, $class;

  # Class name
  my $class_name = $self->class_name;
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
  
  # Class name
  my $class_name = $self->class_name;
  
  my $spvm_module_content = <<"EOS";
class $class_name {

}
EOS
  
  # Generate file
  my $spvm_module_rel_file = SPVM::Builder::Util::convert_class_name_to_rel_file($class_name, 'spvm');
  $spvm_module_rel_file = "lib/$spvm_module_rel_file";
  $self->generate_file($spvm_module_rel_file, $spvm_module_content);
}

sub generate_perl_module_file {
  my ($self) = @_;
  
  # Class name
  my $class_name = $self->class_name;
  
  # Content
  my $perl_module_content = <<"EOS";
package SPVM::$class_name;

our \$VERSION = '0.01';

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

  # Generate file
  my $perl_module_rel_file = SPVM::Builder::Util::convert_class_name_to_rel_file($class_name, 'pm');
  $perl_module_rel_file = "lib/$perl_module_rel_file";
  $self->generate_file($perl_module_rel_file, $perl_module_content);
}

sub generate_native_config_file {
  my ($self) = @_;
  
  # Class name
  my $class_name = $self->class_name;
  
  # C or C++
  my $native = $self->native;
  my $new_method;
  if ($native eq 'c') {
    $new_method = 'new_gnu99';
  }
  elsif ($native eq 'c++') {
    $new_method = 'new_cpp';
  }
  
  # Content
  my $native_config_content = <<"EOS";
use strict;
use warnings;
use SPVM::Builder::Config;

my \$native_config = SPVM::Builder::Config->$new_method;

\$native_config;
EOS

  # Generate file
  my $native_config_rel_file = SPVM::Builder::Util::convert_class_name_to_rel_file($class_name, 'config');
  $native_config_rel_file = "lib/$native_config_rel_file";
  $self->generate_file($native_config_rel_file, $native_config_content);
}

sub generate_native_module_file {
  my ($self) = @_;

  # Class name
  my $class_name = $self->class_name;
  
  # extern C for C++
  my $native = $self->native;
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
  
  # Content
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
  
  # Generate file
  my $native_module_ext;
  if (defined $native) {
    if ($native eq 'c') {
      $native_module_ext = 'c';
    }
    elsif ($native eq 'c++') {
      $native_module_ext = 'cpp';
    }
  }
  my $native_module_rel_file = SPVM::Builder::Util::convert_class_name_to_rel_file($class_name, $native_module_ext);
  $native_module_rel_file = "lib/$native_module_rel_file";
  $self->generate_file($native_module_rel_file, $native_module_content);
}

sub generate_gitignore_file {
  my ($self) = @_;
  
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
  
  # Generate file
  my $gitignore_rel_file = '.gitignore';
  $self->generate_file($gitignore_rel_file, $gitignore_content);
}

sub generate_manifest_skip_file {
  my ($self) = @_;
  
  # Content
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

  # Generate file
  my $manifest_skip_rel_file = 'MANIFEST.SKIP';
  $self->generate_file($manifest_skip_rel_file, $manifest_skip_content);
}

sub generate_changes_file {
  my ($self) = @_;
  
  # Content
  my $changes_content = <<"EOS";
0.01  YYYY-MM-DD
EOS

  # Generate file
  my $changes_rel_file = 'Changes';
  $self->generate_file($changes_rel_file, $changes_content);
}


sub generate_readme_markdown_file {
  my ($self) = @_;
  
  # Class name
  my $class_name = $self->class_name;
  
  # Content
  my $readme_markdown_content = <<"EOS";
# SPVM::$class_name

SPVM::$class_name is a SPVM module.

EOS
  
  # Generate file
  my $readme_markdown_rel_file = 'README.md';
  $self->generate_file($readme_markdown_rel_file, $readme_markdown_content);
}

sub generate_makefile_pl_file {
  my ($self) = @_;
  
  # Class name
  my $class_name = $self->class_name;

  # Native make rule
  my $make_rule_native = $self->native ? "SPVM::Builder::Util::API::create_make_rule_native('$class_name')" : '';
  
  # Precompile make rule
  my $make_rule_precompile = $self->precompile ? "SPVM::Builder::Util::API::create_make_rule_precompile('$class_name')" : '';

  my $perl_module_rel_file = SPVM::Builder::Util::convert_class_name_to_rel_file($class_name, 'pm');
  $perl_module_rel_file = "lib/$perl_module_rel_file";
  
  # "Makefile.PL" content
  my $makefile_pl_content = <<"EOS";
use 5.008_007;
use ExtUtils::MakeMaker;
use strict;
use warnings;
use Config;
use SPVM::Builder::Util::API;

WriteMakefile(
  NAME              => '$class_name',
  VERSION_FROM      => '$perl_module_rel_file',
  PREREQ_PM         => {}, # e.g., Module::Name => 1.1
  LICENSE           => 'perl_5',
  (\$] >= 5.005 ?     ## Add these new keywords supported since 5.005
    (ABSTRACT_FROM  => '$perl_module_rel_file',
     AUTHOR         => 'USER_NAME<USER_MAIL>') : ()),
  test => {TESTS => 't/*.t'},
  clean => {FILES => ['.spvm_build', 't/.spvm_build', 'SPVM-*']},
  META_MERGE => {
    'meta-spec' => { version => 2 },
    resources => {
      repository => {
        type => 'git',
        url  => '',
        web  => '',
      },
    },
  },
  # SPVM::Builder::Util::API is needed for Makefile.PL
  CONFIGURE_REQUIRES => {
    'SPVM'              => '$SPVM::VERSION',
  },
);

sub MY::postamble {

  my \$make_rule = '';
  
  $make_rule_native;
  $make_rule_precompile;
  
  return \$make_rule;
}

1;
EOS

  # Generate file
  my $makefile_pl_rel_file = 'Makefile.PL';
  $self->generate_file($makefile_pl_rel_file, $makefile_pl_content);
}

sub generate_basic_test {
  my ($self) = @_;
  
  # Class name
  my $class_name = $self->class_name;
  
  # Content
  my $basic_test_content = <<"EOS";
use strict;
use warnings;
use Test::More;

use SPVM '$class_name';

done_testing;
EOS
  
  # Generate file
  my $basic_test_rel_file = 't/basic.t';
  $self->generate_file($basic_test_rel_file, $basic_test_content);
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
  if ($force || !-e $output_dir) {
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

  # Generate Makefile.PL file
  $self->generate_makefile_pl_file;
  
  if ($native) {
    # Generate native config file
    $self->generate_native_config_file;

    # Generate native module file
    $self->generate_native_module_file;
  }
}

1;

=head1 NAME

SPVM::Builder::Generator::Dist - Generating SPVM Distrubution

=head2 SYNOPSYS

  my $dist = SPVM::Builder::Generator::Dist->new(
    class_name => 'Math',
  );
  
  $dist->generate_dist;

=head2 DESCRIPTION

C<SPVM::Builder::Generator::Dist> generates a SPVM Distrubution.

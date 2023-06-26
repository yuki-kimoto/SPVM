package SPVM::Dist;

use strict;
use warnings;
use Carp 'confess';

use File::Copy 'copy', 'move';
use File::Path 'mkpath';
use File::Find 'find';
use File::Basename 'dirname', 'basename';
use SPVM::Builder::Util;
use Getopt::Long 'GetOptions';
use Time::Piece();

# Field metods
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

sub module_name {
  my $self = shift;
  if (@_) {
    $self->{module_name} = $_[0];
    return $self;
  }
  else {
    return $self->{module_name};
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

sub resource {
  my $self = shift;
  if (@_) {
    $self->{resource} = $_[0];
    return $self;
  }
  else {
    return $self->{resource};
  }
}

sub interface {
  my $self = shift;
  if (@_) {
    $self->{interface} = $_[0];
    return $self;
  }
  else {
    return $self->{interface};
  }
}

sub only_lib_files {
  my $self = shift;
  if (@_) {
    $self->{only_lib_files} = $_[0];
    return $self;
  }
  else {
    return $self->{only_lib_files};
  }
}

sub no_pm_file {
  my $self = shift;
  if (@_) {
    $self->{no_pm_file} = $_[0];
    return $self;
  }
  else {
    return $self->{no_pm_file};
  }
}

sub lib_dir {
  my $self = shift;
  if (@_) {
    $self->{lib_dir} = $_[0];
    return $self;
  }
  else {
    return $self->{lib_dir};
  }
}

sub user_name {
  my $self = shift;
  if (@_) {
    $self->{user_name} = $_[0];
    return $self;
  }
  else {
    return $self->{user_name};
  }
}

sub user_email {
  my $self = shift;
  if (@_) {
    $self->{user_email} = $_[0];
    return $self;
  }
  else {
    return $self->{user_email};
  }
}

# Class methods
sub new {
  my $class = shift;
  
  my $self = {@_};
  
  bless $self, $class;

  # Module name
  my $module_name = $self->module_name;
  unless (defined $self->module_name) {
    confess "A module name must be specified";
  }
  
  if (defined $self->output_dir) {
    # Remove tailing / or \
    my $output_dir = $self->output_dir;
    $output_dir =~ s|[/\\]$||;
    $self->output_dir($output_dir);
  }
  else {
    my $default_output_dir = "SPVM::$module_name";
    $default_output_dir =~ s/::/-/g;
    $self->output_dir($default_output_dir);
  }
  
  my $native = $self->native;
  if (defined $native && !($native eq 'c' || $native eq 'c++')) {
    confess "Can't support native \"$native\"";
  }
  
  my $resource = $self->resource;
  if ($resource && !defined $native) {
    $self->native('c');
  }
  
  return $self;
}

# Instance methods
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

sub create_lib_rel_file {
  my ($self, $file_base_name) = @_;
  
  my $lib_rel_file;
  
  my $only_lib_files = $self->only_lib_files;
  if ($only_lib_files) {
    $lib_rel_file = $file_base_name;
  }
  else {
    $lib_rel_file = "lib/$file_base_name";
  }
  
  return $lib_rel_file;
}

sub generate_file {
  my ($self, $rel_file, $content) = @_;
  
  my $file = $self->create_path($rel_file);
  my $dir = dirname $file;
  
  $self->generate_dir($dir);
  
  my $force = $self->force;
  if ($force || !-f $file) {
    print "  [write]$file\n";
    SPVM::Builder::Util::spurt_binary($file, $content);
  }
  else {
    print "  [exists]$file\n";
  }
}

sub generate_dir {
  my ($self, $rel_dir, $content) = @_;
  
  my @created = mkpath $rel_dir;
  if (@created) {
    print "  [mkdir]$rel_dir\n";
  }
}

sub generate_spvm_module_file {
  my ($self) = @_;
  
  # Module name
  my $module_name = $self->module_name;
  
  # User name
  my $user_name = $self->user_name;
  unless (defined $user_name) {
    $user_name = '[--user-name]'
  }
  
  # Year
  my $year = $self->_year;

  my $interface = $self->interface;
  
  my $attributes = "";
  if ($interface) {
    $attributes = ": interface_t ";
  }

  my $version_decl = 'version "0.001";';
  
  my $only_lib_files = $self->only_lib_files;
  if ($only_lib_files) {
    $version_decl = '';
  }
  
  my $spvm_module_content = <<"EOS";
# Copyright (c) $year $user_name
# MIT License

class $module_name ${attributes}{
  $version_decl
}
EOS
  
  # Generate file
  my $spvm_module_rel_file = SPVM::Builder::Util::convert_module_name_to_rel_file($module_name, 'spvm');
  my $lib_dir = $self->lib_dir;
  $spvm_module_rel_file = $self->create_lib_rel_file($spvm_module_rel_file);
  $self->generate_file($spvm_module_rel_file, $spvm_module_content);
}

sub generate_perl_module_file {
  my ($self) = @_;
  
  # Module name
  my $module_name = $self->module_name;
  
  # Year
  my $year = $self->_year;
  
  # User name
  my $user_name = $self->user_name;
  unless (defined $user_name) {
    $user_name = '[--user-name]'
  }
  
  # User email
  my $user_email = $self->user_email;
  unless (defined $user_email) {
    $user_email = '[--user-email]'
  }

  my $interface = $self->interface;
  my $resource = $self->resource;
  
  # Description
  my $description;
  my $main_doc;
  if ($interface) {
    $description = "The $module_name interface of L<SPVM> has interface methods for someting.";
    $main_doc  = <<"EOS";
=head1 Usage

  interface $module_name;

=head1 Interface Methods



EOS
  }
  elsif ($resource) {
    $description = "The $module_name resource of L<SPVM> is a L<resouce|SPVM::Document::Resource> for someting.";
    
    my $native = $self->native;
    my $new_method;
    if ($native eq 'c') {
      $new_method = 'new_c99';
    }
    elsif ($native eq 'c++') {
      $new_method = 'new_cpp';
    }
    
    my $native_module_ext;
    if (defined $native) {
      if ($native eq 'c') {
        $native_module_ext = 'c';
      }
      elsif ($native eq 'c++') {
        $native_module_ext = 'cpp';
      }
    }
    
    # extern C for C++
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
    
    $main_doc  = <<"EOS";
=head1 Usage

MyClass.config:
  
  my \$config = SPVM::Builder::Config->$new_method(file => __FILE__);
  
  \$config->use_resource('$module_name');
  
  \$config;

MyClass.$native_module_ext:

  #include "spvm_native.h"
  #include "foo.h"
  
  $extern_c_start
  
  int32_t SPVM__MyClass__test(SPVM_ENV* env, SPVM_VALUE* stack) {
    
    // Use functions in foo.h
    
    return 0;
  }
  
  $extern_c_end
  
=head1 Original Product



=head1 Original Product Version



=head1 Language



=head1 Language Specification



=head1 Required Libraries



=head1 Required Linker Flags



=head1 Required Resources



=head1 Header Files



=head1 Source Files



=head1 Compiler Flags



=head1 How to Create Resource



=head2 Donwload



=head2 Extracting Source Files



=head2 Extracting Header Files



EOS
  }
  else {
    $description = "The $module_name class of L<SPVM> has methods for someting.";
    $main_doc  = <<"EOS";
=head1 Usage

  use $module_name;

=head1 Fields



=head1 Class Methods



=head1 Instance Methods



EOS
  }
  
  my $version_decl = 'our $VERSION = "0.001";';
  
  my $only_lib_files = $self->only_lib_files;
  if ($only_lib_files) {
    $version_decl = '';
  }
  
  # Content
  my $perl_module_content = "";
  $perl_module_content = <<"EOS";
package SPVM::$module_name;

$version_decl

1;

=head1 Name

SPVM::$module_name - Short Description

=head1 Description

$description

$main_doc
=head1 Repository



=head1 Author

$user_name C<$user_email>

=head1 Copyright & License

Copyright (c) $year $user_name

MIT License

EOS

  # Generate file
  my $perl_module_rel_file = SPVM::Builder::Util::convert_module_name_to_rel_file($module_name, 'pm');
  $perl_module_rel_file =  $self->create_lib_rel_file($perl_module_rel_file);
  $self->generate_file($perl_module_rel_file, $perl_module_content);
}

sub generate_native_config_file {
  my ($self) = @_;
  
  # Module name
  my $module_name = $self->module_name;
  
  # C or C++
  my $native = $self->native;
  my $new_method;
  if ($native eq 'c') {
    $new_method = 'new_c99';
  }
  elsif ($native eq 'c++') {
    $new_method = 'new_cpp';
  }
  
  # User name
  my $user_name = $self->user_name;
  unless (defined $user_name) {
    $user_name = '[--user-name]'
  }
  
  # Year
  my $year = $self->_year;
  
  # Content
  my $native_config_content = <<"EOS";
# Copyright (c) $year $user_name
# MIT License

use strict;
use warnings;
use SPVM::Builder::Config;

my \$config = SPVM::Builder::Config->$new_method(file => __FILE__);

\$config;
EOS

  # Generate file
  my $native_config_rel_file = SPVM::Builder::Util::convert_module_name_to_rel_file($module_name, 'config');
  $native_config_rel_file =  $self->create_lib_rel_file($native_config_rel_file);
  $self->generate_file($native_config_rel_file, $native_config_content);
}

sub generate_native_module_file {
  my ($self) = @_;

  # Module name
  my $module_name = $self->module_name;
  
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
  
  # Content
  my $native_module_name = $module_name;
  $native_module_name =~ s/::/__/g;
  my $native_module_file = $module_name;
  $native_module_file =~ s/::/\//g;
  $native_module_file .= ".$native_module_ext";

  # User name
  my $user_name = $self->user_name;
  unless (defined $user_name) {
    $user_name = '[--user-name]'
  }
  
  # Year
  my $year = $self->_year;
  
  my $native_module_content = <<"EOS";
// Copyright (c) $year $user_name
// MIT License

#include "spvm_native.h"

$extern_c_start

static const char* FILE_NAME = "$native_module_file";

int32_t SPVM__${native_module_name}__foo(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  return 0;
}

$extern_c_end
EOS
  
  my $native_module_rel_file = SPVM::Builder::Util::convert_module_name_to_rel_file($module_name, $native_module_ext);
  $native_module_rel_file =  $self->create_lib_rel_file($native_module_rel_file);
  $self->generate_file($native_module_rel_file, $native_module_content);
}

sub generate_gitkeep_file_for_native_module_include_dir {
  my ($self) = @_;

  # Module name
  my $module_name = $self->module_name;
  
  # Generate file
  my $gitkeep_rel_file_for_native_module_include_dir = SPVM::Builder::Util::convert_module_name_to_rel_file($module_name, 'native');
  $gitkeep_rel_file_for_native_module_include_dir .= '/include/.gitkeep';
  $gitkeep_rel_file_for_native_module_include_dir =  $self->create_lib_rel_file($gitkeep_rel_file_for_native_module_include_dir);
  $self->generate_file($gitkeep_rel_file_for_native_module_include_dir, '');
}

sub generate_gitkeep_file_for_native_module_src_dir {
  my ($self) = @_;

  # Module name
  my $module_name = $self->module_name;
  
  # Generate file
  my $gitkeep_rel_file_for_native_module_include_dir = SPVM::Builder::Util::convert_module_name_to_rel_file($module_name, 'native');
  $gitkeep_rel_file_for_native_module_include_dir .= '/src/.gitkeep';
  $gitkeep_rel_file_for_native_module_include_dir =  $self->create_lib_rel_file($gitkeep_rel_file_for_native_module_include_dir);
  $self->generate_file($gitkeep_rel_file_for_native_module_include_dir, '');
}

sub generate_gitignore_file {
  my ($self) = @_;
  
  my $gitignore_content = <<'EOS';
/blib/*
/Makefile
/Makefile.old
/MYMETA.yml
/MYMETA.json
/pm_to_blib
/SPVM-*
.spvm_build
core.*
core
*.bak
*.BAK
*.tmp
*.o
*.bs
EOS
  
  # Generate file
  my $gitignore_rel_file = '.gitignore';
  $self->generate_file($gitignore_rel_file, $gitignore_content);
}

sub generate_manifest_skip_file {
  my ($self) = @_;
  
  # Content
  my $manifest_skip_content = <<'EOS';
(^|\/)blib/
(^|\/)Makefile$
(^|\/)Makefile.old$
(^|\/)MYMETA.yml$
(^|\/)MYMETA.json$
(^|\/)pm_to_blib$
(^|\/).spvm_build/
(^|\/)t/.spvm_build/
(^|\/)SPVM-
(^|\/)core\.
(^|\/)core$
(^|\/)\.git/
\.bak$
\.tmp$
\.tmp/
\.BAK$
\.o$
\.bs$
EOS

  # Generate file
  my $manifest_skip_rel_file = 'MANIFEST.SKIP';
  $self->generate_file($manifest_skip_rel_file, $manifest_skip_content);
}

sub generate_changes_file {
  my ($self) = @_;

  # Year
  my $today_tp = Time::Piece::localtime;
  my $today = $today_tp->strftime('%Y-%m-%d');
  
  # Content
  my $changes_content = <<"EOS";
0.01 $today
  [Changes]
    * First release.
  
EOS

  # Generate file
  my $changes_rel_file = 'Changes';
  $self->generate_file($changes_rel_file, $changes_content);
}


sub generate_readme_markdown_file {
  my ($self) = @_;
  
  # Module name
  my $module_name = $self->module_name;
  
  # Content
  my $readme_markdown_content = <<"EOS";
# SPVM::$module_name

<a href="https://metacpan.org/pod/SPVM::$module_name">SPVM::$module_name</a>

EOS
  
  # Generate file
  my $readme_markdown_rel_file = 'README.md';
  $self->generate_file($readme_markdown_rel_file, $readme_markdown_content);
}

sub generate_makefile_pl_file {
  my ($self) = @_;
  
  # Module name
  my $module_name = $self->module_name;
  
  # Resource
  my $resource = $self->resource;
  
  # Native make rule
  my $make_rule_native = $self->native && !$resource ? "\$make_rule .= SPVM::Builder::Util::API::create_make_rule_native('$module_name');" : '';
  
  # Precompile make rule
  my $make_rule_precompile = $self->precompile && !$resource ? "\$make_rule .= SPVM::Builder::Util::API::create_make_rule_precompile('$module_name');" : '';

  my $perl_module_rel_file = SPVM::Builder::Util::convert_module_name_to_rel_file($module_name, 'pm');
  $perl_module_rel_file =  $self->create_lib_rel_file($perl_module_rel_file);

  my $spvm_module_rel_file = SPVM::Builder::Util::convert_module_name_to_rel_file($module_name, 'spvm');
  $spvm_module_rel_file =  $self->create_lib_rel_file($spvm_module_rel_file);
  
  # User name
  my $user_name = $self->user_name;
  unless (defined $user_name) {
    $user_name = '[--user-name]'
  }
  
  # User email
  my $user_email = $self->user_email;
  unless (defined $user_email) {
    $user_email = '[--user-email]'
  }
  
  # "Makefile.PL" content
  my $makefile_pl_content = <<"EOS";
use 5.008_007;
use ExtUtils::MakeMaker;
use strict;
use warnings;
use Config;
use Getopt::Long 'GetOptions';

GetOptions(
  'meta' => \\my \$meta,
  'no-build-spvm-modules' => \\my \$no_build_spvm_modules,
);

if (\$meta) {
  \$no_build_spvm_modules = 1;
}

unless (\$meta) {
  # Do something such as environment check.
}

my \%configure_and_runtime_requires = ('SPVM' => '$SPVM::VERSION');
WriteMakefile(
  NAME => 'SPVM::$module_name',
  VERSION_FROM => '$perl_module_rel_file',
  LICENSE => 'mit',
  (\$] >= 5.005 ?
    (ABSTRACT_FROM => '$perl_module_rel_file',
     AUTHOR => '$user_name<$user_email>') : ()),
  test => {TESTS => 't/*.t t/*/*.t t/*/*/*.t'},
  clean => {FILES => ['.spvm_build', 't/.spvm_build']},
  META_MERGE => {
    'meta-spec' => { version => 2 },
    resources => {
      repository => {
        type => 'git',
        url  => '',
        web  => '',
      },
    },
    no_index => {
      directory => [],
    }
  },
  NORECURS => 1,
  CONFIGURE_REQUIRES => {
    \%configure_and_runtime_requires,
  },
  PREREQ_PM         => {
    \%configure_and_runtime_requires,
  },
  TEST_REQUIRES => {
    
  },
);

sub MY::postamble {

  my \$make_rule = '';
  
  unless (\$no_build_spvm_modules) {
    require SPVM::Builder::Util::API;
    
    $make_rule_native
    $make_rule_precompile
  }
  
  return \$make_rule;
}

1;
EOS

  # Generate file
  my $makefile_pl_rel_file = 'Makefile.PL';
  $self->generate_file($makefile_pl_rel_file, $makefile_pl_content);
}

sub generate_basic_test_file {
  my ($self) = @_;
  
  # Module name
  my $module_name = $self->module_name;
  
  my $spvm_module_rel_file = SPVM::Builder::Util::convert_module_name_to_rel_file($module_name, 'spvm');
  $spvm_module_rel_file =  $self->create_lib_rel_file($spvm_module_rel_file);
  
  # Content
  my $basic_test_content = <<"EOS";
use Test::More;

use strict;
use warnings;
use FindBin;
use lib "\$FindBin::Bin/lib";
BEGIN { \$ENV{SPVM_BUILD_DIR} = "\$FindBin::Bin/.spvm_build"; }

use SPVM 'TestCase::$module_name';

use SPVM '$module_name';
use SPVM::$module_name;
use SPVM 'Fn';

ok(SPVM::TestCase::$module_name->test);

# Version
{
  my \$version_string = SPVM::Fn->get_version_string("$module_name");
  is(\$SPVM::${module_name}::VERSION, \$version_string);
}

done_testing;
EOS
  
  # Generate file
  my $basic_test_rel_file = 't/basic.t';
  $self->generate_file($basic_test_rel_file, $basic_test_content);
}

sub generate_license_file {
  my ($self) = @_;
  
  # Module name
  my $module_name = $self->module_name;
  
  # User name
  my $user_name = $self->user_name;
  unless (defined $user_name) {
    $user_name = '[--user-name]'
  }
  
  # Year
  my $year = $self->_year;
  
  # Content
  my $license_content = <<"EOS";
MIT License

Copyright (c) $year $user_name

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
EOS
  
  # Generate file
  my $license_rel_file = 'LICENSE';
  $self->generate_file($license_rel_file, $license_content);
}

sub generate_basic_test_spvm_module_file {
  my ($self) = @_;
  
  # Module name
  my $module_name = $self->module_name;
  
  # Resource
  my $resource = $self->resource;
  
  # Content
  my $basic_test_spvm_module_content;
  
  if ($resource) {
    $basic_test_spvm_module_content = <<"EOS";
class TestCase::$module_name {
  native static method test : int ();
}
EOS
  }
  else {
    $basic_test_spvm_module_content = <<"EOS";
class TestCase::$module_name {
  use $module_name;
  static method test : int () {
    
    return 1;
  }
}
EOS
  }
  
  # Generate file
  my $basic_test_spvm_module_rel_file = SPVM::Builder::Util::convert_module_name_to_rel_file("TestCase::$module_name", 'spvm');
  $basic_test_spvm_module_rel_file = "t/lib/$basic_test_spvm_module_rel_file";
  $self->generate_file($basic_test_spvm_module_rel_file, $basic_test_spvm_module_content);
}

sub generate_basic_test_native_config_file {
  my ($self) = @_;
  
  # Module name
  my $module_name = $self->module_name;
  
  # Resource
  my $resource = $self->resource;

  # C or C++
  my $native = $self->native;
  my $new_method;
  if ($native eq 'c') {
    $new_method = 'new_c99';
  }
  elsif ($native eq 'c++') {
    $new_method = 'new_cpp';
  }
  
  # Content
  my $basic_test_native_config_content = <<"EOS";
use strict;
use warnings;

my \$config = SPVM::Builder::Config->$new_method(file => __FILE__);

\$config->use_resource('$module_name');

\$config;
EOS
  
  # Generate file
  my $basic_test_native_config_rel_file = SPVM::Builder::Util::convert_module_name_to_rel_file("TestCase::$module_name", 'config');
  $basic_test_native_config_rel_file = "t/lib/$basic_test_native_config_rel_file";
  $self->generate_file($basic_test_native_config_rel_file, $basic_test_native_config_content);
}

sub generate_basic_test_native_module_file {
  my ($self) = @_;
  
  # Module name
  my $module_name = $self->module_name;
  
  # Resource
  my $resource = $self->resource;

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
  my $native_module_name = $module_name;
  $native_module_name =~ s/::/__/g;
  my $basic_test_native_module_content = <<"EOS";
#include "spvm_native.h"

$extern_c_start

int32_t SPVM__TestCase__${native_module_name}__test(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].ival = 1;
  
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
  my $basic_test_native_module_rel_file = SPVM::Builder::Util::convert_module_name_to_rel_file("TestCase::$module_name", $native_module_ext);
  $basic_test_native_module_rel_file = "t/lib/$basic_test_native_module_rel_file";
  $self->generate_file($basic_test_native_module_rel_file, $basic_test_native_module_content);
}

sub generate_dist {
  my ($self) = @_;
  
  my $module_name = $self->module_name;
  
  unless (length $module_name) {
    confess "The module name must be specified";
  }
  
  if ($module_name =~ /-/) {
    confess "The module name cannnot contain \"-\"";
  }
  
  my $native = $self->native;
  my $interface = $self->interface;
  my $resource = $self->resource;
  
  if ($interface && $resource) {
    die "The --interface option and the --resource option cannot be specified at the same time"
  }
  
  my $module_name_rel_file = $module_name;
  $module_name_rel_file =~ s|::|/|g;
  
  # Generate output directory
  my $output_dir = $self->output_dir;
  $self->generate_dir($output_dir);
  
  # Generate SPVM module file
  $self->generate_spvm_module_file;
  
  # Generate Perl module file
  my $no_pm_file = $self->no_pm_file;
  unless ($no_pm_file) {
    $self->generate_perl_module_file;
  }
  
  if ($native) {
    # Generate native config file
    $self->generate_native_config_file;
    
    # Generate native module file
    unless ($resource) {
      $self->generate_native_module_file;
    }
    
    # Generate ".gitkeep" file for native module include directory
    $self->generate_gitkeep_file_for_native_module_include_dir;
    
    # Generate ".gitkeep" file for native module src directory
    $self->generate_gitkeep_file_for_native_module_src_dir;
  }
  
  my $only_lib_files = $self->only_lib_files;
  unless ($only_lib_files) {
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
    
    # Generate t/basic.t file
    $self->generate_basic_test_file;

    # Generate basic test SPVM module file
    $self->generate_basic_test_spvm_module_file;

    # Generate license file
    $self->generate_license_file;
    
    if ($resource) {
      # Generate basic test native module file
      $self->generate_basic_test_native_module_file;

      # Generate basic test native config file
      $self->generate_basic_test_native_config_file;
    }
  }
}

sub _year {
  my ($self) = @_;
  
  # Year
  my $today_tp = Time::Piece::localtime;
  my $year = $today_tp->year;
  
  return $year;
}

1;

=head1 Name

SPVM::Dist - Generating SPVM Distrubution

=head2 Description

The SPVM::Dist class has methods to generate a SPVM Distrubution.

=head2 Usage

  my $dist = SPVM::Dist->new(
    module_name => 'Math',
  );
  
  $dist->generate_dist;

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

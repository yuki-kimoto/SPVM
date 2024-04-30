package SPVM::Builder::Config;

use strict;
use warnings;
use Config;
use Carp 'confess';
use File::Basename 'dirname', 'fileparse';
use SPVM::Builder::Util;
use SPVM::Builder::LibInfo;
use SPVM::Builder::Resource;

# Fields
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

sub file {
  my $self = shift;
  if (@_) {
    $self->{file} = $_[0];
    return $self;
  }
  else {
    return $self->{file};
  }
}

sub file_optional {
  my $self = shift;
  if (@_) {
    $self->{file_optional} = $_[0];
    return $self;
  }
  else {
    return $self->{file_optional};
  }
}

sub ext {
  my $self = shift;
  if (@_) {
    $self->{ext} = $_[0];
    return $self;
  }
  else {
    return $self->{ext};
  }
}

sub quiet {
  my $self = shift;
  if (@_) {
    $self->{quiet} = $_[0];
    return $self;
  }
  else {
    return $self->{quiet};
  }
}

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

sub cc {
  my $self = shift;
  if (@_) {
    $self->{cc} = $_[0];
    return $self;
  }
  else {
    return $self->{cc};
  }
}

sub ccflags {
  my $self = shift;
  if (@_) {
    $self->{ccflags} = $_[0];
    return $self;
  }
  else {
    return $self->{ccflags};
  }
}

sub dynamic_lib_ccflags {
  my $self = shift;
  if (@_) {
    $self->{dynamic_lib_ccflags} = $_[0];
    return $self;
  }
  else {
    return $self->{dynamic_lib_ccflags};
  }
}

sub thread_ccflags {
  my $self = shift;
  if (@_) {
    $self->{thread_ccflags} = $_[0];
    return $self;
  }
  else {
    return $self->{thread_ccflags};
  }
}

sub mingw_ccflags {
  my $self = shift;
  if (@_) {
    $self->{mingw_ccflags} = $_[0];
    return $self;
  }
  else {
    return $self->{mingw_ccflags};
  }
}

sub std {
  my $self = shift;
  if (@_) {
    $self->{std} = $_[0];
    return $self;
  }
  else {
    return $self->{std};
  }
}

sub optimize {
  my $self = shift;
  if (@_) {
    $self->{optimize} = $_[0];
    return $self;
  }
  else {
    return $self->{optimize};
  }
}

sub include_dirs {
  my $self = shift;
  if (@_) {
    $self->{include_dirs} = $_[0];
    return $self;
  }
  else {
    return $self->{include_dirs};
  }
}

sub spvm_core_include_dir {
  my $self = shift;
  if (@_) {
    $self->{spvm_core_include_dir} = $_[0];
    return $self;
  }
  else {
    return $self->{spvm_core_include_dir};
  }
}

sub native_include_dir {
  my $self = shift;
  if (@_) {
    $self->{native_include_dir} = $_[0];
    return $self;
  }
  else {
    return $self->{native_include_dir};
  }
}

sub native_src_dir {
  my $self = shift;
  if (@_) {
    $self->{native_src_dir} = $_[0];
    return $self;
  }
  else {
    return $self->{native_src_dir};
  }
}

sub source_files {
  my $self = shift;
  if (@_) {
    $self->{source_files} = $_[0];
    return $self;
  }
  else {
    return $self->{source_files};
  }
}

sub after_create_compile_info_cbs {
  my $self = shift;
  if (@_) {
    $self->{after_create_compile_info_cbs} = $_[0];
    return $self;
  }
  else {
    return $self->{after_create_compile_info_cbs};
  }
}

sub before_compile_cbs {
  my $self = shift;
  if (@_) {
    $self->{before_compile_cbs} = $_[0];
    return $self;
  }
  else {
    return $self->{before_compile_cbs};
  }
}

sub ld {
  my $self = shift;
  if (@_) {
    $self->{ld} = $_[0];
    return $self;
  }
  else {
    return $self->{ld};
  }
}

sub ldflags {
  my $self = shift;
  if (@_) {
    $self->{ldflags} = $_[0];
    return $self;
  }
  else {
    return $self->{ldflags};
  }
}

sub dynamic_lib_ldflags {
  my $self = shift;
  if (@_) {
    $self->{dynamic_lib_ldflags} = $_[0];
    return $self;
  }
  else {
    return $self->{dynamic_lib_ldflags};
  }
}

sub thread_ldflags {
  my $self = shift;
  if (@_) {
    $self->{thread_ldflags} = $_[0];
    return $self;
  }
  else {
    return $self->{thread_ldflags};
  }
}

sub static_lib_ldflag {
  my $self = shift;
  if (@_) {
    $self->{static_lib_ldflag} = $_[0];
    return $self;
  }
  else {
    return $self->{static_lib_ldflag};
  }
}

sub ld_optimize {
  my $self = shift;
  if (@_) {
    $self->{ld_optimize} = $_[0];
    return $self;
  }
  else {
    return $self->{ld_optimize};
  }
}

sub lib_dirs {
  my $self = shift;
  if (@_) {
    $self->{lib_dirs} = $_[0];
    return $self;
  }
  else {
    return $self->{lib_dirs};
  }
}

sub libs {
  my $self = shift;
  if (@_) {
    $self->{libs} = $_[0];
    return $self;
  }
  else {
    return $self->{libs};
  }
}

sub after_create_link_info_cbs {
  my $self = shift;
  if (@_) {
    $self->{after_create_link_info_cbs} = $_[0];
    return $self;
  }
  else {
    return $self->{after_create_link_info_cbs};
  }
}

sub before_link_cbs {
  my $self = shift;
  if (@_) {
    $self->{before_link_cbs} = $_[0];
    return $self;
  }
  else {
    return $self->{before_link_cbs};
  }
}

sub output_type {
  my $self = shift;
  if (@_) {
    $self->{output_type} = $_[0];
    return $self;
  }
  else {
    return $self->{output_type};
  }
}

sub resource_loader_config {
  my $self = shift;
  if (@_) {
    $self->{resource_loader_config} = $_[0];
    return $self;
  }
  else {
    return $self->{resource_loader_config};
  }
}

sub category {
  my $self = shift;
  if (@_) {
    $self->{category} = $_[0];
    return $self;
  }
  else {
    return $self->{category};
  }
}

sub config_exe {
  my $self = shift;
  if (@_) {
    $self->{config_exe} = $_[0];
    return $self;
  }
  else {
    return $self->{config_exe};
  }
}

sub is_jit {
  my $self = shift;
  if (@_) {
    $self->{is_jit} = $_[0];
    return $self;
  }
  else {
    return $self->{is_jit};
  }
}

sub cc_input_dir {
  my $self = shift;
  if (@_) {
    $self->{cc_input_dir} = $_[0];
    return $self;
  }
  else {
    return $self->{cc_input_dir};
  }
}

sub cc_output_dir {
  my $self = shift;
  if (@_) {
    $self->{cc_output_dir} = $_[0];
    return $self;
  }
  else {
    return $self->{cc_output_dir};
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

sub output_file {
  my $self = shift;
  if (@_) {
    $self->{output_file} = $_[0];
    return $self;
  }
  else {
    return $self->{output_file};
  }
}

sub used_as_resource {
  my $self = shift;
  if (@_) {
    $self->{used_as_resource} = $_[0];
    return $self;
  }
  else {
    return $self->{used_as_resource};
  }
}

# Class Methods
sub new {
  my $class = shift;
  
  my $self = {@_};
  
  bless $self, ref $class || $class;
  
  my $file_optional = $self->file_optional;
  
  my $file = $self->file;
  if (!$file_optional && !defined $file) {
    confess("The \"file\" field must be defined");
  }
  
  # cc
  unless (defined $self->{cc}) {
    $self->cc($Config{cc});
  }
  
  # ccflags
  unless (defined $self->{ccflags}) {
    $self->ccflags([]);
  }
  
  # dynamic_lib_ccflags
  unless (defined $self->{dynamic_lib_ccflags}) {
    if ($^O eq 'MSWin32') {
      $self->dynamic_lib_ccflags([]);
    }
    else {
      $self->dynamic_lib_ccflags(['-fPIC']);
    }
  }
  
  # thread_ccflags
  unless (defined $self->{thread_ccflags}) {
    if ($^O eq 'MSWin32') {
      $self->thread_ccflags([]);
    }
    else {
      $self->thread_ccflags(['-pthread']);
    }
  }
  
  # mingw_ccflags
  unless (defined $self->{mingw_ccflags}) {
    if ($^O eq 'MSWin32') {
      $self->mingw_ccflags(['-D__USE_MINGW_ANSI_STDIO']);
    }
    else {
      $self->mingw_ccflags([]);
    }
  }
  
  # optimize
  unless (defined $self->{optimize}) {
    $self->optimize('-O3');
  }
  
  # include_dirs
  unless (defined $self->{include_dirs}) {
    $self->include_dirs([]);
  }
  
  # spvm_core_include_dir
  unless (defined $self->spvm_core_include_dir) {
    my $builder_dir = SPVM::Builder::Util::get_builder_dir();
    my $spvm_core_include_dir = "$builder_dir/include";
    
    $self->spvm_core_include_dir($spvm_core_include_dir);
  }
  
  # native_include_dir
  unless (defined $self->native_include_dir) {
    if (defined $file) {
      my $native_dir = $self->_remove_ext_from_config_file($file);
      $native_dir .= '.native';
      my $native_include_dir = "$native_dir/include";
      
      $self->native_include_dir($native_include_dir);
    }
  }
  
  # native_src_dir
  unless (defined $self->native_src_dir) {
    if (defined $file) {
      my $native_dir = $self->_remove_ext_from_config_file($file);
      $native_dir .= '.native';
      my $native_src_dir = "$native_dir/src";
      
      $self->native_src_dir($native_src_dir);
    }
  }
  
  # source_files
  unless (defined $self->{source_files}) {
    $self->source_files([]);
  }
  
  # after_create_compile_info_cbs
  unless (defined $self->{after_create_compile_info_cbs}) {
    $self->after_create_compile_info_cbs([]);
  }
  
  # before_compile_cbs
  unless (defined $self->{before_compile_cbs}) {
    $self->before_compile_cbs([]);
  }
  
  # ld
  unless (defined $self->{ld}) {
    $self->ld($Config{ld});
  }
  
  # ldflags
  unless (defined $self->{ldflags}) {
    $self->ldflags([]);
  }
  
  # dynamic_lib_ldflags
  unless (defined $self->{dynamic_lib_ldflags}) {
    if ($^O eq 'MSWin32') {
      $self->dynamic_lib_ldflags(['-mdll', '-s']);
    }
    else {
      $self->dynamic_lib_ldflags(['-shared', '-pthread']);
    }
  }
  
  # thread_ldflags
  unless (defined $self->{thread_ldflags}) {
    if ($^O eq 'MSWin32') {
      $self->thread_ldflags([]);
    }
    else {
      $self->thread_ldflags(['-pthread']);
    }
  }
  
  # static_lib_ldflag
  unless (defined $self->{static_lib_ldflag}) {
    my $begin = '-Wl,-Bstatic';
    my $end = '-Wl,-Bdynamic';
    $self->static_lib_ldflag([$begin, $end]);
  }
  
  # ld_optimize
  unless (defined $self->{ld_optimize}) {
    $self->ld_optimize('-O2');
  }
  
  # lib_dirs
  unless (defined $self->{lib_dirs}) {
    $self->lib_dirs([]);
  }
  
  # libs
  unless (defined $self->{libs}) {
    $self->libs([]);
  }
  
  # after_create_link_info_cbs
  unless (defined $self->{after_create_link_info_cbs}) {
    $self->after_create_link_info_cbs([]);
  }
  
  # before_link_cbs
  unless (defined $self->{before_link_cbs}) {
    $self->before_link_cbs([]);
  }
  
  # output_type
  unless (defined $self->output_type) {
    $self->output_type('dynamic_lib');
  }
  
  # category
  unless (defined $self->{category}) {
    $self->category('native');
  }
  
  unless (defined $self->{_loaded_config_files}) {
    $self->{_loaded_config_files} = [];
  }
  
  # resources
  unless (defined $self->{resources}) {
    $self->{resources} = {};
  }
  
  return $self;
}

sub new_c {
  my $class = shift;
  
  my $self = $class->new(@_);
  
  $self->ext('c');
  
  return $self;
}

sub new_c99 {
  my $class = shift;
  
  my $self = $class->new_c(@_);
  
  # C99
  $self->std('c99');
  
  return $self;
}

sub new_c11 {
  my $class = shift;
  
  my $self = $class->new_c(@_);
  
  # C11
  $self->std('c11');
  
  return $self;
}

sub new_gnu99 {
  my $class = shift;
  
  my $self = $class->new_c(@_);
  
  # GNU C99
  $self->std('gnu99');
  
  return $self;
}

sub new_gnu11 {
  my $class = shift;
  
  my $self = $class->new_c(@_);
  
  # GNU C11
  $self->std('gnu11');
  
  return $self;
}


sub new_cpp {
  my $class = shift;
  
  my $self = $class->new(@_);
  
  # The compiler
  # [Memo]Free BSD don't have g++ in the environment clang++ exists.
  # [Memo]"Clang" or "clang" is assumed.
  my $config_gcc_version = $Config{gccversion};
  if ($config_gcc_version =~ /\bclang\b/i) {
    $self->cc('clang++');
    $self->ld('clang++');
  }
  else {
    $self->cc('g++');
    $self->ld('g++');
  }
  
  $self->ext('cpp');
  
  return $self;
}

sub new_cpp11 {
  my $class = shift;
  
  my $self = $class->new_cpp(@_);
  
  # C++11
  $self->std('c++11');
  
  return $self;
}

sub new_cpp14 {
  my $class = shift;
  
  my $self = $class->new_cpp(@_);
  
  # C++14
  $self->std('c++14');
  
  return $self;
}

sub new_cpp17 {
  my $class = shift;
  
  my $self = $class->new_cpp(@_);
  
  # C++17
  $self->std('c++17');
  
  return $self;
}

# Instance Methods
sub add_ccflag {
  my ($self, @ccflags) = @_;
  
  push @{$self->{ccflags}}, @ccflags;
}

sub add_include_dir {
  my ($self, @include_dirs) = @_;
  
  push @{$self->{include_dirs}}, @include_dirs;
}

sub add_ldflag {
  my ($self, @ldflags) = @_;
  
  push @{$self->{ldflags}}, @ldflags;
}

sub add_lib_dir {
  my ($self, @lib_dirs) = @_;
  
  push @{$self->{lib_dirs}}, @lib_dirs;
}

sub add_lib {
  my ($self, @libs) = @_;
  
  push @{$self->{libs}}, @libs;
}

sub add_lib_abs {
  my ($self, @libs) = @_;
  
  $self->_add_lib_info({is_abs => 1}, @libs);
}

sub add_static_lib_abs {
  my ($self, @libs) = @_;
  
  $self->_add_lib_info({is_static => 1, is_abs => 1}, @libs);
}

sub add_static_lib {
  my ($self, @libs) = @_;
  
  $self->_add_lib_info({is_static => 1}, @libs);
}

sub _add_lib_info {
  my ($self, $options, @libs) = @_;
  
  my @lib_infos;
  for my $lib (@libs) {
    my $lib_info;
    if (ref $lib eq 'SPVM::Builder::LibInfo') {
      $lib_info = $lib;
    }
    else {
      my $lib_name = $lib;
      $lib_info = SPVM::Builder::LibInfo->new(config => $self, name => $lib_name);
    }
    
    $lib_info->is_static($options->{is_static});
    
    $lib_info->is_abs($options->{is_abs});
    
    push @lib_infos, $lib_info;
  }
  
  $self->add_lib(@lib_infos);
}

sub add_source_file {
  my ($self, @source_files) = @_;
  
  push @{$self->{source_files}}, @source_files;
}

sub add_after_create_compile_info_cb {
  my ($self, @after_create_compile_info_cbs) = @_;
  
  push @{$self->{after_create_compile_info_cbs}}, @after_create_compile_info_cbs;
}

sub add_before_compile_cb {
  my ($self, @before_compile_cbs) = @_;
  
  push @{$self->{before_compile_cbs}}, @before_compile_cbs;
}

sub add_after_create_link_info_cb {
  my ($self, @after_create_link_info_cbs) = @_;
  
  push @{$self->{after_create_link_info_cbs}}, @after_create_link_info_cbs;
}

sub add_before_link_cb {
  my ($self, @before_link_cbs) = @_;
  
  push @{$self->{before_link_cbs}}, @before_link_cbs;
}

sub load_config {
  my ($self, $config_file, $argv) = @_;
  
  unless (-f $config_file) {
    confess("The config file \"$config_file\" must exist");
  }
  
  unless (defined $argv) {
    confess("The arguments \$argv must be defined.");
  }
  
  my $config;
  {
    local @ARGV = @$argv;
    $config = do File::Spec->rel2abs($config_file);
  }
  
  if ($@) {
    confess("The config file \"$config_file\" can't be parsed: $@");
  }
  
  unless (defined $config && $config->isa('SPVM::Builder::Config')) {
    confess("The config file must be an SPVM::Builder::Config object");
  }
  
  push @{$config->get_loaded_config_files}, $config_file;
  
  return $config;
}

sub load_mode_config {
  my ($self, $config_file, $mode, $argv) = @_;
  
  my $mode_config_file = $self->_remove_ext_from_config_file($config_file);
  if (defined $mode) {
    $mode_config_file .= ".$mode";
  }
  $mode_config_file .= ".config";
  
  unless (-f $mode_config_file) {
    confess("Can't find the config file \"$mode_config_file\"");
  }
  
  my $config = $self->load_config($mode_config_file, $argv);
  
  return $config;
}

sub load_base_config {
  my ($self, $config_file, $args) = @_;
  
  my $config = $self->load_mode_config($config_file, undef, $args);

  return $config;
}

sub get_loaded_config_files {
  my $self = shift;
  
  return $self->{_loaded_config_files};
}

sub use_resource {
  my ($self, @args) = @_;
  
  my $first_arg;
  unless (@args % 2 == 0) {
    $first_arg = shift @args;
  }
  
  my $resource;
  if (ref $first_arg) {
    $resource = $first_arg;
  }
  else {
    my $class_name = $first_arg;
    my %args = @args;
    if (exists $args{class_name}) {
      $class_name = delete $args{class_name};
    }
    $resource = SPVM::Builder::Resource->new(class_name => $class_name, %args);
  }
  
  my $resource_class_name = $resource->class_name;
  my $resource_mode = $resource->mode;
  my $resource_argv = $resource->argv;
  
  my $ext = defined $resource_mode ? "$resource_mode.config" : 'config';
  my $config_file_base = SPVM::Builder::Util::convert_class_name_to_rel_file($resource_class_name, $ext);
  
  my $config_file = SPVM::Builder::Util::search_config_file($resource_class_name, $resource_mode);
  
  unless (defined $config_file) {
    my $config_rel_file = SPVM::Builder::Util::convert_class_name_to_rel_file($resource_class_name, 'config');
    
    confess("A config file \"$config_rel_file\" is not found in (@INC)");
  }
  
  my $config = $self->load_config($config_file, $resource_argv);
  $config->file($config_file);
  
  $resource->config($config);
  
  my $index = keys %{$self->{resources}};
  
  $self->{resources}->{$resource_class_name} = {resource => $resource, index => $index};
  
  return $resource;
}

sub no_compile_resource {
  my $self = shift;
  if (@_) {
    $self->{no_compile_resource} = $_[0];
    return $self;
  }
  else {
    return $self->{no_compile_resource};
  }
}

sub get_resource {
  my ($self, $resource_class_name) = @_;
  
  unless (defined $self->{resources}{$resource_class_name}) {
    return;
  }
  
  my $resource = $self->{resources}{$resource_class_name}{resource};
  
  return $resource;
}

sub get_resource_names {
  my ($self) = @_;
  
  my @resource_names = sort { $self->{resources}{$a}{index} <=> $self->{resources}{$b}{index} } keys %{$self->{resources}};
  
  return \@resource_names;
}

sub clone {
  my ($self) = @_;
  
  my $clone = bless {}, ref $self;
  
  for my $name (keys %$self) {
    my $value = $self->{$name};
    
    if (ref $value eq 'ARRAY') {
      $clone->{$name} = [@$value];
    }
    elsif (ref $value eq 'HASH') {
      $clone->{$name} = {%$value};
    }
    else {
      $clone->{$name} = $value;
    }
  }
  
  return $clone;
}

sub _remove_ext_from_config_file {
  my ($self, $config_file) = @_;
  
  my ($config_base_name, $config_dir) = fileparse $config_file;
  
  $config_base_name =~ s/(\.[^\.]+)?\.config$//;
  
  my $config_file_without_ext = "$config_dir$config_base_name";
  
  return $config_file_without_ext;
}

1;

=head1 Name

SPVM::Builder::Config - Config for Compiling and Linking Native Classes

=head1 Description

The SPVM::Builder::Config class has methods to get and set config for compiling and linking L<native classes|SPVM::Document::NativeClass>.

=head1 Usage

  use SPVM::Builder::Config;
  
  # Create a config
  my $config = SPVM::Builder::Config->new(file => __FILE__);
  
  # GNU C99
  my $config = SPVM::Builder::Config->new_gnu99(file => __FILE__);
  
  # C99
  my $config = SPVM::Builder::Config->new_c99(file => __FILE__);
  
  # C++
  my $config = SPVM::Builder::Config->new_cpp(file => __FILE__);
  
  # C++11
  my $config = SPVM::Builder::Config->new_cpp11(file => __FILE__);
  
  # C++17
  my $config = SPVM::Builder::Config->new_cpp17(file => __FILE__);
  
  # Optimize
  $config->optimize("-O2");
  
  # Optimize with debug mode
  $config->optimize("-O0 -g");
  
  # Add ccflags
  $config->add_ccflag("-DFOO");
  
  # Add source files
  $config->add_source_file("foo.c", "bar.c", "baz/baz.c");
  
  # Add libraries
  $config->add_lib("gdi32", "d2d1", "Dwrite");
  
  # Add ldflags
  $config->add_ldflag("-pthread");
  
  # Use resource
  $config->use_resource("Resource::MyResource");
  
=head1 Fields

=head2 ext

  my $ext = $config->ext;
  $config->ext($ext);

Gets and sets the C<ext> field, the extension of a native class.

Examples:

  # MyClass.c
  $config->ext('c');
  
  # MyClass.cpp
  $config->ext('cpp');
  
  # MyClass.cc
  $config->ext('cc');
  
  # MyClass.cu
  $config->ext('cu');
  
  # MyClass.m
  $config->ext('m');

=head2 cc

  my $cc = $config->cc;
  $config->cc($cc);

Gets and sets the C<cc> field, a compiler name.

Examples:
  
  # gcc
  $config->cc('gcc');
  
  # g++ for C++
  $config->cc('g++');
  
  # nvcc for CUDA/GUP
  $config->cc('nvcc');
  
  # cc that compiled this Perl
  use Config;
  $config->cc($Config{cc});

=head2 include_dirs

  my $include_dirs = $config->include_dirs;
  $config->include_dirs($include_dirs);

Gets and sets the C<include_dirs> field, an array reference containing header file search directories.

The values of this field are converted to the C<-I> options when the arguments of the compiler L</"cc"> are created.

  # -I /path1 -I /path2
  $config->include_dirs(['/path1', '/path2']);

=head2 spvm_core_include_dir

  my $spvm_core_include_dir = $config->spvm_core_include_dir;
  $config->spvm_core_include_dir($spvm_core_include_dir);

Gets and sets the C<spvm_core_include_dir> field, an SPVM core header file search directory.

The value of this field is converted to the C<-I> option when the arguments of the compiler L</"cc"> are created.

This field is automatically set and users nomally do not change it.

=head2 native_include_dir

  my $native_include_dir = $config->native_include_dir;
  $config->native_include_dir($native_include_dir);

Gets and sets the C<native_include_dir> field, a L<native header file|SPVM::Document::NativeClass/"Native Header Files"> search directory.

The value of this field is converted to the C<-I> option when the arguments of the compiler L</"cc"> are created.

This field is automatically set and users nomally do not change it.

=head2 native_src_dir

  my $native_src_dir = $config->native_src_dir;
  $config->native_src_dir($native_src_dir);

Gets and sets the C<native_src_dir> field, a L<native source file|SPVM::Document::NativeClass/"Native Source Files"> search directory.

This field is automatically set and users nomally do not change it.

=head2 ccflags

  my $ccflags = $config->ccflags;
  $config->ccflags($ccflags);

Gets and sets the C<ccflags> field, an array reference containing arugments of the compiler L</"cc">.

=head2 dynamic_lib_ccflags

  my $dynamic_lib_ccflags = $config->dynamic_lib_ccflags;
  $config->dynamic_lib_ccflags($dynamic_lib_ccflags);

Gets and sets the C<dynamic_lib_ccflags> field, an array reference containing arugments of the compiler L</"cc"> for dynamic linking.

This field is automatically set and users nomally do not change it.

=head2 thread_ccflags

  my $thread_ccflags = $config->thread_ccflags;
  $config->thread_ccflags($thread_ccflags);

Gets and sets the C<thread_ccflags> field, an array reference containing arugments of the compiler L</"cc"> for threads.

This field is automatically set and users nomally do not change it.

=head2 mingw_ccflags

  my $mingw_ccflags = $config->mingw_ccflags;
  $config->mingw_ccflags($mingw_ccflags);

Gets and sets the C<mingw_ccflags> field, an array reference containing arugments of the compiler L</"cc"> for MinGW.

This field is automatically set and users nomally do not change it.

=head2 std

  my $std = $config->std;
  $config->std($std);

Gets and sets the C<std> field, a language standard.

This field is converted to the C<-std> option when the arguments of the compiler L</"cc"> are created.

Examples:
  
  # -std=c99
  $config->std('c99');
  
  # -std=gnu99
  $config->std('gnu99');
  
  # -std=cpp
  $config->std('cpp');
  
  # -std=cpp11
  $config->std('cpp11');
  
  # -std=cpp17
  $config->std('cpp17');

=head2 optimize

  my $optimize = $config->optimize;
  $config->optimize($optimize);

Gets and sets the C<optimize> field, an arugment of the compiler L</"cc"> for optimization.

Examples:

  $config->optimize('-O3');
  $config->optimize('-O2');
  $config->optimize('-g3 -O0');

=head2 source_files

  my $source_files = $config->source_files;
  $config->source_files($source_files);

Gets and sets the C<source_files> field, an array reference containing relative paths of L<native source file|SPVM::Document::NativeClass/"Native Source Files"> file from the L</"native_src_dir"> field.

=head2 after_create_compile_info_cbs

  my $after_create_compile_info_cbs = $config->after_create_compile_info_cbs;
  $config->after_create_compile_info_cbs($after_create_compile_info_cbs);

Gets and sets the C<after_create_compile_info_cbs> field, an array reference containing callbacks called just after creating compilation information.

These callbacks are executed even if no object file was generated.

The 1th argument of the callback is a L<SPVM::Builder::Config> object.

The 2th argument of the callback is a L<SPVM::Builder::CompileInfo> object.

=head2 before_compile_cbs

  my $before_compile_cbs = $config->before_compile_cbs;
  $config->before_compile_cbs($before_compile_cbs);

Gets and sets the C<before_compile_cbs> field, an array reference containing callbacks called just before the compile command L</"cc"> is executed.

These callbacks are executed only if an object file is actually generated.

The 1th argument of the callback is a L<SPVM::Builder::Config> object.

The 2th argument of the callback is a L<SPVM::Builder::CompileInfo> object.

=head2 ld

  my $ld = $config->ld;
  $config->ld($ld);

Gets and sets the C<ld> field, a linker name.

Examples:

  $config->ld('gcc');
  $config->ld('g++');

=head2 lib_dirs

  my $lib_dirs = $config->lib_dirs;
  $config->lib_dirs($lib_dirs);

Gets and sets the C<lib_dirs> field, an array reference containing library search directories.

The values of this field are converted to the C<-L> options when the arguments of the linker L</"ld"> are created.

  # -L /path1 -L /path2
  $config->lib_dirs(['/path1', '/path2']);

=head2 libs

  my $libs = $config->libs;
  $config->libs($libs);

Gets and sets the C<libs> field, an array reference containing library names such as C<z>, and C<png> or L<SPVM::Builder::LibInfo> objects.

The values of this field are converted to C<-l> options when the arguments of the linker L</"ld"> are created.

See L</"Library Path Resolution"> about resolving library paths.

Examples:

  # -l libz -l libpng
  $config->libs(['z', 'png']);

=head2 ldflags

  my ldflags = $config->ldflags;
  $config->ldflags(ldflags);

Gets and sets the C<ldflags> field, an array reference containing arguments of the linker L</"ld">.

=head2 dynamic_lib_ldflags

  my dynamic_lib_ldflags = $config->dynamic_lib_ldflags;
  $config->dynamic_lib_ldflags(dynamic_lib_ldflags);

Gets and sets the C<dynamic_lib_ldflags> field, an array reference containing arguments of the linker L</"ld"> for dynamic libraries.

This field is automatically set and users nomally do not change it.

=head2 thread_ldflags

  my thread_ldflags = $config->thread_ldflags;
  $config->thread_ldflags(thread_ldflags);

Gets and sets the C<thread_ldflags> field, an array reference containing arguments of the linker L</"ld"> for threads.

This field is automatically set and users nomally do not change it.

=head2 static_lib_ldflag

  my static_lib_ldflag = $config->static_lib_ldflag;
  $config->static_lib_ldflag(static_lib_ldflag);

Gets and sets the C<static_lib_ldflag> field, an array reference containing a pair of arguments to start statically linking and end it.

The library name added by the L</"add_static_lib"> are surrounded by the values of the pair.

  # -Wl,-Bstatic -llibfoo -Wl,-Bdynamic
  $config->static_lib_ldflag(['-Wl,-Bstatic', '-Wl,-Bdynamic']);
  $config->add_static_lib('foo');

This field is automatically set and users nomally do not change it.

This field only works correctly in Linux/Unix.

Mac does not support these options. If you want to search a static library, create a new library search directory, copy a static library to there, and add the new library search directory.
  
  # /path_for_static_lib/libz.a
  $config->add_lib_dir('/path_for_static_lib');
  $config->add_lib('z');

MinGW on Windows supports these options, but instead of linking statically, it links dynamically with absolute paths. This is usually not the intended behavior. If you want to do static linking on Windows, you need to use the C<--static> option.

=head2 ld_optimize

  my $ld_optimize = $config->ld_optimize;
  $config->ld_optimize($ld_optimize);

Gets and sets the C<ld_optimize> field, an argument of the linker L</"ld"> for optimization.

Examples:

  $config->ld_optimize("-O3");

=head2 after_create_link_info_cbs

  my $after_create_link_info_cbs = $config->after_create_link_info_cbs;
  $config->after_create_link_info_cbs($after_create_link_info_cbs);

Gets and sets the C<after_create_link_info_cbs> field, an array reference containing callbacks called just after creating link information.

These callbacks are executed even if no dynamic link library file was generated.

The 1th argument of the callback is a L<SPVM::Builder::Config> object.

The 2th argument of the callback is a L<SPVM::Builder::LinkInfo> object.

=head2 before_link_cbs

  my $before_link_cbs = $config->before_link_cbs;
  $config->before_link_cbs($before_link_cbs);

Gets and sets the C<before_link_cbs> field, an array reference containing callbacks called just before the link command L</"ld"> is executed.

These callbacks are executed only if a dynamic link library is actually generated.

The 1th argument of the callback is a L<SPVM::Builder::Config> object.

The 2th argument of the callback is a L<SPVM::Builder::LinkInfo> object.

=head2 force

  my $force = $config->force;
  $config->force($force);

Gets and sets the C<force> field.

If this field is a true value, the compilation and linking are forced.

If this field is a false value except for undef, the compilation and linking are performed following the rule of the L<dependency resolution|SPVM::Document::NativeClass/"Dependency Resolution">.

If this field is undef, this config does not specify whether the compilation and linking are perfomed.

=head2 quiet

  my $quiet = $config->quiet;
  $config->quiet($quiet);

Gets and sets the C<quiet> field.

If this field is a true value, the messages from the compiler and the linker are output to C<stderr>.

If this field is a false value except for undef, the messages from the compiler and the linker are not output.

If this field is undef, this config does specify whether the messages from the compiler and the linker are output.

=head2 class_name

  my $class_name = $config->class_name;
  $config->class_name($class_name);

Gets and sets the C<class_name> field, the name of the class configured by this config.

This field is automatically set and users nomally do not change it.

=head2 file

  my $file = $config->file;
  $config->file($file);

Gets and sets the C<file> field, the file path of this config.

This field is set by the L</"new"> method and users nomally do not change it.

=head2 file_optional

  my $file_optional = $config->file_optional;
  $config->file_optional($file_optional);

Gets and sets the C<file_optional> field.

If this field is a true value, even if the L<file|/"file"> field is not given to the L</"new"> method, the exception is not thrown.

=head2 output_type

  my $output_type = $config->output_type;
  $config->output_type($output_type);

Gets and sets the C<output_type> field, a type of the output file L</"output_file"> generated by the linker L</"ld">.

If thie field is C<dynamic_lib>, the output file is a dynamic link library.

If thie field is C<static_lib>, the output file is a static link library.

If thie field is C<exe>, the output file is an executable file.

This field is automatically set and users nomally do not change it.

=head2 no_compile_resource

  my $no_compile_resource = $config->no_compile_resource;
  $config->no_compile_resource($no_compile_resource);

Gets and sets the C<no_compile_resource> field.

If this value is a true value, no L<native source files|SPVM::Document::NativeClass/"Native Source Files"> of resources loaded by the L</"use_resource"> method are compiled.

This field is automatically set and users nomally do not change it.

=head2 resource_loader_config

  my $resource_loader_config = $config->resource_loader_config;
  $config->resource_loader_config($resource_loader_config);

Gets and sets the C<resource_loader_config> field, the config file of the class that loaded a resource by the L</"use_resource"> method.

This field is automatically set and users nomally do not change it.

=head2 category

  my $category = $config->category;
  $config->category($category);

Gets and sets the C<category> field.

If this field is C<precompile>, this config is for precompilation, 

If this field is C<native>, this config is for a native class.

This field is automatically set and users nomally do not change it.

=head2 config_exe

  my $config_exe = $config->config_exe;
  $config->config_exe($config_exe);

Gets and sets the C<config_exe> field.

If the L<spvmcc> command generates an excutable file, this field is set to a L<SPVM::Builder::Config::Exe> object.

This field is automatically set and users nomally do not change it.

=head2 cc_input_dir

  my $cc_input_dir = $config->cc_input_dir;
  $config->cc_input_dir($cc_input_dir);

Gets and sets the C<cc_input_dir> field, an input directory for the compiler L</"cc">.

This field is automatically set and users nomally do not change it.

=head2 cc_output_dir

  my $cc_output_dir = $config->cc_output_dir;
  $config->cc_output_dir($cc_output_dir);

Gets and sets the C<cc_output_dir> field, an output directory for the compiler L</"cc">.

This field is automatically set and users nomally do not change it.

=head2 output_dir

  my $output_dir = $config->output_dir;
  $config->output_dir($output_dir);

Gets and sets the C<output_dir> field, an output directory for the linker L</"ld">.

This field is automatically set and users nomally do not change it.

=head2 output_file

  my $output_file = $config->output_file;
  $config->output_file($output_file);

Gets and sets the C<output_file> field. A path of a dinamic link library or an executable file generated by the linker L</"ld">.

This field is automatically set and users nomally do not change it.

=head2 used_as_resource

  my $used_as_resource = $config->used_as_resource;
  $config->used_as_resource($used_as_resource);

Gets and sets the C<used_as_resource> field.

If this field is true, this config is used as a resource.

This field is automatically set and users nomally do not change it.

=head1 Class Methods

=head2 new

  my $config = SPVM::Builder::Config->new(%fields);

Creates a new C<SPVM::Builder::Config> object with L<fields|/"Fields">, and returns it.

The C<file> field must be defined.

Field Default Values:

=over 2

=item * L</"cc">

The C<$Config{cc}> of the L<Config> module.

=item * L</"ccflags">

  []

=item * L</"dynamic_lib_ccflags">

Windows:

  []

Other OSs:

  ["-fPIC"]

=item * L</"thread_ccflags">

Windows:

  []

Other OSs:

  ["-pthread"]

=item * L</"mingw_ccflags">

Windows:

  ['-D__USE_MINGW_ANSI_STDIO']

Other OSs:

  []

=item * L</"optimize">

  "-O3"

=item * L</"include_dirs">

  []

=item * L</"spvm_core_include_dir">

The SPVM core header file search directory.

=item * L</"native_include_dir">

The directory described in L<SPVM::Document::NativeClass/"Native Header Files">.

Examples:

  MyClass.naitve/include

=item * L</"native_src_dir">

The directory described in L<SPVM::Document::NativeClass/"Native Source Files">.

Examples:

  MyClass.naitve/src

=item * L</"source_files">

  []

=item * L</"after_create_compile_info_cbs">

  []

=item * L</"before_compile_cbs">

  []

=item * L</"ld">

The C<$Config{ld}> of the L<Config> module.

=item * L</"ldflags">

  []

=item * L</"dynamic_lib_ldflags">

Windows:

  ["-mdll", "-s"]

Other OSs:

  ["-shared"]

=item * L</"thread_ldflags">

Windows:

  []

Other OSs:

  ["-pthread"]

=item * L</"static_lib_ldflag">

  ["-Wl,-Bstatic", "-Wl,-Bdynamic"]

=item * L</"ld_optimize">

  "-O2"

=item * L</"lib_dirs">

  []

=item * L</"libs">

  []

=item * L</"after_create_link_info_cbs">

  []

=item * L</"before_link_cbs">

  []

=item * L</"output_type">

  "dynamic_lib"

=item * L</"category">

  "native"

=item * Other Fields

  undef

=back

Exceptions:

The "file" field must be defined. Otherwise, an exception is thrown.

Exampels:

  my $config = SPVM::Builder::Config->new(file => __FILE__);

=head2 new_c
  
  my $config = SPVM::Builder::Config->new_c(file => __FILE__);

Calls the L</"new"> method and sets the L</"ext"> field to C<c>, and returns the return value of the L</"new"> method.

=head2 new_gnu99
  
  my $config = SPVM::Builder::Config->new_gnu99(file => __FILE__);

Calls the L</"new_c"> method and sets the L</"std"> field to C<gnu99>, and returns the return value of the L</"new_c"> method.

=head2 new_gnu11
  
  my $config = SPVM::Builder::Config->new_gnu11(file => __FILE__);

Calls the L</"new_c"> method and sets the L</"std"> field to C<gnu11>, and returns the return value of the L</"new_c"> method.

=head2 new_c99
  
  my $config = SPVM::Builder::Config->new_c99(file => __FILE__);

Calls the L</"new_c"> method and sets the L</"std"> field to C<c99>, and returns the return value of the L</"new_c"> method.

=head2 new_c11
  
  my $config = SPVM::Builder::Config->new_c11(file => __FILE__);

Calls the L</"new_c"> method and sets the L</"std"> field to C<c11>, and returns the return value of the L</"new_c"> method.

=head2 new_cpp
  
  my $config = SPVM::Builder::Config->new_cpp(file => __FILE__);

Calls the L</"new"> method and sets the L</"ext"> field to C<cpp> and sets the L</"cc"> field to a C<C++> compiler and sets the L</"ld"> field to a C<C++> linker, and returns the return value of the L</"new"> method.

If C<$Config{gccversion}> contains C<clang>, the L</"cc"> field and the L</"ld"> field are set to C<clang++>. Otherwise, the L</"cc"> field and the L</"ld"> field are set to C<g++>.

=head2 new_cpp11
  
  my $config = SPVM::Builder::Config->new_cpp11(file => __FILE__);

Calls the L</"new_cpp"> method and sets the L</"std"> field to C<c++11>, and returns the return value of the L</"new_cpp"> method.

=head2 new_cpp14
  
  my $config = SPVM::Builder::Config->new_cpp14(file => __FILE__);

Calls the L</"new_cpp"> method and sets the L</"std"> field to C<c++14>, and returns the return value of the L</"new_cpp"> method.

=head2 new_cpp17
  
  my $config = SPVM::Builder::Config->new_cpp17(file => __FILE__);

Calls the L</"new_cpp"> method and sets the L</"std"> field to C<c++17>, and returns the return value of the L</"new_cpp"> method.

=head1 Instance Methods

=head2 add_ccflag

  $config->add_ccflag(@ccflags);

Adds @ccflags to the end of the L</"ccflags"> field.

=head2 add_ldflag

  $config->add_ldflag(@ldflags);

Adds @ldflags to the end of the L</"ldflags"> field.

=head2 add_include_dir

  $config->add_include_dir(@include_dirs);

Adds @include_dirs to the end of the L</"include_dirs"> field.

=head2 add_source_file

  $config->add_source_file(@source_files);

Adds @source_files to the end of the L</"source_files"> field.

Examples:

  $config->add_source_file('foo.c', 'bar.c');

=head2 add_after_create_compile_info_cb

  $config->add_after_create_compile_info_cb(@after_create_compile_info_cbs);

Adds @after_create_compile_info_cbs to the end of the L</"after_create_compile_info_cbs"> field.

Examples:

  $config->add_after_create_compile_info_cb(sub {
    my ($config, $compile_info) = @_;
    
    my $cc = $config->cc;
    
    # Do something
  });

=head2 add_before_compile_cb

  $config->add_before_compile_cb(@before_compile_cbs);

Adds @before_compile_cbs to the end of the L</"before_compile_cbs"> field.

Examples:

  $config->add_before_compile_cb(sub {
    my ($config, $compile_info) = @_;
    
    my $cc_command = $compile_info->to_command;
    
    # Do something
  });

=head2 add_lib_dir

  $config->add_lib_dir(@lib_dirs);

Adds @lib_dirs to the end of the L</"lib_dirs"> field.

=head2 add_lib

  $config->add_lib(@libs);

Adds @libs to the end of the L</"libs"> field.

Examples:

  $config->add_lib('gsl');
  $config->add_lib('gsl', 'z');
  $config->add_lib(
    SPVM::Builder::LibInfo->new(config => $config, name => 'gsl'),
    SPVM::Builder::LibInfo->new(config => $config, name => 'z', is_abs => 1),
  );

=head2 add_lib_abs

  $config->add_lib_abs(@libs);

Adds @libs to the end of the L</"libs"> field with the L<is_abs|SPVM::Builder::LibInfo/"is_abs"> field in the C<SPVM::Builder::LibInfo> class set to a true value.

If a value in @libs is not a L<SPVM::Builder::LibInfo> object, a L<SPVM::Builder::LibInfo> object is created from the library name.

If the library is located in your user directory, it is good to use the L</"add_lib_abs"> method instead of the L</"add_lib"> method.

This is because if the generated dynamic link library has a relative path, that path cannot be resolved when it is loaded.

For system libraries, there is no problem because the linker knows the search directory for the library.

=head2 add_static_lib

  $config->add_static_lib(@libs);

Adds @libs to the end of the L</"libs"> field with the L<is_static|SPVM::Builder::LibInfo/"is_static">  field in the C<SPVM::Builder::LibInfo> class set to a true value.

If a value in @libs is not a L<SPVM::Builder::LibInfo> object, a L<SPVM::Builder::LibInfo> object is created from the library name.

Examples:

  $config->add_static_lib('gsl');
  $config->add_static_lib('gsl', 'z');

=head2 add_static_lib_abs

  $config->add_static_lib_abs(@libs);

Adds @libs to the end of the L</"libs"> field with the L<is_static|SPVM::Builder::LibInfo/"is_static"> field and the L<is_abs|SPVM::Builder::LibInfo/"is_abs"> field  field in the C<SPVM::Builder::LibInfo> class set to a true value.

If a value in @libs is not a L<SPVM::Builder::LibInfo> object, a L<SPVM::Builder::LibInfo> object is created from the library name.

=head2 add_before_link_cb

  $config->add_before_link_cb(@before_link_cbs);

Adds @before_link_cbs to the end of the L</"before_link_cbs"> field.

Examples:

  $config->add_before_link_cb(sub {
    my ($config, $link_info) = @_;
    
    my $object_files = $link_info->object_files;
    
    # Do something
    
  });

=head2 use_resource

  my $resource = $config->use_resource($resource_name);
  my $resource = $config->use_resource($resource_name, %options);

Loads a L<resource|SPVM::Document::Resource> given a resource name and options, and returns it. The return value is a L<SPVM::Builder::Resource> object.

Options:

=over 2

=item * mode

A L<config mode|/"Config Mode"> for the resource.

=item * argv

An array reference contains L<config arguments|/"Config Arguments"> for the resource.

=back

Examples:

  $config->use_resource('Resource::MyResource');
  $config->use_resource('Resource::MyResource', mode => 'mode1', argv => ["option1_name" => "option1_value"]);

=head2 get_resource

  my $resource = $config->get_resource($resource_name);

Gets a resource loaded by the L</"use_resource"> method given a resource name, and returns it. The return value is a L<SPVM::Builder::Resource> object.

=head2 get_resource_names

  my $resource_names = $config->get_resource_names;

Returns resource names loaded by the L</"use_resource"> method.

=head2 load_config

  my $config = $config->load_config($config_file, $argv);

Loads a config file given a config file path and an array refernce containing L<config arguments|/"Config Arguments">, and returns a L<SPVM::Builder::Config> object.

The values referenced by $argv is set to the @ARGV of the config file.

Examples:

  my $config = $config->load_config(__FILE__, \@ARGV);

  my $config = $config->load_config(__FILE__, []);

=head2 load_base_config

  my $config = $config->load_base_config($config_file, $argv);

Creates the base config file path from the config file path $config_file, and calls the L</"load_config"> method given the base config file path and config arguments, and returns its return value.

A base config file is the config file that removes its mode.

  # Config file
  MyClass.mode.config
  
  # Base config file
  MyClass.config

Examples:

  my $config = SPVM::Builder::Config::Exe->load_base_config(__FILE__);

=head2 load_mode_config

  my $config = $config->load_mode_config($config_file, $mode, $argv);

Creates the L<mode config file|/"Config Mode"> path from the config file path $config_file, and calls the L</"load_config"> method given the mode config file path and config arguments, and returns its return value.

  my $config = SPVM::Builder::Config::Exe->load_mode_config(__FILE__, "production");

=head2 get_loaded_config_files

Returns the config files loaded by the L</"load_config"> method.

=head2 clone

  my $clone = $self->clone;

Clones the L<SPVM::Builder::Config> object, and returns it.

=head1 Config Mode

A config can have its mode if the config is one for an executable file generated by the L<spvmcc> command and for a L<resource|SPVM::Document::Resource>.

The mode is written in the format C<.MODE_NAME> just before the C<.config> extension of a config file.

C<MODE_NAME> must consist of C<a-zA-Z0-9_>.

Examples:
  
  # production mode
  MyClass.production.config
  
  # devel mode
  MyClass.devel.config

Use the L</"mode"> field to get the config mode.

  my $modle = $config->mode;

L<SPVM::Builder::Config#use_resource|SPVM::Builder::Config/"use_resource"> has the C<mode> option for giving a config mode.

  $config->use_resource('Resource::MyResource', mode => 'production');

The L<spvmcc> command has the C<--mode> option for giving a config mode.

  spvmcc -o myexe --mode production MyExe

=head1 Config Arguments

A config file can receive its argments.

Key-value pairs are recommended as the values of C<@ARGV> because they are normally assigned to a Perl hash.

  my %options = @ARGV;
  
  my $config = SPVM::Builder::Config->new_gnu99(file => __FILE__);

L<SPVM::Builder::Config#use_resource|SPVM::Builder::Config/"use_resource"> has the C<argv> option for giving config arguments.

  $config->use_resource('Resource::MyResource', argv => [option_name => "option_value"]);

The L<spvmcc> command has the C<--config-argv> option(released in the near future) for giving config arguments.

  spvmcc -o myexe --config-argv option_name --config-argv option_value MyExe

The L<spvmcc> command also has the C<--config-argv-option> option(released in the near future) to write config arguments easily.

  spvmcc -o myexe --config-argv-option option_name=option_value MyExe

=head1 Library Path Resolution

The following is the rule of library path resolution.

Library names are converted to L<SPVM::Builder::LibInfo> objects.

If the L<is_abs|SPVM::Builder::LibInfo/"is_abs"> field in C<SPVM::Builder::LibInfo> is a false value, the linker L</"ld"> resolves libaray paths.

If the L<is_abs|SPVM::Builder::LibInfo/"is_abs"> field in C<SPVM::Builder::LibInfo> is a true value, libaray paths are resolved by the following rules.

A library is searched in the library search directories contained in the L</"lib_dir"> field from the beginning.

If the L<is_static|SPVM::Builder::LibInfo/"is_static"> field in C<SPVM::Builder::LibInfo> is a false value, the search is performed in the order of a dynamic library, a static library.

If the L<is_static|SPVM::Builder::LibInfo/"is_static"> field in C<SPVM::Builder::LibInfo> is a true value, the search is performed only in static libraries.

If a library is found, the C<-l> option of the linker L</"ld"> is created using the found absolute path.

=head1 Examples

GNU C99:

  my $config = SPVM::Builder::Config->new_gnu99(file => __FILE__);

C99:

  my $config = SPVM::Builder::Config->new_c99(file => __FILE__);

C11:

  my $config = SPVM::Builder::Config->new_c11(file => __FILE__);

C++:

  my $config = SPVM::Builder::Config->new_cpp(file => __FILE__);

C++11:

  my $config = SPVM::Builder::Config->new_cpp11(file => __FILE__);

Output messages to C<stderr> from the compiler and the linker:

  $config->quiet(0);

Force the compilation and link:

  $config->force(1);

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
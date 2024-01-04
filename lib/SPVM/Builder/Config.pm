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

# Class Methods
sub new {
  my $class = shift;
  
  my $self = {@_};
  
  bless $self, ref $class || $class;
  
  my $file_optional = $self->file_optional;
  
  my $file = $self->file;
  if (!$file_optional && !defined $file) {
    confess "The \"file\" field must be defined";
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
    my $builder_dir = SPVM::Builder::Util::get_builder_dir_from_config_class();
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
  
  # before_compile_cbs
  unless (defined $self->{before_compile_cbs}) {
    $self->before_compile_cbs([]);
  }
  
  # resources
  unless (defined $self->{resources}) {
    $self->{resources} = {};
  }
  
  # ld
  unless (defined $self->{ld}) {
    $self->ld($Config{ld});
  }
  
  # ldflags
  unless (defined $self->{ldflags}) {
    $self->ldflags([]);
  }
  
  # output_type
  unless (defined $self->output_type) {
    $self->output_type('dynamic_lib');
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
  
  # before_link_cbs
  unless (defined $self->{before_link_cbs}) {
    $self->before_link_cbs([]);
  }
  
  unless (defined $self->{_loaded_config_files}) {
    $self->{_loaded_config_files} = [];
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

sub add_static_lib {
  my ($self, @libs) = @_;
  
  my @static_libs;
  for my $lib (@libs) {
    my $static_lib;
    if (ref $lib eq 'SPVM::Builder::LibInfo') {
      $static_lib = $lib->is_static(1);
    }
    else {
      my $lib_name = $lib;
      $static_lib = SPVM::Builder::LibInfo->new(config => $self);
      $static_lib->name($lib_name);
      $static_lib->is_static(1);
    }
    push @static_libs, $static_lib;
  }
  
  $self->add_lib(@static_libs);
}

sub add_source_file {
  my ($self, @source_files) = @_;
  
  push @{$self->{source_files}}, @source_files;
}

sub add_before_compile_cb {
  my ($self, @before_compile_cbs) = @_;
  
  push @{$self->{before_compile_cbs}}, @before_compile_cbs;
}

sub add_before_link_cb {
  my ($self, @before_link_cbs) = @_;
  
  push @{$self->{before_link_cbs}}, @before_link_cbs;
}

sub load_config {
  my ($self, $config_file, @args) = @_;

  unless (-f $config_file) {
    confess "The config file \"$config_file\" must exist";
  }
  local @ARGV = @args;
  my $config = do File::Spec->rel2abs($config_file);
  if ($@) {
    confess "The config file \"$config_file\" can't be parsed: $@";
  }
  
  unless (defined $config && $config->isa('SPVM::Builder::Config')) {
    confess "The config file must be a SPVM::Builder::Config object";
  }
  
  push @{$config->get_loaded_config_files}, $config_file;
  
  return $config;
}

sub load_mode_config {
  my ($self, $config_file, $mode, @argv) = @_;
  
  my $mode_config_file = $self->_remove_ext_from_config_file($config_file);
  if (defined $mode) {
    $mode_config_file .= ".$mode";
  }
  $mode_config_file .= ".config";
  
  unless (-f $mode_config_file) {
    confess "Can't find the config file \"$mode_config_file\"";
  }
  
  my $config = $self->load_config($mode_config_file, @argv);
  
  return $config;
}

sub load_base_config {
  my ($self, $config_file, @args) = @_;
  
  my $config = $self->load_mode_config($config_file, undef, @args);

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
    my $basic_type_name = $first_arg;
    my %args = @args;
    if (exists $args{class_name}) {
      $basic_type_name = delete $args{class_name};
    }
    $resource = SPVM::Builder::Resource->new(class_name => $basic_type_name, %args);
  }
  
  my $resource_basic_type_name = $resource->class_name;
  my $resource_mode = $resource->mode;
  my $resource_argv = $resource->argv;
  
  my $ext = defined $resource_mode ? "$resource_mode.config" : 'config';
  my $config_file_base = SPVM::Builder::Util::convert_basic_type_name_to_rel_file($resource_basic_type_name, $ext);
  
  my $config_file = SPVM::Builder::Util::get_config_file_from_basic_type_name($resource_basic_type_name, $resource_mode);
  
  my $config = $self->load_config($config_file, @$resource_argv);
  $config->file($config_file);
  
  $resource->config($config);
  
  my $index = keys %{$self->{resources}};
  
  $self->{resources}->{$resource_basic_type_name} = {resource => $resource, index => $index};
  
  return $resource;
}

sub disable_resource {
  my $self = shift;
  if (@_) {
    $self->{disable_resource} = $_[0];
    return $self;
  }
  else {
    return $self->{disable_resource};
  }
}

sub get_resource {
  my ($self, $resource_basic_type_name) = @_;
  
  unless (defined $self->{resources}{$resource_basic_type_name}) {
    return;
  }
  
  my $resource = $self->{resources}{$resource_basic_type_name}{resource};
  
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

SPVM::Builder::Config - Compiler and Linker Configuration for Native Classes

=head1 Description

The SPVM::Builder::Config class has methods to manipulate compiler and linker configuration for L<native classes|SPVM::Document::NativeClass>.

=head1 Usage

  use SPVM::Builder::Config;
  
  # Create a config
  my $config = SPVM::Builder::Config->new(file => __FILE__);
  
  # C99
  my $config = SPVM::Builder::Config->new_c99(file => __FILE__);
  
  # GNU C99
  my $config = SPVM::Builder::Config->new_gnu99(file => __FILE__);
  
  # C++
  my $config = SPVM::Builder::Config->new_cpp(file => __FILE__);
  
  # C++11
  my $config = SPVM::Builder::Config->new_cpp11(file => __FILE__);
  
  # C++17
  my $config = SPVM::Builder::Config->new_cpp17(file => __FILE__);
  
  # Optimize
  $config->optimize('-O2');
  
  # Optimize with debug mode
  $config->optimize('-O0 -g');
  
  # Add libraries
  $config->add_lib('gdi32', 'd2d1', 'Dwrite');

  # Add source files
  $config->add_source_file('foo.c', 'bar.c', 'baz/baz.c');
  
  # Use resource
  $config->use_resource('TestCase::Resource::Zlib');
  $config->use_resource('TestCase::Resource::Foo1', mode => 'mode1', argv => ['args1', 'args2']);
  
  # Get resouce information
  my $resource = $config->get_resource('TestCase::Resource::Zlib');

=head1 Details

See L<SPVM::Document::NativeClass> about creating native classes and those configuration.

=head1 Fields

=head2 ext

  my $ext = $config->ext;
  $config->ext($ext);

Gets and sets the C<ext> field, the extension of a native class.

Examples:
  
  # Foo/Bar.c
  $config->ext('c');
  
  # Foo/Bar.cpp
  $config->ext('cpp');

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

Gets and sets the C<include_dirs> field, an array reference of header file search directories.

The values of this field are converted to the C<-I> options for the compiler L</"cc">.

  # -I/path1 -I/path2
  $config->include_dirs('/path1', '/path2');

=head2 spvm_core_include_dir

  my $spvm_core_include_dir = $config->spvm_core_include_dir;
  $config->spvm_core_include_dir($spvm_core_include_dir);

Gets and sets the C<spvm_core_include_dir> field, the SPVM core header file search directory.

This field are converted to the C<-I> option for the compiler L</"cc">.

=head2 native_include_dir

  my $native_include_dir = $config->native_include_dir;
  $config->native_include_dir($native_include_dir);

Gets and sets the C<native_include_dir> field, the search directory for header files of this native class.

This field are converted to the C<-I> option for the compiler L</"cc">.

=head2 native_src_dir

  my $native_src_dir = $config->native_src_dir;
  $config->native_src_dir($native_src_dir);

Gets and sets the C<native_src_dir> field, the search directory for source files of this native class.

=head2 ccflags

  my $ccflags = $config->ccflags;
  $config->ccflags($ccflags);

Gets and sets the C<ccflags> field, an array reference of compiler options for the compiler L</"cc">.

=head2 dynamic_lib_ccflags

  my $dynamic_lib_ccflags = $config->dynamic_lib_ccflags;
  $config->dynamic_lib_ccflags($dynamic_lib_ccflags);

Gets and sets the C<dynamic_lib_ccflags> field, an array reference of dynamic link options for the compiler L</"cc">.

=head2 thread_ccflags

  my $thread_ccflags = $config->thread_ccflags;
  $config->thread_ccflags($thread_ccflags);

Gets and sets the C<thread_ccflags> field, an array reference of thread options for the compiler L</"cc">.

=head2 std

  my $std = $config->std;
  $config->std($std);

Gets and sets the C<std> field, a language standard.

This field is converted to the C<-std> option for the compiler L</"cc">.

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

Gets and sets the C<optimize> field, an optimization option for the compiler L</"cc">.

Examples:

  $config->optimize('-O3');
  $config->optimize('-O2');
  $config->optimize('-g3 -O0');

=head2 source_files

  my $source_files = $config->source_files;
  $config->source_files($source_files);

Gets and sets the C<source_files> field, an array reference of source files used by this native class.

The source file names are specified as relative paths from the L</"native_src_dir"> field.

=head2 before_compile_cbs

  my $before_compile_cbs = $config->before_compile_cbs;
  $config->before_compile_cbs($before_compile_cbs);

Gets and sets the C<before_compile_cbs> field, an array reference of callbacks called just before the compile command L</"cc"> is executed.

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

Gets and sets the C<lib_dirs> field, an array reference of library search path for the linker L</"ld">.

This is equivalent to the C<-L> option for the linker L</"ld">.

=head2 libs

  my $libs = $config->libs;
  $config->libs($libs);

Gets and sets the C<libs> field, an array reference of library names or L<SPVM::Builder::LibInfo> objects for the linker L</"ld">.

=head2 ldflags

  my ldflags = $config->ldflags;
  $config->ldflags(ldflags);

Gets and sets the C<ldflags> field, an array reference of options for the linker L</"ld">.

=head2 dynamic_lib_ldflags

  my dynamic_lib_ldflags = $config->dynamic_lib_ldflags;
  $config->dynamic_lib_ldflags(dynamic_lib_ldflags);

Gets and sets the C<dynamic_lib_ldflags> field, an array reference of dynamic library options for the linker L</"ld">.

=head2 thread_ldflags

  my thread_ldflags = $config->thread_ldflags;
  $config->thread_ldflags(thread_ldflags);

Gets and sets the C<thread_ldflags> field, an array reference of thread options for the linker L</"ld">.

=head2 static_lib_ldflag

  my static_lib_ldflag = $config->static_lib_ldflag;
  $config->static_lib_ldflag(static_lib_ldflag);

Gets and sets the C<static_lib_ldflag> field, an array reference of options that specify the begining and end of a static library.

Examples:
  
  # -Wl,-Bstatic -lfoo -Wl,-Bdynamic
  $config->static_lib_ldflag(['-Wl,-Bstatic', '-Wl,-Bdynamic']);
  $config->add_static_lib('foo');

=head2 ld_optimize

  my $ld_optimize = $config->ld_optimize;
  $config->ld_optimize($ld_optimize);

Gets and sets the C<ld_optimize> field, an optimization option for the linker L</"ld">.

Examples:

  $config->ld_optimize("-O3");

=head2 before_link_cbs

  my $before_link_cbs = $config->before_link_cbs;
  $config->before_link_cbs($before_link_cbs);

Gets and sets the C<before_link_cbs> field, an array reference of callbacks called just before the link command L</"ld"> is executed.

The 1th argument of the callback is a L<SPVM::Builder::Config> object.

The 2th argument of the callback is a L<SPVM::Builder::LinkInfo> object.

=head2 force

  my $force = $config->force;
  $config->force($force);

Gets and sets the C<force> field.

If this field is a true value, the compilation and linking is forced without using the cache.

If this field is a false value except for undef, the compilation and linking uses the cached if the cache exists.

If this field is undef, whether the compilation and linking is forced is not specified.

=head2 quiet

  my $quiet = $config->quiet;
  $config->quiet($quiet);

Gets and sets the C<quiet> field.

If this field is a true value, compiler and linker messages are output.

If this field is a false value except for undef, compiler and linker messages are are not output.

If this field is undef, whether compiler and linker messages are output is not specified.

=head2 class_name

  my $basic_type_name = $config->class_name;
  $config->class_name($basic_type_name);

Gets and sets the C<class_name> field, the class name configured by this config.

=head2 file

  my $file = $config->file;
  $config->file($file);

Gets and sets the C<file> field, the file path of this config.

=head2 file_optional

  my $file_optional = $config->file_optional;
  $config->file_optional($file_optional);

Gets and sets the C<file_optional> field.

If this field is a true value, even if the L<file|/"file"> field is not given, an exception is not thrown.

=head2 output_type

  my $output_type = $config->output_type;
  $config->output_type($output_type);

Gets and sets the C<output_type> field, an output type of the output file generated by the linker L</"ld">.

If thie field is C<dynamic_lib>, the output file is a dynamic link library.

If thie field is C<static_lib>, the output file is a static link library.

If thie field is C<exe>, the output file is an executable file.

=head2 disable_resource

  my $disable_resource = $config->disable_resource;
  $config->disable_resource($disable_resource);

Gets and sets the C<disable_resource> field.

If this value is a true value, all resources loaded by the L</"use_resource"> method are disabled.

=head1 Class Methods

=head2 new

  my $config = SPVM::Builder::Config->new(%fields);

Creates a new C<SPVM::Builder::Config> object with L<fields|/"Fields">, and returns it.

If a field is not defined, the field is set to the following default value.

=over 2

=item * L</"class_name">

undef

=item * L</"file">

undef

=item * L</"file_optional">

0

=item * L</"ext">

undef

=item * L</"quiet">

undef

=item * L</"force">

undef

=item * L</"cc">

The C<$Config{cc}> of the L<Config> class.

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

=item * L</"std">

undef

=item * L</"optimize">

"-O3"

=item * L</"include_dirs">

[]

=item * L</"spvm_core_include_dir">

The SPVM core header file search directory.

This is generated from the path of the config file L</"file">.

This is something like C</path/SPVM/Builder/include>.

=item * L</"native_include_dir">

The header file search directory for this natvie class.

This is generated from the path of the config file L</"file">.

This is something like C</path/Foo.native/include>.

=item * L</"native_src_dir">

The source file search directory for this natvie class.

This is generated from the path of the config file L</"file">.

This is something like C</path/Foo.native/src>.

=item * L</"source_files">

[]

=item * L</"before_compile_cbs">

[]

=item * L</"ld">

The C<$Config{ld}> of the L<Config> class.

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

=item * L</"before_link_cbs">

[]

=item * L</"output_type">

"dynamic_lib"

=back

Exceptions:

The \"file" field must be defined. Otherwise an exception is thrown.

=head2 new_c
  
  my $config = SPVM::Builder::Config->new_c(file => __FILE__);

Calls the L</"new"> method and sets the L</"ext"> field to C<c>, and returns the return value of the L</"new_c"> method.

=head2 new_c99
  
  my $config = SPVM::Builder::Config->new_c99(file => __FILE__);

Calls the L</"new_c"> method and sets the L</"std"> field to C<c99>, and returns the return value of the L</"new_c"> method.

=head2 new_c11
  
  my $config = SPVM::Builder::Config->new_c11(file => __FILE__);

Calls the L</"new_c"> method and sets the L</"std"> field to C<c11>, and returns the return value of the L</"new_c"> method.

=head2 new_gnu99
  
  my $config = SPVM::Builder::Config->new_gnu99(file => __FILE__);

Calls the L</"new_c"> method and sets the L</"std"> field to C<gnu99>, and returns the return value of the L</"new_c"> method.

=head2 new_gnu11
  
  my $config = SPVM::Builder::Config->new_gnu11(file => __FILE__);

Calls the L</"new_c"> method and sets the L</"std"> field to C<gnu11>, and returns the return value of the L</"new_c"> method.

=head2 new_cpp
  
  my $config = SPVM::Builder::Config->new_cpp(file => __FILE__);

Calls the L</"new"> method and sets the L</"ext"> field to C<cpp> and sets the L</"cc"> field to a C<C++> compiler and sets the L</"ld"> field to a C<C++> linker, and returns the return value of the L</"new"> method.

If the compiler included in C<$Config{gccversion}> is C<clang>, the L</"cc"> field and the L</"ld"> field are set to C<clang++>.

Otherwise the L</"cc"> field and the L</"ld"> field are set to C<g++>.

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

Adds compiler options at the end of the L</"ccflags"> field.

=head2 add_ldflag

  $config->add_ldflag(@ldflags);

Adds linker options at the end of the L</"ldflags"> field.

=head2 add_include_dir

  $config->add_include_dir(@include_dirs);

Adds header file search directories at the end of the L</"include_dirs"> field.

=head2 add_source_file

  $config->add_source_file(@source_files);

Adds source files used by this native class at the end of the L</"source_files"> field.

Examples:

  $config->add_source_file('foo.c', 'bar.c');

=head2 add_before_compile_cb

  $config->add_before_compile_cb(@before_compile_cbs);

Adds callbacks called just before the compile command L</"cc"> is executed at the end of the L</"before_compile_cbs"> field.

Examples:

  $config->add_before_compile_cb(sub {
    my ($config, $compile_info) = @_;
    
    my $cc = $compile_info->cc;
    
    # Do something
  });

=head2 add_lib_dir

  $config->add_lib_dir(@lib_dirs);

Adds library search directories at the end of the L</"lib_dirs"> field.

=head2 add_lib

  $config->add_lib(@libs);

Adds library names or L<SPVM::Builder::LibInfo> objects at the end of the L</"libs"> field.

Examples:

  $config->add_lib('gsl');
  $config->add_lib('gsl', 'z');
  $config->add_lib(
    SPVM::Builder::LibInfo->new(config => $config, name => 'gsl'),
    SPVM::Builder::LibInfo->new(config => $config, name => 'z', abs => 1),
  );

=head2 add_static_lib

  $config->add_static_lib(@libs);

Adds library names or L<SPVM::Builder::LibInfo> objects at the end of the L</"libs"> field with the C<static> field set to a true value.

Examples:

  $config->add_static_lib('gsl');
  $config->add_static_lib('gsl', 'z');

=head2 add_before_link_cb

  $config->add_before_link_cb(@before_link_cbs);

Adds callbacks called just before the link command L</"ld"> is executed at the end of the L</"before_link_cbs"> field.

Examples:

  $config->add_before_link_cb(sub {
    my ($config, $link_info) = @_;
    
    my $object_files = $link_info->object_files;
    
    # Do something
    
  });

=head2 use_resource

  my $resource = $config->use_resource($resource_name);
  my $resource = $config->use_resource($resource_name, %options);

Loads a resource(a L<SPVM::Builder::Resource> object) given a resource name and options, and returns it.

See L<SPVM::Document::Resource> about creating and using resources.

Options:

=over 2

=item * mode

The same as the L<mode|SPVM::Builder::Resource/"mode"> option in the new method in the SPVM::Builder::Resource class.

=item * argv

The same as the L<argv|SPVM::Builder::Resource/"argv"> option in the new method in the SPVM::Builder::Resource class.

=back

Examples:

  $config->use_resource('Resource::Zlib');
  $config->use_resource('Resource::Foo', mode => 'mode1', argv => ['args1', 'args2']);

=head2 get_resource

  my $resource = $config->get_resource($resource_name);

Gets a resource(a L<SPVM::Builder::Resource> object) loaded by the L</"use_resource"> method given a resource name, and returns it.

=head2 get_resource_names

  my $resource_names = $config->get_resource_names;

Returns resource names loaded by the L</"use_resource"> method.

=head2 load_config

  my $config = $config->load_config($config_file, @argv);

Loads a config file, and returns a L<SPVM::Builder::Config> object.

The argument @argv is set to the @ARGV of the config file.

=head2 load_base_config

  my $config = $config->load_base_config($config_file, @argv);

Loads the base config file of the config file given as the argument, and returns a L<SPVM::Builder::Config> object.

The base config file is the config file that removes its mode from the config file given as the argument.

The argument @argv is set to the @ARGV of the base config file.

If the config file given as the argument is C</path/Foo.devel.config>, the base config file is C</path/Foo.config>.

Examples:

  my $config = SPVM::Builder::Config::Exe->load_base_config(__FILE__);

=head2 load_mode_config

  my $config = $config->load_mode_config($config_file, $mode, @argv);

Loads the mode config file of the config file given as the argument, and returns a L<SPVM::Builder::Config> object.

The mode config file is the config file that removes its mode(if the mode exists) from the config file given as the argument and added the mode given as the argument.

The argument @argv is set to the @ARGV of the mode config file.

If the config file given as the argument is C</path/Foo.config> and the mode given as the argument is C<production>, the mode config file is C</path/Foo.production.config>.

If the config file given as the argument is C</path/Foo.devel.config> and the mode given as the argument is C<production>, the mode config file is C</path/Foo.production.config>.

  my $config = SPVM::Builder::Config::Exe->load_mode_config(__FILE__, "production");

=head2 get_loaded_config_files

Returns the config files loaded by the L</"load_config"> method.

=head2 clone

  my $clone = $self->clone;

Clones the L<SPVM::Builder::Config> object, and returns it.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

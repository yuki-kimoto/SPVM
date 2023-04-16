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
    confess "\"file\" option must be specified";
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
    if ($Config{cccdlflags} =~ /-fPIC\b/) {
      $self->dynamic_lib_ccflags(['-fPIC']);
    }
    else {
      $self->dynamic_lib_ccflags([]);
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
      $self->dynamic_lib_ldflags(['-shared']);
    }
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
      $static_lib = SPVM::Builder::LibInfo->new;
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
  
  my $config_file = SPVM::Builder::Util::get_config_file_from_class_name($resource_class_name, $resource_mode);
  
  my $config = $self->load_config($config_file, @$resource_argv);
  $config->file($config_file);
  
  $resource->config($config);
  
  my $index = keys %{$self->{resources}};
  
  $self->{resources}->{$resource_class_name} = {resource => $resource, index => $index};
  
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

The SPVM::Builder::Config - Config of Compiler and Linker

=head1 Description

The SPVM::Builder::Config class has methods to manipulate a config to compile source files and generate a dynamic link.

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
  
  # Optimize
  $config->optimize('-O2');
  
  # Optimize with debug mode
  $config->optimize('-O0 -g');
  
  # Adds source files
  $config->add_source_file('foo.c', 'bar.c', 'baz/baz.c');
  
  # Uses resource
  $config->use_resource('TestCase::Resource::Zlib');
  $config->use_resource('TestCase::Resource::Foo1', mode => 'mode1', argv => ['args1', 'args2']);
  
  # Gets resouce information
  my $resource = $config->get_resource('TestCase::Resource::Zlib');

=head1 Fields

=head2 ext

  my $ext = $config->ext;
  $config->ext($ext);

Gets and sets the C<ext> field.

This field is the extension of a native class.

Examples:
  
  # Foo/Bar.c
  $config->ext('c');
  
  # Foo/Bar.cpp
  $config->ext('cpp');
  
=head2 cc

  my $cc = $config->cc;
  $config->cc($cc);

Gets and sets the C<cc> field.

This field is a compiler name.

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

Gets and sets the C<include_dirs> field.

This field is an array reference of including directories of the compiler.

This is same as C<-I> option of C<gcc>. 

=head2 spvm_core_include_dir

  my $spvm_core_include_dir = $config->spvm_core_include_dir;
  $config->spvm_core_include_dir($spvm_core_include_dir);

Gets and sets the C<spvm_core_include_dir> field.

This is the header including directory of the SPVM core.

=head2 native_include_dir

  my $native_include_dir = $config->native_include_dir;
  $config->native_include_dir($native_include_dir);

Gets and sets the C<native_include_dir> field.

This field is the path of the header including directory of this native class.

=head2 native_src_dir

  my $native_src_dir = $config->native_src_dir;
  $config->native_src_dir($native_src_dir);

Gets and sets the C<native_src_dir> field.

This field is the path of the source directory of this native class.

=head2 ccflags

  my $ccflags = $config->ccflags;
  $config->ccflags($ccflags);

Gets and sets the C<ccflags> field.

This field is an array reference that contains compiler flags.

=head2 dynamic_lib_ccflags

  my $dynamic_lib_ccflags = $config->dynamic_lib_ccflags;
  $config->dynamic_lib_ccflags($dynamic_lib_ccflags);

Gets and sets the C<dynamic_lib_ccflags> field.

This field is an array reference that contains compiler flags for information when the linker generates a dynamic link.

=head2 std

  my $std = $config->std;
  $config->std($std);

Gets and sets the C<std> field.

This field is the value for C<-std> option of the compiler.

Examples:

  $config->std('c99');
  $config->std('gnu99');
  $config->std('cpp');
  $config->std('cpp11');
  $config->std('cpp17');

=head2 optimize

  my $optimize = $config->optimize;
  $config->optimize($optimize);

Gets and sets the C<optimize> field.

This field is the option for optimization of the compiler.

Examples:

  $config->optimize('-O3');
  $config->optimize('-O2');
  $config->optimize('-g3 -O0');

=head2 source_files

  my $source_files = $config->source_files;
  $config->source_files($source_files);

Gets and sets the C<source_files> field.

This field is a array reference that contains source files.

The file name is the relative pass from L</"native_src_dir">.

Examples:

  $config->source_files(['foo.c', 'bar.c']);

=head2 before_compile_cbs

  my $before_compile_cbs = $config->before_compile_cbs;
  $config->before_compile_cbs($before_compile_cbs);

Gets and sets the C<before_compile_cbs> field.

This field is an array reference that contains the callbacks called before a compilation.

Examples:

  $config->before_compile_cbs([sub {
    my ($config, $compile_info) = @_;
    
    my $cc = $compile_info->cc;
    
    # Do something
  }]);

=head2 before_link_cbs

  my $before_link_cbs = $config->before_link_cbs;
  $config->before_link_cbs($before_link_cbs);

Gets and sets the C<before_link_cbs> field.

This field is an array reference that contains the callbacks called before a link.

Examples:

  $config->before_link_cbs([sub {
    my ($config, $link_info) = @_;
    
    my $object_files = $link_info->object_files;
    
    # Do something
    
  }]);

=head2 ld

  my $ld = $config->ld;
  $config->ld($ld);

Gets and sets the C<ld> field.

This field is a linker name.

=head2 lib_dirs

  my $lib_dirs = $config->lib_dirs;
  $config->lib_dirs($lib_dirs);

Gets and sets the C<lib_dirs> field.

This field is an array reference that contains the directories that libraries are searched for by the linker. This is same as C<-L> option of C<gcc>.

=head2 libs

  my $libs = $config->libs;
  $config->libs($libs);

Gets and sets the C<libs> field.

This field is an array reference that contains library names or L<SPVM::Builder::LibInfo> objects. These libraries are linked by L<SPVM::Builder::CC/"link"> method.

=head2 ldflags

  my ldflags = $config->ldflags;
  $config->ldflags(ldflags);

Gets and sets the C<ldflags> field.

This field is an array reference that contains linker flags.

=head2 dynamic_lib_ldflags

  my dynamic_lib_ldflags = $config->dynamic_lib_ldflags;
  $config->dynamic_lib_ldflags(dynamic_lib_ldflags);

Gets and sets the C<dynamic_lib_ldflags> field.

This field is an array reference that contains linker flags for a dynamic link.

=head2 ld_optimize

  my $ld_optimize = $config->ld_optimize;
  $config->ld_optimize($ld_optimize);

Gets and sets the C<ld_optimize> field.

This field is the option for optimization of the linker such as C<-O3>, C<-O2>, C<-g3 -O0>.

Examples:

  $config->ld_optimize("-O3");

=head2 force

  my $force = $config->force;
  $config->force($force);

Gets and sets the C<force> field.

If this field is a true value, the compilation and link are forced without caching.

If this field is a false value, they are not forced.

If this field is undef, whether they are forced or not is determined by other conditions.

=head2 quiet

  my $quiet = $config->quiet;
  $config->quiet($quiet);

Gets and sets the C<quiet> field.

If this field is a true value, messages of the compiler and linker are output.

If this field is a false value, the messages are not output.

If this field is undef, whether the messages are output or not is determined by other conditions.

=head2 class_name

  my $class_name = $config->class_name;
  $config->class_name($class_name);

Gets and sets the C<class_name> field.

This field is the class to use this config.

=head2 file

  my $file = $config->file;
  $config->file($file);

Gets and sets the C<file> field.

This field is the path of the config file.

=head2 file_optional

  my $file_optional = $config->file_optional;
  $config->file_optional($file_optional);

Gets and sets the C<file_optional> field.

If this field is false and the file that is given by the L<file|/"file"> field is not found, an exception is thrown.

=head2 output_type

  my $output_type = $config->output_type;
  $config->output_type($output_type);

Gets and sets the C<output_type> field.

This field is the output type of the linker. C<"dynamic_lib">, C<"static_lib"> and C<"exe"> are available.

Default:

"dynamic_lib"

=head2 disable_resource

  my $disable_resource = $config->disable_resource;
  $config->disable_resource($disable_resource);

Gets and sets the C<disable_resource> field.

If this value is true, All resources loaded by the L</"use_resource"> method is disabled.

=head1 Class Methods

=head2 new

  my $config = SPVM::Builder::Config->new(%fields);

Create a C<SPVM::Builder::Config> object with L<fields|/"Fields">.

Exceptions:

If the L</"file_optional"> field is not set to a true value, the L</"file"> field must be passed. Otherwise an exception is thrown.

Default Field Values:

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

If C<$Config{cccdlflags}> contains C<-fPIC>, the following value is its default value.

["-fPIC"]

Otherwise the following value is its default value.

[]

=item * L</"std">

undef

=item * L</"optimize">

"-O3"

=item * L</"include_dirs">

[]

=item * L</"spvm_core_include_dir">

The header including directory of the SPVM core is created from the class file of the loaded L<SPVM::Builder::Config> class. 

The value looks like C<path/SPVM/Builder/include>.

=item * L</"native_include_dir">

If the L</"file"> field is defined, the path of the header including directory is created from the L</"file"> field.

The value looks like C<path/Foo.native/include>.

=item * L</"native_src_dir">

If the L</"file"> field is defined, the path of the source directory is created from the L</"file"> field.

The value looks like C<path/Foo.native/src>.

=item * L</"source_files">

[]

=item * L</"before_compile_cbs">

[]

=item * L</"ld">

The C<$Config{ld}> of the L<Config> class.

=item * L</"ldflags">

=item * L</"dynamic_lib_ldflags">

Windows:

["-mdll", "-s"]
  
Other OSs:

['-shared']

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

Examples:

  my $config = SPVM::Builder::Config->new(file => __FILE__);

=head2 new_c
  
  my $config = SPVM::Builder::Config->new_c(file => __FILE__);

Calls the L</"new"> method and sets th L</"ext"> field to C<c>.

=head2 new_c99
  
  my $config = SPVM::Builder::Config->new_c99(file => __FILE__);

Calls the L</"new_c"> method and sets the L</"std"> field to C<c99>.

=head2 new_c11
  
  my $config = SPVM::Builder::Config->new_c11(file => __FILE__);

Calls the L</"new_c"> method and sets the L</"std"> field to C<c11>.

=head2 new_gnu99
  
  my $config = SPVM::Builder::Config->new_gnu99(file => __FILE__);

Calls the L</"new_c"> method and sets the L</"std"> field to C<gnu99>.

=head2 new_gnu11
  
  my $config = SPVM::Builder::Config->new_gnu11(file => __FILE__);

Calls the L</"new_c"> method and sets the L</"std"> field to C<gnu11>.

=head2 new_cpp
  
  my $config = SPVM::Builder::Config->new_cpp(file => __FILE__);

Calls the L</"new"> method and sets the L</"ext"> field to C<cpp> and sets the L</"cc"> field to C<C++> compiler and sets the L</"ld"> field to C<C++> linker.

=head2 new_cpp11
  
  my $config = SPVM::Builder::Config->new_cpp11(file => __FILE__);

Calls the L</"new_cpp"> method and sets the L</"std"> field to C<c++11>.

=head2 new_cpp14
  
  my $config = SPVM::Builder::Config->new_cpp14(file => __FILE__);

Calls the L</"new_cpp"> method and sets the L</"std"> field to C<c++14>.

=head2 new_cpp17
  
  my $config = SPVM::Builder::Config->new_cpp17(file => __FILE__);

Calls the L</"new_cpp"> method and sets the L</"std"> field to C<c++17>.

=head1 Instance Methods

=head2 add_ccflag

  $config->add_ccflag(@ccflags);

Adds values after the last element of L</"ccflags"> field.

=head2 add_ldflag

  $config->add_ldflag(@ldflags);

Adds values after the last element of L</"ldflags"> field.

=head2 add_include_dir

  $config->add_include_dir(@include_dirs);

Adds values after the last element of L</"include_dirs"> field.

=head2 add_lib_dir

  $config->add_lib_dir(@lib_dirs);

Adds values after the last element of  C<lib_dirs> field.

=head2 add_source_file

  $config->add_source_file(@source_files);

Adds elements after the last element of L</"source_files"> field.

=head2 add_before_compile_cb

  $config->add_before_compile_cb(@before_compile_cbs);

Adds elements after the last element of L</"before_compile_cbs"> field.

=head2 add_before_compile_cb

  $config->add_before_link_cb(@before_link_cbs);

Adds elements after the last element of L</"before_link_cbs"> field.

=head2 add_lib

  $config->add_lib(@libs);

Adds library names or L<SPVM::Builder::LibInfo> objects after the last element of L</"libs"> field.

Examples:

  $config->add_lib('gsl');
  $config->add_lib('gsl', 'z');
  $config->add_lib(
    SPVM::Builder::LibInfo->new(name => 'gsl'),
    SPVM::Builder::LibInfo->new(name => 'z', abs => 1),
  );

=head2 add_static_lib

  $config->add_static_lib(@libs);

Adds library names or L<SPVM::Builder::LibInfo> objects after the last element of L</"libs"> field.

C<static> field is set to a true value.

Examples:

  $config->add_static_lib('gsl');
  $config->add_static_lib('gsl', 'z');
  $config->add_static_lib(
    SPVM::Builder::LibInfo->new(name => 'gsl'),
    SPVM::Builder::LibInfo->new(name => 'z', abs => 1),
  );

=head2 use_resource

  my $resource = $config->use_resource($resource_name);
  my $resource = $config->use_resource($resource_name, %options);

Loads a resource by the resource name $resource_name using the L<SPVM::Builder::Resource|/"new"> method in the L<SPVM::Builder::Resource> class, and returns a L<SPVM::Builder::Resource> object.
  my $resource = SPVM::Builder::Resource->new(class_name => $resource_name);
  $config->use_resource($resource);

If the options %options are given, they are used as the options of the L<SPVM::Builder::Resource|/"new"> method in the L<SPVM::Builder::Resource> class.

  my $resource = SPVM::Builder::Resource->new(
    class_name => 'Resource::Zlib',
    mode => 'production',
    argv => ['foo', 'bar'],
  );
  $config->use_resource($resource);

Examples:

  $config->use_resource('Resource::Zlib');

=head2 get_resource_names

  my $resource_names = $config->get_resource_names;

Gets resource names loaded by the L/"use_resource/"> method.

=head2 load_config

  my $config = $config->load_config($config_file, @argv);

Loads a config file, and returns a L<SPVM::Builder::Config> object. The argument @argv is set to the @ARGV of the config file.

=head2 load_base_config

  my $config = $config->load_base_config($config_file, @argv);

Loads a base config file like C<Foo.config>. This method is the alias for the following method call using L</"load_mode_config">.

  my $config = $config->load_mode_config($config_file, undef, @argv);

=head2 load_mode_config

  my $config = $config->load_mode_config($config_file, $mode, @argv);

Loads a mode config file like C<Foo.mode.config>.

At first, removes the string matching the regex C<(\.[^\.]+)?\.config$> from the base name of the config file $config_file.

Next, if the mode $mode is defined, C<.$mode.config> is added to the $config_file. Otherwise C<.config> is added.

Last, L</"load_config"> is called with the modified name of the config file.

=head2 get_loaded_config_files

Gets the config files loaded by the L</"load_config"> method.

=head2 clone

  my $clone = $self->clone;

Clones the L<SPVM::Builder::Config> object, and returns it.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

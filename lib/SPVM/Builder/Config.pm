package SPVM::Builder::Config;

use strict;
use warnings;
use Config;
use Carp 'confess';
use File::Basename 'dirname';

# Fields
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

sub cc_each {
  my $self = shift;
  if (@_) {
    $self->{cc_each} = $_[0];
    return $self;
  }
  else {
    return $self->{cc_each};
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

sub ccflags_each {
  my $self = shift;
  if (@_) {
    $self->{ccflags_each} = $_[0];
    return $self;
  }
  else {
    return $self->{ccflags_each};
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

sub resources {
  my $self = shift;
  if (@_) {
    $self->{resources} = $_[0];
    return $self;
  }
  else {
    return $self->{resources};
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

# Methods
sub new {
  my $class = shift;
  
  my $self = {@_};

  bless $self, $class;
  
  # quiet
  unless (defined $self->{quiet}) {
    $self->quiet(1);
  }

  # force
  unless (defined $self->{force}) {
    $self->force(0);
  }
  
  # ext
  unless (defined $self->{ext}) {
    $self->ext(undef);
  }

  # cc
  unless (defined $self->{cc}) {
    $self->cc($Config{cc});
  }

  # include_dirs
  unless (defined $self->{include_dirs}) {
    $self->include_dirs([]);
    
    my @default_include_dirs;

    # Add "include" directory of SPVM::Builder. This directory contains spvm_native.h
    my $spvm_builder_config_dir = $INC{"SPVM/Builder/Config.pm"};
    my $spvm_builder_dir = $spvm_builder_config_dir;
    $spvm_builder_dir =~ s/\/Config\.pm$//;
    my $spvm_include_dir = $spvm_builder_dir;
    $spvm_include_dir .= '/include';
    push @default_include_dirs, $spvm_include_dir;
    
    $self->add_include_dirs(@default_include_dirs);
  }
  
  # ccflags
  unless (defined $self->{ccflags}) {
    $self->ccflags([]);
    
    my @default_ccflags;
    
    # If dynamic link libraries must link position independent codes, add -fPIC option.
    if ($Config{cccdlflags} =~ /-fPIC\b/) {
      push @default_ccflags, '-fPIC';
    }
    
    $self->add_ccflags(@default_ccflags);
  }

  # optimize
  unless (defined $self->{optimize}) {
    $self->optimize('-O3');
  }
  
  # ld
  unless (defined $self->{ld}) {
    $self->ld($Config{ld});
  }

  # lib_dirs
  unless (defined $self->{lib_dirs}) {
    $self->lib_dirs([]);
  }

  # resources
  unless (defined $self->{resources}) {
    $self->resources([]);
  }

  # source_files
  unless (defined $self->{source_files}) {
    $self->source_files([]);
  }
  
  # libs
  unless (defined $self->{libs}) {
    $self->libs([]);
  }
  
  # ldflags
  unless (defined $self->{ldflags}) {
    $self->ldflags([]);
    
    my @default_ldflags;
    
    # Dynamic link options
    if ($^O eq 'MSWin32') {
      push @default_ldflags, '-mdll', '-s';
    }
    else {
      push @default_ldflags, '-shared';
    }
    $self->add_ldflags(@default_ldflags);
  }

  # ld_optimize
  unless (defined $self->{ld_optimize}) {
    $self->ld_optimize('-O2');
  }
  
  return $self;
}

sub new_c {
  my $class = shift;
  
  my $self = SPVM::Builder::Config->new(@_);
  
  # NativeAPI
  $self->ext('c');
  
  return $self;
}

sub new_c99 {
  my $class = shift;
  
  my $self = SPVM::Builder::Config->new_c(@_);
  
  # C99
  $self->set_std('c99');
  
  return $self;
}

sub new_gnu99 {
  my $class = shift;
  
  my $self = SPVM::Builder::Config->new_c(@_);
  
  # C99
  $self->set_std('gnu99');
  
  return $self;
}

sub new_cpp {
  my $class = shift;
  
  my $self = SPVM::Builder::Config->new(@_);
  
  # The compiler
  # [Memo]Free BSD don't have g++ in the environment clang++ exists.
  my $config_gcc_version = $Config{gccversion};
  if ($config_gcc_version =~ /\bclang\b/) {
    $self->cc('clang++');
    $self->ld('clang++');
  }
  else {
    $self->cc('g++');
    $self->ld('g++');
  }
  
  # NativeAPI
  $self->ext('cpp');
  
  return $self;
}

sub new_cpp11 {
  my $class = shift;
  
  my $self = SPVM::Builder::Config->new_cpp(@_);
  
  # C++11
  $self->set_std('c++11');
  
  return $self;
}

sub add_ccflags {
  my ($self, @ccflags) = @_;
  
  push @{$self->{ccflags}}, @ccflags;
}

sub add_include_dirs {
  my ($self, @include_dirs) = @_;
  
  push @{$self->{include_dirs}}, @include_dirs;
}

sub set_std {
  my ($self, $standard) = @_;
  
  my $ccflags = $self->ccflags;
  
  push @$ccflags, "-std=$standard";
  
  # Add -std=foo section
  $self->ccflags($ccflags);
  
  return $self;
}

sub add_ldflags {
  my ($self, @ldflags) = @_;
  
  push @{$self->{ldflags}}, @ldflags;
}

sub add_lib_dirs {
  my ($self, @lib_dirs) = @_;
  
  push @{$self->{lib_dirs}}, @lib_dirs;
}

sub add_libs {
  my ($self, @libs) = @_;
  
  push @{$self->{libs}}, @libs;
}

sub add_source_files {
  my ($self, @source_files) = @_;
  
  push @{$self->{source_files}}, @source_files;
}

sub add_resources {
  my ($self, @resources) = @_;
  
  push @{$self->{resources}}, @resources;
}

sub use { shift->add_resources(@_) }

sub add_static_libs {
  my ($self, @static_libs) = @_;
  
  my @static_lib_infos = map { {type => 'static', name => $_ } } @static_libs;
  
  $self->add_libs(@static_lib_infos);
}

sub add_dynamic_libs {
  my ($self, @dynamic_libs) = @_;
  
  my @dynamic_lib_infos = map { {type => 'dynamic', name => $_ } } @dynamic_libs;
  
  $self->add_libs(@dynamic_lib_infos);
}

sub to_hash {
  my ($self) = @_;
  
  my $hash = {%$self};
  
  return $hash;
}

sub search_lib_dirs_from_cc_info {
  my ($self) = @_;
  
  my $cc = $self->cc;
  
  my $cmd = "$cc -print-search-dirs";
  
  my $output = `$cmd`;
  
  my $lib_dirs_str;
  if ($output =~ /^libraries:\s+=(.+)/m) {
    $lib_dirs_str = $1;
  }
  
  my $sep = $Config{path_sep};
  
  my @lib_dirs;
  if (defined $lib_dirs_str) {
    @lib_dirs = split($sep, $lib_dirs_str);
  }
  
  return \@lib_dirs;
}

sub search_lib_dirs_from_config_libpth {
  my ($self) = @_;
  
  my $libpth = $Config{libpth};
  
  my @lib_dirs = split(/ +/, $libpth);
  
  return \@lib_dirs;
}

sub search_include_dirs_from_config_incpth {
  my ($self) = @_;
  
  my $incpth = $Config{incpth};
  
  my @include_dirs = split(/ +/, $incpth);
  
  return \@include_dirs;
}

sub get_include_dir {
  my ($self, $file) = @_;
  
  my $include_dir = $file;
  $include_dir =~ s|\.config$|.native/include|;
  
  return $include_dir;
}

sub get_src_dir {
  my ($self, $file) = @_;
  
  my $src_dir = $file;
  $src_dir =~ s|\.config$|.native/src|;
  
  return $src_dir;
}

sub get_lib_dir {
  my ($self, $file) = @_;
  
  my $lib_dir = $file;
  $lib_dir =~ s|\.config$|.native/lib|;
  
  return $lib_dir;
}

1;

=head1 NAME

SPVM::Builder::Config - Configurations of Compile and Link of Native Sources

=head1 DESCRIPTION

L<SPVM::Builder::Config> is configuration of c/c++ compile and link.

=head1 FIELDS

Fields.

=head2 ext

  my $ext = $config->ext;
  $config->ext($ext);

Get and set the extension of the SPVM native source.

The default is C<undef>.

B<Examples:>
  
  # Foo/Bar.c
  $config->ext('c');
  
  # Foo/Bar.cpp
  $config->ext('cpp');
  
=head2 cc

  my $cc = $config->cc;
  $config->cc($cc);

Get and set a compiler name. The default is the value of C<cc> of L<Config> module.

B<Examples:>
  
  # gcc
  $config->cc('gcc');
  
  # g++ for C++
  $config->cc('g++');
  
  # nvcc for CUDA/GUP
  $config->cc('nvcc');
  
  # cc that compiled this Perl
  use Config;
  $config->cc($Config{cc});

=head2 cc_each

  my $cc_each = $config->cc_each;
  $config->cc_each($cc_each);

Get and set a callback that returns the compiler name for each source file. The call back receives L<SPVM::Bulder::Config> object and each source file.

C<cc_each> takes precedence over C<cc>.

B<Examples:>
  
  $config->cc_each(sub {
    my ($config, $source_file) = @_;
    
    my $cc;
    # C source file
    if ($source_file =~ /\.c$/) {
      $cc = 'gcc';
    }
    # C++ source file
    elsif ($source_file =~ /\.cpp$/) {
      $cc = 'g++';
    }
    
    return $cc;
  });

=head2 include_dirs

  my $include_dirs = $config->include_dirs;
  $config->include_dirs($include_dirs);

Get and set header including directories of the compiler. This is same as C<-I> option of C<gcc>. 

The default value is "SPVM/Builder/include" of one up of directory that SPVM::Buidler::Config.pm is loaded.

At runtime, the "include" directory of the native module is added before C<include_dirs>.

=head2 ccflags

  my $ccflags = $config->ccflags;
  $config->ccflags($ccflags);

Get and set compiler flags.

B<Default:>

  # $Config{cccdlflags} has -fPIC.
  ['-fPIC']
  
  # Other
  []

=head2 ccflags_each

  my $ccflags_each = $config->ccflags_each;
  $config->ccflags_each($ccflags_each);

Get and set a callback that returns the compiler flags for each source file. The call back receives L<SPVM::Bulder::Config> object and each source file.

C<ccflags_each> takes precedence over C<ccflags>.

B<Examples:>
  
  $config->ccflags_each(sub {
    my ($config, $source_file) = @_;
    
    my $config_ccflags = $config->ccflags;
    
    my $ccflags = [];
    # C source file
    if ($source_file =~ /\.c$/) {
      $ccflags = ['-DFoo', @$config_ccflags];
    }
    # C++ source file
    elsif ($source_file =~ /\.cpp$/) {
      $ccflags = ['-DBar', @$config_ccflags];
    }
    
    return $ccflags;
  });

C<cc_each> takes precedence over C<cc>.

=head2 optimize

  my $optimize = $config->optimize;
  $config->optimize($optimize);

Get and set the option for optimization of the compiler.

The default is C<-O3>.

B<Examples:>

  $config->optimize('-O3');
  $config->optimize('-O2');
  $config->optimize('-g3 -O0');

=head2 source_files

  my $source_files = $config->source_files;
  $config->source_files($source_files);

Get and get source files. These sourceraries are linked by the compiler.

B<Examples:>

  $config->source_files(['foo.c', 'bar.c']);

=head2 ld

  my $ld = $config->ld;
  $config->ld($ld);

Get and set a linker. Default is C<ld> of L<Config> module.

=head2 lib_dirs

  my $lib_dirs = $config->lib_dirs;
  $config->lib_dirs($lib_dirs);

Get and set the directories that libraries are searched for by the linker. This is same as C<-L> option of C<gcc>.

B<Default:>

Windows
  
  The directory that perlxxx.dll exists
  
Not Windows

  empty list

=head2 libs

  my $libs = $config->libs;
  $config->libs($libs);

Get and set libraries. These libraries are linked by the linker.

If a dynamic link library is found from L<"lib_dirs">, this is linked. Otherwise if a static link library is found from L<"lib_dirs">, this is linked.

B<Examples:>

  $config->libs(['gsl', 'png']);

If you want to link only dynamic link library, you can use the following hash reference as the value of the element instead of the library name.

  {type => 'dynamic', name => 'gsl'}

If you want to link only static link library, you can use the following hash reference as the value of the element instead of the library name.

  {type => 'static', name => 'gsl'}

=head2 resources

  my $resources = $config->resources;
  $config->resources($resources);

Get and get resouce module names.

At runtime, each modules' native "include" directory is added before C<include_dirs>, and "lib" directory is added before C<lib_dirs>.

B<Examples:>

  $config->resources(['SPVM::Resouce::Zlib::V1_15']);
  
=head2 ldflags

  my ldflags = $config->ldflags;
  $config->ldflags(ldflags);

Get and set linker flags. The default is emtpy array reference.

B<Default:>

Windows

  ['-mdll', '-s']
  
Non-Windows

  ['-shared']

=head2 ld_optimize

  my $ld_optimize = $config->ld_optimize;
  $config->ld_optimize($ld_optimize);

Get and set the option for optimization of the linker such as C<-O3>, C<-O2>, C<-g3 -O0>.

The default is C<-O2>.

=head2 force

  my $force = $config->force;
  $config->force($force);

Get and set the flag to force compiles and links without caching.

=head2 quiet

  my $quiet = $config->quiet;
  $config->quiet($quiet);

Get and set the flag if the compiler and the linker output the results.

The default is C<1>.

=head1 Methods

=head2 new

  my $config = SPVM::Builder::Config->new;
  
Create L<SPVM::Builder::Config> object.

=head2 new_c
  
  my $config = SPVM::Builder::Config->new_c;

Create default build config with C settings. This is L<SPVM::Builder::Config> object.

If you want to use the specific C version, use C<set_std> method.

  $config->set_std('c99');

=head2 new_c99
  
  my $config = SPVM::Builder::Config->new_gnu99;

Create default build config with C99 settings. This is L<SPVM::Builder::Config> object.

=head2 new_cpp
  
  my $config = SPVM::Builder::Config->new_cpp;

Create default build config with C++ settings. This is L<SPVM::Builder::Config> object.

If you want to use the specific C++ version, use C<set_std> method.

  $config->set_std('c++11');

=head2 new_cpp11
  
  my $config = SPVM::Builder::Config->new_cpp11;

Create default build config with C++11 settings. This is L<SPVM::Builder::Config> object.

=head2 set_std

  $config->set_std($std);

Add the value that is converted to C<-std=$std> after the last element of C<ccflags> field.

B<Example:>

  $config->set_std('gnu99');

=head2 add_ccflags

  $config->add_ccflags(@ccflags);

Add values after the last element of C<ccflags> field.

=head2 add_ldflags

  $config->add_ldflags(@ldflags);

Add values after the last element of C<ldflags> field.

=head2 add_include_dirs

  $config->add_include_dirs(@include_dirs);

Add values after the last element of C<include_dirs> field.

=head2 add_lib_dirs

  $config->add_lib_dirs(@lib_dirs);

Add values after the last element of  C<lib_dirs> field.

=head2 add_source_files

  $config->add_source_files(@source_files);

Add the values after the last element of C<source_files> field.

=head2 add_libs

  $config->add_libs(@libs);

Add the values after the last element of C<libs> field.

B<Examples:>

  $config->add_libs('gsl');

=head2 add_static_libs

  $config->add_static_libs(@libs);

Add the values that each element is converted to the following hash reference after the last element of C<libs> field.

  {type => 'static', name => $lib}

B<Examples:>

  $config->add_static_libs('gsl');

=head2 add_dynamic_libs

  $config->add_dynamic_libs(@libs);

Add the values that each element is converted to the following hash reference after the last element of C<libs> field.

  {type => 'dynamic', name => $lib}

B<Examples:>

  $config->add_dynamic_libs('gsl');

=head2 use

  $config->use(@resources);

This method is the alias for L<"add_resources"> to improve user experiences.

B<Examples:>

  $config->use('SPVM::Resouce::Zlib::V1_15');

=head2 add_resources

  $config->add_resources(@resources);

Add the values after the last element of C<resources> field.

B<Examples:>

  $config->add_resources('SPVM::Resouce::Zlib::V1_15');

=head2 to_hash

  my $config = $config->to_hash;

Convert L<SPVM::Builder::Config> to a hash reference.

=head2 search_lib_dirs_from_cc_info

  my $lib_dirs = $config->search_lib_dirs_from_cc_info;

Get the library searching directories parsing the infomation the compiler has.

=head2 search_lib_dirs_from_config_libpth

  my $lib_dirs = $config->search_lib_dirs_from_config_libpth;

Get the library searching directories parsing C<libpth> of L<Config>.

=head2 search_include_dirs_from_config_incpth

  my $include_dirs = $config->search_include_dirs_from_config_incpth;

Get the header searching directories parsing C<incpth> of L<Config>.

=head2 sub get_include_dir

  my $include_dir = $config->get_include_dir(__FILE__);

Get the header include directory from the config file name.

=head2 get_src_dir

  my $src_dir = $config->get_src_dir(__FILE__);

Get the source directory from the config file name.

=head2 get_lib_dir

  my $lib_dir = $config->get_lib_dir(__FILE__);

Get the library directory from the config file name.

package SPVM::Builder::Config;

use strict;
use warnings;
use Config;

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

sub lddlflags {
  my $self = shift;
  if (@_) {
    $self->{lddlflags} = $_[0];
    return $self;
  }
  else {
    return $self->{lddlflags};
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

sub runtime_libs {
  my $self = shift;
  if (@_) {
    $self->{runtime_libs} = $_[0];
    return $self;
  }
  else {
    return $self->{runtime_libs};
  }
}

sub force_compile {
  my $self = shift;
  if (@_) {
    $self->{force_compile} = $_[0];
    return $self;
  }
  else {
    return $self->{force_compile};
  }
}

sub search_lib_dirs_cb {
  my $self = shift;
  if (@_) {
    $self->{search_lib_dirs_cb} = $_[0];
    return $self;
  }
  else {
    return $self->{search_lib_dirs_cb};
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

  # optimize
  unless (defined $self->{optimize}) {
    $self->optimize('-O3');
  }
  
  # force_compile
  unless (defined $self->{force_compile}) {
    $self->force_compile(0);
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
    
    # MinGW on Windows always create position independent codes, and if -fPIC is specified, the warning occurs.
    unless ($^O eq 'MSWin32') {
      push @default_ccflags, '-fPIC';
    }
    
    $self->add_ccflags(@default_ccflags);
  }
  
  # ld
  unless (defined $self->{ld}) {
    $self->ld($Config{ld});
  }

  # lib_dirs
  unless (defined $self->{lib_dirs}) {
    $self->lib_dirs([]);
    
    my @default_lib_dirs;
    
    # Library directories
    if ($^O eq 'MSWin32') {
      # Windows need perlxxx.dll(for example, perl534.dll) when creating dynamic links
      push @default_lib_dirs, $Config{bin};
    }
    
    $self->add_lib_dirs(@default_lib_dirs);
  }
  
  # lddlflags
  unless (defined $self->{lddlflags}) {
    $self->lddlflags([]);
    
    my @default_lddlflags;
    
    # Dynamic link options
    if ($^O eq 'MSWin32') {
      push @default_lddlflags, '-mdll -s';
    }
    else {
      push @default_lddlflags, '-shared';
    }
    $self->add_lddlflags(@default_lddlflags);
  }
  
  # runtime_libs
  unless (defined $self->{runtime_libs}) {
    $self->runtime_libs([]);
  }
  
  # search_lib_dirs_cb
  unless (defined $self->{search_lib_dirs_cb}) {
    $self->search_lib_dirs_cb(sub {
      my ($self) = @_;
      
      my $cc = $self->cc;
      
      my $cmd = "$cc -print-search-dirs";
      
      my $output = `$cmd`;
      
      my $lib_dirs_str;
      if ($output =~ /^libraries:\s+=(.+)/m) {
        $lib_dirs_str = $1;
      }
      
      my $sep;
      if ($^O eq 'MSWin32') {
        $sep = ';';
      }
      else {
        $sep = ':';
      }
      
      my @lib_dirs;
      if (defined $lib_dirs_str) {
        @lib_dirs = split($sep, $lib_dirs_str);
      }
      
      return \@lib_dirs;
    });
  }

  return $self;
}

sub new_c {
  my $class = shift;
  
  my $self = SPVM::Builder::Config->new;
  
  # NativeAPI
  $self->ext('c');
  
  return $self;
}

sub new_c99 {
  my $class = shift;
  
  my $self = SPVM::Builder::Config->new_c;
  
  # C99
  $self->set_std('c99');
  
  return $self;
}

sub new_cpp {
  my $class = shift;
  
  my $self = SPVM::Builder::Config->new;
  
  # CC
  $self->cc('g++');
  
  # LD
  $self->ld('g++');
  
  # NativeAPI
  $self->ext('cpp');
  
  return $self;
}

sub new_cpp11 {
  my $class = shift;
  
  my $self = SPVM::Builder::Config->new_cpp;
  
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

sub add_lddlflags {
  my ($self, @lddlflags) = @_;
  
  push @{$self->{lddlflags}}, @lddlflags;
}

sub add_lib_dirs {
  my ($self, @lib_dirs) = @_;
  
  push @{$self->{lib_dirs}}, @lib_dirs;
}

sub add_libs {
  my ($self, @libs) = @_;
  
  my @libs_lddlflags = map { "-l$_" } @libs;
  
  $self->add_lddlflags(@libs_lddlflags);
}

sub add_runtime_libs {
  my ($self, @runtime_libs) = @_;
  
  push @{$self->{runtime_libs}}, @runtime_libs;
}

sub to_hash {
  my ($self) = @_;
  
  my $hash = {%$self};
  
  return $hash;
}

sub search_lib_dirs {
  my ($self) = @_;
  
  $self->search_lib_dirs_cb->(@_);
}

1;

=head1 NAME

SPVM::Builder::Config - Configurations of Compile and Link of Native Sources

=head1 DESCRIPTION

L<SPVM::Builder::Config> is configuration of c/c++ compile and link.

=head1 FIELDS

Fields.

=head2 ext

  my $ext = $bconf->ext;
  $bconf->ext($ext);

Get and set the extension of native sources. This is used by the compiler.

The default is C<undef>.

B<Examples:>

  $bconf->ext('c');
  $bconf->ext('cpp');
  
=head2 cc

  my $cc = $bconf->cc;
  $bconf->cc($cc);

Get and set a compiler. The default is the value of C<cc> of L<Config> module.

=head2 include_dirs

  my $include_dirs = $bconf->include_dirs;
  $bconf->include_dirs($include_dirs);

Get and set header including directories of the compiler. This is same as C<-I> option of C<gcc>. 

The default value is "SPVM/Builder/include" of one up of directory that SPVM::Buidler::Config.pm is loaded.

=head2 ccflags

  my $ccflags = $bconf->ccflags;
  $bconf->ccflags($ccflags);

Get and set compiler flags. the default is a empty string.

=head2 optimize

  my $optimize = $bconf->optimize;

Get and set the option for optimization such as C<-O3>, C<-O2>, C<-g3 -O0>.

The default is C<-O3>.

=head2 ld

  my $ld = $bconf->ld;
  $bconf->ld($ld);

Get and set a linker. Default is C<ld> of L<Config> module.

=head2 lib_dirs

  my $lib_dirs = $bconf->lib_dirs;
  $bconf->lib_dirs($lib_dirs);

Get and set the directories libraries are load of the linker. This is same as C<-L> option of C<gcc>.

This value is used by Perl at runtime. Perl needs to load the dynamic link libraries at runtime.

B<Default:>

Windows
  
  The directory that perlxxx.dll exists
  
Not Windows

  empty list

=head2 lddlflags

  my lddlflags = $bconf->lddlflags;
  $bconf->lddlflags(lddlflags);

Get and set linker flags. 

B<Default:>

Windows

  "-mdll -s"
  
Non-Windows

  "-shared"

=head2 runtime_libs

  my $runtime_libs = $bconf->runtime_libs;
  $bconf->runtime_libs($runtime_libs);

Get and get the directories libraries are load in runtime by Perl.

If the library is dynamic link library, you must specify this option to load this at runtime.

=head2 force_compile

  my $force_compile = $bconf->force_compile;
  $bconf->force_compile($force_compile);

Get and set the flag to force compiles and links without caching.

=head2 quiet

  my $quiet = $bconf->quiet;
  $bconf->quiet($quiet);

Get and set the flag if the compiler and the linker output the results.

The default is C<1>.

=head1 Methods

=head2 new

  my $bconf = SPVM::Builder::Config->new;
  
Create L<SPVM::Builder::Config> object.

=head2 new_c
  
  my $bconf = SPVM::Builder::Config->new_c;

Create default build config with C settings. This is L<SPVM::Builder::Config> object.

If you want to use the specific C version, use C<set_std> method.

  $bconf->set_std('c99');

=head2 new_c99
  
  my $bconf = SPVM::Builder::Config->new_c99;

Create default build config with C99 settings. This is L<SPVM::Builder::Config> object.

=head2 new_cpp
  
  my $bconf = SPVM::Builder::Config->new_cpp;

Create default build config with C++ settings. This is L<SPVM::Builder::Config> object.

If you want to use the specific C++ version, use C<set_std> method.

  $bconf->set_std('c++11');

=head2 new_cpp11
  
  my $bconf = SPVM::Builder::Config->new_cpp11;

Create default build config with C++11 settings. This is L<SPVM::Builder::Config> object.

=head2 set_std

  $bconf->set_std($std);

Add the value that is converted to C<-std=$std> after the last element of C<ccflags> field.

B<Example:>

  $bconf->set_std('gnu99');

=head2 add_ccflags

  $bconf->add_ccflags(@ccflags);

Add values after the last element of C<ccflags> field.

=head2 add_lddlflags

  $bconf->add_lddlflags(@lddlflags);

Add values after the last element of C<lddlflags> field.

=head2 add_include_dirs

  $bconf->add_include_dirs(@include_dirs);

Add values after the last element of C<include_dirs> field.

=head2 add_lib_dirs

  $bconf->add_lib_dirs(@lib_dirs);

Add values after the last element of  C<lib_dirs> field.

=head2 add_libs

  $bconf->add_libs(@libs);

Add values that each value is converted to C<-l$lib"> after the last element of C<lddlflags> field.

B<Examples:>

  $bconf->add_libs('gsl');

=head2 add_runtime_libs

  $bconf->add_runtime_libs(@libs);

Add values after the last element of  C<runtime_libs> field.

B<Examples:>

  $bconf->add_runtime_libs('gsl');

=head2 to_hash

  my $config = $bconf->to_hash;

Convert L<SPVM::Builder::Config> to a hash reference.

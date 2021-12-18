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
  
  my $self = {};
  
  $self->{include_dirs} = [];

  $self->{lib_dirs} = [];

  $self->{runtime_libs} = [];
  
  $self->{quiet} = 1;

  $self->{std} = '';

  bless $self, $class;
  
  # cc
  $self->cc($Config{cc});

  # ccflags
  my $ccflags = [];
  
  # MinGW on Windows always create position independent codes, and if -fPIC is specified, the warning occurs.
  unless ($^O eq 'MSWin32') {
    push @$ccflags, '-fPIC';
  }

  $self->ccflags($ccflags);
  
  # ld
  $self->ld($Config{ld});
  
  # Library directories
  if ($^O eq 'MSWin32') {
    # Windows need perlxxx.dll(for example, perl534.dll) when creating dynamic links
    $self->push_lib_dirs($Config{bin});
  }
  
  # lddlflags
  my $lddlflags = [];
  
  # Dynamic link options
  if ($^O eq 'MSWin32') {
    push @$lddlflags, '-mdll -s';
  }
  else {
    push @$lddlflags, '-shared';
  }
  $self->lddlflags($lddlflags);

  # SPVM::Builder::Config directory
  my $spvm_builder_config_dir = $INC{"SPVM/Builder/Config.pm"};

  # SPVM::Builder directory
  my $spvm_builder_dir = $spvm_builder_config_dir;
  $spvm_builder_dir =~ s/\/Config\.pm$//;

  # Add SPVM include directory
  my $spvm_include_dir = $spvm_builder_dir;
  $spvm_include_dir .= '/include';
  $self->unshift_include_dirs($spvm_include_dir);

  # Optimize
  $self->optimize('-O3');
  
  # Get cc library directories callback
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

sub append_ccflags {
  my ($self, $new_ccflags) = @_;
  
  my $ccflags = $self->{ccflags};
  
  push @$ccflags, $new_ccflags;
  
  $self->{ccflags} = $ccflags;
  
  return $self;
}

sub unshift_include_dirs {
  my ($self, @include_dirs) = @_;
  
  unshift @{$self->{include_dirs}}, @include_dirs;
}

sub push_include_dirs {
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

sub append_lddlflags {
  my ($self, $new_lddlflags) = @_;
  
  my $lddlflags = $self->{lddlflags};
  
  push @$lddlflags, $new_lddlflags;
  
  $self->{lddlflags} = $lddlflags;
  
  return $self;
}

sub push_lib_dirs {
  my ($self, @lib_dirs) = @_;
  
  push @{$self->{lib_dirs}}, @lib_dirs;
}

sub unshift_lib_dirs {
  my ($self, @lib_dirs) = @_;
  
  unshift @{$self->{lib_dirs}}, @lib_dirs;
}

sub push_runtime_libs {
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

L<Builder::Config|SPVM::Builder::Config> is configuration of c/c++ compile and link.

=head1 FIELDS

Fields.

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
  
Create L<Builder::Config|SPVM::Builder::Config> object.

=head2 new_c
  
  my $bconf = SPVM::Builder::Config->new_c;

Create default build config with C settings. This is L<Builder::Config|SPVM::Builder::Config> object.

If you want to use the specific C version, use C<set_std> method.

  $bconf->set_std('c99');

=head2 new_c99
  
  my $bconf = SPVM::Builder::Config->new_c99;

Create default build config with C99 settings. This is L<Builder::Config|SPVM::Builder::Config> object.

=head2 new_cpp
  
  my $bconf = SPVM::Builder::Config->new_cpp;

Create default build config with C++ settings. This is L<Builder::Config|SPVM::Builder::Config> object.

If you want to use the specific C++ version, use C<set_std> method.

  $bconf->set_std('c++11');

=head2 new_cpp11
  
  my $bconf = SPVM::Builder::Config->new_cpp11;

Create default build config with C++11 settings. This is L<Builder::Config|SPVM::Builder::Config> object.

=head2 to_hash

  my $config = $bconf->to_hash;

Convert L<SPVM::Builder::Config> to a hash reference.

=head2 set_std

  $bconf->set_std('gnu99');

Set C<-std> value.

Internally, add add C<-std=VALUE> after C<ccflags>.

=head2 append_ccflags

  $bconf->append_ccflags($ccflags);

Add new C<ccflags> after current C<ccflags>.

=head2 append_lddlflags

  $bconf->append_lddlflags($lddlflags);

Add new C<lddlflags> after current C<lddlflags>.
=head2 unshift_include_dirs

  $bconf->unshift_include_dirs($include_dir1, $include_dir2, ...);

Add a element before the first element of C<include_dirs> option.

=head2 push_include_dirs

  $bconf->push_include_dirs($include_dir1, $include_dir2, ...);

Add a element after the last element of C<include_dirs> option.

=head2 unshift_lib_dirs

  $bconf->unshift_lib_dirs($lib_dir1, $lib_dir2, ...);

Add a element before the first element of C<lib_dirs> option.

=head2 push_lib_dirs

  $bconf->push_lib_dirs($lib_dir1, $lib_dir2, ...);

Add a element after the last element of C<lib_dirs> option.

=head2 push_runtime_libs

  $bconf->push_runtime_libs($lib1, $lib2, ...);

Add a library after the last element of C<runtime_libs> option.

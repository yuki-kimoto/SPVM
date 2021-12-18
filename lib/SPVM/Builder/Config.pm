package SPVM::Builder::Config;

use strict;
use warnings;
use Config;

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
  $self->set_cc($Config{cc});

  # ccflags
  my $ccflags = '';
  
  # MinGW on Windows always create position independent codes, and if -fPIC is specified, the warning occurs.
  unless ($^O eq 'MSWin32') {
    $ccflags .= '-fPIC';
  }

  $self->set_ccflags($ccflags);
  
  # ld
  $self->set_ld($Config{ld});
  
  # Library directories
  if ($^O eq 'MSWin32') {
    # Windows need perlxxx.dll(for example, perl534.dll) when creating dynamic links
    $self->push_lib_dirs($Config{bin});
  }
  
  # lddlflags
  my $lddlflags = '';
  
  # Dynamic link options
  if ($^O eq 'MSWin32') {
    $lddlflags .= '-mdll -s';
  }
  else {
    $lddlflags .= '-shared';
  }
  $self->set_lddlflags($lddlflags);

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
  $self->set_optimize('-O3');
  
  # Get cc library directories callback
  $self->set_search_lib_dirs_cb(sub {
    my ($self) = @_;
    
    my $cc = $self->get_cc;
    
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
  $self->set_ext('c');
  
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
  $self->set_cc('g++');
  
  # LD
  $self->set_ld('g++');
  
  # NativeAPI
  $self->set_ext('cpp');
  
  return $self;
}

sub new_cpp11 {
  my $class = shift;
  
  my $self = SPVM::Builder::Config->new_cpp;
  
  # C++11
  $self->set_std('c++11');
  
  return $self;
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

sub get_ext {
  my ($self, $ext) = @_;
  
  return $self->{ext};
}

sub set_ext {
  my ($self, $ext) = @_;
  
  $self->{ext} = $ext;
  
  return $self;
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

sub get_quiet {
  my ($self, $quiet) = @_;
  
  return $self->{quiet};
}

sub set_quiet {
  my ($self, $quiet) = @_;
  
  $self->{quiet} = $quiet;
  
  return $self;
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

sub get_cc {
  my ($self, $cc) = @_;
  
  return $self->{cc};
}

sub set_cc {
  my ($self, $cc) = @_;
  
  return $self->{cc} = $cc;
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

sub get_ccflags {
  my ($self) = @_;
  
  return $self->{ccflags};
}

sub set_ccflags {
  my ($self, $ccflags) = @_;
  
  $self->{ccflags} = $ccflags;
  
  return $self;
}

sub append_ccflags {
  my ($self, $new_ccflags) = @_;
  
  my $ccflags = $self->{ccflags};
  
  $ccflags .= " $new_ccflags";
  
  $self->{ccflags} = $ccflags;
  
  return $self;
}

sub prepend_ccflags {
  my ($self, $new_ccflags) = @_;
  
  my $ccflags = $self->{ccflags};
  
  $ccflags = "$new_ccflags $ccflags";
  
  $self->{ccflags} = $ccflags;
  
  return $self;
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

sub get_optimize {
  my ($self, $optimize) = @_;
  
  return $self->{optimize};
}

sub set_optimize {
  my ($self, $optimize) = @_;
  
  return $self->{optimize} = $optimize;
}

sub get_include_dirs {
  my ($self, $include_dirs) = @_;
  
  return $self->{include_dirs};
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

sub set_include_dirs {
  my ($self, $include_dirs) = @_;
  
  $self->{include_dirs} = $include_dirs;
  
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

sub set_std {
  my ($self, $standard) = @_;
  
  my $ccflags = $self->get_ccflags;
  
  $ccflags .= " -std=$standard";
  
  # Add -std=foo section
  $self->set_ccflags($ccflags);
  
  return $self;
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

sub get_ld {
  my ($self, $ld) = @_;
  
  return $self->{ld};
}

sub set_ld {
  my ($self, $ld) = @_;
  
  return $self->{ld} = $ld;
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

sub get_lddlflags {
  my ($self) = @_;
  
  return $self->{lddlflags};
}

sub set_lddlflags {
  my ($self, $lddlflags) = @_;
  
  $self->{lddlflags} = $lddlflags;
  
  return $self;
}

sub append_lddlflags {
  my ($self, $new_lddlflags) = @_;
  
  my $lddlflags = $self->{lddlflags};
  
  $lddlflags .= " $new_lddlflags";
  
  $self->{lddlflags} = $lddlflags;
  
  return $self;
}

sub prepend_lddlflags {
  my ($self, $new_lddlflags) = @_;
  
  my $lddlflags = $self->{lddlflags};
  
  $lddlflags = "$new_lddlflags $lddlflags";
  
  $self->{lddlflags} = $lddlflags;
  
  return $self;
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

sub get_lib_dirs {
  my ($self, $lib_dirs) = @_;
  
  return $self->{lib_dirs};
}

sub set_lib_dirs {
  my ($self, $lib_dirs) = @_;
  
  $self->{lib_dirs} = $lib_dirs;
  
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

sub get_runtime_libs {
  my ($self) = @_;
  
  return $self->{runtime_libs};
}

sub set_runtime_libs {
  my ($self, $runtime_libs) = @_;
  
  $self->{runtime_libs} = $runtime_libs;
  
  return $self;
}

sub push_runtime_libs {
  my ($self, @runtime_libs) = @_;
  
  push @{$self->{runtime_libs}}, @runtime_libs;
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

sub get_force_compile {
  my ($self, $force_compile) = @_;
  
  return $self->{force_compile};
}

sub set_force_compile {
  my ($self, $force_compile) = @_;
  
  $self->{force_compile} = $force_compile;
  
  return $self;
}

sub to_hash {
  my ($self) = @_;
  
  my $hash = {%$self};
  
  return $hash;
}

sub search_lib_dirs {
  my ($self) = @_;
  
  $self->get_search_lib_dirs_cb->(@_);
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

sub get_search_lib_dirs_cb {
  my ($self, $cb) = @_;
  
  return $self->{search_lib_dirs_cb};
}

sub set_search_lib_dirs_cb {
  my ($self, $cb) = @_;
  
  $self->{search_lib_dirs_cb} = $cb;
}

1;

=head1 NAME

SPVM::Builder::Config - Configurations of Compile and Link of Native Sources

=head1 DESCRIPTION

L<Builder::Config|SPVM::Builder::Config> is configuration of c/c++ compile and link.

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

=head2 get_config

  my $cc = $bconf->get_config('cc');

Get a config value.

=head2 set_config

  $bconf->set_config(cc => $cc);

Set a config value.

=head2 set_std

  $bconf->set_std('gnu99');

Set C<-std> value.

Internally, add add C<-std=VALUE> after C<ccflags>.

=head2 set_cc

  $bconf->set_cc($cc);

Set C<cc>.

=head2 get_cc

  my $cc = $bconf->get_cc;

Get C<cc>.

=head2 set_cc

  $bconf->set_cc($cc);

Set C<cc>.

=head2 get_cc

  my $cc = $bconf->get_cc;

Get C<cc>. Default is the C<cc> value of L<Config> module.

=head2 get_ccflags

  my $ccflags = $bconf->get_ccflags;

Get C<ccflags> option using C<get_config> method.

C<ccflags> option is passed to C<config> option of L<ExtUtils::CBuilder> C<new> method.

Default is empty string.

=head2 set_ccflags

  $bconf->set_ccflags($ccflags);

Set C<ccflags> using C<set_config> method.

See C<get_ccflags> method about C<ccflags> option.

=head2 append_ccflags

  $bconf->append_ccflags($ccflags);

Add new C<ccflags> after current C<ccflags> using C<get_config> and C<set_config> method.

See C<get_ccflags> method about C<ccflags> option.

=head2 prepend_ccflags

  $bconf->prepend_ccflags($ccflags);

Add new C<ccflags> before current C<ccflags> using C<get_config> and C<set_config> method.

See C<get_ccflags> method about C<ccflags> option.

=head2 get_optimize

  my $optimize = $bconf->get_optimize;

Get C<optimize> option using C<get_config> method.

C<optimize> option is passed to C<config> option of L<ExtUtils::CBuilder> C<new> method 

Default is C<-O3>.

=head2 set_optimize

  $bconf->set_optimize($optimize);

Set C<optimize> using C<set_config> method.

See C<get_optimize> method about C<optimize> option.

=head2 set_ld

  $bconf->set_ld($ld);

Set C<ld>.

=head2 get_ld

  my $ld = $bconf->get_ld;

Get C<ld>. Default is the C<ld> value of L<Config> module.

=head2 get_lddlflags

  my $lddlflags = $bconf->get_lddlflags;

Get C<lddlflags> option using C<get_config> method.

C<lddlflags> option is passed to C<config> option of L<ExtUtils::CBuilder> C<new> method.

B<Default:>

Windows

  "-mdll -s"
  
Non-Windows

  "-shared"

=head2 set_lddlflags

  $bconf->set_lddlflags($lddlflags);

Set C<lddlflags> using C<set_config> method.

See C<get_lddlflags> method about C<lddlflags> option.

=head2 append_lddlflags

  $bconf->append_lddlflags($lddlflags);

Add new C<lddlflags> after current C<lddlflags> using C<get_config> and C<set_config> method.

See C<get_lddlflags> method about C<lddlflags> option.

=head2 prepend_lddlflags

  $bconf->prepend_lddlflags($lddlflags);

Add new C<lddlflags> before current C<lddlflags> using C<get_config> and C<set_config> method.

See C<get_lddlflags> method about C<lddlflags> option.

=head2 get_include_dirs

  my $include_dirs = $bconf->get_include_dirs;

Get C<include_dirs> option. This option is array refernce.

C<include_dirs> option is used by C<compile> method of L<Builder::CC|SPVM::Builder::CC> to set -I<inculde_dir>.

Default is "SPVM/Builder/include" of one up of directory that SPVM::Buidler::Config.pm is loaded.

=head2 set_include_dirs

  $bconf->set_include_dirs($include_dirs);

Set C<include_dirs> option. This option is array refernce.

See C<get_include_dirs> method about C<include_dirs> option.

=head2 unshift_include_dirs

  $bconf->unshift_include_dirs($include_dir1, $include_dir2, ...);

Add a element before the first element of C<include_dirs> option.

See C<get_lib_dirs> method about C<lib_dirs> option.

=head2 push_include_dirs

  $bconf->push_include_dirs($include_dir1, $include_dir2, ...);

Add a element after the last element of C<include_dirs> option.

See C<get_lib_dirs> method about C<lib_dirs> option.

=head2 get_lib_dirs

  my $lib_dirs = $bconf->get_lib_dirs;

Get C<lib_dirs> option. This option is array refernce.

C<lib_dirs> option is used by C<compile> method of L<Builder::CC|SPVM::Builder::CC> to set -L<lib_dir>.

Default is emplty list.

=head2 set_lib_dirs

  $bconf->set_lib_dirs($lib_dirs);

Set C<lib_dirs> option. This option is array refernce.

See C<get_lib_dirs> method about C<lib_dirs> option.

=head2 unshift_lib_dirs

  $bconf->unshift_lib_dirs($lib_dir1, $lib_dir2, ...);

Add a element before the first element of C<lib_dirs> option.

See C<get_lib_dirs> method about C<lib_dirs> option.

=head2 push_lib_dirs

  $bconf->push_lib_dirs($lib_dir1, $lib_dir2, ...);

Add a element after the last element of C<lib_dirs> option.

See C<get_lib_dirs> method about C<lib_dirs> option.

=head2 get_runtime_libs

  my $runtime_libs = $bconf->get_runtime_libs;

Get C<runtime_libs> option. This option is array refernce.

C<runtime_libs> option is used to load the library at runtime. If the library is dynamic link library, you must specify this option to load this at runtime.

Don't add prefix '-l' or 'lib' before library name. 'gsl' is valid. 'libgsl', '-lgsl' is invalid.

=head2 set_runtime_libs

  $bconf->set_runtime_libs($runtime_libs);

Set C<runtime_libs> option. This option is array refernce.

See L<"get_runtime_libs"> method about C<runtime_libs> option.

=head2 push_runtime_libs

  $bconf->push_runtime_libs($lib1, $lib2, ...);

Add a library after the last element of C<runtime_libs> option.

See L<"get_runtime_libs"> method about C<runtime_libs> option.

=head2 get_force_compile

  my $force_compile = $bconf->get_force_compile;

Get C<force_compile> option.

C<force_compile> option is used by C<compile> method of L<Builder::CC|SPVM::Builder::CC> to determine whether the method should force compilation of source codes without cache.

=head2 set_force_compile

  $bconf->set_force_compile($force_compile);

Set C<force_compile> option.

See C<get_force_compile> method about C<force_compile> option.

=head2 get_quiet

  my $quiet = $bconf->get_quiet;

Get C<quiet> option.

C<quiet> option is used by C<compile> method of L<Builder::CC|SPVM::Builder::CC> to determine whether the method output compiler messages , default to C<1>.

=head2 set_quiet

  $bconf->set_quiet($quiet);

Set C<quiet> option.

See C<get_quiet> method about C<quiet> option.

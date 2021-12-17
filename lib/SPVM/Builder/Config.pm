package SPVM::Builder::Config;

use strict;
use warnings;
use Config;

sub new {
  my $class = shift;
  
  my $self = {};
  
  $self->{config} = {};
  
  $self->{include_dirs} = [];

  $self->{lib_dirs} = [];

  $self->{runtime_libs} = [];
  
  $self->{quiet} = 1;

  $self->{ccflags} = '';
  
  $self->{std} = '';

  bless $self, $class;

  # Use default config
  my $default_config = {%Config};
  $self->replace_all_config($default_config);
  
  # ccflags
  my $ccflags = '';
  
  # MinGW on Windows always create position independent codes, and if -fPIC is specified, the warning occurs.
  unless ($^O eq 'MSWin32') {
    $ccflags .= '-fPIC';
  }

  $self->set_ccflags($ccflags);

  # SPVM::Builder::Config directory
  my $spvm_builder_config_dir = $INC{"SPVM/Builder/Config.pm"};

  # SPVM::Builder directory
  my $spvm_builder_dir = $spvm_builder_config_dir;
  $spvm_builder_dir =~ s/\/Config\.pm$//;

  # Add SPVM include directory
  my $spvm_include_dir = $spvm_builder_dir;
  $spvm_include_dir .= '/include';
  $self->unshift_include_dirs($spvm_include_dir);

  # Remove and get lib dir from lddlflags
  my @lib_dirs_in_lddlflags = $self->_remove_lib_dirs_from_lddlflags;
  $self->unshift_lib_dirs(@lib_dirs_in_lddlflags);

  # Optimize
  $self->set_optimize('-O3');

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

sub get_ext {
  my ($self, $ext) = @_;
  
  return $self->{ext};
}

sub set_ext {
  my ($self, $ext) = @_;
  
  $self->{ext} = $ext;
  
  return $self;
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

sub get_config {
  my ($self, $name) = @_;
  
  return $self->{config}{$name};
}

sub set_config {
  my ($self, $name, $value) = @_;
  
  $self->{config}{$name} = $value;
  
  return $self;
}

sub get_cc {
  my ($self, $cc) = @_;
  
  return $self->get_config('cc');
}

sub set_cc {
  my ($self, $cc) = @_;
  
  return $self->set_config(cc => $cc);
}

sub get_ccflags {
  my ($self) = @_;
  
  return $self->get_config('ccflags');
}

sub set_ccflags {
  my ($self, $ccflags) = @_;
  
  $self->set_config(ccflags => $ccflags);
  
  return $self;
}

sub append_ccflags {
  my ($self, $new_ccflags) = @_;
  
  my $ccflags = $self->get_config('ccflags');
  
  $ccflags .= " $new_ccflags";
  
  $self->set_config('ccflags' => $ccflags);
  
  return $self;
}

sub prepend_ccflags {
  my ($self, $new_ccflags) = @_;
  
  my $ccflags = $self->get_config('ccflags');
  
  $ccflags = "$new_ccflags $ccflags";
  
  $self->set_config('ccflags' => $ccflags);
  
  return $self;
}

sub get_cccdlflags {
  my ($self) = @_;
  
  return $self->get_config('cccdlflags');
}

sub set_cccdlflags {
  my ($self, $cccdlflags) = @_;
  
  $self->set_config(cccdlflags => $cccdlflags);
  
  return $self;
}

sub append_cccdlflags {
  my ($self, $new_cccdlflags) = @_;
  
  my $cccdlflags = $self->get_config('cccdlflags');
  
  $cccdlflags .= " $new_cccdlflags";
  
  $self->set_config('cccdlflags' => $cccdlflags);
  
  return $self;
}

sub prepend_cccdlflags {
  my ($self, $new_cccdlflags) = @_;
  
  my $cccdlflags = $self->get_config('cccdlflags');
  
  $cccdlflags = "$new_cccdlflags $cccdlflags";
  
  $self->set_config('cccdlflags' => $cccdlflags);
  
  return $self;
}

sub get_archlibexp {
  my ($self) = @_;
  
  return $self->get_config('archlibexp');
}

sub set_archlibexp {
  my ($self, $archlibexp) = @_;
  
  $self->set_config(archlibexp => $archlibexp);
  
  return $self;
}

sub get_optimize {
  my ($self, $optimize) = @_;
  
  return $self->get_config('optimize');
}

sub set_optimize {
  my ($self, $optimize) = @_;
  
  return $self->set_config(optimize => $optimize);
}

sub get_include_dirs {
  my ($self, $include_dirs) = @_;
  
  return $self->{include_dirs};
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

sub get_std {
  my ($self) = @_;
  
  return $self->{std};
}

sub set_std {
  my ($self, $std) = @_;
  
  $self->{std} = $std;
}

sub get_ld {
  my ($self, $ld) = @_;
  
  return $self->get_config('ld');
}

sub set_ld {
  my ($self, $ld) = @_;
  
  return $self->set_config(ld => $ld);
}

sub get_lddlflags {
  my ($self) = @_;
  
  return $self->get_config('lddlflags');
}

sub set_lddlflags {
  my ($self, $lddlflags) = @_;
  
  $self->set_config(lddlflags => $lddlflags);
  
  return $self;
}

sub append_lddlflags {
  my ($self, $new_lddlflags) = @_;
  
  my $lddlflags = $self->get_config('lddlflags');
  
  $lddlflags .= " $new_lddlflags";
  
  $self->set_config('lddlflags' => $lddlflags);
  
  return $self;
}

sub prepend_lddlflags {
  my ($self, $new_lddlflags) = @_;
  
  my $lddlflags = $self->get_config('lddlflags');
  
  $lddlflags = "$new_lddlflags $lddlflags";
  
  $self->set_config('lddlflags' => $lddlflags);
  
  return $self;
}

sub get_shrpenv {
  my ($self) = @_;
  
  return $self->get_config('shrpenv');
}

sub set_shrpenv {
  my ($self, $shrpenv) = @_;
  
  $self->set_config(shrpenv => $shrpenv);
  
  return $self;
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

sub unshift_lib_dirs {
  my ($self, @lib_dirs) = @_;
  
  unshift @{$self->{lib_dirs}}, @lib_dirs;
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

sub unshift_runtime_libs {
  my ($self, @runtime_libs) = @_;
  
  unshift @{$self->{runtime_libs}}, @runtime_libs;
}

sub push_runtime_libs {
  my ($self, @runtime_libs) = @_;
  
  push @{$self->{runtime_libs}}, @runtime_libs;
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

sub replace_all_config {
  my ($self, $config) = @_;
  
  $self->{config} = $config;
}

sub to_hash {
  my ($self) = @_;
  
  my $hash_config = {%{$self->{config}}};
  
  return $hash_config;
}

sub _remove_lib_dirs_from_lddlflags {
  my ($self) = @_;
  
  my $lddlflags = $self->get_lddlflags;
  
  my @parts = split(/ +/, $lddlflags);
  
  my @rest_parts;
  my @lib_dirs;
  for my $part (@parts) {
    if ($part =~ /^-L(.*)/) {
      my $lib_dir = $1;
      push @lib_dirs, $lib_dir;
    }
    else {
      push @rest_parts, $part;
    }
  }
  
  my $rest_lddlflags = join(' ', @rest_parts);
  
  $self->set_lddlflags($rest_lddlflags);
  
  return @lib_dirs;
}

1;

=head1 NAME

SPVM::Builder::Config - build config

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

=head2 replace_all_config

  my $config = {cc => 'g++', ld => 'g++'};
  $bconf->replace_all_config($config);

Replace all config.

All of old configs is removed and added new config.

=head2 to_hash

  my $config = $bconf->to_hash;

Convert configs to hash reference.

=head2 get_config

  my $cc = $bconf->get_config('cc');

Get a config value.

=head2 set_config

  $bconf->set_config(cc => $cc);

Set a config value.

=head2 set_std

  $bconf->set_std('gnu99');

Set C<std>.

Internally, remove C<-std=old> if exists and add C<-std=new> after C<ccflags>.

=head2 delete_std

  $bconf->delete_std;

Delete C<std>.

Internally, remove C<-std=old> if exists from C<ccflags>.

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

Get C<cc>.

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

=head2 get_cccdlflags

  my $cccdlflags = $bconf->get_cccdlflags;

Get C<cccdlflags> option using C<get_config> method.

C<cccdlflags> option is passed to C<config> option of L<ExtUtils::CBuilder> C<new> method.

Default is copied from $Config{cccdlflags}.

=head2 set_cccdlflags

  $bconf->set_cccdlflags($cccdlflags);

Set C<cccdlflags> using C<set_config> method.

See C<get_cccdlflags> method about C<cccdlflags> option.

=head2 append_cccdlflags

  $bconf->append_cccdlflags($cccdlflags);

Add new C<cccdlflags> after current C<cccdlflags> using C<get_config> and C<set_config> method.

See C<get_cccdlflags> method about C<cccdlflags> option.

=head2 prepend_cccdlflags

  $bconf->prepend_cccdlflags($cccdlflags);

Add new C<cccdlflags> before current C<cccdlflags> using C<get_config> and C<set_config> method.

See C<get_cccdlflags> method about C<cccdlflags> option.

=head2 get_archlibexp

  my $archlibexp = $bconf->get_archlibexp;

Get C<archlibexp> option using C<get_config> method.

C<archlibexp> option is passed to C<config> option of L<ExtUtils::CBuilder> C<new> method.

Default is copied from $Config{archlibexp}.

=head2 set_archlibexp

  $bconf->set_archlibexp($archlibexp);

Set C<archlibexp> using C<set_config> method.

See C<get_archlibexp> method about C<archlibexp> option.

=head2 get_optimize

  my $optimize = $bconf->get_optimize;

Get C<optimize> option using C<get_config> method.

C<optimize> option is passed to C<config> option of L<ExtUtils::CBuilder> C<new> method 

Default is copied from $Config{optimize}.

=head2 set_optimize

  $bconf->set_optimize($optimize);

Set C<optimize> using C<set_config> method.

See C<get_optimize> method about C<optimize> option.

=head2 set_ld

  $bconf->set_ld($ld);

Set C<ld>.

=head2 get_ld

  my $ld = $bconf->get_ld;

Get C<ld>.

=head2 get_lddlflags

  my $lddlflags = $bconf->get_lddlflags;

Get C<lddlflags> option using C<get_config> method.

C<lddlflags> option is passed to C<config> option of L<ExtUtils::CBuilder> C<new> method.

Default is copied from $Config{lddlflags}.

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

=head2 get_shrpenv

  my $shrpenv = $bconf->get_shrpenv;

Get C<shrpenv> option using C<get_config> method.

C<shrpenv> option is passed to C<config> option of L<ExtUtils::CBuilder> C<new> method.

Default is copied from $Config{shrpenv}.

=head2 set_shrpenv

  $bconf->set_shrpenv($shrpenv);

Set C<shrpenv> using C<set_config> method.

See C<get_shrpenv> method about C<shrpenv> option.

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

Default is the values of -L<lib_dir> in $Config{lddlflags}.

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

=head2 unshift_runtime_libs

  $bconf->unshift_runtime_libs($lib1, $lib2, ...);

Add a library before the first element of C<runtime_libs> option.

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

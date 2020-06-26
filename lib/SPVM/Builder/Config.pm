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

  $self->{libs} = [];
  
  $self->{quiet} = 1;

  $self->{extra_compiler_flags} = '';
  
  $self->{extra_linker_flags} = '';
  
  $self->{quiet} = 1;
  
  bless $self, $class;

  # Use default config
  my $default_config = {%Config};
  $self->replace_all_config($default_config);

  # Remove and get include dir from ccflags
  my @ccflags_include_dirs = $self->_remove_include_dirs_from_ccflags;
  
  # Add ccflags include dir
  $self->add_include_dirs(@ccflags_include_dirs);
  
  # SPVM::Builder::Config directory
  my $spvm_builder_config_dir = $INC{"SPVM/Builder/Config.pm"};

  # SPVM::Builder directory
  my $spvm_builder_dir = $spvm_builder_config_dir;
  $spvm_builder_dir =~ s/\/Config\.pm$//;

  # Add SPVM include directory to ccflags
  my $spvm_include_dir = $spvm_builder_dir;
  $spvm_include_dir .= '/include';
  $self->add_include_dirs($spvm_include_dir);

  # Remove and get lib dir from lddlflags
  my @lib_dirs_in_lddlflags = $self->_remove_lib_dirs_from_lddlflags;
  $self->add_lib_dirs(@lib_dirs_in_lddlflags);

  return $self;
}

sub new_c99 {
  my $class = shift;
  
  my $self = SPVM::Builder::Config->new;
  
  # C99
  $self->set_std('c99');
  
  # Optimize
  $self->set_optimize('-O3');
  
  # NativeAPI
  $self->set_ext('c');
  
  # I want to print warnings, but if gcc version is different, can't suppress no needed warning message.
  # so I dicide not to print warning in release version
  if ($ENV{SPVM_TEST_ENABLE_WARNINGS}) {
    $self->add_extra_compiler_flags("-Wall -Wextra -Wno-unused-label -Wno-unused-function -Wno-unused-label -Wno-unused-parameter -Wno-unused-variable -Wno-missing-field-initializers");
  }
  
  return $self;
}

sub new_cpp {
  my $class = shift;
  
  my $self = SPVM::Builder::Config->new;
  
  # Optimize
  $self->set_optimize('-O3');
  
  # CC
  $self->set_cc('g++');
  
  # LD
  $self->set_ld('g++');
  
  # NativeAPI
  $self->set_ext('cpp');
  
  return $self;
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

sub add_include_dirs {
  my ($self, @include_dirs) = @_;
  
  unshift @{$self->{include_dirs}}, @include_dirs;
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

sub add_lib_dirs {
  my ($self, @lib_dirs) = @_;
  
  unshift @{$self->{lib_dirs}}, @lib_dirs;
}

sub get_libs {
  my ($self, $libs) = @_;
  
  return $self->{libs};
}

sub set_libs {
  my ($self, $libs) = @_;
  
  $self->{libs} = $libs;
  
  return $self;
}

sub use_lib {
  my ($self, @libs) = @_;
  
  unshift @{$self->{libs}}, @libs;
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

sub set_extra_compiler_flags {
  my ($self, $extra_compiler_flags) = @_;
  
  $self->{extra_compiler_flags} = $extra_compiler_flags;
  
  return $self;
}

sub get_extra_compiler_flags {
  my $self = shift;
  
  return $self->{extra_compiler_flags};
}

sub add_extra_compiler_flags {
  my ($self, $new_extra_compiler_flags) = @_;
  
  my $extra_compiler_flags = $self->{extra_compiler_flags};
  $extra_compiler_flags = '' unless defined $extra_compiler_flags;
  
  $extra_compiler_flags .= " $new_extra_compiler_flags";
  
  $self->{extra_compiler_flags} = $extra_compiler_flags;
}

sub set_extra_linker_flags {
  my ($self, $extra_linker_flags) = @_;
  
  $self->{extra_linker_flags} = $extra_linker_flags;
  
  return $self;
}

sub get_extra_linker_flags {
  my $self = shift;
  
  return $self->{extra_linker_flags};
}

sub add_extra_linker_flags {
  my ($self, $new_extra_linker_flags) = @_;
  
  my $extra_linker_flags = $self->{extra_linker_flags};
  $extra_linker_flags = '' unless defined $extra_linker_flags;
  
  $extra_linker_flags .= " $new_extra_linker_flags";
  
  $self->{extra_linker_flags} = $extra_linker_flags;
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
  my $self = shift;
  
  my $hash_config = {%{$self->{config}}};
  
  return $hash_config;
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

sub set_ccflags {
  my ($self, $ccflags) = @_;
  
  $self->set_config(ccflags => $ccflags);
  
  return $self;
}

sub get_ccflags {
  my $self = shift;
  
  return $self->get_config('ccflags');
}

sub add_ccflags {
  my ($self, $new_ccflags) = @_;
  
  my $ccflags = $self->get_config('ccflags');
  
  $ccflags .= " $new_ccflags";
  
  $self->set_config('ccflags' => $ccflags);
  
  return $self;
}

sub set_std {
  my ($self, $spec) = @_;
  
  my $extra_compiler_flags = $self->get_extra_compiler_flags;
  $extra_compiler_flags = '' unless defined $extra_compiler_flags;
  
  # Remove -std=foo section
  $extra_compiler_flags =~ s/-std=[^ ]+//g;
  
  $extra_compiler_flags .= " -std=$spec";
  
  # Add -std=foo section
  $self->set_extra_compiler_flags($extra_compiler_flags);
  
  return $self;
}

sub delete_std {
  my ($self) = @_;
  
  my $extra_compiler_flags = $self->get_extra_compiler_flags;
  
  # Remove -std=foo section
  $extra_compiler_flags =~ s/-std=[^ ]+//g;
  
  # Add -std=foo section
  $self->set_extra_compiler_flags($extra_compiler_flags);
  
  return $self;
}

sub set_cc {
  my ($self, $cc) = @_;
  
  return $self->set_config(cc => $cc);
}

sub get_cc {
  my ($self, $cc) = @_;
  
  return $self->get_config('cc');
}

sub set_optimize {
  my ($self, $optimize) = @_;
  
  return $self->set_config(optimize => $optimize);
}

sub get_optimize {
  my ($self, $optimize) = @_;
  
  return $self->get_config('optimize');
}

sub set_ld {
  my ($self, $ld) = @_;
  
  return $self->set_config(ld => $ld);
}

sub get_ld {
  my ($self, $ld) = @_;
  
  return $self->get_config('ld');
}

sub set_lddlflags {
  my ($self, $lddlflags) = @_;
  
  $self->set_config(lddlflags => $lddlflags);
  
  return $self;
}

sub get_lddlflags {
  my $self = shift;
  
  return $self->get_config('lddlflags');
}

sub add_lddlflags {
  my ($self, $new_lddlflags) = @_;
  
  my $lddlflags = $self->get_config('lddlflags');
  
  $lddlflags .= " $new_lddlflags";
  
  $self->set_config('lddlflags' => $lddlflags);
  
  return $self;
}

sub _remove_include_dirs_from_ccflags {
  my ($self) = @_;
  
  my $ccflags = $self->get_ccflags;
  
  my @parts = split(/ +/, $ccflags);
  
  my @rest_parts;
  my @include_dirs;
  for my $part (@parts) {
    if ($part =~ /^-I(.*)/) {
      my $include_dir = $1;
      push @include_dirs, $include_dir;
    }
    else {
      push @rest_parts, $part;
    }
  }
  
  my $rest_ccflags = join(' ', @rest_parts);
  
  $self->set_ccflags($rest_ccflags);
  
  return @include_dirs;
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

L<SPVM::Builder::Config> is configuration of c/c++ compile and link.

=head1 Methods

=head2 new

  my $bconf = SPVM::Builder::Config->new;
  
Create L<SPVM::Builder::Config> object.

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

Internally, remove C<-std=old> if exists and add C<-std=new> after C<extra_compiler_flags>.

=head2 delete_std

  $bconf->delete_std;

Delete C<std>.

Internally, remove C<-std=old> if exists from C<extra_compiler_flags>.

=head2 set_cc

  $bconf->set_cc($cc);

Set C<cc>.

=head2 get_cc

  my $cc = $bconf->get_cc;

Get C<cc>.

=head2 set_optimize

  $bconf->set_optimize($optimize);

Set C<optimize>.

=head2 get_optimize

  my $optimize = $bconf->get_optimize;

Get C<optimize>.

=head2 set_ld

  $bconf->set_ld($ld);

Set C<ld>.

=head2 get_ld

  my $ld = $bconf->get_ld;

Get C<ld>.

=head2 set_lddlflags

  $bconf->set_lddlflags($lddlflags);

Set C<lddlflags>.

=head2 get_lddlflags

  my $lddlflags = $bconf->get_lddlflags;

Get C<lddlflags>.

=head2 add_lddlflags

  $bconf->add_lddlflags($lddlflags);

Add C<lddlflags> after current C<lddlflags>.

=head2 new_c99
  
  my $bconf = SPVM::Builder::Config->new_c99;

Create defaulgt build config. This is L<SPVM::Builder::Config> object.

=head2 get_extra_compiler_flags

  my $extra_compiler_flags = $bconf->get_extra_compiler_flags;

Get C<extra_compiler_flags>.

=head2 set_extra_compiler_flags

  $bconf->set_extra_compiler_flags($extra_compiler_flags);

Set C<extra_compiler_flags>.

=head2 add_extra_compiler_flags

  $bconf->add_extra_compiler_flags($extra_compiler_flags);

Add new C<extra_compiler_flags> after current C<extra_compiler_flags>.

=head2 get_extra_linker_flags

  my $extra_linker_flags = $bconf->get_extra_linker_flags;

Get C<extra_linker_flags>.

=head2 set_extra_linker_flags

  $bconf->set_extra_linker_flags($extra_linker_flags);

Set C<extra_linker_flags>.

=head2 add_extra_linker_flags

  $bconf->add_extra_linker_flags($extra_linker_flags);

Add new C<extra_linker_flags> after current C<extra_linker_flags>.

=head2 get_include_dirs

  my $include_dirs = $bconf->get_include_dirs;

Get C<include_dirs> field. This field is array refernce.

C<include_dirs> field is used by C<compile> method of L<SPVM::Builder::CC> to set -I<inculde_dir>.

Default is "SPVM/Builder/include" of one up of directory SPVM::Buidler::Config.pm loaded and the values of -I<include_dir> in $Config{ccflags}.

=head2 set_include_dirs

  $bconf->set_include_dirs($include_dirs);

Set C<include_dirs> field. This field is array refernce.

See C<get_include_dirs> method about C<include_dirs> field.

=head2 add_lib_dirs

  $bconf->add_lib_dirs($lib_dir1, $lib_dir2, ...);

Add a element before the first element of C<lib_dirs> field.

See C<get_lib_dirs> method about C<lib_dirs> field.

=head2 get_lib_dirs

  my $lib_dirs = $bconf->get_lib_dirs;

Get C<lib_dirs> field. This field is array refernce.

C<lib_dirs> field is used by C<compile> method of L<SPVM::Builder::CC> to set -L<lib_dir>.

Default is the values of -L<lib_dir> in $Config{lddlflags}.

=head2 set_lib_dirs

  $bconf->set_lib_dirs($lib_dirs);

Set C<lib_dirs> field. This field is array refernce.

See C<get_lib_dirs> method about C<lib_dirs> field.

=head2 add_lib_dirs

  $bconf->add_lib_dirs($lib_dir1, $lib_dir2, ...);

Add a element before the first element of C<lib_dirs> field.

See C<get_lib_dirs> method about C<lib_dirs> field.

=head2 add_lib_dirs

  $bconf->add_lib_dirs($lib_dir1, $lib_dir2, ...);

Add a element before the first element of C<lib_dirs> field.

See C<get_lib_dirs> method about C<lib_dirs> field.

=head2 get_libs

  my $libs = $bconf->get_libs;

Get C<libs> field. This field is array refernce.

C<libs> field is used by C<link> method of L<SPVM::Builder::CC> to set -l<lib>.

=head2 set_libs

  $bconf->set_libs($libs);

Set C<libs> field. This field is array refernce.

See C<get_libs> method about C<libs> field.

=head2 use_lib

  $bconf->use_lib($lib1, $lib2, ...);

Add a library after the last element of C<libs> field.

Don't use prefix '-l' or 'lib' for library name.

See C<get_libs> method about C<libs> field.

=head2 get_force_compile

  my $force_compile = $bconf->get_force_compile;

Get C<force_compile> field.

C<force_compile> field is used by C<compile> method of L<SPVM::Builder::CC> to determine whether the method should force compilation of source codes without cache.

=head2 set_force_compile

  $bconf->set_force_compile($force_compile);

Set C<force_compile> field.

See C<get_force_compile> method about C<force_compile> field.

=head2 quiet

  my $quiet = $bconf->get_quiet;

Get C<quiet> field.

C<quiet> field is used by C<compile> method of L<SPVM::Builder::CC> to determine whether the method output compiler messages , default to C<1>.

=head2 set_quiet

  $bconf->set_quiet($quiet);

Set C<quiet> field.

See C<get_quiet> method about C<quiet> field.

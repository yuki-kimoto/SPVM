package SPVM::Builder::Config;

use strict;
use warnings;
use Config;

sub get_ext {
  my ($self, $ext) = @_;
  
  return $self->{ext};
}

sub set_ext {
  my ($self, $ext) = @_;
  
  $self->{ext} = $ext;
  
  return $self;
}

sub new {
  my $class = shift;
  
  my $self = {};
  
  $self->{config} = {};

  return bless $self, $class;
}

sub parse_dll_infos {
  my $self = shift;
  
  my $get_lddlflags;
  if (defined $self->get_lddlflags) {
    $get_lddlflags = $self->get_lddlflags;
  }
  else {
    $get_lddlflags = '';
  }
  my $get_extra_linker_flags;
  if (defined $self->get_extra_linker_flags) {
    $get_extra_linker_flags = $self->get_extra_linker_flags;
  }
  else {
    $get_extra_linker_flags = '';
  }
  
  my $linker_flags = $get_lddlflags . " " . $get_extra_linker_flags;
  my $dll_infos = [];
  while ($linker_flags =~ /-(L|l)([\S]+)/g) {
    my $type = $1;
    my $name = $2;
    push @$dll_infos, {type => $type, name => $name};
  }
  
  return $dll_infos;
}

sub new_c99 {
  my $class = shift;
  
  my $bconf = SPVM::Builder::Config->new;
  
  # Use default config
  my $default_config = {%Config};
  $bconf->replace_all_config($default_config);
  
  # Add include directory to ccflags
  my $include_dir = $INC{"SPVM/Builder/Config.pm"};
  $include_dir =~ s/\/Config\.pm$//;
  $include_dir .= '/include';
  $bconf->add_extra_compiler_flags("-I$include_dir");
  
  # C99
  $bconf->set_std('c99');
  
  # Optimize
  $bconf->set_optimize('-O3');
  
  # NativeAPI
  $bconf->set_ext('c');
  
  # I want to print warnings, but if gcc version is different, can't suppress no needed warning message.
  # so I dicide not to print warning in release version
  if ($ENV{SPVM_TEST_ENABLE_WARNINGS}) {
    $bconf->add_extra_compiler_flags("-Wall -Wextra -Wno-unused-label -Wno-unused-function -Wno-unused-label -Wno-unused-parameter -Wno-unused-variable -Wno-missing-field-initializers");
  }
  
  return $bconf;
}

sub new_cpp {
  my $class = shift;
  
  my $bconf = SPVM::Builder::Config->new;
  
  # Use default config
  my $default_config = {%Config};
  $bconf->replace_all_config($default_config);
  
  # Add include directory to ccflags
  my $include_dir = $INC{"SPVM/Builder/Config.pm"};
  $include_dir =~ s/\/Config\.pm$//;
  $include_dir .= '/include';
  $bconf->add_extra_compiler_flags("-I$include_dir");
  
  # Optimize
  $bconf->set_optimize('-O3');
  
  # CC
  $bconf->set_cc('g++');
  
  # LD
  $bconf->set_ld('g++');
  
  # NativeAPI
  $bconf->set_ext('cpp');
  
  # Delete std
  $bconf->delete_std;
  
  return $bconf;
}

sub get_cache {
  my ($self, $cache) = @_;
  
  return $self->{cache};
}

sub set_cache {
  my ($self, $cache) = @_;
  
  $self->{cache} = $cache;
  
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

sub prepend_ccflags {
  my ($self, $new_ccflags) = @_;
  
  my $ccflags = $self->get_config('ccflags');
  
  $ccflags = "$new_ccflags $ccflags";
  
  $self->set_config('ccflags' => $ccflags);
  
  return $self;
}

sub set_std {
  my ($self, $spec) = @_;
  
  my $extra_compiler_flags = $self->get_extra_compiler_flags;
  
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

sub prepend_lddlflags {
  my ($self, $new_lddlflags) = @_;
  
  my $lddlflags = $self->get_config('lddlflags');
  
  $lddlflags = "$new_lddlflags $lddlflags";
  
  $self->set_config('lddlflags' => $lddlflags);
  
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
  
  $self->set_config(extra_compiler_flags => $extra_compiler_flags);
  
  return $self;
}

sub get_extra_compiler_flags {
  my $self = shift;
  
  return $self->get_config('extra_compiler_flags');
}

sub add_extra_compiler_flags {
  my ($self, $new_extra_compiler_flags) = @_;
  
  my $extra_compiler_flags = $self->get_config('extra_compiler_flags');
  
  $extra_compiler_flags .= " $new_extra_compiler_flags";
  
  $self->set_config('extra_compiler_flags' => $extra_compiler_flags);
  
  return $self;
}

sub prepend_extra_compiler_flags {
  my ($self, $new_extra_compiler_flags) = @_;
  
  my $extra_compiler_flags = $self->get_config('extra_compiler_flags');
  
  $extra_compiler_flags = "$new_extra_compiler_flags $extra_compiler_flags";
  
  $self->set_config('extra_compiler_flags' => $extra_compiler_flags);
  
  return $self;
}

sub set_extra_linker_flags {
  my ($self, $extra_linker_flags) = @_;
  
  $self->set_config(extra_linker_flags => $extra_linker_flags);
  
  return $self;
}

sub get_extra_linker_flags {
  my $self = shift;
  
  return $self->get_config('extra_linker_flags');
}

sub add_extra_linker_flags {
  my ($self, $new_extra_linker_flags) = @_;
  
  my $extra_linker_flags = $self->get_config('extra_linker_flags');
  
  $extra_linker_flags .= " $new_extra_linker_flags";
  
  $self->set_config('extra_linker_flags' => $extra_linker_flags);
  
  return $self;
}

sub prepend_extra_linker_flags {
  my ($self, $new_extra_linker_flags) = @_;
  
  my $extra_linker_flags = $self->get_config('extra_linker_flags');
  
  $extra_linker_flags = "$new_extra_linker_flags $extra_linker_flags";
  
  $self->set_config('extra_linker_flags' => $extra_linker_flags);
  
  return $self;
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

=head2 set_ccflags

  $bconf->set_ccflags($ccflags);

Set C<ccflags>.

=head2 get_ccflags

  my $ccflags = $bconf->get_ccflags;

Get C<ccflags>.

=head2 add_ccflags

  $bconf->add_ccflags($ccflags);

Add C<ccflags> after current C<ccflags>.

=head2 prepend_ccflags

  $bconf->add_ccflags($ccflags);

prepend C<ccflags> before current C<ccflags>.

=head2 set_std

  $bconf->set_std('gnu99');

Set C<std>.

Internally, remove C<-std=old> and add C<-std=new> after C<ccflags>.

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

=head2 prepend_lddlflags

  $bconf->add_lddlflags($lddlflags);

Prepend C<lddlflags> before current C<lddlflags>.

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

=head2 prepend_extra_compiler_flags

  $bconf->prepend_extra_compiler_flags($extra_compiler_flags);

Prepend new C<extra_compiler_flags> before current C<extra_compiler_flags>.

=head2 get_extra_linker_flags

  my $extra_linker_flags = $bconf->get_extra_linker_flags;

Get C<extra_linker_flags>.

=head2 set_extra_linker_flags

  $bconf->set_extra_linker_flags($extra_linker_flags);

Set C<extra_linker_flags>.

=head2 add_extra_linker_flags

  $bconf->add_extra_linker_flags($extra_linker_flags);

Add new C<extra_linker_flags> after current C<extra_linker_flags>.

=head2 prepend_extra_linker_flags

  $bconf->prepend_extra_linker_flags($extra_linker_flags);

Prepend new C<extra_linker_flags> before current C<extra_linker_flags>.

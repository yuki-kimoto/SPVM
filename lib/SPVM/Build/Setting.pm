package SPVM::Build::Setting;

use strict;
use warnings;
use Config;

sub new {
  my $class = shift;
  
  my $self = {};
  
  $self->{config} = {};

  $self->{ldflags} = [];

  $self->{include_dirs} = [];
  
  return bless $self, $class;
}

sub set_include_dirs {
  my ($self, $include_dirs) = @_;
  
  $self->{include_dirs} = $include_dirs;
  
  return $self;
}

sub get_include_dirs {
  my $self = shift;
  
  return $self->{include_dirs};
}

sub add_include_dir {
  my ($self, $include_dir) = @_;
  
  push @{$self->{include_dirs}}, $include_dir;
  
  return $self;
}

sub _cmd_options_to_array_options {
  my ($self, $cmd_options) = @_;
  
  my @array_options;
  
  if (defined $cmd_options) {
    @array_options = split(/ +/, $cmd_options);
  }
  
  return \@array_options;
}

sub _array_options_to_cmd_options {
  my ($self, $array_options) = @_;
  
  my $cmd_options = join(' ', @$array_options);
  
  return $cmd_options;
}

sub set_ccflags {
  my ($self, $ccflags) = @_;
  
  $self->{ccflags} = $ccflags;
  
  return $self;
}

sub get_ccflags {
  my $self = shift;
  
  return $self->{ccflags};
}

sub add_ccflag {
  my ($self, $ccflag) = @_;
  
  push @{$self->{ccflags}}, $ccflag;
  
  return $self;
}

sub set_config {
  my ($self, %key_values) = @_;
  
  my $config = $self->{config};
  
  for my $key (keys %key_values) {
    my $value = $key_values{$key};
    $config->{$key} = $value;
  }
  
  return $self;
}

sub add_config {
  my ($self, %key_values) = @_;
  
  my $config = $self->{config};

  for my $key (keys %key_values) {
    my $value = $key_values{$key};
    $config->{$key} .= " $value";
  }
  
  return $self;
}

sub get_config {
  my $self = shift;
  
  my $config = $self->{config};

  if (@_) {
    return $config->{$_[0]};
  }
  else {
    return $config;
  }
}

sub set_std {
  my ($self, $spec) = @_;
  
  my $ccflags = $self->get_ccflags;
  
  # Remove -std=foo section
  for my $ccflag (@$ccflags) {
    $ccflag =~ s/-std=[^ ]+//g;
  }
  
  # Add -std=foo section
  $self->add_ccflag("-std=$spec");
  
  return $self;
}

sub set_cc {
  my ($self, $cc) = @_;
  
  return $self->set_config(cc => $cc);
}

sub get_cc {
  my ($self, $cc) = @_;
  
  return $self->get_config(cc => $cc);
}

sub set_optimize {
  my ($self, $optimize) = @_;
  
  return $self->set_config(optimize => $optimize);
}

sub get_optimize {
  my ($self, $optimize) = @_;
  
  return $self->get_config(optimize => $optimize);
}

sub set_cppflags {
  my ($self, $cppflags) = @_;
  
  $self->{cppflags} = $cppflags;
  
  return $self;
}

sub get_cppflags {
  my $self = shift;
  
  return $self->{cppflags};
}

sub add_cppflag {
  my ($self, $cppflag) = @_;
  
  push @{$self->{cppflags}}, $cppflag;
  
  return $self;
}

sub set_ld {
  my ($self, $ld) = @_;
  
  return $self->set_config(ld => $ld);
}

sub get_ld {
  my ($self, $ld) = @_;
  
  return $self->get_config(ld => $ld);
}

sub set_ldflags {
  my ($self, $ldflags) = @_;
  
  $self->{ldflags} = $ldflags;
  
  return $self;
}

sub get_ldflags {
  my $self = shift;
  
  return $self->{ldflags};
}

sub add_ldflag {
  my ($self, $ldflag) = @_;
  
  push @{$self->{ldflags}}, $ldflag;
  
  return $self;
}

=pod
 Compiler:
    cc='cc', ccflags ='-fno-strict-aliasing -pipe -fstack-protector -I/usr/local/include -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64',
    optimize='-O2',
    cppflags='-fno-strict-aliasing -pipe -fstack-protector -I/usr/local/include'
    ccversion='', gccversion='4.1.2 20080704 (Red Hat 4.1.2-52)', gccosandvers=''
    intsize=4, longsize=8, ptrsize=8, doublesize=8, byteorder=12345678
    d_longlong=define, longlongsize=8, d_longdbl=define, longdblsize=16
    ivtype='long', ivsize=8, nvtype='double', nvsize=8, Off_t='off_t', lseeksize=8
    alignbytes=8, prototype=define
    
  Linker and Libraries:
    ld='cc', ldflags =' -fstack-protector -L/usr/local/lib'
    libpth=/usr/include/oracle/11.2/client64 /usr/local/lib /usr/lib /lib /lib64 /usr/lib64 /usr/local/lib64
    libs=-lnsl -ldl -lm -lcrypt -lutil -lc
    perllibs=-lnsl -ldl -lm -lcrypt -lutil -lc
    libc=libc-2.5.so, so=so, useshrplib=false, libperl=libperl.a
    gnulibc_version='2.5'
=cut


=head1 NAME

SPVM::Build::Setting;

=head1 DESCRIPTION

L<ExtUtils::CBuilder> setting of C<new>, C<compile>, C<link> methods.

=cut

1;

package SPVM::Build::Setting;

use strict;
use warnings;
use Config;

sub new {
  my $class = shift;
  
  my $self = {};
  
  $self->{config} = {};

  return bless $self, $class;
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

sub get_config {
  my ($self, $name) = @_;
  
  return $self->{config}{$name};
}

sub set_config {
  my ($self, $name, $value) = @_;
  
  $self->{config}{$name} = $value;
  
  return $self;
}

sub set_std {
  my ($self, $spec) = @_;
  
  my $ccflags = $self->get_ccflags;
  
  # Remove -std=foo section
  $ccflags =~ s/-std=[^ ]+//g;
  
  $ccflags .= " -std=$spec";
  
  # Add -std=foo section
  $self->set_ccflags($ccflags);
  
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
  
  $self->set_config(ldflags => $ldflags);
  
  return $self;
}

sub get_ldflags {
  my $self = shift;
  
  return $self->get_config('ldflags');
}

sub add_ldflags {
  my ($self, $new_ldflags) = @_;
  
  my $ldflags = $self->get_config('ldflags');
  
  $ldflags .= " $new_ldflags";
  
  $self->set_config('ldflags' => $ldflags);
  
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

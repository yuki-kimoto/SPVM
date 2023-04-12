package SPVM::Builder::LinkInfo;

use strict;
use warnings;
use Config;
use Carp 'confess';
use File::Basename 'dirname';

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

sub config {
  my $self = shift;
  if (@_) {
    $self->{config} = $_[0];
    return $self;
  }
  else {
    return $self->{config};
  }
}

sub output_file {
  my $self = shift;
  if (@_) {
    $self->{output_file} = $_[0];
    return $self;
  }
  else {
    return $self->{output_file};
  }
}

sub object_file_infos {
  my $self = shift;
  if (@_) {
    $self->{object_file_infos} = $_[0];
    return $self;
  }
  else {
    return $self->{object_file_infos};
  }
}

sub lib_infos {
  my $self = shift;
  if (@_) {
    $self->{lib_infos} = $_[0];
    return $self;
  }
  else {
    return $self->{lib_infos};
  }
}

# Class Methods
sub new {
  my $class = shift;
  
  my $self = {@_};

  bless $self, $class;
  
  unless (defined $self->object_file_infos) {
    $self->object_file_infos([]);
  }

  unless (defined $self->lib_infos) {
    $self->lib_infos([]);
  }
  
  return $self;
}

sub create_merged_ldflags {
  my ($self) = @_;
  
  my $config = $self->config;
  
  my @merged_ldflags;
  
  if (defined $config->ld_optimize) {
    push @merged_ldflags, split(/ +/, $config->ld_optimize);
  }
  
  my $output_type = $config->output_type;
  if ($output_type eq 'dynamic_lib') {
    push @merged_ldflags, @{$config->dynamic_lib_ldflags};
  }
  
  my $ldflags = $config->ldflags;
  push @merged_ldflags, @{$config->ldflags};
  
  my $lib_dirs = $config->lib_dirs;
  
  my @lib_dirs_ldflags = map { "-L$_" } @$lib_dirs;
  push @merged_ldflags, @lib_dirs_ldflags;
  
  my $libs = $config->libs;
  my @lib_ldflags = map { ref $_ ? $_->to_string : $_ } @$libs;
  push @merged_ldflags, @lib_ldflags;
  
  return \@merged_ldflags;
}

# Instance Methods
sub create_link_command {
  my ($self) = @_;
  
  my $config = $self->config;
  
  my $ld = $config->ld;
  my $output_file = $self->output_file;
  my $object_file_infos = $self->object_file_infos;
  my $object_files = [map { my $tmp = $_->to_string; $tmp } @$object_file_infos];
  
  my $merged_ldflags = $self->create_merged_ldflags;
  
  my @link_command = ($ld, '-o', $output_file, @$object_files, @$merged_ldflags);
  
  return \@link_command;
}

sub to_string {
  my ($self) = @_;

  my $link_command = $self->create_link_command;;
  my $link_command_string = "@$link_command";
  
  return $link_command_string;
}

1;

=head1 Name

SPVM::Builder::LinkInfo - Link Information

=head1 Description

C<SPVM::Builder::LinkInfo> is a link information. This infromation is used by the linker.

=head1 Fields

=head2 class_name

  my $class_name = $link_info->class_name;
  $link_info->class_name($class_name);

Get and set the class name.

=head2 config

  my $config = $link_info->config;
  $link_info->config($config);

Get and set the L<config|SPVM::Builder::Config> that is used to link the objects.

=head2 output_file

  my $output_file = $link_info->output_file;
  $link_info->output_file($output_file);

Get and set the object file that is compiled.

=head2 object_file_infos

  my $object_file_infos = $link_info->object_file_infos;
  $link_info->object_file_infos($object_file_infos);

Get and set the object file informations to be linked. Each object file is a L<SPVM::Builder::ObjectFileInfo> object.

=head1 Class Methods

=head2 new

  my $link_info = SPVM::Builder::LinkInfo->new;

Creates a new C<SPVM::Builder::LinkInfo> object.

=head2 create_merged_ldflags

  my $merged_ldflags = $link_info->create_merged_ldflags;

Creates the merged ldflags as an array reference.

Examples:

  [qw(-shared -O2 -Llibdir -lz)]

=head2 create_link_command

  my $link_command = $link_info->create_link_command;

Creates the link command as an array reference.

Examples:

  [qw(cc -o dylib.so foo.o bar.o -shared -O2 -Llibdir -lz)]

=head2 to_string

  my $string = $link_info->to_string;

Get the string representation of the L<link command|/"create_link_command">.

Examples:

  "cc -o dylib.so foo.o bar.o -shared -O2 -Llibdir -lz"

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

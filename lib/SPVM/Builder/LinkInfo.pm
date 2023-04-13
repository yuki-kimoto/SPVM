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

sub object_files {
  my $self = shift;
  if (@_) {
    $self->{object_files} = $_[0];
    return $self;
  }
  else {
    return $self->{object_files};
  }
}

# Class Methods
sub new {
  my $class = shift;
  
  my $self = {@_};

  bless $self, $class;
  
  unless (defined $self->object_files) {
    $self->object_files([]);
  }

  return $self;
}

# Instance Methods
sub create_link_command {
  my ($self) = @_;
  
  my $config = $self->config;
  
  my $ld = $config->ld;
  my $output_file = $self->output_file;
  my $object_files = $self->object_files;
  my $object_file_names = [map { $_->to_string; } @$object_files];
  
  my $link_command_args = $self->create_link_command_args;
  
  my @link_command = ($ld, '-o', $output_file, @$link_command_args, @$object_file_names);
  
  return \@link_command;
}

sub create_link_command_args {
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

The SPVM::Builder::LinkInfo class has methods to manipulate link information.

=head1 Fields

=head2 class_name

  my $class_name = $link_info->class_name;
  $link_info->class_name($class_name);

Gets and sets the class name.

=head2 config

  my $config = $link_info->config;
  $link_info->config($config);

Gets and sets a L<SPVM::Builder::Config> object used to link the object files.

=head2 output_file

  my $output_file = $link_info->output_file;
  $link_info->output_file($output_file);

Gets and sets the output file.

=head2 object_files

  my $object_files = $link_info->object_files;
  $link_info->object_files($object_files);

Gets and sets the object files.

This field is an array reference of L<SPVM::Builder::ObjectFileInfo> objects.

=head1 Class Methods

=head2 new

  my $link_info = SPVM::Builder::LinkInfo->new;

Creates a new C<SPVM::Builder::LinkInfo> object.

=head1 Instance Methods

=head2 create_link_command

  my $link_command = $link_info->create_link_command;

Creates a link command, and returns it. The return value is an array reference.

The following one is an example of the return value.

  [qw(cc -o dylib.so -shared -O2 -Llibdir -lz foo.o bar.o)]

=head2 create_link_command_args

  my $link_command_args = $link_info->create_link_command_args;

Creates the parts of the arguments of the link command from the information of the L</"config"> field, and returns it. The return value is an array reference.

The C<-o> option and the object file names are not contained.

The following one is an example of the return value.

  [qw(-shared -O2 -Llibdir -lz)]

=head2 to_string

  my $string = $link_info->to_string;

Calls the L<create_link_command|/"create_link_command"> method and joins all elements of the returned array reference with a space, and returns it.

The following one is an example of the return value.

  "cc -o dylib.so -shared -O2 -Llibdir -lz foo.o bar.o"

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

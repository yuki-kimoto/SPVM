package SPVM::Builder::CompileInfo;

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

sub builder_include_dir {
  my $self = shift;
  if (@_) {
    $self->{builder_include_dir} = $_[0];
    return $self;
  }
  else {
    return $self->{builder_include_dir};
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

sub source_file {
  my $self = shift;
  if (@_) {
    $self->{source_file} = $_[0];
    return $self;
  }
  else {
    return $self->{source_file};
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

# Class methods
sub new {
  my $class = shift;
  
  my $self = {@_};

  bless $self, $class;
  
  unless (defined $self->include_dirs) {
    $self->include_dirs([]);
  }
  
  return $self;
}

# Instance Methods
sub create_compile_command {
  my ($self) = @_;
  
  my $config = $self->config;

  my $cc = $config->cc;
  my $class_name = $self->class_name;
  my $output_file = $self->output_file;
  my $source_file = $self->source_file;
  
  my $merged_ccflags = $self->_create_merged_ccflags;
  
  my @compile_command = ($cc, '-c', '-o', $output_file, @$merged_ccflags, $source_file);
  
  return \@compile_command;
}

# Instance methods
sub to_string {
  my ($self) = @_;

  my $compile_command = $self->create_compile_command;
  my $compile_command_string = "@$compile_command";
  
  return $compile_command_string;
}

sub _create_merged_ccflags {
  my ($self) = @_;
  
  my $config = $self->config;
  
  my @merged_ccflags;
  
  if (defined $self->optimize) {
    push @merged_ccflags, split(/ +/, $self->optimize);
  }
  
  push @merged_ccflags, @{$config->ccflags};

  my $builder_include_dir = $self->builder_include_dir;
  push @merged_ccflags, "-I$builder_include_dir";

  my $include_dirs = $self->include_dirs;
  my @include_dirs_ccflags = map { "-I$_" } @$include_dirs;
  push @merged_ccflags, @include_dirs_ccflags;
  
  return \@merged_ccflags;
}

1;

=head1 Name

SPVM::Builder::CompileInfo - Compilation Information

=head1 Description

The SPVM::Builder::CompileInfo class has methods to manipulate compilation information.

=head1 Fields

=head2 class_name

  my $class_name = $compile_info->class_name;
  $compile_info->class_name($class_name);

Gets and sets the class name.

=head2 ccflags

  my $ccflags = $compile_info->ccflags;
  $compile_info->ccflags($ccflags);

Gets and sets the compiler flags. This field is an array reference. The default value is [].

=head2 optimize

  my $optimize = $compile_info->optimize;
  $compile_info->optimize($optimize);

Gets and sets the optimize.

=head2 include_dirs

  my $include_dirs = $source_file->include_dirs;
  $source_file->include_dirs($include_dirs);

Gets and sets the include directories. This field is an array reference. The default is [].

=head2 source_file

  my $source_file = $compile_info->source_file;
  $compile_info->source_file($source_file);

Gets and sets the source file.

=head2 output_file

  my $output_file = $compile_info->output_file;
  $compile_info->output_file($output_file);

Gets and sets the output file.

=head2 config

  my $config = $compile_info->config;
  $compile_info->config($config);

Gets and sets a L<SPVM::Builder::Config> object that is used to compile the source file.

=head1 Class Methods

=head2 new

  my $compile_info = SPVM::Builder::CompileInfo->new;

Creates a new L<SPVM::Builder::CompileInfo> object.

=head1 Instance Methods

=head2 create_compile_command

  my $compile_command = $compile_info->create_compile_command;

Gets the compile command as an array reference.

The following one is an example of the return value.

  [qw(cc -c -O2 -Iinclude_dir -o foo.o foo.c)]

=head2 to_string

  my $string = $compile_info->to_string;

Calls the L<create_compile_command|/"create_compile_command"> method and joins all elements of the returned array reference with a space, and returns it.

The following one is an example of the return value.

  "cc -c -O2 -Iinclude_dir -o foo.o foo.c"

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

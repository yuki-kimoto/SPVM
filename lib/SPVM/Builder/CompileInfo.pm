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
  
  my $compile_command_args = $self->create_compile_command_args;
  
  my @compile_command = ($cc, '-c', '-o', $output_file, @$compile_command_args, $source_file);
  
  return \@compile_command;
}

sub create_compile_command_args {
  my ($self) = @_;
  
  my $config = $self->config;
  
  my @compile_command_args;
  
  if (defined $config->optimize) {
    push @compile_command_args, split(/ +/, $config->optimize);
  }
  
  push @compile_command_args, @{$config->ccflags};
  
  # include directories
  {
    my @all_include_dirs;
    
    my $spvm_core_include_dir = $config->spvm_core_include_dir;
    push @all_include_dirs, $spvm_core_include_dir;
    
    my $include_dirs = $config->include_dirs;
    push @all_include_dirs, @$include_dirs;
    
    my @all_include_dirs_args = map { "-I$_" } @all_include_dirs;
    
    push @compile_command_args, @all_include_dirs_args;
  }
  
  return \@compile_command_args;
}

# Instance methods
sub to_string {
  my ($self) = @_;

  my $compile_command = $self->create_compile_command;
  my $compile_command_string = "@$compile_command";
  
  return $compile_command_string;
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

=head2 config

  my $config = $compile_info->config;
  $compile_info->config($config);

Gets and sets a L<SPVM::Builder::Config> object used to compile the source file.

=head2 source_file

  my $source_file = $compile_info->source_file;
  $compile_info->source_file($source_file);

Gets and sets the source file.

=head2 output_file

  my $output_file = $compile_info->output_file;
  $compile_info->output_file($output_file);

Gets and sets the output file.

=head1 Class Methods

=head2 new

  my $compile_info = SPVM::Builder::CompileInfo->new;

Creates a new L<SPVM::Builder::CompileInfo> object.

=head1 Instance Methods

=head2 create_compile_command

  my $compile_command = $compile_info->create_compile_command;

Creates the compilation command, and returns it. The return value is an array reference.

The following one is an example of the return value.

  [qw(cc -o foo.o -c -O2 -Ipath/include foo.c)]

=head2 create_compile_command_args

  my $config_args = $compile_info->create_compile_command_args;

Creates the parts of the arguments of the compilation command from the information of the L</"config"> field, and returns it. The return value is an array reference.

The C<-c> option, the C<-o> option and the source file name are not contained.

The following one is an example of the return value.

  [qw(-O2 -Ipath/include)]

=head2 to_string

  my $string = $compile_info->to_string;

Calls the L<create_compile_command|/"create_compile_command"> method and joins all elements of the returned array reference with a space, and returns it.

The following one is an example of the return value.

  "cc -c -o foo.o -O2 -Ipath/include foo.c"

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

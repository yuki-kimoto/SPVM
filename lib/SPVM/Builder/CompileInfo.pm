package SPVM::Builder::CompileInfo;

use strict;
use warnings;
use Config;
use Carp 'confess';
use File::Basename 'dirname';

# Fields
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

sub category {
  my $self = shift;
  if (@_) {
    $self->{category} = $_[0];
    return $self;
  }
  else {
    return $self->{category};
  }
}

# Class methods
sub new {
  my $class = shift;
  
  my $self = {@_};
  
  bless $self, $class;
  
  my $config = $self->config;
  
  unless ($config) {
    confess("The \"config\" field must be defined.");
  }
  
  my $after_create_compile_info_cbs = $config->after_create_compile_info_cbs;
  for my $after_create_compile_info_cb (@$after_create_compile_info_cbs) {
    $after_create_compile_info_cb->($config, $self);
  }
  
  my $config_exe = $config->config_exe;
  if ($config_exe) {
    my $global_after_create_compile_info_cbs = $config_exe->global_after_create_compile_info_cbs;
    for my $global_after_create_compile_info_cb (@$global_after_create_compile_info_cbs) {
      $global_after_create_compile_info_cb->($config, $self);
    }
  }
  
  return $self;
}

# Instance Methods
sub create_command {
  my ($self) = @_;
  
  my $config = $self->config;
  
  my $cc = $config->cc;
  my $output_file = $self->output_file;
  my $source_file = $self->source_file;
  
  my $compile_command_args = $self->create_ccflags;
  
  my @compile_command = ($cc, '-c', '-o', $output_file, @$compile_command_args, $source_file);
  
  return \@compile_command;
}

sub create_ccflags {
  my ($self) = @_;
  
  my $config = $self->config;
  
  my @compile_command_args;
  
  my $std = $config->std;
  if (defined $std) {
    push @compile_command_args, "-std=$std";
  }
  
  my $optimize = $config->optimize;
  if (defined $optimize) {
    push @compile_command_args, split(/ +/, $optimize);
  }
  
  push @compile_command_args, @{$config->ccflags};
  
  push @compile_command_args, @{$config->thread_ccflags};
  
  push @compile_command_args, @{$config->mingw_ccflags};
  
  my $output_type = $config->output_type;
  
  if ($output_type eq 'dynamic_lib') {
    push @compile_command_args, @{$config->dynamic_lib_ccflags};
  }
  
  # include directories
  {
    my @all_include_dirs;
    
    # SPVM core native directory
    my $spvm_core_include_dir = $config->spvm_core_include_dir;
    push @all_include_dirs, $spvm_core_include_dir;
    
    # include directories
    my $include_dirs = $config->include_dirs;
    push @all_include_dirs, @$include_dirs;
    
    # Native include directory
    my $native_include_dir = $config->native_include_dir;
    if (defined $native_include_dir) {
      push @all_include_dirs, $native_include_dir;
    }
    
    # Resource include directories
    my $resource_names = $config->get_resource_names;
    for my $resource_name (@$resource_names) {
      my $resource = $config->get_resource($resource_name);
      my $config = $resource->config;
      my $resource_include_dir = $config->native_include_dir;
      if (defined $resource_include_dir) {
        push @all_include_dirs, $resource_include_dir;
      }
    }
    
    my @all_include_dirs_args = map { "-I$_" } @all_include_dirs;
    
    push @compile_command_args, @all_include_dirs_args;
  }
  
  return \@compile_command_args;
}

sub to_command {
  my ($self) = @_;

  my $compile_command = $self->create_command;
  my $compile_command_string = "@$compile_command";
  
  return $compile_command_string;
}

1;

=head1 Name

SPVM::Builder::CompileInfo - Compiler Information

=head1 Description

The SPVM::Builder::CompileInfo class has methods to manipulate compiler information.

=head1 Fields

=head2 config

  my $config = $compile_info->config;
  $compile_info->config($config);

Gets and sets the C<config> field, a L<SPVM::Builder::Config> object.

=head2 source_file

  my $source_file = $compile_info->source_file;
  $compile_info->source_file($source_file);

Gets and sets the C<source_file> field, a source file.

=head2 output_file

  my $output_file = $compile_info->output_file;
  $compile_info->output_file($output_file);

Gets and sets the C<output_file> field, an output file.

=head2 category

  my $category = $config->category;
  $config->category($category);

Gets and sets the C<category> field.

These are C<precompile_class>, C<native_class>, C<native_source>, C<spvm_core>, C<bootstrap>.

=head1 Class Methods

=head2 new

  my $compile_info = SPVM::Builder::CompileInfo->new(%fields);

Creates a new L<SPVM::Builder::CompileInfo> object given L</"Fields">.

Field Default Values:

=over 2

=item * L</"source_file">

undef

=item * L</"output_file">

undef

=back

Exceptions:

The "config" field must be defined.

=head1 Instance Methods

=head2 create_command

  my $compile_command = $compile_info->create_command;

Creates an array reference of the compilation command, and returns it.

Return Value Examples:

  [qw(cc -o foo.o -c -O2 -Ipath/include foo.c)]

=head2 create_ccflags

  my $config_args = $compile_info->create_ccflags;

Creates n array reference of the compilation options, and returns it.

The source file L<"source_file"> and the output file L</"output_file"> are not contained.

Return Value Examples:

  [qw(-O2 -Ipath/include)]

=head2 to_command

  my $compile_command_string = $compile_info->to_command;

Joins all elements of the return value of the the L</"create_command"> method with a space, and returns it.

Return Value Examples:

  "cc -c -o foo.o -O2 -Ipath/include foo.c"

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

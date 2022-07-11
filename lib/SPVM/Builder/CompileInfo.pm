package SPVM::Builder::CompileInfo;

use strict;
use warnings;
use Config;
use Carp 'confess';
use File::Basename 'dirname';

# Fields
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

sub cc {
  my $self = shift;
  if (@_) {
    $self->{ld} = $_[0];
    return $self;
  }
  else {
    return $self->{ld};
  }
}

sub ccflags {
  my $self = shift;
  if (@_) {
    $self->{ldflags} = $_[0];
    return $self;
  }
  else {
    return $self->{ldflags};
  }
}

sub source_files {
  my $self = shift;
  if (@_) {
    $self->{source_files} = $_[0];
    return $self;
  }
  else {
    return $self->{source_files};
  }
}

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

sub create_compile_command {
  my ($self) = @_;

  my $cc = $self->cc;
  my $ccflags = $self->ccflags;
  my $class_name = $self->class_name;
  my $output_file = $self->output_file;
  my $source_files = $self->source_files;
  
  my $all_ldflags_str = '';
  
  my $ccflags_str = join(' ', @$ccflags);
  $all_ldflags_str .= $ccflags_str;
  
  my $source_files = [map { my $tmp = $_->to_string; $tmp } @$source_files];

  my $cbuilder_extra_compileer_flags = $ccflags_str;
  
  my @compile_command = ($cc, '-o', $output_file, @$source_files, $cbuilder_extra_compileer_flags);
  
  return \@compile_command;
}

# Methods
sub to_string {
  my ($self) = @_;

  my @compile_command = $self->create_compile_command;
  my $compile_command = "@$compile_command";
  
  return $compile_command;
}

# Methods
sub new {
  my $class = shift;
  
  my $self = {@_};

  bless $self, $class;
  
  unless (defined $self->source_files) {
    $self->source_files([]);
  }

  unless (defined $self->ccflags) {
    $self->ccflags([]);
  }
  
  return $self;
}

1;

=head1 Name

SPVM::Builder::CompileInfo - Link Information

=head1 Description

C<SPVM::Builder::CompileInfo> is a compile information. This infromation is used by the compileer.

=head1 Field Methods

=head2 output_file

  my $output_file = $compile_info->output_file;
  $compile_info->output_file($output_file);

Get and set the source file that is compiled.

=head2 cc

  my $cc = $compile_info->cc;
  $compile_info->cc($cc);

Get and set the compileer name.

=head2 ccflags

  my $ccflags = $source_file->ccflags;
  $source_file->ccflags($ccflags);

Get and set the compileer flags.  The default value is C<[]>.

=head2 source_files

  my $source_files = $compile_info->source_files;
  $compile_info->source_files($source_files);

Get and set the source file informations to be compileed. Each source file is a L<SPVM::Builder::ObjectFileInfo> object.

=head2 class_name

  my $class_name = $compile_info->class_name;
  $compile_info->class_name($class_name);

Get and set the class name.

=head2 config

  my $config = $compile_info->config;
  $compile_info->config($config);

Get and set the L<config|SPVM::Builder::Config> that is used to compile the source file.

=head1 Class Methods

=head2 new

  my $compile_info = SPVM::Builder::CompileInfo->new;

=head1 Instance Methods

=head2 new

  my $compile_info = SPVM::Builder::CompileInfo->new;

Create a new C<SPVM::Builder::CompileInfo> object.

=head2 to_string

  my $string = $compile_info->to_string;

Get the string representaion of the compile information.

B<Examples:>

  cc foo.o foo.c -O2 -Iinclude_dir

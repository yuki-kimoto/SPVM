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
    $self->{cc} = $_[0];
    return $self;
  }
  else {
    return $self->{cc};
  }
}

sub ccflags {
  my $self = shift;
  if (@_) {
    $self->{ccflags} = $_[0];
    return $self;
  }
  else {
    return $self->{ccflags};
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

sub create_merged_ccflags {
  my ($self) = @_;
  
  my @merged_ccflags;
  
  if (defined $self->optimize) {
    push @merged_ccflags, $self->optimize;
  }
  
  push @merged_ccflags, @{$self->ccflags};

  my $builder_include_dir = $self->builder_include_dir;
  push @merged_ccflags, "-I$builder_include_dir";

  my $include_dirs = $self->include_dirs;
  my @include_dirs_ccflags = map { "-I$_" } @$include_dirs;
  push @merged_ccflags, @include_dirs_ccflags;
  
  return \@merged_ccflags;
}

sub create_compile_command {
  my ($self) = @_;

  my $cc = $self->cc;
  my $class_name = $self->class_name;
  my $output_file = $self->output_file;
  my $source_file = $self->source_file;
  
  my $merged_ccflags = $self->create_merged_ccflags;;
  
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

# Class methods
sub new {
  my $class = shift;
  
  my $self = {@_};

  bless $self, $class;
  
  unless (defined $self->ccflags) {
    $self->ccflags([]);
  }

  unless (defined $self->include_dirs) {
    $self->include_dirs([]);
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

  my $ccflags = $compile_info->ccflags;
  $compile_info->ccflags($ccflags);

Get and set the compileer flags.  The default value is C<[]>.

=head2 optimize

  my $optimize = $compile_info->optimize;
  $compile_info->optimize($optimize);

Get and set the optimize.

=head2 builder_include_dir

  my $builder_include_dir = $compile_info->builder_include_dir;
  $compile_info->builder_include_dir($builder_include_dir);

Get and set the builder include directory.

=head2 include_dirs

  my $include_dirs = $source_file->include_dirs;
  $source_file->include_dirs($include_dirs);

Get and set the include directories. The default is C<[]>.

=head2 source_file

  my $source_file = $compile_info->source_file;
  $compile_info->source_file($source_file);

Get and set the source file.

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

=head2 create_merged_ccflags

  my $merged_ccflags = $compile_info->create_merged_ccflags;

Get the merged ccflags as an array reference.

B<Examples:>

  [qw(-O2 -Iinclude_dir)]

=head2 create_compile_command

  my $compile_command = $compile_info->create_compile_command;

Get the compile command as an array reference.

B<Examples:>

  [qw(cc -c -o foo.o -O2 -Iinclude_dir foo.c)]

=head2 to_string

  my $string = $compile_info->to_string;

Get the string representaion of the L<compile command|/"create_compile_command">.

B<Examples:>

  cc -c -O2 -Iinclude_dir -o foo.o foo.c 

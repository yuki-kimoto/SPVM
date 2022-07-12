package SPVM::Builder::LinkInfo;

use strict;
use warnings;
use Config;
use Carp 'confess';
use File::Basename 'dirname';

# Field Methods
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

sub output_type {
  my $self = shift;
  if (@_) {
    $self->{output_type} = $_[0];
    return $self;
  }
  else {
    return $self->{output_type};
  }
}

sub ld {
  my $self = shift;
  if (@_) {
    $self->{ld} = $_[0];
    return $self;
  }
  else {
    return $self->{ld};
  }
}

sub ld_optimize {
  my $self = shift;
  if (@_) {
    $self->{ld_optimize} = $_[0];
    return $self;
  }
  else {
    return $self->{ld_optimize};
  }
}

sub ldflags {
  my $self = shift;
  if (@_) {
    $self->{ldflags} = $_[0];
    return $self;
  }
  else {
    return $self->{ldflags};
  }
}

sub dynamic_lib_ldflags {
  my $self = shift;
  if (@_) {
    $self->{dynamic_lib_ldflags} = $_[0];
    return $self;
  }
  else {
    return $self->{dynamic_lib_ldflags};
  }
}

sub lib_dirs {
  my $self = shift;
  if (@_) {
    $self->{lib_dirs} = $_[0];
    return $self;
  }
  else {
    return $self->{lib_dirs};
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

  unless (defined $self->ldflags) {
    $self->ldflags([]);
  }

  unless (defined $self->dynamic_lib_ldflags) {
    $self->dynamic_lib_ldflags([]);
  }

  unless (defined $self->lib_dirs) {
    $self->lib_dirs([]);
  }
  
  return $self;
}

sub create_merged_ldflags {
  my ($self) = @_;
  
  my @merged_ldflags;
  
  if (defined $self->ld_optimize) {
    push @merged_ldflags, $self->ld_optimize;
  }
  
  my $output_type = $self->output_type;
  if ($output_type eq 'dynamic_lib') {
    push @merged_ldflags, @{$self->dynamic_lib_ldflags};
  }
  
  my $ldflags = $self->ldflags;
  push @merged_ldflags, @{$self->ldflags};
  
  my $lib_dirs = $self->lib_dirs;
  
  my @lib_dirs_ldflags = map { "-L$_" } @$lib_dirs;
  push @merged_ldflags, @lib_dirs_ldflags;
  
  my $lib_infos = $self->lib_infos;
  my @lib_ldflags = map { my $tmp = $_->to_string; $tmp } @$lib_infos;
  push @merged_ldflags, @lib_ldflags;
  
  return \@merged_ldflags;
}

# Instance Methods
sub create_link_command {
  my ($self) = @_;
  
  my $ld = $self->ld;
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

=head1 Field Methods

=head2 output_file

  my $output_file = $link_info->output_file;
  $link_info->output_file($output_file);

Get and set the object file that is compiled.

=head2 output_type

  my $output_type = $link_info->output_type;
  $link_info->output_type($output_type);

Get and set the output type.

=head2 ld

  my $ld = $link_info->ld;
  $link_info->ld($ld);

Get and set the linker name.

=head2 ld_optimize

  my $ld_optimize = $link_info->ld_optimize;
  $link_info->ld_optimize($ld_optimize);

Get and set the linker optimization option.

=head2 ldflags

  my $ldflags = $link_info->ldflags;
  $link_info->ldflags($ldflags);

Get and set the linker flags.  The default value is C<[]>.

=head2 dynamic_lib_ldflags

  my $dynamic_lib_ldflags = $link_info->dynamic_lib_ldflags;
  $link_info->dynamic_lib_ldflags($dynamic_lib_ldflags);

Get and set the linker flags for dynamic library.  The default value is C<[]>.

=head2 lib_dirs

  my $lib_dirs = $link_info->lib_dirs;
  $link_info->$link_info->lib_dirs($lib_dirs);

Get and set the library directories. The default is C<[]>.

=head2 object_file_infos

  my $object_file_infos = $link_info->object_file_infos;
  $link_info->object_file_infos($object_file_infos);

Get and set the object file informations to be linked. Each object file is a L<SPVM::Builder::ObjectFileInfo> object.

=head2 lib_infos

  my $lib_infos = $link_info->lib_infos;
  $link_info->lib_infos($lib_infos);

Get and set the library informations to be linked. Each object file is a L<SPVM::Builder::LibInfo> object.

=head2 class_name

  my $class_name = $link_info->class_name;
  $link_info->class_name($class_name);

Get and set the class name.

=head2 config

  my $config = $link_info->config;
  $link_info->config($config);

Get and set the L<config|SPVM::Builder::Config> that is used to link the objects.

=head1 Class Methods

=head2 new

  my $link_info = SPVM::Builder::LinkInfo->new;

=head1 Instance Methods

=head2 new

  my $link_info = SPVM::Builder::LinkInfo->new;

Create a new C<SPVM::Builder::LinkInfo> object.

=head2 create_merged_ldflags

  my $merged_ldflags = $link_info->create_merged_ldflags;

Create the merged ldflags as an array reference.

B<Examples:>

  [qw(-shared -O2 -Llibdir -lz)]

=head2 create_link_command

  my $link_command = $link_info->create_link_command;

Create the link command as an array reference.

B<Examples:>

  [qw(cc -o dylib.so foo.o bar.o -shared -O2 -Llibdir -lz)]

=head2 to_string

  my $string = $link_info->to_string;

Get the string representation of the L<link command|/"create_link_command">.

B<Examples:>

  cc -o dylib.so foo.o bar.o -shared -O2 -Llibdir -lz

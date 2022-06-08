package SPVM::Builder::ObjectFileInfo;

use strict;
use warnings;
use Config;
use Carp 'confess';
use File::Basename 'dirname';

use overload bool => sub {1}, '""' => sub { shift->to_string }, fallback => 1;

# Fields
sub object_file {
  my $self = shift;
  if (@_) {
    $self->{object_file} = $_[0];
    return $self;
  }
  else {
    return $self->{object_file};
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

sub is_resource {
  my $self = shift;
  if (@_) {
    $self->{is_resource} = $_[0];
    return $self;
  }
  else {
    return $self->{is_resource};
  }
}

sub is_lib_file {
  my $self = shift;
  if (@_) {
    $self->{is_lib_file} = $_[0];
    return $self;
  }
  else {
    return $self->{is_lib_file};
  }
}

sub is_native_module {
  my $self = shift;
  if (@_) {
    $self->{is_native_module} = $_[0];
    return $self;
  }
  else {
    return $self->{is_native_module};
  }
}

sub is_exe_config {
  my $self = shift;
  if (@_) {
    $self->{is_exe_config} = $_[0];
    return $self;
  }
  else {
    return $self->{is_exe_config};
  }
}

# Methods
sub to_string {
  my ($self) = @_;
  
  return $self->object_file;
}

# Methods
sub new {
  my $class = shift;
  
  my $self = {@_};

  bless $self, $class;
  
  unless (defined $self->ccflags) {
    $self->ccflags([]);
  }
  
  return $self;
}

1;

=head1 NAME

SPVM::Builder::ObjectFileInfo - Object file information

=head1 DESCRIPTION

B<SPVM::Builder::ObjectFileInfo> is a object file information. This infromation is used by the linker.

=head1 FIELDS

Fields of B<SPVM::Builder::ObjectFileInfo>.

=head2 object_file

  my $object_file = $object_file_info->object_file;
  $object_file_info->object_file($object_file);

Get and set the object file that is compiled.

=head2 source_file

  my $source_file = $object_file_info->source_file;
  $object_file_info->source_file($source_file);

Get and set the source file that is the source of the compiled object file.

=head2 cc

  my $cc = $object_file_info->cc;
  $object_file_info->cc($cc);

Get and set the compiler name that compiled the object file.

=head2 ccflags

  my $ccflags = $object_file_info->ccflags;
  $object_file_info->ccflags($ccflags);

Get and set the compiler flags that compiled the object file. The default value is C<[]>.

=head2 class_name

  my $class_name = $object_file_info->class_name;
  $object_file_info->class_name($class_name);

Get and set the class name belonged to when the object file was compiled.

=head2 is_resource

  my $is_resource = $object_file_info->is_resource;
  $object_file_info->is_resource($is_resource);

Get and set if the object file(this is static library(.a)) is a resource.

=head2 is_lib_file

  my $is_lib_file = $object_file_info->is_lib_file;
  $object_file_info->is_lib_file($is_lib_file);

Get and set if the object file is a library file.

=head2 is_native_module

  my $is_native_module = $object_file_info->is_native_module;
  $object_file_info->is_native_module($is_native_module);

Get and set if the object file is compiled from a native source file.

=head2 is_exe_config

  my $is_exe_config = $object_file_info->is_exe_config;
  $object_file_info->is_exe_config($is_exe_config);

Get and set if the object file is compiled using L<SPVM::Builder::Config::Exe>.

=head1 METHODS

Methods of B<SPVM::Builder::ObjectFileInfo>.

=head2 new

  my $object_file_info = SPVM::Builder::ObjectFileInfo->new;

=head2 to_string

  my $object_file = $object_file_info->to_string;

Get the object file name. This is same as C<object_file> field.

=head1 OPERATORS

L<SPVM::BlessedObject::String> overloads the following operators.

=head2 bool

  my $bool = !!$object_file_info;
  
Always true.

=head2 stringify

  my $object_file_name = "$object_file_info";
  
Alias for L</"to_string">.

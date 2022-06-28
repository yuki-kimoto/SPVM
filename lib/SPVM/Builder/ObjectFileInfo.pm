package SPVM::Builder::ObjectFileInfo;

use strict;
use warnings;
use Config;
use Carp 'confess';
use File::Basename 'dirname';

use overload bool => sub {1}, '""' => sub { shift->to_string }, fallback => 1;

# Fields
sub file {
  my $self = shift;
  if (@_) {
    $self->{file} = $_[0];
    return $self;
  }
  else {
    return $self->{file};
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

sub lib_type {
  my $self = shift;
  if (@_) {
    $self->{lib_type} = $_[0];
    return $self;
  }
  else {
    return $self->{lib_type};
  }
}

sub source_type {
  my $self = shift;
  if (@_) {
    $self->{source_type} = $_[0];
    return $self;
  }
  else {
    return $self->{source_type};
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

# Methods
sub to_string {
  my ($self) = @_;
  
  return $self->file;
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

B<SPVM::Builder::ObjectFileInfo> is a object file information.

=head1 FIELDS

Fields of B<SPVM::Builder::ObjectFileInfo>.

=head2 file

  my $file = $object_file_info->file;
  $object_file_info->file($file);

Get and set the path of the object file.

=head2 source_file

  my $source_file = $object_file_info->source_file;
  $object_file_info->source_file($source_file);

Get and set the path of source file.

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

=head2 lib_type

  my $lib_type = $object_file_info->lib_type;
  $object_file_info->lib_type($lib_type);

Get and set the library type if the object is a static library or a dynamic library.

The values are C<static>, or C<dynamic>.

=head2 source_type

  my $source_type = $object_file_info->source_type;
  $object_file_info->source_type($source_type);

Get and set source type. C<native_module> or C<resource>.

=head2 config

  my $config = $object_file_info->config;
  $object_file_info->config($config);

Get and set the L<config|SPVM::Builder::Config> that is used to compile the source file.

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

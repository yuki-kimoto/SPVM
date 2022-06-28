package SPVM::Builder::Resource;

use strict;
use warnings;
use Config;
use Carp 'confess';
use File::Basename 'dirname';

use overload bool => sub {1}, '""' => sub { shift->to_string }, fallback => 1;

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

sub mode {
  my $self = shift;
  if (@_) {
    $self->{mode} = $_[0];
    return $self;
  }
  else {
    return $self->{mode};
  }
}

sub args {
  my $self = shift;
  if (@_) {
    $self->{args} = $_[0];
    return $self;
  }
  else {
    return $self->{args};
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
sub new {
  my $class = shift;
  
  my $self = {@_};

  return bless $self, ref $class || $class;
}

sub to_string {
  my ($self) = @_;
  
  return $self->class_name;
}

1;

=head1 Name

SPVM::Builder::Resource - Resourceurations of Compile and Link of Native Sources

=head1 Synopsys

  my $resource = SPVM::Builder::Resource->new(
    class_name => 'Resource::Zlib::V1_0_0',
    mode => 'prod',
    args => ['foo', 'bar'],
  );

=head1 Description

C<SPVM::Builder::Resource> is a resource that contains a set of C<C>/C<C++> source files and the headers.

=head1 Field Methods

Fields.

=head2 class_name

  my $class_name = $resource->class_name;
  $resource->class_name($class_name);

Get and set the class name of the resource.

=head2 mode

  my $mode = $resource->mode;
  $resource->mode($mode);

Get and set the mode of the config file of the resource.

=head2 args

  my $args = $resource->args;
  $resource->args($args);

Get and set the arguments of the config file of the resource.

=head2 config

  my $config = $resource->config;
  $resource->config($config);

Get and set the config of the resource. The config is a L<SPVM::Builder::Config> object.

=head1 Class Methods

=head2 new

  my $resource = SPVM::Builder::Resource->new;
  my $resource = SPVM::Builder::Resource->new(%fields);
  
Create a L<SPVM::Builder::Resource> object.

B<Examples:>

  my $resource = SPVM::Builder::Resource->new(
    class_name => 'Resource::Zlib::V1_0_0',
    mode => 'prod',
    args => ['foo', 'bar'],
  );

=head1 Instance Methods

=head2 to_string

  my $string = $resource->to_string;

Get the string representation. This is the same as the value of C</"class_name">.

=head1 Operators

C<SPVM::Builder::Resource> overloads the following operators.

=head2 bool

  my $bool = !!$object_file_info;
  
Always true.

=head2 stringify

  my $object_file_name = "$object_file_info";
  
Alias for L</"to_string">.

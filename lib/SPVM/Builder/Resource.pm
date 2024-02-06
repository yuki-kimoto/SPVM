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

sub argv {
  my $self = shift;
  if (@_) {
    $self->{argv} = $_[0];
    return $self;
  }
  else {
    return $self->{argv};
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
  
  bless $self, ref $class || $class;
  
  unless ($self->argv) {
    $self->argv([]);
  }
  
  return $self;
}

sub to_string {
  my ($self) = @_;
  
  return $self->class_name;
}

1;

=head1 Name

SPVM::Builder::Resource - Resource

=head1 Description

The SPVM::Builder::Resource class has methods to manipulate L<resources|SPVM::Document::Resource>.

=head1 Usage

  my $resource = SPVM::Builder::Resource->new(
    class_name => 'Resource::Zlib',
    mode => 'high_performance',
    argv => ['foo', 'bar'],
  );

=head1 Details

See L<SPVM::Document::Resource> about creating and using resources.

=head1 Fields

=head2 class_name

  my $class_name = $resource->class_name;
  $resource->class_name($class_name);

Gets and sets the C<class_name> field, the class name of this resource.

=head2 mode

  my $mode = $resource->mode;
  $resource->mode($mode);

Gets and sets the C<mode> field, the mode of the config file of this resource.

=head2 argv

  my $argv = $resource->argv;
  $resource->argv($argv);

Gets and sets the C<argv> field, an array reference of command line arguments C<@ARGV> given to the config file of this resource.

=head2 config

  my $config = $resource->config;
  $resource->config($config);

Gets and sets the C<config> field, a L<SPVM::Builder::Config> object.

=head1 Class Methods

=head2 new

  my $resource = SPVM::Builder::Resource->new(%fields);

Creates a new L<SPVM::Builder::Resource> object with L</"Fields">.

If a field is not defined, the field is set to the following default value.

=over 2

=item * L</"class_name">

undef

=item * L</"mode">

undef

=item * L</"argv">

[]

=item * L</"config">

undef

=back

=head1 Instance Methods

=head2 to_string

  my $string = $resource->to_string;

Returns the L</"class_name"> field.

=head1 Operators

Overloads the following operators.

=head2 bool

  my $bool = !!$resource;

Always true.

=head2 stringify

  my $class_name = "$resource";

The alias for the L</"to_string"> method.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

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

=head1 NAME

SPVM::Builder::Resource - Resourceurations of Compile and Link of Native Sources

=head1 SYNOPSYS

  my $resource = SPVM::Builder::Resource->new(
    class_name => 'Resource::Zlib::V1_0_0',
    mode => 'prod',
    args => ['foo', 'bar'],
  );

=head1 DESCRIPTION

L<SPVM::Builder::Resource> is resourceuration of c/c++ compile and link.

=head1 FIELDS

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

=head1 CLASS METHODS

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



=head1 INSTANCE METHODS

=head2 set_std

  $resource->set_std($std);

Add the value that is converted to C<-std=$std> after the last element of C<ccflags> field.

B<Example:>

  $resource->set_std('gnu99');

=head2 add_ccflags

  $resource->add_ccflags(@ccflags);

Add values after the last element of C<ccflags> field.

=head2 add_ldflags

  $resource->add_ldflags(@ldflags);

Add values after the last element of C<ldflags> field.

=head2 add_include_dirs

  $resource->add_include_dirs(@include_dirs);

Add values after the last element of C<include_dirs> field.

=head2 add_lib_dirs

  $resource->add_lib_dirs(@lib_dirs);

Add values after the last element of  C<lib_dirs> field.

=head2 add_source_files

  $resource->add_source_files(@source_files);

Add the values after the last element of C<source_files> field.

=head2 add_libs

  $resource->add_libs(@libs);

Add the values after the last element of C<libs> field.

B<Examples:>

  $resource->add_libs('gsl');

=head2 add_static_libs

  $resource->add_static_libs(@libs);

Add the values that each element is converted to the following hash reference after the last element of C<libs> field.

  {type => 'static', name => $lib}

B<Examples:>

  $resource->add_static_libs('gsl');

=head2 add_dynamic_libs

  $resource->add_dynamic_libs(@libs);

Add the values that each element is converted to the following hash reference after the last element of C<libs> field.

  {type => 'dynamic', name => $lib}

B<Examples:>

  $resource->add_dynamic_libs('gsl');

=head2 to_hash

  my $resource = $resource->to_hash;

Convert L<SPVM::Builder::Resource> to a hash reference.

=head2 search_lib_dirs_from_cc_info

  my $lib_dirs = $resource->search_lib_dirs_from_cc_info;

Get the library searching directories parsing the infomation the compiler has.

=head2 search_lib_dirs_from_resource_libpth

  my $lib_dirs = $resource->search_lib_dirs_from_resource_libpth;

Get the library searching directories parsing C<libpth> of L<Resource>.

=head2 search_include_dirs_from_resource_incpth

  my $include_dirs = $resource->search_include_dirs_from_resource_incpth;

Get the header searching directories parsing C<incpth> of L<Resource>.

=head2 sub get_include_dir

  my $include_dir = $resource->get_include_dir(__FILE__);

Get the header include directory from the resource file name.

=head2 get_src_dir

  my $src_dir = $resource->get_src_dir(__FILE__);

Get the source directory from the resource file name.

=head2 get_lib_dir

  my $lib_dir = $resource->get_lib_dir(__FILE__);

Get the library directory from the resource file name.

=head2 output_type

  my $output_type = $resource->output_type;
  $resource->output_type($type);

=head2 use_resource

  $resource->use_resource($resource);
  $resource->use_resource('Resource::Zlib::V1_0_0');
  $resource->use_resource('Resource::Zlib::V1_0_0', mode => 'prod', args => ['foo', 'bar']);

Use a resource. 

The first argument is a L<SPVM::Builder::Resource> object.

If the first argument is a class name of the resource, a L<SPVM::Builder::Resource> object is created by L<SPVM::Builder::Resource|/"new"> method with C<class_name> option.

  my $resource = SPVM::Builder::Resource->new(class_name => 'Resource::Zlib::V1_0_0');
  $resource->use_resource($resource);

If the rest arguments are used as the options of L<SPVM::Builder::Resource|/"new"> of L<SPVM::Builder::Resource>.

  my $resource = SPVM::Builder::Resource->new(
    class_name => 'Resource::Zlib::V1_0_0',
    mode => 'prod',
    args => ['foo', 'bar'],
  );
  $resource->use_resource($resource);

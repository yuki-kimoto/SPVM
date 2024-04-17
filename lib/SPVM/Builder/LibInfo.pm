package SPVM::Builder::LibInfo;

use strict;
use warnings;
use Config;
use Carp 'confess';
use File::Basename 'dirname';

use overload bool => sub {1}, '""' => sub { shift->to_string }, fallback => 1;

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

sub name {
  my $self = shift;
  if (@_) {
    $self->{name} = $_[0];
    return $self;
  }
  else {
    return $self->{name};
  }
}

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

sub is_static {
  my $self = shift;
  if (@_) {
    $self->{is_static} = $_[0];
    return $self;
  }
  else {
    return $self->{is_static};
  }
}

sub is_abs {
  my $self = shift;
  if (@_) {
    $self->{is_abs} = $_[0];
    return $self;
  }
  else {
    return $self->{is_abs};
  }
}

# Class Methods
sub new {
  my $class = shift;
  
  my $self = {@_};
  
  bless $self, $class;
  
  my $config = $self->config;
  
  unless ($config) {
    confess("The \"config\" field must be defined.");
  }
  
  return $self;
}

# Instance Methods
sub create_ldflags {
  my ($self) = @_;
  
  my @link_command_ldflags;
  
  if ($self->is_abs) {
    if (defined $self->file) {
      push @link_command_ldflags, $self->file;
    }
    else {
      push @link_command_ldflags, "";
    }
  }
  else {
    my $name = $self->name;
    if ($self->is_static) {
      my $config = $self->config;
      
      my $static_lib_begin = $config->static_lib_ldflag->[0];
      my $static_lib_end = $config->static_lib_ldflag->[1];
      
      warn "$static_lib_begin -l$name $static_lib_end";
      
      push @link_command_ldflags, "$static_lib_begin -l$name $static_lib_end";
    }
    else {
      push @link_command_ldflags, "-l$name";
    }
  }
  
  return \@link_command_ldflags;
}

sub to_string { 
  my ($self) = @_;
  
  return $self->name;
}

1;

=head1 Name

SPVM::Builder::LibInfo - Library Information for A Linker

=head1 Description

The SPVM::Builder::LibInfo class has methods to manipulate library information for a linker.

=head1 Usage

  my $lib_info = SPVM::Builder::LibInfo->new(%fields);
  my $lib_ldflags = $lib_info->create_ldflags;

=head1 Fields

=head2 config

  my $config = $lib_info->config;
  $lib_info->config($config);

Gets and sets the C<config> field, a L<SPVM::Builder::Config> object.

=head2 name

  my $name = $lib_info->name;
  $lib_info->name($name);

Gets and sets the C<name> field, a library name.

Examples:
  
  $lib_info->name('z');
  
  $lib_info->name('png');

=head2 file

  my $file = $lib_info->file;
  $lib_info->file($file);

Gets and sets the C<file> field, the absolute path of the library file such as C</path/libz.so>, C</path/libpng.a>.

=head2 is_static

  my $is_static = $lib_info->is_static;
  $lib_info->is_static($is_static);

Gets and sets the C<is_static> field. If this field is a true value, this library is linked statically. Otherwise, is linked dynamically.

=head2 is_abs

  my $is_abs = $lib_info->is_abs;
  $lib_info->is_abs($is_abs);

Gets and sets the C<is_abs> field. If this field is a true value, the library is linked by the absolute path L</"file">. Otherwise, is linked by the relative path from library search path.

=head1 Class Methods

=head2 new

  my $lib_info = SPVM::Builder::LibInfo->new(%fields);

Creates a new L<SPVM::Builder::LibInfo> object given L<fields|/"Fields">.

The C<config> field must be defined.

Field Default Values:

=over 2

=item * All Fields

  undef

=back

Exceptions:

The "config" field must be defined.

=head1 Instance Methods

=head2 create_ldflags

  my $lib_ldflags = $lib_info->create_ldflags;

Creates an array reference of the library part of the linker flags given to the linker L<ld|SPVM::Builder::Config/"ld">, and returns it.

Return Value Examples:
  
  ["-lfoo", "-Wl,-Bstatic -lfoo -Wl,-Bdynamic", "/path/foo.so", "/path/foo.a"]

=head2 to_string

  my $lib_name = $lib_info->to_string;

Returns the L</"name"> field.

=head1 Operators

Overloads the following operators.

=head2 bool

  my $bool = !!$lib_info;

Always true.

=head2 stringify

  my $lib_name = "$lib_info";

Alias for the L</"to_string"> method.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

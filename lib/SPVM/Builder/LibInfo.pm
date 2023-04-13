package SPVM::Builder::LibInfo;

use strict;
use warnings;
use Config;
use Carp 'confess';
use File::Basename 'dirname';

use overload bool => sub {1}, '""' => sub { shift->to_string }, fallback => 1;

# Fields
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

sub static {
  my $self = shift;
  if (@_) {
    $self->{static} = $_[0];
    return $self;
  }
  else {
    return $self->{static};
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

sub static_option_cb {
  my $self = shift;
  if (@_) {
    $self->{static_option_cb} = $_[0];
    return $self;
  }
  else {
    return $self->{static_option_cb};
  }
}

# Class Methods
sub new {
  my $class = shift;
  
  my $self = {@_};

  bless $self, $class;
  
  unless (defined $self->static_option_cb) {
    my $default_static_option_cb = sub {
      my ($self, $name) = @_;
      
      $name = "-Wl,-Bstatic -l$name -Wl,-Bdynamic";
      
      return $name;
    };
    $self->static_option_cb($default_static_option_cb);
  }
  
  return $self;
}

# Instance Methods
sub to_string { 
  my ($self) = @_;
  
  return $self->name;
}

sub to_arg {
  my ($self) = @_;
  
  my $link_command_arg;
  
  if ($self->is_abs) {
    if (defined $self->file) {
      $link_command_arg = $self->file;
    }
    else {
      $link_command_arg = "";
    }
  }
  else {
    my $name = $self->name;
    if ($self->static) {
      $link_command_arg = $self->static_option_cb->($self, $name);
    }
    else {
      $link_command_arg = "-l$name";
    }
  }
  
  return $link_command_arg;
}

1;

=head1 Name

SPVM::Builder::LibInfo - Library Information

=head1 Description

The SPVM::Builder::LibInfo class has methods to manipulate library information.

=head1 Fields

=head2 name

  my $name = $lib_info->name;
  $lib_info->name($name);

Gets and sets the library name.

Examples:
  
  $lib_info->name('z');
  
  $lib_info->name('png');

=head2 file

  my $file = $lib_info->file;
  $lib_info->file($file);

Gets and sets the absolute path of the library file like C</path/libz.so>, C</path/libpng.a>, etc.

=head2 static

  my $static = $lib_info->static;
  $lib_info->static($static);

Gets and sets the flag whether a static library is linked.

Default:

A false value.

=head2 is_abs

  my $is_abs = $lib_info->is_abs;
  $lib_info->is_abs($is_abs);

If the C<is_abs> is true, the library is linked by the library name like C<-lfoo>.

If it is false, the library is linked by the absolute path of the library like C</path/libfoo.so>.

If this field is C<undef>, whether the library is linked by the library name or the absolute path is automatically decided.

=head2 static_option_cb

  my $static_option_cb = $lib_info->static_option_cb;
  $lib_info->static_option_cb($static_option_cb);

Gets and sets the callback to create a linker option to link a static library.

Default:

  sub {
    my ($self, $name) = @_;
    
    $name = "-Wl,-Bstatic -l$name -Wl,-Bdynamic";
    
    return $name;
  };

=head1 Class Methods

=head2 new

  my $lib_info = SPVM::Builder::LibInfo->new;

=head1 Instance Methods

=head2 to_arg

  my $link_command_arg = $lib_info->to_arg;

Creates an argument of the link command from the L</"is_abs"> field and L</"static"> field, and returns it.

The following one is an example of the return value.
  
  -lfoo
  -Wl,-Bstatic -lfoo -Wl,-Bdynamic
  /path/foo.so
  /path/foo.a

=head2 to_string

  my $lib = $lib_info->to_string;

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

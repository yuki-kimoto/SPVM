package SPVM::Builder::Native::BasicType;

use strict;
use warnings;

sub pointer {
  my $self = shift;
  if (@_) {
    $self->{pointer} = $_[0];
    return $self;
  }
  else {
    return $self->{pointer};
  }
}

sub boot_env {
  my $self = shift;
  if (@_) {
    $self->{boot_env} = $_[0];
    return $self;
  }
  else {
    return $self->{boot_env};
  }
}

sub runtime {
  my $self = shift;
  if (@_) {
    $self->{runtime} = $_[0];
    return $self;
  }
  else {
    return $self->{runtime};
  }
}

# Private Instance Methods - Only used in core.
sub _get_native_method_names {
  my ($self) = @_;
  
  my $methods_length = $self->get_methods_length;
  
  my $native_method_names = [];
  
  for (my $method_index = 0; $method_index < $methods_length; $method_index++) {
    my $method = $self->get_method_by_index($method_index);
    my $method_name = $method->get_name;
    if ($method->is_native) {
      push @$native_method_names, $method_name;
    }
  }
  
  return $native_method_names;
}

sub _get_precompile_method_names {
  my ($self) = @_;
  
  my $methods_length = $self->get_methods_length;
  
  my $precompile_method_names = [];
  
  for (my $method_index = 0; $method_index < $methods_length; $method_index++) {
    my $method = $self->get_method_by_index($method_index);
    my $method_name = $method->get_name;
    if ($method->is_precompile) {
      push @$precompile_method_names, $method_name;
    }
  }
  
  return $precompile_method_names;
}

sub _get_class_file {
  my ($self) = @_;
  
  my $class_dir = $self->get_class_dir;
  
  unless ($class_dir) {
    die "The class_dir field must be defined.";
  }
  
  my $class_rel_file = $self->get_class_rel_file;
  
  my $class_file = "$class_dir/$class_rel_file";
  
  return $class_file;
}

1;

=head1 Name

SPVM::Builder::Native::BasicType - Basic Type Native APIs

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

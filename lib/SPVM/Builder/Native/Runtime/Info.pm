package SPVM::Builder::Native::Runtime::Info;

use strict;
use warnings;

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

# Class Methods
sub new {
  my $class = shift;
  
  my $self = bless {
    @_
  }, ref $class || $class;
  
  return $self;
}

sub get_class_names {
  my ($self) = @_;
  
  my $class_names = [];
  
  my $basic_type_names = $self->get_basic_type_names;
  
  for my $basic_type_name (@$basic_type_names) {
    if ($basic_type_name =~ /^[A-Z]/ && $basic_type_name !~ /::anon::/) {
      push @$class_names, $basic_type_name;
    }
  }
  
  return $class_names;
}
  
1;

=head1 Name

SPVM::Builder::Native::Runtime::Info - Runtime Information

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

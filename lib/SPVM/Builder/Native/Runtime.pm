package SPVM::Builder::Native::Runtime;

use strict;
use warnings;

# Fields
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

sub compiler {
  my $self = shift;
  if (@_) {
    $self->{compiler} = $_[0];
    return $self;
  }
  else {
    return $self->{compiler};
  }
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

SPVM::Builder::Native::Runtime - Runtime

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

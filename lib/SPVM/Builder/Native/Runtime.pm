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

sub env {
  my $self = shift;
  if (@_) {
    $self->{env} = $_[0];
    return $self;
  }
  else {
    return $self->{env};
  }
}

sub get_basic_types {
  my ($self, $options) = @_;
  
  $options ||= {};
  
  my $basic_types_length = $self->get_basic_types_length;
  
  my $basic_types = [];
  
  my $match = 1;
  
  for (my $id = 0; $id < $basic_types_length; $id++) {
    my $basic_type = $self->get_basic_type_by_id($id);
    
    if (exists $options->{category}) {
      my $categories = $options->{category};
      
      my $category_match = 0;
      for my $category (@$categories) {
        if ($basic_type->get_category == $category) {
          $category_match = 1;
          last;
        }
      }
      
      unless ($category_match) {
        next;
      }
    }
    
    if (exists $options->{is_anon}) {
      my $is_anon = $options->{is_anon};
      
      my $basic_type_name = $basic_type->get_name;
      my $basic_type_is_anon = $basic_type->is_anon;
      
      my $is_anon_match = !!$basic_type->is_anon == !!$is_anon;
      
      unless ($is_anon_match) {
        next;
      }
    }
    
    push @$basic_types, $basic_type;
  }
  
  return $basic_types;
}

1;

=head1 Name

SPVM::Builder::Native::Runtime - Runtime

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

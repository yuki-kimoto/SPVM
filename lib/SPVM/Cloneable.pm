package SPVM::Cloneable;

1;

=head1 Name

SPVM::Cloneable - Interface Type to Clone Object

=head1 Description

The Cloneable interface in L<SPVM> represents a cloneable interface.

=head1 Usage
  
  class Point {
    interface Cloneable;
    
    method clone : Point () {
      
      my $new_point = Point->new($self->x, $self->y);
      
      return $new_point;
    }
  }

=head1 Interface Methods

=head2 clone

C<required method clone : object ();>

The implementation must return the cloned object.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

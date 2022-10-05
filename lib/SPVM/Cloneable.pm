package SPVM::Cloneable;

1;

=head1 Name

SPVM::Cloneable - Interface Type to Clone Object

=head1 Usage
  
  class Point {
    interface Cloneable;
    
    method clone : Point () {
      my $new_point = Point->new($self->x, $self->y);
      
      return $new_point;
    }
  }

=head1 Description

L<Cloneable|SPVM::Cloneable> is a callback interface to clone a object.

=head1 Interface Methods

Interface methods.

=head2 clone

  required method clone : object ();

The implementation must return the cloned object.

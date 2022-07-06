package SPVM::Cloneable;

1;

=head1 Name

SPVM::Cloneable - A Interface Type to Clone a Object

=head1 Usage
  
  class Point {
    interface Cloneable;
    
    method cloneable_clone : object () {
      my $new_point = Point->new($self->x, $self->y);
      
      return $new_point;
    }
  }

=head1 Description

L<Cloneable|SPVM::Cloneable> is a callback interface to clone a object.

=head1 Interface Methods

Interface methods.

=head2 cloneable_clone

  required method cloneable_clone : object ();

The implementation must return the cloned object.

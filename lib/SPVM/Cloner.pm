package SPVM::Cloner;

1;

=head1 NAME

SPVM::Cloner - Interface Type for the Callback to Clone a Object

=head1 SYNOPSYS
  
  use Cloner;
  use Point;
  
  my $cloner = (Cloner)method : object ($object : object) {
    my $point = (Point)$object;
    
    my $cloned_point = Point->new_xy($point->x, $point->y);
    
    return $cloned_point;
  };
  
  my $point = Point->new_xy(1, 2);
  my $cloned_point = $cloner->($point);

=head1 DESCRIPTION

L<Cloner|SPVM::Cloner> is the interface type for the callback to clone a object.

=head1 INTERFACE METHODSS

  required method : object ($object : object);

The implementation must receive a object and return the cloned object.

package SPVM::Cloner;

1;

=head1 NAME

SPVM::Cloner - A Callback Type to Clone a Object

=head1 SYNOPSYS
  
  use Cloner;
  
  my $cloner : Cloner = method : object ($object : object) {
    my $point = (Point)$object;
    
    my $new_point = Point->new($point->x, $point->y);
    
    return $new_point;
  };
  
  my $point = Point->new(1, 2);
  my $point_clone = $cloner->($point);

=head1 DESCRIPTION

L<Cloner|SPVM::Cloner> is a callback type to clone a object.

=head1 CALLBACK METHOD

  required method : object ($object : object);

The implementation must receive a object and return the cloned object.

package SPVM::Cloner;

1;

=head1 NAME

SPVM::Cloner - a callback interface to clone a object

=head1 SYNOPSYS
  
  use SPVM::Cloner;
  
  my $cloner : SPVM::Cloner = sub : object ($self : self, $object : object) {
    my $point = (SPVM::Point)$object;
    
    my $new_point = SPVM::Point->new($point->x, $point->y);
    
    return $new_point;
  };
  
  my $point = SPVM::Point->new(1, 2);
  my $point_clone = $cloner->($point);

=head1 DESCRIPTION

L<SPVM::Cloner> is a callback interface to clone a object.

=head1 CALLBACK METHOD INTERFACE

  sub : object ($self : self, $object : object);

This method clone object.

This method is planned to be implemented in other classes.

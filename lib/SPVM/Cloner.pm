package SPVM::Cloner;

1;

=head1 NAME

SPVM::Cloner - a callback type to clone a object

=head1 SYNOPSYS
  
  use SPVM::Cloner;
  
  my $cloner : SPVM::Cloner = sub : object ($self : self, $obj : object) {
    my $point = (SPVM::Point)$obj;
    
    my $new_point = SPVM::Point->new($point->x, $point->y);
    
    return $new_point;
  };
  
  my $point = SPVM::Point->new(1, 2);
  my $point_clone = $cloner->($point);

=head1 DESCRIPTION

L<SPVM::Cloner> is a callback type to clone a object.

=head1 CALLBACK METHOD

  sub : object ($self : self, $obj : object);

This method should be cloned object in the method implementation.

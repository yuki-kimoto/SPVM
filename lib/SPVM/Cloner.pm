package SPVM::Cloner;

use SPVM 'SPVM::Cloner';

1;

=head1 NAME

SPVM::Cloner - a callback type to clone a object

=head1 SYNOPSYS
  
  use SPVM::Cloner;
  
  my $cloner : SPVM::Cloner = sub : object ($self : self, $obj : object) {
    my $point = (SPVM::Point)$obj;
    
    my $new_point = SPVM::Point->new;
    $new_point->set_x($point->x);
    $new_point->set_y($point->y);
    
    return $new_point;
  };
  
  my $message = $cloner->();

=head1 DESCRIPTION

L<SPVM::Cloner> is a callback type to clone a object.

=head1 CALLBACK METHOD

  sub : object ($self : self, $obj : object);

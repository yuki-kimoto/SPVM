package SPVM::Stringer;

1;

=head1 NAME

SPVM::Stringer - a callback type to stringify a object

=head1 SYNOPSYS
  
  use SPVM::Stringer;
  
  my $stringer = (SPVM::Stringer)sub : string ($self : self, $object : object) {
    my $point = (SPVM::Point)$object;
    my $x = $point->x;
    my $y = $point->y;
    
    my $string = "($x, $y)";
    
    return $string;
  };
  
  my $point = SPVM::Point->new(1, 2);
  my $string = $stringer->($point);

=head1 DESCRIPTION

L<SPVM::Stringer> is a callback type to stringify a object.

=head1 CALLBACK METHOD INTERFACE

  sub : string ($self : self, $object : object)

This method receives a object and return the string expression.

This method is planned to be implemented in other classes.

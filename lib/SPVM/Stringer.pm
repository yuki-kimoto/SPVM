package SPVM::Stringer;

1;

=head1 NAME

SPVM::Stringer - a callback type for stringification

=head1 SYNOPSYS
  
  use SPVM::Stringer;
  
  my $stringer : SPVM::Stringer = sub : string ($self : self, $obj : object) {
    my $point = (SPVM::Point)$obj;
    my $x = $point->x;
    my $y = $point->y;
    
    my $str = "($x, $y)";
    
    return $str;
  };
  
  my $point = SPVM::Point->new(1, 2);
  my $str = $stringer->($point);

=head1 DESCRIPTION

L<SPVM::Stringer> is a callback type to stringify a object.

=head1 CALLBACK METHOD

  sub : string ($self : self, $obj : object)

This method should receive a object and return the string expression in the method imlementaion.

package SPVM::Stringer;

1;

=head1 NAME

SPVM::Stringer - A Callback Yype to Stringify a Object

=head1 SYNOPSYS
  
  use Stringer;
  
  my $stringer : Stringer = method : string ($object : object) {
    my $point = (Point)$object;
    my $x = $point->x;
    my $y = $point->y;
    
    my $string = "($x, $y)";
    
    return $string;
  };
  
  my $point = Point->new(1, 2);
  my $string = $stringer->($point);

=head1 DESCRIPTION

L<Stringer|SPVM::Stringer> is a callback type to stringify a object.

=head1 CALLBACK METHOD

  required method : string ($object : object)

The implementation must receive a object and return the string expression.

package SPVM::Util;

use SPVM 'SPVM::Util';

1;

=head1 NAME

SPVM::Util - Variouse utilities

=head1 SYNOPSYS
  
  use SPVM::Util;
  
  # Stringify all object and join them by the specific separator
  my $objects = new Foo[3];
  my $str = SPVM::Util->joino(",", $objects, sub : string ($self : self, $obj : object) {
    my $point = (SPVM::Point)$obj;
    my $x = $point->x;
    my $y = $point->y;
    
    my $str = "($x, $y)";
    
    return $str;
  });
  
  # split a string by the specific separator
  my $str = "foo,bar,baz";
  my $splited_strs = split(",", $str);

=head1 DESCRIPTION

Unix standard library.

=head1 CLASS METHODS

=head2 joino

  sub joino : string ($sep : string, $objects : oarray, $stringer : SPVM::Stringer)

Stringify all objects and join them by specific separator.
Each object must have to_str method defined in L<SPVM::Stringer>. otherwise a exception occur.

=head2 split

  sub split : string[] ($sep : string, $string : string)

Split a string by the specific separator.

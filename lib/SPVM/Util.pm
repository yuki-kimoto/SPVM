package SPVM::Util;

use SPVM 'SPVM::Util';

1;

=head1 NAME

SPVM::Util - Variouse utilities

=head1 SYNOPSYS
  
  use SPVM::Util;
  
  # Copy object array
  my $objects = [(object)SPVM::Int->new(1), SPVM::Int->new(2), SPVM::Int->new(3)];
  my $objects_copy = copy_oarray($objects, sub : object ($self : self, $obj : object) {
    my $int_obj = (SPVM::Int)$obj;
    my $new_int_obj = SPVM::Int->new($int_obj->val);
    return $new_int_obj;
  });
  
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

=head2 copy_oarray

  sub copy_oarray : object[] ($objects : object[], $cloner : SPVM::Cloner)

Copy object array. You must specify a L<SPVM::Cloner> object to copy each element.

=head2 equals_oarray

  sub sub equals_oarray : int ($objs1 : oarray, $objs2 : oarray, $equality_checker : SPVM::EqualityChecker)

Check equality of two objects. You must sepecify a L<SPVM::EqualityChecker> object to check the equality of each element.

$objs1 and $objs2 and $equality_checker must be defined, otherwise a exception occur.

Return 1 if the length of $objs1 and $objs2 is same and all element is same, otherwise return 0.

=head2 joino

  sub joino : string ($sep : string, $objects : oarray, $stringer : SPVM::Stringer)

Stringify all objects and join them by specific separator.
You must specify a L<SPVM::Stringer> object to stringify each element.

If separater is undef, a exception occurs.

If object array is undef, a exception occurs.

=head2 split

  sub split : string[] ($sep : string, $string : string)

Split a string by the specific separator.

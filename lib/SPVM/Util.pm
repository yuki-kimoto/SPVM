package SPVM::Util;

use SPVM 'SPVM::Util';

1;

=head1 NAME

SPVM::Util - Unix standard library

=head1 SYNOPSYS
  
  use SPVM::Util;
  
  # Stringify all object and join them by separator
  my $objects = new Foo[3];
  my $str = SPVM::Util->joino(",", $objects);
  
  # Sleep 3 seconds
  
  SPVM::Util->sleep(3);

=head1 DESCRIPTION

Unix standard library.

=head1 CLASS METHODS

=head2 joino

  sub joino : string ($sep : string, $objects : oarray)

Stringify all objects and join them by specific separator.
Each object must be assigned to L<SPVM::Stringer>.

=head2 split

  sub split : string[] ($sep : string, $string : string)

Split string by separator.

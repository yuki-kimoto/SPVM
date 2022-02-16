package SPVM::Stringable;

1;

=head1 NAME

SPVM::Stringable - A Interface Type to Stringify a Object

=head1 SYNOPSYS
  
  class Point {
    implement Stringable;
  
    method to_string : string ();
      my $x = $sel->x;
      my $y = $sel->y;
      
      my $string = "($x, $y)";
      
      return $string;
    };
  }

=head1 DESCRIPTION

L<Stringable|SPVM::Stringable> is a interface type to stringify a object.

=head1 INTERFACE METHODS

Interface methods.

=head2 to_string

  method to_string : string ();

The implementation must return the string expression.

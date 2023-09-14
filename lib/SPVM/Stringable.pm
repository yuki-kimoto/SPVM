package SPVM::Stringable;

1;

=head1 Name

SPVM::Stringable - A Interface Type to Stringify a Object

=head1 Usage
  
  class Point {
    interface Stringable;
  
C<method to_string : string ();>
      my $x = $sel->x;
      my $y = $sel->y;
      
      my $string = "($x,$y)";
      
      return $string;
    };
  }

=head1 Description

L<Stringable|SPVM::Stringable> is an interface type to stringify a object.

=head1 Interface Methods

Interface methods.

=head2 to_string

C<required method to_string : string ();>

The implementation must return the string expression.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

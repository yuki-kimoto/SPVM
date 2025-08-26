package SPVM::Stringable;

1;

=head1 Name

SPVM::Stringable - Stringable Interface

=head1 Usage
  
  class Point {
    interface Stringable;
    
    method to_string : string () {
      
      my $x = $sel->x;
      my $y = $sel->y;
      
      my $string = "($x,$y)";
      
      return $string;
    };
  }

=head1 Description

Stringable interface in L<SPVM> is the interface for stringable classes.

=head1 Interface Methods

=head2 to_string

C<required method to_string : string ();>

Returns the string representation for the instance.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

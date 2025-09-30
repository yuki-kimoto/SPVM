package SPVM::Countable;

1;

=head1 Name

SPVM::Countable - Countable Interface

=head1 Usage
  
  class Point {
    interface Countable;
    
    has elements : int[]
    
    method length : string () {
      
      my $length = @{$self->{elements}};
      
      return $length;
    };
  }

=head1 Description

Countable interface in L<SPVM> is the interface for countable classes.

=head1 Interface Methods

=head2 to_string

C<required method length : int ();>

Meants to return the lenght of the elements.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

package SPVM::Comparator::Byte;

1;

=head1 NAME

SPVM::Comparator::Byte - a callback interface for byte comparation

=head1 SYNOPSYS
  
  use SPVM::Comparator::Byte;
  
  my $comparator : SPVM::Comparator::Byte = sub : int ($self : self, $a : byte, $b : byte); {
    return $a <=> $b;
  };
  
  my $result = $comparator->(3, 5);

=head1 DESCRIPTION

L<Comparator::Byte|SPVM::Comparator::Byte> is a callback interface to compare two byte values.

=head1 CALLBACK METHOD INTERFACE

  sub : int ($self : self, $a : byte, $b : byte);

This method must receive two numbers and return 1 if $a is more than $b, -1 if $x is less than $b, 0 if $a equals $b in the implementation.

This method is planned to be implemented in other classes.

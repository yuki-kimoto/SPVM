package SPVM::Comparator::Byte;

1;

=head1 NAME

SPVM::Comparator::Byte - Comparator::Byte in SPVM | a callback type for byte comparation

=head1 SYNOPSYS
  
  use Comparator::Byte;
  
  my $comparator : Comparator::Byte = method : int ($a : byte, $b : byte); {
    return $a <=> $b;
  };
  
  my $result = $comparator->(3, 5);

=head1 DESCRIPTION

L<Comparator::Byte|SPVM::Comparator::Byte> is a callback type to compare two byte values.

=head1 CALLBACK METHOD INTERFACE

  method : int ($a : byte, $b : byte);

This method must receive two numbers and return 1 if $a is more than $b, -1 if $x is less than $b, 0 if $a equals $b in the implementation.

This method is planned to be implemented in other classes.

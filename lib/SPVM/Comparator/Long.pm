package SPVM::Comparator::Long;

1;

=head1 NAME

SPVM::Comparator - a callback type for comparation

=head1 SYNOPSYS
  
  use SPVM::Comparator::Long;
  
  my $comparator : SPVM::Comparator::Long = sub : int ($self : self, $a : long, $b : long); {
    return $a <=> $b;
  };
  
  my $result = $comparator->(3, 5);

=head1 DESCRIPTION

L<SPVM::Comparator> is a callback type to compare two numbers.

=head1 CALLBACK METHOD

  sub : int ($self : self, $a : long, $b : long);

This method should receive two numbers and return 1 if $a is more than $b, -1 if $x is lass than $b, 0 if $a equals $b in the implementation.

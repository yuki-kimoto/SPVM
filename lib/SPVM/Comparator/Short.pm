package SPVM::Comparator::Short;

1;

=head1 NAME

SPVM::Comparator::Short - a callback type for short comparation

=head1 SYNOPSYS
  
  use SPVM::Comparator::Short;
  
  my $comparator : SPVM::Comparator::Short = sub : int ($self : self, $a : short, $b : short); {
    return $a <=> $b;
  };
  
  my $result = $comparator->(3, 5);

=head1 DESCRIPTION

L<SPVM::Comparator> is a callback type to compare two numbers.

=head1 CALLBACK METHOD

  sub : int ($self : self, $a : short, $b : short);

This method should receive two numbers and return 1 if $a is more than $b, -1 if $x is lass than $b, 0 if $a equals $b in the implementation.

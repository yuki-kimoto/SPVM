package SPVM::Comparator::Short;

1;

=head1 NAME

SPVM::Comparator::Short - A Callback Type for short Comparation

=head1 SYNOPSYS
  
  use Comparator::Short;
  
  my $comparator : Comparator::Short = method : int ($a : short, $b : short); {
    return $a <=> $b;
  };
  
  my $result = $comparator->(3, 5);

=head1 DESCRIPTION

L<Comparator::Short|SPVM::Comparator::Short> is an interface type for the callback to compare two short values.

=head1 INTERFACE METHOD

  required method : int ($a : short, $b : short);

The implementation must receive two numbers and return 1 if $a is more than $b, -1 if $x is less than $b, 0 if $a equals $b in the implementation.

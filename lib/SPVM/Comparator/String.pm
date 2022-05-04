package SPVM::Comparator::String;

1;

=head1 NAME

SPVM::Comparator::String - A Callback Type for string Comparation

=head1 SYNOPSYS
  
  use Comparator::String;
  
  my $comparator : Comparator::String = method : int ($a : string, $b : string); {
    return $a cmp $b;
  };
  
  my $result = $comparator->(3, 5);

=head1 DESCRIPTION

L<Comparator::String|SPVM::Comparator::String> is a callback type to compare two strings.

=head1 CALLBACK METHOD

  required method : int ($a : string, $b : string);

The implementation must receive two strings and return 1 if $a is more than $b, -1 if $x is less than $b, 0 if $a equals $b in the implementation.

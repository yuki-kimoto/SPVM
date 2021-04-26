package SPVM::Comparator::String;

1;

=head1 NAME

SPVM::Comparator::String - a callback type for string comparation

=head1 SYNOPSYS
  
  use SPVM::Comparator::String;
  
  my $comparator : SPVM::Comparator::String = sub : int ($self : self, $a : string, $b : string); {
    return $a cmp $b;
  };
  
  my $result = $comparator->(3, 5);

=head1 DESCRIPTION

L<SPVM::Comparator> is a callback type to compare two strings.

=head1 CALLBACK METHOD

  sub : int ($self : self, $a : string, $b : string);

This method should receive two strings and return 1 if $a is more than $b, -1 if $x is less than $b, 0 if $a equals $b in the implementation.

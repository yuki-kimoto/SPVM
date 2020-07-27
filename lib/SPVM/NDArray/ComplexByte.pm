=head1 NAME

SPVM::NDArray::ComplexByte - N-Dimension Array of SPVM::Complex_2b

=head1 SYNOPSYS
  
  my $ndarray = SPVM::NDArray::ComplexByte->new;
  my $dim1 = 3;
  my $dim2 = 4;
  my $length = $dim1 * $dim2;
  $ndarray->{base} = new SPVM::Complex_2b[$length];
  $ndarray->{length} = $length;
  $ndarray->{shape} = [$dim1, $dim2];

=head1 DESCRIPTION

SPVM::NDArray::ComplexByte is N-Dimension Array of SPVM::Complex_2b.

See L<SPVM::NDArray::Document> about Details of N-Dimension Array.

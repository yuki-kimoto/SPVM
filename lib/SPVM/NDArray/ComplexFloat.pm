=head1 NAME

SPVM::NDArray::ComplexFloat - N-Dimension Array of SPVM::Complex_2f

=head1 SYNOPSYS
  
  my $ndarray = SPVM::NDArray::ComplexFloat->new;
  my $dim1 = 3;
  my $dim2 = 4;
  my $length = $dim1 * $dim2;
  $ndarray->{base} = new SPVM::Complex_2f[$length];
  $ndarray->{length} = $length;
  $ndarray->{shape} = [$dim1, $dim2];

=head1 DESCRIPTION

SPVM::NDArray::ComplexFloat is N-Dimension Array of SPVM::Complex_2f.

See L<SPVM::NDArray::Document> about Details of N-Dimension Array.

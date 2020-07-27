=head1 NAME

SPVM::NDArray::ComplexLong - N-Dimension Array of SPVM::Complex_2l

=head1 SYNOPSYS
  
  my $ndarray = SPVM::NDArray::ComplexLong->new;
  my $dim1 = 3;
  my $dim2 = 4;
  my $length = $dim1 * $dim2;
  $ndarray->{base} = new SPVM::Complex_2l[$length];
  $ndarray->{length} = $length;
  $ndarray->{shape} = [$dim1, $dim2];

=head1 DESCRIPTION

SPVM::NDArray::ComplexLong is N-Dimension Array of SPVM::Complex_2l.

See L<SPVM::NDArray::Document> about Details of N-Dimension Array.

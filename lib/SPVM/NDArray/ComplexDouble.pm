=head1 NAME

SPVM::NDArray::ComplexDouble - N-Dimension Array of SPVM::Complex_2d

=head1 SYNOPSYS
  
  my $ndarray = SPVM::NDArray::ComplexDouble->new;
  my $dim1 = 3;
  my $dim2 = 4;
  my $length = $dim1 * $dim2;
  $ndarray->{base} = new SPVM::Complex_2d[$length];
  $ndarray->{length} = $length;
  $ndarray->{shape} = [$dim1, $dim2];

=head1 DESCRIPTION

SPVM::NDArray::ComplexDouble is N-Dimension Array of SPVM::Complex_2d.

See L<SPVM::NDArray::Document> about Details of N-Dimension Array.

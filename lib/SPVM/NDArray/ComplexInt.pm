=head1 NAME

SPVM::NDArray::ComplexInt - N-Dimension Array of SPVM::Complex_2i

=head1 SYNOPSYS
  
  my $ndarray = SPVM::NDArray::ComplexInt->new;
  my $dim1 = 3;
  my $dim2 = 4;
  my $length = $dim1 * $dim2;
  $ndarray->{base} = new SPVM::Complex_2i[$length];
  $ndarray->{length} = $length;
  $ndarray->{shape} = [$dim1, $dim2];

=head1 DESCRIPTION

SPVM::NDArray::ComplexInt is N-Dimension Array of SPVM::Complex_2i.

See L<SPVM::NDArray::Document> about Details of N-Dimension Array.

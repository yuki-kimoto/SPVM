=head1 NAME

SPVM::NDArray::Double - N-Dimension Array of double

=head1 SYNOPSYS
  
  my $ndarray = SPVM::NDArray::Double->new;
  my $dim1 = 3;
  my $dim2 = 4;
  my $length = $dim1 * $dim2;
  $ndarray->{base} = new double[$length];
  $ndarray->{length} = $length;
  $ndarray->{shape} = [$dim1, $dim2];

=head1 DESCRIPTION

SPVM::NDArray::Double is N-Dimension Array of double.

See L<SPVM::NDArrayDoc> about Details of N-Dimension Array.

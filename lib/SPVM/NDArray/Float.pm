=head1 NAME

SPVM::NDArray::Float - N-Dimension Array of float

=head1 SYNOPSYS
  
  my $ndarray = SPVM::NDArray::Float->new;
  my $dim1 = 3;
  my $dim2 = 4;
  my $length = $dim1 * $dim2;
  $ndarray->{base} = new float[$length];
  $ndarray->{length} = $length;
  $ndarray->{shape} = [$dim1, $dim2];

=head1 DESCRIPTION

SPVM::NDArray::Float is N-Dimension Array of float.

See L<SPVM::NDArrayDoc> about Details of N-Dimension Array.

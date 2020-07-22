=head1 NAME

SPVM::NDArray::Short - N-Dimension Array of short

=head1 SYNOPSYS
  
  my $ndarray = SPVM::NDArray::Short->new;
  my $dim1 = 3;
  my $dim2 = 4;
  my $length = $dim1 * $dim2;
  $ndarray->{base} = new short[$length];
  $ndarray->{length} = $length;
  $ndarray->{shape} = [$dim1, $dim2];

=head1 DESCRIPTION

SPVM::NDArray::Short is N-Dimension Array of short.

See L<SPVM::NDArrayDoc> about Details of N-Dimension Array.

=head1 NAME

SPVM::NDArray::Long - N-Dimension Array of long

=head1 SYNOPSYS
  
  my $ndarray = SPVM::NDArray::Long->new;
  my $dim1 = 3;
  my $dim2 = 4;
  my $length = $dim1 * $dim2;
  $ndarray->{base} = new long[$length];
  $ndarray->{length} = $length;
  $ndarray->{shape} = [$dim1, $dim2];

=head1 DESCRIPTION

SPVM::NDArray::Long is N-Dimension Array of long.

See L<SPVM::NDArrayDoc> about Details of N-Dimension Array.

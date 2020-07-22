=head1 NAME

SPVM::NDArray::Int - N-Dimension Array of int

=head1 SYNOPSYS
  
  my $ndarray = SPVM::NDArray::Int->new;
  my $dim1 = 3;
  my $dim2 = 4;
  my $length = $dim1 * $dim2;
  $ndarray->{base} = new int[$length];
  $ndarray->{length} = $length;
  $ndarray->{shape} = [$dim1, $dim2];

=head1 DESCRIPTION

SPVM::NDArray::Int is N-Dimension Array of int.

See L<SPVM::NDArrayDoc> about Details of N-Dimension Array.

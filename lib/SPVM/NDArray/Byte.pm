=head1 NAME

SPVM::NDArray::Byte - N-Dimension Array of byte

=head1 SYNOPSYS
  
  my $ndarray = SPVM::NDArray::Byte->new;
  my $dim1 = 3;
  my $dim2 = 4;
  my $length = $dim1 * $dim2;
  $ndarray->{base} = new byte[$length];
  $ndarray->{length} = $length;
  $ndarray->{shape} = [$dim1, $dim2];

=head1 DESCRIPTION

SPVM::NDArray::Byte is N-Dimension Array of byte.

See L<SPVM::NDArrayDoc> about Details of N-Dimension Array.

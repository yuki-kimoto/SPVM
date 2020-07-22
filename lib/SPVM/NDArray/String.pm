=head1 NAME

SPVM::NDArray::String - N-Dimension Array of string

=head1 SYNOPSYS
  
  my $ndarray = SPVM::NDArray::String->new;
  my $dim1 = 3;
  my $dim2 = 4;
  my $length = $dim1 * $dim2;
  $ndarray->{base} = new string[$length];
  $ndarray->{length} = $length;
  $ndarray->{shape} = [$dim1, $dim2];

=head1 DESCRIPTION

SPVM::NDArray::String is N-Dimension Array of string.

See L<SPVM::NDArrayDoc> about Details of N-Dimension Array.

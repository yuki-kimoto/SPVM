=head1 NAME

SPVM::NDArray::ComplexShort - N-Dimension Array of SPVM::Complex_2s

=head1 SYNOPSYS
  
  my $ndarray = SPVM::NDArray::ComplexShort->new;
  my $dim1 = 3;
  my $dim2 = 4;
  my $length = $dim1 * $dim2;
  $ndarray->{base} = new SPVM::Complex_2s[$length];
  $ndarray->{length} = $length;
  $ndarray->{shape} = [$dim1, $dim2];

=head1 DESCRIPTION

SPVM::NDArray::ComplexShort is N-Dimension Array of SPVM::Complex_2s.

See L<SPVM::NDArray::Document> about Details of N-Dimension Array.

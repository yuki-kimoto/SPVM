=head1 NAME

SPVM::NDArray::QuatFloat - N-Dimension Array of SPVM::Quat_4f

=head1 SYNOPSYS
  
  my $ndarray = SPVM::NDArray::QuatFloat->new;
  my $dim1 = 3;
  my $dim2 = 4;
  my $length = $dim1 * $dim2;
  $ndarray->{base} = new SPVM::Quat_4f[$length];
  $ndarray->{length} = $length;
  $ndarray->{shape} = [$dim1, $dim2];

=head1 DESCRIPTION

SPVM::NDArray::QuatFloat is N-Dimension Array of SPVM::Quat_4f.

See L<SPVM::NDArray::Document> about Details of N-Dimension Array.

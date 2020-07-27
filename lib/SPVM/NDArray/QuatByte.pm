=head1 NAME

SPVM::NDArray::QuatByte - N-Dimension Array of SPVM::Quat_4b

=head1 SYNOPSYS
  
  my $ndarray = SPVM::NDArray::QuatByte->new;
  my $dim1 = 3;
  my $dim2 = 4;
  my $length = $dim1 * $dim2;
  $ndarray->{base} = new SPVM::Quat_4b[$length];
  $ndarray->{length} = $length;
  $ndarray->{shape} = [$dim1, $dim2];

=head1 DESCRIPTION

SPVM::NDArray::QuatByte is N-Dimension Array of SPVM::Quat_4b.

See L<SPVM::NDArray::Document> about Details of N-Dimension Array.

=head1 NAME

SPVM::NDArray::QuatShort - N-Dimension Array of SPVM::Quat_4s

=head1 SYNOPSYS
  
  my $ndarray = SPVM::NDArray::QuatShort->new;
  my $dim1 = 3;
  my $dim2 = 4;
  my $length = $dim1 * $dim2;
  $ndarray->{base} = new SPVM::Quat_4s[$length];
  $ndarray->{length} = $length;
  $ndarray->{shape} = [$dim1, $dim2];

=head1 DESCRIPTION

SPVM::NDArray::QuatShort is N-Dimension Array of SPVM::Quat_4s.

See L<SPVM::NDArray::Document> about Details of N-Dimension Array.

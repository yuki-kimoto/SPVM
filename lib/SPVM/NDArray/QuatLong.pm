=head1 NAME

SPVM::NDArray::QuatLong - N-Dimension Array of SPVM::Quat_4l

=head1 SYNOPSYS
  
  my $ndarray = SPVM::NDArray::QuatLong->new;
  my $dim1 = 3;
  my $dim2 = 4;
  my $length = $dim1 * $dim2;
  $ndarray->{base} = new SPVM::Quat_4l[$length];
  $ndarray->{length} = $length;
  $ndarray->{shape} = [$dim1, $dim2];

=head1 DESCRIPTION

SPVM::NDArray::QuatLong is N-Dimension Array of SPVM::Quat_4l.

See L<SPVM::NDArray::Document> about Details of N-Dimension Array.

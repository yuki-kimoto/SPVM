=head1 NAME

SPVM::NDArray::QuatDouble - N-Dimension Array of SPVM::Quat_4d

=head1 SYNOPSYS
  
  my $ndarray = SPVM::NDArray::QuatDouble->new;
  my $dim1 = 3;
  my $dim2 = 4;
  my $length = $dim1 * $dim2;
  $ndarray->{base} = new SPVM::Quat_4d[$length];
  $ndarray->{length} = $length;
  $ndarray->{shape} = [$dim1, $dim2];

=head1 DESCRIPTION

SPVM::NDArray::QuatDouble is N-Dimension Array of SPVM::Quat_4d.

See L<SPVM::NDArray::Document> about Details of N-Dimension Array.

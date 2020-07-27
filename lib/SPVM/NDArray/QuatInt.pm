=head1 NAME

SPVM::NDArray::QuatInt - N-Dimension Array of SPVM::Quat_4i

=head1 SYNOPSYS
  
  my $ndarray = SPVM::NDArray::QuatInt->new;
  my $dim1 = 3;
  my $dim2 = 4;
  my $length = $dim1 * $dim2;
  $ndarray->{base} = new SPVM::Quat_4i[$length];
  $ndarray->{length} = $length;
  $ndarray->{shape} = [$dim1, $dim2];

=head1 DESCRIPTION

SPVM::NDArray::QuatInt is N-Dimension Array of SPVM::Quat_4i.

See L<SPVM::NDArray::Document> about Details of N-Dimension Array.

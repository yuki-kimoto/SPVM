=head1 NAME

SPVM::Matrix::Float - float Matrix

=head1 SYNOPSYS

my $values = new float[10];
my $rows_length = 2;
my $columns_length = 3;
my $matrix = new SPVM::Matrix::Float;
$matrix->{values} = $values;
$matrix->{rows_length} = $rows_length;
$matrix->{columns_length} = $columns_length;

=head1 DESCRIPTION

SPVM::Matrix::Float is float Matrix data strcuture.

See L<SPVM::Matrix::Util> about matrix operations.

=head1 CONSTRUCTOR

  my $matrix = new SPVM::Matrix::Float;

=head1 FIELDS

=head2 values

  has values : public float[];
  
Matrix elements. This elements is assumed as Column-Major order.

=head2 rows_length

  has rows_length : public int;

Matrix rows length.

=head2 columns_length

  has columns_length : public int;

Matrix columns length.

=head1 NAME

SPVM::Matrix::ComplexLong - complex long Matrix

=head1 SYNOPSYS
  
  my $values = new SPVM::Complex_2l[10];
  my $row = 2;
  my $col = 3;
  my $matrix = SPVM::Matrix::ComplexLong->new($values, $row, $col);

Accessors

  my $values = $matrix->values;
  my $row = $matrix->row;
  my $col = $matrix->col;
  
=head1 DESCRIPTION

SPVM::Matrix::ComplexLong is complex long Matrix.

=head1 METHODS

=head2 new : SPVM::Matrix::ComplexLong ($values : ${element_type}[], $row : int, $col : int)

  my $values = new SPVM::Complex_2l[10];
  my $row = 2;
  my $col = 3;
  my $matrix = SPVM::Matrix::ComplexLong->new($values, $row, $col);

B<Arguments:>

1. Values. this value is set to C<values> field. Note that the reference is set to C<values> field not creating new array which elements is copied from argument array.

2. Row. This value is set to C<row> field.

3. Column. This value is set to C<col> field.

B<Return Value:>

Matrix object.

B<Exception:>

1. If Values is not defined, a exception occurs.

2. If Values length is different from Row * Column, a exception occurs.

=head2 values : ${element_type}[] ()

  my $values = $matrix->values;

Get C<values> field. Note that get the reference of C<values> field not creating new array which elements is copied from C<values> field.

=head2 row : int ()

  my $row = $matrix->row;

Get C<row> field.

=head2 col : int ()

  my $col = $matrix->col;

Get C<col> field.

=head2 to_string : string ()
  
  my $string = $matrix->to_string;

Convert Matrix Content to String. Each column is joined 1 space and Each row is end with \n

  1 3 5
  2 4 6

=head1 Matrix Features

=head2 Values is always defined

C<values> field is alway defined after new matrix object.

=head2 Array length of Values is always Row length * Column length

The array length of C<values> is always C<row> field * C<col> field.

=head2 Column-major

Matrix is Column-major.
  
  # Matrix
  # $x11 $x12 $x13
  # $x21 $x22 $x23
  my $values = [$x11, $x21, $x12, $x22, $x13, $x23];
  my $row = 2;
  my $col = 3;
  my $matrix = SPVM::Matrix::ComplexLong->new($values, $row, $col);

=head2 Imutable Things

The following fields is imutable.

1. C<values> field

2. C<row> field

3. C<col> field

=head2 Mutable Things

The following thing is mutable.

1. Each value of C<values> field.
  
  # Can set each value of C<values> field.
  $matrix->values->[0] = $x11;


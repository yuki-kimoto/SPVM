=head1 NAME

SPVM::Matrix::Double - double Matrix

=head1 SYNOPSYS

my $values = new double[10];
my $rows_length = 2;
my $columns_length = 3;
my $matrix = SPVM::Matrix::Double->new($values, $rows_length, $columns_length);

Accessors

my $values = $matrix->values;
my $rows_length= $matrix->rows_length;
my $columns_length = $matrix->columns_length;

=head1 DESCRIPTION

SPVM::Matrix::Double is double Matrix.

=head1 METHODS

=head2 new : SPVM::Matrix::Double ($values : ${element_type}[], $rows_length: int, $columns_length : int)

my $values = new double[10];
my $rows_length = 2;
my $columns_length = 3;
my $matrix = SPVM::Matrix::Double->new($values, $rows_length, $columns_length);

B<Arguments:>

1. Values. this value is set to C<values> field. Note that the reference is set to C<values> field not creating new array which elements is copied from argument array.

2. Row. This value is set to C<rows_length> field.

3. Column. This value is set to C<columns_length> field.

B<Return Value:>

Matrix object.

B<Exception:>

1. If Values is not defined, a exception occurs.

2. If Values length is different from Row * Column, a exception occurs.

=head2 values : ${element_type}[] ()

my $values = $matrix->values;

Get C<values> field. Note that get the reference of C<values> field not creating new array which elements is copied from C<values> field.

=head2 rows_length : int ()

my $rows_length= $matrix->rows_length;

Get C<rows_length> field.

=head2 columns_length : int ()

my $columns_length = $matrix->columns_length;

Get C<columns_length> field.

=head2 to_string : string ()

my $string = $matrix->to_string;

Convert Matrix Content to String. Each column is joined 1 space and Each row is end with \n

1 3 5
2 4 6

=head1 Matrix Features

=head2 Values is always defined

C<values> field is alway defined after new matrix object.

=head2 Array length of Values is always Row length * Column length

The array length of C<values> is always C<rows_length> field * C<columns_length> field.

=head2 Column-major

Matrix is Column-major.

# Matrix
# $x11 $x12 $x13
# $x21 $x22 $x23
my $values = [$x11, $x21, $x12, $x22, $x13, $x23];
my $rows_length= 2;
my $columns_length = 3;
my $matrix = SPVM::Matrix::Double->new($values, $rows_length, $columns_length);

=head2 Imutable Things

The following fields is imutable.

1. C<values> field

2. C<rows_length> field

3. C<columns_length> field

=head2 Mutable Things

The following thing is mutable.

1. Each value of C<values> field.

# Can set each value of C<values> field.
$matrix->values->[0] = $x11;


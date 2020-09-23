=head1 NAME

SPVM::Matrix::Util - Matrix Utilities

=head1 DESCRIPTION

SPVM::Matrix::Util is matrix utilities. Matirx operation is defined.

Matrix Data Structure is defined in L<SPVM::Matrix::Float> and L<SPVM::Matrix::Double>

=head1 CLASS METHODS

=head2 mat_new

  sub mat_new : SPVM::Matrix::Double ($values : double[], $rows_length: int, $columns_length : int)

Create new L<SPVM::Matrix::Double> object.

B<Arguments:>

1. Values. this value is set to C<values> field. Note that the reference is set to C<values> field not creating new array which elements is copied from argument array. Elements order is assumed as Column-Major order.

2. Row. This value is set to C<rows_length> field.

3. Column. This value is set to C<columns_length> field.

B<Return Value:>

L<SPVM::Matrix::Double> object.

B<Exception:>

1. If Values is not defined, a exception occurs.

2. If Values length is different from Row * Column, a exception occurs.

=head2 mat_newf

  sub mat_newf : SPVM::Matrix::Float ($values : float[], $rows_length: int, $columns_length : int)

Create new L<SPVM::Matrix::Float> object.

B<Arguments:>

1. Values. this value is set to C<values> field. Note that the reference is set to C<values> field not creating new array which elements is copied from argument array. Elements order is assumed as Column-Major order.

2. Row. This value is set to C<rows_length> field.

3. Column. This value is set to C<columns_length> field.

B<Return Value:>

L<SPVM::Matrix::Float> object.

B<Exception:>

1. If Values is not defined, a exception occurs.

2. If Values length is different from Row * Column, a exception occurs.

=head2 mat_new_zero

  sub mat_new_zero : SPVM::Matrix::Double ($rows_length: int, $columns_length : int)

Create new L<SPVM::Matrix::Double> object with zero value.

=head2 mat_new_zerof

  sub mat_new_zerof : SPVM::Matrix::Float ($rows_length: int, $columns_length : int)

Create new L<SPVM::Matrix::Float> object with zero value.

=head2 mat_new_ident

  sub mat_new_ident : SPVM::Matrix::Double ($dim : int)

Create new ident <SPVM::Matrix::Double> by specifing the dimention.

=head2 mat_new_identf

  sub mat_new_identf : SPVM::Matrix::Float ($dim : int)

Create new ident <SPVM::Matrix::Float> by specifing the dimention.

=head2 mat_transpose

  sub mat_transpose : SPVM::Matrix::Double ($mat : SPVM::Matrix::Double)

Transpose double matrix and return new L<SPVM::Matrix::Double> object.

=head2 mat_transposef

  sub mat_transposef : SPVM::Matrix::Float ($mat : SPVM::Matrix::Float)

Transpose float matrix and return new L<SPVM::Matrix::Float> object.

=head2 mat_add

  sub mat_add : SPVM::Matrix::Double ($mat1 : SPVM::Matrix::Double, $mat2 : SPVM::Matrix::Double)

Add two double Matrix and return new L<SPVM::Matrix::Double> object.

=head2 mat_addf

  sub mat_addf : SPVM::Matrix::Float ($mat1 : SPVM::Matrix::Float, $mat2 : SPVM::Matrix::Float)

Add two float Matrix and return new L<SPVM::Matrix::Float> object.

=head2 mat_sub

  sub mat_sub : SPVM::Matrix::Double ($mat1 : SPVM::Matrix::Double, $mat2 : SPVM::Matrix::Double)

Subtract two double Matrix and return new L<SPVM::Matrix::Double> object.

=head2 mat_subf

  sub mat_subf : SPVM::Matrix::Float ($mat1 : SPVM::Matrix::Float, $mat2 : SPVM::Matrix::Float)

Subtract two float Matrix and return new L<SPVM::Matrix::Float> object.

=head2 mat_scamul

  sub mat_scamul : SPVM::Matrix::Double ($scalar : double, $mat1 : SPVM::Matrix::Double)

Scalar multiply float matrix and return new L<SPVM::Matrix::Double> object.

=head2 mat_scamulf

  sub mat_scamulf : SPVM::Matrix::Float ($scalar : float, $mat1 : SPVM::Matrix::Float)

Scalar multiply float matrix and return new L<SPVM::Matrix::Float> object.

=head2 mat_mul

  sub mat_mul : SPVM::Matrix::Double ($mat1 : SPVM::Matrix::Double, $mat2 : SPVM::Matrix::Double)

Multiply two double Matrix and return new L<SPVM::Matrix::Double> object.

=head2 mat_mulf

  sub mat_mulf : SPVM::Matrix::Float ($mat1 : SPVM::Matrix::Float, $mat2 : SPVM::Matrix::Float)

Multiply two float Matrix and return new L<SPVM::Matrix::Float> object.

=head2 mat_str

  sub mat_str : string ($mat : SPVM::Matrix::Double)

Convert Matrix Content to String. Each column is joined 1 space and Each row is end with \n

1 3 5
2 4 6

=head2 mat_strf

  sub mat_strf : string ($mat : SPVM::Matrix::Float)

Convert Matrix Content to String. Each column is joined 1 space and Each row is end with \n

1 3 5
2 4 6

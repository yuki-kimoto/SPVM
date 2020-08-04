use strict;
use warnings;

my @number_categories = ('real', 'complex', 'quat');

my @types = qw(byte short int long float double);
sub prefix {
  my ($type) = @_;
  my $prefix = substr($type, 0, 1);
  return $prefix;
}

for my $number_category (@number_categories) {
  for my $type (@types) {
    my $prefix = prefix($type);
    
    my $package_name;
    my $element_type;
    my $spvm_module_file;
    my $perl_module_file;
    if ($number_category eq 'real') {
      $package_name = "SPVM::Matrix::";
      $element_type = "$type";
      $spvm_module_file = "lib/SPVM/Matrix/";
    }
    elsif ($number_category eq 'complex') {
      $package_name = "SPVM::Matrix::Complex";
      $element_type = "SPVM::Complex_2" . prefix($type);
      $spvm_module_file = "lib/SPVM/Matrix/Complex";
    }
    elsif ($number_category eq 'quat') {
      $package_name = "SPVM::Matrix::Quat";
      $element_type = "SPVM::Quat_4" . prefix($type);
      $spvm_module_file = "lib/SPVM/Matrix/Quat";
    }
    $package_name .= ucfirst $type;
    $spvm_module_file .= ucfirst($type) . '.spvm';
    $perl_module_file = $spvm_module_file;
    $perl_module_file =~ s/\.spvm$/.pm/;
    
    my $transpose_element;
    if ($number_category eq 'real') {
      $transpose_element = <<"EOS"
        \$mat_trans_values->[\$row_index * \$col + \$col_index] = \$values->[\$col_index * \$row + \$row_index];
EOS
    }
    elsif ($number_category eq 'complex') {
      $transpose_element = <<"EOS";
        \$mat_trans_values->[\$row_index * \$col + \$col_index].x = \$values->[\$col_index * \$row + \$row_index].x;
        \$mat_trans_values->[\$row_index * \$col + \$col_index].y = \$values->[\$col_index * \$row + \$row_index].y;
EOS

    }
    elsif ($number_category eq 'quat') {
      $transpose_element = <<"EOS";
        \$mat_trans_values->[\$row_index * \$col + \$col_index].t = \$values->[\$col_index * \$row + \$row_index].t;
        \$mat_trans_values->[\$row_index * \$col + \$col_index].x = \$values->[\$col_index * \$row + \$row_index].x;
        \$mat_trans_values->[\$row_index * \$col + \$col_index].y = \$values->[\$col_index * \$row + \$row_index].y;
        \$mat_trans_values->[\$row_index * \$col + \$col_index].z = \$values->[\$col_index * \$row + \$row_index].z;
EOS
    }
    
    my $spvm_module_content = "# $package_name is created by regen/regen_matrix.pl\n";
    $spvm_module_content .= <<"EOS";
package $package_name {
  use SPVM::StringBuffer;
  
  has values : ro ${element_type}[];
  has row : ro int;
  has col : ro int;
  
  sub new : $package_name (\$values : ${element_type}[], \$row : int, \$col : int) {
    unless (\$values) {
      die "Values must defined";
    }

    unless (\$row * \$col == scalar \@\$values) {
      die "Values length must be row * col";
    }
    my \$matrix = new $package_name;
    \$matrix->{values} = \$values;
    \$matrix->{row} = \$row;
    \$matrix->{col} = \$col;
    return \$matrix;
  }

  sub new_zero : $package_name (\$row : int, \$col : int) {

    unless (\$row > 0) {
      die "Row must be more than 0";
    }
    unless (\$col > 0) {
      die "Col must be more than 0";
    }
    my \$matrix = new $package_name;
    my \$length = \$row * \$col;
    \$matrix->{values} = new  ${element_type}[\$length];
    \$matrix->{row} = \$row;
    \$matrix->{col} = \$col;
    return \$matrix;
  }

  sub new_unit : $package_name (\$dim : int) {
    unless (\$dim < 1) {
      die "Dimension must be more than 0";
    }
    
    my \$matrix = $package_name->new_zero(\$dim, \$dim);
    my \$values = \$matrix->{values};
    for (my \$i = 0; \$i < \$dim; \$i++) {
      \$values->[\$i * \$dim + \$i] = 1;
    }

    return \$matrix;
  }

  sub transpose : $package_name (\$self : self) {
    my \$row = \$self->{row};
    my \$col = \$self->{col};
    my \$length = \$row * \$col;
    
    my \$mat_trans = $package_name->new(new ${element_type}[\$length], \$col, \$row);
    
    my \$values = \$self->{values};
    my \$mat_trans_values = \$mat_trans->{values};
    
    for (my \$row_index = 0; \$row_index < \$row; \$row_index++) {
      for (my \$col_index = 0; \$col_index < \$col; \$col_index++) {
$transpose_element
      }
    }
    
    return \$mat_trans;
  }
  
  sub str : string (\$self : self) {
    my \$values = \$self->{values};
    my \$row = \$self->{row};
    my \$col = \$self->{col};
    my \$length = \$row * \$col;
    
    my \$buffer = SPVM::StringBuffer->new;
    for (my \$row_index = 0; \$row_index < \$row; \$row_index++) {
      for (my \$elem_index = \$row_index; \$elem_index < \$length; \$elem_index += \$row) {
        \$buffer->push(\$values->[\$elem_index]);
        if (\$elem_index < \$length - \$col + 1) {
          \$buffer->push(" ");
        }
      }
      \$buffer->push("\\n");
    }
    
    my \$str = \$buffer->to_string;
    
    return \$str;
  }

  sub add : $package_name (\$self : self, \$mat : $package_name) {
    my \$self_values = \$self->{values};
    my \$self_row = \$self->{row};
    my \$self_col = \$self->{col};
    
    my \$mat_row = \$mat->{row};
    my \$mat_col = \$mat->{col};
    my \$mat_values = \$mat->{values};
    
    if (\$self_row != \$mat_row) {
      die "Self row must be equals to mat row";
    }

    if (\$self_col != \$mat_col) {
      die "Self col must be equals to mat col";
    }

    my \$self_length = \$self_row * \$self_col;
    my \$mat_result = $package_name->new(new ${element_type}[\$self_length], \$self_row, \$self_col);
    my \$mat_result_values = \$mat_result->{values};
    
    for (my \$i = 0; \$i < \$self_length; \$i++) {
      \$mat_result_values->[\$i] = (${element_type})(\$self_values->[\$i] + \$mat_values->[\$i]);
    }
    
    return \$mat_result;
  }

  sub sub : $package_name (\$self : self, \$mat : $package_name) {
    my \$self_values = \$self->{values};
    my \$self_row = \$self->{row};
    my \$self_col = \$self->{col};
    
    my \$mat_row = \$mat->{row};
    my \$mat_col = \$mat->{col};
    my \$mat_values = \$mat->{values};
    
    if (\$self_row != \$mat_row) {
      die "Self row must be equals to mat row";
    }

    if (\$self_col != \$mat_col) {
      die "Self col must be equals to mat col";
    }

    my \$self_length = \$self_row * \$self_col;
    my \$mat_result = $package_name->new(new ${element_type}[\$self_length], \$self_row, \$self_col);
    my \$mat_result_values = \$mat_result->{values};
    
    for (my \$i = 0; \$i < \$self_length; \$i++) {
      \$mat_result_values->[\$i] = (${element_type})(\$self_values->[\$i] - \$mat_values->[\$i]);
    }
    
    return \$mat_result;
  }

  sub scamul : $package_name (\$self : self, \$scalar : ${element_type}) {
    my \$self_values = \$self->{values};
    my \$self_row = \$self->{row};
    my \$self_col = \$self->{col};

    my \$self_length = \$self_row * \$self_col;
    my \$mat_result = $package_name->new(new ${element_type}[\$self_length], \$self_row, \$self_col);
    my \$mat_result_values = \$mat_result->{values};
    
    for (my \$i = 0; \$i < \$self_length; \$i++) {
      \$mat_result_values->[\$i] = (${element_type})(\$scalar * \$self_values->[\$i]);
    }
    
    return \$mat_result;
  }

  sub mul : $package_name (\$self : self, \$mat : $package_name) {
    my \$self_values = \$self->{values};
    my \$self_row = \$self->{row};
    my \$self_col = \$self->{col};
    
    my \$mat_row = \$mat->{row};
    my \$mat_col = \$mat->{col};
    my \$mat_values = \$mat->{values};
    
    if (\$self_col != \$mat_row) {
      die "Self col must be equals to mat row";
    }

    my \$self_length = \$self_row * \$self_col;
    my \$mat_result = $package_name->new(new ${element_type}[\$self_length], \$self_row, \$mat_col);
    my \$mat_result_values = \$mat_result->{values};
    my \$mat_result_col = \$mat_result->{col};
    my \$mat_result_row = \$mat_result->{row};
    
    for(my \$i = 0; \$i < \$self_row; \$i++) {
      for(my \$j = 0; \$j < \$mat_col; \$j++) {
        for(my \$k = 0; \$k < \$self_col; \$k++) {
          \$mat_result_values->[\$i * \$mat_result_col + \$j]  += + \$self_values->[\$i * \$self_col + \$k] * \$mat_values->[\$k * \$mat_col + \$j];
        }
      }
    }
    
    return \$mat_result;
  }

}
EOS
   
    open my $spvm_module_fh, '>', $spvm_module_file
      or die "Can't open $spvm_module_file: $!";
    print $spvm_module_fh $spvm_module_content;

    my $perl_module_content = <<EOS;
=head1 NAME

$package_name - $number_category $type Matrix

=head1 SYNOPSYS
  
  my \$values = new ${element_type}[10];
  my \$row = 2;
  my \$col = 3;
  my \$matrix = $package_name->new(\$values, \$row, \$col);

Accessors

  my \$values = \$matrix->values;
  my \$row = \$matrix->row;
  my \$col = \$matrix->col;
  
=head1 DESCRIPTION

$package_name is $number_category $type Matrix.

=head1 METHODS

=head2 new : $package_name (\$values : \${element_type}[], \$row : int, \$col : int)

  my \$values = new ${element_type}[10];
  my \$row = 2;
  my \$col = 3;
  my \$matrix = $package_name->new(\$values, \$row, \$col);

B<Arguments:>

1. Values. this value is set to C<values> field. Note that the reference is set to C<values> field not creating new array which elements is copied from argument array.

2. Row. This value is set to C<row> field.

3. Column. This value is set to C<col> field.

B<Return Value:>

Matrix object.

B<Exception:>

1. If Values is not defined, a exception occurs.

2. If Values length is different from Row * Column, a exception occurs.

=head2 values : \${element_type}[] ()

  my \$values = \$matrix->values;

Get C<values> field. Note that get the reference of C<values> field not creating new array which elements is copied from C<values> field.

=head2 row : int ()

  my \$row = \$matrix->row;

Get C<row> field.

=head2 col : int ()

  my \$col = \$matrix->col;

Get C<col> field.

=head2 to_string : string ()
  
  my \$string = \$matrix->to_string;

Convert Matrix Content to String. Each column is joined 1 space and Each row is end with \\n

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
  # \$x11 \$x12 \$x13
  # \$x21 \$x22 \$x23
  my \$values = [\$x11, \$x21, \$x12, \$x22, \$x13, \$x23];
  my \$row = 2;
  my \$col = 3;
  my \$matrix = $package_name->new(\$values, \$row, \$col);

=head2 Imutable Things

The following fields is imutable.

1. C<values> field

2. C<row> field

3. C<col> field

=head2 Mutable Things

The following thing is mutable.

1. Each value of C<values> field.
  
  # Can set each value of C<values> field.
  \$matrix->values->[0] = \$x11;

EOS

    open my $perl_module_fh, '>', $perl_module_file
      or die "Can't open $perl_module_file: $!";
    print $perl_module_fh $perl_module_content;
  }
}

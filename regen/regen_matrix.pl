use strict;
use warnings;

my @types = qw(float double);
sub prefix {
  my ($type) = @_;
  my $prefix = substr($type, 0, 1);
  return $prefix;
}

for my $type (@types) {
  my $prefix = prefix($type);
  
  my $package_name;
  my $element_type;
  my $spvm_module_file;
  my $perl_module_file;
  $package_name = "SPVM::Matrix::";
  $element_type = "$type";
  $spvm_module_file = "lib/SPVM/Matrix/";
  $package_name .= ucfirst $type;
  $spvm_module_file .= ucfirst($type) . '.spvm';
  $perl_module_file = $spvm_module_file;
  $perl_module_file =~ s/\.spvm$/.pm/;
  
  my $transpose_element = <<"EOS";
      \$mat_trans_values->[\$row_index * \$columns_length + \$column_index] = \$values->[\$column_index * \$rows_length+ \$row_index];
EOS
  
  my $spvm_module_content = "# $package_name is created by regen/regen_matrix.pl\n";
  $spvm_module_content .= <<"EOS";
package $package_name {
use SPVM::StringBuffer;

has values : ro ${element_type}[];
has rows_length : ro int;
has columns_length : ro int;

sub new : $package_name (\$values : ${element_type}[], \$rows_length: int, \$columns_length : int) {
  unless (\$values) {
    die "Values must defined";
  }

  unless (\$rows_length* \$columns_length == scalar \@\$values) {
    die "Values length must be row * col";
  }
  my \$matrix = new $package_name;
  \$matrix->{values} = \$values;
  \$matrix->{rows_length} = \$rows_length;
  \$matrix->{columns_length} = \$columns_length;
  return \$matrix;
}

sub new_zero : $package_name (\$rows_length: int, \$columns_length : int) {

  unless (\$rows_length> 0) {
    die "Row must be more than 0";
  }
  unless (\$columns_length > 0) {
    die "Col must be more than 0";
  }
  my \$matrix = new $package_name;
  my \$length = \$rows_length* \$columns_length;
  \$matrix->{values} = new  ${element_type}[\$length];
  \$matrix->{rows_length} = \$rows_length;
  \$matrix->{columns_length} = \$columns_length;
  return \$matrix;
}

sub new_ident : $package_name (\$dim : int) {
  if (\$dim < 1) {
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
  my \$rows_length = \$self->{rows_length};
  my \$columns_length = \$self->{columns_length};
  my \$length = \$rows_length * \$columns_length;
  
  my \$mat_trans = $package_name->new(new ${element_type}[\$length], \$columns_length, \$rows_length);
  
  my \$values = \$self->{values};
  my \$mat_trans_values = \$mat_trans->{values};
  
  for (my \$row_index = 0; \$row_index < \$rows_length; \$row_index++) {
    for (my \$column_index = 0; \$column_index < \$columns_length; \$column_index++) {
$transpose_element
    }
  }
  
  return \$mat_trans;
}

sub str : string (\$self : self) {
  my \$values = \$self->{values};
  my \$rows_length = \$self->{rows_length};
  my \$columns_length = \$self->{columns_length};
  my \$length = \$rows_length * \$columns_length;
  
  my \$buffer = SPVM::StringBuffer->new;
  for (my \$row_index = 0; \$row_index < \$rows_length; \$row_index++) {
    for (my \$elem_index = \$row_index; \$elem_index < \$length; \$elem_index += \$rows_length) {
      \$buffer->push(\$values->[\$elem_index]);
      if (\$elem_index < \$length - \$columns_length + 1) {
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
  my \$self_rows_length = \$self->{rows_length};
  my \$self_columns_length = \$self->{columns_length};
  
  my \$mat_rows_length = \$mat->{rows_length};
  my \$mat_columns_length = \$mat->{columns_length};
  my \$mat_values = \$mat->{values};
  
  if (\$self_rows_length != \$mat_rows_length) {
    die "Self row must be equals to mat row";
  }

  if (\$self_columns_length != \$mat_columns_length) {
    die "Self col must be equals to mat col";
  }

  my \$self_length = \$self_rows_length * \$self_columns_length;
  my \$mat_result = $package_name->new(new ${element_type}[\$self_length], \$self_rows_length, \$self_columns_length);
  my \$mat_result_values = \$mat_result->{values};
  
  for (my \$i = 0; \$i < \$self_length; \$i++) {
    \$mat_result_values->[\$i] = (${element_type})(\$self_values->[\$i] + \$mat_values->[\$i]);
  }
  
  return \$mat_result;
}

sub sub : $package_name (\$self : self, \$mat : $package_name) {
  my \$self_values = \$self->{values};
  my \$self_rows_length = \$self->{rows_length};
  my \$self_columns_length = \$self->{columns_length};
  
  my \$mat_rows_length = \$mat->{rows_length};
  my \$mat_columns_length = \$mat->{columns_length};
  my \$mat_values = \$mat->{values};
  
  if (\$self_rows_length != \$mat_rows_length) {
    die "Self row must be equals to mat row";
  }

  if (\$self_columns_length != \$mat_columns_length) {
    die "Self col must be equals to mat col";
  }

  my \$self_length = \$self_rows_length * \$self_columns_length;
  my \$mat_result = $package_name->new(new ${element_type}[\$self_length], \$self_rows_length, \$self_columns_length);
  my \$mat_result_values = \$mat_result->{values};
  
  for (my \$i = 0; \$i < \$self_length; \$i++) {
    \$mat_result_values->[\$i] = (${element_type})(\$self_values->[\$i] - \$mat_values->[\$i]);
  }
  
  return \$mat_result;
}

sub scamul : $package_name (\$self : self, \$scalar : ${element_type}) {
  my \$self_values = \$self->{values};
  my \$self_rows_length = \$self->{rows_length};
  my \$self_columns_length = \$self->{columns_length};

  my \$self_length = \$self_rows_length * \$self_columns_length;
  my \$mat_result = $package_name->new(new ${element_type}[\$self_length], \$self_rows_length, \$self_columns_length);
  my \$mat_result_values = \$mat_result->{values};
  
  for (my \$i = 0; \$i < \$self_length; \$i++) {
    \$mat_result_values->[\$i] = (${element_type})(\$scalar * \$self_values->[\$i]);
  }
  
  return \$mat_result;
}

sub mul : $package_name (\$self : self, \$mat : $package_name) {
  my \$self_values = \$self->{values};
  my \$self_rows_length = \$self->{rows_length};
  my \$self_columns_length = \$self->{columns_length};
  
  my \$mat_rows_length = \$mat->{rows_length};
  my \$mat_columns_length = \$mat->{columns_length};
  my \$mat_values = \$mat->{values};
  
  if (\$self_columns_length != \$mat_rows_length) {
    die "Self col must be equals to mat row";
  }

  my \$mat_result_length = \$self_rows_length * \$mat_columns_length;
  my \$mat_result = $package_name->new(new ${element_type}[\$mat_result_length], \$self_rows_length, \$mat_columns_length);
  my \$mat_result_values = \$mat_result->{values};
  my \$mat_result_col = \$mat_result->{columns_length};
  my \$mat_result_row = \$mat_result->{rows_length};
  
  for(my \$row_index = 0; \$row_index < \$self_rows_length; \$row_index++) {
    for(my \$column_index = 0; \$column_index < \$mat_columns_length; \$column_index++) {
      for(my \$incol = 0; \$incol < \$self_columns_length; \$incol++) {
        \$mat_result_values->[\$row_index + \$column_index * \$mat_result_row]
         += \$self_values->[\$row_index + \$incol * \$self_rows_length] * \$mat_values->[\$incol + \$column_index * \$mat_rows_length];
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

$package_name - $type Matrix

=head1 SYNOPSYS

my \$values = new ${element_type}[10];
my \$rows_length = 2;
my \$columns_length = 3;
my \$matrix = $package_name->new(\$values, \$rows_length, \$columns_length);

Accessors

my \$values = \$matrix->values;
my \$rows_length= \$matrix->rows_length;
my \$columns_length = \$matrix->columns_length;

=head1 DESCRIPTION

$package_name is $type Matrix.

=head1 METHODS

=head2 new : $package_name (\$values : \${element_type}[], \$rows_length: int, \$columns_length : int)

my \$values = new ${element_type}[10];
my \$rows_length = 2;
my \$columns_length = 3;
my \$matrix = $package_name->new(\$values, \$rows_length, \$columns_length);

B<Arguments:>

1. Values. this value is set to C<values> field. Note that the reference is set to C<values> field not creating new array which elements is copied from argument array.

2. Row. This value is set to C<rows_length> field.

3. Column. This value is set to C<columns_length> field.

B<Return Value:>

Matrix object.

B<Exception:>

1. If Values is not defined, a exception occurs.

2. If Values length is different from Row * Column, a exception occurs.

=head2 values : \${element_type}[] ()

my \$values = \$matrix->values;

Get C<values> field. Note that get the reference of C<values> field not creating new array which elements is copied from C<values> field.

=head2 rows_length : int ()

my \$rows_length= \$matrix->rows_length;

Get C<rows_length> field.

=head2 columns_length : int ()

my \$columns_length = \$matrix->columns_length;

Get C<columns_length> field.

=head2 to_string : string ()

my \$string = \$matrix->to_string;

Convert Matrix Content to String. Each column is joined 1 space and Each row is end with \\n

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
# \$x11 \$x12 \$x13
# \$x21 \$x22 \$x23
my \$values = [\$x11, \$x21, \$x12, \$x22, \$x13, \$x23];
my \$rows_length= 2;
my \$columns_length = 3;
my \$matrix = $package_name->new(\$values, \$rows_length, \$columns_length);

=head2 Imutable Things

The following fields is imutable.

1. C<values> field

2. C<rows_length> field

3. C<columns_length> field

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

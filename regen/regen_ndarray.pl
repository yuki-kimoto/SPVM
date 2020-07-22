use strict;
use warnings;

my @types = qw(byte short int long float double string);

sub prefix {
  my ($type) = @_;
  my $prefix = substr($type, 0, 1);
  return $prefix;
}

for my $type (@types) {
  my $prefix = prefix($type);
  
  my $package_name = "SPVM::NDArray::" . ucfirst($type);
  
  my $spvm_module_content = <<"EOS";
# $package_name is created by regen/regen_ndarray.pl
package $package_name : public {
  has base : public ${type}[];
  has offset : public int;
  has length : public int;
  has T : public byte;
  has shape : public int[];
  has na_flags : public byte[];
}
EOS
  
  my $spvm_module_file = "lib/SPVM/NDArray/"  . ucfirst($type) . ".spvm";
  open my $spvm_module_fh, '>', $spvm_module_file
    or die "Can't open $spvm_module_file: $!";
  print $spvm_module_fh $spvm_module_content;

  my $perl_module_content = <<EOS;
=head1 NAME

$package_name - N-Dimension Array of $type

=head1 SYNOPSYS
  
  my \$ndarray = $package_name->new;
  my \$dim1 = 3;
  my \$dim2 = 4;
  my \$length = \$dim1 * \$dim2;
  \$ndarray->{base} = new ${type}[\$length];
  \$ndarray->{length} = \$length;
  \$ndarray->{shape} = [\$dim1, \$dim2];

=head1 DESCRIPTION

$package_name is N-Dimension Array of $type.

See L<SPVM::NDArrayDoc> about Details of N-Dimension Array.
EOS

  my $perl_module_file = "lib/SPVM/NDArray/"  . ucfirst($type) . ".pm";
  open my $perl_module_fh, '>', $perl_module_file
    or die "Can't open $perl_module_file: $!";
  print $perl_module_fh $perl_module_content;

}

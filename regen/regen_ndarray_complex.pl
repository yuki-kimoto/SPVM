use strict;
use warnings;

my @types = qw(byte short int long float double);

sub prefix {
  my ($type) = @_;
  my $prefix = substr($type, 0, 1);
  return $prefix;
}

for my $type (@types) {
  my $prefix = prefix($type);
  
  my $package_name = "SPVM::NDArray::Complex" . ucfirst($type);
  
  my $package_content = <<"EOS";
# $package_name is created by regen/regen_ndarray_complex.pl
package $package_name : public {
  use SPVM::Complex_2${prefix};
  has base : public SPVM::Complex_2${prefix}[];
  has offset : public int;
  has length : public int;
  has T : public byte;
  has shape : public int[];
  has na_flags : public byte[];
}
EOS
  
  my $module_file = "lib/SPVM/NDArray/Complex"  . ucfirst($type) . ".spvm";
  open my $module_fh, '>', $module_file
    or die "Can't open $module_file: $!";
  print $module_fh $package_content;
}

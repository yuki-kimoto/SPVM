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
  
  my $package_name = "SPVM::NDArray::Quat" . ucfirst($type);
  
  my $package_content = <<"EOS";
# $package_name is created by regen/regen_ndarray_quat.pl
package $package_name : public {
  use SPVM::Quat_4${prefix};
  has base : public SPVM::Quat_4${prefix}[];
  has offset : public int;
  has length : public int;
  has T : public byte;
  has shape : public int[];
  has na_flags : public byte[];
}
EOS
  
  my $spvm_module_file = "lib/SPVM/NDArray/Quat"  . ucfirst($type) . ".spvm";
  open my $module_fh, '>', $spvm_module_file
    or die "Can't open $spvm_module_file: $!";
  print $module_fh $package_content;
}

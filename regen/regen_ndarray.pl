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
  
  my $package_content = "# $package_name is created by regen/regen_ndarray.pl\n";
  $package_content .= "package $package_name : public {\n";
  $package_content .= <<"EOS";
  has base : public ${type}[];
EOS
  
  if ($type ne 'string') {
    $package_content .=  "  has base_im : public ${type}[];\n";
  }
  
  $package_content .= <<"EOS";
  has offset : public int;
  has length : public int;
  has T : public byte;
  has is_complex : public byte;
  has shape : public int[];
  has na_flags : public byte[];
EOS
  $package_content .= "}\n";
  
  my $module_file = "lib/SPVM/NDArray/"  . ucfirst($type) . ".spvm";
  open my $module_fh, '>', $module_file
    or die "Can't open $module_file: $!";
  print $module_fh $package_content;
}

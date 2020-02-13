use strict;
use warnings;

my @types = qw(byte short int long float double string);

sub prefix {
  my ($type) = @_;
  my $prefix = substr($type, 0, 1);
  return $prefix;
}
sub base_type {
  my ($type) = @_;
  
  my $base_type;
  if ($type eq 'string') {
    $base_type = 'String';
  }
  else {
    $base_type = "Complex_2" . substr($type, 0, 1);
  }
  return $base_type;
}

for my $type (@types) {
  my $prefix = prefix($type);
  
  my $package_name = "SPVM::NDArray::" . ucfirst($type);
  my $base_type = base_type $type;
  
  my $package_content = "# $package_name is created by regen/regen_ndarray.pl\n";
  $package_content .= "package $package_name : public {\n";
  $package_content .= <<"EOS";
  has base : public ${base_type}[];
  has offset : public int;
  has length : public int;
  has trans : public byte;
  has shape : public int[];
  has na_flags : public byte[];
EOS
  $package_content .= "}\n";
  
  my $module_file = "lib/SPVM/NDArray/"  . ucfirst($type) . ".spvm";
  open my $module_fh, '>', $module_file
    or die "Can't open $module_file: $!";
  print $module_fh $package_content;
}

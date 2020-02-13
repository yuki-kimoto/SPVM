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
  
  my $package_name = "SPVM::NDArray::${type}";
  
  my $package_content = "# $package_name is created by regen/regen_ndaray.pl\n";
  $package_content .= "package $package_name {\n";
  for(my $i = 0; $i < $dim; $i++) {
    $package_content .= <<"EOS";
  has base $type[];
  has offset int;
  has length int;
  has T byte;
  has shape int[];
  has na_flags byte[];
EOS
  }
  }
  $package_content .= "}\n";
  
  my $module_file = "lib/SPVM/Vector${dim}_${dim}${prefix}.spvm";
  open my $module_fh, '>', $module_file
    or die "Can't open $module_file: $!";
  print $module_fh $package_content;
}

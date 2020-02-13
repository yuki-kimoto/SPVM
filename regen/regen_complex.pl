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
  
  my $package_name = "SPVM::Complex_2$prefix";
  
  my $package_content = "# $package_name is created by regen/regen_complex.pl\n";
  $package_content .= "package $package_name : mulnum_t {\n";
    $package_content .= <<"EOS";
  has re : $type;
  has im : $type;
EOS
  $package_content .= "}\n";
  
  my $module_file = "lib/SPVM/Complex_2$prefix.spvm";
  open my $module_fh, '>', $module_file
    or die "Can't open $module_file: $!";
  print $module_fh $package_content;
}

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
  
  my $package_name = "SPVM::Quaternion_4$prefix";
  
  my $package_content = "# $package_name is created by regen/regen_quaternion.pl\n";
  $package_content .= "package $package_name : mulnum_t {\n";
    $package_content .= <<"EOS";
  has t : $type;
  has x : $type;
  has y : $type;
  has z : $type;
EOS
  $package_content .= "}\n";
  
  my $module_file = "lib/SPVM/Quaternion_4$prefix.spvm";
  open my $module_fh, '>', $module_file
    or die "Can't open $module_file: $!";
  print $module_fh $package_content;
}

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
  
  my $package_name = "SPVM::Quat_4$prefix";
  
  my $package_content = <<"EOS";
# $package_name is created by regen/regen_quat.pl
package $package_name : mulnum_t {
  has t : $type;
  has x : $type;
  has y : $type;
  has z : $type;
EOS

  $package_content .= "}\n";
  
  my $spvm_module_file = "lib/SPVM/Quat_4$prefix.spvm";
  open my $module_fh, '>', $spvm_module_file
    or die "Can't open $spvm_module_file: $!";
  print $module_fh $package_content;
}

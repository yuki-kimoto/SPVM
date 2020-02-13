use strict;
use warnings;

my @dims = (2, 3, 4);
my @types = qw(byte short int long float double);
sub prefix {
  my ($type) = @_;
  my $prefix = substr($type, 0, 1);
  return $prefix;
}

for my $dim (@dims) {
  for my $type (@types) {
    my $prefix = prefix($type);
    
    my $package_name = "SPVM::Vector_${dim}${prefix}";
    
    my $package_content = "# $package_name is created by regen/regen_vector.pl\n";
    $package_content .= "package $package_name : public mulnum_t {\n";
    for(my $i = 0; $i < $dim; $i++) {
      $package_content .= "  has x$i : public $type;\n";
    }
    $package_content .= "}\n";
    
    my $module_file = "lib/SPVM/Vector_${dim}${prefix}.spvm";
    open my $module_fh, '>', $module_file
      or die "Can't open $module_file: $!";
    print $module_fh $package_content;
  }
}

use strict;
use warnings;

my @types = qw(float double);
sub prefix {
  my ($type) = @_;
  my $prefix = substr($type, 0, 1);
  return $prefix;
}

for my $type (@types) {
  my $prefix = prefix($type);
  
  my $package_name = "SPVM::Complex_2$prefix";
  
  my $spvm_module_content = "# $package_name is created by regen/regen_complex.pl\n";
  $spvm_module_content .= "package $package_name : mulnum_t {\n";
    $spvm_module_content .= <<"EOS";
  has x : $type;
  has y : $type;
EOS
  $spvm_module_content .= "}\n";
  
  my $spvm_module_file = "lib/SPVM/Complex_2$prefix.spvm";
  open my $spvm_module_fh, '>', $spvm_module_file
    or die "Can't open $spvm_module_file: $!";
  print $spvm_module_fh $spvm_module_content;

  my $perl_module_content = <<EOS;
=head1 NAME

$package_name - Complex $type multi numeric type

=head1 SYNOPSYS

  my \$z : $package_name;
  \$z->{x} = 1;
  \$z->{y} = 2;
  
=head1 DESCRIPTION

$package_name is Complex $type multi numeric type.
EOS

  my $perl_module_file = "lib/SPVM/Complex_2$prefix.pm";
  open my $perl_module_fh, '>', $perl_module_file
    or die "Can't open $perl_module_file: $!";
  print $perl_module_fh $perl_module_content;
}

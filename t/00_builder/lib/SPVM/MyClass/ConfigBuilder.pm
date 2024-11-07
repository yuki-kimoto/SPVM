package SPVM::MyClass::ConfigBuilder;

use base 'SPVM::Builder::ConfigBuilder';

sub build_config {
  my ($self, $config) = @_;
  
  $config->add_ccflag('foo');
}

1;

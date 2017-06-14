package SPVM::Compiler;

use Object::Simple -base;

has 'package_infos';

sub new {
  my $self = shift->SUPER::new(@_);
  
  $self->package_infos([]);
  
  return $self;
}

1;

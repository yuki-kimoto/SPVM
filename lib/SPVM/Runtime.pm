package SPVM::Runtime;

use Object::Simple -base;

has 'object';

sub new {
  my $self = shift->SUPER::new(@_);
  
  return $self;
}

1;

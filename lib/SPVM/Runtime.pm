package SPVM::Runtime;

use Object::Simple -base;

has 'runtime';
has 'sub_info';

sub new {
  my $self = shift->SUPER::new(@_);
  
  return $self;
}

1;

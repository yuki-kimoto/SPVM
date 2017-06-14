package SPVM::Compiler;

use Object::Simple -base;

has 'package_infos';
has 'include_paths';

sub new {
  my $self = shift->SUPER::new(@_);
  
  $self->package_infos([]);
  $self->include_paths([]);
  
  return $self;
}

1;

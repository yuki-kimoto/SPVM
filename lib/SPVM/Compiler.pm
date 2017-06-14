package SPVM::Compiler;

use Object::Simple -base;

has 'package_infos';
has 'include_paths';
has 'compiler';

sub new {
  my $self = shift->SUPER::new(@_);
  
  $self->package_infos([]);
  $self->include_paths([]);
  
  return $self;
}

sub create_spvm_subs {
  my $self = shift;
  
}

1;

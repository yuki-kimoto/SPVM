package SPVM::Compiler;

use Object::Simple -base;

use Carp 'croak';

has 'object';

# XS subroutine
# get_sub_table

sub new {
  my $self = shift->SUPER::new(@_);
  
  return $self;
}

1;

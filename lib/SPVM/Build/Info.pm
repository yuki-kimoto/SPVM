package SPVM::Build::Info;

use strict;
use warnings;

sub new {
  my $class = shift;
  
  my $self = {@_};
  
  bless $self, $class;
  
  return $self;
}

1;

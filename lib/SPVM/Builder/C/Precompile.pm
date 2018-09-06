package SPVM::Builder::C::Precompile;

use strict;
use warnings;
use base 'SPVM::Builder::C';

use Carp 'croak', 'confess';
use File::Spec;

use ExtUtils::CBuilder;
use Config;
use File::Copy 'move';
use File::Path 'mkpath', 'rmtree';

use File::Basename 'dirname', 'basename';

use SPVM::Builder;
use SPVM::Builder::Util;

sub new {
  my $self = shift->SUPER::new(@_);

  $self->{category} = 'precompile';
  
  return $self;
}

1;

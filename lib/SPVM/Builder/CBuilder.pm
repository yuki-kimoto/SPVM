package SPVM::Builder::CBuilder;

use strict;
use warnings;

use base 'ExtUtils::CBuilder';

# warn command instead of print command
sub do_system {
  my ($self, @cmd) = @_;
  warn "@cmd\n" if !$self->{quiet};
  return !system(@cmd);
}

1;

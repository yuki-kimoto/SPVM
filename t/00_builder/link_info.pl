use strict;
use warnings;

use Test::More;

use SPVM::Builder::LinkInfo;

{
  my $object_file = SPVM::Builder::LinkInfo->new;
  is(ref $object_file, 'SPVM::Builder::LinkInfo');
}

done_testing;

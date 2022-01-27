use strict;
use warnings;

use Test::More;

use SPVM::Builder::ObjectFile;

{
  my $object_file = SPVM::Builder::ObjectFile->new;
  is(ref $object_file, 'SPVM::Builder::ObjectFile');
}

done_testing;

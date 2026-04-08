use strict;
use warnings;

use Test::More;

use SPVM::Builder::ObjectFileInfo;

{
  my $object_file_info = SPVM::Builder::ObjectFileInfo->new;
  is(ref $object_file_info, 'SPVM::Builder::ObjectFileInfo');
}

done_testing;

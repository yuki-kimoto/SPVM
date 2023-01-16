use strict;
use warnings;

use Test::More;

use SPVM ();

eval { SPVM::get_memory_blocks_count(); };

like($@, qr|SPVM->import must be called at least once|);

done_testing;

use strict;
use warnings;

use Test::More;

my $makefile_file = 'Makefile';

# Dependency
my $makefile_content = do { open my $fh, '<', $makefile_file or die; local $/; <$fh> };

like($makefile_content, qr|\Qlib/SPVM/Fn.spvm|);
like($makefile_content, qr|\Qlib/SPVM/Fn.config|);
like($makefile_content, qr|\Qlib/SPVM/Fn.c|);

done_testing;

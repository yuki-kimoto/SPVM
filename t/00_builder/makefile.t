use strict;
use warnings;

use Test::More;

my $makefile_file = 'Makefile';

# Dependency
my $makefile_content = do { open my $fh, '<', $makefile_file or die; local $/; <$fh> };

like($makefile_content, qr|\Qlib/SPVM/Fn.spvm|);
like($makefile_content, qr|\Qlib/SPVM/Fn.config|);
like($makefile_content, qr|\Qlib/SPVM/Fn.c|);
like($makefile_content, qr|\Qlib/SPVM/Fn.native/include/SPVM__Fn.h|);
like($makefile_content, qr|\Qlib/SPVM/Fn.native/src/SPVM__Fn.c|);

# Resources
like($makefile_content, qr|\Qlib/SPVM/Fn/Resource.spvm|);
like($makefile_content, qr|\Qlib/SPVM/Fn/Resource.config|);
like($makefile_content, qr|\Qlib/SPVM/Fn/Resource.native/include/SPVM__Fn__Resource.h|);
like($makefile_content, qr|\Qlib/SPVM/Fn/Resource.native/src/SPVM__Fn__Resource.c|);

done_testing;

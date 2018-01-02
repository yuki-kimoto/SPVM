use strict;
use warnings;
use utf8;
use Data::Dumper;
use File::Basename 'basename';
use FindBin;

use Test::More 'no_plan';

my $file = 't/' . basename $0;

use FindBin;
use lib "$FindBin::Bin/lib";

my $ok;

BEGIN {
  $SIG{__DIE__} = sub {
    if ($@ =~ /SPVM compile error/) {
      $ok = 1;
    }
  };
}
use SPVM 'TestCase::CompileError::InvalidType';

ok($ok);


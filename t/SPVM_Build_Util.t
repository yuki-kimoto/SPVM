use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM::Builder::Util;

# Documented function check
{
  {
    my $make_rule = SPVM::Builder::Util::create_make_rule_native('Foo');
    ok($make_rule);
  }

  {
    my $make_rule = SPVM::Builder::Util::create_make_rule_precompile('Foo');
    ok($make_rule);
  }
}

1;

done_testing;

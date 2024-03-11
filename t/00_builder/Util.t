use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM::Builder::Util;

# Documented function check
{
  my $lib_dir = "t/test_files";
  {
    my $make_rule = SPVM::Builder::Util::create_make_rule_native('Foo', {lib_dir => $lib_dir});
    ok($make_rule);
  }

  {
    my $make_rule = SPVM::Builder::Util::create_make_rule_precompile('Foo', {lib_dir => $lib_dir});
    ok($make_rule);
  }
}

done_testing;

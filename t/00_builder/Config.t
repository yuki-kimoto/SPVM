use strict;
use warnings;

use Test::More;

use SPVM::Builder::Config;

{
  my $config = SPVM::Builder::Config->new;
  is(ref $config, 'SPVM::Builder::Config');
}

# cc
{
  my $config = SPVM::Builder::Config->new;
  $config->cc('cc_foo');
  is($config->cc, 'cc_foo');
}

# ld
{
  my $config = SPVM::Builder::Config->new;
  $config->ld('ld_foo');
  is($config->ld, 'ld_foo');
}

# extra
{
  ok(SPVM::Builder::LibInfo->can('new'));
  ok(SPVM::Builder::Resource->can('new'));
}

# new
{
  {
    my $config = SPVM::Builder::Config->new_c;
    is($config->ext, 'c');
  }
  {
    my $config = SPVM::Builder::Config->new_c99;
    is($config->ext, 'c');
    is($config->std, 'c99');
  }
  {
    my $config = SPVM::Builder::Config->new_c11;
    is($config->ext, 'c');
    is($config->std, 'c11');
  }
  {
    my $config = SPVM::Builder::Config->new_c99;
    is($config->ext, 'c');
    is($config->std, 'c99');
  }
  {
    my $config = SPVM::Builder::Config->new_c11;
    is($config->ext, 'c');
    is($config->std, 'c11');
  }
  {
    my $config = SPVM::Builder::Config->new_cpp;
    is($config->ext, 'cpp');
    like($config->cc, qr/(g\+\+|clang\+\+)/);
    like($config->ld, qr/(g\+\+|clang\+\+)/);
  }
  {
    my $config = SPVM::Builder::Config->new_cpp11;
    is($config->ext, 'cpp');
    like($config->cc, qr/(g\+\+|clang\+\+)/);
    like($config->ld, qr/(g\+\+|clang\+\+)/);
    is($config->std, 'c++11');
  }
  {
    my $config = SPVM::Builder::Config->new_cpp14;
    is($config->ext, 'cpp');
    like($config->cc, qr/(g\+\+|clang\+\+)/);
    like($config->ld, qr/(g\+\+|clang\+\+)/);
    is($config->std, 'c++14');
  }
  {
    my $config = SPVM::Builder::Config->new_cpp17;
    is($config->ext, 'cpp');
    like($config->cc, qr/(g\+\+|clang\+\+)/);
    like($config->ld, qr/(g\+\+|clang\+\+)/);
    is($config->std, 'c++17');
  }
}

done_testing;

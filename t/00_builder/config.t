use strict;
use warnings;

use Test::More;

use SPVM::Builder::Config;

{
  my $config = SPVM::Builder::Config->new(file_optional => 1);
  is(ref $config, 'SPVM::Builder::Config');
}

# cc
{
  my $config = SPVM::Builder::Config->new(file_optional => 1);
  $config->cc('cc_foo');
  is($config->cc, 'cc_foo');
}

# ld
{
  my $config = SPVM::Builder::Config->new(file_optional => 1);
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
    my $config = SPVM::Builder::Config->new_c(file_optional => 1);
    is($config->ext, 'c');
  }
  {
    my $config = SPVM::Builder::Config->new_c99(file_optional => 1);
    is($config->ext, 'c');
    like("@{$config->ccflags}", qr/\Q-std=c99/);
  }
  {
    my $config = SPVM::Builder::Config->new_c11(file_optional => 1);
    is($config->ext, 'c');
    like("@{$config->ccflags}", qr/\Q-std=c11/);
  }
  {
    my $config = SPVM::Builder::Config->new_gnu99(file_optional => 1);
    is($config->ext, 'c');
    like("@{$config->ccflags}", qr/\Q-std=gnu99/);
  }
  {
    my $config = SPVM::Builder::Config->new_gnu11(file_optional => 1);
    is($config->ext, 'c');
    like("@{$config->ccflags}", qr/\Q-std=gnu11/);
  }
  {
    my $config = SPVM::Builder::Config->new_cpp(file_optional => 1);
    is($config->ext, 'cpp');
    like($config->cc, qr/(g\+\+|clang\+\+)/);
    like($config->ld, qr/(g\+\+|clang\+\+)/);
  }
  {
    my $config = SPVM::Builder::Config->new_cpp11(file_optional => 1);
    is($config->ext, 'cpp');
    like($config->cc, qr/(g\+\+|clang\+\+)/);
    like($config->ld, qr/(g\+\+|clang\+\+)/);
    like("@{$config->ccflags}", qr/\Q-std=c++11/);
  }
  {
    my $config = SPVM::Builder::Config->new_cpp14(file_optional => 1);
    is($config->ext, 'cpp');
    like($config->cc, qr/(g\+\+|clang\+\+)/);
    like($config->ld, qr/(g\+\+|clang\+\+)/);
    like("@{$config->ccflags}", qr/\Q-std=c++14/);
  }
  {
    my $config = SPVM::Builder::Config->new_cpp17(file_optional => 1);
    is($config->ext, 'cpp');
    like($config->cc, qr/(g\+\+|clang\+\+)/);
    like($config->ld, qr/(g\+\+|clang\+\+)/);
    like("@{$config->ccflags}", qr/\Q-std=c++17/);
  }
}

done_testing;

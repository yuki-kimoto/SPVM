use strict;
use warnings;

use Test::More;

use SPVM::Builder::Config::Exe;

{
  my $config_exe = SPVM::Builder::Config::Exe->new;
  isa_ok($config_exe, 'SPVM::Builder::Config');
  is(ref $config_exe, 'SPVM::Builder::Config::Exe');
}

# global_ccflags
{
  my $config_exe = SPVM::Builder::Config::Exe->new;
  $config_exe->global_ccflags(['foo']);
  is_deeply($config_exe->global_ccflags, ['foo']);
}

# add_global_ccflags
{
  my $config_exe = SPVM::Builder::Config::Exe->new;
  $config_exe->add_global_ccflags('foo', 'bar');
  is_deeply($config_exe->global_ccflags, ['foo', 'bar']);
}

done_testing;

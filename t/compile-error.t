use strict;
use warnings;
use utf8;
use Data::Dumper;
use File::Basename 'basename';
use FindBin;

use SPVM::Build;

use Test::More 'no_plan';

my $file = 't/' . basename $0;

use FindBin;
use lib "$FindBin::Bin/default/lib";

my $ok;

{
  my $package_infos = [
    {
      name => 'TestCase::CompileError::InvalidType',
      file => __FILE__,
      line => __LINE__ - 2,
    }
  ];
  my $build = SPVM::Build->new(package_infos => $package_infos);
  my $success = $build->compile_spvm();
  ok($success == 0);
}

{
  my $package_infos = [
    {
      name => 'TestCase::CompileError::TypeCantBeDetectedUndef',
      file => __FILE__,
      line => __LINE__ - 2,
    }
  ];
  my $build = SPVM::Build->new(package_infos => $package_infos);
  my $success = $build->compile_spvm();
  ok($success == 0);
}

{
  my $package_infos = [
    {
      name => 'TestCase::CompileError::TypeCantBeDetectedUndefDefault',
      file => __FILE__,
      line => __LINE__ - 2,
    }
  ];
  my $build = SPVM::Build->new(package_infos => $package_infos);
  my $success = $build->compile_spvm();
  ok($success == 0);
}

{
  my $package_infos = [
    {
      name => 'TestCase::CompileError::AssignIncompatibleType::DifferentObject',
      file => __FILE__,
      line => __LINE__ - 2,
    }
  ];
  my $build = SPVM::Build->new(package_infos => $package_infos);
  my $success = $build->compile_spvm();
  ok($success == 0);
}

{
  my $package_infos = [
    {
      name => 'TestCase::CompileError::AssignIncompatibleType::ConstToNoConst',
      file => __FILE__,
      line => __LINE__ - 2,
    }
  ];
  my $build = SPVM::Build->new(package_infos => $package_infos);
  my $success = $build->compile_spvm();
  ok($success == 0);
}

{
  my $package_infos = [
    {
      name => 'TestCase::CompileError::Field::Private',
      file => __FILE__,
      line => __LINE__ - 2,
    }
  ];
  my $build = SPVM::Build->new(package_infos => $package_infos);
  my $success = $build->compile_spvm();
  ok($success == 0);
}

{
  my $package_infos = [
    {
      name => 'TestCase::CompileError::New::Private',
      file => __FILE__,
      line => __LINE__ - 2,
    }
  ];
  my $build = SPVM::Build->new(package_infos => $package_infos);
  my $success = $build->compile_spvm();
  ok($success == 0);
}

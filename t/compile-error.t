use strict;
use warnings;
use utf8;
use Data::Dumper;
use File::Basename 'basename';
use FindBin;

use SPVM::Builder;

use Test::More 'no_plan';

my $file = 't/' . basename $0;

use FindBin;
use lib "$FindBin::Bin/default/lib";

# Assign
{
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::Assign::DifferentObject');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::Assign::ConstToNoConst');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::Assign::NotNumericToNumeric');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::Assign::NarrwoingConvertionIntToByte');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::Assign::NarrwoingConvertionIntToShort');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::Assign::NarrwoingConvertionLongToByte');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::Assign::NarrwoingConvertionLongToInt');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::Assign::NarrwoingConvertionLongToShort');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
}

# isa
{
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::Isa::LeftIsNotObject');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::Isa::RightIsAnyObject');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
}

{
  my $build = SPVM::Builder->new;
  $build->use('TestCase::CompileError::InvalidType');
  my $success = $build->compile_spvm();
  ok($success == 0);
}

{
  my $build = SPVM::Builder->new;
  $build->use('TestCase::CompileError::TypeCantBeDetectedUndef');
  my $success = $build->compile_spvm();
  ok($success == 0);
}

{
  my $build = SPVM::Builder->new;
  $build->use('TestCase::CompileError::TypeCantBeDetectedUndefDefault');
  my $success = $build->compile_spvm();
  ok($success == 0);
}

{
  my $build = SPVM::Builder->new;
  $build->use('TestCase::CompileError::Field::Private');
  my $success = $build->compile_spvm();
  ok($success == 0);
}

{
  my $build = SPVM::Builder->new;
  $build->use('TestCase::CompileError::New::Private');
  my $success = $build->compile_spvm();
  ok($success == 0);
}

# Convert
{
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::Convert::ConvertToRef');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }

  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::Convert::ConvertFromRef');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }

  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::Convert::ConvertFromValueType');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
}

# Concat
{
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::Concat::RightIsNotString');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
  {
    my $build = SPVM::Builder->new;
    $build->use('TestCase::CompileError::Concat::LeftIsNotString');
    my $success = $build->compile_spvm();
    ok($success == 0);
  }
}

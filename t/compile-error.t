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

BEGIN { $ENV{SPVM_NO_COMPILE} = 1 }

sub init_spvm {
  @SPVM::PACKAGE_INFOS = ();
  %SPVM::PACKAGE_INFO_SYMTABLE = ();
}

{
  BEGIN { init_spvm() }
  use SPVM 'TestCase::CompileError::InvalidType';
  BEGIN {
    my $success = SPVM::Build->new->compile_spvm();
    ok($success == 0);
  }
}

{
  BEGIN { init_spvm() }
  use SPVM 'TestCase::CompileError::TypeCantBeDetectedUndefDefault';
  BEGIN {
    my $success = SPVM::Build->new->compile_spvm();
    ok($success == 0);
  }
}

{
  BEGIN { init_spvm() }
  use SPVM 'TestCase::CompileError::AssignIncompatibleType::DifferentObject';
  BEGIN {
    my $success = SPVM::Build->new->compile_spvm();
    ok($success == 0);
  }
}

{
  BEGIN { init_spvm() }
  use SPVM 'TestCase::CompileError::Field::Private';
  BEGIN {
    my $success = SPVM::Build->new->compile_spvm();
    ok($success == 0);
  }
}

{
  BEGIN { init_spvm() }
  use SPVM 'TestCase::CompileError::New::Private';
  BEGIN {
    my $success = SPVM::Build->new->compile_spvm();
    ok($success == 0);
  }
}

use strict;
use warnings;
use utf8;
use FindBin;

use SPVM::Builder;

use lib "$FindBin::Bin/../default/lib";
use lib "$FindBin::Bin/lib";

use MyTest qw(compile_not_ok_file compile_not_ok);

use Test::More;

# SPVM compile error
{
  my $command = "$^X -Mblib $FindBin::Bin/perl_program.pl 2>&1";
  my $output = `$command 2>&1`;
  like($output, qr/CompileError/);
}

# SPVM dist compile error
{
  my $command = "$^X -Mblib $FindBin::Bin/dist.pl 2>&1";
  my $output = `$command 2>&1`;
  like($output, qr/CompileError/);
}


done_testing;

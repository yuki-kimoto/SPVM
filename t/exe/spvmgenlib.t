use Test::More;
use strict;
use warnings;

{
  # Basic
  {
    my $spvmgenlib_cmd = qq($^X -Mblib blib/script/spvmgenlib -v);
    system($spvmgenlib_cmd) == 0
      or die "Can't execute spvmgenlib command $spvmgenlib_cmd:$!";
    my $output = `$spvmgenlib_cmd`;
    like($output, qr/spvmgenlib/);
  }
}

done_testing;

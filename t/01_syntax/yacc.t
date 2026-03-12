use lib "t/lib";

use strict;
use warnings;
use utf8;
use FindBin;

use lib "$FindBin::Bin/lib";

use TestUtil qw(compile_not_ok_file compile_not_ok);

use Test::More;

# Compilation Errors in yacc/spvm_yacc.y

# reduce/reduce is not allowed
{
  {
    my $tmp_dir = File::Temp->newdir;
    my $output = `bison -o $tmp_dir/spvm_yacc.c --defines=$tmp_dir/spvm_yacc.h -t -p SPVM_yy -d yacc/spvm_yacc.y 2>&1`;
    if ($? == 0) {
      warn "$output";
      if ($output =~ m|reduce/reduce|) {
        ok(0);
      }
    }
  }
}

# Extra
{
  {
    my $source = 'class MyClass { static method main : int () { my $num = 0; 1 && $num = 3; } }';
    compile_not_ok($source, qr|The left operand of assignment operator must be mutable|);
  }
}

done_testing;

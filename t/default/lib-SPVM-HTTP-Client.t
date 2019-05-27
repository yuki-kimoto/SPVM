use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';
use TestFile;

use SPVM 'TestCase::Lib::SPVM::HTTP::Client';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

# Copy test_files to test_files_tmp with replacing os newline
TestFile::copy_test_files_tmp_replace_newline();

sub _ok (&) {
  my $fname = "$FindBin::Bin/../test_files_tmp/_socket_data.tmp";
  open (my $fh, ">", $fname) or die "Can't open $fname:$!";
  close $fh;
  ok(shift->($fname));
  print("--- REMOTE DATA ---\n");
  open ($fh, "<", $fname) or die "Can't open $fname:$!";
  print do { local $/; <$fh> };
  print("------- EOF -------\n");
  close $fh;
  #unlink $fname;
}

# SPVM::HTTP::Client
{
  _ok { TestCase::Lib::SPVM::HTTP::Client->test_basic(@_) }
}


# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

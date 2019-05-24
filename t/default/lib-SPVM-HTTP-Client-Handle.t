use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Lib::SPVM::HTTP::Client::Handle';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

sub _ok (&) {
  my $file = "$FindBin::Bin/../test_files_tmp/socket_mock.txt";
  open my $fh, ">", $file or die $!;
  close $fh;
  ok(shift->($file));
  unlink($file) or die $!;
}

# SPVM::HTTP::Client::Handle
{
  _ok { TestCase::Lib::SPVM::HTTP::Client::Handle->test_read(@_) };
  _ok { TestCase::Lib::SPVM::HTTP::Client::Handle->test_readline(@_) };
  _ok { TestCase::Lib::SPVM::HTTP::Client::Handle->test_read_header_lines(@_) };
}


# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

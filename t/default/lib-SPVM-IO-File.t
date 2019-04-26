use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Lib::SPVM::IO::File';

use TestFile;

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

# Copy test_files to test_files_tmp with replacing os newline
TestFile::copy_test_files_tmp_replace_newline();

{
  # open
  {
    my $sp_file = SPVM::new_str("$FindBin::Bin/../test_files_tmp/fread.txt");
    ok(TestCase::Lib::SPVM::IO::File->test_open($sp_file));
  }
  
  # close
  {
    my $sp_file = SPVM::new_str("$FindBin::Bin/../test_files_tmp/fread.txt");
    ok(TestCase::Lib::SPVM::IO::File->test_close($sp_file));
  }
  
  # read
  {
    my $sp_file = SPVM::new_str("$FindBin::Bin/../test_files_tmp/fread.txt");
    ok(TestCase::Lib::SPVM::IO::File->test_read($sp_file));
  }
  
  # write
  {
    my $sp_file = SPVM::new_str("$FindBin::Bin/../test_files_tmp/fwrite.txt");
    ok(TestCase::Lib::SPVM::IO::File->test_write($sp_file));
  }
  
  # gets
  {
    {
      my $sp_file = SPVM::new_str("$FindBin::Bin/../test_files_tmp/fread.txt");
      ok(TestCase::Lib::SPVM::IO::File->test_gets($sp_file));
    }
    {
      my $sp_file = SPVM::new_str("$FindBin::Bin/../test_files_tmp/fread.txt");
      ok(TestCase::Lib::SPVM::IO::File->test_gets_while($sp_file));
    }
    {
      my $sp_file = SPVM::new_str("$FindBin::Bin/../test_files_tmp/file_eof.txt");
      ok(TestCase::Lib::SPVM::IO::File->test_gets_eof($sp_file));
    }
    {
      my $sp_file = SPVM::new_str("$FindBin::Bin/../test_files_tmp/long_line.txt");
      ok(TestCase::Lib::SPVM::IO::File->test_gets_long_line($sp_file));
    }
  }
  
  # gets_chomp
  {
    {
      my $sp_file = SPVM::new_str("$FindBin::Bin/../test_files_tmp/fread.txt");
      ok(TestCase::Lib::SPVM::IO::File->test_gets_chomp($sp_file));
    }
    {
      my $sp_file = SPVM::new_str("$FindBin::Bin/../test_files_tmp/fread.txt");
      ok(TestCase::Lib::SPVM::IO::File->test_gets_chomp_while($sp_file));
    }
    {
      my $sp_file = SPVM::new_str("$FindBin::Bin/../test_files_tmp/file_eof.txt");
      ok(TestCase::Lib::SPVM::IO::File->test_gets_chomp_eof($sp_file));
    }
    {
      my $sp_file = SPVM::new_str("$FindBin::Bin/../test_files_tmp/long_line.txt");
      ok(TestCase::Lib::SPVM::IO::File->test_gets_chomp_long_line($sp_file));
    }
  }

  # slurp
  {
    my $sp_file = SPVM::new_str("$FindBin::Bin/../test_files_tmp/fread.txt");
    ok(TestCase::Lib::SPVM::IO::File->test_slurp($sp_file));
  }
}


# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

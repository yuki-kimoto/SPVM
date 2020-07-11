use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Lib::SPVM::IO::File';



use TestFile;

sub slurp_binmode {
  my ($output_file) = @_;
  
  open my $fh, '<', $output_file
    or die "Can't open file $output_file:$!";
  
  binmode $fh;
  
  my $output = do { local $/; <$fh> };
  
  return $output;
}

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Copy test_files to test_files_tmp with replacing os newline
TestFile::copy_test_files_tmp();

my $test_dir = "$FindBin::Bin/..";

# flush
{
  # test_flush
  {
    my $file = "$test_dir/test_files_tmp/io_file_test_flush.txt";
    ok(TestCase::Lib::SPVM::IO::File->test_flush($file));
    my $output = slurp_binmode($file);
    is($output, 'Hello');

    # This is not real tests, but I can't know the way to test buffer
    my $stdout_source = slurp_binmode('blib/lib/SPVM/IO/File.c');
    like($stdout_source, qr|\Qfflush(fh);//SPVM::IO::File::flush|);
  }
}

# auto_flush
{
  # test_auto_flush
  {
    my $file = "$test_dir/test_files_tmp/io_file_test_auto_flush.txt";
    ok(TestCase::Lib::SPVM::IO::File->test_auto_flush($file));
    my $output = slurp_binmode($file);
    is($output, 'Hello');

    # This is not real tests, but I can't know the way to test buffer
    my $stdout_source = slurp_binmode('blib/lib/SPVM/IO/File.c');
    like($stdout_source, qr|\Qfflush(fh);//SPVM::IO::File::print|);
  }
}

# print
{
  # test_print
  {
    my $file = "$test_dir/test_files_tmp/io_file_test_print.txt";
    ok(TestCase::Lib::SPVM::IO::File->test_print($file));
    my $output = slurp_binmode($file);
    is($output, 'Hello');
  }

  # test_print_newline
  {
    my $file = "$test_dir/test_files_tmp/io_file_test_print_newline.txt";
    ok(TestCase::Lib::SPVM::IO::File->test_print_newline($file));
    my $output = slurp_binmode($file);
    is($output, "\x0A");
  }

  # test_print_long_lines
  {
    my $file = "$test_dir/test_files_tmp/io_file_test_print_long_lines.txt";
    ok(TestCase::Lib::SPVM::IO::File->test_print_long_lines($file));
    my $output = slurp_binmode($file);
    is($output, "AAAAAAAAAAAAA\x0ABBBBBBBBBBBBBBBBBBB\x0ACCCCCCCCCCCCCCCCCCCCCCCCCCC\x0ADDDDDDDDDDDDDDDDDDDDDDDDD\x0AEEEEEEEEEEEEEEEEEEEEEE\x0AFFFFFFFFFFFFFF\x0A");
  }
}

# open
{
  my $sp_file = SPVM::new_string("$test_dir/test_files_tmp/fread.txt");
  ok(TestCase::Lib::SPVM::IO::File->test_open($sp_file));
}

# read
{
  my $sp_file = SPVM::new_string("$test_dir/test_files_tmp/fread.txt");
  ok(TestCase::Lib::SPVM::IO::File->test_read($sp_file));
}

# readline
{
  {
    my $sp_file = SPVM::new_string("$test_dir/test_files_tmp/fread.txt");
    ok(TestCase::Lib::SPVM::IO::File->test_readline($sp_file));
  }
  {
    my $sp_file = SPVM::new_string("$test_dir/test_files_tmp/fread.txt");
    ok(TestCase::Lib::SPVM::IO::File->test_readline_while($sp_file));
  }
  {
    my $sp_file = SPVM::new_string("$test_dir/test_files_tmp/file_eof.txt");
    ok(TestCase::Lib::SPVM::IO::File->test_readline_eof($sp_file));
  }
  {
    my $sp_file = SPVM::new_string("$test_dir/test_files_tmp/long_line.txt");
    ok(TestCase::Lib::SPVM::IO::File->test_readline_long_line($sp_file));
  }
}

# readline and chomp_lf
{
  {
    my $sp_file = SPVM::new_string("$test_dir/test_files_tmp/fread.txt");
    ok(TestCase::Lib::SPVM::IO::File->test_readline_chomp_lf($sp_file));
  }
  {
    my $sp_file = SPVM::new_string("$test_dir/test_files_tmp/fread.txt");
    ok(TestCase::Lib::SPVM::IO::File->test_readline_chomp_lf_while($sp_file));
  }
  {
    my $sp_file = SPVM::new_string("$test_dir/test_files_tmp/file_eof.txt");
    ok(TestCase::Lib::SPVM::IO::File->test_readline_chomp_lf_eof($sp_file));
  }
  {
    my $sp_file = SPVM::new_string("$test_dir/test_files_tmp/long_line.txt");
    ok(TestCase::Lib::SPVM::IO::File->test_readline_chomp_lf_long_line($sp_file));
  }
}

# slurp
{
  my $sp_file = SPVM::new_string("$test_dir/test_files_tmp/fread.txt");
  ok(TestCase::Lib::SPVM::IO::File->test_slurp($sp_file));
}


# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

use lib "t/testlib";
use TestAuto;

use strict;
use warnings;
use File::Path 'mkpath';

use Test::More;

use TestFile;
use SPVM 'TestCase::Print';
use SPVM 'TestCase::NativeAPI';

my $test_dir = $ENV{SPVM_TEST_DIR};
my $build_dir = $ENV{SPVM_BUILD_DIR};

my $test_tmp_dir = "$test_dir/test_files_tmp";

my $output_file = "$test_tmp_dir/print-output.txt";

mkpath $test_tmp_dir;

sub slurp_binmode {
  my ($output_file) = @_;
  
  open my $fh, '<', $output_file
    or die "Can't open file $output_file:$!";
  
  binmode $fh;
  
  my $output = do { local $/; <$fh> };
  
  return $output;
}

# Start objects count
my $start_memory_blocks_count = SPVM::api->get_memory_blocks_count();

{
  SPVM::TestCase::NativeAPI->save_stdout_windows_binary_mode();
  
  # print
  {
    # print
    {
      SPVM::TestCase::NativeAPI->freopen_stdout($output_file);
      
      SPVM::TestCase::Print->print;
      
      SPVM::TestCase::NativeAPI->close_stdout();
      
      my $output = slurp_binmode($output_file);
      is($output, 'Hello');
    }
    
    {
      SPVM::TestCase::NativeAPI->freopen_stdout($output_file);
      
      SPVM::TestCase::Print->print_newline;
      
      SPVM::TestCase::NativeAPI->close_stdout();
      
      my $output = slurp_binmode($output_file);
      is($output, "\x0A");
    }
    
    {
      SPVM::TestCase::NativeAPI->freopen_stdout($output_file);
      
      SPVM::TestCase::Print->print_long_lines;
      
      SPVM::TestCase::NativeAPI->close_stdout();
      
      my $output = slurp_binmode($output_file);
      is($output, "AAAAAAAAAAAAA\x0ABBBBBBBBBBBBBBBBBBB\x0ACCCCCCCCCCCCCCCCCCCCCCCCCCC\x0ADDDDDDDDDDDDDDDDDDDDDDDDD\x0AEEEEEEEEEEEEEEEEEEEEEE\x0AFFFFFFFFFFFFFF\x0A");
    }
    
    {
      SPVM::TestCase::NativeAPI->freopen_stdout($output_file);
      
      SPVM::TestCase::Print->print_empty;
      
      SPVM::TestCase::NativeAPI->close_stdout();
      
      my $output = slurp_binmode($output_file);
      is($output, "");
    }
    
    {
      SPVM::TestCase::NativeAPI->freopen_stdout($output_file);
      
      SPVM::TestCase::Print->print_undef;
      
      SPVM::TestCase::NativeAPI->close_stdout();
      
      my $output = slurp_binmode($output_file);
      is($output, "");
    }
  }
}

# All object is freed
my $end_memory_blocks_count = SPVM::api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;

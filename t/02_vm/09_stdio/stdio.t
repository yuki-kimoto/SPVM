use lib "t/testlib";
use TestAuto;

use strict;
use warnings;
use File::Path 'mkpath';

use Test::More;

use TestFile;
use SPVM 'TestCase::Stdio';
use SPVM 'TestCase::NativeAPI';

my $test_dir = $ENV{SPVM_TEST_DIR};
my $build_dir = $ENV{SPVM_BUILD_DIR};

my $test_tmp_dir = "$test_dir/test_files_tmp";

my $script_file = "$test_tmp_dir/print-script.pl";
my $output_file = "$test_tmp_dir/print-output.txt";

mkpath $test_tmp_dir;

sub write_script_file {
  my ($script_file, $func_call) = @_;
  
  my $pre = <<"EOS";
use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use SPVM 'TestCase::Stdio';



use TestFile;

EOS

  open my $script_fh, '>', $script_file
    or die "Can't open file $script_file: $!";
  
  my $output_source = "$pre$func_call;";
  
  print $script_fh $output_source;
}

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

{
  # stdout
  {
    # print "\n" to stdout
    {
      my $func_call = 'SPVM::TestCase::Stdio->print_line_feed_to_stdout';
      write_script_file($script_file, $func_call);
      system("$^X -Mblib $script_file > $output_file");
      my $output = slurp_binmode($output_file);
      is($output, "\x0A");
    }
  }

  # stderr
  {
    # print "\n" to stderr
    {
      my $func_call = 'SPVM::TestCase::Stdio->print_line_feed_to_stderr';
      write_script_file($script_file, $func_call);
      system("$^X -Mblib $script_file 2> $output_file");
      my $output = slurp_binmode($output_file);
      is($output, "\x0A");
    }
  }
  
  # stdin, stdout, stderr is binary mode
  ok(SPVM::TestCase::NativeAPI->check_stdin_stdout_stderr_binary_mode);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;

use lib "t/testlib";
use TestAuto;

use strict;
use warnings;
use File::Path 'mkpath';

use Test::More;

use TestFile;
use SPVM 'TestCase::Print';

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

use SPVM 'TestCase::Print';



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
my $start_memory_blocks_count = SPVM::api->get_memory_blocks_count();

{
  # print
  {
    # test_print
    {
      my $func_call = 'SPVM::TestCase::Print->print';
      write_script_file($script_file, $func_call);
      system("$^X -Mblib $script_file > $output_file");
      my $output = slurp_binmode($output_file);
      is($output, 'Hello');
    }

    # test_print_newline
    {
      my $func_call = 'SPVM::TestCase::Print->print_newline';
      write_script_file($script_file, $func_call);
      system("$^X -Mblib $script_file > $output_file");
      my $output = slurp_binmode($output_file);
      is($output, "\x0A");
    }
    
    # test_print_long_lines
    {
      my $func_call = 'SPVM::TestCase::Print->print_long_lines';
      write_script_file($script_file, $func_call);
      system("$^X -Mblib $script_file > $output_file");
      my $output = slurp_binmode($output_file);
      is($output, "AAAAAAAAAAAAA\x0ABBBBBBBBBBBBBBBBBBB\x0ACCCCCCCCCCCCCCCCCCCCCCCCCCC\x0ADDDDDDDDDDDDDDDDDDDDDDDDD\x0AEEEEEEEEEEEEEEEEEEEEEE\x0AFFFFFFFFFFFFFF\x0A");
    }
    # test_print_empty
    {
      my $func_call = 'SPVM::TestCase::Print->print_empty';
      write_script_file($script_file, $func_call);
      system("$^X -Mblib $script_file > $output_file");
      my $output = slurp_binmode($output_file);
      is($output, "");
    }
    # test_print_undef
    {
      my $func_call = 'SPVM::TestCase::Print->print_undef';
      write_script_file($script_file, $func_call);
      system("$^X -Mblib $script_file > $output_file");
      my $output = slurp_binmode($output_file);
      is($output, "");
    }
  }
}

# All object is freed
my $end_memory_blocks_count = SPVM::api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;

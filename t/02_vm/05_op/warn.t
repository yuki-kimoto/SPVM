use lib "t/testlib";
use TestAuto;

use strict;
use warnings;
use File::Path 'mkpath';

use Test::More;

use TestFile;
use SPVM 'TestCase::Warn';



my $test_dir = $ENV{SPVM_TEST_DIR};
my $build_dir = $ENV{SPVM_BUILD_DIR};

my $test_tmp_dir = "$test_dir/test_files_tmp";

my $script_file = "$test_tmp_dir/warn-script.pl";
my $output_file = "$test_tmp_dir/warn-output.txt";

mkpath $test_tmp_dir;

sub write_script_file {
  my ($script_file, $func_call) = @_;
  
  my $pre = <<"EOS";
use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use SPVM 'TestCase::Warn';



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
  # warn
  {
    # test_warn
    {
      my $func_call = 'SPVM::TestCase::Warn->test_warn';
      write_script_file($script_file, $func_call);
      system("$^X -Mblib $script_file 2> $output_file");
      my $output = slurp_binmode($output_file);
      like($output, qr|Hello\n  TestCase::Warn->test_warn at .*TestCase/Warn.spvm line 4|);
    }

    # test_warn_newline
    {
      my $func_call = 'SPVM::TestCase::Warn->test_warn_newline';
      write_script_file($script_file, $func_call);
      system("$^X -Mblib $script_file 2> $output_file");
      my $output = slurp_binmode($output_file);
      is($output, "\x0A");
    }
    
    # test_warn_long_lines
    {
      my $func_call = 'SPVM::TestCase::Warn->test_warn_long_lines';
      write_script_file($script_file, $func_call);
      system("$^X -Mblib $script_file 2> $output_file");
      my $output = slurp_binmode($output_file);
      is($output, "AAAAAAAAAAAAA\x0ABBBBBBBBBBBBBBBBBBB\x0ACCCCCCCCCCCCCCCCCCCCCCCCCCC\x0ADDDDDDDDDDDDDDDDDDDDDDDDD\x0AEEEEEEEEEEEEEEEEEEEEEE\x0AFFFFFFFFFFFFFF\x0A");
    }

    # test_warn_empty
    {
      my $func_call = 'SPVM::TestCase::Warn->test_warn_empty';
      write_script_file($script_file, $func_call);
      system("$^X -Mblib $script_file 2> $output_file");
      my $output = slurp_binmode($output_file);
      like($output, qr|Warning\n  TestCase::Warn->test_warn_empty at .*TestCase/Warn.spvm line 21|);
    }

    # test_test_warn_undef
    {
      my $func_call = 'SPVM::TestCase::Warn->test_warn_undef';
      write_script_file($script_file, $func_call);
      system("$^X -Mblib $script_file 2> $output_file");
      my $output = slurp_binmode($output_file);
      like($output, qr|Warning\n  TestCase::Warn->test_warn_undef at .*TestCase/Warn.spvm line 27|);
    }

    # test_test_warn_no_operand
    {
      my $func_call = 'SPVM::TestCase::Warn->test_warn_no_operand';
      write_script_file($script_file, $func_call);
      system("$^X -Mblib $script_file 2> $output_file");
      my $output = slurp_binmode($output_file);
      like($output, qr|Warning\n  TestCase::Warn->test_warn_no_operand at .*TestCase/Warn.spvm line 33|);
    }
    
    # test_test_warn_undef_type
    {
      my $func_call = 'SPVM::TestCase::Warn->test_warn_undef_type';
      write_script_file($script_file, $func_call);
      system("$^X -Mblib $script_file 2> $output_file");
      my $output = slurp_binmode($output_file);
      like($output, qr|Warning\n  TestCase::Warn->test_warn_undef_type at .*TestCase/Warn.spvm line 39|);
    }
  }
}

# All object is freed
my $end_memory_blocks_count = SPVM::api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;

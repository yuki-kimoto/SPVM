use lib "t/testlib";
use TestAuto;

use strict;
use warnings;
use File::Path 'mkpath';

use Test::More;

use TestFile;
use SPVM 'TestCase::Operator::Warn';



my $test_dir = $ENV{SPVM_TEST_DIR};
my $build_dir = $ENV{SPVM_BUILD_DIR};

my $test_tmp_dir = "$test_dir/test_files/.tmp";

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

use SPVM 'TestCase::Operator::Warn';



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
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

{
  # warn
  {
    # test_warn
    {
      my $func_call = 'SPVM::TestCase::Operator::Warn->test_warn';
      write_script_file($script_file, $func_call);
      system("$^X -Mblib $script_file 2> $output_file");
      my $output = slurp_binmode($output_file);
      like($output, qr|Hello\n  TestCase::Operator::Warn->test_warn at .*TestCase/Operator/Warn.spvm line 4|);
    }

    # test_warn_newline
    {
      my $func_call = 'SPVM::TestCase::Operator::Warn->test_warn_newline';
      write_script_file($script_file, $func_call);
      system("$^X -Mblib $script_file 2> $output_file");
      my $output = slurp_binmode($output_file);
      like($output, qr/\x0A/);
      like($output, qr|^  TestCase::Operator::Warn->test_warn_newline at .*TestCase/Operator/Warn.spvm line \d+|m);
    }
    
    # test_warn_long_lines
    {
      my $func_call = 'SPVM::TestCase::Operator::Warn->test_warn_long_lines';
      write_script_file($script_file, $func_call);
      system("$^X -Mblib $script_file 2> $output_file");
      my $output = slurp_binmode($output_file);
      like($output, qr|AAAAAAAAAAAAA\x0ABBBBBBBBBBBBBBBBBBB\x0ACCCCCCCCCCCCCCCCCCCCCCCCCCC\x0ADDDDDDDDDDDDDDDDDDDDDDDDD\x0AEEEEEEEEEEEEEEEEEEEEEE\x0AFFFFFFFFFFFFFF\x0A|);
      like($output, qr|^  TestCase::Operator::Warn->test_warn_long_lines at .*TestCase/Operator/Warn.spvm line \d+|m);
    }

    # test_warn_empty
    {
      my $func_call = 'SPVM::TestCase::Operator::Warn->test_warn_empty';
      write_script_file($script_file, $func_call);
      system("$^X -Mblib $script_file 2> $output_file");
      my $output = slurp_binmode($output_file);
      like($output, qr|\n  TestCase::Operator::Warn->test_warn_empty at .*TestCase/Operator/Warn.spvm line 21|);
    }

    # test_test_warn_undef
    {
      my $func_call = 'SPVM::TestCase::Operator::Warn->test_warn_undef';
      write_script_file($script_file, $func_call);
      system("$^X -Mblib $script_file 2> $output_file");
      my $output = slurp_binmode($output_file);
      like($output, qr|undef\n  TestCase::Operator::Warn->test_warn_undef at .*TestCase/Operator/Warn.spvm line 27|);
    }

    # test_test_warn_no_operand
    {
      my $func_call = 'SPVM::TestCase::Operator::Warn->test_warn_no_operand';
      write_script_file($script_file, $func_call);
      system("$^X -Mblib $script_file 2> $output_file");
      my $output = slurp_binmode($output_file);
      like($output, qr|Warning\n  TestCase::Operator::Warn->test_warn_no_operand at .*TestCase/Operator/Warn.spvm line 33|);
    }
    
    # test_warn_object_type
    {
      my $func_call = 'SPVM::TestCase::Operator::Warn->test_warn_object_type';
      write_script_file($script_file, $func_call);
      system("$^X -Mblib $script_file 2> $output_file");
      my $output = slurp_binmode($output_file);
      like($output, qr|^Int\(0x[0-9a-fA-F]+\)\n  TestCase::Operator::Warn->test_warn_object_type at .*TestCase/Operator/Warn.spvm line 39|);
    }
    
    # test_Fn_print_stderr
    {
      my $func_call = 'SPVM::TestCase::Operator::Warn->test_Fn_print_stderr';
      write_script_file($script_file, $func_call);
      system("$^X -Mblib $script_file 2> $output_file");
      my $output = slurp_binmode($output_file);
      is($output, 'Hello');
    }
    
    # test_Fn_print_stderr_undef
    {
      my $func_call = 'SPVM::TestCase::Operator::Warn->test_Fn_print_stderr_undef';
      write_script_file($script_file, $func_call);
      system("$^X -Mblib $script_file 2> $output_file");
      my $output = slurp_binmode($output_file);
      is($output, '');
    }
    
    # test_Fn_say_stderr
    {
      my $func_call = 'SPVM::TestCase::Operator::Warn->test_Fn_say_stderr';
      write_script_file($script_file, $func_call);
      system("$^X -Mblib $script_file 2> $output_file");
      my $output = slurp_binmode($output_file);
      is($output, "Hello\x{0A}");
    }
    
    # test_Fn_say_stderr_undef
    {
      my $func_call = 'SPVM::TestCase::Operator::Warn->test_Fn_say_stderr_undef';
      write_script_file($script_file, $func_call);
      system("$^X -Mblib $script_file 2> $output_file");
      my $output = slurp_binmode($output_file);
      is($output, "\x{0A}");
    }
    
    SPVM::TestCase::Operator::Warn->warn_object_address;
    
    SPVM::TestCase::Operator::Warn->warn_ref;
  }
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;

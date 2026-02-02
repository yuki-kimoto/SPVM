use lib "t/testlib";
use TestAuto;

use strict;
use warnings;
use File::Path 'mkpath';

use Test::More;

use TestFile;
use SPVM (); # Load SPVM API
use SPVM 'TestCase::Operator::Warn';

my $test_dir = $ENV{SPVM_TEST_DIR};
my $test_tmp_dir = "$test_dir/test_files/.tmp";

my $script_file = "$test_tmp_dir/warn-script.pl";
my $output_file = "$test_tmp_dir/warn-output.txt";

mkpath $test_tmp_dir;

# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

my $class_name = 'TestCase::Operator::Warn';

# warn
{
  {
    # test_warn
    {
      my $method_name = 'test_warn';
      TestFile::generate_class_method_call_script($script_file, $class_name, $method_name);
      system("$^X -Mblib $script_file 2> $output_file");
      my $output = TestFile::slurp_binmode($output_file);
      like($output, qr|Hello\n  TestCase::Operator::Warn#test_warn at .*TestCase/Operator/Warn.spvm line 4|);
    }

    # test_warn_newline
    {
      my $method_name = 'test_warn_newline';
      TestFile::generate_class_method_call_script($script_file, $class_name, $method_name);
      system("$^X -Mblib $script_file 2> $output_file");
      my $output = TestFile::slurp_binmode($output_file);
      like($output, qr/\x0A/);
      like($output, qr|^  TestCase::Operator::Warn#test_warn_newline at .*TestCase/Operator/Warn.spvm line \d+|m);
    }
    
    # test_warn_long_lines
    {
      my $method_name = 'test_warn_long_lines';
      TestFile::generate_class_method_call_script($script_file, $class_name, $method_name);
      system("$^X -Mblib $script_file 2> $output_file");
      my $output = TestFile::slurp_binmode($output_file);
      like($output, qr|AAAAAAAAAAAAA\x0ABBBBBBBBBBBBBBBBBBB\x0ACCCCCCCCCCCCCCCCCCCCCCCCCCC\x0ADDDDDDDDDDDDDDDDDDDDDDDDD\x0AEEEEEEEEEEEEEEEEEEEEEE\x0AFFFFFFFFFFFFFF\x0A|);
      like($output, qr|^  TestCase::Operator::Warn#test_warn_long_lines at .*TestCase/Operator/Warn.spvm line \d+|m);
    }

    # test_warn_empty
    {
      my $method_name = 'test_warn_empty';
      TestFile::generate_class_method_call_script($script_file, $class_name, $method_name);
      system("$^X -Mblib $script_file 2> $output_file");
      my $output = TestFile::slurp_binmode($output_file);
      like($output, qr|\n  TestCase::Operator::Warn#test_warn_empty at .*TestCase/Operator/Warn.spvm line 21|);
    }

    # test_test_warn_undef
    {
      my $method_name = 'test_warn_undef';
      TestFile::generate_class_method_call_script($script_file, $class_name, $method_name);
      system("$^X -Mblib $script_file 2> $output_file");
      my $output = TestFile::slurp_binmode($output_file);
      like($output, qr|undef\n  TestCase::Operator::Warn#test_warn_undef at .*TestCase/Operator/Warn.spvm line 27|);
    }

    # test_test_warn_no_operand
    {
      my $method_name = 'test_warn_no_operand';
      TestFile::generate_class_method_call_script($script_file, $class_name, $method_name);
      system("$^X -Mblib $script_file 2> $output_file");
      my $output = TestFile::slurp_binmode($output_file);
      like($output, qr|Warning\n  TestCase::Operator::Warn#test_warn_no_operand at .*TestCase/Operator/Warn.spvm line 33|);
    }
    
    # test_warn_object_type
    {
      my $method_name = 'test_warn_object_type';
      TestFile::generate_class_method_call_script($script_file, $class_name, $method_name);
      system("$^X -Mblib $script_file 2> $output_file");
      my $output = TestFile::slurp_binmode($output_file);
      like($output, qr|^Int\(0x[0-9a-fA-F]+\)\n  TestCase::Operator::Warn#test_warn_object_type at .*TestCase/Operator/Warn.spvm line 39|);
    }
    
    # test_Fn_print_stderr
    {
      my $method_name = 'test_Fn_print_stderr';
      TestFile::generate_class_method_call_script($script_file, $class_name, $method_name);
      system("$^X -Mblib $script_file 2> $output_file");
      my $output = TestFile::slurp_binmode($output_file);
      is($output, 'Hello');
    }
    
    # test_Fn_print_stderr_undef
    {
      my $method_name = 'test_Fn_print_stderr_undef';
      TestFile::generate_class_method_call_script($script_file, $class_name, $method_name);
      system("$^X -Mblib $script_file 2> $output_file");
      my $output = TestFile::slurp_binmode($output_file);
      is($output, '');
    }
    
    # test_Fn_say_stderr
    {
      my $method_name = 'test_Fn_say_stderr';
      TestFile::generate_class_method_call_script($script_file, $class_name, $method_name);
      system("$^X -Mblib $script_file 2> $output_file");
      my $output = TestFile::slurp_binmode($output_file);
      is($output, "Hello\x{0A}");
    }
    
    # test_Fn_say_stderr_undef
    {
      my $method_name = 'test_Fn_say_stderr_undef';
      TestFile::generate_class_method_call_script($script_file, $class_name, $method_name);
      system("$^X -Mblib $script_file 2> $output_file");
      my $output = TestFile::slurp_binmode($output_file);
      is($output, "\x{0A}");
    }
    
    SPVM::TestCase::Operator::Warn->warn_object_address;
    
    SPVM::TestCase::Operator::Warn->warn_ref;
    
    {
      my $method_name = 'print_STDERR';
      TestFile::generate_class_method_call_script($script_file, $class_name, $method_name);
      system("$^X -Mblib $script_file 2> $output_file");
      my $output = TestFile::slurp_binmode($output_file);
      is($output, 'Hello');
    }
    
    {
      my $method_name = 'say_STDERR';
      TestFile::generate_class_method_call_script($script_file, $class_name, $method_name);
      system("$^X -Mblib $script_file 2> $output_file");
      my $output = TestFile::slurp_binmode($output_file);
      is($output, "Hello\x{0A}");
    }
    
    # test_diag
    {
      my $method_name = 'test_diag';
      TestFile::generate_class_method_call_script($script_file, $class_name, $method_name);
      system("$^X -Mblib $script_file 2> $output_file");
      my $output = TestFile::slurp_binmode($output_file);
      like($output, qr|Hello\n  TestCase::Operator::Warn#test_diag at .*TestCase/Operator/Warn.spvm line|);
    }
    
  }
}

# warn_level
{
  # warn_level 0
  {
    my $method_name = 'test_warn_level_zero';
    TestFile::generate_class_method_call_script($script_file, $class_name, $method_name);
    system("$^X -Mblib $script_file 2> $output_file");
    my $output = TestFile::slurp_binmode($output_file);
    like($output, qr|Hello\n  TestCase::Operator::Warn#test_warn_level_zero at .*TestCase/Operator/Warn.spvm line|);
  }
  
  # warn_level -1
  {
    my $method_name = 'test_warn_level_negative';
    TestFile::generate_class_method_call_script($script_file, $class_name, $method_name);
    system("$^X -Mblib $script_file 2> $output_file");
    my $output = TestFile::slurp_binmode($output_file);
    is($output, "");
  }
  
  # warn_level 1
  {
    eval { SPVM::TestCase::Operator::Warn->test_warn_level_positive };
    like($@, qr/Hello/);
  }
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;

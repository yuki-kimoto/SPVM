use lib "t/lib";
use TestAuto;

use strict;
use warnings;
use File::Path 'mkpath';

use Test::More;

use TestUtil;
use SPVM 'TestCase::Operator::Print';

my $test_dir = "$FindBin::Bin";
my $build_dir = "$FindBin::Bin/.spvm_build";

my $test_tmp_dir = "$test_dir/test_files/.tmp";

my $script_file = "$test_tmp_dir/print-script.pl";
my $output_file = "$test_tmp_dir/print-output.txt";

mkpath $test_tmp_dir;

sub write_script_file {
  my ($script_file, $func_call) = @_;
  
  my $pre = <<"EOS";
use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use SPVM 'TestCase::Operator::Print';

EOS

  open my $script_fh, '>', $script_file
    or die "Can't open file $script_file: $!";
  
  my $output_source = "$pre$func_call;";
  
  print $script_fh $output_source;
}

# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

{
  # print
  {
    # test_print
    {
      my $func_call = 'SPVM::TestCase::Operator::Print->print';
      write_script_file($script_file, $func_call);
      system("$^X -Mblib $script_file > $output_file");
      my $output = TestUtil::slurp_binmode($output_file);
      is($output, 'Hello');
    }

    # test_print_newline
    {
      my $func_call = 'SPVM::TestCase::Operator::Print->print_newline';
      write_script_file($script_file, $func_call);
      system("$^X -Mblib $script_file > $output_file");
      my $output = TestUtil::slurp_binmode($output_file);
      is($output, "\x0A");
    }
    
    # test_print_long_lines
    {
      my $func_call = 'SPVM::TestCase::Operator::Print->print_long_lines';
      write_script_file($script_file, $func_call);
      system("$^X -Mblib $script_file > $output_file");
      my $output = TestUtil::slurp_binmode($output_file);
      is($output, "AAAAAAAAAAAAA\x0ABBBBBBBBBBBBBBBBBBB\x0ACCCCCCCCCCCCCCCCCCCCCCCCCCC\x0ADDDDDDDDDDDDDDDDDDDDDDDDD\x0AEEEEEEEEEEEEEEEEEEEEEE\x0AFFFFFFFFFFFFFF\x0A");
    }
    # test_print_empty
    {
      my $func_call = 'SPVM::TestCase::Operator::Print->print_empty';
      write_script_file($script_file, $func_call);
      system("$^X -Mblib $script_file > $output_file");
      my $output = TestUtil::slurp_binmode($output_file);
      is($output, "");
    }
    # test_print_undef
    {
      my $func_call = 'SPVM::TestCase::Operator::Print->print_undef';
      write_script_file($script_file, $func_call);
      system("$^X -Mblib $script_file > $output_file");
      my $output = TestUtil::slurp_binmode($output_file);
      is($output, "");
    }
  }
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;

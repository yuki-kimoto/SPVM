use lib "t/testlib";
use TestAuto;

use strict;
use warnings;
use File::Path 'mkpath';

use Test::More;

use TestFile;
use SPVM 'TestCase::Say';



my $test_tmp_dir = "t/test_files_tmp";

my $script_file = "$test_tmp_dir/say-script.pl";
my $output_file = "$test_tmp_dir/say-output.txt";

mkpath $test_tmp_dir;

sub write_script_file {
  my ($script_file, $func_call) = @_;
  
  my $pre = <<"EOS";
use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use SPVM 'TestCase::Say';



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
  # print
  {
    # test_print
    {
      my $func_call = 'SPVM::TestCase::Say->test_say';
      write_script_file($script_file, $func_call);
      system("$^X -Mblib $script_file > $output_file");
      my $output = slurp_binmode($output_file);
      is($output, "Hello\n");
    }

    # test_print_newline
    {
      my $func_call = 'SPVM::TestCase::Say->test_say_newline';
      write_script_file($script_file, $func_call);
      system("$^X -Mblib $script_file > $output_file");
      my $output = slurp_binmode($output_file);
      # (In Windows/MinGW, __USE_MINGW_ANSI_STDIO is defined, output maybe lf, not crlf)
      is($output, "\x0A\n");
    }
    
    # test_print_long_lines
    {
      my $func_call = 'SPVM::TestCase::Say->test_say_long_lines';
      write_script_file($script_file, $func_call);
      system("$^X -Mblib $script_file > $output_file");
      my $output = slurp_binmode($output_file);
      is($output, "AAAAAAAAAAAAA\x0ABBBBBBBBBBBBBBBBBBB\x0ACCCCCCCCCCCCCCCCCCCCCCCCCCC\x0ADDDDDDDDDDDDDDDDDDDDDDDDD\x0AEEEEEEEEEEEEEEEEEEEEEE\x0AFFFFFFFFFFFFFF\x0A\n");
    }
    # test_print_empty
    {
      my $func_call = 'SPVM::TestCase::Say->test_say_empty';
      write_script_file($script_file, $func_call);
      system("$^X -Mblib $script_file > $output_file");
      my $output = slurp_binmode($output_file);
      is($output, "\n");
    }
    # test_say_undef
    {
      my $func_call = 'SPVM::TestCase::Say->test_say_undef';
      write_script_file($script_file, $func_call);
      system("$^X -Mblib $script_file > $output_file");
      my $output = slurp_binmode($output_file);
      is($output, "\n");
    }
  }
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;

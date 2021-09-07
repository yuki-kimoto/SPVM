use lib "t/lib";
use TestAuto;

use strict;
use warnings;
use FindBin;
use File::Path 'mkpath';

use Test::More 'no_plan';

use TestFile;
use SPVM 'SPVM::TestCase::Warn';



my $test_tmp_dir = "$FindBin::Bin/../test_files_tmp";

my $script_file = "$test_tmp_dir/warn-script.pl";
my $output_file = "$test_tmp_dir/warn-output.txt";

mkpath $test_tmp_dir;

sub write_script_file {
  my ($script_file, $func_call) = @_;
  
  my $pre = <<"EOS";
use lib "t/lib";
use TestAuto;

use strict;
use warnings;
use FindBin;

use SPVM 'SPVM::TestCase::Warn';



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
  # warn
  {
    # test_warn
    {
      my $func_call = 'SPVM::TestCase::Warn->test_warn';
      write_script_file($script_file, $func_call);
      system("$^X -Mblib $script_file 2> $output_file");
      my $output = slurp_binmode($output_file);
      like($output, qr|Hello at .*SPVM/TestCase/Warn.spvm line 4|);
    }

    # test_warn_newline
    {
      my $func_call = 'SPVM::TestCase::Warn->test_warn_newline';
      write_script_file($script_file, $func_call);
      system("$^X -Mblib $script_file 2> $output_file");
      my $output = slurp_binmode($output_file);
      # (In Windows/MinGW, __USE_MINGW_ANSI_STDIO is defined, output maybe lf, not crlf)
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
      like($output, qr|Warning: something's wrong at .*SPVM/TestCase/Warn.spvm line 21|);
    }

    # test_warn_long_lines
    {
      my $func_call = 'SPVM::TestCase::Warn->test_warn_undef';
      write_script_file($script_file, $func_call);
      system("$^X -Mblib $script_file 2> $output_file");
      my $output = slurp_binmode($output_file);
      like($output, qr|Warning: something's wrong at .*SPVM/TestCase/Warn.spvm line 27|);
    }
  }
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

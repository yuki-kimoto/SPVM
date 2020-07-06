use lib "t/lib";
use TestAuto;

use strict;
use warnings;
use FindBin;
use File::Path 'mkpath';

use Test::More 'no_plan';


use SPVM 'SPVM::IO::Stdout';
use SPVM 'TestCase::Lib::SPVM::IO::Stdout';



use TestFile;

my $test_tmp_dir = "$FindBin::Bin/../test_files_tmp";

my $script_file = "$test_tmp_dir/SPVM-IO-Stdout-script.pl";
my $output_file = "$test_tmp_dir/SPVM-IO-Stdout-output.txt";

mkpath $test_tmp_dir;

sub write_script_file {
  my ($script_file, $func_call) = @_;
  
  my $pre = <<"EOS";
use lib "t/lib";
use TestAuto;

use strict;
use warnings;
use FindBin;

use SPVM 'TestCase::Lib::SPVM::IO::Stdout';


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

# print
{
  # print - basic tests
  {
    
    # test_print_newline
    {
      my $func_call = 'TestCase::Lib::SPVM::IO::Stdout->test_print_newline';
      write_script_file($script_file, $func_call);
      system("$^X -Mblib $script_file > $output_file");
      my $output = slurp_binmode($output_file);
      # (In Windows/MinGW, __USE_MINGW_ANSI_STDIO is defined, output maybe lf, not crlf)
      is($output, "\x0A");
    }
    
    # test_print_long_lines
    {
      my $func_call = 'TestCase::Lib::SPVM::IO::Stdout->test_print_long_lines';
      write_script_file($script_file, $func_call);
      system("$^X -Mblib $script_file > $output_file");
      my $output = slurp_binmode($output_file);
      is($output, "AAAAAAAAAAAAA\x0ABBBBBBBBBBBBBBBBBBB\x0ACCCCCCCCCCCCCCCCCCCCCCCCCCC\x0ADDDDDDDDDDDDDDDDDDDDDDDDD\x0AEEEEEEEEEEEEEEEEEEEEEE\x0AFFFFFFFFFFFFFF\x0A");
    }

    # test_print_empty
    {
      my $func_call = 'TestCase::Lib::SPVM::IO::Stdout->test_print_empty';
      write_script_file($script_file, $func_call);
      system("$^X -Mblib $script_file > $output_file");
      my $output = slurp_binmode($output_file);
      is($output, '');
    }
  }
  
  # print - auto flash
  {
    # SPVM::IO::Stdout auto flash default is false
    {
      my $auto_flush_default = SPVM::IO::Stdout->AUTO_FLUSH;
      ok(!$auto_flush_default);
    }
    
    # This is not real tests, but I can't know the way to test buffer
    my $stdout_source = slurp_binmode('blib/lib/SPVM/IO/Stdout.c');
    like($stdout_source, qr|\Qfflush(stdout);//SPVM::IO::Stdout::print|);
    
    # print with set auto flush
    {
      # test_print
      {
        my $func_call = 'SPVM::IO::Stdout->SET_AUTO_FLUSH(1);TestCase::Lib::SPVM::IO::Stdout->test_print';
        write_script_file($script_file, $func_call);
        system("$^X -Mblib $script_file > $output_file");
        my $output = slurp_binmode($output_file);
        is($output, 'Hello');
      }
      
      # test_print_newline
      {
        my $func_call = 'SPVM::IO::Stdout->SET_AUTO_FLUSH(1);TestCase::Lib::SPVM::IO::Stdout->test_print_newline';
        write_script_file($script_file, $func_call);
        system("$^X -Mblib $script_file > $output_file");
        my $output = slurp_binmode($output_file);
        # (In Windows/MinGW, __USE_MINGW_ANSI_STDIO is defined, output maybe lf, not crlf)
        is($output, "\x0A");
      }
      
      # test_print_long_lines
      {
        my $func_call = 'SPVM::IO::Stdout->SET_AUTO_FLUSH(1);TestCase::Lib::SPVM::IO::Stdout->test_print_long_lines';
        write_script_file($script_file, $func_call);
        system("$^X -Mblib $script_file > $output_file");
        my $output = slurp_binmode($output_file);
        is($output, "AAAAAAAAAAAAA\x0ABBBBBBBBBBBBBBBBBBB\x0ACCCCCCCCCCCCCCCCCCCCCCCCCCC\x0ADDDDDDDDDDDDDDDDDDDDDDDDD\x0AEEEEEEEEEEEEEEEEEEEEEE\x0AFFFFFFFFFFFFFF\x0A");
      }
    }
    
    SPVM::IO::Stdout->SET_AUTO_FLUSH(0);
  }

  # print - exception
  {
    # print - exception
    {
      my $func_call = 'TestCase::Lib::SPVM::IO::Stdout->test_print_exeption_undef';
      write_script_file($script_file, $func_call);
      system("$^X -Mblib $script_file > $output_file");
      my $output = slurp_binmode($output_file);
      is($output, 1);
    }
  }
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

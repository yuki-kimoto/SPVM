use lib "t/lib";
use TestAuto;

use strict;
use warnings;
use FindBin;

use Test::More 'no_plan';


use SPVM 'TestCase::Lib::SPVM::IO::Stdout';

use TestFile;

my $script_file = "$FindBin::Bin/../../test_files_tmp/SPVM-IO-Stdout-script.pl";
my $output_file = "$FindBin::Bin/../../test_files_tmp/SPVM-IO-Stdout-output.txt";

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

{
  # print
  {
    my $func_call = 'TestCase::Lib::SPVM::IO::Stdout->test_print';
    write_script_file($script_file, $func_call);
    system("perl -Mblib $script_file > $output_file");
    my $output = slurp_binmode($output_file);
    is($output, 'Hello');
  }

  # set_binmode
  {
    ok(TestCase::Lib::SPVM::IO::Stdout->test_set_binmode);
  }
}


# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

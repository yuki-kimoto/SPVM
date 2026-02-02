use lib "t/testlib";
use TestAuto;

use strict;
use warnings;
use File::Path 'mkpath';

use Test::More;

use TestFile;
use File::Spec;
use SPVM (); # Load SPVM API

my $devnull = File::Spec->devnull;

my $test_dir = $ENV{SPVM_TEST_DIR};
my $test_tmp_dir = "$test_dir/test_files/.tmp";

my $script_file = "$test_tmp_dir/end-block-script.pl";

mkpath $test_tmp_dir;

# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

my $class_name = 'TestCase::Definition::EndBlock';

# END block
{
  # Test the execution order of END blocks
  # SPVM END blocks are executed in reverse order of definition.
  {
    # Actually, just calling a non-existent method will still run END blocks if the class is loaded.
    # But for safety, let's assume we call a class method or just the class itself.
    TestFile::generate_class_method_call_script($script_file, $class_name);
    
    # Capture output. END blocks print to STDOUT in your SPVM code.
    my $output = `$^X -Mblib $script_file`;
    
    # Check the execution order: "END 2" should come before "END 1"
    like($output, qr/END 2\nEND 1\n/, "END blocks are executed in reverse order of definition");
  }
  
  # Test STDERR: Check if die is converted to a warning
  # Capture only STDERR by redirecting STDOUT to $devnull and then STDERR to STDOUT
  {
    # Redirection order: 
    # 1. Redirect STDERR to STDOUT (2>&1)
    # 2. Redirect original STDOUT to $devnull (1>$devnull)
    my $stderr = `$^X -Mblib $script_file 2>&1 1>$devnull`;
    like($stderr, qr/Die in END block/, "die in END block is converted to a warning on STDERR.");
  }
  
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count, "Memory leak check");

done_testing;

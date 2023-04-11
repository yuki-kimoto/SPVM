use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Examples';

use SPVM 'TestCase::ModuleContainsMultiClass';

use Devel::Peek;

# Start objects count
my $start_memory_blocks_count = SPVM::api->get_memory_blocks_count();

{
  # OK if segfault don't occur
  SPVM::TestCase::Examples->new_only_field_object;
  ok(1);
}

# This test case is a class contains multi classes
{
  my $outputs_length = 4;
  my $inputs_length = 3;
  my $weights_mat = SPVM::TestCase::ModuleContainsMultiClass->mat_new_zero($outputs_length, $inputs_length);
}

# SYNOPSIS
{
  # sum.pl
  use strict;
  use warnings;

  use SPVM 'MyMath';

  # Call method
  my $total = SPVM::MyMath->sum([3, 6, 8, 9]);
  is($total, 26);
}

# VERSION
{
  my $spvm_class_file = "blib/lib/SPVM.pm";
  open my $fh, '<', $spvm_class_file
    or die;
  my $spvm_class_content = do { local $/; <$fh> };
  
  like($spvm_class_content, qr|our \$VERSION = '[\d\._]+';|);
}

# All object is freed
my $end_memory_blocks_count = SPVM::api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;

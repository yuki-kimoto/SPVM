use lib "t/lib";
use JITTestAuto;

use strict;
use warnings;
use utf8;

use Test::More 'no_plan';

use SPVM 'TestCase';

# Start objects count
my $start_objects_count = SPVM::get_objects_count();

# .
{
  {
    is("ab", SPVM::TestCase::concat_special_assign()->to_data);
    is("ab", SPVM::TestCase::concat()->to_data);
  }
}

# String
{
  {
    my $values = SPVM::TestCase::string_empty();
    is($values->to_data, "");
  }
  
  {
    my $values = SPVM::TestCase::string_utf8();
    is($values->to_string, "あいうえお");
  }
}

# All object is freed
my $end_objects_count = SPVM::get_objects_count();
is($end_objects_count, $start_objects_count);

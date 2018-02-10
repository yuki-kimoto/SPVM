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
    is("ab", SPVM::TestCase::concat_string_special_assign()->to_data);
    is("ab", SPVM::TestCase::concat_string_string()->to_data);
    is("a3", SPVM::TestCase::concat_string_byte()->to_data);
    is("a3", SPVM::TestCase::concat_string_short()->to_data);
    is("a3", SPVM::TestCase::concat_string_int()->to_data);
    is("a3", SPVM::TestCase::concat_string_long()->to_data);
    is("a3.000000", SPVM::TestCase::concat_string_float()->to_data);
    is("a3.000000", SPVM::TestCase::concat_string_double()->to_data);
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

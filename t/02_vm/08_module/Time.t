use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::Time';



# Start objects count
my $start_memory_blocks_count = SPVM::api->get_memory_blocks_count();

# Time::Info
{
  my $time = SPVM::TestCase::Module::Time->time_info;
}

# time
{
  my $time = SPVM::TestCase::Module::Time->time;
  my $perl_time = time;
  if ($time > $perl_time - 2 && $time < $perl_time + 2) {
    pass();
  }
  else {
    fail();
  }
}

# localtime
{
  my $time = time;
  my @perl_localtime = localtime($time);
  
  my $time_info = SPVM::TestCase::Module::Time->localtime($time);
  
  is($perl_localtime[0], $time_info->tm_sec);
  is($perl_localtime[1], $time_info->tm_min);
  is($perl_localtime[2], $time_info->tm_hour);
  is($perl_localtime[3], $time_info->tm_mday);
  is($perl_localtime[4], $time_info->tm_mon);
  is($perl_localtime[5], $time_info->tm_year);
  is($perl_localtime[6], $time_info->tm_wday);
  is($perl_localtime[7], $time_info->tm_yday);
  is($perl_localtime[8], $time_info->tm_isdst);
}

# gmtime
{
  my $time = time;
  my @perl_gmtime = gmtime($time);
  
  my $time_info = SPVM::TestCase::Module::Time->gmtime($time);
  
  is($perl_gmtime[0], $time_info->tm_sec);
  is($perl_gmtime[1], $time_info->tm_min);
  is($perl_gmtime[2], $time_info->tm_hour);
  is($perl_gmtime[3], $time_info->tm_mday);
  is($perl_gmtime[4], $time_info->tm_mon);
  is($perl_gmtime[5], $time_info->tm_year);
  is($perl_gmtime[6], $time_info->tm_wday);
  is($perl_gmtime[7], $time_info->tm_yday);
  is($perl_gmtime[8], $time_info->tm_isdst);
}

# All object is freed
my $end_memory_blocks_count = SPVM::api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;

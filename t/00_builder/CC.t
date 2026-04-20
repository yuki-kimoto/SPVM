use strict;
use warnings;

use Test::More;

use SPVM::Builder::CC;
use SPVM::Builder::Config;

# detect_quiet
{
  # default - 0
  {
    my $config = SPVM::Builder::Config->new;
    my $cc = SPVM::Builder::CC->new;
    
    my $quiet = $cc->detect_quiet($config);
    is($quiet, 0);
  }

  # $cc->quiet
  {
    my $config = SPVM::Builder::Config->new;
    my $cc = SPVM::Builder::CC->new;
    
    {
      $cc->quiet(0);
      my $quiet = $cc->detect_quiet($config);
      is($quiet, 0);
    }
    
    {
      $cc->quiet(1);
      my $quiet = $cc->detect_quiet($config);
      is($quiet, 1);
    }
  }

  # $config->quiet
  {
    my $config = SPVM::Builder::Config->new;
    my $cc = SPVM::Builder::CC->new;
    
    {
      $config->quiet(0);
      my $quiet = $cc->detect_quiet($config);
      is($quiet, 0);
    }
    
    {
      $config->quiet(1);
      my $quiet = $cc->detect_quiet($config);
      is($quiet, 1);
    }
  }
  
  # order
  {
    {
      my $config = SPVM::Builder::Config->new( is_jit => 1);
      my $cc = SPVM::Builder::CC->new;
      
      $cc->quiet(0);
      $config->quiet(1);
      
      my $quiet = $cc->detect_quiet($config);
      is($quiet, 0);
    }
    
    {
      my $config = SPVM::Builder::Config->new( is_jit => 1);
      my $cc = SPVM::Builder::CC->new;
      
      $config->quiet(0);
      
      my $quiet = $cc->detect_quiet($config);
      is($quiet, 0);
    }
  }
}

done_testing;

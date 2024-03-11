use strict;
use warnings;

use Test::More;

use SPVM::Builder::CC;
use SPVM::Builder::Config;

# detect_quiet
{
  # default - 0
  {
    my $config = SPVM::Builder::Config->new(file_optional => 1);
    my $cc = SPVM::Builder::CC->new;
    
    my $quiet = $cc->detect_quiet($config);
    is($quiet, 0);
  }

  # $cc->debug - 0
  {
    my $config = SPVM::Builder::Config->new(file_optional => 1);
    my $cc = SPVM::Builder::CC->new;
    $cc->debug(1);
    
    my $quiet = $cc->detect_quiet($config);
    is($quiet, 0);
  }

  # $cc->quiet
  {
    my $config = SPVM::Builder::Config->new(file_optional => 1);
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
    my $config = SPVM::Builder::Config->new(file_optional => 1);
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
      my $config = SPVM::Builder::Config->new(file_optional => 1, is_jit => 1);
      my $cc = SPVM::Builder::CC->new;
      
      $cc->debug(1);
      $cc->quiet(1);
      $config->quiet(1);
      
      my $quiet = $cc->detect_quiet($config);
      is($quiet, 0);
    }
    
    {
      my $config = SPVM::Builder::Config->new(file_optional => 1, is_jit => 1);
      my $cc = SPVM::Builder::CC->new;
      
      $cc->quiet(0);
      $config->quiet(1);
      
      my $quiet = $cc->detect_quiet($config);
      is($quiet, 0);
    }
    
    {
      my $config = SPVM::Builder::Config->new(file_optional => 1, is_jit => 1);
      my $cc = SPVM::Builder::CC->new;
      
      $config->quiet(0);
      
      my $quiet = $cc->detect_quiet($config);
      is($quiet, 0);
    }
  }
}

# detect_force
{
  # default - 0
  {
    my $config = SPVM::Builder::Config->new(file_optional => 1);
    my $cc = SPVM::Builder::CC->new;
    
    my $force = $cc->detect_force($config);
    is($force, 0);
  }

  # $cc->force
  {
    my $config = SPVM::Builder::Config->new(file_optional => 1);
    my $cc = SPVM::Builder::CC->new;
    
    {
      $cc->force(0);
      my $force = $cc->detect_force($config);
      is($force, 0);
    }
    
    {
      $cc->force(1);
      my $force = $cc->detect_force($config);
      is($force, 1);
    }
  }

  # $config->force
  {
    my $config = SPVM::Builder::Config->new(file_optional => 1);
    my $cc = SPVM::Builder::CC->new;
    
    {
      $config->force(0);
      my $force = $cc->detect_force($config);
      is($force, 0);
    }
    
    {
      $config->force(1);
      my $force = $cc->detect_force($config);
      is($force, 1);
    }
  }
  
  # order
  {
    {
      my $config = SPVM::Builder::Config->new(file_optional => 1);
      my $cc = SPVM::Builder::CC->new;
      
      $cc->force(0);
      $config->force(1);
      
      my $force = $cc->detect_force($config);
      is($force, 0);
    }

    {
      my $config = SPVM::Builder::Config->new(file_optional => 1);
      my $cc = SPVM::Builder::CC->new;
      
      $config->force(0);
      
      my $force = $cc->detect_force($config);
      is($force, 0);
    }
  }
}

done_testing;

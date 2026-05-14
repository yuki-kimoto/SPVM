use strict;
use warnings;

use Test::More;

use SPVM::Builder::CC;
use SPVM::Builder::Config;
use SPVM::Builder;

# detect_quiet
{
  # default - 0
  {
    my $builder = SPVM::Builder->new;
    my $config = SPVM::Builder::Config->new;
    my $cc = SPVM::Builder::CC->new(builder => $builder);
    
    my $quiet = $builder->detect_quiet($config);
    is($quiet, 0);
  }

  # $cc->builder->quiet
  {
    my $builder = SPVM::Builder->new;
    my $config = SPVM::Builder::Config->new;
    my $cc = SPVM::Builder::CC->new(builder => $builder);
    
    {
      $cc->builder->quiet(0);
      my $quiet = $builder->detect_quiet($config);
      is($quiet, 0);
    }
    
    {
      $cc->builder->quiet(1);
      my $quiet = $builder->detect_quiet($config);
      is($quiet, 1);
    }
  }

  # $config->quiet
  {
    my $builder = SPVM::Builder->new;
    my $config = SPVM::Builder::Config->new;
    my $cc = SPVM::Builder::CC->new(builder => $builder);
    
    {
      $config->quiet(0);
      my $quiet = $builder->detect_quiet($config);
      is($quiet, 0);
    }
    
    {
      $config->quiet(1);
      my $quiet = $builder->detect_quiet($config);
      is($quiet, 1);
    }
  }
  
  # order
  {
    {
      my $builder = SPVM::Builder->new;
      my $config = SPVM::Builder::Config->new(is_jit => 1);
      my $cc = SPVM::Builder::CC->new(builder => $builder);
      
      $cc->builder->quiet(0);
      $config->quiet(1);
      
      my $quiet = $builder->detect_quiet($config);
      is($quiet, 0);
    }
    
    {
      my $builder = SPVM::Builder->new;
      my $config = SPVM::Builder::Config->new(is_jit => 1);
      my $cc = SPVM::Builder::CC->new(builder => $builder);
      
      $config->quiet(0);
      
      my $quiet = $builder->detect_quiet($config);
      is($quiet, 0);
    }
  }
}

done_testing;

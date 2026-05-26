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
      my $builder = SPVM::Builder->new(is_jit => 1);
      my $config = SPVM::Builder::Config->new;
      my $cc = SPVM::Builder::CC->new(builder => $builder);
      
      $cc->builder->quiet(0);
      $config->quiet(1);
      
      my $quiet = $builder->detect_quiet($config);
      is($quiet, 0);
    }
    
    {
      my $builder = SPVM::Builder->new(is_jit => 1);
      my $config = SPVM::Builder::Config->new;
      my $cc = SPVM::Builder::CC->new(builder => $builder);
      
      $config->quiet(0);
      
      my $quiet = $builder->detect_quiet($config);
      is($quiet, 0);
    }
  }
}

subtest 'Check spvm_native.h' => sub {
  my $header_path = 'lib/SPVM/Builder/include/spvm_native.h';

  ok(-f $header_path);

  open my $fh, '<', $header_path or die "Could not open $header_path: $!";
  my $content = do { local $/; <$fh> };
  close $fh;

  my %allowed_headers = map { $_ => 1 } qw(stdint.h stdio.h string.h stdlib.h inttypes.h assert.h);

  my @includes = $content =~ /#include\s*[<"]([^>"]+)[>"]/g;

  is(scalar @includes, 6);

  foreach my $include (@includes) {
    ok($allowed_headers{$include});
  }
};

done_testing;

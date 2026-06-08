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

subtest 'PDB file' => sub {
  {
    my $Fn_dll_file = 'blib/lib/SPVM/Fn.dll';
    ok(-f $Fn_dll_file);
    my $has_pdb_section = &has_pdb_section($Fn_dll_file);
    
    if ($has_pdb_section) {
      ok(-f 'blib/lib/SPVM/Fn.pdb');
    }
    else {
      diag "[Test Skip]No pdf file.";
    }
  }
  
  {
    my $Fn_dll_file = 'blib/lib/SPVM/Fn.precompile.dll';
    ok(-f $Fn_dll_file);
    my $has_pdb_section = &has_pdb_section($Fn_dll_file);
    
    if ($has_pdb_section) {
      ok(-f 'blib/lib/SPVM/Fn.precompile.pdb');
    }
    else {
      diag "[Test Skip]No pdf file.";
    }
  }
  
};

done_testing;

sub has_pdb_section {
  my ($file) = @_;

  # Check file existence and die if missing
  die "File '$file' not found" unless -f $file;

  # Extract filename without extension
  my ($base_name) = $file =~ m|([^/\\.]+)\.[^/\\.]+$|;
  die "Could not extract base name from '$file'" unless $base_name;

  # Open as binary
  open my $fh, '<:raw', $file or die "Could not open '$file': $!";
  
  # Read full content
  undef $/;
  my $content = <$fh>;
  close $fh;

  # Search for <base_name>.pdb
  return $content =~ /\Q$base_name\E\.pdb\b/i ? 1 : 0;
}
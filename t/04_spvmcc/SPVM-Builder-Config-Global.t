use strict;
use warnings;
use utf8;
use Test::More;
use SPVM::Builder::Config;
use SPVM::Builder::Config::Global;
use Carp 'confess';

# Helper to create a mock config object for internal testing
sub create_mock_config {
  return bless {
    lang    => 'c',
    dialect => 'c11',
    ccflags => ['-Wall'],
    cc      => 'gcc',
    empty   => undef,
    str     => 'base',
  }, 'SPVM::Builder::Config';
}

# --- Condition Matching logic ---
subtest 'Condition Matching' => sub {
  my $config = create_mock_config();

  # Exact string match
  my $called = 0;
  SPVM::Builder::Config::Global::_match_apply($config, { lang => 'c' }, sub { $called = 1 });
  ok($called, 'Exact string match');

  # Regex match
  $called = 0;
  SPVM::Builder::Config::Global::_match_apply($config, { dialect => qr/^c\d+$/ }, sub { $called = 1 });
  ok($called, 'Regex match');

  # Match undef field (Both sides undef)
  $called = 0;
  SPVM::Builder::Config::Global::_match_apply($config, { unknown => undef }, sub { $called = 1 });
  ok($called, 'Undef vs Undef');

  # Mismatch (scalar)
  $called = 0;
  SPVM::Builder::Config::Global::_match_apply($config, { lang => 'cpp' }, sub { $called = 1 });
  ok(!$called, 'Mismatch string');

  # Mismatch (defined condition vs undef config)
  $called = 0;
  SPVM::Builder::Config::Global::_match_apply($config, { empty => 'val' }, sub { $called = 1 });
  ok(!$called, 'Value vs Undef mismatch');
};

# --- Append Logic (+key syntax) ---
subtest 'Append Logic (+key)' => sub {
  
  # Undef + ARRAY -> ARRAY (Initial assignment)
  {
      my $config = create_mock_config();
      SPVM::Builder::Config::Global::_match_apply($config, undef, { '+new_field' => ['-g'] });
      is_deeply($config->{new_field}, ['-g'], 'Undef + ARRAY');
  }

  # Scalar + Scalar -> String concatenation
  {
      my $config = create_mock_config();
      SPVM::Builder::Config::Global::_match_apply($config, undef, { '+str' => '_ext' });
      is($config->{str}, 'base_ext', 'Scalar + Scalar concatenation');
  }

  # Scalar + ARRAY -> [Scalar, @ARRAY] (Promotion to ARRAY)
  {
      my $config = create_mock_config();
      SPVM::Builder::Config::Global::_match_apply($config, undef, { '+str' => ['opt1', 'opt2'] });
      is_deeply($config->{str}, ['base', 'opt1', 'opt2'], 'Scalar + ARRAY promotion');
  }

  # ARRAY + Scalar -> push(@ARRAY, Scalar)
  {
      my $config = create_mock_config();
      SPVM::Builder::Config::Global::_match_apply($config, undef, { '+ccflags' => '-O3' });
      is_deeply($config->{ccflags}, ['-Wall', '-O3'], 'ARRAY + Scalar push');
  }

  # ARRAY + ARRAY -> push(@ARRAY, @ARRAY) (Merge)
  {
      my $config = create_mock_config();
      SPVM::Builder::Config::Global::_match_apply($config, undef, { '+ccflags' => ['-O2', '-g'] });
      is_deeply($config->{ccflags}, ['-Wall', '-O2', '-g'], 'ARRAY + ARRAY merge');
  }
};

# --- Callback execution ---
subtest 'Execution Modes' => sub {
  my $config = create_mock_config();
  
  # Callback mode
  my $passed_config;
  SPVM::Builder::Config::Global::_match_apply($config, undef, sub { $passed_config = $_[0] });
  is($passed_config, $config, 'Callback receives config object');

  # Static override (No + prefix)
  SPVM::Builder::Config::Global::_match_apply($config, undef, { lang => 'cpp' });
  is($config->{lang}, 'cpp', 'Standard override works');
};

# --- Error cases ---
subtest 'Error Handling' => sub {
  my $config = create_mock_config();
  $config->{bad_field} = { hash => 1 }; # HASH ref is not supported

  eval {
      SPVM::Builder::Config::Global::_match_apply($config, undef, { '+bad_field' => 'str' });
  };
  ok($@, 'Confess on unsupported type combination');
};

# --- Array Sensitivity (Match element in ARRAY) ---
subtest 'Array Sensitivity (Config side is ARRAY)' => sub {
  my $config = create_mock_config();
  # Mock config current state: ccflags => ['-Wall']

  # Match element in ARRAY (String)
  my $called = 0;
  SPVM::Builder::Config::Global::_match_apply($config, { ccflags => '-Wall' }, sub { $called = 1 });
  ok($called, 'Match string element in ARRAY');

  # Match element in ARRAY (Regex)
  $called = 0;
  SPVM::Builder::Config::Global::_match_apply($config, { ccflags => qr/^-W/ }, sub { $called = 1 });
  ok($called, 'Match regex against elements in ARRAY');

  # Mismatch element in ARRAY
  $called = 0;
  SPVM::Builder::Config::Global::_match_apply($config, { ccflags => '-O3' }, sub { $called = 1 });
  ok(!$called, 'Mismatch string element in ARRAY');

  # Match undef in ARRAY
  $called = 0;
  my $config_with_undef = bless { tags => ['stable', undef, 'v1'] }, 'SPVM::Builder::Config';
  SPVM::Builder::Config::Global::_match_apply($config_with_undef, { tags => undef }, sub { $called = 1 });
  ok($called, 'Match undef element in ARRAY');

  # Mismatch regex against all elements
  $called = 0;
  SPVM::Builder::Config::Global::_match_apply($config, { ccflags => qr/^-O/ }, sub { $called = 1 });
  ok(!$called, 'Mismatch regex against all elements in ARRAY');
};

# --- Negative Matching (!prefix) ---
subtest 'Negative Matching (!prefix)' => sub {
  my $config = create_mock_config();
  # Mock config: lang => 'c', ccflags => ['-Wall']

  # Negative string match (Success: 'cpp' is NOT 'c')
  my $called = 0;
  SPVM::Builder::Config::Global::_match_apply($config, { '!lang' => 'cpp' }, sub { $called = 1 });
  ok($called, 'Negative string match (match because value is different)');

  # Negative string match (Failure: 'c' IS 'c')
  $called = 0;
  SPVM::Builder::Config::Global::_match_apply($config, { '!lang' => 'c' }, sub { $called = 1 });
  ok(!$called, 'Negative string match (mismatch because value is same)');

  # Negative Array Sensitivity (Success: '-O3' is NOT in ['-Wall'])
  $called = 0;
  SPVM::Builder::Config::Global::_match_apply($config, { '!ccflags' => '-O3' }, sub { $called = 1 });
  ok($called, 'Negative array match (match because element is not in array)');

  # Negative Array Sensitivity (Failure: '-Wall' IS in ['-Wall'])
  $called = 0;
  SPVM::Builder::Config::Global::_match_apply($config, { '!ccflags' => '-Wall' }, sub { $called = 1 });
  ok(!$called, 'Negative array match (mismatch because element is in array)');

  # Negative Regex match (Success: 'base' does not match /x/)
  $called = 0;
  SPVM::Builder::Config::Global::_match_apply($config, { '!str' => qr/x/ }, sub { $called = 1 });
  ok($called, 'Negative regex match');

  # Negative Undef match (Success: 'lang' is defined, so it matches '!lang => undef')
  $called = 0;
  SPVM::Builder::Config::Global::_match_apply($config, { '!lang' => undef }, sub { $called = 1 });
  ok($called, 'Negative undef match (match because field is defined)');
};

# --- Config Global Explicit and Undef Matching ---
subtest 'Config Global Explicit and Undef Matching' => sub {
  
  # Match global field explicitly
  {
    my $global = bless { build_type => 'debug' }, 'SPVM::Builder::Config::Global';
    my $config = { lang => 'c', config_global => $global };
    
    my $called = 0;
    SPVM::Builder::Config::Global::_match_apply($config, { global => { build_type => 'debug' } }, sub { $called = 1 });
    ok($called, 'Explicit Global: matches value in config_global');
    
    $called = 0;
    SPVM::Builder::Config::Global::_match_apply($config, { global => { build_type => 'release' } }, sub { $called = 1 });
    ok(!$called, 'Explicit Global: mismatch correctly');
  }

  # Match both local and global at the same time
  {
    my $global = bless { cc => 'gcc' }, 'SPVM::Builder::Config::Global';
    my $config = { lang => 'c', config_global => $global };
    
    my $called = 0;
    SPVM::Builder::Config::Global::_match_apply($config, { lang => 'c', global => { cc => 'gcc' } }, sub { $called = 1 });
    ok($called, 'Hybrid: matches both local and global fields');
  }

  # Match undef vs undef (The "Deep Sea" case)
  {
    my $global = bless { opt => undef }, 'SPVM::Builder::Config::Global';
    my $config = { config_global => $global };
    
    # 1. Local is missing (undef) and condition is undef
    my $called = 0;
    SPVM::Builder::Config::Global::_match_apply($config, { unknown => undef }, sub { $called = 1 });
    ok($called, 'Undef Match: matches when local field is missing and condition is undef');

    # 2. Global field is explicitly undef
    $called = 0;
    SPVM::Builder::Config::Global::_match_apply($config, { global => { opt => undef } }, sub { $called = 1 });
    ok($called, 'Undef Match: matches when global field is explicitly undef');
  }

  # Negative match with global
  {
    my $global = bless { build_type => 'debug' }, 'SPVM::Builder::Config::Global';
    my $config = { config_global => $global };
    
    my $called = 0;
    SPVM::Builder::Config::Global::_match_apply($config, { global => { '!build_type' => 'release' } }, sub { $called = 1 });
    ok($called, 'Negative Global: matches because build_type is not release');
  }
};

done_testing;
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
    like($@, qr/not supported for the combination of HASH/, 'Confess on unsupported type combination');
};

done_testing;
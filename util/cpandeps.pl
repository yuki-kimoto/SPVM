#!/usr/bin/env perl
use strict;
use warnings;
use utf8;
use HTTP::Tiny;
use JSON::PP;
use Getopt::Long;

# Get options
my $verbose = 0;
GetOptions("v|verbose" => \$verbose);

my %visited;
my $json = JSON::PP->new->utf8;
my $http = HTTP::Tiny->new(timeout => 10);

sub get_dependencies_recursive {
    my ($name, $level) = @_;
    $level //= 0;

    # Skip if already visited
    return if $visited{$name}++;

    my $indent = "  " x $level;

    # Access via HTTP to avoid SSL issues
    # Find distribution name from module endpoint
    my $url = "http://fastapi.metacpan.org/v1/module/$name";
    my $res = $http->get($url);

    unless ($res->{success}) {
        # Try as release name if module not found
        fetch_from_release($name, $name, $level);
        return;
    }

    my $mod_data = eval { $json->decode($res->{content}) };
    return if $@ || !$mod_data;

    my $dist = $mod_data->{distribution};
    fetch_from_release($name, $dist, $level);
}

sub fetch_from_release {
    my ($mod_name, $dist, $level) = @_;
    my $indent = "  " x $level;

    my $url = "http://fastapi.metacpan.org/v1/release/$dist";
    my $res = $http->get($url);
    return unless $res->{success};

    my $rel_data = eval { $json->decode($res->{content}) };
    return if $@ || !$rel_data;

    # Show info to STDERR only if verbose
    if ($verbose) {
        print STDERR "${indent}- $mod_name (Dist: $dist)\n";
    }

    my $deps = $rel_data->{dependency} || [];
    foreach my $dep (@$deps) {
        # Follow runtime requires only
        if ($dep->{phase} eq 'runtime' && $dep->{relationship} eq 'requires') {
            my $next_mod = $dep->{module};
            
            # Skip perl and visited modules
            next if !$next_mod || $next_mod eq 'perl';
            
            # Recurse
            get_dependencies_recursive($next_mod, $level + 1);
        }
    }
}

my $target = shift or die "Usage: $0 [-v] Module::Name\n";

# Show header to STDERR if verbose
print STDERR "--- Analyzing dependencies for $target ---\n" if $verbose;

get_dependencies_recursive($target);

# Show footer to STDERR if verbose
print STDERR "--- Done ---\n" if $verbose;

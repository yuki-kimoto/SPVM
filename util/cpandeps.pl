#!/usr/bin/env perl
use strict;
use warnings;
use utf8;
use HTTP::Tiny;
use JSON::PP;

my %visited;
my $json = JSON::PP->new->utf8;
my $http = HTTP::Tiny->new(timeout => 10);

sub get_dependencies_recursive {
    my ($name, $level) = @_;
    $level //= 0;

    # すでに見たモジュールはスキップ（無限ループ防止）
    return if $visited{$name}++;

    my $indent = "  " x $level;

    # HTTPでアクセス（SSL依存を排除）
    # moduleエンドポイントで配布物(dist)名を特定する
    my $url = "http://fastapi.metacpan.org/v1/module/$name";
    my $res = $http->get($url);

    unless ($res->{success}) {
        # モジュール名で見つからない場合はリリース名として試行
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

    # 自身の情報を表示
    print "${indent}- $mod_name (Dist: $dist)\n";

    my $deps = $rel_data->{dependency} || [];
    foreach my $dep (@$deps) {
        # runtime かつ requires だけを追う
        if ($dep->{phase} eq 'runtime' && $dep->{relationship} eq 'requires') {
            my $next_mod = $dep->{module};
            
            # perl自身や、すでに見たものは飛ばす
            next if !$next_mod || $next_mod eq 'perl';
            
            # 再帰呼び出し
            get_dependencies_recursive($next_mod, $level + 1);
        }
    }
}

my $target = shift or die "Usage: $0 Module::Name\n";
print "--- Analyzing dependencies for $target ---\n";
get_dependencies_recursive($target);
print "--- Done ---\n";

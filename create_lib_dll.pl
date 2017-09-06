use strict;
use warnings;
use ExtUtils::CBuilder;

use File::Copy 'move';
use File::Path 'mkpath';

my $cbuilder = ExtUtils::CBuilder->new(config => {optimize => '-O3'});

my $obj_file = $cbuilder->compile(
  source => 'spvm_lib_std.c',
  include_dirs => ['lib/SPVM']
);
my $lib_file = $cbuilder->link(objects => $obj_file);

mkpath 'blib/arch/auto/SPVM/std';

my $lib_file_blib = 'blib/arch/auto/SPVM/std/std.so';
move($lib_file, $lib_file_blib)
  or die "Can't move $lib_file to $lib_file_blib";

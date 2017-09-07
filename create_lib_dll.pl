use strict;
use warnings;
use ExtUtils::CBuilder;
use Config;

use File::Copy 'move';
use File::Path 'mkpath';

my $cbuilder = ExtUtils::CBuilder->new(config => {optimize => '-O3'});

my @libs = ('std', 'Math');

my $dlext = $Config{dlext};

for my $lib (@libs) {
  my $obj_file = $cbuilder->compile(
    source => "spvm_lib/spvm_lib_${lib}.c",
    include_dirs => ['lib/SPVM']
  );
  my $lib_file = $cbuilder->link(objects => $obj_file, module_name => "SPVM::$lib");

  mkpath "blib/arch/auto/SPVM/${lib}";

  my $lib_file_blib = "blib/arch/auto/SPVM/${lib}/${lib}.$dlext";
  move($lib_file, $lib_file_blib)
    or die "Can't move $lib_file to $lib_file_blib";
}

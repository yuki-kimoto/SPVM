use strict;
use warnings;
use ExtUtils::CBuilder;
use Config;

use File::Copy 'move';
use File::Path 'mkpath';

use FindBin;
use lib "$FindBin::Bin/lib";
use SPVM::Util;

my $cbuilder = ExtUtils::CBuilder->new(config => {optimize => '-O3'});

my @libs = ('std', 'Math');

my $dlext = $Config{dlext};

my $func_list = {
  std => SPVM::Util::create_native_func_names('SPVM::std'),
  Math => SPVM::Util::create_native_func_names('SPVM::Math')
};

for my $lib (@libs) {
  my $obj_file = $cbuilder->compile(
    source => "spvm_lib/spvm_lib_${lib}.c",
    include_dirs => ['lib/SPVM']
  );
  my $lib_file = $cbuilder->link(
    objects => $obj_file,
    module_name => "SPVM::$lib",
    dl_func_list => $func_list->{$lib}
  );

  mkpath "blib/arch/auto/SPVM/${lib}";

  my $lib_file_blib = "blib/arch/auto/SPVM/${lib}/${lib}.$dlext";
  move($lib_file, $lib_file_blib)
    or die "Can't move $lib_file to $lib_file_blib";
}

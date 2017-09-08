use strict;
use warnings;
use ExtUtils::CBuilder;
use Config;

use File::Copy 'move';
use File::Path 'mkpath';

my $cbuilder = ExtUtils::CBuilder->new(config => {optimize => '-O3'});

my @libs = ('std', 'Math');

my $dlext = $Config{dlext};

my $func_list = {
  std => [qw(
    boot_SPVM__std
    SPVM__std__println_byte
    SPVM__std__println_short
    SPVM__std__println_int
    SPVM__std__println_long
    SPVM__std__println_float
    SPVM__std__println_double
    SPVM__std__println

    SPVM__std__print_byte
    SPVM__std__print_short
    SPVM__std__print_int
    SPVM__std__print_long
    SPVM__std__print_float
    SPVM__std__print_double
    
    SPVM__std__sum_int
    SPVM__std__test1
    SPVM__std__test2
  )],
  Math => [qw(
    boot_SPVM__Math
    SPVM__Math__sin
  )]
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

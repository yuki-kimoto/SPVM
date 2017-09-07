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
    println_byte
    println_short
    println_int
    println_long
    println_float
    println_double
    println

    print_byte
    print_short
    print_int
    print_long
    print_float
    print_double
    
    sum_int
    test1
    test2
  )],
  Math => [
    'sin'
  ]
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

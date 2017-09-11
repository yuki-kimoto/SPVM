use strict;
use warnings;
use ExtUtils::CBuilder;
use Config;

use File::Copy 'move';
use File::Path 'mkpath';
use File::Basename 'dirname', 'basename';

use FindBin;
use lib "$FindBin::Bin/lib";
use SPVM::Util;

my $cbuilder = ExtUtils::CBuilder->new(config => {optimize => '-O3'});

my @modules = ('SPVM::std', 'SPVM::Math');

my $dlext = $Config{dlext};

for my $module (@modules) {
  my $module_base_name = $module;
  $module_base_name =~ s/^.+:://;
  
  my $src_dir = $module;
  $src_dir =~ s/::/\//g;
  
  my $src_file = "$src_dir/$module_base_name.c";
  
  my $obj_file = $cbuilder->compile(
    source => "lib/$src_file",
    include_dirs => ['lib/SPVM']
  );
  
  my $native_func_names = SPVM::Util::create_native_func_names($module);
  my $lib_file = $cbuilder->link(
    objects => $obj_file,
    module_name => $module,
    dl_func_list => $native_func_names
  );
  
  mkpath "blib/arch/auto/$src_dir";
  
  my $lib_file_blib = "blib/arch/auto/$src_dir/${module_base_name}.$dlext";
  unlink $obj_file;
  move($lib_file, $lib_file_blib)
    or die "Can't move $lib_file to $lib_file_blib";
}

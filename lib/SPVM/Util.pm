package SPVM::Util;

use strict;
use warnings;
use Carp 'croak';

use ExtUtils::CBuilder;
use Config;

use File::Copy 'move';
use File::Path 'mkpath';
use File::Basename 'dirname', 'basename';

sub build_shared_lib {
  my $module = shift;
  
  my $cbuilder = ExtUtils::CBuilder->new(config => {optimize => '-O3'});
  
  my $dlext = $Config{dlext};
  
  my $module_base_name = $module;
  $module_base_name =~ s/^.+:://;
  
  my $src_dir = $module;
  $src_dir =~ s/::/\//g;
  $src_dir .= '.native';
  
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

sub create_native_func_names {
  my $module = shift;
  
  my $module_file = $module;
  $module_file =~ s/:/\//g;
  $module_file = "lib/$module_file.spvm";
  
  open my $module_fh, '<', $module_file
    or croak "Can't open $module_file: $!";
  
  my $native_func_names = [];
  
  my $src = do { local $/; <$module_fh> };
  
  while ($src =~ /sub\s+([^\s]+)\s*\((?:[^\)]*?)\)\s*\:\s*([^\{;]+);/g) {
    my $sub_name = $1;
    my $descripter_type = $2;
    if ($descripter_type =~ /\bnative\b/) {
      my $native_func_name = "${module}::$sub_name";
      $native_func_name =~ s/:/_/g;
      
      push @$native_func_names, $native_func_name;
    }
  }
  
  return $native_func_names;
}

1;

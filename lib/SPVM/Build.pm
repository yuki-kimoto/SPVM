package SPVM::Build;

use strict;
use warnings;
use Carp 'croak';

use ExtUtils::CBuilder;
use Config;

use File::Copy 'move';
use File::Path 'mkpath';
use File::Basename 'dirname', 'basename';
use File::Temp 'tempdir';

sub build_shared_lib {
  my %opt = @_;
  
  # Module name
  my $module_name = $opt{module_name};
  
  # Module directory
  my $module_dir = $opt{module_dir};
  
  my $module_base_name = $module_name;
  $module_base_name =~ s/^.+:://;
  
  my $src_dir = $module_name;
  $src_dir =~ s/::/\//g;
  $src_dir .= '.native';
  
  # Correct source files
  my $src_files = [];
  my @valid_exts = ('c', 'C', 'cpp', 'i', 's', 'cxx', 'cc');
  for my $src_file (glob "$module_dir/$src_dir/*") {
    if (grep { $src_file =~ /\.$_$/ } @valid_exts) {
      push @$src_files, $src_file;
    }
  }
  
  # Compile source files
  my $cbuilder = ExtUtils::CBuilder->new(config => {optimize => '-O3'});
  my $object_files = [];
  for my $src_file (@$src_files) {
    # Object file
    my $temp_dir = tempdir;
    my $object_file = $module_name;
    $object_file =~ s/:/_/g;
    $object_file = "$temp_dir/$object_file.o";
    
    # Compile source file
    $cbuilder->compile(
      source => $src_file,
      object_file => $object_file,
      include_dirs => ['lib/SPVM']
    );
    push @$object_files, $object_file;
  }
  
  # Link
  my $dlext = $Config{dlext};
  my $native_func_names = SPVM::Build::create_native_func_names($module_name);
  my $lib_file = $cbuilder->link(
    objects => $object_files,
    module_name => $module_name,
    dl_func_list => $native_func_names
  );
  
  mkpath "blib/arch/auto/$src_dir";
  
  my $lib_file_blib = "blib/arch/auto/$src_dir/${module_base_name}.$dlext";
  move($lib_file, $lib_file_blib)
    or die "Can't move $lib_file to $lib_file_blib";
  
  return $lib_file;
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

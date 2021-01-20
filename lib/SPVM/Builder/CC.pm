package SPVM::Builder::CC;

use strict;
use warnings;
use Carp 'confess';

use SPVM::Builder::Util;
use SPVM::Builder::Config;

use ExtUtils::CBuilder;
use File::Copy 'copy', 'move';
use File::Path 'mkpath';
use DynaLoader;
use Config;
use File::Find 'find';

use File::Basename 'dirname', 'basename';

sub new {
  my $class = shift;
  
  my $self = {@_};
  
  return bless $self, $class;
}

sub category { shift->{category} }

sub builder { shift->{builder} }

sub build {
  my ($self, $package_name, $opt) = @_;
  
  my $category = $self->{category};
  my $sub_names;
  if ($category eq 'native') {
    $sub_names = $self->builder->get_native_sub_names($package_name)
  }
  elsif ($category eq 'precompile') {
    $sub_names = $self->builder->get_precompile_sub_names($package_name)
  }
  
  if (@$sub_names) {
    # Shared library is already installed in distribution directory
    my $dll_file = $self->get_dll_file_dist($package_name);
    
    # Try runtime compile if shared objectrary is not found
    unless (-f $dll_file) {
      if ($category eq 'native') {
        $self->build_dll_native_runtime($package_name, $sub_names);
      }
      elsif ($category eq 'precompile') {
        $self->build_dll_precompile_runtime($package_name, $sub_names);
      }
      $dll_file = $self->get_dll_file_runtime($package_name);
    }
    $self->bind_subs($dll_file, $package_name, $sub_names);
  }
}

sub get_dll_file_runtime {
  my ($self, $package_name) = @_;
  
  my $dll_rel_file = SPVM::Builder::Util::convert_package_name_to_dll_category_rel_file($package_name, $self->category);
  my $build_dir = $self->{build_dir};
  
  return unless defined $build_dir;
  
  my $lib_dir = "$build_dir/work/lib";
  my $dll_file = "$lib_dir/$dll_rel_file";
  
  return $dll_file;
}

sub create_cfunc_name {
  my ($self, $package_name, $sub_name) = @_;
  
  my $category = $self->category;
  my $prefix = 'SP' . uc($category) . '__';
  
  # Precompile Subroutine names
  my $sub_abs_name_under_score = "${package_name}::$sub_name";
  $sub_abs_name_under_score =~ s/:/_/g;
  my $cfunc_name = "$prefix$sub_abs_name_under_score";
  
  return $cfunc_name;
}

sub get_config_runtime {
  my ($self, $package_name, $category) = @_;
  
  my $module_file = $self->builder->get_module_file($package_name);
  my $src_dir = SPVM::Builder::Util::remove_package_part_from_file($module_file, $package_name);

  # Config file
  my $config_rel_file = SPVM::Builder::Util::convert_package_name_to_category_rel_file_with_ext($package_name, $category, 'config');
  my $config_file = "$src_dir/$config_rel_file";
  
  # Config
  my $bconf;
  if (-f $config_file) {
    $bconf = SPVM::Builder::Util::load_config($config_file);
  }
  else {
    if ($category eq 'native') {
      my $error = <<"EOS";
Can't find $config_file.

Config file must contains at least the following code
----------------------------------------------
use strict;
use warnings;

use SPVM::Builder::Config;
my \$bconf = SPVM::Builder::Config->new_c99;

\$bconf;
----------------------------------------------
$@
EOS
      confess $error;
    }
    else {
      $bconf = SPVM::Builder::Config->new_c99;
    }
  }
  
  return $bconf;
}

sub bind_subs {
  my ($self, $dll_file, $package_name, $sub_names) = @_;
  
  
  # m library is maybe not dynamic link library
  my %must_not_load_libs = map { $_ => 1 } ('m');
  
  # Load pre-required dynamic library
  my $category = $self->category;
  my $bconf = $self->get_config_runtime($package_name, $category);
  my $lib_dirs = $bconf->get_lib_dirs;
  {
    local @DynaLoader::dl_library_path = (@$lib_dirs, @DynaLoader::dl_library_path);
    my $libs = $bconf->get_libs;
    for my $lib (@$libs) {
      unless ($must_not_load_libs{$lib}) {
        my ($lib_file) = DynaLoader::dl_findfile("-l$lib");
        my $dll_libref = DynaLoader::dl_load_file($lib_file);
        unless ($dll_libref) {
          my $dl_error = DynaLoader::dl_error();
          confess "Can't load dll file \"$dll_file\": $dl_error";
        }
      }
    }
  }
  
  for my $sub_name (@$sub_names) {
    my $sub_abs_name = "${package_name}::$sub_name";

    my $cfunc_name = $self->create_cfunc_name($package_name, $sub_name);
    my $cfunc_address;
    if ($dll_file) {
      my $dll_libref = DynaLoader::dl_load_file($dll_file);
      if ($dll_libref) {
        $cfunc_address = DynaLoader::dl_find_symbol($dll_libref, $cfunc_name);
        unless ($cfunc_address) {
          my $dl_error = DynaLoader::dl_error();
          my $error = <<"EOS";
Can't find native function \"$cfunc_name\" corresponding to $sub_abs_name in \"$dll_file\"

You must write the following definition.
--------------------------------------------------
#include <spvm_native.h>

int32_t $cfunc_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  return SPVM_SUCCESS;
}
--------------------------------------------------

$dl_error
EOS
          confess $error;
        }
      }
      else {
        my $dl_error = DynaLoader::dl_error();
        confess "Can't load dll file \"$dll_file\": $dl_error";
      }
    }
    else {
      confess "DLL file is not specified";
    }
    
    if ($category eq 'native') {
      $self->bind_sub_native($package_name, $sub_name, $cfunc_address);
    }
    elsif ($category eq 'precompile') {
      $self->bind_sub_precompile($package_name, $sub_name, $cfunc_address);
    }
  }
}

sub build_dll {
  my ($self, $package_name, $sub_names, $opt) = @_;
  
  # Compile source file and create object files
  my $object_files = $self->compile($package_name, $opt);
  
  # Link object files and create shared objectrary
  $self->link(
    $package_name,
    $sub_names,
    $object_files,
    $opt
  );
}

sub compile {
  my ($self, $package_name, $opt) = @_;

  # Build directory
  my $build_dir = $self->{build_dir};
  if (defined $build_dir) {
    mkpath $build_dir;
  }
  else {
    confess "SPVM_BUILD_DIR environment variable must be set for compile";
  }
  
  # Input directory
  my $src_dir = $opt->{src_dir};

  # Temporary directory
  my $object_dir = $opt->{object_dir};
  unless (defined $object_dir && -d $object_dir) {
    confess "Temporary directory must be specified for " . $self->category . " build";
  }
  
  my $category = $self->category;
 
  my $package_rel_file = SPVM::Builder::Util::convert_package_name_to_rel_file($package_name, 'spvm');
  my $package_rel_dir = SPVM::Builder::Util::convert_package_name_to_rel_dir($package_name);
  my $work_object_dir = "$object_dir/$package_rel_dir";
  mkpath $work_object_dir;
  
  # Package base name
  my $package_base_name = $package_name;
  $package_base_name =~ s/^.+:://;

  # Config file
  my $config_rel_file = SPVM::Builder::Util::convert_package_name_to_category_rel_file_with_ext($package_name, $category, 'config');
  my $config_file = "$src_dir/$config_rel_file";
  
  # Native Directory
  my $native_dir = $config_file;
  $native_dir =~ s/\.config$//;
  $native_dir .= '.native';
  
  # Include directory
  my $native_include_dir = "$native_dir/include";
  
  # Source directory
  my $native_src_dir = "$native_dir/src";

  # Config
  my $bconf;
  if (-f $config_file) {
    $bconf = SPVM::Builder::Util::load_config($config_file);
  }
  else {
    $bconf = SPVM::Builder::Config->new_c99;;
  }
  
  # Add native include dir
  unshift @{$bconf->get_include_dirs}, $native_include_dir;

  # Quiet output
  my $quiet = $bconf->get_quiet;
  
  # SPVM Subroutine source file
  my $src_rel_file_no_ext = SPVM::Builder::Util::convert_package_name_to_category_rel_file_without_ext($package_name, $category);
  my $spvm_sub_src_file_no_ext = "$src_dir/$src_rel_file_no_ext";
  my $src_ext = $bconf->get_ext;
  unless (defined $src_ext) {
    confess "Source extension is not specified";
  }
  my $spvm_sub_src_file = "$spvm_sub_src_file_no_ext.$src_ext";
  unless (-f $spvm_sub_src_file) {
    confess "Can't find source file $spvm_sub_src_file";
  }
  
  # CBuilder configs
  my $ccflags = $bconf->get_ccflags;
  
  # Use all of default %Config not to use %Config directory by ExtUtils::CBuilder
  # and overwrite user configs
  my $config = $bconf->to_hash;

  # Compile source files
  my $cbuilder = ExtUtils::CBuilder->new(quiet => $quiet, config => $config);
  
  # Parse source code dependency
  my $dependency = $self->_parse_native_src_dependency($native_include_dir, $native_src_dir, $src_ext);

  # Native source files
  my @native_src_files = sort keys %$dependency;
  
  # Compile source files
  my $object_files = [];
  my $is_native_src;
  for my $src_file ($spvm_sub_src_file, @native_src_files) {
    my $object_file;
    # Native object file name
    if ($is_native_src) {
      my $object_rel_file = SPVM::Builder::Util::convert_package_name_to_category_rel_file_with_ext($package_name, $category, 'native');
      
      my $object_file_base = $src_file;
      $object_file_base =~ s/^\Q$native_src_dir//;
      $object_file_base =~ s/^[\\\/]//;
      
      $object_file_base =~ s/\.[^\.]+$/.o/;
      $object_file = "$object_dir/$object_rel_file/$object_file_base";
      
      my $object_dir = dirname $object_file;
      mkpath $object_dir;
    }
    # SPVM subroutine object file name
    else {
      my $object_rel_file = SPVM::Builder::Util::convert_package_name_to_category_rel_file_with_ext($package_name, $category, 'o');
      $object_file = "$object_dir/$object_rel_file";
    }
    
    # Do compile. This is same as make command
    my $do_compile;
    if ($package_name =~ /^anon/) {
      $do_compile = 1;
    }
    else {
      if ($bconf->get_force_compile) {
        $do_compile = 1;
      }
      else {
        if (!-f $object_file) {
          $do_compile = 1;
        }
        else {
          # Do compile if one of dependency files(source file and include files and config file) is newer than object file
          my @dependency_files;
          if (-f $config_file) {
            push @dependency_files, $config_file;
          }
          push @dependency_files, $src_file;
          my $dependency_files_native = $dependency->{$src_file};
          if ($dependency_files_native) {
            for my $dependency_file_native (@$dependency_files_native) {
              push @dependency_files, $dependency_file_native;
            }
          }
          
          my $mod_time_object_file = (stat($object_file))[9];
          for my $dependency_file (@dependency_files) {
            my $mod_time_dependency_file = (stat($dependency_file))[9];
            if ($mod_time_dependency_file > $mod_time_object_file) {
              $do_compile = 1;
              last;
            }
          }
        }
      }
    }
    
    if ($do_compile) {
      eval {
        # Compile source file
        $cbuilder->compile(
          source => $src_file,
          object_file => $object_file,
          include_dirs => $bconf->get_include_dirs,
          extra_compiler_flags => $bconf->get_extra_compiler_flags,
        );
      };
      if (my $error = $@) {
        confess $error;
      }
    }
    push @$object_files, $object_file;
    
    $is_native_src = 1;
  }
  
  return $object_files;
}

sub _parse_native_src_dependency {
  my ($self, $include_dir, $src_dir, $src_ext) = @_;
  
  # Get header files
  my @include_file_names;
  if (-d $include_dir) {
    find(
      {
        wanted => sub {
          my $include_file_name = $File::Find::name;
          if (-f $include_file_name) {
            push @include_file_names, $include_file_name;
          }
        },
        no_chdir => 1,
      },
      $include_dir,
    );
  }
  
  # Get source files
  my @src_file_names;
  if (-d $src_dir) {
    find(
      {
        wanted => sub {
          my $src_file_name = $File::Find::name;
          if (-f $src_file_name) {
            push @src_file_names, $src_file_name;
          }
        },
        no_chdir => 1,
      },
      $src_dir,
    );
  }
  
  my $dependencies = {};
  for my $include_file_name (@include_file_names) {
    my $include_file_name_no_ext_rel = $include_file_name;
    $include_file_name_no_ext_rel =~ s/^\Q$include_dir//;
    $include_file_name_no_ext_rel =~ s/^[\\\/]//;
    $include_file_name_no_ext_rel =~ s/\.[^\\\/]+$//;
    
    my $match_at_least_one;
    for my $src_file_name (@src_file_names) {
      # Skip if file have no source extension
      next unless $src_file_name =~ /\Q.$src_ext\E$/;
      
      my $src_file_name_no_ext_rel = $src_file_name;
      $src_file_name_no_ext_rel =~ s/^\Q$src_dir//;
      $src_file_name_no_ext_rel =~ s/^[\\\/]//;
      $src_file_name_no_ext_rel =~ s/\.[^\\\/]+$//;
      
      if ($src_file_name_no_ext_rel eq $include_file_name_no_ext_rel) {
        $dependencies->{$src_file_name} ||= [];
        push @{$dependencies->{$src_file_name}}, $include_file_name;
        $match_at_least_one++;
      }
    }
    
    # If not match at least one, we assume the header files is common file
    unless ($match_at_least_one) {
      for my $src_file_name (@src_file_names) {
        # Skip if file have no source extension
        next unless $src_file_name =~ /\Q.$src_ext\E$/;
        push @{$dependencies->{$src_file_name}}, $include_file_name;
      }
    }
  }
  
  return $dependencies;
}

sub link {
  my ($self, $package_name, $sub_names, $object_files, $opt) = @_;

  # Build directory
  my $build_dir = $self->{build_dir};
  if (defined $build_dir) {
    mkpath $build_dir;
  }
  else {
    confess "SPVM_BUILD_DIR environment variable must be set for linking" . $self->category . " build";
  }
  
  # Input directory
  my $src_dir = $opt->{src_dir};

  # Work temporary directory
  my $object_dir = $opt->{object_dir};
  unless (defined $object_dir && -d $object_dir) {
    confess "Temporary directory must be specified for " . $self->category . " build";
  }
  
  # Output directory
  my $lib_dir = $opt->{lib_dir};
  unless (defined $lib_dir && -d $lib_dir) {
    confess "Output directory must be specified for " . $self->category . " build";
  }

  # shared object file
  my $dll_rel_file = SPVM::Builder::Util::convert_package_name_to_dll_category_rel_file($package_name, $self->category);
  my $dll_file = "$lib_dir/$dll_rel_file";

  # Create temporary package directory
  my $tmp_package_rel_file = SPVM::Builder::Util::convert_package_name_to_rel_file($package_name, 'spvm');
  my $tmp_package_rel_dir = SPVM::Builder::Util::convert_package_name_to_rel_dir($package_name);
  my $tmp_package_dir = "$object_dir/$tmp_package_rel_dir";
  mkpath $tmp_package_dir;
  
  # Category
  my $category = $self->category;

  # Config file
  my $config_rel_file = SPVM::Builder::Util::convert_package_name_to_category_rel_file_with_ext($package_name, $category, 'config');
  my $config_file = "$src_dir/$config_rel_file";
  
  # Config
  my $bconf;
  if (-f $config_file) {
    $bconf = SPVM::Builder::Util::load_config($config_file);
  }
  else {
    if ($category eq 'native') {
      my $error = <<"EOS";
Can't find $config_file.

Config file must contains at least the following code
----------------------------------------------
use strict;
use warnings;

use SPVM::Builder::Config;
my \$bconf = SPVM::Builder::Config->new_c99;

\$bconf;
----------------------------------------------

EOS
      confess $error;
    }
    else {
      $bconf = SPVM::Builder::Config->new_c99;
    }
  }

  # Native Directory
  my $native_dir = $config_file;
  $native_dir =~ s/\.config$//;
  $native_dir .= '.native';
  
  # Library directory
  my $native_lib_dir = "$native_dir/lib";
  $bconf->unshift_lib_dirs($native_lib_dir);

  # Quiet output
  my $quiet = $bconf->get_quiet;
  
  # CBuilder configs
  my $lddlflags = $bconf->get_lddlflags;

  # Use all of default %Config not to use %Config directory by ExtUtils::CBuilder
  # and overwrite user configs
  my $config = $bconf->to_hash;
  
  my $cfunc_names = [];
  for my $sub_name (@$sub_names) {
    my $category = $self->category;
    my $category_uc = uc $category;
    my $cfunc_name = "SP${category_uc}__${package_name}::$sub_name";
    $cfunc_name =~ s/:/_/g;
    push @$cfunc_names, $cfunc_name;
  }
  
  # This is dummy to suppress boot strap function
  # This is bad hack
  unless (@$cfunc_names) {
    push @$cfunc_names, '';
  }
  
  my $cbuilder = ExtUtils::CBuilder->new(quiet => $quiet, config => $config);
  my $tmp_dll_file;
  my $lib_dirs_str = join(' ', map { "-L$_" } @{$bconf->get_lib_dirs});
  my $libs_str = join(' ', map { "-l$_" } @{$bconf->get_libs});
  my $extra_linker_flag = $bconf->get_extra_linker_flags;
  
  $extra_linker_flag = "$lib_dirs_str $libs_str $extra_linker_flag";
  eval {
    $tmp_dll_file = $cbuilder->link(
      objects => $object_files,
      module_name => $package_name,
      dl_func_list => $cfunc_names,
      extra_linker_flags => $extra_linker_flag
    );
  };
  if (my $error = $@) {
    confess $error;
  }

  # Create shared object blib directory
  my $package_rel_file_without_ext = SPVM::Builder::Util::convert_package_name_to_rel_file($package_name);
  my $dll_dir = dirname "$lib_dir/$package_rel_file_without_ext";
  mkpath $dll_dir;
  
  # Move shared objectrary file to blib directory
  move($tmp_dll_file, $dll_file)
    or die "Can't move $tmp_dll_file to $dll_file";
  
  return $dll_file;
}

sub get_dll_file_dist {
  my ($self, $package_name) = @_;
  
  my @package_name_parts = split(/::/, $package_name);
  my $module_module_file = $self->builder->get_module_file($package_name);
  
  my $dll_file = SPVM::Builder::Util::convert_module_file_to_dll_category_file($module_module_file, $self->category);
  
  return $dll_file;
}

sub build_dll_precompile_runtime {
  my ($self, $package_name, $sub_names) = @_;

  # Build directory
  my $build_dir = $self->{build_dir};
  if (defined $build_dir) {
    mkpath $build_dir;
  }
  else {
    confess "SPVM_BUILD_DIR environment variable must be set for build precompile subroutine in runtime";
  }
  
  # Object directory
  my $object_dir = "$build_dir/work/object";
  mkpath $object_dir;
  
  # Source directory
  my $src_dir = "$build_dir/work/src";
  mkpath $src_dir;
  
  # Lib directory
  my $lib_dir = "$build_dir/work/lib";
  mkpath $lib_dir;
  
  $self->create_source_precompile(
    $package_name,
    $sub_names,
    {
      src_dir => $src_dir,
    }
  );
  
  $self->build_dll(
    $package_name,
    $sub_names,
    {
      src_dir => $src_dir,
      object_dir => $object_dir,
      lib_dir => $lib_dir,
    }
  );
}

sub build_dll_native_runtime {
  my ($self, $package_name, $sub_names) = @_;
  
  my $module_file = $self->builder->get_module_file($package_name);
  my $src_dir = SPVM::Builder::Util::remove_package_part_from_file($module_file, $package_name);

  # Build directory
  my $build_dir = $self->{build_dir};
  if (defined $build_dir) {
    mkpath $build_dir;
  }
  else {
    confess "SPVM_BUILD_DIR environment variable must be set for build native subroutine in runtime";
  }
  
  my $object_dir = "$build_dir/work/object";
  mkpath $object_dir;
  
  my $lib_dir = "$build_dir/work/lib";
  mkpath $lib_dir;
  
  $self->build_dll(
    $package_name,
    $sub_names,
    {
      src_dir => $src_dir,
      object_dir => $object_dir,
      lib_dir => $lib_dir,
    }
  );
}

sub build_dll_precompile_dist {
  my ($self, $package_name, $sub_names) = @_;
  
  my $object_dir = ".spvm_build/work/object";
  mkpath $object_dir;
  
  my $src_dir = ".spvm_build/work/src";
  mkpath $src_dir;

  my $lib_dir = 'blib/lib';
  
  $self->create_source_precompile(
    $package_name,
    $sub_names,
    {
      src_dir => $src_dir,
    }
  );
  
  $self->build_dll(
    $package_name,
    $sub_names,
    {
      src_dir => $src_dir,
      object_dir => $object_dir,
      lib_dir => $lib_dir,
    }
  );
}

sub build_dll_native_dist {
  my ($self, $package_name, $sub_names) = @_;
  
  my $src_dir = 'lib';

  my $object_dir = ".spvm_build/work/object";
  mkpath $object_dir;

  my $lib_dir = 'blib/lib';

  my $category = $self->category;
  
  # Build shared object
  $self->build_dll(
    $package_name,
    $sub_names,
    {
      src_dir => $src_dir,
      object_dir => $object_dir,
      lib_dir => $lib_dir,
    }
  );
}

sub create_source_precompile {
  my ($self, $package_name, $sub_names, $opt) = @_;
  
  my $src_dir = $opt->{src_dir};
  mkpath $src_dir;
  
  my $category = 'precompile';
  
  my $package_rel_file_without_ext = SPVM::Builder::Util::convert_package_name_to_rel_file($package_name);
  my $package_rel_dir = SPVM::Builder::Util::convert_package_name_to_rel_dir($package_name);
  my $source_file = "$src_dir/$package_rel_file_without_ext.$category.c";
  
  my $source_dir = "$src_dir/$package_rel_dir";
  mkpath $source_dir;

  my $package_csource = $self->build_package_csource_precompile($package_name, $sub_names);
  
  my $is_create_source_file;
  # Anon sub
  if ($package_name =~ /^anon/) {
    $is_create_source_file = 1;
  }
  # Normal sub
  else {
    # Get old csource source
    my $old_package_csource;
    if (-f $source_file) {
      open my $fh, '<', $source_file
        or die "Can't open $source_file";
      $old_package_csource = do { local $/; <$fh> };
    }
    else {
      $old_package_csource = '';
    }
    
    if ($package_csource ne $old_package_csource) {
      $is_create_source_file = 1;
    }
    else {
      $is_create_source_file = 0;
    }
  }
  
  # Create source fil
  if ($is_create_source_file) {
    open my $fh, '>', $source_file
      or die "Can't create $source_file";
    print $fh $package_csource;
    close $fh;
  }
}

1;

=head1 NAME

SPVM::Builder::CC - Native code Compiler and linker. Wrapper of ExtUtils::CBuilder for SPVM

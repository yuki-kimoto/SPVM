package SPVM::Builder::CC;

use strict;
use warnings;
use Carp 'confess';

use ExtUtils::CBuilder;
use File::Copy 'copy', 'move';
use File::Path 'mkpath';
use File::Find 'find';
use File::Basename 'dirname', 'basename';

use SPVM::Builder::Util;
use SPVM::Builder::Config;

sub category { shift->{category} }
sub builder { shift->{builder} }
sub force { shift->{force} }
sub quiet { shift->{quiet} }

sub new {
  my $class = shift;
  
  my $self = {@_};
  
  if ($ENV{SPVM_CC_DEBUG}) {
    $self->{quiet} = 0;
  }
  
  return bless $self, $class;
}

sub build_shared_lib_runtime {
  my ($self, $class_name) = @_;

  my $category = $self->category;
  
  # Build directory
  my $build_dir = $self->builder->build_dir;
  if (defined $build_dir) {
    mkpath $build_dir;
  }
  else {
    confess "SPVM_BUILD_DIR environment variable must be set for build $category method in runtime";
  }
  
  # Source directory
  my $src_dir;
  if ($category eq 'precompile') {
    $src_dir = $self->builder->create_build_src_path;
    mkpath $src_dir;
    
    $self->create_precompile_csource(
      $class_name,
      {
        src_dir => $src_dir,
      }
    );
  }
  elsif ($category eq 'native') {
    my $module_file = $self->builder->get_module_file($class_name);
    $src_dir = SPVM::Builder::Util::remove_class_part_from_file($module_file, $class_name);
  }
  
  # Object directory
  my $object_dir = $self->builder->create_build_object_path;
  mkpath $object_dir;
  
  # Lib directory
  my $lib_dir = $self->builder->create_build_lib_path;
  mkpath $lib_dir;
  
  my $build_shared_lib_file = $self->build_shared_lib(
    $class_name,
    {
      src_dir => $src_dir,
      object_dir => $object_dir,
      lib_dir => $lib_dir,
    }
  );
  
  return $build_shared_lib_file;
}

sub build_shared_lib_dist {
  my ($self, $class_name) = @_;
  
  my $category = $self->category;
  
  my $src_dir;
  if ($category eq 'precompile') {
    $src_dir = $self->builder->create_build_src_path;
    mkpath $src_dir;

    $self->create_precompile_csource(
      $class_name,
      {
        src_dir => $src_dir,
      }
    );
  }
  elsif ($category eq 'native') {
    $src_dir = 'lib';
  }

  my $object_dir = $self->builder->create_build_object_path;
  mkpath $object_dir;
  
  my $lib_dir = 'blib/lib';
  
  
  $self->build_shared_lib(
    $class_name,
    {
      src_dir => $src_dir,
      object_dir => $object_dir,
      lib_dir => $lib_dir,
    }
  );
}

sub build_shared_lib {
  my ($self, $class_name, $opt) = @_;
  
  # Compile source file and create object files
  my $object_files = $self->compile($class_name, $opt);
  
  # Link object files and create shared library
  my $build_shared_lib_file = $self->link(
    $class_name,
    $object_files,
    $opt
  );
  
  return $build_shared_lib_file;
}

sub compile {
  my ($self, $class_name, $opt) = @_;

  # Category
  my $category = $self->category;

  # Build directory
  my $build_dir = $self->builder->build_dir;
  if (defined $build_dir) {
    mkpath $build_dir;
  }
  else {
    confess "SPVM_BUILD_DIR environment variable must be set for compile";
  }
  
  # Source directory
  my $src_dir = $opt->{src_dir};

  # Object directory
  my $object_dir = $opt->{object_dir};
  unless (defined $object_dir && -d $object_dir) {
    confess "Temporary directory must be specified for " . $self->category . " build";
  }
  
  # Config file
  my $config_rel_file = SPVM::Builder::Util::convert_class_name_to_category_rel_file($class_name, $category, 'config');
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
  unshift @{$bconf->include_dirs}, $native_include_dir;

  # Quiet output
  my $quiet = $bconf->quiet;

  # If quiet field exists, overwrite it
  if (defined $self->quiet) {
    $quiet = $self->quiet;
  }
  
  # SPVM Method source file
  my $src_rel_file_no_ext = SPVM::Builder::Util::convert_class_name_to_category_rel_file($class_name, $category);
  my $spvm_method_src_file_no_ext = "$src_dir/$src_rel_file_no_ext";
  my $src_ext = $bconf->ext;
  unless (defined $src_ext) {
    confess "Source extension is not specified";
  }
  
  my $spvm_method_src_file = "$spvm_method_src_file_no_ext.$src_ext";
  unless (-f $spvm_method_src_file) {
    confess "Can't find source file $spvm_method_src_file";
  }
  
  # Parse source code dependency
  my $dependency = $self->parse_native_source_dependencies($native_include_dir, $native_src_dir, $src_ext);

  # Native source files
  my @native_src_files = sort keys %$dependency;
  
  my $cbuilder = ExtUtils::CBuilder->new(quiet => $quiet);
  
  # Compile source files
  my $object_files = [];
  my $is_native_src;
  for my $src_file ($spvm_method_src_file, @native_src_files) {
    my $object_file;
    # Native object file name
    if ($is_native_src) {
      my $object_rel_file = SPVM::Builder::Util::convert_class_name_to_category_rel_file($class_name, $category, 'native');
      
      my $object_file_base = $src_file;
      $object_file_base =~ s/^\Q$native_src_dir//;
      $object_file_base =~ s/^[\\\/]//;
      
      $object_file_base =~ s/\.[^\.]+$/.o/;
      $object_file = "$object_dir/$object_rel_file/$object_file_base";
      
      my $object_dir = dirname $object_file;
      mkpath $object_dir;
    }
    # SPVM method object file name
    else {
      my $object_rel_file = SPVM::Builder::Util::convert_class_name_to_category_rel_file($class_name, $category, 'o');
      $object_file = "$object_dir/$object_rel_file";
    }
    
    # Do compile. This is same as make command
    my $do_compile;
    if ($self->force) {
      $do_compile = 1;
    }
    else {
      if ($bconf->force_compile) {
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
      my $class_rel_dir = SPVM::Builder::Util::convert_class_name_to_rel_dir($class_name);
      my $work_object_dir = "$object_dir/$class_rel_dir";
      mkpath dirname $object_file;

      my $cc_cmd = $self->create_compile_command($bconf, $object_file, $src_file);
      eval {
        # Execute compile command
        $cbuilder->do_system(@$cc_cmd)
          or confess "Can't compile $src_file: @$cc_cmd";
      };
    }
    push @$object_files, $object_file;
    
    $is_native_src = 1;
  }
  
  return $object_files;
}

sub create_compile_command {
  my ($self, $bconf, $output_file, $src_file) = @_;
  
  my $cc = $bconf->cc;
  
  my $cflags = '';

  my $include_dirs = $bconf->include_dirs;
  my $inc = join(' ', map { "-I$_" } @$include_dirs);
  $cflags .= " $inc";
  
  my $ccflags = $bconf->ccflags;
  $cflags .= " " . join(' ', @$ccflags);
  
  my $optimize = $bconf->optimize;
  $cflags .= " $optimize";
  
  my @cflags = ExtUtils::CBuilder->new->split_like_shell($cflags);
  
  my $cc_cmd = [$cc, '-c', @cflags, '-o', $output_file, $src_file];
  
  return $cc_cmd;
}

sub link {
  my ($self, $class_name, $object_files, $opt) = @_;

  # Category
  my $category = $self->category;

  # Build directory
  my $build_dir = $self->builder->build_dir;
  if (defined $build_dir) {
    mkpath $build_dir;
  }
  else {
    confess "SPVM_BUILD_DIR environment variable must be set for link";
  }
  
  # Object directory
  my $object_dir = $opt->{object_dir};
  unless (defined $object_dir && -d $object_dir) {
    confess "Object directory must be specified for link";
  }
  
  # Shared library directory
  my $lib_dir = $opt->{lib_dir};
  unless (defined $lib_dir && -d $lib_dir) {
    confess "Shared lib directory must be specified for link";
  }

  # Shared library file
  my $shared_lib_rel_file = SPVM::Builder::Util::convert_class_name_to_shared_lib_rel_file($class_name, $self->category);
  my $shared_lib_file = "$lib_dir/$shared_lib_rel_file";

  # Config file
  my $config_rel_file = SPVM::Builder::Util::convert_class_name_to_category_rel_file($class_name, $category, 'config');
  my $src_dir = $opt->{src_dir};
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
  if (-d $native_lib_dir) {
    $bconf->unshift_lib_dirs($native_lib_dir);
  }
  
  # Quiet output
  my $quiet = $bconf->quiet;

  # If quiet field exists, overwrite it
  if (defined $self->quiet) {
    $quiet = $self->quiet;
  }
  
  # dl_func_list
  # This option is needed Windows DLL file
  my $dl_func_list = [];
  my $method_names = $self->builder->get_method_names($class_name, $category);
  for my $method_name (@$method_names) {
    my $cfunc_name = SPVM::Builder::Util::create_cfunc_name($class_name, $method_name, $category);
    push @$dl_func_list, $cfunc_name;
  }
  
  if ($category eq 'precompile') {
    # Add anon class sub names to dl_func_list
    my $anon_class_names = $self->builder->get_anon_class_names_by_parent_class_name($class_name);
    
    for my $anon_class_name (@$anon_class_names) {
      my $anon_method_cfunc_name = SPVM::Builder::Util::create_cfunc_name($anon_class_name, "", $category);
      push @$dl_func_list, $anon_method_cfunc_name;
    }
  }
  
  # This is bad hack to suppress boot strap function error.
  unless (@$dl_func_list) {
    push @$dl_func_list, '';
  }

  # Add library directories and libraries to Linker flags
  my $lib_dirs_str = join(' ', map { "-L$_" } @{$bconf->lib_dirs});
 
  # Config
  my $ld = $bconf->ld;
  my $lddlflags = $bconf->lddlflags;
  
  my $lddlflags_str = join(' ', @{$bconf->lddlflags});
  $lddlflags_str = "$lib_dirs_str $lddlflags_str";
  
  my $config = {
    ld => $ld,
    lddlflags => $lddlflags_str,
    shrpenv => '',
  };
  
  # ExtUtils::CBuilder object
  my $cbuilder = ExtUtils::CBuilder->new(quiet => $quiet, config => $config);

  # Link and create shared library
  my $tmp_shared_lib_file;
  eval {
    $tmp_shared_lib_file = $cbuilder->link(
      objects => $object_files,
      module_name => $class_name,
      dl_func_list => $dl_func_list,
    );
  };
  if (my $error = $@) {
    confess $error;
  }

  # Move temporary shared library file to blib directory
  mkpath dirname $shared_lib_file;
  move($tmp_shared_lib_file, $shared_lib_file)
    or die "Can't move $tmp_shared_lib_file to $shared_lib_file";
  
  return $shared_lib_file;
}

sub create_precompile_csource {
  my ($self, $class_name, $opt) = @_;

  my $src_dir = $opt->{src_dir};
  mkpath $src_dir;
  
  my $category = 'precompile';
  
  my $class_rel_file_without_ext = SPVM::Builder::Util::convert_class_name_to_rel_file($class_name);
  my $class_rel_dir = SPVM::Builder::Util::convert_class_name_to_rel_dir($class_name);
  my $source_file = "$src_dir/$class_rel_file_without_ext.$category.c";
  
  my $source_dir = "$src_dir/$class_rel_dir";
  mkpath $source_dir;
  
  my $class_csource = $self->build_class_csource_precompile($class_name);
  
  my $is_create_csource_file;

  # Get old csource source
  my $old_class_csource;
  if (-f $source_file) {
    open my $fh, '<', $source_file
      or die "Can't open $source_file";
    $old_class_csource = do { local $/; <$fh> };
  }
  else {
    $old_class_csource = '';
  }
  
  if ($class_csource ne $old_class_csource) {
    $is_create_csource_file = 1;
  }
  else {
    $is_create_csource_file = 0;
  }
  
  # Create source fil
  if ($is_create_csource_file) {
    open my $fh, '>', $source_file
      or die "Can't create $source_file";
    print $fh $class_csource;
    close $fh;
  }
}

sub parse_native_source_dependencies {
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

1;

=head1 NAME

SPVM::Builder::CC - Compiler and Linker of Native Sources

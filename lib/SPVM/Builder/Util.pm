package SPVM::Builder::Util;

use strict;
use warnings;
use Carp 'confess';
use Config;
use File::Path 'mkpath';
use Pod::Usage 'pod2usage';
use Getopt::Long 'GetOptionsFromArray';
use List::Util 'min';
use File::Basename 'dirname';
use File::Spec;

# SPVM::Builder::Util is used from Makefile.PL
# so this module must be wrote as pure perl script, not contain XS functions and don't use any other SPVM modules.

sub need_generate {
  my ($opt) = @_;
  
  my $global_force = $opt->{global_force};
  my $config_force = $opt->{config_force};
  my $input_files = $opt->{input_files};
  my $output_file = $opt->{output_file};

  my $need_generate;
  if ($global_force) {
    $need_generate = 1;
  }
  elsif ($config_force) {
    $need_generate = 1;
  }
  else {
    if (!-f $output_file) {
      $need_generate = 1;
    }
    else {
      my $input_files_mtime_max = 0;
      my $exists_input_file_at_least_one;
      for my $input_file (@$input_files) {
        if (-f $input_file) {
          $exists_input_file_at_least_one = 1;
          my $input_file_mtime = (stat($input_file))[9];
          if ($input_file_mtime > $input_files_mtime_max) {
            $input_files_mtime_max = $input_file_mtime;
          }
        }
      }
      if ($exists_input_file_at_least_one) {
        my $output_file_mtime = (stat($output_file))[9];
        if ($input_files_mtime_max > $output_file_mtime) {
          $need_generate = 1;
        }
      }
    }
  }
  
  return $need_generate;
}

sub slurp_binary {
  my ($file) = @_;
  
  open my $fh, '<', $file
    or confess "Can't open file \"$file\":$!";
    
  my $content = do { local $/; <$fh> };
  
  return $content;
}

sub spurt_binary {
  my ($file, $content) = @_;
  
  open my $fh, '>:raw', $file
    or confess "Can't open file \"$file\":$!";
    
  print $fh $content;
}

sub create_cfunc_name {
  my ($class_name, $method_name, $category) = @_;
  
  my $prefix;
  if ($category eq 'native') {
    $prefix = 'SPVM__';
  }
  elsif ($category eq 'precompile') {
    $prefix = 'SPVMPRECOMPILE__'
  }
  
  # Precompile Method names
  my $method_abs_name_under_score = "${class_name}::$method_name";
  $method_abs_name_under_score =~ s/:/_/g;
  my $cfunc_name = "$prefix$method_abs_name_under_score";
  
  return $cfunc_name;
}

sub load_config {
  my ($config_file) = @_;
  
  unless (-f $config_file) {
    confess "Can't find config file \"$config_file\"";
  }
  my $config = do File::Spec->rel2abs($config_file);
  if ($@) {
    confess "Can't parse config file \"$config_file\": $@";
  }
  
  return $config;
}

sub unindent {
  my $str = shift;
  my $min = min map { m/^([ \t]*)/; length $1 || () } split "\n", $str;
  $str =~ s/^[ \t]{0,$min}//gm if $min;
  return $str;
}

sub extract_usage {
  my $file = @_ ? "$_[0]" : (caller)[1];

  open my $handle, '>', \my $output;
  pod2usage -exitval => 'noexit', -input => $file, -output => $handle;
  $output =~ s/^.*\n|\n$//;
  $output =~ s/\n$//;

  return SPVM::Builder::Util::unindent($output);
}

sub getopt {
  my ($array, $opts) = map { ref $_[0] eq 'ARRAY' ? shift : $_ } \@ARGV, [];
  my $save = Getopt::Long::Configure(qw(default no_auto_abbrev no_ignore_case),
    @$opts);
  GetOptionsFromArray $array, @_;
  Getopt::Long::Configure($save);
}

sub convert_module_file_to_shared_lib_file {
  my ($module_file, $category) = @_;
  
  my $dlext = $Config{dlext};
  $module_file =~ s/\.[^.]+$//;
  my $shared_lib_category_file = $module_file;
  $shared_lib_category_file .= $category eq 'native' ? ".$dlext" : ".$category.$dlext";
  
  return $shared_lib_category_file;
}

sub convert_class_name_to_shared_lib_rel_file {
  my ($class_name, $category) = @_;
  
  my $dlext = $Config{dlext};
  my $shared_lib_category_rel_file = convert_class_name_to_rel_file($class_name);
  $shared_lib_category_rel_file .= $category eq 'native' ? ".$dlext" : ".$category.$dlext";
  
  return $shared_lib_category_rel_file;
}

sub convert_class_name_to_category_rel_file {
  my ($class_name, $category, $ext) = @_;
  
  $class_name =~ s/^SPVM:://;
  
  my $rel_file_with_ext = "SPVM::$class_name";
  $rel_file_with_ext =~ s/::/\//g;
  $rel_file_with_ext .= $category eq 'native' ? "" : ".$category";
  if (defined $ext) {
    $rel_file_with_ext .= ".$ext";
  }
  
  return $rel_file_with_ext;
}

sub convert_class_name_to_rel_dir {
  my ($class_name) = @_;

  $class_name =~ s/^SPVM:://;

  my $rel_dir;
  my $rel_file = "SPVM::$class_name";
  $rel_file =~ s/::/\//g;
  $rel_dir = dirname $rel_file;
  
  return $rel_dir;
}

sub convert_class_name_to_rel_file {
  my ($class_name, $ext) = @_;

  $class_name =~ s/^SPVM:://;
  
  my $rel_file_with_ext = "SPVM::$class_name";
  $rel_file_with_ext =~ s/::/\//g;
  
  if (defined $ext) {
    $rel_file_with_ext .= ".$ext";
  }
  
  return $rel_file_with_ext;
}

sub remove_class_part_from_file {
  my ($file, $class_name) = @_;

  $class_name =~ s/^SPVM:://;
  
  $file =~ s/\.spvm$//;
  my $class_file = "SPVM::$class_name";
  $class_file =~ s/::/\//g;
  $file =~ s/$class_file$//;
  $file =~ s/[\\\/]$//;
  
  return $file;
}

sub create_make_rule_native {
  my $class_name = shift;
  
  create_class_make_rule($class_name, 'native');
}

sub create_make_rule_precompile {
  my $class_name = shift;
  
  create_class_make_rule($class_name, 'precompile');
}

sub create_class_make_rule {
  my ($class_name, $category) = @_;

  $class_name =~ s/^SPVM:://;
  
  my $module_base_name = $class_name;
  $module_base_name =~ s/^.+:://;
  
  my $src_dir = 'lib';

  my $class_rel_file = convert_class_name_to_rel_file($class_name, 'spvm');
  
  my $noext_file = $class_rel_file;
  $noext_file =~ s/\.[^\.]+$//;
  
  my $spvm_file = $noext_file;
  $spvm_file .= '.spvm';
  $spvm_file = "$src_dir/$spvm_file";
  
  my $native_c_file = $noext_file;
  $native_c_file .= '.c';
  $native_c_file = "$src_dir/$native_c_file";

  my $config_file = $noext_file;
  $config_file .= '.config';
  $config_file = "$src_dir/$config_file";

  # Dependency files
  my @deps;
  
  # Dependency c source files
  push @deps, grep { $_ ne '.' && $_ ne '..' } glob "$src_dir/$class_rel_file/*";
  
  # Dependency module file
  if ($category eq 'native') {
    push @deps, $spvm_file, $native_c_file, $config_file;
  }
  elsif ($category eq 'precompile') {
    push @deps, $spvm_file;
  }

  # Shared library file
  my $shared_lib_rel_file = convert_class_name_to_shared_lib_rel_file($class_name, $category);
  my $shared_lib_file = "blib/lib/$shared_lib_rel_file";
  
  my $make_rule = '';
  
  # dynamic section
  $make_rule .= "dynamic :: $shared_lib_file\n";
  $make_rule .= "\t\$(NOECHO) \$(NOOP)\n\n";
  
  # Get source files
  $make_rule .= "$shared_lib_file :: @deps\n";
  $make_rule .= "\t$^X -Mblib -MSPVM::Builder::API -e \"SPVM::Builder::API->new(build_dir => '.spvm_build')->build_shared_lib_dist_$category('$class_name')\"\n\n";
  
  return $make_rule;
}

sub get_spvm_core_source_file_names {
  
  my @spvm_core_source_file_names = qw(
    spvm_allocator.c
    spvm_allow.c
    spvm_api.c
    spvm_array_field_access.c
    spvm_basic_type.c
    spvm_block.c
    spvm_call_method.c
    spvm_case_info.c
    spvm_class.c
    spvm_class_var_access.c
    spvm_class_var.c
    spvm_implement.c
    spvm_compiler.c
    spvm_constant.c
    spvm_csource_builder_precompile.c
    spvm_descriptor.c
    spvm_dumper.c
    spvm_field_access.c
    spvm_field.c
    spvm_hash.c
    spvm_list.c
    spvm_method.c
    spvm_my.c
    spvm_op.c
    spvm_op_checker.c
    spvm_opcode_array.c
    spvm_opcode_builder.c
    spvm_opcode.c
    spvm_string_buffer.c
    spvm_switch_info.c
    spvm_toke.c
    spvm_type.c
    spvm_use.c
    spvm_var.c
    spvm_yacc.c
    spvm_yacc_util.c
  );
  
  return \@spvm_core_source_file_names;
}


sub get_spvm_core_header_file_names {
  
  my @spvm_core_header_file_names = qw(
    spvm_allocator.h
    spvm_allow.h
    spvm_api.h
    spvm_array_field_access.h
    spvm_basic_type.h
    spvm_block.h
    spvm_call_method.h
    spvm_case_info.h
    spvm_check_ast_info.h
    spvm_class.h
    spvm_class_var_access.h
    spvm_class_var.h
    spvm_compiler.h
    spvm_constant.h
    spvm_csource_builder_precompile.h
    spvm_descriptor.h
    spvm_dumper.h
    spvm_field_access.h
    spvm_field.h
    spvm_hash.h
    spvm_implement.h
    spvm_limit.h
    spvm_list.h
    spvm_method.h
    spvm_my.h
    spvm_name_info.h
    spvm_native.h
    spvm_object.h
    spvm_op_checker.h
    spvm_opcode_array.h
    spvm_opcode_builder.h
    spvm_opcode.h
    spvm_op.h
    spvm_string_buffer.h
    spvm_switch_info.h
    spvm_toke.h
    spvm_typedecl.h
    spvm_type.h
    spvm_use.h
    spvm_var.h
    spvm_weaken_backref.h
    spvm_yacc.h
    spvm_yacc_util.h
  );
  
  return \@spvm_core_header_file_names;
}

1;

=head1 NAME

SPVM::Builder::Util - Build Utilities

=head1 DESCRIPTION

SPVM::Builder::Util is building utilities.

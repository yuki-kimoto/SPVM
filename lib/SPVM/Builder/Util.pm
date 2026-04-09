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
use SPVM::Builder::Config;
use Encode 'decode';
use File::Find 'find';
use Time::HiRes ();
use Digest::SHA 'sha1_hex';
use Fcntl qw(:flock);

# SPVM::Builder::Util is used from Makefile.PL
# so this class must be wrote as pure perl. Do not contain XS functions.

sub get_spvm_header_files {
  my $builder_dir = &get_builder_dir;
  
  my $include_dir = "$builder_dir/include";
  
  # Get all .h files in the include directory
  my @spvm_header_files = glob("$include_dir/*.h");
  
  unless (@spvm_header_files) {
    confess("The SPVM header files are not found in the directory '$include_dir'.");
  }
  
  return \@spvm_header_files;
}

sub get_spvm_precompile_source_files {
  my $builder_dir = &get_builder_dir;
  
  my $src_dir = "$builder_dir/src";
  
  # Specify the required source files
  my @filenames = (
    'spvm_precompile.c',
    'spvm_string_buffer.c',
  );
  
  my @spvm_precompile_source_files;
  for my $filename (@filenames) {
    my $file = "$src_dir/$filename";
    if (-f $file) {
      push @spvm_precompile_source_files, $file;
    }
    else {
      confess("The SPVM precompile source file '$file' is not found.");
    }
  }
  
  return \@spvm_precompile_source_files;
}

sub get_spvm_core_source_file_names {
  
  my @spvm_core_source_file_names = qw(
    spvm_allocator.c
    spvm_allow.c
    spvm_api_allocator.c
    spvm_api_arg.c
    spvm_api_basic_type.c
    spvm_api.c
    spvm_api_class_file.c
    spvm_api_class_var.c
    spvm_api_compiler.c
    spvm_api_field.c
    spvm_api_internal.c
    spvm_api_method.c
    spvm_api_mutex.c
    spvm_api_runtime.c
    spvm_api_string_buffer.c
    spvm_api_type.c
    spvm_array_field_access.c
    spvm_attribute.c
    spvm_basic_type.c
    spvm_block.c
    spvm_call_method.c
    spvm_case_info.c
    spvm_check.c
    spvm_class_file.c
    spvm_class_var_access.c
    spvm_class_var.c
    spvm_compiler.c
    spvm_constant.c
    spvm_dumper.c
    spvm_field_access.c
    spvm_field.c
    spvm_hash.c
    spvm_interface.c
    spvm_list.c
    spvm_method.c
    spvm_mutex.c
    spvm_op.c
    spvm_opcode_builder.c
    spvm_opcode.c
    spvm_opcode_list.c
    spvm_precompile.c
    spvm_precompile_header_content.c
    spvm_runtime.c
    spvm_strerror.c
    spvm_string_buffer.c
    spvm_string.c
    spvm_switch_info.c
    spvm_toke.c
    spvm_type.c
    spvm_use.c
    spvm_utf8.c
    spvm_var.c
    spvm_var_decl.c
    spvm_version_from.c
    spvm_vm.c
    spvm_yacc.c
    spvm_yacc_util.c
  );

  return \@spvm_core_source_file_names;
}

sub slurp_binary {
  my ($file) = @_;
  
  open my $fh, '<', $file
    or confess("Can't open file '$file':$!");
    
  my $content = do { local $/; <$fh> };
  
  return $content;
}

sub slurp_utf8 {
  my ($file) = @_;
  
  my $content = &slurp_binary($file);
  
  $content = decode('UTF-8', $content);
  
  return $content;
}

sub file_contains {
  my ($file, $string) = @_;
  
  my $content = &slurp_utf8($file);
  
  my $contains;
  if (index($content, $string) >= 0) {
    $contains = 1;
  }
  
  return $contains;
}

sub spurt_binary {
  my ($file, $content) = @_;
  
  unless (defined $file) {
    confess("A file must be defined.");
  }
  
  mkpath dirname $file;
  
  open my $fh, '>:raw', $file
    or confess("Can't open file '$file':$!");
    
  print $fh $content;
}

sub spurt_binary_parallel_safe {
  my ($file, $content) = @_;

  unless (defined $file) {
    confess("A file must be defined.");
  }

  # Ensure the directory exists
  mkpath dirname $file;

  # Lock the output file during the operation
  &lock_output_file($file, sub {
    # If the file exists, check if the content is different
    if (-f $file) {
      open my $fh_read, '<:raw', $file
        or confess("Can't open file '$file' for reading: $!");
      my $current_content = do { local $/; <$fh_read> };
      close $fh_read;

      # If the content is exactly the same, do nothing and return
      return if $current_content eq $content;
    }

    # Write the new content if the file doesn't exist or content is different
    open my $fh_write, '>:raw', $file
      or confess("Can't open file '$file' for writing: $!");
    print $fh_write $content;
    close $fh_write;
  });
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
  
  pod2usage -exitval => 'noexit', -input => $file, -output => $handle, -verbose => 99, -sections => "Usage";
  $output =~ s/^.*\n|\n$//;
  $output =~ s/\n$//;

  return SPVM::Builder::Util::unindent($output);
}

sub getopt {
  my ($array, $opts) = map { ref $_[0] eq 'ARRAY' ? shift : $_ } \@ARGV, [];
  my $save = Getopt::Long::Configure(qw(default no_auto_abbrev no_ignore_case),
    @$opts);
  my $success = GetOptionsFromArray $array, @_;
  Getopt::Long::Configure($save);
  
  unless ($success) {
    Carp::confess("Failed to parse command line options.");
  }
}

sub convert_class_file_to_dynamic_lib_file {
  my ($class_file, $category) = @_;
  
  my $dlext = $Config{dlext};
  $class_file =~ s/\.[^.]+$//;
  my $dynamic_lib_category_file = $class_file;
  $dynamic_lib_category_file .= $category eq 'native' ? ".$dlext" : ".$category.$dlext";
  
  return $dynamic_lib_category_file;
}

sub convert_class_name_to_dynamic_lib_rel_file {
  my ($class_name, $category) = @_;
  
  my $dlext = $Config{dlext};
  my $dynamic_lib_category_rel_file = &convert_class_name_to_rel_file($class_name);
  $dynamic_lib_category_rel_file .= $category eq 'native' ? ".$dlext" : ".$category.$dlext";
  
  return $dynamic_lib_category_rel_file;
}

sub convert_class_name_to_category_rel_file {
  my ($class_name, $category, $ext) = @_;
  
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
  
  my $rel_dir;
  my $rel_file = "SPVM::$class_name";
  $rel_file =~ s/::/\//g;
  $rel_dir = dirname $rel_file;
  
  return $rel_dir;
}

sub convert_class_name_to_rel_file {
  my ($class_name, $ext) = @_;
  
  my $rel_file_with_ext = "SPVM::$class_name";
  $rel_file_with_ext =~ s/::/\//g;
  
  if (defined $ext) {
    $rel_file_with_ext .= ".$ext";
  }
  
  return $rel_file_with_ext;
}

sub get_class_base_dir {
  my ($file, $class_name) = @_;
  
  $file =~ s/\.spvm$//;
  my $class_file = "SPVM::$class_name";
  $class_file =~ s/::/\//g;
  $file =~ s/$class_file$//;
  $file =~ s/[\\\/]$//;
  
  return $file;
}

sub create_make_rule_native {
  my $class_name = shift;
  
  create_make_rule($class_name, 'native', @_);
}

sub create_make_rule_precompile {
  my $class_name = shift;
  
  create_make_rule($class_name, 'precompile', @_);
}

sub create_make_rule {
  my ($class_name, $category, $options) = @_;

  $options ||= {};

  if ($category eq 'native') {
    $options->{native_classes} = [$class_name];
  }
  elsif ($category eq 'precompile') {
    $options->{precompile_classes} = [$class_name];
  }

  return create_make_rule_parallel($options);
}

sub create_make_rule_parallel {
  my ($options) = @_;

  $options ||= {};

  my $make_rule = '';

  # Generate a unique target name
  my @target_parts;
  
  # Target identification includes filenames to ensure unique SHA1 when list changes
  if (my $precompile_classes = $options->{precompile_classes}) {
    push @target_parts, map { "precompile|$_" } @$precompile_classes;
  }
  if (my $precompile_classes_file = $options->{precompile_classes_file}) {
    push @target_parts, "precompile_file|$precompile_classes_file";
  }
  if (my $native_classes = $options->{native_classes}) {
    push @target_parts, map { "native|$_" } @$native_classes;
  }
  if (my $native_classes_file = $options->{native_classes_file}) {
    push @target_parts, "native_file|$native_classes_file";
  }
  
  # Create a SHA1 hex digest from sorted parts
  my $target_id = sha1_hex(join("\n", sort @target_parts));
  my $target = "spvm-build-parallel-$target_id";

  # Order-only dependencies
  my $order_only_dependent_files = $options->{order_only_dependent_files} // [];
  my $order_only_str = @$order_only_dependent_files ? " | " . join(' ', @$order_only_dependent_files) : "";

  # Dynamic target
  $make_rule .= "dynamic :: $target\n";
  $make_rule .= "\t\$(NOECHO) \$(NOOP)\n\n";

  # Parallel build rule
  $make_rule .= ".PHONY: $target\n";
  $make_rule .= "$target :$order_only_str\n";

  # Build options
  my $new_options_string = "build_dir => '.spvm_build'";

  my @build_options;
  if (exists $options->{force}) {
    push @build_options, "force => $options->{force}";
  }
  if (defined(my $optimize = $options->{optimize})) {
    push @build_options, "optimize => '$optimize'";
  }
  if (defined(my $jobs = $options->{jobs})) {
    push @build_options, "jobs => $jobs";
  }
  
  # New file-based options
  if (defined(my $native_classes_file = $options->{native_classes_file})) {
    push @build_options, "native_classes_file => '$native_classes_file'";
  }
  if (defined(my $precompile_classes_file = $options->{precompile_classes_file})) {
    push @build_options, "precompile_classes_file => '$precompile_classes_file'";
  }

  # Array-based options
  if (my $native_classes = $options->{native_classes}) {
    push @build_options, "native_classes => [" . join(', ', map { "'$_'" } @$native_classes) . "]";
  }
  if (my $precompile_classes = $options->{precompile_classes}) {
    push @build_options, "precompile_classes => [" . join(', ', map { "'$_'" } @$precompile_classes) . "]";
  }

  my $build_options_hash_str = "{" . join(', ', @build_options) . "}";

  # Build command line
  $make_rule .= "\t$^X -Mblib -MSPVM::Builder::API -e \"SPVM::Builder::API->new($new_options_string)->build_parallel_dynamic_lib_dist($build_options_hash_str)\"\n\n";

  return $make_rule;
}

sub search_config_file {
  my ($class_name, $mode) = @_;
  
  my $ext = 'config';
  if (defined $mode) {
    $ext = "$mode.$ext";
  }
  
  my $config_file_base = SPVM::Builder::Util::convert_class_name_to_rel_file($class_name, $ext);
  my $config_file;
  for my $inc (@INC) {
    my $config_file_tmp = "$inc/$config_file_base";
    if (-f $config_file_tmp) {
      $config_file = $config_file_tmp;
      last;
    }
  }
  
  return $config_file;
}

sub get_builder_dir {
  my $builder_config_dir = $INC{"SPVM/Builder/Config.pm"};
  my $builder_dir = $builder_config_dir;
  $builder_dir =~ s/\/Config\.pm$//;
  return $builder_dir;
}

sub get_dynamic_lib_file_dist {
  my ($class_file, $category) = @_;

  my $dynamic_lib_file = SPVM::Builder::Util::convert_class_file_to_dynamic_lib_file($class_file, $category);
  
  return $dynamic_lib_file;
}

sub create_default_config {
  
  my $config = SPVM::Builder::Config->new_c99;
  
  return $config;
}

sub get_normalized_env {
  my ($name) = @_;
  
  my $value = $ENV{$name};
  
  if (defined $value && !length $value) {
    $value = undef;
  }
  
  return $value;
}

sub get_version_string {
  my ($spvm_class_file) = @_;
  
  open my $spvm_module_fh, '<', $spvm_class_file or die "Can't open the file '$spvm_class_file': $!";
  local $/;
  my $content = <$spvm_module_fh>;
  my $version_string;
  if ($content =~ /\bversion\s*"([\d\._]+)"\s*;/) {
    $version_string = $1;
  }

  unless (defined $version_string) {
    confess("The version string can't be find in $spvm_class_file file");
  }
  
  return $version_string;
}

sub get_spvm_version_string {
  
  my $builder_dir = &get_builder_dir;
  my $spvm_version_header_file = "$builder_dir/include/spvm_version.h";
  
  open my $spvm_module_fh, '<', $spvm_version_header_file
    or die "Can't open the file '$spvm_version_header_file': $!";
  local $/;
  my $content = <$spvm_module_fh>;
  my $version_string;
  if ($content =~ /#define\s+SPVM_NATIVE_VERSION_NUMBER\s* ([\d\._]+)/) {
    $version_string = $1;
  }
  
  unless (defined $version_string) {
    confess("The version string can't be found in '$spvm_version_header_file'");
  }
  
  return $version_string;
}

sub create_dl_func_list {
  my ($class_name, $method_names, $options) = @_;
  
  $options ||= {};
  
  my $category = $options->{category} || '';
  
  # dl_func_list
  # This option is needed Windows DLL file
  my $dl_func_list = [];
  for my $method_name (@$method_names) {
    my $cfunc_name = SPVM::Builder::Util::create_cfunc_name($class_name, $method_name, $category);
    push @$dl_func_list, $cfunc_name;
  }
  
  # This is bad hack to suppress boot strap function error.
  unless (@$dl_func_list) {
    push @$dl_func_list, '';
  }
  
  return $dl_func_list;
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

sub resolve_inc {
  my ($current_inc, $source, $blib, $include_dirs) = @_;
  
  my $include_dirs_by_lib_directive = SPVM::Builder::Util::parse_lib_directive($source, $FindBin::Bin);
  
  # Get blib include directories if $blib is true
  my @blib_include_dirs;
  if ($blib) {
    # Temporarily isolate @INC to get paths from the blib module
    local @INC;
    require blib;
    blib->import;
    @blib_include_dirs = @INC;
  }
  
  # Final include directories
  my @inc = @$current_inc;
  
  # To match Perl's @INC priority (last-in, first-priority),
  # we add paths in reverse order of priority using unshift.
  
  # 3rd priority: include directories from arguments (like -I)
  unshift @inc, @$include_dirs;
  
  # 2nd priority: include directories from blib (like -Mblib)
  unshift @inc, @blib_include_dirs;
  
  # 1st priority: include directories from #lib directives in the source (like use lib)
  unshift @inc, @$include_dirs_by_lib_directive;
  
  # Normalize paths by removing the trailing /SPVM or \SPVM
  @inc = map { my $dir = $_; $dir =~ s/[\\\/]SPVM$//; $dir; } @inc;
  
  return \@inc;
}

sub parse_lib_directive {
  my ($source, $bin) = @_;
  
  my $include_dirs = [];
  
  while ($source =~ /^#lib "([^"]+)"/gm) {
    my $include_dir = $1;
    
    $include_dir =~ s/\$FindBin::Bin/$bin/g;
    
    unshift @$include_dirs, $include_dir;
  }
  
  return $include_dirs;
}

# Create C string literal for MSVC/TCC compatibility
sub create_c_string_literal {
  my ($content) = @_;
  
  return 'NULL' unless defined $content;

  my @chunks;
  my $current_chunk = '';
  my $count = 0;

  {
    use bytes;
    for my $i (0 .. length($content) - 1) {
      my $char = substr($content, $i, 1);
      my $escaped;
      
      # Escape characters
      if ($char eq "\\") { $escaped = "\\\\"; }
      elsif ($char eq "\"") { $escaped = "\\\""; }
      elsif ($char =~ /[[:print:]]/) { $escaped = $char; }
      else { $escaped = sprintf("\\%03o", ord($char)); }

      $current_chunk .= $escaped;
      $count++;

      # Split for MSVC limit
      if ($count >= 100) {
        push @chunks, qq(      "$current_chunk"\n);
        $current_chunk = '';
        $count = 0;
      }
    }
    push @chunks, qq(      "$current_chunk"\n) if length $current_chunk;
  }
  
  return join('', @chunks);
}

sub build_precompile_header_content_c_source {
  my ($options) = @_;
  
  my $builder_dir = &get_builder_dir;
  my $include_dir = "$builder_dir/include";
  my $src_dir = "$builder_dir/src";
  
  my $spvm_native_h = "$include_dir/spvm_native.h";
  my $spvm_implement_h = "$include_dir/spvm_implement.h";
  my $output_file = "$src_dir/spvm_precompile_header_content.c";
  
  # Minimal definitions for standard types and functions
  my $header_content = <<'EOS';
/* Minimal definitions for standard types and functions */
#define NULL ((void*)0)
struct _iobuf;
typedef struct _iobuf FILE;

typedef signed char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

#if defined(__LP64__)
  /* LP64 System (Linux, macOS, etc.) */
  typedef long int64_t;
  typedef unsigned long uint64_t;
  typedef long intptr_t;
  typedef unsigned long size_t;
  #define PRId64 "ld"
#else
  /* LLP64 System (Windows 64-bit) */
  typedef long long int64_t;
  typedef unsigned long long uint64_t;
  typedef long long intptr_t;
  typedef unsigned long long size_t;
  #define PRId64 "lld"
#endif

#define PRId8 "d"
#define PRId16 "d"
#define PRId32 "d"
#define INT8_MIN (-128)
#define INT8_MAX 127
#define INT16_MIN (-32768)
#define INT16_MAX 32767
#define INT32_MIN (-2147483647 - 1)
#define INT32_MAX 2147483647

#define INT64_MIN (-9223372036854775807LL - 1)
#define INT64_MAX 9223372036854775807LL
#define EOF (-1)
EOS

  # Remove the #ifndef SPVM_NATIVE_NO_INCLUDE_HEADERS block
  my $process_header = sub {
    my ($path) = @_;
    my $content = &slurp_binary($path);
    
    # Remove the block including #ifndef and #endif
    $content =~ s/^\s*#ifndef\s+SPVM_NATIVE_NO_INCLUDE_HEADERS.*?#endif//msg;
    
    return $content;
  };

  $header_content .= "\n/* spvm_native.h (headers-stripped) */\n" . $process_header->($spvm_native_h);
  $header_content .= "\n/* spvm_implement.h (headers-stripped) */\n" . $process_header->($spvm_implement_h);

  my $c_string_literal = &create_c_string_literal($header_content);

  my $final_c_source = "/* This file is auto-generated by SPVM::Builder::Util::build_precompile_header_content_c_source */\n";
  $final_c_source .= "static const char* spvm_precompile_header_content = \n$c_string_literal;\n\n";
  $final_c_source .= "const char* get_precompile_header_content() {\n";
  $final_c_source .= "  return spvm_precompile_header_content;\n";
  $final_c_source .= "}\n";

  # Check if the content is completely identical
  my $old_content = -f $output_file ? &slurp_binary($output_file) : "";
  
  if ($old_content ne $final_c_source) {
    &spurt_binary($output_file, $final_c_source);
    warn "Generated \"$output_file\".\n";
  }

  return $output_file;
}

sub get_cpu_count {
  my $cpu_count;

  if ($^O eq 'MSWin32') {
    # Windows
    $cpu_count = $ENV{NUMBER_OF_PROCESSORS} || 1;
  }
  else {
    # Linux / Unix / macOS
    # (Comment: Using nproc is the most reliable way on modern Linux)
    my $nproc = `nproc 2>/dev/null`;
    if ($nproc) {
      $cpu_count = int($nproc);
    }
    else {
      # (Comment: Fallback to /proc/cpuinfo or sysctl)
      my $cpuinfo = `grep -c ^processor /proc/cpuinfo 2>/dev/null`;
      if ($cpuinfo) {
        $cpu_count = int($cpuinfo);
      }
      else {
        my $sysctl = `sysctl -n hw.ncpu 2>/dev/null`;
        $cpu_count = $sysctl ? int($sysctl) : 1;
      }
    }
  }

  return $cpu_count;
}

sub check_option_names {
  my ($options, $available_option_names) = @_;
  
  # Check if options exists
  unless ($options) {
    return;
  }
  
  # Create a hash for fast lookup
  my $available_option_names_h = {};
  for my $available_option_name (@$available_option_names) {
    $available_option_names_h->{$available_option_name} = 1;
  }
  
  # Validate each option name (Iterate through hash keys)
  for my $option_name (keys %$options) {
    # Check if the option name is available
    unless ($available_option_names_h->{$option_name}) {
      Carp::confess("'$option_name' option is not available.");
    }
  }
}

sub normalize_path {
  my ($path, $base_dir) = @_;
  
  unless (defined $path) {
    confess("The path \$path must be defined.");
  }
  
  unless (defined $base_dir) {
    confess("The base directory \$base_dir must be defined.");
  }
  
  my $abs_path = File::Spec->rel2abs($path);
  my $abs_base_dir = File::Spec->rel2abs($base_dir);
  
  my $normalized_path = File::Spec->abs2rel($abs_path, $abs_base_dir);
  $normalized_path =~ s|\\|/|g;
  
  return $normalized_path;
}

sub quote_literal {
  my ($string) = @_;

  if ($^O eq 'MSWin32') {
    if (length $string && $string !~ /[ \t\n\x0b"|<>%]/) {
      return $string;
    }

    $string =~ s{(\\*)(?="|\z)}{$1$1}g;
    $string =~ s{"}{\\"}g;
    
    my $quoted_string = qq{"$string"};
    
    return $quoted_string;
  }
  else {
    if (length $string && $string !~ /[^a-zA-Z0-9,._+@%\/-]/) {
      return $string;
    }

    $string =~ s{'}{'\\''}g;
    
    my $quoted_string = "'$string'";
    
    return $quoted_string;
  }
}

sub lock_output_file {
  my ($output_file, $cb) = @_;
  
  my $output_dir = dirname($output_file);
  my $lock_file = "$output_dir/" . sha1_hex($output_file) . ".lock";
  
  open my $lock_fh, '>>', $lock_file
    or die "Can't open lock file $lock_file: $!";
  
  # Exclusive lock
  flock($lock_fh, LOCK_EX)
    or die "Can't get lock on $lock_file: $!";
  
  my $error;
  eval {
    $cb->();
  };
  $error = $@;
  
  # Always unlock
  flock($lock_fh, LOCK_UN);
  
  if ($error) {
    die $error;
  }
}

1;

=head1 Name

SPVM::Builder::Util - Builder Utilities

=head1 Description

The SPVM::Builder::Util class has utility functions for L<SPVM::Builder> class.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

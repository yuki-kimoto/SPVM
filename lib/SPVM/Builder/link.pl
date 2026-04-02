use strict;
use warnings;
use ExtUtils::CBuilder;
use SPVM::Builder::Util;
use File::Copy;

# Get arguments
my ($command_tmp_dir, $ld_cmd_heading, $ld_cmd_string, $output_file, $class_name, $hint_cc, $output_type, $ld, $dl_func_list_file, $object_file_names_file, $ldflags_file) = @ARGV;

# Read dl_func_list
my $dl_func_list;
if (-f $dl_func_list_file) {
  my $content = SPVM::Builder::Util::slurp_binary($dl_func_list_file);
  $dl_func_list = [split(/\n/, $content)];
} else {
  warn "Warning: dl_func_list_file '$dl_func_list_file' not found.";
}

# Read object_file_names
my @object_file_names;
if (-f $object_file_names_file) {
  my $content = SPVM::Builder::Util::slurp_binary($object_file_names_file);
  @object_file_names = split(/\n/, $content);
} else {
  warn "Warning: object_file_names_file '$object_file_names_file' not found.";
}

# Read ldflags
my @ldflags;
if (-f $ldflags_file) {
  my $content = SPVM::Builder::Util::slurp_binary($ldflags_file);
  @ldflags = split(/\n/, $content);
} else {
  warn "Warning: ldflags_file '$ldflags_file' not found.";
}

# Define log file paths
my $log_stdout = "$command_tmp_dir/stdout.log";
my $log_stderr = "$command_tmp_dir/stderr.log";

# Redirect stdout and stderr to log files
open(STDOUT, '>', $log_stdout) or warn "Can't open $log_stdout: $!";
open(STDERR, '>', $log_stderr) or warn "Can't open $log_stderr: $!";

# Print command information
print "$ld_cmd_heading\n";
print "$ld_cmd_string\n";

# Configure CBuilder
my $cbuilder_config = {
  cc => $hint_cc,
  ld => $ld,
  lddlflags => '',
  shrpenv => '',
  libpth => '',
  libperl => '',
  perllibs => '-lm'
};
my $cbuilder = ExtUtils::CBuilder->new(quiet => 1, config => $cbuilder_config);

# Determine link method and output option
my $link_method = ($output_type eq 'exe') ? 'link_executable' : 'link';
my $output_option = ($output_type eq 'exe') ? 'exe_file' : 'lib_file';

# Run linker
my @link_temporary_files;
(undef, @link_temporary_files) = $cbuilder->$link_method(
  $output_option => $output_file,
  objects => \@object_file_names,
  extra_linker_flags => "@ldflags",
  module_name => $class_name,
  dl_func_list => $dl_func_list,
);

# Backup temporary files
for my $tmp_file (@link_temporary_files) {
  $tmp_file =~ s/^"//;
  $tmp_file =~ s/"$//;
  if (-f $tmp_file) {
    my $extension = ($tmp_file =~ /\.([^\.]+)$/) ? $1 : 'tmp';
    File::Copy::copy($tmp_file, "$command_tmp_dir/link_temporary_file.$extension");
  }
}

exit(0);

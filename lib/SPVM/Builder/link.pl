use strict;
use warnings;
use ExtUtils::CBuilder;
use File::Copy ();
use Fcntl qw(:flock :seek);
use Digest::SHA qw(sha1_hex);
use File::Basename qw(dirname);

# Get arguments
my ($command_tmp_dir, $ld_command_heading, $ld_command_string, $output_file, $class_name, $hint_cc, $output_type, $ld, $dl_func_list_file, $object_file_names_file, $ldflags_file) = @ARGV;

# Function to read file content (replaces slurp_binary)
sub read_file {
  my ($file) = @_;
  return undef unless -f $file;
  open my $fh, '<', $file
    or die "Can't open $file: $!";
  binmode $fh;
  local $/;
  return <$fh>;
}

# Read dl_func_list
my $dl_func_list;
if (my $content = read_file($dl_func_list_file)) {
  $dl_func_list = [split(/\n/, $content)];
}

# Read object_file_names
my @object_file_names;
if (my $content = read_file($object_file_names_file)) {
  @object_file_names = split(/\n/, $content);
}

# Read ldflags
my @ldflags;
if (my $content = read_file($ldflags_file)) {
  @ldflags = split(/\n/, $content);
}

# Define log file paths
my $log_stdout = "$command_tmp_dir/stdout.log";
my $log_stderr = "$command_tmp_dir/stderr.log";

# Redirect stdout and stderr to log files
open(STDOUT, '>', $log_stdout)
  or warn "Can't open $log_stdout: $!";
open(STDERR, '>', $log_stderr)
  or warn "Can't open $log_stderr: $!";

# Print command information
print "$ld_command_heading\n";
print "$ld_command_string\n";

# File locking
my $output_dir = dirname($output_file);
my $lock_file = "$output_dir/" . sha1_hex($output_file) . ".lock";
open my $lock_fh, '>>', $lock_file
  or warn "Can't open lock file $lock_file: $!";
flock($lock_fh, LOCK_EX)
  or warn "Can't get lock on $lock_file: $!";

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

# File unlocking
flock($lock_fh, LOCK_UN)
  or warn "Can't unlock $lock_file: $!";

exit(0);

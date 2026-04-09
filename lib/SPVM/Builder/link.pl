use strict;
use warnings;
use ExtUtils::CBuilder;
use File::Copy ();
use Fcntl qw(:flock :seek);
use Digest::SHA qw(sha1_hex);
use File::Basename 'dirname', 'basename';
use MIME::Base64 qw(decode_base64);
use File::Spec;

# Get arguments
my @argv = split("\0", decode_base64($ARGV[0]));
my ($command_tmp_dir, $output_file, $class_name, $hint_cc, $output_type, $ld, $dl_func_list_file, $object_file_names_file, $ldflags_file) = @argv;

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
my $log_stderr = "$command_tmp_dir/stderr.log";

# Redirect stdout and stderr to log files
open(STDOUT, '>', File::Spec->devnull)
  or warn "Can't open null device: $!";
open(STDERR, '>', $log_stderr)
  or warn "Can't open $log_stderr: $!";

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
my @link_tmp_files;
my $error;

my $tmp_output_file = "$command_tmp_dir/link.output";

# Link to the .tmp file instead of the final file
(undef, @link_tmp_files) = $cbuilder->$link_method(
  $output_option => $tmp_output_file,
  objects => \@object_file_names,
  extra_linker_flags => "@ldflags",
  module_name => $class_name,
  dl_func_list => $dl_func_list,
);

# Rename (Move) the temporary file to the final output file
# In Windows, if $output_file already exists and is being used, move may fail.
# But it's generally safer than flock-based contention during long writes.
File::Copy::move($tmp_output_file, $output_file)
  or die "Can't move $tmp_output_file to $output_file: $!";

# Backup temporary files
for my $tmp_file (@link_tmp_files) {
  if (-f $tmp_file) {
    my $to_file = "$command_tmp_dir/" . basename $tmp_file;
    File::Copy::copy($tmp_file, $to_file)
      or warn("Cannot copy '$tmp_file' to '$to_file'.");
  }
}

exit(0);

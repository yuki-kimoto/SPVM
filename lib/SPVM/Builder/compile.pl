use strict;
use warnings;
use Fcntl qw(:flock);
use Digest::SHA qw(sha1_hex);
use File::Basename 'dirname', 'basename';
use MIME::Base64 qw(decode_base64);
use File::Spec;
use File::Copy ();

# Get arguments
my @argv = split("\0", decode_base64($ARGV[0]));
my ($command_tmp_dir, $output_file, @cc_cmd) = @argv;

# Define log file paths
my $log_stderr = "$command_tmp_dir/stderr.log";

# Redirect stdout and stderr to log files
open(STDOUT, '>', File::Spec->devnull)
  or warn "Can't open null device: $!";
open(STDERR, '>', $log_stderr)
  or warn "Can't open $log_stderr: $!";

my $tmp_output_file = "$command_tmp_dir/compile.output";
$cc_cmd[-1] .= $tmp_output_file;

# Execute the command
my $exit_status;
system(@cc_cmd);
$exit_status = $? >> 8;

# Rename (Move) the temporary file to the final output file
# In Windows, if $output_file already exists and is being used, move may fail.
# But it's generally safer than flock-based contention during long writes.
File::Copy::move($tmp_output_file, $output_file)
  or die "Can't move $tmp_output_file to $output_file: $!";

# Exit with the command's exit status
exit($exit_status);


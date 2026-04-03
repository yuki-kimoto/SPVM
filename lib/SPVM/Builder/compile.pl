use strict;
use warnings;
use Fcntl qw(:flock);
use Digest::SHA qw(sha1_hex);
use File::Basename qw(dirname);

# Get arguments
my ($output_file, $command_tmp_dir, $cc_command_heading, $cc_command_string, @cc_cmd) = @ARGV;

# Define log file paths
my $log_stdout = "$command_tmp_dir/stdout.log";
my $log_stderr = "$command_tmp_dir/stderr.log";

# Redirect stdout and stderr to log files
open(STDOUT, '>', $log_stdout)
  or warn "Can't open $log_stdout: $!";
open(STDERR, '>', $log_stderr)
  or warn "Can't open $log_stderr: $!";

# Print command information
print "$cc_command_heading\n";
print "$cc_command_string\n";

# File locking
my $output_dir = dirname($output_file);
my $lock_file = "$output_dir/" . sha1_hex($output_file) . ".lock";
open my $lock_fh, '>>', $lock_file
  or warn "Can't open lock file $lock_file: $!";
flock($lock_fh, LOCK_EX)
  or warn "Can't get lock on $lock_file: $!";

# Execute the command
system(@cc_cmd);

# File unlocking
flock($lock_fh, LOCK_UN)
  or warn "Can't unlock $lock_file: $!";

# Exit with the command's exit status
exit($? >> 8);

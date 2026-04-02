use strict;
use warnings;

# Get arguments
my ($command_tmp_dir, $cc_cmd_heading, $cc_cmd_string, @cc_cmd) = @ARGV;

# Define log file paths
my $log_stdout = "$command_tmp_dir/stdout.log";
my $log_stderr = "$command_tmp_dir/stderr.log";

# Redirect stdout and stderr to log files
open(STDOUT, '>', $log_stdout)
  or warn "Can't open $log_stdout: $!";
open(STDERR, '>', $log_stderr)
  or warn "Can't open $log_stderr: $!";

# Print command information
print "$cc_cmd_heading\n";
print "$cc_cmd_string\n";

# Execute the command
system(@cc_cmd);

# Exit with the command's exit status
exit($? >> 8);

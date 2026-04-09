use strict;
use warnings;
use Fcntl qw(:flock);
use Digest::SHA qw(sha1_hex);
use File::Basename qw(dirname);
use MIME::Base64 qw(decode_base64);
use File::Spec;

# Get arguments
my @argv = split("\0", decode_base64($ARGV[0]));
my ($command_tmp_dir, $output_file, @cc_cmd) = @argv;

# Define log file paths
my $log_stdout = "$command_tmp_dir/stdout.log";
my $log_stderr = "$command_tmp_dir/stderr.log";

# Redirect stdout and stderr to log files
open(STDOUT, '>', File::Spec->devnull)
  or warn "Can't open null device: $!";
open(STDERR, '>', $log_stderr)
  or warn "Can't open $log_stderr: $!";

# File locking
my $output_dir = dirname($output_file);
my $lock_file = "$output_dir/" . sha1_hex($output_file) . ".lock";
open my $lock_fh, '>>', $lock_file
  or warn "Can't open lock file $lock_file: $!";
flock($lock_fh, LOCK_EX)
  or warn "Can't get lock on $lock_file: $!";

# Execute the command
my $exit_status;
&lock_output_file($output_file, sub {
  system(@cc_cmd);
  $exit_status = $? >> 8;
});

# Exit with the command's exit status
exit($exit_status);

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

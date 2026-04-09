use strict;
use warnings;
use Fcntl qw(:flock);
use Digest::SHA qw(sha1_hex);
use File::Basename 'dirname', 'basename';
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

# Execute the command
my $exit_status;
&lock_output_file($output_file, sub {
  system(@cc_cmd);
  $exit_status = $? >> 8;
});

# Exit with the command's exit status
exit($exit_status);

# Copied from SPVM::Builder::Util#lock_output_file
sub lock_output_file {
  my ($output_file, $cb) = @_;
  
  # Get the base filename (e.g., "myapp.o" or "bootstrap.c")
  my $base_name = basename($output_file);
  my $output_dir = dirname($output_file);
  
  # Create lock file path: [dir]/[base_name].lock
  my $lock_file = "$output_dir/$base_name.lock";
  
  open my $lock_fh, '>>', $lock_file
    or die "Can't open lock file $lock_file: $!";
  
  # Exclusive lock (Wait if another process is writing)
  flock($lock_fh, LOCK_EX)
    or die "Can't get lock on $lock_file: $!";
  
  my $error;
  eval {
    $cb->();
  };
  $error = $@;
  
  # Unlock (flock will also be released when $lock_fh is closed or process exits)
  flock($lock_fh, LOCK_UN);
  
  if ($error) {
    die $error;
  }
}

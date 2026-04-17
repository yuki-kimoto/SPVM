use strict;
use warnings;
use MIME::Base64 qw(decode_base64);
use File::Copy ();

# Get arguments
my @argv = split("\0", decode_base64($ARGV[0]));
my ($command_tmp_dir, $output_file, @cc_cmd) = @argv;

# Define log file paths
my $log_stdout = "$command_tmp_dir/stdout.log";
my $log_stderr = "$command_tmp_dir/stderr.log";

# Redirect stdout and stderr to log files
open(STDOUT, '>', $log_stdout)
  or die "Can't open file '$log_stdout': $!";
open(STDERR, '>', $log_stderr)
  or die "Can't open file '$log_stderr': $!";

my $tmp_output_file = "$command_tmp_dir/compile.output";
$cc_cmd[-1] .= $tmp_output_file;

# Execute the command
my $system_status = system(@cc_cmd);

if ($system_status == -1) {
  die "Failed to execute compilation command. \$!=$!, \@cc_cmd='@cc_cmd'";
}
elsif ($system_status & 127) {
  my $signal = $system_status & 127;
  die "Compilation command died with signal. \$signal=$signal, \@cc_cmd='@cc_cmd'";
}
else {
  my $exit_status = $system_status >> 8;
  if ($exit_status != 0) {
    die "Compilation command failed with exit code. \$exit_status=$exit_status, \@cc_cmd='@cc_cmd'";
  }
}

# Try to move the temporary file to the output file.
# This logic is used in SPVM::Builder::Util::spurt_binary_parallel_safe, compile.pl and link.pl
unless (File::Copy::move($tmp_output_file, $output_file)) {
  my $errno = $!;
  
  # On Windows, if the destination file is already opened by another process (like gcc),
  # move fails with "Permission denied" (EACCES).
  # In this case, we can safely ignore the error because the content is guaranteed to be the same by SHA-1.
  if ($^O eq 'MSWin32' && $errno == Errno::EACCES()) {
    warn "Warning: Can't move '$tmp_output_file' to '$output_file': $!. This error is ignored because the output file already exists and its content is expected to be the same.";
  }
  else {
    confess("Can't move '$tmp_output_file' to '$output_file': $!");
  }
}

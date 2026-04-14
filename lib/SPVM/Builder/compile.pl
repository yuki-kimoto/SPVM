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

# Rename (Move) the temporary file to the final output file
File::Copy::move($tmp_output_file, $output_file)
  or die "Can't move $tmp_output_file to $output_file: $!";

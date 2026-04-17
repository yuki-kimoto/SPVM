use strict;
use warnings;
use MIME::Base64 qw(decode_base64);
use File::Copy ();
use File::Path 'mkpath';
use File::Basename 'basename', 'dirname';

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

mkpath dirname $output_file;

File::Copy::move($tmp_output_file, $output_file)
  or confess("Can't move '$tmp_output_file' to '$output_file': $!");

package SPVM::Builder::Ninja;

use strict;
use warnings;

sub add_ninja_log {
  my ($dir_name, $new_record_h, $ninja_log_entries_h) = @_;

  my $output_file  = $new_record_h->{output_file};
  my $command_hash = $new_record_h->{command_hash};

  # Update the global hash in memory
  $ninja_log_entries_h->{$output_file} = $new_record_h;

  my $log_file = "$dir_name/.ninja_log";
  my $must_write_header = !-f $log_file;

  open my $fh, '>>', $log_file or die "Can't open $log_file for appending: $!";
  
  # Use binary mode to ensure \x0A is not translated to \r\n on Windows
  binmode $fh;
  
  # Define LF as a physical byte 0x0A
  my $LF = "\x0A";

  # Write the Ninja log version header
  if ($must_write_header) {
    print $fh "# ninja log v5$LF";
  }

  my $start_time = $new_record_h->{start_time} || 0;
  my $end_time   = $new_record_h->{end_time}   || 0;
  my $mtime      = $new_record_h->{mtime}      || 0;

  # Format the log entry and ensure it ends with a physical LF
  my $record = sprintf("%d\t%d\t%d\t%s\t%s$LF", 
    $start_time, 
    $end_time, 
    $mtime, 
    $output_file, 
    $command_hash);
    
  print $fh $record;

  close $fh;
}

1;

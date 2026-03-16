package SPVM::Builder::Ninja;

# SPVM::Builder::Ninja is used from Makefile.PL
# so this class must be wrote as pure perl. Do not contain XS functions.

use strict;
use warnings;

sub new {
  my $class = shift;
  
  my $self = {
    dir => undef,
    ninja_log_entries_h => {},
  };
  
  return bless $self, ref $class || $class;
}

sub dir {
  my $self = shift;
  if (@_) {
    $self->{dir} = $_[0];
    return $self;
  }
  else {
    return $self->{dir};
  }
}

sub ninja_log_entries_h {
  my $self = shift;
  if (@_) {
    $self->{ninja_log_entries_h} = $_[0];
    return $self;
  }
  else {
    return $self->{ninja_log_entries_h};
  }
}

sub add_ninja_log {
  my ($self, $new_record_h) = @_;

  my $dir_name = $self->dir;
  my $ninja_log_entries_h = $self->ninja_log_entries_h;

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

sub load_ninja_log {
  my ($self) = @_;

  my $dir_name = $self->dir;
  my $log_file = "$dir_name/.ninja_log";
  my $ninja_log_entries_h = {};

  # Return an empty hash if the log file does not exist
  if (!-f $log_file) {
    $self->ninja_log_entries_h($ninja_log_entries_h);
    return $ninja_log_entries_h;
  }

  open my $fh, '<', $log_file or die "Can't open $log_file for reading: $!";
  
  # Use binary mode to handle physical LF (0x0A) consistently across platforms
  binmode $fh;

  while (my $line = <$fh>) {
    # Remove the physical LF (0x0A) and optional CR (0x0D) just in case
    $line =~ s/[\x0A\x0D]+$//;

    # Skip the Ninja version header (e.g., "# ninja log v5")
    next if $line =~ /^#/;

    # Parse tab-separated values
    my @fields = split(/\t/, $line);

    if (@fields >= 5) {
      my ($start_time, $end_time, $mtime, $output_file, $command_hash) = @fields;

      # Store the record.
      $ninja_log_entries_h->{$output_file} = {
        start_time   => $start_time,
        end_time     => $end_time,
        mtime        => $mtime,
        output_file  => $output_file,
        command_hash => $command_hash,
      };
    }
  }

  close $fh;

  # Update internal state
  $self->ninja_log_entries_h($ninja_log_entries_h);

  return $ninja_log_entries_h;
}

1;
package SPVM::Builder::CommandInfo;

use strict;
use warnings;

use Carp 'confess';
use SPVM::Builder::Accessor 'has';

# Fields
has [qw(
  config
  output_file
  command_hash
  start_time
  end_time
  log_dir
)];

# Instance Methods
sub create_command { confess('Not implemented.') }

sub to_command {
  my ($self, $options) = @_;

  my $compile_command = $self->create_command($options);
  
  my @quoted_parts;
  for my $part (@$compile_command) {
    push @quoted_parts, $self->_quote_literal($part);
  }
  
  my $compile_command_string = join(' ', @quoted_parts);
  
  return $compile_command_string;
}

sub _quote_literal {
  my ($self, $string) = @_;

  if ($^O eq 'MSWin32') {
    if (length $string && $string !~ /[ \t\n\x0b"|<>%]/) {
      return $string;
    }

    $string =~ s{(\\*)(?="|\z)}{$1$1}g;
    $string =~ s{"}{\\"}g;

    return qq{"$string"};
  }
  else {
    if (length $string && $string !~ /[^a-zA-Z0-9,._+@%\/-]/) {
      return $string;
    }

    $string =~ s{'}{'\\''}g;

    return "'$string'";
  }
}

1;

=head1 Name

SPVM::Builder::CommandInfo - Command Information

=head1 Description

The SPVM::Builder::CommandInfo class has methods to manipulate Command information.

=head1 Fields

=head2 config

  my $config = $command_info->config;
  $command_info->config($config);

Gets and sets the C<config> field, a L<SPVM::Builder::Config> object.

=head2 output_file

  my $output_file = $command_info->output_file;
  $command_info->output_file($output_file);

Gets and sets the C<output_file> field, an output file.

=head2 command_hash

  my $command_hash = $command_info->command_hash;
  $command_info->command_hash($command_hash);

Gets and sets the C<command_hash> field, a SHA-1 hash string that uniquely identifies the compilation task.

This hash ensures the consistency of the compilation. It is generated from the following information:

=over 2

=item * The compilation command itself.

=item * The Command version.

=item * The SPVM version-specific headers.

=item * The information of the dependent files.

=back

If any of these change, the hash will change, triggering a re-compilation in the C<ninja> build system.

=head2 start_time

  my $start_time = $command_info->start_time;
  $command_info->start_time($start_time);

Gets and sets the C<start_time> field. It is a Unix timestamp in milliseconds when the command execution started.

=head2 end_time

  my $end_time = $command_info->end_time;
  $command_info->end_time($end_time);

Gets and sets the C<end_time> field. It is a Unix timestamp in milliseconds when the command execution ended.

=head2 log_dir

  my $log_dir = $command_info->log_dir;
  $command_info->log_dir($log_dir);

Gets and sets the C<log_dir> field. It is a directory where the stdout and stderr log files of the command are stored.

=head1 Instance Methods

=head2 create_command

  my $compile_command = $compile_info->create_command;

Creates an array reference of the command conponents, and returns it.

This method is meant to be implemented in child classes.

=head2 to_command

  my $compile_command_string = $compile_info->to_command;

Converts the array reference of the compilation command returned by the L</"create_command"> method into a single string that can be executed in a shell (such as C<sh> or C<bash>) or the Windows Command Prompt (C<cmd.exe>).

Each argument is automatically and appropriately quoted only when necessary (e.g., containing spaces or special characters) according to the operating system (OS) to ensure it can be safely executed as a command line.

Return Value Examples:

=over 2

=item * On UNIX/Linux (Only strings with special characters like C<=> or spaces are quoted):

  gcc -c -o foo.o -O2 '-std=c99' -Ipath/include foo.c

=item * On Windows (Only strings with characters like spaces or C<"> are quoted):

  gcc -c -o foo.o -O2 -std=c99 -Ipath/include foo.c

=back

=cut

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

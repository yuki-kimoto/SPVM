package SPVM::Builder::CommandInfo;

use strict;
use warnings;

use Carp 'confess';
use SPVM::Builder::Accessor 'has';
use SPVM::Builder::Util;

# Fields
has [qw(
  config
  output_file
  command_hash
  start_time
  end_time
  tmp_dir
  process_id
)];

# Instance Methods
sub create_command { confess('Not implemented.') }

sub create_command_string {
  my ($self, $options) = @_;

  my $compile_command = $self->create_command($options);
  
  my @quoted_parts;
  for my $part (@$compile_command) {
    push @quoted_parts, SPVM::Builder::Util::quote_literal($part);
  }
  
  my $compile_command_string = join(' ', @quoted_parts);
  
  return $compile_command_string;
}

1;

=head1 Name

SPVM::Builder::CommandInfo - Command Information

=head1 Description

SPVM::Builder::CommandInfo class manages command information.

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

=head2 tmp_dir

  my $tmp_dir = $command_info->tmp_dir;
  $command_info->tmp_dir($tmp_dir);

Gets and sets the C<tmp_dir> field. It is a directory where the stderr log file and other temporary files of the command are stored.

=head2 process_id

  my $process_id = $command_info->process_id;
  $command_info->process_id($process_id);

Gets and sets the C<process_id> field. It is the process ID of the command.

=head1 Instance Methods

=head2 create_command

  my $command = $command_info->create_command;
  my $command_no_output = $command_info->create_command({no_output_option => 1});

Creates an array reference of the command components, and returns it.

If the C<no_output_option> option is a true value, the output option (e.g. C<-o output_file>) is not added to the command.

This method is meant to be implemented in child classes.

=head2 create_command_string

  my $command_string = $command_info->create_command_string;
  my $command_string_no_output = $command_info->create_command_string({no_output_option => 1});

Converts the array reference of the command returned by the L</"create_command"> method into a single string that can be executed in a shell (such as C<sh> or C<bash>) or the Windows Command Prompt (C<cmd.exe>).

If the C<no_output_option> option is a true value, this option is passed to the L</"create_command"> method, and the output option is not included in the returned string.

Each argument is automatically and appropriately quoted only when necessary (e.g., containing spaces or special characters) according to the operating system (OS) to ensure it can be safely executed as a command line.

Return Value Examples:

=over 2

=item * On UNIX/Linux:

  gcc -c -o foo.o -O2 '-std=c99' -Ipath/include foo.c

  # With no_output_option => 1
  gcc -c -O2 '-std=c99' -Ipath/include foo.c

=item * On Windows:

  gcc -c -o foo.o -O2 -std=c99 -Ipath/include foo.c

  # With no_output_option => 1
  gcc -c -O2 -std=c99 -Ipath/include foo.c

=back

=head1 Well Knowned Child Classes

=over

=item * L<SPVM::Builder::LinkInfo>

=item * L<SPVM::Builder::CompileInfo>

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

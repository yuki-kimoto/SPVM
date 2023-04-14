package SPVM::Builder::ObjectFileInfo;

use strict;
use warnings;
use Config;
use Carp 'confess';
use File::Basename 'dirname';

use overload bool => sub {1}, '""' => sub { shift->to_string }, fallback => 1;

# Fields
sub file {
  my $self = shift;
  if (@_) {
    $self->{file} = $_[0];
    return $self;
  }
  else {
    return $self->{file};
  }
}

sub compile_info {
  my $self = shift;
  if (@_) {
    $self->{compile_info} = $_[0];
    return $self;
  }
  else {
    return $self->{compile_info};
  }
}

# Class methods
sub new {
  my $class = shift;
  
  my $self = {@_};
  
  bless $self, $class;
  
  return $self;
}

# Instance methods
sub to_string {
  my ($self) = @_;
  
  return $self->file;
}

1;

=head1 Name

SPVM::Builder::ObjectFileInfo - Object File Information

=head1 Description

The SPVM::Builder::ObjectFileInfo class has methods to manipulate information of an object file.

=head1 Fields

=head2 file

  my $file = $object_file_info->file;
  $object_file_info->file($file);

Gets and sets the file name of an object file.

=head2 compile_info

  my $compile_info = $object_file_info->compile_info;
  $object_file_info->compile_info($compile_info);

Gets and sets a L<SPVM::Builder::CompileInfo> object.

=head1 Class Methods

=head2 new

  my $object_file_info = SPVM::Builder::ObjectFileInfo->new(%fields);

Default Field Values:

If a field is not defined, the field is set to the following default value.

=over 2

=item * L</"file">

undef

=item * L</"compile_info">

undef

=back

=head1 Instance Methods

=head2 to_string

  my $object_file_info = $object_file_info->to_string;

Returns the L</"file"> field.

=head1 Operators

Overloads the following operators.

=head2 bool

  my $bool = !!$object_file_info;

Always true.

=head2 stringify

  my $object_file_info_name = "$object_file_info";

Alias for the L</"to_string"> method.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

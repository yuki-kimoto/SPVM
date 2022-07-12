package SPVM::Builder::ObjectFileInfo;

use strict;
use warnings;
use Config;
use Carp 'confess';
use File::Basename 'dirname';

use overload bool => sub {1}, '""' => sub { shift->to_string }, fallback => 1;

# Field methods
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
  
  return $self->compile_info->output_file;
}

1;

=head1 Name

SPVM::Builder::ObjectFileInfo - Object file information

=head1 Description

B<SPVM::Builder::ObjectFileInfo> is a object file information.

=head1 Field Methods

Fields of B<SPVM::Builder::ObjectFileInfo>.

=head2 compile_info

  my $compile_info = $object_file_info->compile_info;
  $object_file_info->compile_info($compile_info);

Get and set the L<SPVM::Builder::CompileInfo> object.

=head1 Class Methods

=head2 new

  my $object_file_info = SPVM::Builder::ObjectFileInfo->new;

=head1 Instance Methods

=head2 to_string

  my $object_file = $object_file_info->to_string;

Get the object file name. This is same as C<$object_file->compile_info->output_file>.

=head1 Operators

L<SPVM::BlessedObject::String> overloads the following operators.

=head2 bool

  my $bool = !!$object_file_info;
  
Always true.

=head2 stringify

  my $object_file_name = "$object_file_info";
  
Alias for L</"to_string">.

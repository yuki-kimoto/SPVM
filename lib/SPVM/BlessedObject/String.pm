package SPVM::BlessedObject::String;

use strict;
use warnings;

use Carp 'confess';

use base 'SPVM::BlessedObject';

use overload bool => sub {1}, '""' => sub { shift->to_string }, fallback => 1;

use SPVM::ExchangeAPI;

sub to_string {
  my $self = shift;
  
  my $string = $self->to_bin;
  
  my $success = utf8::decode($string);
  
  unless ($success) {
    confess "The SPVM::BlessedObject::String object can't be decoded to Perl string";
  }
  
  return $string;
}

sub to_bin { my $ret; eval { $ret =  shift->_xs_to_bin(@_) }; if ($@) { confess $@ } $ret; }

1;

=head1 Name

SPVM::BlessedObject::String - SPVM string

=head1 Description

The object of the C<SPVM::BlessedObject::String> class holds a SPVM string.

=head1 Usage

  my $string = $blessed_object_string->to_string;
  
  my $binary = $blessed_object_string->to_bin;

=head1 Instance Methods

=head2 to_string

  my $string = $blessed_object_string->to_string;

Returns a string decoded to Perl string using L<utf8::decode|https://metacpan.org/pod/utf8>.

If the docoding fails, an exception is thrown.

=head2 to_bin

  my $binary = $blessed_object_string->to_bin;

Returns a string as a binary.

=head1 Operators

Overloads the following operators.

=head2 bool

  my $bool = !!$blessed_object_string;

Always true.

=head2 stringify

  my $string = "$blessed_object_string";

The alias for L</"to_string">.

=head1 Copyright & License

Copyright 2023 Yuki Kimoto. All Rights Reserved.

MIT License.

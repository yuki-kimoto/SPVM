package SPVM::BlessedObject::Array;

use strict;
use warnings;
use Carp 'confess';

use base 'SPVM::BlessedObject';

use overload '@{}' => sub {
  my ($array) = @_;
  
  my $elems = $array->to_elems;
  
  return $elems;
};

use overload fallback => 1;

use SPVM::ExchangeAPI;

sub length { my $ret; eval { $ret =  shift->_xs_length(@_) }; if ($@) { confess $@ } $ret; }

sub to_elems { my $ret; eval { $ret =  shift->_xs_to_elems(@_) }; if ($@) { confess $@ } $ret; }

sub to_strings {
  my $self = shift;
  
  my $elems = $self->to_elems;
  
  my $strings = [map { $_->to_string } @$elems];
  
  return $strings;
}

sub to_bins {
  my $self = shift;
  
  my $elems = $self->to_elems;
  
  my $binaries = [map { $_->to_bin } @$elems];
  
  return $binaries;
}

sub to_bin { my $ret; eval { $ret =  shift->_xs_to_bin(@_) }; if ($@) { confess $@ } $ret; }

sub set { my $ret; eval { $ret =  shift->_xs_set(@_) }; if ($@) { confess $@ } $ret; }

sub get { my $ret; eval { $ret =  shift->_xs_get(@_) }; if ($@) { confess $@ } $ret; }

1;

=head1 Name

SPVM::BlessedObject::Array - SPVM Array

=head2 DESCRIPTION

The object of the C<SPVM::BlessedObject::Array> class holds a SPVM array.

=head1 Usage

  # Gets an element of the array
  my $elem = $blessed_object_array->get(2);
  
  # Sets an element of the array
  $blessed_object_array->set(2 => 5);
  
  # Converts a SPVM array to a Perl array reference
  my $elems = $blessed_object_array->to_elems;
  
  # Converts a SPVM array to a binary
  my $binary = $blessed_object_array->to_bin;

=head1 Methods

=head2 get

  my $elem = $blessed_object_array->get($index);

Returns an element of the array with the index.

=head2 set

  $blessed_object_array->set($index, $elem);

Sets an element of the array with the index.

If the $elem cannnot be assigned to the element of the array, an exception is thrown.

=head2 to_elems

  my $elems = $blessed_object_array->to_elems;

Converts a SPVM array to a Perl array reference and returns it.

=head2 to_bin

  my $binary = $blessed_object_array->to_bin;

Converts a SPVM array to a binary and returns it.

This binary is unpacked by L<unpack|https://perldoc.perl.org/functions/unpack> function.

If the array is an object array, an excetion is thrown.

Examples:

  # byte[]
  my @elems = unpack 'c*', $binary;
  
  # short[]
  my @elems = unpack 's*', $binary;
  
  # int[]
  my @elems = unpack 'l*', $binary;

  # long[]
  my @elems = unpack 'q*', $binary;

  # float[]
  my @elems = unpack 'f*', $binary;

  # double[]
  my @elems = unpack 'd*', $binary;

=head2 to_strings

  my $elems = $blessed_object_array->to_strings;

Converts a SPVM string array to a Perl array reference and returns it.

Each element calls L<to_string|SPVM::BlessedObject::String/"to_string"> method.

=head2 to_bins

  my $elems = $blessed_object_array->to_bins;

Converts a SPVM string array to Perl array reference and returns it.

Each element calls L<to_bin|SPVM::BlessedObject::String/"to_bin"> method.

=head1 Operators

Overloads the following operators.

=head2 array dereference
  
  my @elems = @$array;

This is the same as the following operation.

  my @elems = @{$array->to_elems};

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

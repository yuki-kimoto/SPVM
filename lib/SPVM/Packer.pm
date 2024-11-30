package SPVM::Packer;



1;

=head1 Name

SPVM::Packer - Pack and Unpack Operations

=head1 Description

Packer class in L<SPVM> has methods for pack and unpack operations

=head1 Usage

  use Packer;
  
  my $packer = Packer->new;
  
  my $objects = [(object)1, 2L, 0.5, [1, 2], "abc"];
  
  my $binary = $packer->pack("lqdl2a128");
  
  my $objects_unpack = $packer->unpack($binary);

=head1 Class Methods

C<static method new : Packer ();>

Creates a new L<Packer|SPVM::Packer> object.

=head1 Instance Methods

=head2 pack

C<static method pack : string ($template : string, $objects : object[]);>

Converts the objects $objects to a binary data according to the template $template, and returns it.

Template Syntax:

A template is a string. It consist of specifier parts.

  TEMPLATE := "SpecifierPart1SpecifierPart2SpecifierPartN"

A specifier part is consist of a speficier, an endian, and a length. An endian and a length are optional.

  SpecifierPart := Specifier[Endian][Length]

Here is the list of specifiers.

  [Specifiers]  [Types]              [An output binary in pack or an input binary in unpack]
  a             string               string. It is null padded in pack method.
  
  H             string               A hex string (high nybble first)
  
  c             Byte or byte[]       Singed 8-bit integers
  
  C             Byte or byte[]       Unsinged 8-bit integers
  
  s             Short or short[]     Singed 16-bit integers
  
  S             Short or short[]     Unsinged 16-bit integers
  
  l             Int or int[]         Singed 32-bit integers
  
  L             Int or int[]         Unsinged 32-bit integers
  
  q             Long or long[]       Singed 64-bit integers
  
  Q             Long or long[]       Unsinged 64-bit integers
  
  f             Float or float[]     32-bit floating point numbers.
  
  d             Double or double[]   64-bit floating point numbers.
  
An endian is big-endian C<E<gt>> or little-endian C<E<gt>>.

If big-endian is specified, the binary data is converted from big-endian to system-endian in L</"pack"> method, or from system-endian to big-endian in L</"unpack"> method.

If little-endian is specified, the binary data is converted from little-endian to system-endian in L</"pack"> method, or from system-endian to little-endian in L</"unpack"> method.

A length must be a positive integer. If a length is specified, the type(such as C<Int>) becomes a corresponding array type(such as C<int[]>).

Exceptions:

If template syntax is invalid, an exception is thrown.

The template $template must be defined. Otherwise an exception is thrown.

The objects $objects must be defined. Otherwise an exception is thrown.

The length of the specifiers in the template $template must be less than or equal to the lenght of the objects $objects. Otherwise an exception is thrown.

The type of the element in the objects $objects is invalid, an exception is thrown.

=head2 unpack

C<static method unpack : object[] ($template : string, $binary : string);>

Converts the binary data $binary to the objects $objects according to the template $template, and returns it.

See L</"pack"> method about templates.

Exceptions:

If template syntax is invalid, an exception is thrown.

The template $template must be defined. Otherwise an exception is thrown.

The binary data $binary must be defined. Otherwise an exception is thrown.

The current offset $binary_offset plus (the size $size * the length $length of the specifier) must be less than the length($binary_length) of the binary data $binary. Otherwise an exception is thrown.

=head1 Copyright & License

Copyright (c) 2024 Yuki Kimoto

MIT License


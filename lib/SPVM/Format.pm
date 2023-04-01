package SPVM::Format;

1;

=encoding utf8

=head1 Name

SPVM::Format - Format Utilities

=head1 Usage

  use Format;
  
  # Foo 123 abc 1.115 Bar
  my $result = Format->sprintf("Foo %d %s %.3f Bar", 123, "abc", 1.115);
  
  # %d - "123"
  my $result = Format->sprintf("%d", 123);
  
  # %5d - "  123"
  my $result = Format->sprintf("%5d", 123);

  # %05d - "00123"
  my $result = Format->sprintf("%05d", 123);
  
  # %+d - "+123"
  my $result = Format->sprintf("%+d", 123);
  
  # %-5d - "123  "
  my $result = Format->sprintf("%-5d", 123);
  
  # %d - "x"
  my $result = Format->sprintf("%c", 'x');
  
  # %c - "あ"
  my $result = Format->sprintf("%c", Fn->ord("あ"));

  # %s - "ABC"
  my $result = Format->sprintf("%s", "ABC");
  
  # %.2s - "AB"
  my $result = Format->sprintf("%.2s", "ABC");
  
  # %u - "4294967295"
  my $result = Format->sprintf("%u", -1);
  
  # %f - "3.141500"
  my $result = Format->sprintf("%f", 3.1415);
  
  # %.2f - "3.14"
  my $result = Format->sprintf("%.2f", 3.1415);
  
  # %g - "3.14"
  my $result = Format->sprintf("%g", 3.14);
  
  # %x - "ff"
  my $result = Format->sprintf("%x", 255);
    
  # %x - "ffffffff"
  my $result = Format->sprintf("%x", -1);

  # %p - "0x8000000000000000"
  my $result = Format->sprintf("%p", $object);

=head1 Description

C<Format> is a formatting utilities for C<sprintf> method.

=head1 Class Methods

=head2 sprintf

  static method sprintf : string ($format : string, $args : object[]...);

Creates a formatted string form the $format and the $args.

=head3 Specifiers

=begin html

<table>
  <tr><th>Specifiers</th><th>Descriptions</th><th>Acceptable Types</th></tr>
  <tr><td>%c</td><td>An <code>UTF-8</code> character</td><td><a href="https://metacpan.org/pod/SPVM::Byte">Byte</a>, <a href="https://metacpan.org/pod/SPVM::Int">Int</a></td></tr>
  <tr><td>%d</td><td>Signed 32-bit integer</td><td><a href="https://metacpan.org/pod/SPVM::Int">Int</a></td></tr>
  <tr><td>%f</td><td>64bit floating point</td><td><a href="https://metacpan.org/pod/SPVM::Double">Double</a>, <a href="https://metacpan.org/pod/SPVM::Float">Float</a></td></tr>
  <tr><td>%g</td><td>64bit floating point</td><td><a href="https://metacpan.org/pod/SPVM::Double">Double</a>, <a href="https://metacpan.org/pod/SPVM::Float">Float</a></td></tr>
  <tr><td>%x</td><td>Unsiged 32-bit integer represented by hexadecima characters <code>0-9a-z</code></td><td><a href="https://metacpan.org/pod/SPVM::Int">Int</a></td></tr>
  <tr><td>%X</td><td>Unsiged 32-bit integer represented by hexadecima characters <code>0-9A-Z</code></td><td><a href="https://metacpan.org/pod/SPVM::Int">Int</a></td></tr>
  <tr><td>%lX</td><td>Unsiged 64-bit integer represented by hexadecima characters <code>0-9A-Z</code></td><td><a href="https://metacpan.org/pod/SPVM::Long">Long</a></td></tr>
  <tr><td>%ld</td><td>Signed 64bit integer</td><td><a href="https://metacpan.org/pod/SPVM::Long">Long</a></td></tr>
  <tr><td>%lu</td><td>Unsigned 64bit integer</td><td><a href="https://metacpan.org/pod/SPVM::Long">Long</a></td></tr>
  <tr><td>%lx</td><td>Unsiged 64-bit integer represented by hexadecima characters <code>0-9a-z</code></td><td><a href="https://metacpan.org/pod/SPVM::Long">Long</a></td></tr>
  <tr><td>%s</td><td>String</td><td>String Type</td></tr>
  <tr><td>%p</td><td>Address</td><td>Object Type</td></tr>
  <tr><td>%u</td><td>Unsigned 32-bit integer</td><td><a href="https://metacpan.org/pod/SPVM::Int">Int</a></td></tr>
</table>

=end html

=head3 Specifier Options

Specifier options can be written between C<%> and the character of specifier such as C<d>, C<f>.

=begin html

<table>
  <tr><th>Specifier Options</th><th>Descriptions</th></tr>
  <tr><td>0[DECIMAL_NUMBERS]</td><td>Zero padding</td></tr>
  <tr><td>+</td><td>Adding a plus sign</td></tr>
  <tr><td>-</td><td>Left justified</td></tr>
  <tr><td>.[DECIMAL_NUMBERS]</td><td>Precision(Maximam width in %s)</td></tr>
</table>

=end html

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

package SPVM::Format;

1;

=encoding utf8

=head1 Name

SPVM::Format - Format Utilities

=head1 Synopsys

  use Format;
  
  # %d - "123"
  my $formatted_string = Format->sprintf("%d", 123);
  
  # %5d - "  123"
  my $formatted_string = Format->sprintf("%5d", 123);

  # %05d - "00123"
  my $formatted_string = Format->sprintf("%05d", 123);
  
  # %+d - "+123"
  my $formatted_string = Format->sprintf("%+d", 123);
  
  # %-5d - "123  "
  my $formatted_string = Format->sprintf("%-5d", 123);
  
  # %d - "x"
  my $formatted_string = Format->sprintf("%c", 'x');
  
  # %c - "あ"
  my $formatted_string = Format->sprintf("%c", Format->ord("あ"));

  # %s - "ABC"
  my $formatted_string = Format->sprintf("%s", "ABC") eq "ABC");
  
  # %u - "4294967295"
  my $formatted_string = Format->sprintf("%u", -1) eq "4294967295");
  
  # %f - "3.141500"
  my $formatted_string = Format->sprintf("%f", 3.1415) eq "3.141500");
  
  # %.2f - "3.14"
  my $formatted_string = Format->sprintf("%.2f", 3.1415) eq "3.14");
  
  # %g - "3.14"
  my $formatted_string = Format->sprintf("%g", 3.14) eq "3.14");
  
  # %x - "ff"
  my $formatted_string = Format->sprintf("%x", 255) eq "ff");
    
  # %x - "ffffffff"
  my $formatted_string = Format->sprintf("%x", -1) eq "ffffffff");

=head1 Description

C<Format> is a formatting utilities such as C<sprintf> method.

=head1 Class Methods

Class method of B<Format> module.

=head2 sprintf

  static method sprintf : string ($format : string, $args : object[]...)

Create a formatted string with the format and the values.

=begin html

<table>
  <tr><th>Specifiers</th><th>Descriptions</th><th>Acceptable Types</th></tr>
  <tr><td>%c</td><td>An <code>UTF-8</code> character</td><td><a href="https://metacpan.org/pod/SPVM::Byte">Byte</a>, <a href="https://metacpan.org/pod/SPVM::Int">Int</a></td></tr>
  <tr><td>%d</td><td>Signed 32bit integer</td><td><a href="https://metacpan.org/pod/SPVM::Int">Int</a></td></tr>
  <tr><td>%u</td><td>Unsigned 32bit integer</td><td><a href="https://metacpan.org/pod/SPVM::Int">Int</a></td></tr>
  <tr><td>%x</td><td>Unsiged 32 bit integer to a hexadecimal string using <code>0-9a-z</code></td><td><a href="https://metacpan.org/pod/SPVM::Int">Int</a></td></tr>
  <tr><td>%X</td><td>Unsiged 32 bit integer to a hexadecimal string using <code>0-9A-Z</code></td><td><a href="https://metacpan.org/pod/SPVM::Int">Int</a></td></tr>
  <tr><td>%ld</td><td>Signed 64bit integer</td><td><a href="https://metacpan.org/pod/SPVM::Long">Long</a></td></tr>
  <tr><td>%lu</td><td>Unsigned 64bit integer</td><td><a href="https://metacpan.org/pod/SPVM::Long">Long</a></td></tr>
  <tr><td>%lx</td><td>Unsiged 64 bit integer to a hexadecimal string using <code>0-9a-z</code></td><td><a href="https://metacpan.org/pod/SPVM::Long">Long</a></td></tr>
  <tr><td>%lX</td><td>Unsiged 64 bit integer to a hexadecimal string using <code>0-9A-Z</code></td><td><a href="https://metacpan.org/pod/SPVM::Long">Long</a></td></tr>
  <tr><td>%f</td><td>64bit floating point</td><td><a href="https://metacpan.org/pod/SPVM::Double">Double</a>, <a href="https://metacpan.org/pod/SPVM::Float">Float</a></td></tr>
  <tr><td>%s</td><td>String</td><td>string</td></tr>
  <tr><td>%U</td><td>Unicode Code Point to a UTF-8 character</td><td></td></tr>
</table>

=end html

B<Specifier Options:>

Specifier options can be written between C<%> and the character of specifier such as C<d>, C<f>.

=begin html

<table>
  <tr><th>Specifier options</th><th>Descriptions</th></tr>
  <tr><td>0[DECIMAL_NUMBERS]</td><td>Zero padding</td></tr>
  <tr><td>+</td><td>Adding a plus sign</td></tr>
  <tr><td>-</td><td>Left justified</td></tr>
  <tr><td>.[DECIMAL_NUMBERS]</td><td>Precision</td></tr>
</table>

=end html

B<Examples:>
    
  # %d - "123"
  my $formatted_string = Format->sprintf("%d", 123);
  
  # %5d - "  123"
  my $formatted_string = Format->sprintf("%5d", 123);

  # %05d - "00123"
  my $formatted_string = Format->sprintf("%05d", 123);
  
  # %+d - "+123"
  my $formatted_string = Format->sprintf("%+d", 123);
  
  # %-5d - "123  "
  my $formatted_string = Format->sprintf("%-5d", 123);
  
  # %d - "x"
  my $formatted_string = Format->sprintf("%c", 'x');
  
  # %c - "あ"
  my $formatted_string = Format->sprintf("%c", Format->ord("あ"));

  # %s - "ABC"
  my $formatted_string = Format->sprintf("%s", "ABC") eq "ABC");
  
  # %u - "4294967295"
  my $formatted_string = Format->sprintf("%u", -1) eq "4294967295");
  
  # %f - "3.141500"
  my $formatted_string = Format->sprintf("%f", 3.1415) eq "3.141500");
  
  # %.2f - "3.14"
  my $formatted_string = Format->sprintf("%.2f", 3.1415) eq "3.14");
  
  # %g - "3.14"
  my $formatted_string = Format->sprintf("%g", 3.14) eq "3.14");
  
  # %x - "ff"
  my $formatted_string = Format->sprintf("%x", 255) eq "ff");
    
  # %x - "ffffffff"
  my $formatted_string = Format->sprintf("%x", -1) eq "ffffffff");


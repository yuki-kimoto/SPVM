package SPVM::MIME::Base64;

use SPVM 'SPVM::MIME::Base64';

1;

=head1 NAME

SPVM::MIME::Base64 - Base64 encode/decode

=head1 SYNOPSYS
  
  use SPVM::MIME::Base64;
  
  my $b64 = SPVM::MIME::Base64->new;
  my $text = $b64->encode($binary);
  my $binary = $b64->decode($text);

=head1 DESCRIPTION

Base64 encode/decode

=head1 METHODS

=head2 new

  sub new : SPVM::MIME::Base64 ()

Create new L<SPVM::MIME::Base64> object.

=head2 encode

  sub encode : string ($self : self, $binary : string)

Encode binary data to base64 text.

=head2 decode

  sub decode : string ($self : self, $base64_text : string)

Decode encoded Base64 text to binary data.

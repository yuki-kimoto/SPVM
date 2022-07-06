package SPVM::BlessedObject::String;

use Carp 'confess';

use base 'SPVM::BlessedObject';

use overload bool => sub {1}, '""' => sub { shift->to_string }, fallback => 1;

use SPVM::ExchangeAPI;

sub to_string {
  my $self = shift;
  
  my $string = SPVM::ExchangeAPI::string_object_to_bin($SPVM::BUILDER, $self);
  
  my $success = utf8::decode($string);
  
  unless ($success) {
    confess "This string can't be decoded to Perl string";
  }
  
  return $string;
}

sub to_bin {
  my $self = shift;
  
  my $bin = SPVM::ExchangeAPI::string_object_to_bin($SPVM::BUILDER, $self);
  
  return $bin;
}

1;

=head1 Name

SPVM::BlessedObject::String - String based blessed object

=head2 DESCRIPTION

SPVM::BlessedObject::String is array based blessed object.

This object contains SPVM array object.

=head1 Usage

  # Convert to Perl decoded String
  my $string = $spvm_string->to_string;
  
=head1 Methods

=head2 to_string

  my $string = $spvm_string->to_string;

Return the string as Perl decoded String. If the docoding fails, an exception will thrown.

=head2 to_bin

  my $string = $spvm_string->to_bin;

Return the string value as bytes.

=head1 Operators

L<SPVM::BlessedObject::String> overloads the following operators.

=head2 bool

  my $bool = !!$url;
  
Always true.

=head2 stringify

  my $str = "$url";
  
Alias for L</"to_string">.

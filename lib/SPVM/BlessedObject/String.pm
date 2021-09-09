package SPVM::BlessedObject::String;

use base 'SPVM::BlessedObject';

use overload bool => sub {1}, '""' => sub { shift->to_string }, fallback => 1;

use SPVM::ExchangeAPI;

sub to_string {
  my $self = shift;
  
  my $env = $self->{env};
  
  SPVM::ExchangeAPI::string_object_to_string($env, $self);
}

1;

=head1 NAME

SPVM::BlessedObject::String - String based blessed object

=head2 DESCRIPTION

SPVM::BlessedObject::String is array based blessed object.

This object contains SPVM array object.

=head1 SYNOPSYS

  # Convert to Perl decoded String
  my $string = $spvm_string->to_string;
  
=head1 METHODS

=head2 to_string

  my $string = $spvm_string->to_string;

Convert to Perl decoded String

=head1 OPERATORS

L<BlessedObject::String|SPVM::BlessedObject::String> overloads the following operators.

=head2 bool

  my $bool = !!$url;
  
Always true.

=head2 stringify

  my $str = "$url";
  
Alias for L</"to_string">.

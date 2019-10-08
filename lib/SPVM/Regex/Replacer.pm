package SPVM::Regex::Replacer;

use SPVM 'SPVM::Regex::Replacer';

1;

=head1 NAME

SPVM::Regex::Replacer - a callback type for the regex replacement

=head1 SYNOPSYS
  
  use SPVM::Regex::Replacer;
  
  my $replacer : SPVM::Regex::Replacer = sub replace_to : string ($self : self, $re : SPVM::Regex) {
    return "AB" . $re->caps->[0] . "C";
  });
  
  my $message = $replacer->replace_to;

=head1 DESCRIPTION

L<SPVM::Regex::Replacer> is a callback type for the regex replacement

=head1 INSTANCE METHODS

=head2 replace_to

  sub replace_to : string ($self : self, $re : SPVM::Regex)

package SPVM::Regex::Replacer;

1;

=head1 NAME

SPVM::Regex::Replacer - Regex::Replacer in SPVM | a callback type for the regex replacement

=head1 SYNOPSYS
  
  use Regex::Replacer;
  
  my $replacer : Regex::Replacer = method : string ($re : Regex) {
    return "AB" . $re->captures->[0] . "C";
  });
  
  my $re = Regex->new("ab(c)");
  my $string_for_replace = $replacer->($re);

=head1 DESCRIPTION

L<Regex::Replacer|SPVM::Regex::Replacer> is a callback type for the regex replacement.

=head1 CALLBACK METHOD INTERFACE

  method : string ($re : Regex)

This method return the string after the replacement.

This method is planned to be implemented in other classes.

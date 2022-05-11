package SPVM::Regex::Replacer;

1;

=head1 NAME

SPVM::Regex::Replacer - Interface Type for Regex Replacement Callback

=head1 SYNOPSYS
  
  use Regex::Replacer;
  use Regex;
  
  my $replacer = (Regex::Replacer)method : string ($re : Regex) {
    my $replaced_string_match = "AB" . $re->captures->[0] . "C";
    return $replaced_string_match;
  });
  
  my $string = "abc";
  my $re = Regex->new("ab(c)");
  my $replaced_string = $re->replace_all_cb($string, 0, $replacer);

=head1 DESCRIPTION

L<Regex::Replacer|SPVM::Regex::Replacer> is the interface type for the regex replacement callback.

=head1 INTERFACE METHODS

  required method : string ($re : Regex)

The implementation must receive a L<Regex|SPVM::Regex> object and return the string after the replacement.

package SPVM::Regex::Replacer;

1;

=head1 NAME

SPVM::Regex::Replacer - a callback interface for the regex replacement

=head1 SYNOPSYS
  
  use SPVM::Regex::Replacer;
  
  my $replacer : SPVM::Regex::Replacer = sub : string ($self : self, $re : SPVM::Regex) {
    return "AB" . $re->caps->[0] . "C";
  });
  
  my $re = SPVM::Regex->new("ab(c)");
  my $str_for_replace = $replacer->($re);

=head1 DESCRIPTION

L<SPVM::Regex::Replacer> is a callback interface for the regex replacement

=head1 CALLBACK METHOD INTERFACE

  sub : string ($self : self, $re : SPVM::Regex)

This method must return a string for replacement in the method implementation.

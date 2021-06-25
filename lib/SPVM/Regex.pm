package SPVM::Regex;

1;

=head1 NAME

SPVM::Regex - Regular expression

=head1 SYNOPSYS
  
  use SPVM::Regex;
  
  # Pattern match
  {
    my $re = SPVM::Regex->new("ab*c");
    my $target = "zabcz";
    my $match = $re->match($target, 0);
  }

  # Pattern match - UTF-8
  {
    my $re = SPVM::Regex->new("あ+");
    my $target = "いあああい";
    my $match = $re->match($target, 0);
  }

  # Pattern match - Character class and the nagation
  {
    my $re = SPVM::Regex->new("[A-Z]+[^A-Z]+");
    my $target = "ABCzab";
    my $match = $re->match($target, 0);
  }

  # Pattern match with captures
  {
    my $re = SPVM::Regex->new("^(\w+) (\w+) (\w+)$");
    my $target = "abc1 abc2 abc3";
    my $match = $re->match($target, 0);
    
    if ($match) {
      my $cap1 = $re->captures->[0];
      my $cap2 = $re->captures->[1];
      my $cpa3 = $re->captures->[2];
    }
  }
  
  # Replace
  {
    my $re = SPVM::Regex->new("abc");
    my $target = "ppzabcz";
    
    # "ppzABCz"
    my $result = $re->replace($target, 0, "ABC");
    
    my $replace_count = $re->replace_count;
  }

  # Replace with a callback and capture
  {
    my $re = SPVM::Regex->new("a(bc)");
    my $target = "ppzabcz";
    
    # "ppzABbcCz"
    my $result = $re->replace_cb($target, 0, sub : string ($self : self, $re : SPVM::Regex) {
      return "AB" . $re->captures->[0] . "C";
    });
  }

  # Replace all
  {
    my $re = SPVM::Regex->new("abc");
    my $target = "ppzabczabcz";
    
    # "ppzABCzABCz"
    my $result = $re->replace_all($target, 0, "ABC");
  }

  # Replace all with a callback and capture
  {
    my $re = SPVM::Regex->new("a(bc)");
    my $target = "ppzabczabcz";
    
    # "ppzABCbcPQRSzABCbcPQRSz"
    my $result = $re->replace_all_cb($target, 0, sub : string ($self : self, $re : SPVM::Regex) {
      return "ABC" . $re->captures->[0] . "PQRS";
    });
  }
  
=head1 DESCRIPTION

L<SPVM::Regex> provides regular expression functions.

=head1 REGULAR EXPRESSION SYNTAX

L<SPVM::Regex> provides the methodset of Perl regular expression. The target string and regex string is interpretted as UTF-8 string.
  
  # Quantifier
  +     more than or equals to 1 repeats
  *     more than or equals to 0 repeats
  ?     0 or 1 repeats
  {m,n} repeats between m and n
  
  # Regular expression character
  ^    first of string
  $    last of string
  .    all character except "\n"
  
  #    Default mode     ASCII mode
  \d   Not supported    [0-9]
  \D   Not supported    not \d
  \s   Not supported    " ", "\t", "\f", "\r", "\n"
  \S   Not supported    not \s
  \w   Not supported    [a-zA-Z0-9_]
  \W   Not supported    not \w
  
  # Character class and the negatiton
  [a-z0-9]
  [^a-z0-9]
  
  # Capture
  (foo)

B<Regex Options:>

  s    single line mode
  a    ascii mode

Regex options is used by C<new_with_options> method.

  my $re = SPVM::Regex->new("^ab+c", "sa");

B<Limitations:>

L<SPVM::Regex> do not support the same set of characters after a quantifier.
      
  # A exception occurs
  SPVM::Regex->new("a*a");
  SPVM::Regex->new("a?a");
  SPVM::Regex->new("a+a");
  SPVM::Regex->new("a{1,3}a")
      
If 0 width quantifir is between two same set of characters after a quantifier, it is invalid.
      
  # A exception occurs
  SPVM::Regex->new("\d+\D*\d+");
  SPVM::Regex->new("\d+\D?\d+");

=head1 STATIC METHODS

=head2 new

  my $re = SPVM::Regex->new("^ab+c");

Create a new L<SPVM::Regex> object and compile the regex.

=head2 new_with_options

  my $re = SPVM::Regex->new("^ab+c", "s");

Create a new L<SPVM::Regex> object and compile the regex with the options.

=head1 INSTANCE METHODS

=head2 captures

  sub captures : string[] ()

Get the strings captured by "match" method.

=head2  match_start

  sub match_start : int ()

Get the start byte offset of the string matched by "match" method method.

=head2 match_length

  sub match_length : int ()

Get the byte length of the string matched by "match" method method.

=head2 replace_count

  sub replace_count : int ();

Get the replace count of the strings replaced by "replace" or "replace_all" method.

=head2 match

  sub match : int ($self : self, $target : string, $target_offset : int)

Execute pattern matching to the specific string and the start byte offset of the string.

If the pattern match succeeds, 1 is returned, otherwise 0 is returned.

You can get captured strings using "captures" method,
and get the byte offset of the matched whole string using "match_start" method,
and get the length of the matched whole string using "match_length" method.

=head2 replace

  sub replace  : string ($self : self, $target : string, $target_offset : int, $replace : string)

Replace the target string specified with the start byte offset with replace string.

=head2 replace_cb

  sub replace_cb  : string ($self : self, $target : string, $target_offset : int, $replace_cb : SPVM::Regex::Replacer)

Replace the target string specified with the start byte offset with replace callback. The callback must have "replace_to" method defined in L<SPVM::Regex::Replacer>.

=head2 replace_all

  sub replace_all  : string ($self : self, $target : string, $target_offset : int, $replace : string)

Replace all of the target strings specified with the start byte offset with replace string.

=head2 replace_all_cb

  sub replace_all_cb  : string ($self : self, $target : string, $target_offset : int, $replace_cb : SPVM::Regex::Replacer)

Replace all of the target strings specified with the start byte offset with replace callback. The callback must have "replace_to" method defined in L<SPVM::Regex::Replacer>.

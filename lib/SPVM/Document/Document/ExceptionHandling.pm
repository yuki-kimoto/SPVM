=head1 Name

SPVM::Document::Language::ExceptionHandling - Exception Handling in SPVM Language

=head1 Description

This document describes exception handling in SPVM language.

=head1 Exception Handling

Explains exceptions.

=head2 Throwing Exception

You can throw an exception using the L<die statement|/"die Statement">.

  die OPERAND;

Examples:

  # Throw an exception
  die "Error";

=head2 Catching Exception 

You can catch an exception using an L<eval block|/"eval Block">.

  eval {
    die "Error";
  }

The L<undef|/"Undefined Value"> is set to the L<exception variable|/"Exception Variable"> C<$@> at the top of the L<eval block|/"eval Block">.

The error message is set to the L<exception variable|/"Exception Variable"> C<$@> when the exception is thrown.

Examples:
  
  # Catch the exception
  eval {
    # Throw an exception
    die "Error";
  }
  
  # Check the error message
  if ($@) {
    # ...
  }

=head2 Exception Variable

B<Exception Variable> is a global variable that is represented by "B<$@>"

  $@

See the L<setting class varialbe|/"Setting Class Variable"> to get Exception Variable Value.

See L</"Setting Exception Variable"> to set Exception Variable Value.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

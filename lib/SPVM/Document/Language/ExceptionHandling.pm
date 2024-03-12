=head1 Name

SPVM::Document::Language::ExceptionHandling - Exception Handling in The SPVM Language

=head1 Description

This document describes exception handling in the SPVM language.

=head1 Exception Handling

=head2 Throwing Exception

The L<die statement|SPVM::Document::Language::Statements/"die Statement"> throws an exception.

  die "This value is invalid.";

A basic type ID can be given to the die statement. This is set to C<eval_error_id> if an exception is thrown.

  die basic_type_id Error::System, "This value is invalid.";

A class name can be given to the die statement. This is the same as the above code.

  die Error::System "This value is invalid.";

If a basic type ID and a class name are not given, it is set to the basic type ID of the L<Error|SPVM::Error> class.

=head2 Catching Exception 

An eval block catches an exception.

  eval {
    die "This value is invalid.";
  }

C<undef> is set to L<$@|/"Exception Variable"> at the beginning of each eval block.

0 is set to C<eval_error_id> at the beginning of each eval block.

If an exception is thrown, the message passed to the die statement is set to L<$@|/"Exception Variable">, and the basic type ID passed to the die statement is set to C<eval_error_id>.

  if ($@) {
    # Do something if an exception is thrwon
  }
  
  # If you need to check eval_error_id, write the following code.
  if ($@) {
    if (eval_error_id isa_error Error::System) {
      
    }
  }

C<$@> could be overwritten by the other operations, so it is good to save it into a local variable.

  if (my $error = $@) {
    
  }

=head2 Exception Variable

C<$@> is the exception variable. This is used to save a message for an exception.

  $@

The type is the string type.

Using the assignment operator, the value of the exception variable can be set.

  $@ = "Error Message";
  
  $@ = undef;

The exception variable is a stack variable(not a global variable).

If a new stack is created for a thread, exception variables exist for each thread.

=head1 See Also

=over 2

=item * L<SPVM::Document::Language::Statements>

=item * L<SPVM::Document::Language::Operators>

=item * L<SPVM::Document::Language>

=item * L<SPVM::Document>

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

=head1 Name

SPVM::Document::Language::Statements - Statements in the SPVM Language

=head1 Description

This document describes statements in the SPVM language.

=head1 Statements

A statement is a basic instruction that tells the program what to do.

Statements can be written direct under L<scope block|SPVM::Document::Language::Class/"Scope Block">.

  # Scope block
  {
    # Statements
    STATEMENT1
    STATEMENT2
    STATEMENT3
  }

=head2 Conditional Statements

=head3 if Statement

The C<if> statement is a conditional statement with the following syntax.

  if (CONDITION1) {
    
  }
  elsif (CONDITION2) {
    
  }
  elsif (CONDITIONn) {
    
  }
  else {
    
  }

The C<elsif> statement and the C<else> statement are optional.

At first, all C<elsif> statements are expanded to the following code using C<if> - C<else> statements.

  if (CONDITION1) {
    
  }
  else {
    if (CONDITION2) {
      
    }
    else {
      if (CONDITIONn) {
        
      }
      else {
        
      }
    }
  }

The C<if> statement is converted to simple C<if> - C<else> statements, so see a simple C<if> - C<else> statement.

  if (CONDITION) {
    
  }
  else {
    
  }

The L<condition evaluation|SPVM::Document::Language::Operators/"Condition Evaluation"> is performed on the condition I<CONDITION>.

If the evaluated value is not 0, the program jumps to the beginning of the C<if> block.

If the evaluated value is 0 and there is the C<else> block, the program jumps to the beginning of the C<else> block.

If the evaluated value is 0 and there is no C<else> block, the program jumps to the end of the C<if> block.

A C<if> - C<else> statement is enclosed by an invisible simple block.

  {
    if (CONDITION) {
      
    }
    else {
      
    }
  }

Examples:

  # if statement.
  my $flag = 1;
  
  if ($flag == 1) {
    say "One";
  }
  
  # if statement with elsif and else
  my $flag = 2;
  
  if ($flag == 1) {
    say "One";
  }
  elsif ($flag == 2) {
    say "Two";
  }
  elsif ($flag == 3) {
    say "Three";
  }
  else {
    say "Other";
  }

=head3 else Statement

The C<else> statement is a conditional statement used in L<if statement|/"if Statement">.

  if (CONDITION) {
    
  }
  else {
    
  }

=head3 elsif Statement

The C<elsif> statement is a conditional statement used in L<if statement|/"if Statement">.

  if (CONDITION1) {
  
  }
  elsif (CONDITION2) {
  
  }

=head3 unless Statement

The C<unless> statement is a conditional statement with the following syntax.

  unless (CONDITION) {
    
  }

The C<unless> statement is expanded to the following code.

  if (!CONDITION) {
    
  }

Examples:

  # unless statement.
  my $flag = 1;
  
  unless ($flag == 0) {
    say "Not Zero";
  }

=head3 switch Statement

The C<switch> statement is a conditional statement with the following syntax.
  
  # The switch statement
  switch (CONDITION) {
    case CASE1: {
      # ...
    }
    case CASE2: {
      # ...
    }
    case CASEn: {
      # ...
    }
    default: {
      # ...
    }
  }

The L<integer promotional conversion|SPVM::Document::Language::Operators/"Integer Promotional Conversion"> is performed on the condition I<CONDITION>.

The operand of the case statement I<CASEn> must be a L<character literal|SPVM::Document::Language::Tokenization/"Character Literal">, an L<integer literal|SPVM::Document::Language::Tokenization/"Integer Literals"> and an L<inline-expaned class method call to get an enumeration value|SPVM::Document::Language::Class/"Inline Expansion of Method Call to Get an Enuemration Value">.

If I<CASEn> is a L<character literal|SPVM::Document::Language::Tokenization/"Character Literal">, the value is converted to int type at compile-time.

The C<case> statements and the C<default> statement are optional.

If I<CONDITION> matches I<CASEn>, the program jumps to the beginning of the case block of I<CASEn>.

If there are no case statements and no default statement, the program jumps to the end of the C<switch> block.

If there is the C<default> statement and I<CONDITION> dose not matches I<CASEn>, the program jumps to the beginning of the C<default> block.

If there is no C<default> statement and I<CONDITION> dose not matches I<CASEn>, the program jumps to the end of the C<switch> block.

A L<break|/"break Statement"> statement is implicitly added to the end of the statements in every C<case> block.

  case CASEn: {
    # A break statement is added implicitly to the end of the statements
    break;
  }

It is allowed to jump multiple case statements into a single block.

  switch (CONDITION) {
    case CASE1:
    case CASE2:
    {
      # ...
    }
  }

Compilation Errors:

I<CONDITION> must be an integer type within int. Otherwise, a compilation error occurs.

The values of the case statements must not be duplicated. Otherwise, a compilation error occurs.

Examples:

  # switch statement
  my $code = 2;
  my $flag = 1;
  switch ($code) {
    case 1: {
      say "1";
    }
    case 2: {
      say "2";
    }
    case 3: {
      if ($flag) {
        break;
      }
      say "3";
    }
    case 4:
    case 5:
    {
      say "4 or 5";
    }
    default: {
      say "Other";
    }
  }
  
  # switch statement with enumeration
  class Foo {
    enum {
      ID1,
      ID2,
      ID3,
    }
    
    static method main : int () {
      my $value = 1;
      switch ($value) {
        case Foo->ID1: {
          say "1";
        }
        case Foo->ID2: {
          say "2";
        }
        case Foo->ID3: {
          if ($flag) {
            break;
          }
          say "3";
        }
        default: {
          say "Other";
        }
      }
    }
  }

=head4 case Statement

The C<case> statement specifies a case in L<switch statement|/"switch Statement">.

  # The case statement
  switch (CONDITION) {
    case CASEn: {
      # ...
    }
  }

=head4 default Statement

The C<default> statement specifies a default case in L<switch statement|/"switch Statement">.

  # The default statement
  switch (CONDITION) {
    default: {
      # ...
    }
  }

=head4 break Statement

The C<break> statement makes the program jump to the end of L<switch|/"switch Statement"> block.

  # The break statement
  break;

Examples:

  my $code = 2;
  my $flag = 1;
  switch ($code) {
    case 3: {
      if ($flag) {
        # The break statement makes the program jump to the end of the switch block
        break;
      }
      say "3";
    }
    default: {
      say "Other";
    }
  }
  # The end of the switch block

=head2 Loop Statements

=head3 while Statement

The C<while> statement is a loop statement with the following syntax.

  # The while statement
  while (CONDITION) {
  
  }

The L<condition evaluation|SPVM::Document::Language::Operators/"Condition Evaluation"> is performed on the condition I<CONDITION>.

If the evaluated value is 0, the program jumps to the end of the C<while> block. Otherwise, the program jumps to the beginning of the C<while> block.

When the program reaches the end of the C<while> block, it jumps to the beginning of the C<while> statement.

Examples:

  # The while statement
  my $i = 0;
  while ($i < 5) {
    
    say "$i";
    
    $i++;
  }

The C<while> statement is enclosed by an invisible simple block.
  
  {
    while (CONDITION) {
    
    }
  }

=head3 next Statement

The C<next> statement makes the program jump to the beginning of the current L<while statement|/"while Statement">.

  # The next statement
  next;

Examples:

  my $i = 0;
  
  # The beginning of the while statement
  while ($i < 5) {
  
    if ($i == 3) {
      $i++;
      
      # The next statement makes the program jump to the beginning of the current while statement.
      next;
    }
    
    say "$i";
    $i++;
  }

=head3 last Statement

The C<last> statement makes the program jump to the end of the current L<while statement|/"while Statement">.

  # The last statement
  last;

Examples:

  while (1) {
    # The last statement makes the program jump to the end fo the current while statement.
    last;
  }
  # The end fo the while statement

=head3 for Statement

The C<for> statement is a loop statement with the following syntax.

  # The for statement
  for (INIT; CONDITION; INCREMENT) {
  
  }

A C<for> statement is expanded to the following code using a L<while statement|/"while Statement">.
  
  {
    INIT;
    while (CONDITION) {
      
      # ...
      
      INCREMENT;
    }
  }

Exampels:

  # The for statement
  for (my $i = 0; $i < 5; $i++) {
    say "$i";
  }

=head3 for-each Statement

The for-each statement is a loop statement with the following syntax.
  
  # The for-each statemenet
  for my VAR (@ARRAY) {
    
  }
  
  for my VAR (@{ARRAY}) {
    
  }

A for-each statement is expanded to the following code using a L<for statement|/"for Statement">.

  for (my $i = 0; $i < @{ARRAY}; $i++) {
    my VAR = ARRAY->[$i];
    
  }

Example:

  # The for-each statemenet
  my $array = [1, 2, 3];
  for my $element (@$array) {
    say "$elemenet";
  }

=head2 return Statement

The return statement causes the program to return to its caller. And it set the return value.

  // void
  return;
  
  // non-void
  return OPERAND;

This statement causes the program to return to its caller.

If I<OPERAND> is specified, the return vlaue is set to I<OPERAND>.

I<OPERAND> is an an L<operator|SPVM::Document::Language::Operators/"Operators">.

This is because leave scope operations must not destroy I<OPERAND>.

Compilation Errors:

If the return type of the current method is the void type, I<OPERAND> must not exist. Otherwise, a compilation error occurs.

If the return type of the current method is the non-void type, I<OPERAND> must exist. Otherwise, a compilation error occurs.

The type of I<OPERAND> must satisfy L<assignment requirement|SPVM::Document::Language::Types/"Assignment Requirement"> to the return type of the current method. Otherwise, a compilation error occurs.

=head2 die Statement

The C<die> statement throws an L<exception|SPVM::Document::Language::ExceptionHandling/"Throwing Exception">.
  
  # The die statement
  die
  die OPERAND_MESSAGE
  
  # The die statement with an error class
  die ERROR_CLASS
  die ERROR_CLASS OPERAND_MESSAGE
  
  # The die statement with the basic type ID of an error class
  die OPERAND_ERROR_ID, OPERAND_MESSAGE

I<OPERAND_MESSAGE> is a string of string type for an error message. If the exception thrown by the C<die> statement is catched, L<exception variable|SPVM::Document::Language::ExceptionHandling/"Exception Variable"> C<$@> is set to I<OPERAND_MESSAGE> with stack traces added.

If the exception is not catched, the program prints it to L<SPVM's standard error|SPVM::Document::Language::System/"Standard Streams">, and finishes the program with an error ID.

The following is an example of stack traces of an exception message.

  Error
    TestCase::Minimal->sum2 at SPVM/TestCase/Minimal.spvm line 1640
    TestCase->main at SPVM/TestCase.spvm line 1198

If I<OPERAND_MESSAGE> is not given or C<undef>, I<OPERAND_MESSAGE> is set to C<"Error">.

I<ERROR_CLASS> is a class name, normally of L<Error|SPVM::Error> class, or its child class. If the exception thrown by the C<die> statement is catched, L<eval_error_id|SPVM::Document::Language::Operators/"eval_error_id Operator"> is set to the basic type ID of I<ERROR_CLASS>.

The L<integer promotional conversion|SPVM::Document::Language::Operators/"Integer Promotional Conversion"> is performed on I<OPERAND_ERROR_ID>.

I<OPERAND_ERROR_ID> is an integer value within int type. If it is given and the exception thrown by the C<die> statement is catched, L<eval_error_id|SPVM::Document::Language::Operators/"eval_error_id Operator"> is set to I<OPERAND_ERROR_ID>.

See also L<Exception Handling|SPVM::Document::Language::ExceptionHandling> for exception handling using the C<die> statement.

Comlication Errors:

I<OPERAND_MESSAGE> must be string type or the undef type. Otherwise, a compilation error occurs.

I<ERROR_CLASS> must be a class type. Otherwise, a compilation error occurs.

I<OPERAND_ERROR_ID> must be an integer type within int. Otherwise, a compilation error occurs.

Examples:
  
  # The die statement with exception handling
  eval {
    die "Error";
  }
  
  if ($@) {
    # ...
  }
  
  # The die statement with an error class
  die Error::System "System Error";
  
  # The die statement with the basic type ID of an error class
  my $error_id = Fn->get_basic_type_id("Error::System");
  die $error_id, "System Error";

=head2 Operator Statement

The operator statement operates an L<operator|SPVM::Document::Language::Operators/"Operators">.

  # The operator statemenet
  OPERATOR;

Examples:

  1;
  $var;
  1 + 2;
  &foo();
  my $num = 1 + 2;

=head2 Empty Statement

The empty statement operates nothing.

  # The empty statemenet
  ;

=head2 require Statement

The C<require> statement loads a class only if it is found.

  if (require BASIC_TYPE) {
    
  }
  
  if (require BASIC_TYPE) {
    
  }
  else {
    
  }

This statement searches for the type I<BASIC_TYPE> in L<class search directories|SPVM::Document::Language::Class/"Class Search Directories"> from the beginning, and if found, it loads I<BASIC_TYPE> at compilation time.

If I<BASIC_TYPE> is found, the C<if> block is converted to a L<simple block|SPVM::Document::Language::Class/"Simple Block"> and the C<else> block(if it eixsts) is removed at compilation time.

If I<BASIC_TYPE> is not found, a compilation error does not occur.

If I<BASIC_TYPE> is not found, the C<else> block (if it eixstgs) is converted to a L<simple block|SPVM::Document::Language::Class/"Simple Block"> and the C<if> block is removed at compilation time.

Examples:

  my $foo : object;
  if (require MyClass) {
    $foo = new MyClass;
  }
  else {
    warn "Warning: Can't load MyClass";
  }

=head1 See Also

=over 2

=item * L<SPVM::Document::Language::Class>

=item * L<SPVM::Document::Language::Operators>

=item * L<SPVM::Document::Language>

=item * L<SPVM::Document>

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

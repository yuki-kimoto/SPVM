=head1 Name

SPVM::Document::Language::Statements - Statements in SPVM Language

=head1 Description

This document describes statements in SPVM language.

=head1 Statements

A statement is a basic instruction that tells the program what to do.

Statements can be written direct under the L<scope block|SPVM::Document::Language::Class/"Scope Block">.

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

The L<boolean conversion|SPVM::Document::Language::Types/"Boolean Conversion"> is performed on the condition I<CONDITION>.

If the evaluated value is not 0, the program jumps to the beginning of the C<if> block.

If the evaluated value is 0 and there is the C<else> block, the program jumps to the beginning of the C<else> block.

If the evaluated value is 0 and there is no C<else> block, the program jumps to the end of the C<if> block.

Local variable declartions in I<CONDITION> are allowed.

  if (my $condition = 1) {
    
  }
  else {
    
  }

This is expanded to the following code.

  {
    my $condition = 1;
    if ($condition) {
      
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

The C<else> statement is a conditional statement used in the L<if statement|/"if Statement">.

  if (CONDITION) {
    
  }
  else {
    
  }

=head3 elsif Statement

The C<elsif> statement is a conditional statement used in the L<if statement|/"if Statement">.

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

The L<integer promotional conversion|SPVM::Document::Language::Types/"Integer Promotional Conversion"> is performed on the condition I<CONDITION>.

The operand of the case statement I<CASEn> must be a L<character literal|SPVM::Document::Language::Tokenization/"Character Literal">, an L<integer literal|SPVM::Document::Language::Tokenization/"Integer Literal"> and an L<enumeration value|SPVM::Document::Language::Class/"Getting Enumeration Value">.

If I<CASEn> is a L<character literal|SPVM::Document::Language::Tokenization/"Character Literal">, the value is converted to the int type at compile-time.

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

I<CONDITION> must be an integer type within int, otherwise a compilation error occurs.

The values of the case statements cannnot be duplicated. If so, a compilation error occurs.

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
  
  # switch statement using enumeration
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

The C<case> statement specifies a case in the L<switch statement|/"switch Statement">.

  # The case statement
  switch (CONDITION) {
    case CASEn: {
      # ...
    }
  }

=head4 default Statement

The C<default> statement specifies a default case in the L<switch statement|/"switch Statement">.

  # The default statement
  switch (CONDITION) {
    default: {
      # ...
    }
  }

=head4 break Statement

The C<break> statement makes the program jump to the end of the L<switch||/"switch Statement"> block.

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

The C<while> statement runs loop.

  while (CONDITION) {
  
  }

First, The L<boolean conversion|SPVM::Document::Language::Types/"Boolean Conversion"> is performed on the condition.

Next, If the condition is 0, the program jumps to the end of the while block, otherwise the program goes to the beginning of the while block.

When the program reaches the end of the while block, it jumps back to the while statement and evaluates the condition again.

Examples:

  # The while statement
  my $i = 0;
  while ($i < 5) {
  
    say "$i";
  
    $i++;
  }

The L<last statement|/"last Statement"> is used inside the while block. By The L<last statement|/"last Statement">, the program jumps to the end of the current while block.
  
  # The last statement
  while (1) {
    # The program jumps to the end fo the current while block.
    last;
  }

The L<next statement|/"next Statement"> is used inside the while block. By The L<last statement|/"last Statement">, the program goes back to the C<while> statement of the current while block.

  my $i = 0;
  while ($i < 5) {
  
    if ($i == 3) {
      $i++;
      
      # the program goes back to the while statement of the current while block.
      next;
    }
    
    say "$i";
    $i++;
  }

The C<while> statement is enclosed by an inbisible simple block.
  
  # The while statement
  while (1) {
    
  }

  # The above is the same as the following.
  {
    while (1) {
      
    }
  }

=head3 for Statement

The C<for> Statement writes loop syntax easily.

  # The for statement.
  for (INIT_STATEMENT; CONDITION; INCREMENT_STATEMENT) {
  
  }

The C<for> statement is the alias for the C<while> statement.
  
  # The above for statemenet is the same as the following while statemenet.
  {
    INIT_STATEMENT;
    while (CONDITION) {
      
      # ...
      
      INCREMENT_STATEMENT;
    }
  }

B<Exampels:>

  # The for statement
  for (my $i = 0; $i < 5; $i++) {
    say "$i";
  }

=head3 for-each Statement

The for-each statement writes loop syntax easily for the simple iteration.
  
  # The for-each statemenet
  for my VAR (@ARRAY) {
  
  }
  
  for my VAR (@{ARRAY}) {
    
  }

The above for-each statement is the same as the following the L<for statement|/"for Statement">.

  for (my $i = 0; $i < @ARRAY; $i++) {
    my VAR = ARRAY->[$i];
    
  }

B<Example:>

  # The for-each statemenet
  my $array = [1, 2, 3];
  for my $element (@$array) {
    say "$elemenet";
  }

=head3 next Statement

The C<next> statement goes back to the L<while statement|/"while Statement"> of the current while block.

  next;

See also the L<while statement|/"while Statement">.

=head3 last Statement

The C<last> statement jumps to the end of the current while block.

  last;

See also the L<while statement|/"while Statement">.

=head2 return Statement

The C<return> statement returns a value.
  
  // void
  return;
  
  // non-void
  return OPERAND;

Compilation Errors:

If the return type of the current L<method|SPVM::Document::Language::Class/"Method Definition"> is the void typ, I<OPERAND> cannnot exist. If so, a compilation error occurs.

If the return type of the current L<method|SPVM::Document::Language::Class/"Method Definition"> is the non-void type, I<OPERAND> must exist, otherwise a compilation error occurs.

The type of I<OPERAND> must satisfy L<type assignability|SPVM::Document::Language::Types/"Type Assignability"> to the return type of the current method, otherwise a compilation error occurs.

=head2 die Statement

The C<die> statement throws an L<exception|SPVM::Document::Language::ExceptionHandling/"Throwing Exception">.

  die OPERAND_MESSAGE
  die
  die ERROR_TYPE OPERAND_MESSAGE
  die ERROR_TYPE
  die OPERAND_ERROR_ID ',' OPERAND_MESSAGE

OPERAND_MESSAGE is an error message. The error message is set to the L<exception variable|SPVM::Document::Language::ExceptionHandling/"Exception Variable"> C<$@>.

If an exception is thrown, the program prints the error message to the standard error with the stack traces and finishes with error ID 255.

If OPERAND_MESSAGE is omitted or C<undef>, "Error" is set to the L<exception variable|SPVM::Document::Language::ExceptionHandling/"Exception Variable"> C<$@>.

ERROR_TYPE is a class type. If ERROR_TYPE is given, the basic type ID of the class is the value got by the L<eval_error_id operator|SPVM::Document::Language::Operators/"eval_error_id Operator">.

OPERAND_ERROR_ID is an integer value within int type. If OPERAND_ERROR_ID is given, it is the value got by the L<eval_error_id operator|SPVM::Document::Language::Operators/"eval_error_id Operator">.

the L<integer promotional conversion|SPVM::Document::Language::Types/"Integer Promotional Conversion"> is performed on OPERAND_ERROR_ID.

The return type is the void typ.

The following one is an example of a stack trace. Each line of the stack trace constains the class name, the method name, the file name and the line number of the caller.

  Error
    TestCase::Minimal->sum2 at SPVM/TestCase/Minimal.spvm line 1640
    TestCase->main at SPVM/TestCase.spvm line 1198

The exception can be caught by the eval block.

Comlication Errors:

OPERAND_MESSAGE must be the string type or the undef type, otherwise a compilation error occurs.

ERROR_TYPE must be a class type, otherwise a compilation error occurs.

OPERAND_ERROR_ID must be an integer type within int, otherwise a compilation error occurs.

Examples:
  
  # Catch the exception
  eval {
    # Throw an exception
    die "Error";
  }
  
  # Check the exception
  if ($@) {
    # ...
  }
  
  die Error::System "System Error";
  
  my $error_id = 10;
  die $error_id, "Some Error";
  
=head2 Operator Statement

The operator statement executes an L<operator|/"Operators">.

This operator is composed of an operator and C<;>.
  
  # The operator statemenet
  OPERATOR;

Examples:

  1;
  $var;
  1 + 2;
  &foo();
  my $num = 1 + 2;

=head2 Empty Statement

The empty statement C<;> does nothing.

  # The empty statemenet
  ;

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

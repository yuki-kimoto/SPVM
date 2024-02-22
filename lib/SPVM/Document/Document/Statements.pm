=head1 Name

SPVM::Document::Language::Statements - Statements in SPVM Language

=head1 Description

This document describes statements in SPVM language.

=head1 Statements

Statements are the list of the statement.

Statements are written direct under the scope block.
  
  # Scope block
  {
    # Statements
    STATEMENT1
    STATEMENT2
    STATEMENT3
  }

=head2 Conditional Branch

The conditional branch is explained in the following topics.

=head3 if Statement

The C<if> statement runs conditional branch.

  if (CONDITION) {
  
  }

First, The L<boolean conversion|SPVM::Document::Language::Types/"Boolean Conversion"> is performed on the condition.

Next, if the condition is not 0, the execution position jumps to the beginning of the if block. Otherwise jumps to the end of the if block.

The local variable declartion and the initialization in the condition of the C<if> statement are allowed.

  if (my $condition = 1) {
  
  }

This is parsed as the following code.

  {
    my $condition = 1;
    if ($condition) {
    
    }
  }

Examples:

  # if statement.
  my $flag = 1;
  
  if ($flag == 1) {
    print "One\n";
  }

=head3 elsif Statement

The C<elsif> statement runs conditional branch used with the if statement

  if (CONDITION1) {
  
  }
  elsif (CONDITION2) {
  
  }

If the C<condition 1> doesn't match, the execution position jumps to the end of the if block.

Next, The L<boolean conversion|SPVM::Document::Language::Types/"Boolean Conversion"> is performed on the C<condition 2>.

Next, if the C<condition 2> is not 0, the execution position jumps to the beginning of the elsif block. Otherwise jumps to the end of the elsif block

Multiple C<elsif> statements are allowed.

  if (CONDITION1) {
  
  }
  elsif (CONDITION2) {
  
  }
  elsif (CONDITION3) {
  
  }

The local variable declartion and the initialization in the condition of the C<elsif> statement are allowed.

  if (my $condition = 1) {
  
  }
  elsif (my $condition = 2) {
  
  }

This is parsed as the following code.

  {
    my $condition = 1;
    if ($condition) {
      
    }
    else {
      my $condition = 2;
      if ($condition) {
        
      }
    }
  }

Examples:

  # elsif statement.
  my $flag = 2;
  
  if ($flag == 1) {
    print "One\n";
  }
  elsif ($flag == 2) {
    print "Two\n";
  }

=head3 else Statement

The C<else> statement runs conditional branch used with the if statement or the elsif statement.

  if (CONDITION) {
  
  }
  else {
  
  }

If the condition doesn't match, the execution position jumps to the end of the if block.

Next, the execution position jumps to the beginning of the else block.

The C<elsif> statements with the else statement are allowed.

  if (CONDITION1) {
  
  }
  elsif (CONDITION2) {
  
  }
  else {
  
  }

Examples:

  # else statement.
  my $flag = 3;
  
  if ($flag == 1) {
    print "One\n";
  }
  elsif ($flag == 2) {
    print "Two\n";
  }
  else {
    print "Other";
  }

=head3 unless Statement

The C<unless> statement runs conditional branch that does the opposite of the if statement

  unless (CONDITION) {
    
  }

The C<unless> statement is the same as the following if Statement.

  if (!CONDITION) {
    
  }

The C<unless> statements with the elsif statement and the else statement are allowed.

  unless (CONDITION1) {
    
  }
  elsif (CONDITION2) (
    
  }
  else {
    
  }

Examples:

  # unless statement.
  my $flag = 1;
  
  unless ($flag == 0) {
    print "Not Zero\n";
  }

=head3 switch Statement

The C<switch> statement runs conditional branch.

  switch (CONDITION) {
    case CASE_VALUE1: {
      # ...
    }
    case CASE_VALUE2: {
      # ...
    }
    case CASE_VALUE3: {
      # ...
    }
    default: {
      # ...
    }
  }

The L<integer promotional conversion|/"Integer Promotional Conversion"> is performed on the condition.

The value of the case statement must be one of the L<character literal|SPVM::Document::Language::Tokenization/"Character Literal">, the L<integer literal|SPVM::Document::Language::Tokenization/"Integer Literal"> or the L<getting enumeration value|SPVM::Document::Language::Operators/"Getting Enumeration Value">.

If it is a L<character literal|SPVM::Document::Language::Tokenization/"Character Literal">, the value is converted to the int type at compile-time.

If the condition matches the value of a C<case> statement, the program jumps to the beginning of the case block.

If the condition doesn't match any C<case> statements and the default statement exists, the program jumps to the beginning the default block.

If the condition doesn't match any C<case> statements and the default statement doesn't exists, the program jumps to the end of the switch block.

The C<case> statements and the default statement can be ommited.

The C<break> statement jumps to the end of the switch block.

  switch (CONDITION) {
    case CASE_VALUE1: {
      break;
    }
    case CASE_VALUE2: {
      break;
    }
    case CASE_VALUE3: {
      break;
    }
    default: {
      
    }
  }

If the last statment of the case block is not the C<break> statement, a C<break> statement is added to the end of the case block.
  
  # The break statement is ommitted.
  switch (CONDITION) {
    case CASE_VALUE1: {
    }
  }
  
  # The above becomes the following.
  switch (CONDITION) {
    case CASE_VALUE1: {
      break;
    }
  }

Multiple C<case> statements before a case block can be specified at once.

  switch (CONDITION) {
    case CASE_VALUE1:
    case CASE_VALUE2:
    {
      # ...
    }
  }

Compilation Errors:

The condition must be an integer type within int. Otherwise a compilation error occurs.

The values of the case statements cannnot be duplicated. If so, a compilation error occurs.

Examples:

  # switch statement
  my $code = 2;
  my $flag = 1;
  switch ($code) {
    case 1: {
      print "1\n";
    }
    case 2: {
      print "2\n";
    }
    case 3: {
      if ($flag) {
        break;
      }
      print "3\n";
    }
    case 4:
    case 5:
    {
      print "4 or 5\n";
    }
    default: {
      print "Other\n";
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
          print "1\n";
        }
        case Foo->ID2: {
          print "2\n";
        }
        case Foo->ID3: {
          if ($flag) {
            break;
          }
          print "3\n";
        }
        default: {
          print "Other\n";
        }
      }
    }
  }

=head4 case Statement

The C<case> statement specifies a case value and a branch of a L<switch statement|/"switch Statement">.

  # The case statement
  switch (CONDITION) {
    case CASE_VALUE1: {
      # ...
    }
  }

=head4 default Statement

The C<default> statement specifies a default branch of a L<switch statement|/"switch Statement">.

  # The default statement
  switch (CONDITION) {
    default: {
      # ...
    }
  }

=head4 break Statement

The C<break> statement is jumps to the end of the switch block of the L<switch statement|/"switch Statement">.

  # The break statement
  break;

=head2 Loop Syntax

=head3 while Statement

The C<while> statement runs loop.

  while (CONDITION) {
  
  }

First, The L<boolean conversion|SPVM::Document::Language::Types/"Boolean Conversion"> is performed on the condition.

Next, If the condition is 0, the program jumps to the end of the while block. Otherwise the program goes to the beginning of the while block.

When the program reaches the end of the while block, it jumps back to the while statement and evaluates the condition again.

Examples:

  # The while statement
  my $i = 0;
  while ($i < 5) {
  
    print "$i\n";
  
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
    
    print "$i\n";
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
    print "$i\n";
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
    print "$elemenet\n";
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

If the return type of the current L<method|SPVM::Document::Language::Class/"Method Definition"> is the non-void type, I<OPERAND> must exist. Otherwise a compilation error occurs.

The type of I<OPERAND> must satisfy L<type assignability|SPVM::Document::Language::Types/"Type Assignability"> to the return type of the current method. Otherwise a compilation error occurs.

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

OPERAND_MESSAGE must be the string type or the undef type. Otherwise a compilation error occurs.

ERROR_TYPE must be a class type. Otherwise a compilation error occurs.

OPERAND_ERROR_ID must be an integer type within int. Otherwise a compilation error occurs.

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

The operator statement executes an operator.

This operator is composed of an L<operator|/"Operators"> and C<;>.
  
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

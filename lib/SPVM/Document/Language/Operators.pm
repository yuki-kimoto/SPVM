=encoding utf8

=head1 Name

SPVM::Document::Language::Operators - Operators in the SPVM Language

=head1 Description

This document describes operators in the SPVM language.

=head1 Operators

An operator is a basic instruction that normally a return value.

=head2 Numeric Operators

=head3 Unary Plus Operator

The unary plus operator C<+> is a unary operator that returns its operand.

  +OPERAND

This operator performs L<integer promotional conversion|/"Integer Promotional Conversion"> on the operand I<OPERAND>, and returns it.

The return type is the type after the conversion is performed.

Compilation Errors:

The type of I<OPERAND> must be a L<numeric type|SPVM::Document::Language::Types/"Numeric Types">. Otherwise, a compilation error occurs.

Examples:
  
  # Examples of the unary plus operator
  my $num = +10;

=head3 Unary Minus Operator

The unary minus operator C<-> is a unary operator that returns the negated value of its operand.

  -OPERAND

This operator performs L<integer promotional conversion|/"Integer Promotional Conversion"> on the operand I<OPERAND>, negates it, and returns it.

The return type is the type after the conversion is performed.

Compilation Errors:

The type of I<OPERAND> must be a L<numeric type|SPVM::Document::Language::Types/"Numeric Types">. Otherwise, a compilation error occurs.

Examples:

  # Examples of the unary minus operator
  my $num = -10;

=head3 Addition Operator

The addition operator C<+> adds two operands.
  
  LEFT_OPERAND + RIGHT_OPERAND

This operator performs L<binary numeric conversion|/"Binary Numeric Conversion"> on the left operand I<LEFT_OPERAND> and the right operand I<RIGHT_OPERAND>.

And it performs the same operation as the following C language operation, and returns its return value.

  LEFT_OPERAND + RIGHT_OPERAND

The return type is the type after L<binary numeric conversion|/"Binary Numeric Conversion"> is performed.

Compilation Errors:

The type of I<LEFT_OPERAND> must be a L<numeric type|SPVM::Document::Language::Types/"Numeric Types">. Otherwise, a compilation error occurs.

The type of I<RIGHT_OPERAND> must be a L<numeric type|SPVM::Document::Language::Types/"Numeric Types">. Otherwise, a compilation error occurs.

Examples:

  # Examples of addition operator
  my $result = 1 + 2;

=head3 Subtraction Operator

The subtraction operator C<-> subtracts its right operand from its left operand.
  
  LEFT_OPERAND - RIGHT_OPERAND

This operator performs L<binary numeric conversion|/"Binary Numeric Conversion"> on the left operand I<LEFT_OPERAND> and the right operand I<RIGHT_OPERAND>.

And it performs the same operation as the following C language operation, and returns its return value.

  LEFT_OPERAND - RIGHT_OPERAND

The return type is the type after L<binary numeric conversion|/"Binary Numeric Conversion"> is performed.

Compilation Errors:

The type of I<LEFT_OPERAND> must be a L<numeric type|SPVM::Document::Language::Types/"Numeric Types">. Otherwise, a compilation error occurs.

The type of I<RIGHT_OPERAND> must be a L<numeric type|SPVM::Document::Language::Types/"Numeric Types">. Otherwise, a compilation error occurs.

Examples:

  # Examples of subtraction operator
  my $result = 1 - 2;

=head3 Multiplication Operator

The multiplication operator C<*> multiplies two operands.
  
  LEFT_OPERAND * RIGHT_OPERAND

This operator performs L<binary numeric conversion|/"Binary Numeric Conversion"> on the left operand I<LEFT_OPERAND> and the right operand I<RIGHT_OPERAND>.

And it performs the same operation as the following C language operation, and returns its return value.

  LEFT_OPERAND * RIGHT_OPERAND

The return type is the type after L<binary numeric conversion|/"Binary Numeric Conversion"> is performed.

Compilation Errors:

The type of I<LEFT_OPERAND> must be a L<numeric type|SPVM::Document::Language::Types/"Numeric Types">. Otherwise, a compilation error occurs.

The type of I<RIGHT_OPERAND> must be a L<numeric type|SPVM::Document::Language::Types/"Numeric Types">. Otherwise, a compilation error occurs.

Examples:

  # Examples of multiplication operator
  my $result = 1 * 2;

=head3 Division Operator

The division operator C</> divides its left operand by its right operand.
  
  LEFT_OPERAND / RIGHT_OPERAND

This operator performs L<binary numeric conversion|/"Binary Numeric Conversion"> on the left operand I<LEFT_OPERAND> and the right operand I<RIGHT_OPERAND>.

And it performs the same operation as the following C language operation, and returns its return value.

  LEFT_OPERAND / RIGHT_OPERAND

The return type is the type after L<binary numeric conversion|/"Binary Numeric Conversion"> is performed.

Exceptions:

If the left operand type I<LEFT_OPERAND> and the right operand I<RIGHT_OPERAND> are an integer type and I<RIGHT_OPERAND> is 0, an exception is thrown.

Compilation Errors:

The type of I<LEFT_OPERAND> must be a L<numeric type|SPVM::Document::Language::Types/"Numeric Types">. Otherwise, a compilation error occurs.

The type of I<RIGHT_OPERAND> must be a L<numeric type|SPVM::Document::Language::Types/"Numeric Types">. Otherwise, a compilation error occurs.

Examples:

  # Examples of division operator
  my $result = 1 / 2;

=head3 Division Unsigned Int Operator

The division unsigned int operator C<div_uint> interprets its two operands as unsigned 32bit integers, and divides its left operand by its right operand.
  
  LEFT_OPERAND div_uint RIGHT_OPERAND

This operator performs the same operation as the following C language operation, and returns its return value.

  (uint32_t)LEFT_OPERAND / (uint32_t)RIGHT_OPERAND

The return type is int type.

Exceptions:

If I<RIGHT_OPERAND> is 0, an exception is thrown.

Compilation Errors:

The type of I<LEFT_OPERAND> must be int type. Otherwise, a compilation error occurs.

The type of I<RIGHT_OPERAND> must be int type. Otherwise, a compilation error occurs.

Examples:

  # Examples of the division unsigned int operator
  my $result = 1 div_uint 2;

=head3 Division Unsigned Long Operator

The division unsigned long operator C<div_ulong> interprets its two operands as unsigned 64bit integers, and divides its left operand by its right operand.

  LEFT_OPERAND div_ulong RIGHT_OPERAND

This operator performs the same operation as the following C language operation, and returns its return value.

  (uint64_t)LEFT_OPERAND / (uint64_t)RIGHT_OPERAND

The return type is long type.

Exceptions:

If I<RIGHT_OPERAND> is 0, an exception is thrown.

Compilation Errors:

The type of I<LEFT_OPERAND> must be long type. Otherwise, a compilation error occurs.

The type of I<RIGHT_OPERAND> must be long type. Otherwise, a compilation error occurs.

Examples:

  # Examples of the division unsigned long operator
  my $result = 1L div_ulong 2L;

=head3 Modulo Operator

The modulo operator C<%> calculates the modulo of the division of its two operands.
  
  LEFT_OPERAND % RIGHT_OPERAND

This operator performs L<binary numeric conversion|/"Binary Numeric Conversion"> on the left operand I<LEFT_OPERAND> and the right operand I<RIGHT_OPERAND>.

And it performs the same operation as the following C language operation, and returns its return value.

  RETURN_VALUE = LEFT_OPERAND % RIGHT_OPERAND;
  if ((LEFT_OPERAND < 0) != (RIGHT_OPERAND < 0) && RETURN_VALUE) { RETURN_VALUE += RIGHT_OPERAND; }

The return type is the type after L<binary numeric conversion|/"Binary Numeric Conversion"> is performed.

Exceptions:

If I<RIGHT_OPERAND> is 0, an exception is thrown.

Compilation Errors:

The type of I<LEFT_OPERAND> must be an L<integer type|SPVM::Document::Language::Types/"Integer Types">. Otherwise, a compilation error occurs.

The type of I<RIGHT_OPERAND> must be an L<integer type|SPVM::Document::Language::Types/"Integer Types">. Otherwise, a compilation error occurs.

Examples:

  # Examples of modulo operator
  my $result = 1 % 2;

=head3 Modulo Unsigned Int Operator

The modulo unsigned int operator C<mod_uint> interprets its two operands as unsigned 32bit integers, and calculates the modulo of the division of its two operands.
  
  LEFT_OPERAND mod_uint RIGHT_OPERAND

This operator performs the same operation as the following C language operation, and returns its return value.

  (uint32_t)LEFT_OPERAND % (uint32_t)RIGHT_OPERAND

The return type is int type.

Exceptions:

If I<RIGHT_OPERAND> is 0, an exception is thrown.

Compilation Errors:

The type of I<LEFT_OPERAND> must be int type. Otherwise, a compilation error occurs.

The type of I<RIGHT_OPERAND> must be int type. Otherwise, a compilation error occurs.

Examples:

  # Examples of the modulo unsigned int operator
  my $result = 1 mod_uint 2;

=head3 Modulo Unsigned Long Operator

The modulo unsigned long operator C<mod_ulong> interprets its two operands as unsigned 64bit integers, and calculates the modulo of the division of its two operands.
  
  LEFT_OPERAND mod_ulong RIGHT_OPERAND

This operator performs the same operation as the following C language operation, and returns its return value.

  (uint64_t)LEFT_OPERAND % (uint64_t)RIGHT_OPERAND

The return type is is long type.

Exceptions:

If I<RIGHT_OPERAND> is 0, an exception is thrown.

Compilation Errors:

The type of I<LEFT_OPERAND> must be long type. Otherwise, a compilation error occurs.

The type of I<RIGHT_OPERAND> must be long type. Otherwise, a compilation error occurs.

Examples:

  # Examples of the modulo unsigned long operator
  my $result = 1L mod_ulong 2L;

=head3 Increment Operators

=head4 Pre-Increment Operator

The pre-increment operator C<++> increases the value of an operand by 1, and returns it.

  ++OPERAND

This operator increases the value of the operand I<OPERAND> by 1 using L<additonal operator|/"Addition Operator">, performs a L<type cast|/"Type Cast"> to the type of I<OPERAND> on it, and returns it.

The return type is the type of I<OPERAND>.

Compilation Errors:

I<OPERAND> must be a local variable, a class variable, a field access, an element access, a dereference. Otherwise, a compilation error occurs.

The type of I<OPERAND> must be a numeric type. Otherwise, a compilation error occurs.

Examples:
  
  # Examples of the pre-increment operator
  
  # A local variable
  ++$num;
  
  # A class variable
  ++$NUM;
  
  # A field access
  ++$point->{x};
  
  # An element access
  ++$nums->[0];
  
  # A dereference
  ++$$num_ref;

=head4 Post-Increment Operator

The post-increment operator C<++> increases the value of an operand by 1, and returns the value before performing the incrementation.

  OPERAND++

This operator increases the value of the operand I<OPERAND> by 1 using L<additonal operator|/"Addition Operator">, performs a L<type cast|/"Type Cast"> to the type of I<OPERAND> on it, assigns it on I<OPERAND>, and returns I<OPERAND> before performing the incrementation.

The return type is the type of I<OPERAND>.

Compilation Errors:

I<OPERAND> must be a local variable, a class variable, a field access, an element access, a dereference. Otherwise, a compilation error occurs.

The type of I<OPERAND> must be a numeric type. Otherwise, a compilation error occurs.

Examples:
  
  # Examples of the post-increment operator
  
  # A local variable
  $num++;
  
  # A class variable
  $NUM++;
  
  # A field access
  $point->{x}++;
  
  # An element access
  $nums->[0]++;
  
  # A dereference
  $$num_ref++;

=head3 Decrement Operators

=head4 Pre-Decrement Operator

The pre-decrement operator C<--> decreases the value of an operand by 1, and returns it.

  --OPERAND

This operator decreases the value of the operand I<OPERAND> by 1 using L<subtraction operator|/"Subtraction Operator">, performs a L<type cast|/"Type Cast"> to the type of I<OPERAND> on it, and returns it.

The return type is the type of I<OPERAND>.

Complation Errors:

I<OPERAND> must be a local variable, a class variable, a field access, an element access, a dereference. Otherwise, a compilation error occurs.

The type of I<OPERAND> must be a numeric type. Otherwise, a compilation error occurs.

Examples:
  
  # Examples of the pre-decrement operator
  
  # A local variable
  --$num;
  
  # A class variable
  --$NUM;
  
  # A field access
  --$point->{x};
  
  # An element access
  --$nums->[0];
  
  # A dereferenced value
  --$$num_ref;

=head4 Post-Decrement Operator

The post-increment operator C<--> decreases the value of an operand by 1, and returns the value before performing the decrementation.

  OPERAND--

This operator decreases the value of the operand I<OPERAND> by 1 using L<subtraction operator|/"Subtraction Operator">, performs a L<type cast|/"Type Cast"> to the type of I<OPERAND> on it, assigns it on I<OPERAND>, and returns I<OPERAND> before performing the decrementation.

The return type is the type of I<OPERAND>.

Compilation Errors:

I<OPERAND> must be a local variable, a class variable, a field access, an element access, a dereference. Otherwise, a compilation error occurs.

The type of I<OPERAND> must be a numeric type. Otherwise, a compilation error occurs.

Examples:
  
  # Examples of the post-decrement operator
  
  # A local variable
  $num--;
  
  # A class variable
  $NUM--;
  
  # A field access
  $point->{x}--;
  
  # An element access
  $nums->[0]--;
  
  # A dereference
  $$num_ref--;

=head3 Bitwise Operators

=head4 Bitwise AND Operator

The bitwise AND operator C<&> performs L<bitwise AND operation|https://en.wikipedia.org/wiki/Bitwise_operation#AND>.

  LEFT_OPERAND & RIGHT_OPERAND

This operator performs L<binary numeric conversion|/"Binary Numeric Conversion"> on the left operand I<LEFT_OPERAND> and the right operand I<RIGHT_OPERAND>.

And it performs the same operation as the following C language operation, and returns its return value.

  LEFT_OPERAND & RIGHT_OPERAND

The return type is the type after L<binary numeric conversion|/"Binary Numeric Conversion"> is performed.

Compilation Errors:

The type of I<LEFT_OPERAND> must be an L<integer type|SPVM::Document::Language::Types/"Integer Types">. Otherwise, a compilation error occurs.

The type of I<RIGHT_OPERAND> must be an L<integer type|SPVM::Document::Language::Types/"Integer Types">. Otherwise, a compilation error occurs.

Examples:
  
  # Examples of bitwise AND operator
  my $num1 = 0xff;
  my $num2 = 0x12;
  my $result = $num1 & $num2;

=head4 Bitwise OR Operator

The bitwise OR operator C<|> performs L<bitwise OR operation|https://en.wikipedia.org/wiki/Bitwise_operation#OR>.
  
  LEFT_OPERAND | RIGHT_OPERAND

This operator performs L<binary numeric conversion|/"Binary Numeric Conversion"> on the left operand I<LEFT_OPERAND> and the right operand I<RIGHT_OPERAND>.

And it performs the same operation as the following C language operation, and returns its return value.

  LEFT_OPERAND | RIGHT_OPERAND

The return type is the type after L<binary numeric conversion|/"Binary Numeric Conversion"> is performed.

Compilation Errors:

The type of I<LEFT_OPERAND> must be an L<integer type|SPVM::Document::Language::Types/"Integer Types">. Otherwise, a compilation error occurs.

The type of I<RIGHT_OPERAND> must be an L<integer type|SPVM::Document::Language::Types/"Integer Types">. Otherwise, a compilation error occurs.

Examples:
  
  # Examples of the bitwise OR operator
  my $num1 = 0xff;
  my $num2 = 0x12;
  my $result = $num1 | $num2;

=head4 Bitwise NOT Operator

The bitwise NOT operator C<~> performs L<bitwise NOT operation|https://en.wikipedia.org/wiki/Bitwise_operation#NOT>.
  
  ~OPERAND

This operator performs L<numeric widening conversion|/"Numeric Widening Conversion"> on the operand I<OPERAND>.

And it performs the same operation as the following C language operation, and returns its return value.

  ~OPERAND

The return type is the type that L<numeric widening conversion|/"Numeric Widening Conversion"> is performed.

Compilation Errors:

The type of I<OPERAND> must be an L<integer type|SPVM::Document::Language::Types/"Integer Types">. Otherwise, a compilation error occurs.

Examples:
  
  # Examples of bitwise NOT operator
  my $result = ~0xFF0A;

=head3 Shift Operators

=head4 Left Shift Operator

The left shift operator C<E<lt>E<lt>> performs L<arithmetic left shift|https://en.wikipedia.org/wiki/Bitwise_operation#Arithmetic_shift>.

  LEFT_OPERAND << RIGHT_OPERAND

This operator performs L<numeric widening conversion|/"Numeric Widening Conversion"> on the left operand I<LEFT_OPERAND>.

And it performs L<numeric widening conversion|/"Numeric Widening Conversion"> on the right operand I<RIGHT_OPERAND>.

And it performs the same operation as the following C language operation, and returns its return value.

  LEFT_OPERAND << RIGHT_OPERAND

The return type is the type of I<LEFT_OPERAND>.

Compilation Erorrs:

The type of I<LEFT_OPERAND> must be an L<integer type|SPVM::Document::Language::Types/"Integer Types">. Otherwise, a compilation error occurs.

The type of I<RIGHT_OPERAND> must be an L<integer types|SPVM::Document::Language::Types/"Integer Types"> within int. Otherwise, a compilation error occurs.

Examples:

  # Examples of left shift operator
  my $result = 0xFF0A << 3;

=head4 Arithmetic Right Shift Operator

The arithmetic right shift operator C<E<gt>E<gt>> performs L<arithmetic right shift|https://en.wikipedia.org/wiki/Bitwise_operation#Arithmetic_shift>.

  LEFT_OPERAND >> RIGHT_OPERAND

This operator performs L<numeric widening conversion|/"Numeric Widening Conversion"> on the left operand I<LEFT_OPERAND>.

And it performs L<numeric widening conversion|/"Numeric Widening Conversion"> on the right operand I<RIGHT_OPERAND>.

And it performs the same operation as the following C language operation, and returns its return value.

  LEFT_OPERAND >> RIGHT_OPERAND;

The return type is the type of I<LEFT_OPERAND>.

Compilation Errors:

The type of I<LEFT_OPERAND> must be an L<integer type|SPVM::Document::Language::Types/"Integer Types">. Otherwise, a compilation error occurs.

The type of I<RIGHT_OPERAND> must be an L<integer types|SPVM::Document::Language::Types/"Integer Types"> within int. Otherwise, a compilation error occurs.

Examples:

  # Examples of arithmetic right shift operator
  my $result = 0xFF0A >> 3;

=head4 Logical Right Shift Operator

The logical right shift operator C<E<gt>E<gt>E<gt>> performs L<logical right shift|https://en.wikipedia.org/wiki/Bitwise_operation#Logical_shift>.
  
  LEFT_OPERAND >>> RIGHT_OPERAND

This operator performs L<numeric widening conversion|/"Numeric Widening Conversion"> on the left operand I<LEFT_OPERAND>.

And it performs L<numeric widening conversion|/"Numeric Widening Conversion"> on the right operand I<RIGHT_OPERAND>.

And if the type of I<LEFT_OPERAND> is int type, it performs the same operation as the following C language operation

  (uint32_t)LEFT_OPERAND >> RIGHT_OPERAND

If the type of I<LEFT_OPERAND> is long type, it performs the same operation as the following C language operation.

  (uint64_t)LEFT_OPERAND >> RIGHT_OPERAND

And returns its return value.

The return type is the type of I<LEFT_OPERAND>.

Compilation Errors:

The type of I<LEFT_OPERAND> must be an L<integer type|SPVM::Document::Language::Types/"Integer Types">. Otherwise, a compilation error occurs.

The type of I<RIGHT_OPERAND> must be an L<integer types|SPVM::Document::Language::Types/"Integer Types"> within int. Otherwise, a compilation error occurs.

Examples:

  # Examples of logical right shift operator
  my $result = 0xFF0A >>> 3;

=head2 Logical Operators

=head3 Logical AND Operator

The logical AND operator C<&&> performs a logical AND operation.
  
  LEFT_OPERAND && RIGHT_OPERAND

This operator performs L<condition evaluation|/"Condition Evaluation"> on the left operand I<LEFT_OPERAND>.

If the evaluated value is 0, it returns 0. Otherwise, performs L<condition evaluation|/"Condition Evaluation"> on the right operand I<RIGHT_OPERAND>.

And it returns the evaluated value of I<RIGHT_OPERAND>.

The return type is int type.

Examples:

  # Examples of logical AND operator
  if (1 && 0) {
    
  }

=head3 Logical OR Operator

The logical OR operator C<||> performes a logical OR operation.

  # logical OR operator
  LEFT_OPERAND || RIGHT_OPERAND

Thg logical OR operator performs L<condition evaluation|/"Condition Evaluation"> on the left operand I<LEFT_OPERAND>.

If the evaluated value is not 0, it returns the evaluated value. Otherwise, performs L<condition evaluation|/"Condition Evaluation"> on the right operand I<RIGHT_OPERAND>.

And it returns the evaluated value of I<RIGHT_OPERAND>.

The return type is int type.

Examples:

  # Examples of logical OR operator
  if (1 || 0) {
    
  }

=head3 Logical NOT Operator

The logical NOT operator C<!> performes a logical NOT operation.

  !OPERAND

Thg logical NOT operator performs L<condition evaluation|/"Condition Evaluation"> on the operand I<OPERAND>.

If the evaluated value is 0, returns 1, otherwise returns 0.

The return type is int type.

  # Examples of logical NOT operator
  if (!1) {
    
  }

=head2 Defined-OR  Operator

The defined-OR operator C<//> performes a defined-OR operation.

  # defined-OR operator
  LEFT_OPERAND // RIGHT_OPERAND

Thg defined-OR operator performs L<condition evaluation|/"Condition Evaluation"> on the left operand I<LEFT_OPERAND>.

If the evaluated value is not 0, it returns the evaluated value. Otherwise, returns I<RIGHT_OPERAND>.

The return type is the type of I<LEFT_OPERAND>.

Compilation Errors:

The left operand type of defined-or operator // must be an object type. Otherwise, an compication error occurs.

Examples:

  # Examples of defined-OR operator
  my $value = "foo";
  my $default = "default";
  my $ret = $value // $default;

=head2 Ternary Operator

The ternary operator performes a ternary operation.

  # ternary operator
  CONDITION ? LEFT_OPERAND : RIGHT_OPERAND

The type of I<LEFT_OPERAND> and I<RIGHT_OPERAND> must satisfy assignment requrement to any object type.

I<CONDITION> is evaluated by L<condition evaluation|/"Condition Evaluation">.

If the evaluated value is not 0, it returns I<LEFT_OPERAND>. Otherwise, returns I<RIGHT_OPERAND>.

The return type is the type of I<LEFT_OPERAND>.

Compilation Errors:



Examples:

  # Examples of ternary operator
  my $flag = 1;
  my $left = "foo";
  my $right = "default";
  my $ret = $flag ? $left : $right;

=head2 Condition Evaluation

The condition evaluation is the operation performed on the operand at a conditional part of L<if statement|SPVM::Document::Language::Statements/"if Statement">, L<while statement|SPVM::Document::Language::Statements/"while Statement">, and L<logical operators|/"Logical Operators">.

The condition evaluation performs the following operations corresponding to the operand type.

The return type is int type.

B<byte:>

B<short:>

B<int:>

The L<integer promotional conversion|/"Integer Promotional Conversion"> is performed on the operand.

And return the value after conversion.

B<undef:>

Returns 0.

B<BOOL:>

Return the C<value> field in L<Bool|SPVM::Bool> object.

B<long:>

B<float:>

B<double:>

B<a reference type:> 

Performs the following C language operation, and returns it.

  !!OPERAND

B<an object type:>

If the compile type of the operand is not L<Bool|SPVM::Bool> class, performs the following C language operation, and returns it.

  !!OPERAND

Compilation Errors:

The operand type of the condition evaluation must be a L<numeric type|SPVM::Document::Language::Types/"Numeric Types">, an L<object type|SPVM::Document::Language::Types/"Object Types">, a L<reference type|SPVM::Document::Language::Types/"Reference Types">, or L<undef type|SPVM::Document::Language::Types/"undef Type">. Otherwise, a compilation error occurs.

Examples:
  
  # Examples of the condition evaluation
  if (1) {
    # ok
  }
  
  if (0) {
    # not ok
  }
  
  if (1.5) {
    # ok
  }
  
  if (0.0) {
    # not ok
  }
  
  if (true) {
    # ok
  }
  
  if (Bool->TRUE) {
    # ok
  }
  
  if (false) {
    # not ok
  }
  
  if (Bool->FALSE) {
    # not ok
  }
  
  my $object = SPVM::Int->new(1);
  
  if ($object) {
    # ok
  }
  
  $object = undef;
  if ($object) {
    # not ok
  }
  
  my $value = 1;
  my $ref = \$value;
  
  if ($ref) {
    # ok
  }
  
  if (undef) {
    # not ok
  }

=head2 Array Length Operator

The array length operator C<@> gets the length of an array.
  
  @OPERAND
  @{OPERAND}

This operator returns the length the array I<OPERAND>.

The return type is int type.

If I<OPERAND> is a class type or an interface type, this operation is replaced with C<length> method call of L<Countable|SPVM::Countable> interface.

  OPERAND->length

Exceptions:

I<OPERAND> must be defined. Otherwise, an exception is thrown.

Compilation Errors:

The type of I<OPERAND> must be an array type or a class with L<Countable|SPVM::Countable> interface. Otherwise, a compilation error occurs.

Examples:
  
  # Examples of the array length operator
  my $nums = new int[10];
  my $length = @$nums;

=head2 scalar Operator

The C<scalar> operator returns its operand.

  scalar OPERAND

This operator returns the operand I<OPERAND>. I<OPERAND> must be L<array length operator|/"Array Length Operator">.

This operator exists only for readability.

The return type is int type.

Compilation Errors:

I<OPERAND> must be L<array length operator|/"Array Length Operator">. Otherwise, a compilation error occurs.

Examples:
  
  # Examples of scalar operator
  my $nums = new int[3];
  say scalar @$nums;

=head2 Sequential Operator

The sequential operator is an operator with the following syntax.
  
  (OPERAND1, OPERAND2, ..., OPERANDn)

This operator evaluates operands C<OPERAND1>, C<OPERAND1> ... C<OPERANDn> from left to right, and returns the value of the rightmost operand C<OPERANDn>.

The return type is the type of C<OPERANDn>.

The L<if statement|SPVM::Document::Language::Statements/"if Statement"> C<IF_STATEMENT> can place directory before C<OPERANDn>.

  (OPERAND1, OPERAND2, ..., IF_STATEMENT, OPERANDn)

Examples:

  # Examples of sequential operator
  
  # 3 is assigned to $foo
  my $foo = (1, 2, 3);
  
  # $x is 3, $ret is 5
  my $x = 1;
  my $y = 2;
  my $result = ($x += 2, $x + $y);
  
  # Peseud ternary operator
  {
    my $condition = 1;
    my $ret = (my $_ = 0, if ($condition) { $_ = 3; } else { $_ = 5; }, $_);
  }

=head2 Comparison Operators

Comparison operators compare two operands.

=head3 Numeric Comparison Operators

Numeric comparison operators compare two numbers or two addresses of objects.

  LEFT_OPERAND == RIGHT_OPERAND
  LEFT_OPERAND != RIGHT_OPERAND
  LEFT_OPERAND > RIGHT_OPERAND
  LEFT_OPERAND >= RIGHT_OPERAND
  LEFT_OPERAND < RIGHT_OPERAND
  LEFT_OPERAND <= RIGHT_OPERAND
  LEFT_OPERAND <=> RIGHT_OPERAND

This operator performs L<binary numeric conversion|/"Binary Numeric Conversion"> on the left operand I<LEFT_OPERAND> and the right operand I<RIGHT_OPERAND>.

And it performs the same operation as the following C language operation, and returns its return value.

  (int32_t)(LEFT_OPERAND == RIGHT_OPERAND);
  (int32_t)(LEFT_OPERAND != RIGHT_OPERAND);
  (int32_t)(LEFT_OPERAND > RIGHT_OPERAND);
  (int32_t)(LEFT_OPERAND >= RIGHT_OPERAND);
  (int32_t)(LEFT_OPERAND < RIGHT_OPERAND);
  (int32_t)(LEFT_OPERAND <= RIGHT_OPERAND);
  (int32_t)(LEFT_OPERAND > RIGHT_OPERAND ? 1 : LEFT_OPERAND < RIGHT_OPERAND ? -1 : 0);

The return type is int type.

Compilation Errors:

C<==>, C<!=>

The type of the I<LEFT_OPERAND> must be a numeric type, an object type, a reference type, or the undef type. Otherwise, a compilation error occurs.

The type of the I<RIGHT_OPERAND> must be a numeric type, an object type, a reference type, or the undef type. Otherwise, a compilation error occurs.

If the type of the I<LEFT_OPERAND> is a numeric type, the type of the I<RIGHT_OPERAND> must be a numeric type. Otherwise, a compilation error occurs.

If the type of the I<LEFT_OPERAND> is an object type, the type of the I<RIGHT_OPERAND> must be an object type or the undef type. Otherwise, a compilation error occurs.

If the type of the I<LEFT_OPERAND> is the undef type, the type of the I<RIGHT_OPERAND> must be an object type or the undef type. Otherwise, a compilation error occurs.

If the type of the I<LEFT_OPERAND> is a reference type, the type of the I<RIGHT_OPERAND> must be a reference type or undef type. Otherwise, a compilation error occurs.

C<E<lt>>, C<E<lt>=>, C<E<gt>>, C<E<gt>=>, C<E<lt>=E<gt>>

The type of the I<LEFT_OPERAND> must be a numeric type. Otherwise, a compilation error occurs.

The type of the I<RIGHT_OPERAND> must be a numeric type. Otherwise, a compilation error occurs.

=head3 String Comparison Operators

String comparison operators compare tow strings in the dictionary order.

  LEFT_OPERAND eq RIGHT_OPERAND
  LEFT_OPERAND ne RIGHT_OPERAND
  LEFT_OPERAND gt RIGHT_OPERAND
  LEFT_OPERAND ge RIGHT_OPERAND
  LEFT_OPERAND lt RIGHT_OPERAND
  LEFT_OPERAND le RIGHT_OPERAND
  LEFT_OPERAND cmp RIGHT_OPERAND

These operators perform the following operations.

=begin html

<table>
  <tr>
    <th>Operators</th>
    <th>Operations</th>
  </tr>
  <tr>
    <td>
      <i>eq</i>
    </td>
    <td>
      If <i>LEFT_OPERAND</i> is equal to <i>RIGHT_OPERAND</i> in the dictionary order, returns 1, otherwise returns 0.
    </td>
  </tr>
  <tr>
    <td>
      <i>ne</i>
    </td>
    <td>
      If <i>LEFT_OPERAND</i> is not equal to <i>RIGHT_OPERAND</i> in the dictionary order, returns 1, otherwise returns 0.
    </td>
  </tr>
  <tr>
    <td>
      <i>gt</i>
    </td>
    <td>
      If <i>LEFT_OPERAND</i> is greater than <i>RIGHT_OPERAND</i> in the dictionary order, returns 1, otherwise returns 0.
    </td>
  </tr>
  <tr>
    <td>
      <i>ge</i>
    </td>
    <td>
      If <i>LEFT_OPERAND</i> is greater than or equal to <i>RIGHT_OPERAND</i> in the dictionary order, returns 1, otherwise returns 0.
    </td>
  </tr>
  <tr>
    <td>
      <i>lt</i>
    </td>
    <td>
      If <i>LEFT_OPERAND</i> is less than <i>RIGHT_OPERAND</i> in the dictionary order, returns 1, otherwise returns 0.
    </td>
  </tr>
  <tr>
    <td>
      <i>le</i>
    </td>
    <td>
      If <i>LEFT_OPERAND</i> is less than or equal to <i>RIGHT_OPERAND</i> in the dictionary order, returns 1, otherwise returns 0.
    </td>
  </tr>
  <tr>
    <td>
      <i>cmp</i>
    </td>
    <td>
      If <i>LEFT_OPERAND</i> is greater than <i>RIGHT_OPERAND</i> in the dictionary order, returns 1. If <i>LEFT_OPERAND</i> is less than <i>RIGHT_OPERAND</i> in the dictionary order, return -1. If <i>LEFT_OPERAND</i> is equal to <i>RIGHT_OPERAND</i> in the dictionary order, returns 0.
    </td>
  </tr>
</table>

=end html

The return type is int type. 

Compilation Errors.

The type of I<LEFT_OPERAND> must be string type or the byte[] type. Otherwise, a compilation error occurs.

The type of I<RIGHT_OPERAND> must be string type or the byte[] type. Otherwise, a compilation error occurs.

=head2 Constant Operator

The constant operator gets a constant value represented by a literal.

  LITERAL

I<LITERAL> is a L<literal|SPVM::Document::Language::Tokenization/"Literals">.

The return type is the type of I<LITERAL>.

Compilation Errors:

Compilation errors casued by L<literal|SPVM::Document::Language::Tokenization/"Literals"> syntax could occur.

=head2 length Operator

The C<length> operator gets the length of a string.

  length OPERAND

If the string I<OPERAND> is defind, this operator returns the length of I<OPERAND>. Note that this length is in bytes, not the number of UTF-8 characters.

If I<OPERAND> is not defined, returns 0.

The return type is int type.

Compilation Errors:

The type of I<OPERAND> must be string type. Otherwise, a compilation error occurs.

Examples:
  
  # Examples of The length operator
  
  # The length is 5
  my $message = "Hello";
  my $length = length $message;
  
  # The length is 9
  my $message = "あいう";
  my $length = length $message;

=head2 capacity Operator

The C<capacity> operator gets the capacity of a string or an array.

  capacity OPERAND

This operator returns the capacity of I<OPERAND>.

The return type is int type.

Exceptions:

I<OPERAND> must be defined. Otherwise, an exception is thrown.

Compilation Errors:

The type of I<OPERAND> must be string type or an array type. Otherwise, a compilation error occurs.

Examples:
  
  # Examples of capacity operator
  
  # The capacity is 5
  my $message = "Hello";
  my $capacity = capacity $message;
  
=head2 String Concatenation Operator

The string concatenation operator C<.> concats two strings.
  
  LEFT_OPERAND . RIGHT_OPERAND

This operator performs L<numeric-to-string conversion|/"Numeric-to-String Conversion"> on the left operand I<LEFT_OPERAND> if the type of I<LEFT_OPERAND> is a L<numeric type|SPVM::Document::Language::Types/"Numeric Types">.

And it performs L<numeric-to-string conversion|/"Numeric-to-String Conversion"> on the right operand I<RIGHT_OPERAND> if the type of I<RIGHT_OPERAND> is a L<numeric type|SPVM::Document::Language::Types/"Numeric Types">.

And it concats I<LEFT_OPERAND> and I<RIGHT_OPERAND>, and returns its return value.

The type of I<LEFT_OPERAND> and I<RIGHT_OPERAND> are allowed to be the byte[] type.

The return type is string type.

Exceptions:

I<LEFT_OPERAND> must be defined. Otherwise, an exception is thrown.

I<RIGHT_OPERAND> must be defined. Otherwise, an exception is thrown.

Compilation Errors:

The type of I<LEFT_OPERAND> must be string type, the byte[] type, or a numeric type. Otherwise, a compilation error occurs.

The type of I<RIGHT_OPERAND> must be string type, the byte[] type, or a numeric type. Otherwise, a compilation error occurs.

Examples:
  
  # Examples of the string concatenation operator
  my $result = "abc" . "def";
  my $result = "def" . 34;

=head2 new_string_len Operator

The C<new_string_len> operator creates a new string with a length.
  
  new_string_len OPERAND

This operator performs L<integer promotional conversion|/"Integer Promotional Conversion"> on the length I<OPERAND>.

And creates a new string with the length, fills all characters in the string with C<\0>, and returns it.

The return type is mutable string type.

Exceptions:

I<OPERAND> must be greater than or equal to 0. Otherwise, an exception is thrown.

Compilation Errors:

The type of I<OPERAND> must be an L<integer type|SPVM::Document::Language::Types/"Integer Types"> within int. Otherwise, a compilation error occurs.

Examples:
  
  # Examples of new_string_len operator
  my $message = new_string_len 5;

=head2 make_read_only Operator

The C<make_read_only> operator makes a string read-only.

  make_read_only OPERAND

If the string I<OPERAND> is defined, this operator makes I<OPERAND> read-only.

A read-only string cannnot be cast to L<mutable|SPVM::Document::Language::Types/"mutable Type Qualifier"> string type. If so, an exception is thrown.

The return type is the void type.

Compilation Errors:

I<OPERAND> must be string type. Otherwise, a compilation error occurs.

Examples:

  # Examples of make_read_only operator
  
  # A string
  my $string = new_string_len 3;
  
  # Make the string read-only
  make_read_only $string;
  
  # The conversion to the mutable string type throw an exception.
  my $string_mutable = (mutable string)$string;

=head2 make_fixed_length Operator

The C<make_fixed_length> operator makes a string or an array fixed length.

  make_fixed_length OPERAND

If I<OPERAND> is defined, this operator makes I<OPERAND> fixed length.

A fixed length string or array cannnot change its length and capacity. If so, an exception is thrown.

The return type is the void type.

Compilation Errors:

I<OPERAND> must be string or an array type. Otherwise, a compilation error occurs.

Examples:

  # Examples of make_fixed_length operator
  
  # A string
  my $string = new_string_len 3;
  
  # Make the string read-only
  make_fixed_length $string;
  
=head2 enable_options Operator

The C<enable_options> operator enables C<options> flag of an object.

  enable_options OPERAND

The type of object I<OPERAND> must be an object type.

If I<OPERAND> is defined and its type is any object array type C<object[]>, this operator enables C<options> flag of I<OPERAND>.

The return type is the void type.

Compilation Errors:

The type of I<OPERAND> must be an object type. Otherwise, a compilation error occurs.

Examples:

  # Examples of enable_options operator
  my $options = [(object)max => 1, title => "Hello"];
  enable_options $options;

=head2 disable_options Operator

The C<disable_options> operator disables C<options> flag of an object.

  disable_options OPERAND

The type of object I<OPERAND> must be an object type.

If I<OPERAND> is defined, this operator disables C<options> flag of I<OPERAND>.

The return type is the void type.

Compilation Errors:

The type of I<OPERAND> must be an object type. Otherwise, a compilation error occurs.

Examples:

  # Examples of disable_options operator
  my $options = {max => 1, title => "Hello"};
  disable_options $options;

=head2 is_options Operator

The C<is_options> operator checks if C<options> flag of an object is enabled.

  is_options OPERAND

The type of object I<OPERAND> must be an object type.

If I<OPERAND> is defined and C<options> flag of I<OPERAND> is enabled, the C<is_options> operator returns 1; otherwise returns 0.

The return type is int type.

Compilation Errors:

The type of I<OPERAND> must be an object type. Otherwise, a compilation error occurs.

Examples:
  
  # Examples of is_options operator
  my $options = {max => 1, title => "Hello"};
  my $is_options = is_options $options;

=head2 is_read_only Operator

The C<is_read_only> operator checks if a string is read-only.

  is_read_only OPERAND

If the string I<OPERAND> is defined and read-only, the C<is_read_only> operator returns 1, otherwise returns 0.

The return type is int type.

Compilation Errors:

I<OPERAND> must be string type. Otherwise, a compilation error occurs.

Examples:
  
  # Examples of is_read_only operator
  my $message = "Hello";
  my $is_read_only = is_read_only $message;

=head2 is_fixed_length Operator

The C<is_fixed_length> operator checks if a string or array is read-only.

  is_fixed_length OPERAND

If I<OPERAND> is defined and fixed length, the C<is_fixed_length> operator returns 1, otherwise returns 0.

The return type is int type.

Compilation Errors:

I<OPERAND> must be string or an array type. Otherwise, a compilation error occurs.

Examples:
  
  # Examples of is_fixed_length operator
  my $message = (mutable string)copy "Hello";
  my $is_fixed_length = is_fixed_length $message;

=head2 print Operator

The C<print> operator prints a string to standard output.

  print OPERAND

This operator outputs the string I<OPERAND> to L<SPVM's standard output|SPVM::Document::Language::System/"Standard Streams">.

If I<OPERAND> is not defined, this operator outputs nothing.

The return type is the void type.

Compilation Errors:

I<OPERAND> must be string type. Otherwise, a compilation error occurs.

=head2 say Operator

The C<say> operator prints a string to standard output with a newline.

  say OPERAND

This operator outputs the string I<OPERAND> to L<SPVM's standard output|SPVM::Document::Language::System/"Standard Streams"> with a newline C<\n>.

If I<OPERAND> is not defined, this operator outputs a newline C<\n>.

The return type is the void type.

Compilation Errors:

I<OPERAND> must be string type. Otherwise, a compilation error occurs.

=head2 warn Operator

The C<warn> operator prints a string to standard error with a stack trace.

  warn
  warn OPERAND

If I<OPERAND> is omitted, I<OPERAND> is set to the string C<"Warning">.

This operator outputs I<OPERAND> to L<SPVM's standard error|SPVM::Document::Language::System/"Standard Streams">.

If I<OPERAND> is not defined, this operator outputs the string C<"undef">.

If the type of I<OPERAND> is string type and I<OPERAND> is defined, this operator outputs I<OPERAND>.

If the type of I<OPERAND> is an object type except for string type and I<OPERAND> is defined, this operator outputs the type name and the address of I<OPERAND>, such as C<"Point(0x55d8a44ed090)">.

If the type of I<OPERAND> is a reference type, this operator outputs the return value of L</"address Operator"> such as C<"0x55d8a44ed090">.

This operator outputs a newline, two tabs and a stack trace information following the output above.

A stack trace information consists of the current method name, file name, and line number.

  MyClass->test at path/MyClass.spvm line 33

The return type is the void type.

Compilation Errors:

The type of I<OPERAND> must be a numeric type, an object type, or a reference type. Otherwise, a compilation error occurs.

Examples:
  
  warn;
  warn "Something is wrong.";
  
  # Point(0x55d8a44ed090)
  my $point = Point->new;
  warn $point;

=head2 address Operator

The C<address> operator gets the address of an object or a reference as a hex string.

  address OPERAND

This operator gets the address of I<OPERAND> and converts it to a hex string(such as 0x7ffee23b8ac4), and returns it.

The return type is string type.

The type of I<OPERAND> must be an object type or a reference type.

Compilation Errors:

The type of I<OPERAND> must be an object type or a reference type. Otherwise compilation error occurs.

=head2 __FILE__ Operator

The C<__FILE__> operator gets the path of the file where the current class is defined.

  __FILE__

This operator creates a string with the path of the file where the current class is defined, and returns it.

The return type is string type.

The return value can be changed by L<file directive|SPVM::Document::Language::Tokenization/"File Directive">.

Examples:
  
  # Examples of __FILE__ operator
  class Foo::Bar {
    static method baz : void () {
      # path/SPVM/Foo/Bar.spvm
      my $file_name = __FILE__;
    }
  }

=head2 __LINE__ Operator

The C<__LINE__> operator gets the current line number.

  __LINE__

This operator returns the current line number.

The return type is int type.

Examples:

  # Examples of __LINE__ operator
  class Foo::Bar {
    static method baz : void () {
      my $line = __LINE__;
    }
  }

=head2 __PACKAGE__ Operator

The C<__PACKAGE__> operator gets the name of L<outmost class|SPVM::Document::Language::Class/"Outmost Class">.

  __PACKAGE__

This operator creates a string with the name of L<outmost class|SPVM::Document::Language::Class/"Outmost Class">, and returns it.

The return type is string type.

Examples:

  class Foo::Bar {
    static method baz : void () {
      # Foo::Bar
      my $outmost_class_name = __PACKAGE__;
      
      my $anon_method = method : void () {
        # Foo::Bar
        my $outmost_class_name = __PACKAGE__;
      };
    }
  }

=head2 new Operator

The C<new> operator creates a new object, a new array, and a new multi-dimensional array.

See also L<use statement|SPVM::Document::Language::Class/"use Statement"> about the way to load classes.

See also L<SPVM::Document::Language::GarbageCollection> about garbage collection of objects.

=head3 Creating an Object

The following syntax of new operator creates a new object.

  new CLASS_TYPE;

The class type I<CLASS_TYPE> must be a loaded L<class type|SPVM::Document::Language::Types/"Class Types">.

This operator creates a new object of I<CLASS_TYPE>, and returns it.

The fields of the new object are initialized by its L<type initial value|SPVM::Document::Language::Types/"Type Initial Value">.

The return type is I<CLASS_TYPE>.

Compilation Errors:

I<CLASS_TYPE> must be a loaded class type. Otherwise, a compilation error occurs.

Examples:

  # Examples of new operator - Creating a new object
  my $object = new Foo;

=head3 Creating an Array

The following syntax of new operator creates a new array.

  new BASIC_TYPE[LENGTH]

The basic type I<BASIC_TYPE> must be a loaded L<basic type|SPVM::Document::Language::Types/"Basic Types">.

This operator performs L<integer promotional conversion|/"Integer Promotional Conversion"> on the length I<LENGTH>.

And creates a new array of the length I<LENGTH> which element type is I<BASIC_TYPE>.

And all elements of the new array are initialized by its L<type initial value|SPVM::Document::Language::Types/"Type Initial Value">.

And returns the new array.

The return type is C<I<BASIC_TYPE>[]>.

Exceptions:

I<LENGTH> must be greater than or equal to 0. Otherwise, an exception is thrown.

Compilation Errors:

I<LENGTH> must be an L<integer type|SPVM::Document::Language::Types/"Integer Types"> within int. Otherwise, a compilation error occurs.

Examples:

  # Examples of new operator - Creating a new array
  my $values = new int[3];
  my $objects = new Foo[3];
  my $objects = new object[3];
  my $mulnum_values = new Complex_2d[3]

=head3 Creating a Multi-Dimensional Array

The following syntax of new operator creates a new multi-dimensional array.

  new BASIC_TYPE[]..[LENGTH]

(C<[]..> means one or more C<[]>.)

The basic type I<BASIC_TYPE> must be a loaded L<basic type|SPVM::Document::Language::Types/"Basic Types">.

This operator performs L<integer promotional conversion|/"Integer Promotional Conversion"> on the length I<LENGTH>.

And creates a new multi-dimensional array of the length I<LENGTH> which element type is C<I<BASIC_TYPE>[]..>.

And all elements of the new multi-dimensional array are initialized by its L<type initial value|SPVM::Document::Language::Types/"Type Initial Value">.

And returns the new multi-dimensional array.

The return type is C<I<BASIC_TYPE>[]..[]>.

Exceptions:

I<LENGTH> must be greater than or equal to 0. Otherwise, an exception is thrown.

Compilation Errors:

I<LENGTH> must be an L<integer type|SPVM::Document::Language::Types/"Integer Types"> within int. Otherwise, a compilation error occurs.

The type dimension must be less than or equal to 255. Otherwise, a compilation error occurs.

Examples:

  # Examples of new operator - Creating a new multi-dimensional array
  
  # 2 dimentional int array
  my $muldim_values = new int[][3];
  
  # 3 dimentional int array
  my $muldim_values = new int[][][3];

=head2 Array Initialization

The syntax of the array initialization creates a new array and sets the elements, and returns the new array.

  [ELEMENT1, ELEMENT2, .., ELEMENTn]

This is expanded to the following code.
  
  (
    # Create a new array
    my $array = new ELEMENT1_TYPE[n],
    
    # Set elements
    $array->[0] = ELEMENT1,
    $array->[1] = ELEMENT2,
    ...,
    $array->[n - 1] = ELEMENTn,
    $array,
  )

I<ELEMENT1_TYPE> is the type of I<ELEMENT1>. 

If elements does not exist, I<ELEMENT1_TYPE> is the any object type C<object>, I<n> is 0, and setting elements is not performed.

The return type is C<I<ELEMENT1_TYPE>[]>.

Compilation Errors:

If the type of I<ELEMENT1> is the undef type, a compilation error occurs.

Examples:
  
  # Examples of the array initialization
  
  # int array
  my $nums = [1, 2, 3];
  
  # double array
  my $nums = [1.5, 2.6, 3.7];
  
  # string array
  my $strings = ["foo", "bar", "baz"];

The int array example is expanded to the following code.

  # int array
  my $nums = new int[3];
  $nums->[0] = 1;
  $nums->[1] = 2;
  $nums->[2] = 3;

=head3 Key-Value Array Initialization

The syntax of the key-value array initialization creates a new array and sets the elements with key-value pairs, and returns the new array.

  {ELEMENT1, ELEMENT2, ELEMENT3, ELEMENT4}

This syntax is the same as L</"Array Initialization">, but the return type is always L<any object array type|SPVM::Document::Language::Types/"Any Object Array Type"> C<object[]>.

And the length of the elements must be an even number.

The array created in this way is called "Options" and C<options> flag of this object is enabled.

Compilation Errors:

The length of the elements must be an even number, a compilation error occurs.

Examples:

  # Examples of the key-value array initialization
  
  # Empty
  my $key_values = {};
  
  # Key values
  my $key_values = {foo => 1, bar => "Hello"};

=head4 Options

The object of C<object[]> type created by L</"Key-Value Array Initialization"> is called "Options".
  
  # Called "Options"
  {foo => 1, bar => 2}

=head2 Anon Method Operator

An anon method operator creates an object of an L<anon method class|SPVM::Document::Language::Class/"Anon Method Class">.

  ANON_METHOD_CLASS_DEFINTION

This operator defines an anon method class using L<anon method class definition|SPVM::Document::Language::Class/"Anon Method Class Definition"> I<ANON_METHOD_CLASS_DEFINTION>, creates a new object from the class, and retunrs it.

If the anon method class field definition in I<ANON_METHOD_CLASS_DEFINTION> has field default values, the fields of the anon method object are set to these values.

Examples:
  
  # Examples of the anon method operator
  my $comparator = (Comparator)method : int ($x1 : object, $x2 : object) {
    my $point1 = (Point)$x1;
    my $point2 = (Point)$x2;
    
    return $point1->x <=> $point2->x;
  };
  
  # With an anon method class field definition
  my $num = 1;
  my $comparator = [$num : int] (Comparator)method : int ($x1 : object, $x2 : object) {
    my $point1 = (Point)$x1;
    my $point2 = (Point)$x2;
    
    say $num;
    
    return $point1->x <=> $point2->x;
  };
  
=head2 undef Operator

The C<undef> operator returns an L<undefined value|SPVM::Document::Language::Types/"Undefined Value">.
  
  undef

The return type is L<undef type|SPVM::Document::Language::Types/"undef Type">.

Examples:
  
  # Examples of undef operator
  my $string = (string)undef;
  
  if (undef) {
    
  }
  
  my $message = "Hello";
  if ($message == undef) {
    
  }

=head2 copy Operator

The C<copy> operator copies a numeric array, a multi-numeric array or a string.
  
  copy OPERAND

If the operand I<OPERAND> is not an undefined value, this operator creates a new object of the same type as the operand I<OPERAND>, and copies the elements of the array or the characters of the string into the new object, and returns it.

If I<OPERAND> is not defined, this operator returns an undefined value.

The read-only flag of the string is not copied.

The return type is the type of I<OPERAND>.

Compilation Errors:

The operand type must be string type, a numeric array type, or a multi-numeric array type. Otherwise, a compilation error occurs.

Examples:
  
  # Exampels of copy operator
  my $message = copy "abc";

=head2 dump Operator

The C<dump> operator gets the string representation dumping the data contained in the object.

  dump OPERAND

This operator creates a new string with the string representation dumping the data contained in the object I<OPERAND> and returns it.

The following is an example of the return value the C<dump> operator.
  
  # An return vlaue of dump operator
  TestCase::Operator::DumpTest1 (0x55f21f7e6050) {
    byte_value => 1,
    short_value => 2,
    int_value => 3,
    long_value => 4,
    float_value => 1.1,
    double_value => 1.2,
    string_value => "a",
    int_array => [
      1,
      2,
      3
    ] : int[](0x55f21fb9b8d0),
    object_value => TestCase::Operator::DumpTest1 (0x55f21f764640) {
      byte_value => 0,
      short_value => 0,
      int_value => 0,
      long_value => 0,
      float_value => 0,
      double_value => 0,
      string_value => undef,
      int_array => undef,
      object_value => undef
    }
  }

The return type is string type.

The string representation might be changed to make it more readable. So don't use the C<dump> operator for the purpose of the data serialization.

Compilation Errors:

I<OPERAND> must be an object type, ohterwise a compilation error occurs.

=head2 Reference Operator

The reference operator C<\> creates the reference to the value owned by a variable.

  \VARIALBE

This operator creates the reference to the value owned by the variable I<VARIALBE>, and returns it.

I<VARIALBE> is must be a local variable of a numeric type or a multi-numeric type.

The return type is L<Reference Types|SPVM::Document::Language::Types/"Reference Types"> of I<VARIALBE>.

Compilation Errors:

I<VARIALBE> must be a local variable of a numeric type or a multi-numeric type. Otherwise, a compilation error occurs.

Examples:
  
  # Examples of reference operator
  
  # Create a reference of a numeric type
  my $num : int;
  my $num_ref = \$num;
  
  # Create a reference of a multi-numeric type
  my $z : Complex_2d;
  my $z_ref = \$z;

=head2 Dereference Operator

The dereference operator C<$> gets a referenced value.

  $VARIABLE

This operator returns the value referenced by the variable I<VARIABLE> of a reference type.

The return type is the type of the value referenced by I<VARIABLE>.

Compilation Errors:

The type of I<VARIABLE> must be a reference type. Otherwise, a compilation error occurs.

Exceptions:

If I<VARIABLE> is undef, an exception is thrown.

Examples:
  
  # Examples of dereference operator
  my $num : int;
  my $num_ref = \$num;
  my $num_deref = $$num_ref;
  
  my $z : Complex_2d;
  my $z_ref = \$z;
  my $z_deref = $$z_ref;

=head2 Assignment Operator

The assignment operator C<=> performs an assignment.
  
  LEFT_OPERAND = RIGHTH_OPERAND

A data conversion described in L<Assignment Requirement|SPVM::Document::Language::Types/"Assignment Requirement"> is performed on I<RIGHTH_OPERAND> if necessary.

And assignment operator performs different operations depending on the left operand I<LEFT_OPERAND>.

If I<LEFT_OPERAND> is a local variable, this operator performs the operation that L<sets a local variable|/"Local Variable Set Operation">.

If I<LEFT_OPERAND> is a class variable, this operator performs the operation that L<sets a class variable|/"Class Variable Set Operation">.

If I<LEFT_OPERAND> is an element access, this operator performs the operation that L<sets an array element|/"Array Element Set Operation">.

If I<LEFT_OPERAND> is a field access, this operator performs the operation that L<sets a field|/"Field Set Operation">.

If I<LEFT_OPERAND> is a dereference, this operator performs the operation that L<sets a referenced value|/"Referenced Value Set Operation">.

If I<LEFT_OPERAND> is the exception variable, this operator performs the operation that L<sets the exception variable|/"Exception Variable Set Operation">.

See also L<SPVM::Document::Language::GarbageCollection/"Assignment"> about how assignment operator changes the reference counts of I<LEFT_OPERAND> and I<RIGHTH_OPERAND>.

Examples:
  
  # Examples of assignment operator
  
  # A local variable
  $num = 1;
  
  # A class variable
  $NUM = 1;
  
  # A field access
  $point->{x} = 1;
  
  # An element access
  $nums->[0] = 1;
  
  # A dereference
  $$num_ref = 1;
  
  # The exception variable
  $@ = 2;

=head2 Special Assignment Operators

A special assignment operator is the combination of an operator such as C<+>, C<-> and L<assignment operator|/"Assignment Operator"> C<=>.

  LEFT_OPERAND OPERATOR= RIGHTH_OPERAND

A special assignment operator is expanded to the following code.

  LEFT_OPERAND = (TYPE_OF_LEFT_OPERAND)(LEFT_OPERAND OPERATOR RIGHTH_OPERAND)

See the following code using a special assignment operator C<+=>. C<$x> is int type.
  
  $x += 2;

This is expanded to the following code.

  $x = (int)($x + 2)

List of Special Assignment Operators:

=begin html

<table>
  <tr>
    <td>The addition assignment operator</td>
    <td>+=</td>
  </tr>
  <tr>
    <td>The subtraction assignment operator</td>
    <td>-=</td>
  </tr>
  <tr>
    <td>The multiplication assignment operator</td>
    <td>*=</td>
  </tr>
  <tr>
    <td>The division assignment operator</td>
    <td>/=</td>
  </tr>
  <tr>
    <td>The modulo assignment operator</td>
    <td>%=</td>
  </tr>
  <tr>
    <td>The bitwise AND assignment operator</td>
    <td>&=</td>
  </tr>
  <tr>
    <td>The bitwise OR assignment operator</td>
    <td>|=</td>
  </tr>
  <tr>
    <td>The left shift assignment operator</td>
    <td><<=</td>
  </tr>
  <tr>
    <td>The arithmetic right shift assignment operator</td>
    <td>>>=</td>
  </tr>
  <tr>
    <td>The logical right shift assignment operator</td>
    <td>>>>=</td>
  </tr>
  <tr>
    <td>The concatenation assignment operator</td>
    <td>.=</td>
  </tr>
  <tr>
    <td>The defined-or assignment operator</td>
    <td>//=</td>
  </tr>
</table>

=end html

Examples:

  # Special assignment operators
  $x += 1;
  $x -= 1;
  $x *= 1;
  $x /= 1;
  $x &= 1;
  $x |= 1;
  $x ^= 1;
  $x %= 1;
  $x <<= 1;
  $x >>= 1;
  $x >>>= 1;
  $x .= "abc";

=head2 Get and Set Operations

=head3 Local Variable Get Operation

The operation of getting local variable gets the value of a L<local variable|SPVM::Document::Language::Class/"Local Variable">.

  $var

I<$var> is a L<local variable access|/"Local Variable Access">.

This operation returns the value of I<$var>.

The return type is the type of I<$var>.

Compilation Errors:

Compiliation errors caused by the syntax of L<local variable access|/"Local Variable Access"> could occur.

Examples:

  $var;

=head3 Local Variable Set Operation

The operation of setting a local variable sets a L<local variable|SPVM::Document::Language::Class/"Local Variable">.

  $var = OPERAND

I<$var> is a L<local variable access|/"Local Variable Access">.

This operation sets I<$var> to I<OPERAND> using L<assignment operator|/"Assignment Operator">, and returns the value after setting.

The return value is the type of I<$var>.

Compilation Errors:

Compiliation errors caused by the syntax of L<local variable access|/"Local Variable Access"> could occur.

The assignment must satisfy L<assignment requirement|SPVM::Document::Language::Types/"Assignment Requirement">. Otherwise, a compilation error occurs.

Examples:

  $var = 3;

=head3 Local Variable Access

The local variable access has the following syntax.

  VAR_NAME

See L<Variable Name Resolution|SPVM::Document::Language::Class/"Variable Name Resolution"> about I<VAR_NAME> and the resolution of a local variable name.

Examples:

  $var

=head3 Class Variable Get Operation

The operation of getting a class variable gets the value of a L<class variable|SPVM::Document::Language::Class/"Class Variable">.

  $VAR

I<$VAR> is a L<class variable access|/"Class Variable Access">.

This operation returns the value of I<$VAR>.

The return type is the type of I<$VAR>.

Compilation Errors:

Compiliation errors caused by the syntax of L<class variable access|/"Class Variable Access"> could occur.

Examples:
  
  # Examples of getting a class variable
  class Foo {
    our $VAR : int;
    
    static method bar : int () {
      
      my $var1 = $Foo::VAR;
      
      # $Foo::VAR
      my $var2 = $VAR;
      
      my $anon_method = method : void () {
        # $Foo::BAR
        $VAR;
      }
    }
  }

=head3 Class Variable Set Operation

The operation of setting a class variable operator sets a L<class variable|SPVM::Document::Language::Class/"Class Variable">.

  $VAR = OPERAND

I<$VAR> is a L<class variable access|/"Class Variable Access">.

This operation sets I<$VAR> to I<OPERAND> using L<assignment operator|/"Assignment Operator">, and returns the value after setting.

The return type is the type of I<$VAR>.

Compilation Errors:

Compiliation errors caused by the syntax of L<class variable access|/"Class Variable Access"> could occur.

The assignment must satisfy L<assignment requirement|SPVM::Document::Language::Types/"Assignment Requirement">. Otherwise, a compilation error occurs.

Examples:

  # Examples of setting a class variable
  class Foo {
    our $VAR : int;
    
    static method bar : int () {
      $Foo::VAR = 1;
      
      # $Foo::VAR = 3
      $VAR = 3;
    }
    my $anon_method = method : void () {
      # $Foo::VAR = 5
      $VAR = 5;
    }
  }

=head3 Class Variable Access

The class variable access has the following syntax.

  VAR_NAME
  CLASS_TYPE::VAR_NAME

See L<Variable Name Resolution|SPVM::Document::Language::Class/"Variable Name Resolution"> about I<VAR_NAME>, I<CLASS_TYPE>, and the resolution of a class variable name.

Examples:

  $VAR
  $MyClass::VAR
  
=head3 Array Element Get Operation

The operation of getting an array element gets an element of an L<array|SPVM::Document::Language::Types/"Array">.

  ARRAY->[INDEX]

I<ARRAY-E<gt>[INDEX]> is an L<element access|/"Array Element Access">.

This operator performs L<integer promotional conversion|/"Integer Promotional Conversion"> on I<INDEX>.

And returns the element of I<ARRAY> at I<INDEX>.

The return type is the element type of I<ARRAY>.

Exceptions:

I<ARRAY> must be defined. Otherwise, an exception is thrown.

I<INDEX> must be greater than or equal to 0. Otherwise, an exception is thrown.

Compilation Errors:

Compiliation errors caused by the syntax of L<element access|/"Array Element Access"> could occur.

Examples:

  my $nums = new int[3];
  my $num = $nums->[1];
  
  my $points = new Point[3];
  my $point = $points->[1];

=head3 Array Element Set Operation

The operation of setting array element sets an element of an array.

  ARRAY->[INDEX] = OPERAND

I<ARRAY-E<gt>[INDEX]> is an L<element access|/"Array Element Access">.

This operator performs L<integer promotional conversion|/"Integer Promotional Conversion"> on I<INDEX>.

And sets the element of I<ARRAY> at I<INDEX> to I<OPERAND> using L<assignment operator|/"Assignment Operator">, and returns the element after setting.

The return type is the element type.

Exceptions:

I<ARRAY> must be defined. Otherwise, an exception is thrown.

I<INDEX> must be greater than or equal to 0. Otherwise, an exception is thrown.

Compilation Errors:

Compiliation errors caused by the syntax of L<element access|/"Array Element Access"> could occur.

The assignment must satisfy L<assignment requirement|SPVM::Document::Language::Types/"Assignment Requirement">. Otherwise, a compilation error occurs.

Examples:

  my $nums = new int[3];
  $nums->[1] = 3;
  
  my $points = new Point[3];
  $points->[1] = Point->new(1, 2);
  
=head3 List Element Get Operation

The list element get operation gets an element of a list object with an index.

  INVOCANT->[INDEX_OPERAND]

I<INVOCANT-E<gt>[INDEX_OPERAND]> is a L<array element access|/"Array Element Access">.

This operation is replaced with C<get> method call.

  INVOCANT->get(INDEX_OPERAND)

Compilation Errors:

Compiliation errors caused by the syntax of L<array element access|/"Array Element Access"> could occur.

Examples:

  my $list = List->new([1, 2]);
  my $x = $list->[1];

=head3 List Element Set Operation

The list element set operation gets an element of a list object with an index.

  INVOCANT->[INDEX_OPERAND] = OPERAND

I<INVOCANT-E<gt>[INDEX_OPERAND]> is a L<array element access|/"Array Element Access">.

This operation is replaced with C<set> method call.

  INVOCANT->set(INDEX_OPERAND, OPERAND)

Compilation Errors:

Compiliation errors caused by the syntax of L<array element access|/"Array Element Access"> could occur.

The assignment must satisfy L<assignment requirement|SPVM::Document::Language::Types/"Assignment Requirement">. Otherwise, a compilation error occurs.

Examples:

  my $list = List->new([1, 2]);
  $list->[1] = 3;

=head3 Array Element Access

The element access has the following syntax.

  ARRAY->[INDEX]

The type of the array I<ARRAY> is an array type.

The type of the index I<INDEX> is an L<integer type|SPVM::Document::Language::Types/"Integer Types"> within int.

If I<INDEX> is a minus value, it is set to I<INDEX> plus the length of the array.

Exceptions:

If I<INDEX> is less than 0 or more than or equal to the length of the array, an exception is thrown.

Compilation Errors:

I<ARRAY> must be an array type, string type, a class type, or an interface type. Otherwise, a compilation error occurs.

I<INDEX> must be an L<integer type|SPVM::Document::Language::Types/"Integer Types"> within int. Otherwise, a compilation error occurs.

=head3 Character Get Operation

The operation of getting a character gets a character of a string.

  STRING->[INDEX]

I<STRING-E<gt>[INDEX]> is an L<character access|/"Character Access">.

The type of I<STRING> is string type.

This operator performs L<integer promotional conversion|/"Integer Promotional Conversion"> on I<INDEX>.

And returns the character of I<STRING> at I<INDEX>.

The return type is byte type.

Exceptions:

I<STRING> must be defined. Otherwise, an exception is thrown.

I<INDEX> must be greater than or equal to 0. Otherwise, an exception is thrown.

Compilation Errors:

Compiliation errors caused by the syntax of L<character access|/"Character Access"> could occur.

Examples:

  my $string = "abc";
  my $char = $string->[0];

=head3 Character Set Operation

The operation of setting a character sets the character of a string.

  STRING->[INDEX] = OPERAND

I<STRING-E<gt>[INDEX]> is an L<character access|/"Character Access">.

This operator performs L<integer promotional conversion|/"Integer Promotional Conversion"> on I<INDEX>.

And sets the character of I<STRING> at I<INDEX> to I<OPERAND> using L<assignment operator|/"Assignment Operator">, and returns the character after setting.

The return type is byte type.

Exceptions:

I<STRING> must be defined. Otherwise, an exception is thrown.

I<INDEX> must be greater than or equal to 0. Otherwise, an exception is thrown.

If I<STRING> is not a mutable string, an exception is thrown.

Compilation Errors:

Compiliation errors caused by the syntax of L<character access|/"Character Access"> could occur.

The assignment must satisfy L<assignment requirement|SPVM::Document::Language::Types/"Assignment Requirement">. Otherwise, a compilation error occurs.

Examples:

  my $string = new_string_len 3;
  $string->[0] = 'a';

=head3 Character Access

The character access has the following syntax.

  STRING->[INDEX]

The type of the string I<STRING> is string type.

The type of the index I<INDEX> is an L<integer type|SPVM::Document::Language::Types/"Integer Types"> within int.

Compilation Errors:

I<STRING> must be string type. Otherwise, a compilation error occurs.

I<INDEX> must be an L<integer type|SPVM::Document::Language::Types/"Integer Types"> within int. Otherwise, a compilation error occurs.

=head3 Field Get Operation

The operation of getting field gets the value of a field of a class type.

  INVOCANT->{FIELD_NAME}

I<INVOCANT-E<gt>{FIELD_NAME}> is a L<field access|/"Field Access">.

This operation gets the value of the field specified by I<FIELD_NAME> of the type of I<INVOCANT>.

The retrun type is the type of the field.

Compilation Errors:

Compiliation errors caused by the syntax of L<field access|/"Field Access"> could occur.

Examples:

  my $point = Point->new;
  my $x = $point->{x};

=head3 Field Set Operation

The operation of setting field sets the field of a class type.

  INVOCANT->{FIELD_NAME} = OPERAND

I<INVOCANT-E<gt>{FIELD_NAME}> is a L<field access|/"Field Access">.

The type of I<INVOCANT> is a class type.

This operation sets the field specified by I<FIELD_NAME> of the type of I<INVOCANT> to I<OPERAND> using L<assignment operator|/"Assignment Operator">, and returns the value of the field after setting.

The return type is the field type.

Compilation Errors:

Compiliation errors caused by the syntax of L<field access|/"Field Access"> could occur.

The assignment must satisfy L<assignment requirement|SPVM::Document::Language::Types/"Assignment Requirement">. Otherwise, a compilation error occurs.

Examples:

  my $point = Point->new;
  $point->{x} = 1;

=head3 Multi-Numeric Field Get Operation

The operation of getting a multi-numeric field gets the value of a field of a L<multi-numeric type|SPVM::Document::Language::Types/"Multi-Numeric Types">.

  INVOCANT->{FIELD_NAME}

I<INVOCANT-E<gt>{FIELD_NAME}> is a L<field access|/"Field Access">.

The type of I<INVOCANT> is a multi-numeric type.

This operation gets the value of the field specified by I<FIELD_NAME> of the type of I<INVOCANT>.

The retrun type is the type of the field.

Compilation Errors:

Compiliation errors caused by the syntax of L<field access|/"Field Access"> could occur.

Examples:

  my $z : Complex_2d;
  my $re = $z->{re};

=head3 Multi-Numeric Field Set Operation

The operation of setting multi-numeric field sets the field of L<multi-numeric type|SPVM::Document::Language::Types/"Multi-Numeric Types">.

  INVOCANT->{FIELD_NAME} = OPERAND

I<INVOCANT-E<gt>{FIELD_NAME}> is a L<field access|/"Field Access">.

The type of I<INVOCANT> is a multi-numeric type.

This operation sets the field specified by I<FIELD_NAME> of the type of I<INVOCANT> to I<OPERAND> using L<assignment operator|/"Assignment Operator">, and returns the value of the field after setting.

The return type is the field type.

Compilation Errors:

Compiliation errors caused by the syntax of L<field access|/"Field Access"> could occur.

The assignment must satisfy L<assignment requirement|SPVM::Document::Language::Types/"Assignment Requirement">. Otherwise, a compilation error occurs.

Examples:

  my $z : Complex_2d;
  $z->{re} = 2.5;
  
=head3 Referenced Multi-Numeric Field Get Operation

The operation of getting a multi-numeric field gets the value of a field of a L<multi-numeric type|SPVM::Document::Language::Types/"Multi-Numeric Types"> referenced by a multi-numeric Reference Types.

This operation is expaned to the following code.

  ($INVOCANT)->{FIELD_NAME}

The type of I<INVOCANT> is a multi-numeric refenrece type.

Compilation Errors:

Compiliation errors caused by the syntax of L<field access|/"Field Access"> could occur.

Compiliation errors caused by L<dereference operator|/"Dereference Operator"> could occur.

Exceptions:

If I<INVOCANT> is undef, an exception is thrown.

Examples:

  my $z : Complex_2d;
  my $z_ref = \$z;
  my $re = $z_ref->{re};

=head3 Referenced Multi-Numeric Field Set Operation

The operation of setting a multi-numeric field sets the value of a field of a L<multi-numeric type|SPVM::Document::Language::Types/"Multi-Numeric Types"> referenced by a multi-numeric Reference Types.

This operation is expaned to the following code.

  ($INVOCANT)->{FIELD_NAME} = OPERAND

The type of I<INVOCANT> is a multi-numeric refenrece type.

Compilation Errors:

Compiliation errors caused by the syntax of L<field access|/"Field Access"> could occur.

Compiliation errors caused by L<dereference operator|/"Dereference Operator"> could occur.

The assignment must satisfy L<assignment requirement|SPVM::Document::Language::Types/"Assignment Requirement">. Otherwise, a compilation error occurs.

Exceptions:

If I<INVOCANT> is undef, an exception is thrown.

Examples:

  my $z : Complex_2d;
  my $z_ref = \$z;
  $z_ref->{re} = 2.5;

=head3 Hash Value Get Operation

The operation of getting field gets the value of a field of a class type.

  INVOCANT->{KEY_OPERAND}

I<INVOCANT-E<gt>{KEY_OPERAND}> is a L<hash value access|/"Hash Value Access">.

This operation is replaced with C<get> method call.

  INVOCANT->get(KEY_OPERAND)

Compilation Errors:

Compiliation errors caused by the syntax of L<hash value access|/"Hash Value Access"> could occur.

Examples:

  my $hash = Hash->new({x => 1});
  my $x = $hash->{"x"};

=head3 Hash Value Set Operation

The operation of setting field sets the field of a class type.

  INVOCANT->{KEY_OPERAND} = OPERAND

I<INVOCANT-E<gt>{KEY_OPERAND}> is a L<hash value access|/"Hash Value Access">.

This operation is replaced with C<set> method call.

  INVOCANT->set(KEY_OPERAND, OPERAND)

Compilation Errors:

Compiliation errors caused by the syntax of L<hash value access|/"Hash Value Access"> could occur.

The assignment must satisfy L<assignment requirement|SPVM::Document::Language::Types/"Assignment Requirement">. Otherwise, a compilation error occurs.

Examples:

  my $hash = Hash->new({x => 1});
  $hash->{"x"} = 2;

=head3 Field Access

The field access has the following syntax.

  INVOCANT->{FIELD_NAME}

See L<Field Access Resolution|SPVM::Document::Language::Class/"Field Access Resolution"> about I<INVOCANT>, I<FIELD_NAME>, and the resolution of a field access.

Examples:

  $point->{x}

=head3 Hash Value Access

The hash value access has the following syntax.

  INVOCANT->{KEY_OPERAND}

The type of I<INVOCANT> is a class type or an interface type.

The type of I<KEY_OPERAND> is string type.

Examples:
  
  $hash->{"x"};

Compilation Errors:

The type of INVOCANT must be a class type or an interface type. Otherwise a compilation error occurs.

The type of KEY_OPERAND must be string type. Otherwise a compilation error occurs.

=head3 Referenced Value Get Operation

The operation of getting the referenced value gets a referenced value.

See L<dereference operator|/"Dereference Operator">.

=head3 Referenced Value Set Operation

The operation of setting the referenced value sets a referenced value.

  $VARIABLE = OPERAND

Thie operation sets the value referenced by the reference I<VARIABLE> to I<OPERAND> using L<assignment operator|/"Assignment Operator">, and returns the value after setting.

The return type is the type of the referenced value.

Compilation Errors:

The type of I<VARIABLE> must be a reference type. Otherwise, a compilation error occurs.

The assignment must satisfy L<assignment requirement|SPVM::Document::Language::Types/"Assignment Requirement">. Otherwise, a compilation error occurs.

Examples:

  my $num : int;
  my $num_ref : int* = \$num;
  $$num_ref = 1;
  
  my $z : Complex_2d;
  my $z_ref : Complex_2d* = \$z;
  
  my $z2 : Complex_2d;
  
  $$z_ref = $z2;

=head3 Exception Variable Get Operation

The operation of getting the exception variable gets the string stored in L<exception variable|SPVM::Document::Language::ExceptionHandling/"Exception Variable">.

  $@

This operator returns the string stored in the exception variable.

The return type is string type.

Examples:
  
  # Examples of getting the exception variable
  my $message = $@;

=head3 Exception Variable Set Operation

The operation of setting the exception variable sets L<exception variable|SPVM::Document::Language::ExceptionHandling/"Exception Variable">.

  $@ = OPERAND

This operator sets the exception variable to I<OPERAND> using L<assignment operator|/"Assignment Operator">.

The return type is string type.

Compilation Errors:

The assignment must satisfy L<assignment requirement|SPVM::Document::Language::Types/"Assignment Requirement">. Otherwise, a compilation error occurs.

Examples:

  # Examples of setting the exception variable
  $@ = "Error";

=head2 Data Conversions

This section describes data conversions.

=head3 Numeric Widening Conversion

The numeric widening conversion is the data conversion from a L<numeric type|SPVM::Document::Language::Types/"Numeric Types"> to a larger L<numeric type|SPVM::Document::Language::Types/"Numeric Types">.

See L<numeric types order|SPVM::Document::Language::Types/"Numeric Types Order"> about the order of numeric types.

This conversion performs the same operation as the C language type cast.
  
  (TYPE)OPERAND

B<byte to short:>

  (int16_t)OPERAND_int8_t;

B<byte to int:>

  (int32_t)OPERAND_int8_t;

B<byte to long:>

  (int64_t)OPERAND_int8_t;

B<byte to float:>

  (float)OPERAND_int8_t;

B<byte to double:>

  (double)OPERAND_int8_t;

B<short to int:>

  (int32_t)OPERAND_int16_t;

B<short to long:>

  (int64_t)OPERAND_int16_t;

B<short to float:>

  (float)OPERAND_int16_t;

B<short to double:>

  (double)OPERAND_int16_t;

B<int to long:>

  (int64_t)OPERAND_int32_t;

B<int to float:>

  (float)OPERAND_int32_t;

B<int to double:>

  (double)OPERAND_int32_t;

B<long to float:>

  (float)OPERAND_int64_t;

B<long to double:>

  (double)OPERAND_int64_t;

B<float to double:>

  (double)OPERAND_float;

=head3 Integer Promotional Conversion

The integer promotional conversion is the data conversion from an L<integer type|SPVM::Document::Language::Types/"Integer Types"> within int to int type using L<numeric widening conversion|/"Numeric Widening Conversion">.

=head3 Numeric Narrowing Conversion

The numeric narrowing conversion is the data conversion from a L<numeric type|SPVM::Document::Language::Types/"Numeric Types"> to a smaller L<numeric type|SPVM::Document::Language::Types/"Numeric Types">.

See L<numeric types order|SPVM::Document::Language::Types/"Numeric Types Order"> about the order of numeric types.

This conversion performs the same operation as the C language type cast.

  (TYPE)OPERAND

B<double to float:>

  (float)OPERAND_double;

B<double to long:>

  (int64_t)OPERAND_double;

B<double to int:>

  (int32_t)OPERAND_double;

B<double to short:>

  (int16_t)OPERAND_double;

B<double to byte:>

  (int8_t)OPERAND_double;

B<float to long:>

  (int64_t)OPERAND_float;

B<float to int:>

  (int32_t)OPERAND_float;

B<float to short:>

  (int16_t)OPERAND_float;

B<float to byte:>

  (int8_t)OPERAND_float;

B<long to int:>

  (int32_)OPERAND_int64_t;

B<long to short:>

  (int16_t)OPERAND_int64_t;

B<long to byte:>

  (int8_t)OPERAND_int64_t;

B<int to short:>

  (int16_t)OPERAND_int32_t;

B<int to byte:>

  (int16_t)OPERAND_int32_t;

B<short to byte:>

  (int8_t)OPERAND_int16_t;

=head3 Binary Numeric Conversion

The binary numeric conversion is the data conversion to upgrade L<numeric type|SPVM::Document::Language::Types/"Numeric Types"> of the left operand and the right operand of a binary operator.

This conversion performs the following operations.

If the left operand type is smaller than the right operand, L<numeric widening conversion|/"Numeric Widening Conversion"> from the left operand type to the right operand type is performed on the left operand.

If the right operand type is smaller than the left operand, L<numeric widening conversion|/"Numeric Widening Conversion"> from the right operand type to the left operand type is performed on the right operand.

If the converted type of the left operand is the smaller than int type, L<numeric widening conversion|/"Numeric Widening Conversion"> from the left operand type to int type is performed on the left operand.

If the converted type of the right operand is the smaller than int type, L<numeric widening conversion|/"Numeric Widening Conversion"> from the right operand type to int type is performed on the right operand.

=head3 Numeric-to-String Conversion

The numeric-to-string conversion is the data conversion from a L<numeric type|SPVM::Document::Language::Types/"Numeric Types"> to L<string type|SPVM::Document::Language::Types/"string Type">.

This conversion performs the same operation as the C language C<sprintf>.

B<byte to string:>

  sprintf(RETURN_VALUE, "%" PRId8, OPERAND_byte);

B<short to string:>

  sprintf(RETURN_VALUE, "%" PRId16, OPERAND_short);

B<int to string:>

  sprintf(RETURN_VALUE, "%" PRId32, OPERAND_int);

B<long to string:>

  sprintf(RETURN_VALUE, "%" PRId64, OPERAND_long);

B<float to string:>

  sprintf(RETURN_VALUE, "%g", OPERAND_float);

B<double to string:>

  sprintf(RETURN_VALUE, "%g", OPERAND_double);

Examples:

  # Examples of the numeric-to-string conversion
  my $byte = (byte)1;
  my $string_byte = (string)$byte;
  
  my $short = (short)2;
  my $string_short = (string)$short;
  
  my $int = 3;
  my $string_int = (string)$int;
  
  my $long = 4L;
  my $string_long = (string)$long;
  
  my $float = 2.5f;
  my $string_float = (string)$float;
  
  my $double = 3.3;
  my $string_double = (string)$double;

=head3 String-to-Numeric Conversion

The string-to-numeric conversion is the data conversion from L<string type|SPVM::Document::Language::Types/"string Type"> to a L<numeric type|SPVM::Document::Language::Types/"Numeric Types">.

B<string to byte:>

If the string is not defined, it returns 0.

If it is defined, it is coverted to a number by the C<strtoll> function in the C language.

The number is greater than C<INT8_MAX>, the number is set to C<INT8_MAX>.

The number is less than C<INT8_MIN>, the number is set to C<INT8_MIN>.

And returns the number.

B<string to short:>

If the string is not defined, it returns 0.

If it is defined, it is coverted to a number by the C<strtoll> function in the C language.

The number is greater than C<INT16_MAX>, the number is set to C<INT16_MAX>.

The number is less than C<INT16_MIN>, the number is set to C<INT16_MIN>.

And returns the number.

B<string to int:>

If the string is not defined, it returns 0.

If it is defined, it is coverted to a number by the C<strtoll> function in the C language.

The number is greater than C<INT32_MAX>, the number is set to C<INT32_MAX>.

The number is less than C<INT32_MIN>, the number is set to C<INT32_MIN>.

And returns the number.

B<string to long:>

If the string is not defined, it returns 0.

If it is defined, it is coverted to a number by the C<strtoll> function in the C language.

And returns the number.

B<string to float:>

If the string is not defined, it returns 0.

If it is defined, it is coverted to a number by the C<strtof> function in the C language.

And returns the number.

B<string to double:>

If the string is not defined, it returns 0.

If it is defined, it is coverted to a number by the C<strtod> function in the C language.

And returns the number.

Exampels:
  
  # Examples of string to numeric conversions
  
  # string to byte
  my $string : string = "Hello";
  my $number : byte = (byte)$string;
  
  # string to short
  my $string : string = "Hello";
  my $number : short = (short)$string;
  
  # string to int
  my $string : string = "Hello";
  my $number : int = (int)$string;
  
  # string to long
  my $string : string = "Hello";
  my $number : long = (long)$string;
  
  # string to float
  my $string : string = "Hello";
  my $float : float = (float)$string;
  
  # string to double
  my $string : string = "Hello";
  my $number : double = (double)$string;

=head3 String-to-byte[] Conversion

The string-to-byte[] conversion is the data conversion from string type to the byte[] type.

This conversion creates a new array which type is the C<byte[]> type, copies all characters in the string to the elements of the new array, and returns the new array.

If the string is not defined, it returns C<undef>.

Examples:

  # Examples of the string-to-byte[] conversion
  my $string : string = "Hello";
  my $bytes : byte[] = (byte[])$string;

=head3 byte[]-to-string Conversion

The byte[]-to-string conversion is the data conversion from the byte[] type to string type.

This conversion creates a new string, copies all elements in the array which type is the byte[] type to the characters of the new string, and returns the new string.

If the array is not defined, returns C<undef>.

  # Examples of the byte[]-to-string conversion
  my $bytes : byte[] = new byte[3];
  $bytes->[0] = 'a';
  $bytes->[1] = 'b';
  $bytes->[2] = 'c';
  my $string : string = (string)$bytes;

=head3 Boxing Conversion

The boxing conversion is the type coversion from a L<numeric type|SPVM::Document::Language::Types/"Numeric Types"> to its corresponding L<numeric object type|SPVM::Document::Language::Types/"Numeric Object Types">.

=begin html

<table>
  <tr>
    <th>
      To
    </th>
    <th>
      From
    </th>
  </tr>
  <tr>
    <td>
      <a href="https://metacpan.org/pod/SPVM::Byte">Byte</a>
    </td>
    <td>
      byte
    </td>
  </tr>
  <tr>
    <td>
      <a href="https://metacpan.org/pod/SPVM::Short">Short</a>
    </td>
    <td>
      short
    </td>
  </tr>
  <tr>
    <td>
      <a href="https://metacpan.org/pod/SPVM::Int">Int</a>
    </td>
    <td>
      int
    </td>
  </tr>
  <tr>
    <td>
      <a href="https://metacpan.org/pod/SPVM::Long">Long</a>
    </td>
    <td>
      long
    </td>
  </tr>
  <tr>
    <td>
      <a href="https://metacpan.org/pod/SPVM::Float">Float</a>
    </td>
    <td>
      float
    </td>
  </tr>
  <tr>
    <td>
      <a href="https://metacpan.org/pod/SPVM::Double">Double</a>
    </td>
    <td>
      double
    </td>
  </tr>
</table>

=end html

A boxing conversion creates a new numeric object corresponding to its numeric type, and copyes the value of the numeric type to the C<value> field of the new numeric object, and return the new numeric object.

=head3 Unboxing Conversion

The unboxing conversion is the type coversion from an object of a L<numeric object type|SPVM::Document::Language::Types/"Numeric Object Types"> to the value of its corresponding L<numeric type|SPVM::Document::Language::Types/"Numeric Types">.

=begin html

<table>
  <tr>
    <th>
      To
    </th>
    <th>
      From
    </th>
  </tr>
  <tr>
    <td>
      byte, short, int, long, float, double
    </td>
    <td>
      <a href="https://metacpan.org/pod/SPVM::Byte">Byte</a>
    </td>
  </tr>
  <tr>
    <td>
      byte, short, int, long, float, double
    </td>
    <td>
      <a href="https://metacpan.org/pod/SPVM::Short">Short</a>
    </td>
  </tr>
  <tr>
    <td>
      byte, short, int, long, float, double
    </td>
    <td>
      <a href="https://metacpan.org/pod/SPVM::Int">Int</a>
    </td>
  </tr>
  <tr>
    <td>
      byte, short, int, long, float, double
    </td>
    <td>
      <a href="https://metacpan.org/pod/SPVM::Long">Long</a>
    </td>
  </tr>
  <tr>
    <td>
      byte, short, int, long, float, double
    </td>
    <td>
      <a href="https://metacpan.org/pod/SPVM::Float">Float</a>
    </td>
  </tr>
  <tr>
    <td>
      byte, short, int, long, float, double
    </td>
    <td>
      <a href="https://metacpan.org/pod/SPVM::Double">Double</a>
    </td>
  </tr>
</table>

=end html

If the destination numeric type is bigger than the source numeric type, L<Numeric Widening Conversion|https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Widening-Conversion> is performed.

If the destination numeric type is smaller than the source numeric type, L<Numeric Narrowing Conversion|https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Narrowing-Conversion> is performed.

An unboxing conversion could be performed on the object of any object type C<object>.

Exceptions:

If the type of the object is not its corresponding numeric type, an exception is thrown.

=over 2

=item * The right operand of L<assignment operator|SPVM::Document::Language::Operators/"Assignment Operator">.

=item * Arguments given to a L<method call|SPVM::Document::Language::Operators/"Method Call">

=item * A return value given to L<return statement|SPVM::Document::Language::Statements/"return Statement">

=back

What type combinations cause implicit data conversions is explained in L<assignment requirement|SPVM::Document::Language::Types/"Assignment Requirement">.

Examples:
  
  # Assignment operators
  # int to double 
  my $number : double = 5;
  
  # double to Double
  my $number_object : Double = 5.1;
  
  # Double to double
  my $number : double = Double->new(5.1);
  
  # int to string
  my $string : string = 4;
  
  # Method call
  # int to double
  my $double_object = Double->new(3);
  
  # Return value
  method my_method : double () {
    
    # int to double
    return 3;
  }

=head2 Type Cast

A type cast converts a value from its type to another type.

  # A type cast
  (TYPE)OPERAND
  
  # A postfix type cast
  OPERAND->(TYPE)

The return type is I<TYPE>.

If a data conversion is needed in the type cast, a type cast performs a data conversion on I<OPERAND>, and returns the value after the data conversion.

Otherwise it returns I<OPERAND>.

If a data check is needed in the type cast, a type cast performs a data check on I<OPERAND>.

Data conversions and data checks in type casts are explained in L<Cast Requirement|SPVM::Document::Language::Types/"Cast Requirement">.

Exceptions:

If a data check returns 0, an exception is thrown.

Compilation Errors:

I<OPERAND> must satisfy L<cast requirement|SPVM::Document::Language::Types/"Cast Requirement">. Otherwise, a compilation error occurs.

Examples:
  
  # Examples of the type cast
  
  # long to int 
  my $num = (int)123L;
  
  # byte[] to string
  my $num = (string)new byte[3];
  
  # string to byte[]
  my $num = (byte[])"Hello";
  
  # Postfix type cast
  my $stringable = Point->new->(Stringable);

=head2 isa Operator

The C<isa> operator checks whether an operand can be assigned to a type.

  OPERAND isa TYPE
  $@      isa TYPE_WITHOUT_STRING

If the type I<TYPE> is a numeric type, a multi-numeric type, a reference type, this operator checks L<assignment requirement|SPVM::Document::Language::Types/"Assignment Requirement"> without data convertion.

If the assignment requirement is satisfied, this operator returns 1, otherwise returns 0.

If I<TYPE> is an object type, this operator checks L<assignment requirement|SPVM::Document::Language::Types/"Assignment Requirement"> at runtime.

If the assignment requirement at runtime is satisfied, this operator returns 1, otherwise returns 0.

The return type is int type.

If the left operand is $@ and the right type is not string type, a special interpretation is applied.

  $@ isa TYPE_WITHOUT_STRING

is replaced with

  $@ && eval_error_id isa_error TYPE_WITHOUT_STRING

See also L</"eval_error_id Operator"> and L</"isa_error Operator">.

Compilation Errors:

The right type I<TYPE> of isa operator must not be any object type. Otherwise, a compilation error occurs.

The left operand type I<OPERAND> of isa operator must be an object type. Otherwise, a compilation error occurs.

Examples:
  
  if ($value isa int) {
    
  }
  
  if ($value isa Point) {
    
  }
  
  if ($value isa Point3D) {
    
  }
  
  if ($value isa Stringable) {
    
  }
  
  if ($value isa int) {
    
  }
  
  if ($@ isa Error::System) {
    
  }

=head2 is_type Operator

The C<is_type> operator checks if the type of an operand is equal to a type.

  OPERAND is_type TYPE
  $@      is_type TYPE_WITHOUT_STRING

If the type I<TYPE> is a numeric type, a multi-numeric type, or a reference type, this operator checks if the compilation type of I<OPERAND> is equal to I<TYPE>.

If the check is true, this operator returns 1, otherwise returns 0.

If I<TYPE> is an object type, this operator checks if the runtime type of I<OPERAND> is equal to I<TYPE> at runtime.

If it is true, this operator returns 1, otherwise returns 0.

The return type is int type.

If the left operand is $@ and the right type is not string type, a special interpretation is applied.

  $@ is_type TYPE_WITHOUT_STRING

is replaced with

  $@ && eval_error_id is_error TYPE_WITHOUT_STRING

See also L</"eval_error_id Operator"> and L</"is_error Operator">.

Compilation Errors:

The right type I<TYPE> of is_type operator must not be any object type. Otherwise, a compilation error occurs.

The left operand type I<OPERAND> of is_type operator must be an object type. Otherwise, a compilation error occurs.

Examples:

  if ($object is_type int) {
    
  }
  
  if ($object is_type Point) {
    
  }
  
  if ($object is_type int[]) {
    
  }
  
  if ($object is_type Stringable[]) {
    
  }
  
  if ($@ is_type Error::System) {
    
  }

=head2 is_compile_type Operator

The C<is_compile_type> operator checks whether the compilation type of an operand is equal to a type.

  OPERAND is_compile_type QUALIFIED_TYPE

If the compilation type of I<OPERAND> is equal to the type with type modifier I<QUALIFIED_TYPE>, returns 1, otherwise returns 0.

The return type is int type.

Examples:

  {
    my $value : int;
    if ($value is_compile_type int) {
      # Pass
    }
  }
  
  {
    my $object : object = new TestCase::Minimal;
    if ($object is_compile_type object) {
      # Pass
    }
  }
  
  {
    my $value : Stringer = method : string () { return "aaa"; };
    if ($value is_compile_type Stringer) {
      # Pass
    }
  }
  
  {
    my $value : string;
    if ($value is_compile_type string) {
      # Pass
    }
  }
  
  {
    my $value : mutable string;
    if ($value is_compile_type mutable string) {
      # Pass
    }
  }

=head2 isa_error Operator

The C<isa_error> operator checks whether the type specified by a basic type ID can be assigned to a class type. This operator is normally used for error classes to check L</"eval_error_id Operator">.

  OPERAND isa_error TYPE

This operator performs L<integer promotional conversion|/"Integer Promotional Conversion"> on the operand I<OPERAND>.

And this operator checks whether the type specified by the basic type ID I<OPERAND> satisfies L<assignment requirement|SPVM::Document::Language::Types/"Assignment Requirement"> without data conversion to the type I<TYPE>.

If it is satisfied, this operator returns 1, otherwise returns 0.

The return type is int type.

Compilation Errors:

I<OPERAND> must be an L<integer type|SPVM::Document::Language::Types/"Integer Types"> within int. Otherwise, a compilation error occurs.

I<TYPE> must be a class type. Otherwise, a compilation error occurs.

Examples:

  if (eval_error_id isa_error Error) {
    
  }
  
  if (eval_error_id isa_error Error::System) {
    
  }
  
=head2 is_error Operator

The C<is_error> operator checks whether the type specified by a basic type ID is equal to a class type. This operator is normally used for error classes to check L</"eval_error_id Operator">.

  OPERAND is_error TYPE

This operator performs L<integer promotional conversion|/"Integer Promotional Conversion"> on the operand I<OPERAND>.

And this operator checks whether the type specified by the basic type ID I<OPERAND> is equal to the type I<TYPE>.

If it is, this operator returns 1, otherwise returns 0.

The return type is int type.

Compilation Errors:

I<OPERAND> must be an L<integer type|SPVM::Document::Language::Types/"Integer Types"> within int. Otherwise, a compilation error occurs.

I<TYPE> must be a class type. Otherwise, a compilation error occurs.

Examples:

  if (eval_error_id is_error Error) {
    
  }
  
  if (eval_error_id is_error Error::System) {
    
  }

=head2 type_name Operator

The C<type_name> operator gets the type name of the object.

  type_name OPERAND

If the object I<OPERAND> is defined, creates a string with the type name of I<OPERAND> and returns it. Otherwise, returns an undefined value.

The return type is string type.

Compilation Errors.

I<OPERAND> must be an object type. Otherwise, a compilation error occurs.

Examples:
  
  # "Point"
  my $point = Point->new;
  my $type_name = type_name $point;
  
  # "Point"
  my $point = (object)Point->new;
  my $type_name = type_name $point;

=head2 compile_type_name Operator

The C<compile_type_name> operator gets the compilation type of the operand I<OPERAND>.

  compile_type_name OPERAND

This operator creates a new string with the compilation type name of I<OPERAND> and returns it.

The return type is string type.

Examples:
  
  # Point
  my $point = Point->new;
  my $compile_type_name = type_name $point;
  
  # object
  my $point = (object)Point->new;
  my $compile_type_name = type_name $point;
  
  # mutable string
  my $string = (mutable string)copy "abc";
  my $compile_type_name = compile_type_name $string;
  
  # Hash of List of string
  my $object = (Hash of List of string)undef;
  my $compile_type_name = compile_type_name $object;
  
=head2 basic_type_id Operator

The C<basic_type_id> operator gets the basic type ID of a type.

  basic_type_id TYPE

This operator returns the basic type ID of the type I<TYPE>.

The return type is int type.

Examples:

  my $basic_type_id = basic_type_id int;
  
  my $basic_type_id = basic_type_id int[];
  
  my $error_basic_type_id = basic_type_id Error;

=head2 can Operator

The C<can> operator checks if a method can be called. 

  OPERAND can METHOD_NAME

If I<OPERAND> is able to call the method given by I<METHOD_NAME>, returns 1, otherwise returns 0.

I<METHOD_NAME> is a L<method name|SPVM::Document::Language::Tokenization/"Method Name"> or an empty string C<"">.

The return type is int type.

Compilation Errors:

The type of I<OPERAND> must be the class type or L<interface type|SPVM::Document::Language::Types/"Interface Types">. Otherwise, a compilation error occurs.

The METHOD_NAME must be a method name or an empty string C<"">. Otherwise, a compilation error occurs.

Examples:

  my $stringable = (Stringable)Point->new(1, 2);
  
  if ($stringable can to_string) {
    # ...
  }
  
  if ($stringable can "") {
    # ...
  }

=head2 args_width Operator

The C<args_width> operator gets the stack length of the arguments passed to the method.

  args_width

Note that the stack length of the arguments is different from the length of the arguments.

If the method call is the instance method call, the stack length of the arguments is the length of the arguments + 1 for the invocant.

If an argument is a multi-numeric type, the stack length of the argument becomes the length of the fields.

Examples:
  
  static method my_static_method : int ($args : int, $bar : int = 0) {
    my $args_width = args_width;
    
    return $args_width;
  };
  
  # 1
  &my_static_method(1);
  
  # 2
  &my_static_method(1, 2);
  
  static method my_instance_method : int ($args : int, $bar : int = 0) {
    my $args_width = args_width;
    
    return $args_width;
  };
  
  # 2 (1 + the invocant)
  &my_instance_method(1);
  
  # 3 (2 + the invocant)
  &my_instance_method(1, 2);

  static method my_mulnum_method : int ($z : Complex_2d, $bar : int = 0) {
    my $args_width = args_width;
    
    return $args_width;
  };

  # 2 (The length of the fields of Complex_2d)
  my $z : Complex_2d;
  &my_mulnum_method($z);
  
  # 3 (The length of the fields of Complex_2d + 1)
  my $z : Complex_2d;
  &my_mulnum_method($z, 2);

=head2 eval_error_id Operator

The C<eval_error_id> operatoer gets the value of C<eval_error_id>.

  eval_error_id

See L<SPVM::Document::Language::ExceptionHandling> about the way to use the C<eval_error_id> operator.

=head2 weaken Operator

The C<weaken> operator enables a L<weak reference|SPVM::Document::Language::GarbageCollection/"Weak Reference">.

  weaken INVOCANT->{FIELD_NAME};

I<INVOCANT-E<gt>{FIELD_NAME}> is a L<field access|/"Field Access">.

This operator enable a weak reference of the field specified by I<FIELD_NAME> of the type of I<INVOCANT>.

The return type is the void type.

Compilation Errors:

Compiliation errors caused by the syntax of L<field access|/"Field Access"> could occur.

The incovant of the field access must be a class type.

The type of I<INVOCANT-E<gt>{FIELD_NAME}> must be an object type. Otherwise, a compilation error occurs.

Examples:

  # Exmaples of weaken operator
  weaken $object->{point};

=head2 unweaken Operator

The C<unweaken> operator disables a L<weak reference|SPVM::Document::Language::GarbageCollection/"Weak Reference">.

  unweaken INVOCANT->{FIELD_NAME};

I<INVOCANT-E<gt>{FIELD_NAME}> is a L<field access|/"Field Access">.

This operator enable a weak reference of the field specified by I<FIELD_NAME> of the type of I<INVOCANT>.

The return type is the void type.

Compilation Errors:

Compiliation errors caused by the syntax of L<field access|/"Field Access"> could occur.

The incovant of the field access must be a class type.

The type of I<INVOCANT-E<gt>{FIELD_NAME}> must be an object type. Otherwise, a compilation error occurs.

Examples:

  # Exmaples of unweaken operator
  unweaken $object->{point};

=head2 isweak Operator

The C<isweak> operator checks if L<weak reference|SPVM::Document::Language::GarbageCollection/"Weak Reference"> of a field is enabled.

  isweak INVOCANT->{FIELD_NAME};

I<INVOCANT-E<gt>{FIELD_NAME}> is a L<field access|/"Field Access">.

If the field specified by I<FIELD_NAME> of the object I<INVOCANT> is weaken, this operator returns 1, otherwise returns 0.

The return type is int type.

Compilation Errors:

Compiliation errors caused by the syntax of L<field access|/"Field Access"> could occur.

The incovant of the field access must be a class type.

The type of I<INVOCANT-E<gt>{FIELD_NAME}> must be an object type. Otherwise, a compilation error occurs.

Examples:

  # Exmaples of isweak operator
  my $isweak = isweak $object->{point};

=head2 exists Operator

The C<exists> operator checks if a field value exists.

  exists INVOCANT->{FIELD_NAME};

I<INVOCANT-E<gt>{FIELD_NAME}> is a L<field access|/"Field Access">.

If the field specified by I<FIELD_NAME> of the object I<INVOCANT> exists, this operator returns 1, otherwise returns 0.

The return type is int type.

Compilation Errors:

Compiliation errors caused by the syntax of L<field access|/"Field Access"> could occur.

The incovant of the field access must be a class type.

The type of I<INVOCANT-E<gt>{FIELD_NAME}> must be an object type or a numeric type. Otherwise, a compilation error occurs.

Examples:

  # Exmaples of exists operator
  my $exists = exists $object->{point};

=head2 delete Operator

The C<delete> operator delete a field value.

  delete INVOCANT->{FIELD_NAME};

The field existence flag is set to 0, and the value of the field is set to 0 in the case of numeric types or undef in the case of object types.

I<INVOCANT-E<gt>{FIELD_NAME}> is a L<field access|/"Field Access">.

This operator enable a weak reference of the field specified by I<FIELD_NAME> of the type of I<INVOCANT>.

The return type is the void type.

Compilation Errors:

Compiliation errors caused by the syntax of L<field access|/"Field Access"> could occur.

The incovant of the field access must be a class type.

The type of I<INVOCANT-E<gt>{FIELD_NAME}> must be an object type or a numeric type. Otherwise, a compilation error occurs.

Examples:

  # Exmaples of delete operator
  delete $object->{point};

=head2 copy_fields Operator

The C<copy_fields> operator copies fields.

  copy_fields DIST_OPERAND, SRC_OPERAND, TYPE;

The type of I<TYPE> must be a class type.

The copy_fields operator copies every field from I<SRC_OPERAND> to I<DIST_OPERAND> using all the field names defined in I<TYPE> class.

For example, if the field names defined in I<TYPE> class are C<x>, C<y>, and C<z>, then copy_field operator is expanded to the following codes:
  
  if (exists SRC_OPERAND->{x}) {
    DIST_OPERAND->{x} = SRC_OPERAND->{x};
  }
  if (exists SRC_OPERAND->{y}) {
    DIST_OPERAND->{y} = SRC_OPERAND->{y};
  }
  if (exists SRC_OPERAND->{z}) {
    DIST_OPERAND->{z} = SRC_OPERAND->{z};
  }

Compilation Errors:

The type of I<TYPE> must be a class type. Otherwise, a compilation error occurs. 

Examples:
  
  # Exampels of copy_fields operator
  my $object = MyClass->new;
  
  my $object_child = MyClass::Child->new;
  
  copy_fields $object_child, $object, MyClass;

=head2 set_length Operator

The C<set_length> operator sets the length of a string or an array.
  
  set_length(OBJECT_OPERAND, LENGTH_OPERAND);

The type of I<OBJECT_OPERAND> must be a string or an array.

The type of I<LENGTH_OPERAND> is an integer value with C<int>.

If the length is extended, L</"set_capacity Operator"> is called if needed.

If the length is extended, the extended elements are set to its default value.

If the length is shorten, unused elements is destroyed.

Compilation Errors:

I<OBJECT_OPERAND> type must be an array type or string type. Otherwise a compilation error occurs.

I<OBJECT_OPERAND> type must be an integer type. Otherwise a compilation error occurs.

I<LENGTH_OPERAND> type must be an integer type. Otherwise a compilation error occurs.

Exceptions:

I<OBJECT_OPERAND> must be defined. Otherwise an exception is thrown.

the type of I<OBJECT_OPERAND> must be string type or an array type. Otherwise an exception is thrown.

I<OBJECT_OPERAND> must not be a fixed length object. If so, an exception is thrown.

Examples:

  # Examples of set_length operator
  my $string = (mutable string)copy "abc";
  
  set_length($string, 4);

=head2 set_capacity Operator

The C<set_capacity> operator sets the capacity of a string or an array.
  
  set_capacity(OBJECT_OPERAND, CAPACITY_OPERAND);

The type of I<OBJECT_OPERAND> must be a string or an array.

The type of I<CAPACITY_OPERAND> is an integer value with C<int>.

The new capacity is allocated and old elements are copied on it.

Compilation Errors:

I<OBJECT_OPERAND> type must be an array type or string type. Otherwise a compilation error occurs.

I<OBJECT_OPERAND> type must be an integer type. Otherwise a compilation error occurs.

I<CAPACITY_OPERAND> type must be an integer type. Otherwise a compilation error occurs.

Exceptions:

I<OBJECT_OPERAND> must be defined. Otherwise an exception is thrown.

The type of I<OBJECT_OPERAND> must be string type or an array type. Otherwise an exception is thrown.

I<OBJECT_OPERAND> must not be a fixed capacity object. If so, an exception is thrown.

If this operator cannot allocate memory, an exception is thrown.

If I<CAPACITY_OPERAND> is smaller capacity than its length plus 1, an exception is thrown.

Examples:

  # Examples of set_capacity operator
  my $string = (mutable string)copy "abc";
  
  set_capacity($string, 4);

=head1 Scope Operations

See the doc of L<scope|SPVM::Document::Language::GarbageCollection/"Scope"> about scope operations.

=head1 Method Call

A method call is an L<operator|/"Operators"> to call a L<method|SPVM::Document::Language::Class/"Method">.

A method call resolves to one of the three types of method calls, a L<class method call|/"Class Method Call">, a L<static instance method call|/"Static Instance Method Call">, and an L<instance method call|/"Instance Method Call"> by L<method call resolution|SPVM::Document::Language::Class/"Method Call Resolution">.

If the method call is a static instance method call or an instance method call, the invocant is prepended to the given arguments.

The method call performs L<method call execution|/"Method Call Execution"> given the arguments.

=head2 Class Method Call

A class method call calls a class method.

  CLASS_TYPE->METHOD_NAME
  CLASS_TYPE->METHOD_NAME(OPT_ARGS)
  &METHOD_NAME
  &METHOD_NAME(OPT_ARGS)

See L<Class Method Call Resolution|SPVM::Document::Language::Class/"Class Method Call Resolution"> about I<CLASS_TYPE>, I<METHOD_NAME>, I<OPT_ARGS>, C<&>, and the resolution of a class method call.

Examples:

  # Examples of static instance method calls
  my $point3d = Point3D->new;
  
  $point3d->Point::clear;
  
  $point3d->SUPER::clear;

=head2 Static Instance Method Call

A static instance method call calls an instance method specifying a class.

  INVOCANT->CLASS_TYPE::METHOD_NAME
  INVOCANT->CLASS_TYPE::METHOD_NAME(OPT_ARGS)

See L<Static Instance Method Call Resolution|SPVM::Document::Language::Class/"Static Instance Method Call Resolution"> about I<INVOCANT>, I<CLASS_TYPE>, I<METHOD_NAME>, I<OPT_ARGS>, and the resolution of a static instance method call.

Examples:

  # Examples of static instance method calls
  $object->SUPER::bar(5, 3. 6);
  
  $point3d->Point::clear;

=head2 Instance Method Call

An instance method call calls an instance method.

  INVOCANT->METHOD_NAME
  INVOCANT->METHOD_NAME(OPT_ARGS)

See L<Instance Method Call Resolution|SPVM::Document::Language::Class/"Instance Method Call Resolution"> about I<INVOCANT>, I<CLASS_TYPE>, I<METHOD_NAME>, I<OPT_ARGS>, and the resolution of an instance method call.

Examples:

  # Examples of instance method calls
  
  my $point = Point->new;
  
  $point->clear;
  
  my $stringable = (Stringable)$point;
  
  my $string = $strinble->to_string;

=head2 Method Call Execution

The L<argument width|SPVM::Document::NativeClass/"Arguments Width"> is stored to L<runtime stack|SPVM::Document::NativeClass/"Runtime Stack">.

The call stack depth stored in L<runtime stack|SPVM::Document::NativeClass/"Runtime Stack"> is incremented by 1.

If the call stack depth is greater than 1000, an exception is thrown.

If the method call is not a class method call, the arugments of the object type are checked whether the following L<isa|/"isa Operator"> operator returns a true value.

  ARG isa TYPE_OF_ARG

I<ARG> is an argument. I<TYPE_OF_ARG> is the type of the corresponding arugment of the method.

If the return vlaue is not a true value, an exception is thrown.

If the method is a L<INIT method|SPVM::Document::Language::Class/"INIT Method"> and it is already called, nothing is performed.

If the method is a L<native method|SPVM::Document::Language::Class/"Native Method">, a L<native method call execution|/"Native Method Call Execution"> is performed.

Otherwise if the method is a L<precompilation method|SPVM::Document::Language::Class/"Precompilation Method">, a L<precompilation method call execution|/"Precompilation Method Call Execution"> is performed.

Otherwise a L<VM method call execution|/"VM Method Call Execution"> is performed.

If an exception is thrown by the method call execution, the exception is thrown.

If the return type of the method is an object type, the object is pushed to L<native mortal stack|SPVM::Document::NativeClass/"Native Mortal Stack">.

The call stack depth stored in L<runtime stack|SPVM::Document::NativeClass/"Runtime Stack"> is decremented by 1. This resotre is always performed even if an excetpion is thrown.

=head3 VM Method Call Execution

Heap memories for local variables are allocated.

The L<enter_scope|SPVM::Document::NativeAPI/"enter_scope"> native API is called.

SPVM operation codes generated from L<method implementation|SPVM::Document::Language::Class/"Method Implementation"> are executed.

The L<leave_scope|SPVM::Document::NativeAPI/"leave_scope"> native API is called.

Heap memories for local variables are released.

=head3 Precompilation Method Call Execution

If a set of the machine codes of the precompilation method is loaded, the program executes it.

Otherwise if L<is_precompile_fallback|SPVM::Document::NativeAPI::Method/"is_precompile_fallback"> native API returns a true value, the program executes L</"VM Method Call Execution">.

Otherwise an exception is thrown.

=head3 Native Method Call Execution

The L<enter_scope|SPVM::Document::NativeAPI/"enter_scope"> native API is called.

If a set of the machine codes of L<native function|SPVM::Document::NativeClass/"Native Function"> of the native method is loaded, the program executes it.

Otherwise an exception is thrown after executing the following code.

The L<leave_scope|SPVM::Document::NativeAPI/"leave_scope"> native API is called.

=head1 See Also

=over 2

=item * L<Class Definition|SPVM::Document::Language::Statements>

=item * L<Class Definition|SPVM::Document::Language::Class>

=item * L<Types|SPVM::Document::Language::Types>

=item * L<Exception Handling|SPVM::Document::Language::ExceptionHandling>

=item * L<Garbage Collection|SPVM::Document::Language::GarbageCollection>

=item * L<SPVM::Document::Language>

=item * L<SPVM::Document>

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

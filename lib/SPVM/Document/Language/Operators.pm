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

This operator performs the L<integer promotional conversion|SPVM::Document::Language::Types/"Integer Promotional Conversion"> on the operand I<OPERAND>, and returns it.

The return type is the type after the conversion is performed.

Compilation Errors:

The type of I<OPERAND> must be a L<numeric type|SPVM::Document::Language::Types/"Numeric Types">, otherwise a compilation error occurs.

Examples:
  
  # Examples of the unary plus operator
  my $num = +10;

=head3 Unary Minus Operator

The unary minus operator C<-> is a unary operator that returns the negated value of its operand.

  -OPERAND

This operator performs the L<integer promotional conversion|SPVM::Document::Language::Types/"Integer Promotional Conversion"> on the operand I<OPERAND>, negates it, and returns it.

The return type is the type after the conversion is performed.

Compilation Errors:

The type of I<OPERAND> must be a L<numeric type|SPVM::Document::Language::Types/"Numeric Types">, otherwise a compilation error occurs.

Examples:

  # Examples of the unary minus operator
  my $num = -10;

=head3 Addition Operator

The addition operator C<+> adds two operands.
  
  LEFT_OPERAND + RIGHT_OPERAND

This operator performs the L<binary numeric conversion|SPVM::Document::Language::Types/"Binary Numeric Conversion"> on the left operand I<LEFT_OPERAND> and the right operand I<RIGHT_OPERAND>.

And it performs the same operation as the following C language operation, and returns its return value.

  LEFT_OPERAND + RIGHT_OPERAND

The return type is the type after the L<binary numeric conversion|SPVM::Document::Language::Types/"Binary Numeric Conversion"> is performed.

Compilation Errors:

The type of I<LEFT_OPERAND> must be a L<numeric type|SPVM::Document::Language::Types/"Numeric Types">, otherwise a compilation error occurs.

The type of I<RIGHT_OPERAND> must be a L<numeric type|SPVM::Document::Language::Types/"Numeric Types">, otherwise a compilation error occurs.

Examples:

  # Examples of the addition operator
  my $result = 1 + 2;

=head3 Subtraction Operator

The subtraction operator C<-> subtracts its right operand from its left operand.
  
  LEFT_OPERAND - RIGHT_OPERAND

This operator performs the L<binary numeric conversion|SPVM::Document::Language::Types/"Binary Numeric Conversion"> on the left operand I<LEFT_OPERAND> and the right operand I<RIGHT_OPERAND>.

And it performs the same operation as the following C language operation, and returns its return value.

  LEFT_OPERAND - RIGHT_OPERAND

The return type is the type after the L<binary numeric conversion|SPVM::Document::Language::Types/"Binary Numeric Conversion"> is performed.

Compilation Errors:

The type of I<LEFT_OPERAND> must be a L<numeric type|SPVM::Document::Language::Types/"Numeric Types">, otherwise a compilation error occurs.

The type of I<RIGHT_OPERAND> must be a L<numeric type|SPVM::Document::Language::Types/"Numeric Types">, otherwise a compilation error occurs.

Examples:

  # Examples of the subtraction operator
  my $result = 1 - 2;

=head3 Multiplication Operator

The multiplication operator C<*> multiplies two operands.
  
  LEFT_OPERAND * RIGHT_OPERAND

This operator performs the L<binary numeric conversion|SPVM::Document::Language::Types/"Binary Numeric Conversion"> on the left operand I<LEFT_OPERAND> and the right operand I<RIGHT_OPERAND>.

And it performs the same operation as the following C language operation, and returns its return value.

  LEFT_OPERAND * RIGHT_OPERAND

The return type is the type after the L<binary numeric conversion|SPVM::Document::Language::Types/"Binary Numeric Conversion"> is performed.

Compilation Errors:

The type of I<LEFT_OPERAND> must be a L<numeric type|SPVM::Document::Language::Types/"Numeric Types">, otherwise a compilation error occurs.

The type of I<RIGHT_OPERAND> must be a L<numeric type|SPVM::Document::Language::Types/"Numeric Types">, otherwise a compilation error occurs.

Examples:

  # Examples of the multiplication operator
  my $result = 1 * 2;

=head3 Division Operator

The division operator C</> divides its left operand by its right operand.
  
  LEFT_OPERAND / RIGHT_OPERAND

This operator performs the L<binary numeric conversion|SPVM::Document::Language::Types/"Binary Numeric Conversion"> on the left operand I<LEFT_OPERAND> and the right operand I<RIGHT_OPERAND>.

And it performs the same operation as the following C language operation, and returns its return value.

  LEFT_OPERAND / RIGHT_OPERAND

The return type is the type after the L<binary numeric conversion|SPVM::Document::Language::Types/"Binary Numeric Conversion"> is performed.

Exceptions:

If the type of the left operand I<LEFT_OPERAND> and the right operand I<RIGHT_OPERAND> are an integer type and I<RIGHT_OPERAND> is 0, an exception is thrown.

Compilation Errors:

The type of I<LEFT_OPERAND> must be a L<numeric type|SPVM::Document::Language::Types/"Numeric Types">, otherwise a compilation error occurs.

The type of I<RIGHT_OPERAND> must be a L<numeric type|SPVM::Document::Language::Types/"Numeric Types">, otherwise a compilation error occurs.

Examples:

  # Examples of the division operator
  my $result = 1 / 2;

=head3 Division Unsigned Int Operator

The division unsigned int operator C<div_uint> interprets its two operands as unsigned 32bit integers, and divides its left operand by its right operand.
  
  LEFT_OPERAND div_uint RIGHT_OPERAND

This operator performs the same operation as the following C language operation, and returns its return value.

  (uint32_t)LEFT_OPERAND / (uint32_t)RIGHT_OPERAND

The return type is the int type.

Exceptions:

If I<RIGHT_OPERAND> is 0, an exception is thrown.

Compilation Errors:

The type of I<LEFT_OPERAND> must be the int type, otherwise a compilation error occurs.

The type of I<RIGHT_OPERAND> must be the int type, otherwise a compilation error occurs.

Examples:

  # Examples of the division unsigned int operator
  my $result = 1 div_uint 2;

=head3 Division Unsigned Long Operator

The division unsigned long operator C<div_ulong> interprets its two operands as unsigned 64bit integers, and divides its left operand by its right operand.

  LEFT_OPERAND div_ulong RIGHT_OPERAND

This operator performs the same operation as the following C language operation, and returns its return value.

  (uint64_t)LEFT_OPERAND / (uint64_t)RIGHT_OPERAND

The return type is the long type.

Exceptions:

If I<RIGHT_OPERAND> is 0, an exception is thrown.

Compilation Errors:

The type of I<LEFT_OPERAND> must be the long type, otherwise a compilation error occurs.

The type of I<RIGHT_OPERAND> must be the long type, otherwise a compilation error occurs.

Examples:

  # Examples of the division unsigned long operator
  my $result = 1L div_ulong 2L;

=head3 Modulo Operator

The modulo operator C<%> calculates the modulo of the division of its two operands.
  
  LEFT_OPERAND % RIGHT_OPERAND

This operator performs the L<binary numeric conversion|SPVM::Document::Language::Types/"Binary Numeric Conversion"> on the left operand I<LEFT_OPERAND> and the right operand I<RIGHT_OPERAND>.

And it performs the same operation as the following C language operation, and returns its return value.

  RETURN_VALUE = LEFT_OPERAND % RIGHT_OPERAND;
  if ((LEFT_OPERAND < 0) != (RIGHT_OPERAND < 0) && RETURN_VALUE) { RETURN_VALUE += RIGHT_OPERAND; }

The return type is the type after the L<binary numeric conversion|SPVM::Document::Language::Types/"Binary Numeric Conversion"> is performed.

Exceptions:

If I<RIGHT_OPERAND> is 0, an exception is thrown.

Compilation Errors:

The type of I<LEFT_OPERAND> must be an L<integer type|SPVM::Document::Language::Types/"Integer Types">, otherwise a compilation error occurs.

The type of I<RIGHT_OPERAND> must be an L<integer type|SPVM::Document::Language::Types/"Integer Types">, otherwise a compilation error occurs.

Examples:

  # Examples of the modulo operator
  my $result = 1 % 2;

=head3 Modulo Unsigned Int Operator

The modulo unsigned int operator C<mod_uint> interprets its two operands as unsigned 32bit integers, and calculates the modulo of the division of its two operands.
  
  LEFT_OPERAND mod_uint RIGHT_OPERAND

This operator performs the same operation as the following C language operation, and returns its return value.

  (uint32_t)LEFT_OPERAND % (uint32_t)RIGHT_OPERAND

The return type is the int type.

Exceptions:

If I<RIGHT_OPERAND> is 0, an exception is thrown.

Compilation Errors:

The type of I<LEFT_OPERAND> must be the int type, otherwise a compilation error occurs.

The type of I<RIGHT_OPERAND> must be the int type, otherwise a compilation error occurs.

Examples:

  # Examples of the modulo unsigned int operator
  my $result = 1 mod_uint 2;

=head3 Modulo Unsigned Long Operator

The modulo unsigned long operator C<mod_ulong> interprets its two operands as unsigned 64bit integers, and calculates the modulo of the division of its two operands.
  
  LEFT_OPERAND mod_ulong RIGHT_OPERAND

This operator performs the same operation as the following C language operation, and returns its return value.

  (uint64_t)LEFT_OPERAND % (uint64_t)RIGHT_OPERAND

The return type is is the long type.

Exceptions:

If I<RIGHT_OPERAND> is 0, an exception is thrown.

Compilation Errors:

The type of I<LEFT_OPERAND> must be the long type, otherwise a compilation error occurs.

The type of I<RIGHT_OPERAND> must be the long type, otherwise a compilation error occurs.

Examples:

  # Examples of the modulo unsigned long operator
  my $result = 1L mod_ulong 2L;

=head3 Increment Operators

=head4 Pre-Increment Operator

The pre-increment operator C<++> increases the value of an operand by 1, and returns it.

  ++OPERAND

This operator increases the value of the operand I<OPERAND> by 1 using the L<additonal operator|/"Addition Operator">, performs a L<type cast|/"Type Cast"> to the type of I<OPERAND> on it, and returns it.

The return type is the type of I<OPERAND>.

Compilation Errors:

I<OPERAND> must be a local variable, a class variable, a field access, an element access, a dereference, otherwise a compilation error occurs.

The type of I<OPERAND> must be a numeric type, otherwise a compilation error occurs.

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

This operator increases the value of the operand I<OPERAND> by 1 using the L<additonal operator|/"Addition Operator">, performs a L<type cast|/"Type Cast"> to the type of I<OPERAND> on it, assigns it on I<OPERAND>, and returns I<OPERAND> before performing the incrementation.

The return type is the type of I<OPERAND>.

Compilation Errors:

I<OPERAND> must be a local variable, a class variable, a field access, an element access, a dereference, otherwise a compilation error occurs.

The type of I<OPERAND> must be a numeric type, otherwise a compilation error occurs.

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

This operator decreases the value of the operand I<OPERAND> by 1 using the L<subtraction operator|/"Subtraction Operator">, performs a L<type cast|/"Type Cast"> to the type of I<OPERAND> on it, and returns it.

The return type is the type of I<OPERAND>.

Complation Errors:

I<OPERAND> must be a local variable, a class variable, a field access, an element access, a dereference, otherwise a compilation error occurs.

The type of I<OPERAND> must be a numeric type, otherwise a compilation error occurs.

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

This operator decreases the value of the operand I<OPERAND> by 1 using the L<subtraction operator|/"Subtraction Operator">, performs a L<type cast|/"Type Cast"> to the type of I<OPERAND> on it, assigns it on I<OPERAND>, and returns I<OPERAND> before performing the decrementation.

The return type is the type of I<OPERAND>.

Compilation Errors:

I<OPERAND> must be a local variable, a class variable, a field access, an element access, a dereference, otherwise a compilation error occurs.

The type of I<OPERAND> must be a numeric type, otherwise a compilation error occurs.

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

The bitwise AND operator C<&> performs the L<bitwise AND operation|https://en.wikipedia.org/wiki/Bitwise_operation#AND>.

  LEFT_OPERAND & RIGHT_OPERAND

This operator performs the L<binary numeric conversion|SPVM::Document::Language::Types/"Binary Numeric Conversion"> on the left operand I<LEFT_OPERAND> and the right operand I<RIGHT_OPERAND>.

And it performs the same operation as the following C language operation, and returns its return value.

  LEFT_OPERAND & RIGHT_OPERAND

The return type is the type after the L<binary numeric widening conversion|/"Binary Numeric Widening Type"> is performed.

Compilation Errors:

The type of I<LEFT_OPERAND> must be an L<integer type|SPVM::Document::Language::Types/"Integer Types">, otherwise a compilation error occurs.

The type of I<RIGHT_OPERAND> must be an L<integer type|SPVM::Document::Language::Types/"Integer Types">, otherwise a compilation error occurs.

Examples:
  
  # Examples of the bitwise AND operator
  my $num1 = 0xff;
  my $num2 = 0x12;
  my $result = $num1 & $num2;

=head4 Bitwise OR Operator

The bitwise OR operator C<|> performs the L<bitwise OR operation|https://en.wikipedia.org/wiki/Bitwise_operation#OR>.
  
  LEFT_OPERAND | RIGHT_OPERAND

This operator performs the L<binary numeric conversion|SPVM::Document::Language::Types/"Binary Numeric Conversion"> on the left operand I<LEFT_OPERAND> and the right operand I<RIGHT_OPERAND>.

And it performs the same operation as the following C language operation, and returns its return value.

  LEFT_OPERAND | RIGHT_OPERAND

The return type is the type after the L<binary numeric widening conversion|/"Binary Numeric Widening Type"> is performed.

Compilation Errors:

The type of I<LEFT_OPERAND> must be an L<integer type|SPVM::Document::Language::Types/"Integer Types">, otherwise a compilation error occurs.

The type of I<RIGHT_OPERAND> must be an L<integer type|SPVM::Document::Language::Types/"Integer Types">, otherwise a compilation error occurs.

Examples:
  
  # Examples of the bitwise OR operator
  my $num1 = 0xff;
  my $num2 = 0x12;
  my $result = $num1 | $num2;

=head4 Bitwise NOT Operator

The bitwise NOT operator C<~> performs the L<bitwise NOT operation|https://en.wikipedia.org/wiki/Bitwise_operation#NOT>.
  
  ~OPERAND

This operator performs the L<numeric widening conversion|SPVM::Document::Language::Types/"Numeric Widening Conversion"> on the operand I<OPERAND>.

And it performs the same operation as the following C language operation, and returns its return value.

  ~OPERAND

The return type is the type that the L<numeric widening conversion|SPVM::Document::Language::Types/"Numeric Widening Conversion"> is performed.

Compilation Errors:

The type of I<OPERAND> must be an L<integer type|SPVM::Document::Language::Types/"Integer Types">, otherwise a compilation error occurs.

Examples:
  
  # Examples of the bitwise NOT operator
  my $result = ~0xFF0A;

=head3 Shift Operators

=head4 Left Shift Operator

The left shift operator C<E<lt>E<lt>> performs the L<arithmetic left shift|https://en.wikipedia.org/wiki/Bitwise_operation#Arithmetic_shift>.

  LEFT_OPERAND << RIGHT_OPERAND

This operator performs the L<numeric widening conversion|SPVM::Document::Language::Types/"Numeric Widening Conversion"> on the left operand I<LEFT_OPERAND>.

And it performs the L<numeric widening conversion|SPVM::Document::Language::Types/"Numeric Widening Conversion"> on the right operand I<RIGHT_OPERAND>.

And it performs the same operation as the following C language operation, and returns its return value.

  LEFT_OPERAND << RIGHT_OPERAND

The return type is the type of I<LEFT_OPERAND>.

Compilation Erorrs:

The type of I<LEFT_OPERAND> must be an L<integer type|SPVM::Document::Language::Types/"Integer Types">, otherwise a compilation error occurs.

The type of I<RIGHT_OPERAND> must be an L<integer types within int|SPVM::Document::Language::Types/"Integer Types within int">, otherwise a compilation error occurs.

Examples:

  # Examples of the left shift operator
  my $result = 0xFF0A << 3;

=head4 Arithmetic Right Shift Operator

The arithmetic right shift operator C<E<gt>E<gt>> performs the L<arithmetic right shift|https://en.wikipedia.org/wiki/Bitwise_operation#Arithmetic_shift>.

  LEFT_OPERAND >> RIGHT_OPERAND

This operator performs the L<numeric widening conversion|SPVM::Document::Language::Types/"Numeric Widening Conversion"> on the left operand I<LEFT_OPERAND>.

And it performs the L<numeric widening conversion|SPVM::Document::Language::Types/"Numeric Widening Conversion"> on the right operand I<RIGHT_OPERAND>.

And it performs the same operation as the following C language operation, and returns its return value.

  LEFT_OPERAND >> RIGHT_OPERAND;

The return type is the type of I<LEFT_OPERAND>.

Compilation Errors:

The type of I<LEFT_OPERAND> must be an L<integer type|SPVM::Document::Language::Types/"Integer Types">, otherwise a compilation error occurs.

The type of I<RIGHT_OPERAND> must be an L<integer types within int|SPVM::Document::Language::Types/"Integer Types within int">, otherwise a compilation error occurs.

Examples:

  # Examples of the arithmetic right shift operator
  my $result = 0xFF0A >> 3;

=head4 Logical Right Shift Operator

The logical right shift operator C<E<gt>E<gt>E<gt>> performs the L<logical right shift|https://en.wikipedia.org/wiki/Bitwise_operation#Logical_shift>.
  
  LEFT_OPERAND >>> RIGHT_OPERAND

This operator performs the L<numeric widening conversion|SPVM::Document::Language::Types/"Numeric Widening Conversion"> on the left operand I<LEFT_OPERAND>.

And it performs the L<numeric widening conversion|SPVM::Document::Language::Types/"Numeric Widening Conversion"> on the right operand I<RIGHT_OPERAND>.

And if the type of I<LEFT_OPERAND> is the int type, it performs the same operation as the following C language operation

  (uint32_t)LEFT_OPERAND >> RIGHT_OPERAND

If the type of I<LEFT_OPERAND> is the long type, it performs the same operation as the following C language operation.

  (uint64_t)LEFT_OPERAND >> RIGHT_OPERAND

And returns its return value.

The return type is the type of I<LEFT_OPERAND>.

Compilation Errors:

The type of I<LEFT_OPERAND> must be an L<integer type|SPVM::Document::Language::Types/"Integer Types">, otherwise a compilation error occurs.

The type of I<RIGHT_OPERAND> must be an L<integer types within int|SPVM::Document::Language::Types/"Integer Types within int">, otherwise a compilation error occurs.

Examples:

  # Examples of the logical right shift operator
  my $result = 0xFF0A >>> 3;

=head2 Logical Operator

=head3 Logical AND Operator

The logical AND operator C<&&> performs a logical AND operation.
  
  LEFT_OPERAND && RIGHT_OPERAND

This operator performs the L<boolean conversion|SPVM::Document::Language::Types/"Boolean Conversion"> on the left operand I<LEFT_OPERAND>.

If the evaluated value is 0, it returns 0, otherwise performs the L<boolean conversion|SPVM::Document::Language::Types/"Boolean Conversion"> on the right operand I<RIGHT_OPERAND>.

And it returns the evaluated value of I<RIGHT_OPERAND>.

The return type is the int type.

Examples:

  # Examples of the logical AND operator
  if (1 && 0) {
    
  }

=head3 Logical OR Operator

The logical OR operator C<||> performes a logical OR operation.

  # The logical OR operator
  LEFT_OPERAND || RIGHT_OPERAND

Thg logical OR operator performs the L<boolean conversion|SPVM::Document::Language::Types/"Boolean Conversion"> on the left operand I<LEFT_OPERAND>.

If the evaluated value is not 0, it returns the evaluated value, otherwise performs the L<boolean conversion|SPVM::Document::Language::Types/"Boolean Conversion"> on the right operand I<RIGHT_OPERAND>.

And it returns the evaluated value of I<RIGHT_OPERAND>.

The return type is the int type.

Examples:

  # Examples of the logical OR operator
  if (1 || 0) {
    
  }

=head3 Logical NOT Operator

The logical NOT operator C<!> performes a logical NOT operation.

  !OPERAND

Thg logical NOT operator performs the L<boolean conversion|SPVM::Document::Language::Types/"Boolean Conversion"> on the operand I<OPERAND>.

If the evaluated value is 0, returns 1, otherwise returns 0.

The return type is the int type.

  # Examples of the logical NOT operator
  if (!1) {
    
  }

=head2 Array Length Operator

The array length operator C<@> gets the length of an array.
  
  @OPERAND
  @{OPERAND}

This operator returns the length the array I<OPERAND>.

The return type is the int type.

Exceptions:

I<OPERAND> must be defined, otherwise an exception is thrown.

Compilation Errors:

The type of I<OPERAND> must be an array type, otherwise a compilation error occurs.

Examples:
  
  # Examples of the array length operator
  my $nums = new int[10];
  my $length = @$nums;

=head2 scalar Operator

The C<scalar> operator returns its operand.

  scalar OPERAND

This operator returns the operand I<OPERAND>. I<OPERAND> must be the L<array length operator/"Array Length Operator">.

This operator exists only for readability.

The return type is the int type.

Compilation Errors:

I<OPERAND> must be the L<array length operator|/"Array Length Operator">, otherwise a compilation error occurs.

Examples:
  
  # Examples of the scalar operator
  my $nums = new int[3];
  say scalar @$nums;

=head2 Sequential Operator

The sequential operator is an operator with the following syntax.
  
  (OPERAND1, OPERAND2, ..., OPERANDn)

This operator evaluates operands C<OPERAND1>, C<OPERAND1> ... C<OPERANDn> from left to right, and returns the value of the rightmost operand C<OPERANDn>.

The return type is the type of C<OPERANDn>.

Examples:

  # Examples of the sequential operator
  
  # 3 is assigned to $foo
  my $foo = (1, 2, 3);
  
  # $x is 3, $ret is 5
  my $x = 1;
  my $y = 2;
  my $result = ($x += 2, $x + $y);

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

This operator performs the L<binary numeric conversion|SPVM::Document::Language::Types/"Binary Numeric Conversion"> on the left operand I<LEFT_OPERAND> and the right operand I<RIGHT_OPERAND>.

And it performs the same operation as the following C language operation, and returns its return value.

  (int32_t)(LEFT_OPERAND == RIGHT_OPERAND);
  (int32_t)(LEFT_OPERAND != RIGHT_OPERAND);
  (int32_t)(LEFT_OPERAND > RIGHT_OPERAND);
  (int32_t)(LEFT_OPERAND >= RIGHT_OPERAND);
  (int32_t)(LEFT_OPERAND < RIGHT_OPERAND);
  (int32_t)(LEFT_OPERAND <= RIGHT_OPERAND);
  (int32_t)(LEFT_OPERAND > RIGHT_OPERAND ? 1 : LEFT_OPERAND < RIGHT_OPERAND ? -1 : 0);

The return type is the int type.

Compilation Errors:

C<==>, C<!=>

The type of the I<LEFT_OPERAND> must be a numeric type, an object type, a reference type, or the undef type, otherwise a compilation error occurs.

The type of the I<RIGHT_OPERAND> must be a numeric type, an object type, a reference type, or the undef type, otherwise a compilation error occurs.

If the type of the I<LEFT_OPERAND> is a numeric type, the type of the I<RIGHT_OPERAND> must be a numeric type, otherwise a compilation error occurs.

If the type of the I<LEFT_OPERAND> is an object type, the type of the I<RIGHT_OPERAND> must be an object type or the undef type, otherwise a compilation error occurs.

If the type of the I<LEFT_OPERAND> is the undef type, the type of the I<RIGHT_OPERAND> must be an object type or the undef type, otherwise a compilation error occurs.

If the type of the I<LEFT_OPERAND> is a reference type, the type of the I<RIGHT_OPERAND> must be a reference type, otherwise a compilation error occurs.

C<E<lt>>, C<E<lt>=>, C<E<gt>>, C<E<gt>=>, C<E<lt>=E<gt>>

The type of the I<LEFT_OPERAND> must be a numeric type, otherwise a compilation error occurs.

The type of the I<RIGHT_OPERAND> must be a numeric type, otherwise a compilation error occurs.

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

The return type is the int type. 

Compilation Errors.

The type of I<LEFT_OPERAND> must be the string type or the byte[] type, otherwise a compilation error occurs.

The type of I<RIGHT_OPERAND> must be the string type or the byte[] type, otherwise a compilation error occurs.

=head2 Constant Operator

The constant operator gets a constant value represented by a literal.

  LITERAL

I<LITERAL> is a L<literal|SPVM::Document::Language::Tokenization/"Literal">.

The return type is the type of I<LITERAL>.

Compilation Errors:

Compilation errors casued by L<literal|SPVM::Document::Language::Tokenization/"Literal"> syntax could occur.

=head2 length Operator

The C<length> operator gets the length of a string.

  length OPERAND

If the string I<OPERAND> is defind, this operator returns the length of I<OPERAND>. Note that this length is in bytes, not the number of UTF-8 characters.

If I<OPERAND> is not defined, returns 0.

The return type is the int type.

Compilation Errors:

The type of I<OPERAND> must be the string type, otherwise a compilation error occurs.

Examples:
  
  # Examples of The length operator
  
  # The length is 5
  my $message = "Hello";
  my $length = length $message;
  
  # The length is 9
  my $message = "あいう";
  my $length = length $message;

=head2 String Concatenation Operator

The string concatenation operator C<.> concats two strings.
  
  LEFT_OPERAND . RIGHT_OPERAND

This operator performs the L<numeric-to-string conversion|SPVM::Document::Language::Types/"Numeric-to-String Conversion"> on the left operand I<LEFT_OPERAND> if the type of I<LEFT_OPERAND> is a L<numeric type|SPVM::Document::Language::Types/"Numeric Types">.

And it performs the L<numeric-to-string conversion|SPVM::Document::Language::Types/"Numeric-to-String Conversion"> on the right operand I<RIGHT_OPERAND> if the type of I<RIGHT_OPERAND> is a L<numeric type|SPVM::Document::Language::Types/"Numeric Types">.

And it concats L<LEFT_OPERAND> and L<RIGHT_OPERAND>, and returns its return value.

The type of L<LEFT_OPERAND> and L<RIGHT_OPERAND> are allowed to be the byte[] type.

The return type is the string type.

Exceptions:

I<LEFT_OPERAND> must be defined, otherwise an exception is thrown.

I<RIGHT_OPERAND> must be defined, otherwise an exception is thrown.

Compilation Errors:

The type of I<LEFT_OPERAND> must be the string type, the byte[] type, or a numeric type, otherwise a compilation error occurs.

The type of I<RIGHT_OPERAND> must be the string type, the byte[] type, or a numeric type, otherwise a compilation error occurs.

Examples:
  
  # Examples of the string concatenation operator
  my $result = "abc" . "def";
  my $result = "def" . 34;

=head2 new_string_len Operator

The C<new_string_len> operator creates a new string with a length.
  
  new_string_len OPERAND

This operator performs the L<integer promotional conversion|SPVM::Document::Language::Types/"Integer Promotional Conversion"> on the length I<OPERAND>.

And creates a new string with the length, fills all characters in the string with C<\0>, and returns it.

The return type is the string type.

Exceptions:

I<OPERAND> must be greater than or equal to 0, otherwise an exception is thrown.

Compilation Errors:

The type of I<OPERAND> must be an L<integer type|SPVM::Document::Language::Types/"Integer Types"> within int, otherwise a compilation error occurs.

Examples:
  
  # Examples of the new_string_len operator
  my $message = new_string_len 5;

=head2 make_read_only Operator

The C<make_read_only> operator makes a string read-only.

  make_read_only OPERAND

If the string I<OPERAND> is defined, this operator makes I<OPERAND> read-only.

A read-only string cannnot be cast to the L<mutable|SPVM::Document::Language::Types/"mutable Type Qualifier"> string type. If so, an exception is thrown.

The return type is the void type.

Compilation Errors:

I<OPERAND> must be the string type, otherwise a compilation error occurs.

Examples:

  # Examples of the make_read_only operator
  
  # A string
  my $string = new_string_len 3;
  
  # Make the string read-only
  make_read_only $string;
  
  # The conversion to the mutable string type throw an exception.
  my $string_mutable = (mutable string)$string;

=head2 is_read_only Operator

The C<is_read_only> operator checks if a string is read-only.

  is_read_only OPERAND

If the string I<OPERAND> is defined and read-only, the C<is_read_only> operator returns 1, otherwise returns 0.

The return type is the int type.

Compilation Errors:

I<OPERAND> must be the string type, otherwise a compilation error occurs.

Examples:
  
  # Examples of the is_read_only operator
  my $message = "Hello";
  my $is_read_only = is_read_only $message;

=head2 print Operator

The C<print> operator prints a string to standard output.

  print OPERAND

This operator outputs the string I<OPERAND> to the L<SPVM's standard output|SPVM::Document::Language::System/"Standard Streams">.

If I<OPERAND> is not defined, this operator outputs nothing.

The return type is the void type.

Compilation Errors:

I<OPERAND> must be the string type, otherwise a compilation error occurs.

=head2 say Operator

The C<say> operator prints a string to standard output with a newline.

  say OPERAND

This operator outputs the string I<OPERAND> to the L<SPVM's standard output|SPVM::Document::Language::System/"Standard Streams"> with a newline C<\n>.

If I<OPERAND> is not defined, this operator outputs a newline C<\n>.

The return type is the void type.

Compilation Errors:

I<OPERAND> must be the string type, otherwise a compilation error occurs.

=head2 warn Operator

The C<warn> operator prints a string to standard error with a stack trace.

  warn
  warn OPERAND

If I<OPERAND> is omitted, I<OPERAND> is set to the string C<"Warning">.

This operator outputs I<OPERAND> to the L<SPVM's standard error|SPVM::Document::Language::System/"Standard Streams">.

If I<OPERAND> is not defined, this operator outputs the string C<"undef">.

If the type of I<OPERAND> is the string type and I<OPERAND> is defined, this operator outputs I<OPERAND>.

If the type of I<OPERAND> is an object type except for the string type and I<OPERAND> is defined, this operator outputs the type name and the address of I<OPERAND>, such as C<"Point(0x55d8a44ed090)">.

If the end character of the I<OPERAND> is not C<\n>, this operator outputs a newline, two tabs and a stack trace information following the output above.

A stack trace information consists of the current method name, file name, and line number.

  MyClass->test at path/MyClass.spvm line 33

The return type is the void type.

Compilation Errors:

The type of I<OPERAND> must be an object type, otherwise a compilation error occurs.

Examples:
  
  warn;
  warn "Something is wrong.";
  
  # Point(0x55d8a44ed090)
  my $point = Point->new;
  warn $point;

=head2 __FILE__ Operator

The C<__FILE__> operator gets the path of the file where the current class is defined.

  __FILE__

This operator creates a string with the path of the file where the current class is defined, and returns it.

The return type is the string type.

The return value can be changed by the L<file directive|SPVM::Document::Language::Tokenization/"File Directive">.

Examples:
  
  # Examples of the __FILE__ operator
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

The return type is the int type.

Examples:

  # Examples of the __LINE__ operator
  class Foo::Bar {
    static method baz : void () {
      my $line = __LINE__;
    }
  }

=head2 __PACKAGE__ Operator

The C<__PACKAGE__> operator gets the name of the L<outmost class|SPVM::Document::Language::Class/"Outmost Class">.

  __PACKAGE__

This operator creates a string with the name of the L<outmost class|SPVM::Document::Language::Class/"Outmost Class">, and returns it.

The return type is the string type.

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

See also the L<use statement|SPVM::Document::Language::Class/"use Statement"> about the way to load classes.

See also L<SPVM::Document::Language::GarbageCollection> about garbage collection of objects.

=head3 Creating an Object

The following syntax of the new operator creates a new object.

  new CLASS_TYPE;

The class type I<CLASS_TYPE> must be a loaded L<class type|SPVM::Document::Language::Types/"Class Type">.

This operator creates a new object of I<CLASS_TYPE>, and returns it.

The fields of the new object are initialized by its L<type initial value|SPVM::Document::Language::Types/"Type Initial Value">.

The return type is I<CLASS_TYPE>.

Compilation Errors:

I<CLASS_TYPE> must be a loaded class type, otherwise a compilation error occurs.

Examples:

  # Examples of the new operator - Creating a new object
  my $object = new Foo;

=head3 Creating an Array

The following syntax of the new operator creates a new array.

  new BASIC_TYPE[LENGTH]

The basic type I<BASIC_TYPE> must be a loaded L<basic type|SPVM::Document::Language::Types/"Basic Type">.

This operator performs the L<integer promotional conversion|SPVM::Document::Language::Types/"Integer Promotional Conversion"> on the length I<LENGTH>.

And creates a new array of the length I<LENGTH> which element type is I<BASIC_TYPE>.

And all elements of the new array are initialized by its L<type initial value|SPVM::Document::Language::Types/"Type Initial Value">.

And returns the new array.

The return type is C<I<BASIC_TYPE>[]>.

Exceptions:

I<LENGTH> must be greater than or equal to 0, otherwise an exception is thrown.

Compilation Errors:

I<LENGTH> must be an L<integer type|SPVM::Document::Language::Types/"Integer Types"> within int, otherwise a compilation error occurs.

Examples:

  # Examples of the new operator - Creating a new array
  my $values = new int[3];
  my $objects = new Foo[3];
  my $objects = new object[3];
  my $mulnum_values = new Complex_2d[3]

=head3 Creating a Multi-Dimensional Array

The following syntax of the new operator creates a new multi-dimensional array.

  new BASIC_TYPE[]..[LENGTH]

(C<[]..> means one or more C<[]>.)

The basic type I<BASIC_TYPE> must be a loaded L<basic type|SPVM::Document::Language::Types/"Basic Type">.

This operator performs the L<integer promotional conversion|SPVM::Document::Language::Types/"Integer Promotional Conversion"> on the length I<LENGTH>.

And creates a new multi-dimensional array of the length I<LENGTH> which element type is C<I<BASIC_TYPE>[]..>.

And all elements of the new multi-dimensional array are initialized by its L<type initial value|SPVM::Document::Language::Types/"Type Initial Value">.

And returns the new multi-dimensional array.

The return type is C<I<BASIC_TYPE>[]..[]>.

Exceptions:

I<LENGTH> must be greater than or equal to 0, otherwise an exception is thrown.

Compilation Errors:

I<LENGTH> must be an L<integer type|SPVM::Document::Language::Types/"Integer Types"> within int, otherwise a compilation error occurs.

The type dimension must be less than or equal to 255, otherwise a compilation error occurs.

Examples:

  # Examples of the new operator - Creating a new multi-dimensional array
  
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

This syntax is the same as L</"Array Initialization">, but the return type is always the L<any object array type|SPVM::Document::Language::Types/"Any Object Array Type"> C<object[]>.

And the length of the elements must be an even number.

Compilation Errors:

The length of the elements must be an even number, a compilation error occurs.

Examples:

  # Examples of the key-value array initialization
  
  # Empty
  my $key_values = {};
  
  # Key values
  my $key_values = {foo => 1, bar => "Hello"};

=head2 Anon Method Operator

The anon method operator creates an anon method.

  ANON_METHOD

This operator defines an L<anon method|SPVM::Document::Language::Class/"Anon Method"> I<ANON_METHOD>, creates a new object of the anon class that owns the anon method, and retunrs it.

Examples:
  
  my $comparator = (Comparator)method : int ($x1 : object, $x2 : object) {
    my $point1 = (Point)$x1;
    my $point2 = (Point)$x2;
    
    return $point1->x <=> $point2->x;
  };

=head2 undef Operator

The C<undef> operator returns an L<undefined value|SPVM::Document::Language::Types/"Undefined Value">.
  
  undef

The return type is the L<undef type|SPVM::Document::Language::Types/"undef Type">.

Examples:
  
  # Examples of the undef operator
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

The type of the operand must be the string type, a numeric array type, or a multi-numeric array type, otherwise a compilation error occurs.

Examples:
  
  # Exampels of the copy operator
  my $message = copy "abc";

=head2 dump Operator

The C<dump> operator gets the string representation dumping the data contained in the object.

  dump OPERAND

This operator creates a new string with the string representation dumping the data contained in the object I<OPERAND> and returns it.

The following is an example of the return value the C<dump> operator.
  
  # An return vlaue of the dump operator
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

The return type is the string type.

The string representation might be changed to make it more readable. So don't use the C<dump> operator for the purpose of the data serialization.

Compilation Errors:

I<OPERAND> must be an object type, ohterwise a compilation error occurs.

=head2 Reference Operator

The reference operator C<\> creates the reference to the value owned by a variable.

  \VARIALBE

This operator creates the reference to the value owned by the variable I<VARIALBE>, and returns it.

I<VARIALBE> is must be a local variable of a numeric type or a multi-numeric type.

The return type is the L<Reference Types|SPVM::Document::Language::Types/"Reference Types"> of I<VARIALBE>.

Compilation Errors:

I<VARIALBE> must be a local variable of a numeric type or a multi-numeric type, otherwise a compilation error occurs.

Examples:
  
  # Examples of the reference operator
  
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

The type of I<VARIABLE> must be a reference type, otherwise a compilation error occurs.

Examples:
  
  # Examples of the dereference operator
  my $num : int;
  my $num_ref = \$num;
  my $num_deref = $$num_ref;
  
  my $z : Complex_2d;
  my $z_ref = \$z;
  my $z_deref = $$z_ref;

=head2 Assignment Operator

The assignment operator C<=> performs an assignment.
  
  LEFT_OPERAND = RIGHTH_OPERAND

The assignment operator performs different operations depending on the left operand I<LEFT_OPERAND>.

If I<LEFT_OPERAND> is a local variable, this operator performs the operation that L<sets a local variable|/"Setting a Local Variable">.

If I<LEFT_OPERAND> is a class variable, this operator performs the operation that L<sets a class variable|/"Setting a Class Variable">.

If I<LEFT_OPERAND> is an element access, this operator performs the operation that L<sets an array element|/"Setting an Array Element">.

If I<LEFT_OPERAND> is a field access, this operator performs the operation that L<sets a field|/"Setting a Field">.

If I<LEFT_OPERAND> is a dereference, this operator performs the operation that L<sets a referenced value|/"Setting a Referenced Value">.

If I<LEFT_OPERAND> is the exception variable, this operator performs the operation that L<sets the exception variable|/"Setting the Exception Variable">.

See also L<SPVM::Document::Language::GarbageCollection/"Assignment"> about how the assignment operator changes the reference counts of I<LEFT_OPERAND> and I<RIGHTH_OPERAND>.

Examples:
  
  # Examples of the assignment operator
  
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

A special assignment operator is the combination of an operator such as C<+>, C<-> and the L<assignment operator|/"Assignment Operator"> C<=>.

  LEFT_OPERAND OPERATOR= RIGHTH_OPERAND

A special assignment operator is expanded to the following code.

  LEFT_OPERAND = (TYPE_OF_LEFT_OPERAND)(LEFT_OPERAND OPERATOR RIGHTH_OPERAND)

See the following code using a special assignment operator C<+=>. C<$x> is the int type.
  
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

=head2 Getting and Setting Operators

=head3 Getting a Local Variable

The operation of getting local variable gets the value of a L<local variable|SPVM::Document::Language::Class/"Local Variable">.

  $var

I<$var> is a L<local variable access|SPVM::Document::Language::Class/"Local Variable Access">.

This operation returns the value of I<$var>.

The return type is the type of I<$var>.

Compilation Errors:

Compiliation errors caused by the syntax of the L<local variable access|SPVM::Document::Language::Class/"Local Variable Access"> could occur.

Examples:

  $var;

=head3 Setting a Local Variable

The operation of setting a local variable sets a L<local variable|SPVM::Document::Language::Class/"Local Variable">.

  $var = OPERAND

I<$var> is a L<local variable access|SPVM::Document::Language::Class/"Local Variable Access">.

This operation sets I<$var> to I<OPERAND> using the L<assignment operator|/"Assignment Operator">, and returns the value after setting.

The return value is the type of I<$var>.

Compilation Errors:

Compiliation errors caused by the syntax of the L<local variable access|SPVM::Document::Language::Class/"Local Variable Access"> could occur.

The assignment must satisfy the L<assignment requirement|SPVM::Document::Language::Types/"Assignment Requirement">, otherwise a compilation error occurs.

Examples:

  $var = 3;

head3 Getting a Class Variable

The operation of getting a class variable gets the value of a L<class variable|SPVM::Document::Language::Class/"Class Variable">.

  $VAR

I<$VAR> is a L<class variable access|SPVM::Document::Language::Class/"Class Variable Access">.

This operation returns the value of I<$VAR>.

The return type is the type of I<$VAR>.

Compilation Errors:

Compiliation errors caused by the syntax of the L<class variable access|SPVM::Document::Language::Class/"Class Variable Access"> could occur.

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

=head3 Setting a Class Variable

The operation of setting a class variable operator sets a L<class variable|SPVM::Document::Language::Class/"Class Variable">.

  $VAR = OPERAND

I<$VAR> is a L<class variable access|SPVM::Document::Language::Class/"Class Variable Access">.

This operation sets I<$VAR> to I<OPERAND> using the L<assignment operator|/"Assignment Operator">, and returns the value after setting.

The return type is the type of I<$VAR>.

Compilation Errors:

Compiliation errors caused by the syntax of the L<class variable access|SPVM::Document::Language::Class/"Class Variable Access"> could occur.

The assignment must satisfy the L<assignment requirement|SPVM::Document::Language::Types/"Assignment Requirement">, otherwise a compilation error occurs.

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

=head3 Getting an Array Element

The operation of getting an array element gets an element of an L<array|SPVM::Document::Language::Types/"Array">.

  ARRAY->[INDEX]

I<ARRAY-E<gt>[INDEX]> is an L<element access|SPVM::Document::Language::Class/"Element Access">.

This operator performs the L<integer promotional conversion|SPVM::Document::Language::Types/"Integer Promotional Conversion"> on I<INDEX>.

And returns the element of I<ARRAY> at I<INDEX>.

The return type is the element type of I<ARRAY>.

Exceptions:

I<ARRAY> must be defined, otherwise an exception is thrown.

I<INDEX> must be greater than or equal to 0, otherwise an exception is thrown.

Compilation Errors:

Compiliation errors caused by the syntax of the L<element access|SPVM::Document::Language::Class/"Element Access"> could occur.

Examples:

  my $nums = new int[3];
  my $num = $nums->[1];
  
  my $points = new Point[3];
  my $point = $points->[1];

=head3 Setting an Array Element

The operation of setting array element sets an element of an array.

  ARRAY->[INDEX] = OPERAND

I<ARRAY-E<gt>[INDEX]> is an L<element access|SPVM::Document::Language::Class/"Element Access">.

This operator performs the L<integer promotional conversion|SPVM::Document::Language::Types/"Integer Promotional Conversion"> on I<INDEX>.

And sets the element of I<ARRAY> at I<INDEX> to I<OPERAND> using the L<assignment operator|/"Assignment Operator">, and returns the element after setting.

The return type is the element type.

Exceptions:

I<ARRAY> must be defined, otherwise an exception is thrown.

I<INDEX> must be greater than or equal to 0, otherwise an exception is thrown.

Compilation Errors:

Compiliation errors caused by the syntax of the L<element access|SPVM::Document::Language::Class/"Element Access"> could occur.

The assignment must satisfy the L<assignment requirement|SPVM::Document::Language::Types/"Assignment Requirement">, otherwise a compilation error occurs.

Examples:

  my $nums = new int[3];
  $nums->[1] = 3;
  
  my $points = new Point[3];
  $points->[1] = Point->new(1, 2);
  
=head3 Getting a Character

The operation of getting a character gets a character of a string.

  STRING->[INDEX]

I<STRING-E<gt>[INDEX]> is an L<character access|SPVM::Document::Language::Class/"Character Access">.

The type of I<STRING> is the string type.

This operator performs the L<integer promotional conversion|SPVM::Document::Language::Types/"Integer Promotional Conversion"> on I<INDEX>.

And returns the character of I<STRING> at I<INDEX>.

The return type is the byte type.

Exceptions:

I<STRING> must be defined, otherwise an exception is thrown.

I<INDEX> must be greater than or equal to 0, otherwise an exception is thrown.

Compilation Errors:

Compiliation errors caused by the syntax of the L<character access|SPVM::Document::Language::Class/"Character Access"> could occur.

Examples:

  my $string = "abc";
  my $char = $string->[0];

=head3 Setting a Character

The operation of setting a character sets the character of a string.

  STRING->[INDEX] = OPERAND

I<STRING-E<gt>[INDEX]> is an L<character access|SPVM::Document::Language::Class/"Character Access">.

This operator performs the L<integer promotional conversion|SPVM::Document::Language::Types/"Integer Promotional Conversion"> on I<INDEX>.

And sets the character of I<STRING> at I<INDEX> to I<OPERAND> using the L<assignment operator|/"Assignment Operator">, and returns the character after setting.

The return type is the byte type.

Exceptions:

I<STRING> must be defined, otherwise an exception is thrown.

I<INDEX> must be greater than or equal to 0, otherwise an exception is thrown.

If I<STRING> is not a mutable string, an exception is thrown.

Compilation Errors:

Compiliation errors caused by the syntax of the L<character access|SPVM::Document::Language::Class/"Character Access"> could occur.

The assignment must satisfy the L<assignment requirement|SPVM::Document::Language::Types/"Assignment Requirement">, otherwise a compilation error occurs.

Examples:

  my $string = new_string_len 3;
  $string->[0] = 'a';

=head3 Getting a Field

The operation of getting field gets the value of a field of a class type.

  INVOCANT->{FIELD_NAME}

I<INVOCANT-E<gt>{FIELD_NAME}> is a L<field access|SPVM::Document::Language::Class/"Field Access">.

This operation gets the value of the field specified by I<FIELD_NAME> of the type of I<INVOCANT>.

The retrun type is the type of the field.

Compilation Errors:

Compiliation errors caused by the syntax of the L<field access|SPVM::Document::Language::Class/"Field Access"> could occur.

Examples:

  my $point = Point->new;
  my $x = $point->{x};

=head3 Setting a Field

The operation of setting field sets the field of a class type.

  INVOCANT->{FIELD_NAME} = OPERAND

I<INVOCANT-E<gt>{FIELD_NAME}> is a L<field access|SPVM::Document::Language::Class/"Field Access">.

The type of I<INVOCANT> is a class type.

This operation sets the field specified by I<FIELD_NAME> of the type of I<INVOCANT> to I<OPERAND> using the L<assignment operator|/"Assignment Operator">, and returns the value of the field after setting.

The return type is the field type.

Compilation Errors:

Compiliation errors caused by the syntax of the L<field access|SPVM::Document::Language::Class/"Field Access"> could occur.

The assignment must satisfy the L<assignment requirement|SPVM::Document::Language::Types/"Assignment Requirement">, otherwise a compilation error occurs.

Examples:

  my $point = Point->new;
  $point->{x} = 1;

=head3 Getting a Multi-Numeric Field

The operation of getting a multi-numeric field gets the value of a field of a L<multi-numeric type|SPVM::Document::Language::Types/"Multi-Numeric Type">.

  INVOCANT->{FIELD_NAME}

I<INVOCANT-E<gt>{FIELD_NAME}> is a L<field access|SPVM::Document::Language::Class/"Field Access">.

The type of I<INVOCANT> is a multi-numeric type.

This operation gets the value of the field specified by I<FIELD_NAME> of the type of I<INVOCANT>.

The retrun type is the type of the field.

Compilation Errors:

Compiliation errors caused by the syntax of the L<field access|SPVM::Document::Language::Class/"Field Access"> could occur.

Examples:

  my $z : Complex_2d;
  my $re = $z->{re};

=head3 Setting a Multi-Numeric Field

The operation of setting multi-numeric field sets the field of the L<multi-numeric type|SPVM::Document::Language::Types/"Multi-Numeric Type">.

  INVOCANT->{FIELD_NAME} = OPERAND

I<INVOCANT-E<gt>{FIELD_NAME}> is a L<field access|SPVM::Document::Language::Class/"Field Access">.

The type of I<INVOCANT> is a multi-numeric type.

This operation sets the field specified by I<FIELD_NAME> of the type of I<INVOCANT> to I<OPERAND> using the L<assignment operator|/"Assignment Operator">, and returns the value of the field after setting.

The return type is the field type.

Compilation Errors:

Compiliation errors caused by the syntax of the L<field access|SPVM::Document::Language::Class/"Field Access"> could occur.

The assignment must satisfy the L<assignment requirement|SPVM::Document::Language::Types/"Assignment Requirement">, otherwise a compilation error occurs.

Examples:

  my $z : Complex_2d;
  $z->{re} = 2.5;
  
=head3 Getting a Referenced Multi-Numeric Field

The operation of getting a multi-numeric field gets the value of a field of a L<multi-numeric type|SPVM::Document::Language::Types/"Multi-Numeric Type"> referenced by a multi-numeric Reference Types.

This operation is expaned to the following code.

  ($INVOCANT)->{FIELD_NAME}

The type of I<INVOCANT> is a multi-numeric refenrece type.

Compilation Errors:

Compiliation errors caused by the syntax of the L<field access|SPVM::Document::Language::Class/"Field Access"> could occur.

Compiliation errors caused by the L<dereference operator|/"Dereference Operator"> could occur.

Examples:

  my $z : Complex_2d;
  my $z_ref = \$z;
  my $re = $z_ref->{re};

=head3 Setting a Referenced Multi-Numeric Field

The operation of setting a multi-numeric field sets the value of a field of a L<multi-numeric type|SPVM::Document::Language::Types/"Multi-Numeric Type"> referenced by a multi-numeric Reference Types.

This operation is expaned to the following code.

  ($INVOCANT)->{FIELD_NAME} = OPERAND

The type of I<INVOCANT> is a multi-numeric refenrece type.

Compilation Errors:

Compiliation errors caused by the syntax of the L<field access|SPVM::Document::Language::Class/"Field Access"> could occur.

Compiliation errors caused by the L<dereference operator|/"Dereference Operator"> could occur.

The assignment must satisfy the L<assignment requirement|SPVM::Document::Language::Types/"Assignment Requirement">, otherwise a compilation error occurs.

Examples:

  my $z : Complex_2d;
  my $z_ref = \$z;
  $z_ref->{re} = 2.5;

=head3 Getting a Referenced Value

The operation of getting the referenced value gets a referenced value.

See the L<dereference operator|/"Dereference Operator">.

=head3 Setting a Referenced Value

The operation of setting the referenced value sets a referenced value.

  $VARIABLE = OPERAND

Thie operation sets the value referenced by the reference I<VARIABLE> to I<OPERAND> using the L<assignment operator|/"Assignment Operator">, and returns the value after setting.

The return type is the type of the referenced value.

Compilation Errors:

The type of I<VARIABLE> must be a reference type, otherwise a compilation error occurs.

The assignment must satisfy the L<assignment requirement|SPVM::Document::Language::Types/"Assignment Requirement">, otherwise a compilation error occurs.

Examples:

  my $num : int;
  my $num_ref : int* = \$num;
  $$num_ref = 1;
  
  my $z : Complex_2d;
  my $z_ref : Complex_2d* = \$z;
  
  my $z2 : Complex_2d;
  
  $$z_ref = $z2;

=head3 Getting the Exception Variable

The operation of getting the exception variable gets the string stored in the L<exception variable|SPVM::Document::Language::ExceptionHandling/"Exception Variable">.

  $@

This operator returns the string stored in the exception variable.

The return type is the string type.

Examples:
  
  # Examples of getting the exception variable
  my $message = $@;

=head3 Setting the Exception Variable

The operation of setting the exception variable sets the L<exception variable|SPVM::Document::Language::ExceptionHandling/"Exception Variable">.

  $@ = OPERAND

This operator sets the exception variable to I<OPERAND> using the L<assignment operator|/"Assignment Operator">.

The return type is the string type.

Compilation Errors:

The assignment must satisfy the L<assignment requirement|SPVM::Document::Language::Types/"Assignment Requirement">, otherwise a compilation error occurs.

Examples:

  # Examples of setting the exception variable
  $@ = "Error";

=head2 Type Cast

A type cast performs a L<type conversion|SPVM::Document::Language::Types/"Type Conversions">.

  # A type cast
  (TYPE)OPERAND
  
  # A postfix type cast
  OPERAND->(TYPE)

A type cast performs the type conversion on I<OPERAND> from the type of the operand I<OPERAND> to the type I<TYPE>, and returns the value after the type conversion.

The return type is I<TYPE>.

Compilation Errors:

I<OPERAND> must satisfy the L<cast requirement|SPVM::Document::Language::Types/"Cast Requirement">, otherwise a compilation error occurs.

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

If the type I<TYPE> is a numeric type, a multi-numeric type, a reference type, the L<any object type|/"Any Object Type">, or the L<any object array type|SPVM::Document::Language::Types/"Any Object Array Type">, this operator checks the L<assignment requirement|SPVM::Document::Language::Types/"Assignment Requirement"> without implicite type convertion.

If the assignment requirement is satisfied, this operator returns 1, otherwise returns 0.

If I<TYPE> is an object type except for the L<any object type|/"Any Object Type">, or the L<any object array type|SPVM::Document::Language::Types/"Any Object Array Type">, this operator checks the L<assignment requirement|SPVM::Document::Language::Types/"Assignment Requirement"> without implicite conversion at runtime.

If the runtime assignment requirement is satisfied, this operator returns 1, otherwise returns 0.

The return type is the int type.

Compilation Errors:

If the runtime assignment requirement is checked, I<OPERAND> must be an object type, otherwise a compilation error occurs.

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

=head2 is_type Operator

The C<is_type> operator checks whether the type of an operand is equal to a type.

  OPERAND is_type TYPE

If the type I<TYPE> is a numeric type, a multi-numeric type, a reference type, the L<any object type|/"Any Object Type">, or the L<any object array type|SPVM::Document::Language::Types/"Any Object Array Type">, this operator checks the compilation type of I<OPERAND> is equal to I<TYPE>.

If it is true, this operator returns 1, otherwise returns 0.

If the type is an object type except for the L<any object type|/"Any Object Type">, or the L<any object array type|SPVM::Document::Language::Types/"Any Object Array Type">, this operator checks the runtime type of I<OPERAND> is equal to I<TYPE>.

If it is true, this operator returns 1, otherwise returns 0.

The return type is int type.

Compilation Errors:

If the runtime check is performed, I<OPERAND> must be an object type, otherwise a compilation error occurs.

Examples:

  if ($object is_type int) {
    
  }
  
  if ($object is_type Point) {
    
  }
  
  if ($object is_type int[]) {
    
  }
  
  if ($object is_type Stringable[]) {
    
  }

=head2 is_compile_type Operator

The C<is_compile_type> operator checks whether the compilation type of an operand is equal to a type.

  OPERAND is_compile_type TYPE

If the compilation type of I<OPERAND> is equal to the type I<TYPE>, returns 1, otherwise returns 0.

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

=head2 isa_error Operator

The C<isa_error> operator checks whether the type specified by a basic type ID can be assigned to a class type. This operator is normally used for error classes to check L<eval_error_id/"eval_error_id Operator">>.

  OPERAND isa_error TYPE

This operator performs the L<integer promotional conversion|SPVM::Document::Language::Types/"Integer Promotional Conversion"> on the operand I<OPERAND>.

And this operator checks whether the type specified by the basic type ID I<OPERAND> satisfies the L<assignment requirement|SPVM::Document::Language::Types/"Assignment Requirement"> without implicite conversion to the type I<TYPE>.

If it is satisfied, this operator returns 1, otherwise returns 0.

The return type is int type.

Compilation Errors:

I<OPERAND> must be an L<integer type|SPVM::Document::Language::Types/"Integer Types"> within int, otherwise a compilation error occurs.

I<TYPE> must be a class type, otherwise a compilation error occurs.

Examples:

  if (eval_error_id isa_error Error) {
    
  }
  
  if (eval_error_id isa_error Error::System) {
    
  }
  
=head2 is_error Operator

The C<is_error> operator checks whether the type specified by a basic type ID is equal to a class type. This operator is normally used for error classes to check L<eval_error_id/"eval_error_id Operator">>.

  OPERAND is_error TYPE

This operator performs the L<integer promotional conversion|SPVM::Document::Language::Types/"Integer Promotional Conversion"> on the operand I<OPERAND>.

And this operator checks whether the type specified by the basic type ID I<OPERAND> is equal to the type I<TYPE>.

If it is, this operator returns 1, otherwise returns 0.

The return type is int type.

Compilation Errors:

I<OPERAND> must be an L<integer type|SPVM::Document::Language::Types/"Integer Types"> within int, otherwise a compilation error occurs.

I<TYPE> must be a class type, otherwise a compilation error occurs.

Examples:

  if (eval_error_id is_error Error) {
    
  }
  
  if (eval_error_id is_error Error::System) {
    
  }

=head2 type_name Operator

The C<type_name> operator gets the type name of the object.

  type_name OPERAND

If the object I<OPERAND> is defined, creates a string with the type name of I<OPERAND> and returns it, otherwise returns an undefined value.

The return type is the string type.

Compilation Errors.

I<OPERAND> must be an object type, otherwise a compilation error occurs.

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

The return type is the string type.

Examples:
  
  # "Point"
  my $point = Point->new;
  my $type_name = type_name $point;
  
  # "object"
  my $point = (object)Point->new;
  my $type_name = type_name $point;

=head2 basic_type_id Operator

The C<basic_type_id> operator gets the basic type ID of a type.

  basic_type_id TYPE

This operator returns the basic type ID of the type I<TYPE>.

The return type is the int type.

Examples:

  my $basic_type_id = basic_type_id int;
  
  my $basic_type_id = basic_type_id int[];
  
  my $error_basic_type_id = basic_type_id Error;

=head2 Method Call

The method call syntax calls a L<method|SPVM::Document::Language::Class/"Method">.

=head3 Class Method Call

A method defined as the L<class method|/"Class Method"> can be called using the class method call.

  ClassName->MethodName(ARGS1, ARGS2, ...);
  
  &MethodName(ARGS1, ARGS2, ...);

C<&> means the current class.

If C<&> is used in anon method, it means its outmost class.

Compilation Errors:

If the number of arguments does not correct, a compilation error occurs.

If the types of arguments have no type compatible, a compilation error occurs.

Examples:
  
  class Foo {
    
    static method main : void () {
      
      my $result = Foo->bar(1, 2, 3);
      
      # Same as Foo->bar
      my $result = &bar(1, 2, 3);
      
      my $anon_method = method : void () {
        # Same as Foo->bar;
        my $result = &foo;
      };
    }
    
    static method foo : int () {
      return 5;
    }
  }

=head4 Getting an Enumeration Value

The operation of getting an enumeration value gets a value of an L<enumeration|SPVM::Document::Language::Class/"Enumeration">.

The definition of an enumeration value is replaced to a class method, so this operation is the same as a L<class method call|/"Class Method Call">.
  
  # Definition of an enumeration
  class MyClass {
    enum {
      VALUE1,
      VALUE2,
      VALUE3,
    }
  }
  
  # These are replaced to definitions of class methods
  class MyClass {
    static method VALUE1 : int () { return 0; }
    static method VALUE2 : int () { return 1; }
    static method VALUE3 : int () { return 2; }
  }

However, there is one important difference.

The class method calls are replaced to L<interger literals|SPVM::Document::Language::Tokenization/"Integer Literal"> at compilation time.

For this replacement, this operation is used as an operand of the L<case statement|SPVM::Document::Language::Statements/"case Statement">.

  switch ($num) {
    case MyClass->VALUE1: {
      # ...
    }
    case MyClass->VALUE2: {
      # ...
    }
    case MyClass->VALUE3: {
      # ...
    }
    default: {
      # ...
    }
  }

Note that if an enumeration value is changed, the binary compatibility is broken.

=head3 Instance Method Call

A method defined as the instance method can be called using the instance method call.

  Instance->MethodName(ARGS1, ARGS2, ...);

The called method is resolved from the type of the instance.

Compilation Errors:

If the number of arguments does not correct, a compilation error occurs.

If the types of arguments have no type compatible, a compilation error occurs.

Examples:

  $object->bar(5, 3. 6);

The C<SUPER::> qualifier calls the method of the super class of the current class.

  $object->SUPER::bar(5, 3. 6);

A instance method can be called statically by specifing the calss name.

  $point3d->Point::clear;

=head2 can Operator

The C<can> operator checks if a method can be called. 

  OPERAND can METHOD_NAME

An empty string C<""> means an L<anon method|/"Anon Method">.

If I<OPERAND> can call the method given by METHOD_NAME, returns 1, otherwise returns 0.

The return type is int type.

Compilation Errors:

The type of I<OPERAND> must be the class type or the L<interface type|SPVM::Document::Language::Types/"Interface Type">, otherwise a compilation error occurs.

The METHOD_NAME must be a method name or an empty string C<"">, otherwise a compilation error occurs.

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

I<INVOCANT-E<gt>{FIELD_NAME}> is a L<field access|SPVM::Document::Language::Class/"Field Access">.

This operator enable a weak reference of the field specified by I<FIELD_NAME> of the type of I<INVOCANT>.

The return type is the void type.

Compilation Errors:

Compiliation errors caused by the syntax of the L<field access|SPVM::Document::Language::Class/"Field Access"> could occur.

The type of I<INVOCANT-E<gt>{FIELD_NAME}> must be an object type, otherwise a compilation error occurs.

Examples:

  # Exmaples of the weaken operator
  weaken $object->{point};

=head2 unweaken Operator

The C<unweaken> operator disables a L<weak reference|SPVM::Document::Language::GarbageCollection/"Weak Reference">.

  unweaken INVOCANT->{FIELD_NAME};

I<INVOCANT-E<gt>{FIELD_NAME}> is a L<field access|SPVM::Document::Language::Class/"Field Access">.

This operator enable a weak reference of the field specified by I<FIELD_NAME> of the type of I<INVOCANT>.

The return type is the void type.

Compilation Errors:

Compiliation errors caused by the syntax of the L<field access|SPVM::Document::Language::Class/"Field Access"> could occur.

The type of I<INVOCANT-E<gt>{FIELD_NAME}> must be an object type, otherwise a compilation error occurs.

Examples:

  # Exmaples of the unweaken operator
  unweaken $object->{point};

=head2 isweak Operator

The C<isweak> operator checks if the L<weak reference|SPVM::Document::Language::GarbageCollection/"Weak Reference"> of a field is enabled.

  isweak INVOCANT->{FIELD_NAME};

I<INVOCANT-E<gt>{FIELD_NAME}> is a L<field access|SPVM::Document::Language::Class/"Field Access">.

If the field specified by I<FIELD_NAME> of the object I<INVOCANT> is weaken, this operator returns 1, otherwise returns 0.

The return type is the int type.

Compilation Errors:

Compiliation errors caused by the syntax of the L<field access|SPVM::Document::Language::Class/"Field Access"> could occur.

The type of I<INVOCANT-E<gt>{FIELD_NAME}> must be an object type, otherwise a compilation error occurs.

Examples:

  # Exmaples of the isweak operator
  my $isweak = isweak $object->{point};

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

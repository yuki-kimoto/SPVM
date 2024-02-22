=encoding utf8

=head1 Name

SPVM::Document::Language::Operators - Operators in SPVM Language

=head1 Description

This document describes operators in SPVM language.

=head1 Operators

=head2 Unary Plus Operator

The unary plus operator C<+> returns I<OPERAND>.

  +OPERAND

Before this operation, the L<integer promotional conversion|SPVM::Document::Language::Types/"Integer Promotional Conversion"> is performed on I<OPERAND>.

The return type is the type after the L<integer promotional conversion|SPVM::Document::Language::Types/"Integer Promotional Conversion"> has been performed.

Compilation Errors:

The type of I<OPERAND> must be a numeric type. Otherwise a compilation error occurs.

Examples:
  
  # The unary plus operator
  my $num = +10;

=head2 Unary Minus Operator

  -OPERAND

The unary minus operator C<-> returns the negative value of I<OPERAND>.

Before this operation, the L<integer promotional conversion|SPVM::Document::Language::Types/"Integer Promotional Conversion"> is performed on I<OPERAND>.

The return type is the type after the L<integer promotional conversion|SPVM::Document::Language::Types/"Integer Promotional Conversion"> has been performed.

Compilation Errors:

The type of I<OPERAND> must be a numeric type. Otherwise a compilation error occurs.

Examples:

  # A unary minus operator
  my $num = -10;

=head2 Addition Operator

The addition operator C<+> calculates the addition of I<LEFT_OPERAND> and I<RIGHT_OPERAND>.

  LEFT_OPERAND + RIGHT_OPERAND

The addition operator performs the same operation as the following C language operation.

  LEFT_OPERAND + RIGHT_OPERAND

Before this operation, The L<binary numeric conversion|SPVM::Document::Language::Types/"Binary Numeric Conversion"> is performed on I<LEFT_OPERAND> and I<RIGHT_OPERAND>.

The return type is the type after the L<binary numeric conversion|SPVM::Document::Language::Types/"Binary Numeric Conversion"> has been performed.

Compilation Errors:

The type of I<LEFT_OPERAND> must be a numeric type. Otherwise a compilation error occurs.

The type of I<RIGHT_OPERAND> must be a numeric type. Otherwise a compilation error occurs.

=head2 Subtraction Operator

The subtraction operator C<-> calculates the subtraction of I<LEFT_OPERAND> and I<RIGHT_OPERAND>.

  LEFT_OPERAND - RIGHT_OPERAND

The subtraction operator performs the same operation as the following C language operation.

  LEFT_OPERAND - RIGHT_OPERAND

Before this operation, The L<binary numeric conversion|SPVM::Document::Language::Types/"Binary Numeric Conversion"> is performed on I<LEFT_OPERAND> and I<RIGHT_OPERAND>.

The return type is the type after the L<binary numeric conversion|SPVM::Document::Language::Types/"Binary Numeric Conversion"> has been performed.

Compilation Errors:

The type of I<LEFT_OPERAND> must be a numeric type. Otherwise a compilation error occurs.

The type of I<RIGHT_OPERAND> must be a numeric type. Otherwise a compilation error occurs.

=head2 Multiplication Operator

The multiplication operator C<*> calculates the multiplication of I<LEFT_OPERAND> and I<RIGHT_OPERAND>.

  LEFT_OPERAND * RIGHT_OPERAND

Before this operation, The L<binary numeric conversion|SPVM::Document::Language::Types/"Binary Numeric Conversion"> is performed on I<LEFT_OPERAND> and I<RIGHT_OPERAND>.

The multiplication operator performs the same operation as the following C language operation.

  LEFT_OPERAND * RIGHT_OPERAND;

The return type is the type after the L<binary numeric conversion|SPVM::Document::Language::Types/"Binary Numeric Conversion"> has been performed.

Compilation Errors:

The type of I<LEFT_OPERAND> must be a numeric type. Otherwise a compilation error occurs.

The type of I<RIGHT_OPERAND> must be a numeric type. Otherwise a compilation error occurs.

=head2 Division Operator

The division operator C</> calculates the division of I<LEFT_OPERAND> and I<RIGHT_OPERAND>.

  LEFT_OPERAND / RIGHT_OPERAND

Before this operation, The L<binary numeric conversion|SPVM::Document::Language::Types/"Binary Numeric Conversion"> is performed on I<LEFT_OPERAND> and I<RIGHT_OPERAND>.

The division operator performs the same operation as the following C language operation.

  LEFT_OPERAND / RIGHT_OPERAND;

The return type is the type after the L<binary numeric conversion|SPVM::Document::Language::Types/"Binary Numeric Conversion"> has been performed.

Compilation Errors:

The type of I<LEFT_OPERAND> must be a numeric type. Otherwise a compilation error occurs.

The type of I<RIGHT_OPERAND> must be a numeric type. Otherwise a compilation error occurs.

Exceptions:

If I<LEFT_OPERAND> and I<RIGHT_OPERAND> are an integer type and I<RIGHT_OPERAND> is 0, an exception is thrown.

=head2 Division Unsigned Int Operator

The division unsigned int operator C<div_uint> calculates the unsigned int division of I<LEFT_OPERAND> and I<RIGHT_OPERAND>.

  LEFT_OPERAND div_uint RIGHT_OPERAND

The division unsigned int operator performs the same operation as the following C language operation.

  (uint32_t)LEFT_OPERAND / (uint32_t)RIGHT_OPERAND;

The return type is the int type.

Compilation Errors:

The type of I<LEFT_OPERAND> must be a numeric type. Otherwise a compilation error occurs.

The type of I<RIGHT_OPERAND> must be a numeric type. Otherwise a compilation error occurs.

Exceptions:

If I<RIGHT_OPERAND> is 0, an exception is thrown.

=head2 Division Unsigned Long Operator

The division unsigned long operator C<div_ulong> calculates the unsigned long division of I<LEFT_OPERAND> and I<RIGHT_OPERAND>.

  LEFT_OPERAND div_ulong RIGHT_OPERAND

The division unsigned long operator performs the same operation as the following C language operation.

  (uint64_t)LEFT_OPERAND / (uint64_t)RIGHT_OPERAND;

The return type of the division operator is the long type.

Compilation Errors:

The type of I<LEFT_OPERAND> must be the long type. Otherwise a compilation error occurs.

The type of I<RIGHT_OPERAND> must be the long type. Otherwise a compilation error occurs.

Exceptions:

If I<RIGHT_OPERAND> is 0, an exception is thrown.

=head2 Modulo Operator

The modulo operator C<%> is calculates a modulo of I<LEFT_OPERAND> and I<RIGHT_OPERAND>.

  LEFT_OPERAND % RIGHT_OPERAND

Before this operation, the L<binary numeric conversion|SPVM::Document::Language::Types/"Binary Numeric Conversion"> is performed on I<LEFT_OPERAND> and I<RIGHT_OPERAND>.

The modulo operator performs the same operation as the following C language operation.

  RETURN_VALUE = LEFT_OPERAND % RIGHT_OPERAND;
  if ((LEFT_OPERAND < 0) != (RIGHT_OPERAND < 0) && RETURN_VALUE) { RETURN_VALUE += RIGHT_OPERAND; }

The return type is the type after the L<binary numeric conversion|SPVM::Document::Language::Types/"Binary Numeric Conversion"> has been performed.

Compilation Errors:

The type of I<LEFT_OPERAND> must be an integer type. Otherwise a compilation error occurs.

The type of I<RIGHT_OPERAND> must be an integer type. Otherwise a compilation error occurs.

Exceptions:

If I<RIGHT_OPERAND> is 0, an exception is thrown.

=head2 Modulo Unsigned Int Operator

The modulo unsigned int operator C<mod_uint> calculates a unsigned int modulo of I<LEFT_OPERAND> and I<RIGHT_OPERAND>.

  LEFT_OPERAND mod_uint RIGHT_OPERAND

The modulo unsigned int operator performs the same operation as the following C language operation.

  (uint32_t)LEFT_OPERAND % (uint32_t)RIGHT_OPERAND;

The return type is the int type.

Compilation Errors:

The type of I<LEFT_OPERAND> must be the int type. Otherwise a compilation error occurs.

The type of I<RIGHT_OPERAND> must be the int type. Otherwise a compilation error occurs.

Exceptions:

If I<RIGHT_OPERAND> is 0, an exception is thrown.

=head2 Modulo Unsigned Long Operator

The modulo unsigned long operator C<mod_ulong> calculates a unsigned long modulo of I<LEFT_OPERAND> and I<RIGHT_OPERAND>.

  LEFT_OPERAND mod_ulong RIGHT_OPERAND

The modulo unsigned long operator performs the same operation as the following C language operation.

  (uint64_t)LEFT_OPERAND % (uint64_t)RIGHT_OPERAND;

The return type of the modulo unsigned long operator is the long type.

Compilation Errors:

The type of I<LEFT_OPERAND> must be the long type. Otherwise a compilation error occurs.

The type of I<RIGHT_OPERAND> must be the long type. Otherwise a compilation error occurs.

Exceptions:

If I<RIGHT_OPERAND> is 0, an exception is thrown.

=head2 Increment Operator

Increment operators are the L<pre-increment operator|/"Pre-Increment Operator"> and L<post-increment operator|/"Post-Increment Operator">.

=head3 Pre-Increment Operator

The pre-increment operator adds 1 to I<OPERAND> and returns the value after the incrementation.
  
  # Pre-increment operator
  ++OPERAND

The pre-increment operator performs the same operation as the following.

  (OPERAND = (TYPE_OF_OPERAND)(OPERAND + 1))

For example, if the type of I<OPERAND> is the L<byte type|/"byte Type">, the following operation is performed.

  ($num = (byte)($num + 1))

Compilation Errors:

The type of I<OPERAND> must be a local variable, a L<class variable|/"Class Variable">, a L<field access|/"Field Access"></a>, an L<array access|/"The array Access">, a L<dereference|/"Dereference">. Otherwise a compilation error occurs.

Examples:
  
  # Pre-increment of a local variable
  ++$num;
  
  # Pre-increment of a class variable
  ++$NUM;
  
  # Pre-increment of an element of an array
  ++$point->{x};
  
  # Pre-increment of a field
  ++$nums->[0];
  
  # Pre-increment of a dereferenced value
  ++$$num_ref;

=head3 Post-Increment Operator

The post-increment operator adds 1 to I<OPERAND> and returns the value before the incrementation.
  
  # Post-increment operator
  OPERAND++

The post-increment operator performs the same operation as the following.

  (my TMP_VARIABLE = OPERAND, OPERAND = (TYPE_OF_OPERAND)(OPERAND + 1), TMP_VARIABLE)

For example, if the type of I<OPERAND> is the L<byte type|/"byte Type">, the following operation is performed.

  (my $tmp = $num, $num = (byte)($num + 1), $tmp)

Compilation Errors:

The type of I<OPERAND> must be a local variable, a L<class variable|/"Class Variable">, a L<field access|/"Field Access"></a>, an L<array access|/"The array Access">, a L<dereference|/"Dereference">. Otherwise a compilation error occurs.

Examples:
  
  # Post-increment of a local variable
  $num++;
  
  # Post-increment of a class variable
  $NUM++;
  
  # Post-increment of an element of an array
  $point->{x}++;
  
  # Post-increment of a field
  $nums->[0]++;
  
  # Post-increment of a dereferenced value
  $$num_ref++;

=head2 Decrement Operator

Decrement operators are the L<pre-decrement operator|/"Pre-Decrement Operator"> and L<post-decrement operator|/"Post-Decrement Operator">.

=head3 Pre-Decrement Operator

The pre-decrement operator subtracts 1 to I<OPERAND> and returns the value after the decrementation.
  
  # Pre-decrement operator
  --OPERAND

The pre-decrement operator performs the same operation as the following.

  (OPERAND = (TYPE_OF_OPERAND)(OPERAND - 1))

For example, if the type of I<OPERAND> is the L<byte type|/"byte Type">, the following operation is performed.

  ($num = (byte)($num - 1))

Complation Errors:

The type of I<OPERAND> must be a local variable, a L<class variable|/"Class Variable">, a L<field access|/"Field Access">, an L<array access|/"The array Access">, a L<dereference|/"Dereference">. Otherwise a compilation error occurs.

Examples:
  
  # Pre-decrement of a local variable
  --$num;
  
  # Pre-decrement of a class variable
  --$NUM;
  
  # Pre-decrement of an element of an array
  --$point->{x};
  
  # Pre-decrement of a field
  --$nums->[0];
  
  # Pre-decrement of a dereferenced value
  --$$num_ref;

=head3 Post-Decrement Operator

The post-decrement operator subtracts 1 to I<OPERAND> and returns the value before the decrementation.
  
  # Post-decrement operator
  OPERAND--

The post-decrement operator performs the same operation as the following.

  (my TMP_VARIABLE = OPERAND, OPERAND = (TYPE_OF_OPERAND)(OPERAND - 1), TMP_VARIABLE)

For example, if the type of I<OPERAND> is the L<byte type|/"byte Type">, the following operation is performed.

  (my $tmp = $num, $num = (byte)($num - 1), $tmp)

Compilation Errors:

The type of I<OPERAND> must be a local variable, a L<class variable|/"Class Variable">, a L<field access|/"Field Access"></a>, an L<array access|/"The array Access">, a L<dereference|/"Dereference">. Otherwise a compilation error occurs.

Examples:
  
  # Post-decrement of a local variable
  $num--;
  
  # Post-decrement of a class variable
  $NUM--;
  
  # Post-decrement of an element of an array
  $point->{x}--;
  
  # Post-decrement of a field
  $nums->[0]--;
  
  # Post-decrement of a dereferenced value
  $$num_ref--;

=head2 Bit Operator

Bit operators perform bit operations.

=head3 Bit AND Operator

The bit AND operator C<&> performes a bit AND operation.

  LEFT_OPERAND & RIGHT_OPERAND

Before this operation, the L<binary numeric conversion|SPVM::Document::Language::Types/"Binary Numeric Conversion"> is performed.

The return value is the same as the follwoing operation of the C language.

  LEFT_OPERAND & RIGHT_OPERAND;

The return type is the type after the L<binary numeric widening conversion|/"Binary Numeric Widening Type"> is performed.

Compilation Errors:

I<LEFT_OPERAND> and I<RIGHT_OPERAND> must be an L<integer type/"Integer Type">. Otherwise a compilation error occurs.

Examples:
  
  # The bit AND operator
  my $num1 = 0xff;
  my $num2 = 0x12;
  my $result = $num1 & $num2;
  
=head3 Bit OR Operator

The bit OR operator C<|> performes a bit OR operation.

  LEFT_OPERAND | RIGHT_OPERAND

Before this operation, the L<binary numeric conversion|SPVM::Document::Language::Types/"Binary Numeric Conversion"> is performed.

The return value is the same as the follwoing operation of the C language.

  LEFT_OPERAND | RIGHT_OPERAND;

The return type is the type after the L<binary numeric widening conversion|/"Binary Numeric Widening Type"> is performed.

Compilation Errors:

I<LEFT_OPERAND> and I<RIGHT_OPERAND> must be an L<integer type/"Integer Type">. Otherwise a compilation error occurs.

Examples:
  
  # The bit OR operator
  my $num1 = 0xff;
  my $num2 = 0x12;
  my $result = $num1 | $num2;

=head3 Bit NOT Operator

The bit NOT operator C<~> performs the bit NOT operation.

  ~OPERAND

The L<numeric widening conversion|/"Numeric Widening Conversion"> is performed.

The return value is the same as the follwoing operation of the C language.

  ~OPERAND

The return type is the type that the L<numeric widening conversion|/"Numeric Widening Conversion"> is performed.

Compilation Errors:

The type of I<OPERAND> must is an integer type. Otherwise a compilation error occurs.

Examples:
  
  # The bit NOT operator
  my $num = ~0xFF0A;

=head2 Shift Operator

Shift operators perform bit shift operations.

=head3 Left Shift Operator

The left shift operator C<E<lt>E<lt>> performs the left bit shift.

  LEFT_OPERAND << RIGHT_OPERAND

Before this operation, the L<numeric widening conversion|SPVM::Document::Language::Types/"Numeric Widening Conversion"> is performed on I<LEFT_OPERAND>.

Before this operation, the L<numeric widening conversion|SPVM::Document::Language::Types/"Numeric Widening Conversion"> is performed on I<RIGHT_OPERAND>.

The left shift operator performs the same operation as the following C language operation.

  LEFT_OPERAND << RIGHT_OPERAND;

The return type is the same as the type of I<LEFT_OPERAND>.

Compilation Erorrs:

The type of I<LEFT_OPERAND> must be an integer type. Otherwise a compilation error occurs.

The type of I<RIGHT_OPERAND> must be an integer type within int. Otherwise a compilation error occurs.

=head3 Arithmetic Right Shift Operator

The arithmetic right shift operator C<E<gt>E<gt>> performs the arithmetic right bit shift.

  LEFT_OPERAND >> RIGHT_OPERAND

Before this operation, the L<numeric widening conversion|SPVM::Document::Language::Types/"Numeric Widening Conversion"> is performed on I<LEFT_OPERAND>.

Before this operation, the L<numeric widening conversion|SPVM::Document::Language::Types/"Numeric Widening Conversion"> is performed on I<RIGHT_OPERAND>.

The operation result of the arithmetic right shift Operator is the operation that exactly same as the following operation in the C language.

  LEFT_OPERAND >> RIGHT_OPERNAD;

The return type is the same as the type of I<LEFT_OPERAND>.

Compilation Errors:

The type of I<LEFT_OPERAND> must be an integer type. Otherwise a compilation error occurs.

The type of I<RIGHT_OPERAND> must be an integer type within int. Otherwise a compilation error occurs.

=head3 Logical Right Shift Operator

The logical right shift operator C<E<gt>E<gt>E<gt>> performs the logical right bit shift.

  LEFT_OPERAND >>> RIGHT_OPERAND

Before this operation, the L<numeric widening conversion|SPVM::Document::Language::Types/"Numeric Widening Conversion"> is performed on I<LEFT_OPERAND>.

Before this operation, the L<numeric widening conversion|SPVM::Document::Language::Types/"Numeric Widening Conversion"> is performed on I<RIGHT_OPERAND>.

The operation result of logical right shift Operator is the same as the following calculation in the C language.
  
  // The type of LEFT_OPERAND is the int type
  (uint32_t)LEFT_OPERAND >> RIGHT_OPERAND;

  // The type of LEFT_OPERAND is the long type
  (uint64_t)LEFT_OPERAND >> RIGHT_OPERAND;

The return type is the same as the type of I<LEFT_OPERAND>.

Compilation Errors:

The type of I<LEFT_OPERAND> must be an integer type. Otherwise a compilation error occurs.

The type of I<RIGHT_OPERAND> must be an integer type within int. Otherwise a compilation error occurs.

=head2 Logical Operator

The logical operators performs logical operations.

=head3 Logical AND Operator

The logical AND operator C<&&> performs a logical AND operation.

  LEFT_OPERAND && RIGHT_OPERAND
  
The return type of the logical AND operator is the int type.

Thg logical AND operator performs the L<boolean conversion|SPVM::Document::Language::Types/"Boolean Conversion"> to I<LEFT_OPERAND>. If the evaluated value is 0, returns 0. Otherwise proceed to the evaluation of I<RIGHT_OPERAND>.

It performs the L<boolean conversion|SPVM::Document::Language::Types/"Boolean Conversion"> to I<RIGHT_OPERAND>. If the evaluated value is 0, returns 0. Otherwise return the evaluated value.

=head3 Logical OR Operator

The logical OR operator C<||> performes a logical OR operation.

  LEFT_OPERAND || RIGHT_OPERAND

The return type of the logical OR operator is the int type.

Thg logical OR operator performs the L<boolean conversion|SPVM::Document::Language::Types/"Boolean Conversion"> to I<LEFT_OPERAND>. If the evaluated value is not 0, return the evaluated value. Otherwise proceed to the evaluation of I<RIGHT_OPERAND>.

It performs the L<boolean conversion|SPVM::Document::Language::Types/"Boolean Conversion"> to I<RIGHT_OPERAND>. If the evaluated value is not 0, return the evaluated value. Otherwise returns 0.

=head3 Logical NOT Operator

The logical NOT operator C<!> performes a logical NOT operation.

  !OPERAND

The return type of the logical NOT operator is the int type.

Thg logical NOT operator performs the L<boolean conversion|SPVM::Document::Language::Types/"Boolean Conversion"> to I<OPERAND>. If the evaluated value is 0, returns 1. Otherwise returns 0.

=head2 String Concatenation Operator

String concatenation operator C<.> concats two strings.

  LEFT_OPERAND . RIGHT_OPERAND

If the type of I<OPERAND> is numeric type, a L<numeric-to-string conversion|SPVM::Document::Language::Types/"Numeric-to-String Conversion"> is performed.

The return type is the string type.

A string concatenation operator returns the result to concat two operands.

If both I<LEFT_OPERAND> and I<RIGHT_OPERAND> are a L<string literal|/"String Literal">, the two string literals are concatenated at compile-time.

If I<LEFT_OPERAND> or I<RIGHT_OPERAND> is L<undef|/"Undefined Value">, an exception occurs.

Compilation Errors:

I<LEFT_OPERAND> and I<RIGHT_OPERAND> must be the string type, the byte[] type, or numeric type. Otherwise a compilation error occurs.

Examples:

  my $str = "abc" . "def";
  my $str = "def" . 34;
  my $str = 123 . 456;

=head2 Array Length Operator

The array length operator gets the length of the array.

  @OPERAND

The array length operator returns the int type value that is the length of the L<array|SPVM::Document::Language::Types/"Array">.

Array Length Operator returns the L<operator|/"Operators">

Compilation Errors:

The type of the operand must be an array type. Otherwise a compilation error occurs.

Examples:
  
  # Getting the length of the array.
  my $nums = new byte[10];
  my $length = @$nums;
  
  # Getting the length of the array with a scalar operator. This is exactly same as the avobe
  my $nums = new byte[10];
  my $length = scalar @$nums;

Note that SPVM does not have the context different from Perl, and array length operators always return the length of the array.

=head2 Sequential Operator

The sequential operator evaluates operands from left to right, and returns the value of the rightmost operand.

  (OPERAND1, OPERAND2, ..., OPERNADN)

B<Exampless:>

  # 3 is assigned to $foo
  my $foo = (1, 2, 3);
  
  # $x is 3, $ret is 5
  my $x = 1;
  my $y = 2;
  my $ret = ($x += 2, $x + $y);

=head2 Assignment Operator

The assignment operator C<=> assigns a value.

  LEFT_OPERAND = RIGHTH_OPERAND

The assignment operator has different meanings depending on I<LEFT_OPERAND> and I<RIGHT_OPERAND>.

=head3 Local Variable Assignment

See L</"Setting Local Variable">.

=head3 Class Variable Assignment

See L</"Setting Class Variable">.

=head3 Array Element Assignment

See L</"Setting Array Element">.

=head3 Field Assignment

See L</"Setting Field">.

=head2 Special Assignment Operator

A special assignment operator is the alias for the combination of an operator I<OPERATOR> and L</"Assignment Operator"> C<=>.

  LEFT_OPERAND OPERATOR= RIGHTH_OPERAND

Above is the alias for the following code.

  LEFT_OPERAND = (TYPE_OF_LEFT_OPERAND)(LEFT_OPERAND OPERATOR RIGHTH_OPERAND)

For example, See a C<byte> case.

  # Addition assignment operator
  $x += 1;
  
  # Above is the same as the following code.
  $x = (byte)($x + 1)

The following operators are used as the operators of the special assignment operators.

=begin html

<table>
  <tr>
    <td>Addition assignment operator</td>
    <td>+=</td>
  </tr>
  <tr>
    <td>Subtraction assignment operator</td>
    <td>-=</td>
  </tr>
  <tr>
    <td>Multiplication assignment operator</td>
    <td>*=</td>
  </tr>
  <tr>
    <td>Division assignment operator</td>
    <td>/=</td>
  </tr>
  <tr>
    <td>Modulo assignment operator</td>
    <td>%=</td>
  </tr>
  <tr>
    <td>Bit AND assignment operator</td>
    <td>&=</td>
  </tr>
  <tr>
    <td>Bit OR assignment operator</td>
    <td>|=</td>
  </tr>
  <tr>
    <td>Left shift assignment operator</td>
    <td><<=</td>
  </tr>
  <tr>
    <td>Arithmetic right shift assignment operator</td>
    <td>>>=</td>
  </tr>
  <tr>
    <td>Logical right shift assignment operator</td>
    <td>>>>=</td>
  </tr>
  <tr>
    <td>Concatenation assignment operator</td>
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

=head2 Comparison Operator

Comparison operators compare I<LEFT_OPERAND> and I<RIGHT_OPERAND>.

=head3 Numeric Comparison Operator

Numeric comparison operators compare I<LEFT_OPERAND> and I<RIGHT_OPERAND> in the numeric order.

  LEFT_OPERAND == RIGHT_OPERAND
  LEFT_OPERAND != RIGHT_OPERAND
  LEFT_OPERAND > RIGHT_OPERAND
  LEFT_OPERAND >= RIGHT_OPERAND
  LEFT_OPERAND < RIGHT_OPERAND
  LEFT_OPERAND <= RIGHT_OPERAND
  LEFT_OPERAND <=> RIGHT_OPERAND

=begin html

<table>
  <tr>
    <th>Operator</th>
    <th>Description</th>
  </tr>
  <tr>
    <td>
      <i>==</i>
    </td>
    <td>
      If <i>LEFT_OPERAND</i> is equal to <i>RIGHT_OPERNAD</i> in the numeric order, returns 1, otherwise returns 0. The comparation of operands of object types and reference types are also available.
    </td>
  </tr>
  <tr>
    <td>
      <i>!=</i>
    </td>
    <td>
      If <i>LEFT_OPERAND</i> is not equal to <i>RIGHT_OPERNAD</i> in the numeric order, returns 1, otherwise returns 0. The comparation of operands of object types and reference types are also available.
    </td>
  </tr>
  <tr>
    <td>
      <i>></i>
    </td>
    <td>
      If <i>LEFT_OPERAND</i> is greater than <i>RIGHT_OPERNAD</i> in the numeric order, returns 1, otherwise returns 0.
    </td>
  </tr>
  <tr>
    <td>
      <i>>=</i>
    </td>
    <td>
      If <i>LEFT_OPERAN</i> is greater than or equal to <i>RIGHT_OPERNAD</i> in the numeric order, returns 1, otherwise returns 0.
    </td>
  </tr>
  <tr>
    <td>
      <i><</i>
    </td>
    <td>
      If <i>LEFT_OPERAND</i> is less than <i>RIGHT_OPERNAD</i> in the numeric order, returns 1, otherwise returns 0.
    </td>
  </tr>
  <tr>
    <td>
      <i><=</i>
    </td>
    <td>
      If <i>LEFT_OPERAND</i> is less than or equal to <i>RIGHT_OPERNAD</i> in the numeric order, returns 1, otherwise returns 0.
    </td>
  </tr>
  <tr>
    <td>
      <i><=></i>
    </td>
    <td>
      If <i>LEFT_OPERAND</i> is greater than <i>RIGHT_OPERNAD</i> in the numeric order, returns 1. If <i>LEFT_OPERAND</i> is less than <i>RIGHT_OPERNAD</i> in the numeric order, return -1. If <i>LEFT_OPERAND</i> is equals to <i>RIGHT_OPERNAD</i> in the numeric order, returns 0.
    </td>
  </tr>
</table>

=end html

Before this operation, the L<binary numeric conversion|SPVM::Document::Language::Types/"Binary Numeric Conversion"> is performed on I<LEFT_OPERAND> and I<RIGHT_OPERAND>.

The numeric comparison operators performed the same operations as the following C language operations.

  (int32_t)(LEFT_OPERAND == RIGHT_OPERAND);
  (int32_t)(LEFT_OPERAND != RIGHT_OPERAND);
  (int32_t)(LEFT_OPERAND > RIGHT_OPERAND);
  (int32_t)(LEFT_OPERAND >= RIGHT_OPERAND);
  (int32_t)(LEFT_OPERAND < RIGHT_OPERAND);
  (int32_t)(LEFT_OPERAND <= RIGHT_OPERAND);
  (int32_t)(LEFT_OPERAND > RIGHT_OPERAND ? 1 : LEFT_OPERAND < RIGHT_OPERAND ? -1 : 0);

The return type is the int type.

Compilation Errors:

The type of I<LEFT_OPERAND> of the C<==> operator and the C<!=> operator must be a numeric type, an object type, or an reference type. Otherwise a compilation error occurs.

The type of I<RIGHT_OPERAND> of the C<==> operator and the C<!=> operator must be a numeric type, an object type, or an reference type. Otherwise a compilation error occurs.

If the type of I<RIGHT_OPERAND> of the C<==> operator and the C<!=> operator is an object type or an reference type, and the type of I<LEFT_OPERAND> is different from the type of I<RIGHT_OPERAND>, a compilation error occurs.

The type of I<LEFT_OPERAND> of the C<E<gt>> operator, the C<E<gt>=> operator, the C<E<lt>> operator, the C<E<lt>=> operator, and the C<E<lt>=E<gt>> operator must be a numeric type. Otherwise a compilation error occurs.

The type of I<RIGHT_OPERAND> of the C<E<gt>> operator, the C<E<gt>=> operator, the C<E<lt>> operator, the C<E<lt>=> operator, and the C<E<lt>=E<gt>> operator must be a numeric type. Otherwise a compilation error occurs.

=head3 String Comparison Operator

String comparison operators compare I<LEFT_OPERAND> and I<RIGHT_OPERAND> in the dictionary order.

  LEFT_OPERAND eq RIGHT_OPERAND
  LEFT_OPERAND ne RIGHT_OPERAND
  LEFT_OPERAND gt RIGHT_OPERAND
  LEFT_OPERAND ge RIGHT_OPERAND
  LEFT_OPERAND lt RIGHT_OPERAND
  LEFT_OPERAND le RIGHT_OPERAND
  LEFT_OPERAND cmp RIGHT_OPERAND

=begin html

<table>
  <tr>
    <th>Operators</th>
    <th>Descriptions</th>
  </tr>
  <tr>
    <td>
      <i>eq</i>
    </td>
    <td>
      If <i>LEFT_OPERAND</i> is equal to <i>RIGHT_OPERNAD</i> in the dictionary order, returns 1, otherwise returns 0.
    </td>
  </tr>
  <tr>
    <td>
      <i>ne</i>
    </td>
    <td>
      If <i>LEFT_OPERAND</i> is not equal to <i>RIGHT_OPERNAD</i> in the dictionary order, returns 1, otherwise returns 0.
    </td>
  </tr>
  <tr>
    <td>
      <i>gt</i>
    </td>
    <td>
      If <i>LEFT_OPERAND</i> is greater than <i>RIGHT_OPERNAD</i> in the dictionary order, returns 1, otherwise returns 0.
    </td>
  </tr>
  <tr>
    <td>
      <i>ge</i>
    </td>
    <td>
      If <i>LEFT_OPERAND</i> is greater than or equal to <i>RIGHT_OPERNAD</i> in the dictionary order, returns 1, otherwise returns 0.
    </td>
  </tr>
  <tr>
    <td>
      <i>lt</i>
    </td>
    <td>
      If <i>LEFT_OPERAND</i> is less than <i>RIGHT_OPERNAD</i> in the dictionary order, returns 1, otherwise returns 0.
    </td>
  </tr>
  <tr>
    <td>
      <i>le</i>
    </td>
    <td>
      If <i>LEFT_OPERAND</i> is less than or equal to <i>RIGHT_OPERNAD</i> in the dictionary order, returns 1, otherwise returns 0.
    </td>
  </tr>
  <tr>
    <td>
      <i>cmp</i>
    </td>
    <td>
      If <i>LEFT_OPERAND</i> is greater than <i>RIGHT_OPERNAD</i> in the dictionary order, returns 1. If <i>LEFT_OPERAND</i> is less than <i>RIGHT_OPERNAD</i> in the dictionary order, return -1. If <i>LEFT_OPERAND</i> is equal to <i>RIGHT_OPERNAD</i> in the dictionary order, returns 0.
    </td>
  </tr>
</table>

=end html

The return type is the int type. 

Compilation Errors.

The type of I<LEFT_OPERAND> must be the string type or the byte[] type. Otherwise a compilation error occurs.

The type of I<RIGHT_OPERAND> must be the string type or the byte[] type. Otherwise a compilation error occurs.

=head2 isa Operator

The C<isa> operator checks whether I<LEFT_OPERAND> can be assigned to the right type.

  LEFT_OPERAND isa RIGHT_TYPE

If the right type is a numeric type, a multi-numeric type, a reference type, the L<any object type|/"Any Object Type">, the L<any object array type|/"Any Object Array Type">, this operator checks the L<type assignability|SPVM::Document::Language::Types/"Type Assignability">.

If the assignability without implicite convertion is true, it returns 1, otherwise returns 0.

If the right type is another object type, this operator checks the L<runtime assignability|/"Runtime Type Assignability">.

If the runtime assignability is true, it returns 1, otherwise returns 0.

The return type is the int type.

Compilation Errors:

If the runtime assignability is checked, I<LEFT_OPERAND> of the isa operator must be an object type. Otherwise a compilation error occurs.

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

=head2 isa_error Operator

The C<isa_error> operator checks whether the basic type ID given by I<LEFT_OPERAND> can be assigned to the right type.

  LEFT_OPERAND isa RIGHT_TYPE

The return type is int type.

If the assignability is true, returns 1. Otherwise returns 0.

Compilation Errors:

I<LEFT_OPERAND> of the isa_error operator must be an integer type within int. Otherwise a compilation error occurs.

I<RIGHT_OPERAND> of the isa_error operator must be a class type. Otherwise a compilation error occurs.

Examples:

  if (eval_error_id isa_error Error) {
    
  }
  
  if (eval_error_id isa_error Error::System) {
    
  }
  
=head2 is_type Operator

The C<is_type> operator checks whether the type of I<LEFT_OPERAND> is equal to the right type.

  LEFT_OPERAND is_type RIGHT_TYPE

If the right type is a numeric type, a multi-numeric type, a reference type, the L<any object type|/"Any Object Type">, the L<any object array type|/"Any Object Array Type">, this operator checks the compile type of I<LEFT_OPERAND> is equal to the right type.

If the check is true, it returns 1, otherwise returns 0.

If the right type is another object type, this operator checks the runtime type of I<LEFT_OPERAND> is equal to the right type.

If the runtime check is true, it returns 1, otherwise returns 0.

The return type is int type.

Compilation Errors:

If the runtime check is performed, I<LEFT_OPERAND> of the is_type operator must be an object type. Otherwise a compilation error occurs.

Examples:

  if ($object is_type int) {
    
  }
  
  if ($object is_type Point) {
    
  }
  
  if ($object is_type int[]) {
    
  }
  
  if ($object is_type Stringable[]) {
    
  }

=head2 is_error Operator

The C<is_error> operator checks whether the basic type ID given by I<LEFT_OPERAND> is the basic type of the right type.

  LEFT_OPERAND isa RIGHT_TYPE

The return type is int type.

If it is ok, returns 1. Otherwise returns 0.

Compilation Errors:

I<LEFT_OPERAND> of the is_error operator must be an integer type within int. Otherwise a compilation error occurs.

I<RIGHT_OPERAND> of the is_error operator must be a class type. Otherwise a compilation error occurs.

Examples:

  if (eval_error_id is_error Error) {
    
  }
  
  if (eval_error_id is_error Error::System) {
    
  }
  
=head2 is_compile_type Operator

The C<is_compile_type> operator is a L<comparison operator|/"Comparison Operator"> to check whether the compilation-time type of I<LEFT_OPERAND> is the right type.

  LEFT_OPERAND is_compile_type RIGHT_TYPE

If the compilation-time type of I<LEFT_OPERAND> is the right type, returns 1. Otherwise returns 0.

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
  
=head2 type_name Operator

The C<type_name> operator returns the type name of the object.

  type_name OPERAND

If I<OPERAND> is defined, returns the type name of the object. Otherwise returns L<undef|/"Undefined Value">.

The return type is the string type.

Compilation Errors.

If I<OPERAND> is not an object type, a compilation error occurs.

Examples:
  
  # "Point"
  my $poitn = Point->new;
  my $type_name = type_name $point;

=head2 compile_type_name Operator

The C<compile_type_name> operator returns the type name at compilation time.

  type_name OPERAND

The return type is the string type.

Examples:
  
  # int
  my $num = 1;
  my $compile_type_name = compile_type_name $num;

=head2 dump Operator

The C<dump> operator gets the string representation of the object.

  dump OPERAND

It returns the string representation of the object.

The return type is the string type.

The string representation may be changed. Please don't use the C<dump> operator for the purpose of the data serialization.

Compilation Errors:

If I<OPERAND> is not an object type or the undef type, a compilation error occurs.

=head2 new_string_len Operator

The C<new_string_len> operator creates a L<string|/"String"> with the length.

  new_string_len OPERAND

The L<integer promotional conversion|SPVM::Document::Language::Types/"Integer Promotional Conversion"> is performed on I<OPERAND>.

The C<new_string_len> operator returns a new string that length is the length specified by I<OPERAND> and all characters are C<\0>.

The character just after the last character is C<\0>. The string created by the new_string_len operator can be used as the C language string ending with C<\0>.

The return type is the string type.

The length specified by I<OPERAND> must be greater than or equal to 0. Otherwise an exception is thrown.

Compilation Errors:

The type of I<OPERAND> must be an integer type within int. Otherwise a compilation error occurs.

Examples:
  
  # New a string with the length
  my $message = new_string_len 5;

=head2 copy Operator

The C<copy> operator copies the object.

  copy OPERAND

If the type of operand is none of the string type, a numeric type, a multi-numeric type,
An L<exception|/"Exception Handling"> is thorwn.

The C<copy> operator returns the copied object.

The return type is the same as the type of operand.

Read-only flag of the string is dropped.

Compilation Errors:

The type of the operand must be an object type. Otherwise a compilation error occurs.

Examples:
  
  # New a string with the length
  my $message = copy "abc";

=head2 is_read_only Operator

The C<is_read_only> operator checks if the L<string|/"String"> is read-only.

  is_read_only OPERAND

If the string is read-only, the C<is_read_only> operator returns 1, otherwise returns 0.

The return type is an int type.

Compilation Errors:

The operand must be the string type. Otherwise a compilation error occurs.

Examples:
  
  # New a string with the length
  my $message = "Hello";
  my $is_read_only = is_read_only $message;

=head2 length Operator

The string length operator C<length> gets the length of the string.

  length OPERAND

The returned length is the byte size. Note that the length is not the count of UTF-8 characters.

The return type is the int type.

Compilation Errors:

The type of I<OPERAND> must be the string type. Otherwise a compilation error occurs.

Examples:
  
  # Getting the string length. The length is 5.
  my $message = "Hello";
  my $length = length $message;
  
  # Getting the string length of UTF-8. The length is 9.
  my $message = "あいう";
  my $length = length $message;

=head2 scalar Operator

The C<scalar> operator is an L<Operator|/"Operators"> that returns I<OPERAND>.

  scalar OPERAND

Compilation Errors:

The operand must be an L</"The array Length Operator">. Otherwise a compilation error occurs.

Examples:
  
  # Getting the array length 
  my $nums = new int[3];
  foo(scalar @$nums);

  # This is exactlly same as the above.
  my $nums = new int[3];
  foo(@$nums);

Note that the sclara operator exists only to reduce the confusion.

=head2 isweak Operator

The C<isweak> operator checks whether a field is referenced by a L<weak reference|SPVM::Document::Language::GarbageCollection/"Weak Reference">

  isweak OBJECT->{FIELD_NAME};

If the field is weaken, the C<isweak> operator returns 1, otherwise returns 0.

The return type of the C<isweak> operator is the int type.

Compilation Errors:

The type of the object must be the class type. Otherwise a compilation error occurs.

If the field name is not found, a compilation error occurs.

The type of the field targetted by the C<isweak> operator is not an object type, a compilation error occurs.

Examples:

  # isweak
  my $isweak = isweak $object->{point};

=head2 can Operator

The C<can> operator checks if a method can be called. 

  OPERAND can METHOD_NAME

An empty string C<""> means an L<anon method|/"Anon Method">.

If I<OPERAND> can call the method given by METHOD_NAME, returns 1. Otherwise returns 0.

The return type is int type.

Compilation Errors:

The type of I<OPERAND> must be the class type or the L<interface type|/"Interface Type">. Otherwise a compilation error occurs.

The METHOD_NAME must be a method name or an empty string C<"">. Otherwise a compilation error occurs.

Examples:

  my $stringable = (Stringable)Point->new(1, 2);
  
  if ($stringable can to_string) {
    # ...
  }
  
  if ($stringable can "") {
    # ...
  }

=head2 basic_type_id Operator

The C<basic_type_id> operator gets the basic type ID from a type.

  basic_type_id TYPE

The return value is the basic type ID.

The return type is the int type.

Examples:

  my $basic_type_id = basic_type_id int;
  
  my $basic_type_id = basic_type_id int[];
  
  my $error_basic_type_id = basic_type_id Error;
  
=head2 eval_error_id Operator

The C<eval_error_id> operatoer gets the error ID of the exception caught by an eval block.

  eval_error_id

This value is set to 0 at the beginning of the L<eval block|eval Block>.

=head2 warn Operator

The C<warn> operator prints a message to the standard error.

  warn OPERNAD;
  warn;

If I<OPERAND> is omitted or I<OPERAND> is L<undef|/"Undefined Value">, I<OPERAND> is set to the string C<"Warning">.

The return type is the void type.

If the end character of the OPERNAD is C<\n>, the C<warn> operator prints the OPERNAD itself.

Otherwise the current file name and the current line number by the format C<"\n  at $file_name line $line\n"> are added to the end of the OPERNAD.

The buffer of the standard error is flushed after the printing.

Compilation Errors:

The OPERNAD must be the string type or the L<undef type|/"undef Type">. Otherwise a compilation error occurs.

Examples:

  warn "Something is wrong.";

=head2 print Operator

The C<print> operator prints a L<string|/"String"> to the standard output.

  print OPERAND;

I<OPERAND> must be the string type.

The return type is the void type.

If I<OPERAND> is an L<undef|/"Undefined Value">, print nothing.

=head2 say Operator

The C<say> operator prints a L<string|/"String"> with a line break C<\n> to the standard output.

  say OPERAND;

I<OPERAND> must be the string type.

The return type is the void type.

If I<OPERAND> is an L<undef|/"Undefined Value">, print C<\n>.

=head2 make_read_only Operator

The C<make_read_only> operator makes the L<string|/"Strings"> read-only.

  make_read_only OPERAND;

I<OPERAND> must be the string type.

The return type is the void type.

Read-only strings cannnot be cast to string type qualified by L<mutable|/"mutable Type Qualifier">.

  # A string
  my $string = new_string_len 3;
  
  # Make the string read-only
  make_read_only $string;
  
  # The conversion to the string type qualified by mutable throw an exception.
  my $string_mut = (mutable string)$string;

=head2 weaken Operator

The C<weaken> operator creates a L<weak reference|SPVM::Document::Language::GarbageCollection/"Weak Reference">.

  weaken OBJECT->{FIELD_NAME};

The return type is the void type.

Compilation Errors:

The type of the object must be the class type. Otherwise a compilation error occurs.

If the field name is not found, a compilation error occurs.

The type of the field targetted by the C<weaken> statement is not an object type, a compilation error occurs.

Examples:

  # weaken
  weaken $object->{point};

=head2 unweaken Operator

The C<unweaken> operator unweakens a L<weak reference|SPVM::Document::Language::GarbageCollection/"Weak Reference">.

  unweaken OBJECT->{FIELD_NAME};

The return type is the void type.

Compilation Errors:

The type of the object must be the class type. Otherwise a compilation error occurs.

If the field name is not found, a compilation error occurs.

The type of the field targetted by the C<unweaken> statement is not an object type, a compilation error occurs.

Examples:

  # unweaken
  unweaken $object->{point};

=head3 args_width Operator

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

=head2 __PACKAGE__ Operator

The C<__PACKAGE__> operator gets the current class name.

  __PACKAGE__

The return type is the string type.

If the __PACKAGE__ operator is used in anon method, it returns its outer class.

Examples:

  class Foo::Bar {
    static method baz : void () {
      # Foo::Bar
      my $current_class_name = __PACKAGE__;
      
      my $cb = method : void () {
        # Foo::Bar
        my $current_class_name = __PACKAGE__;
      };
    }
  }

=head2 __FILE__ Operator

The C<__FILE__> operator gets the current file name.

  __FILE__

The current file name means the relative path from the base path of the class file. For example, if the class loaded path is C</mypath> and the class name is C<Foo::Bar>, the absolute path is C</mypath/SPVM/Foo/Bar.spvm> and the relative path is C<SPVM/Foo/Bar.spvm>. C<SPVM/Foo/Bar.spvm> is the current file name.

Examples:

  # SPVM/Foo/Bar.spvm
  class Foo::Bar {
    static method baz : void () {
      # Get the current file name - SPVM/Foo/Bar.spvm
      my $file_name == __FILE__;
    }
  }
  class Foo::Bar2 {
    static method baz : void () {
      # Get the current file name - SPVM/Foo/Bar.spvm
      my $file_name == __FILE__;
    }
  }

=head2 __LINE__ Operator

The C<__LINE__> operator gets the current line number of the current file.

  __LINE__

Examples:

  class Foo::Bar {
    static method baz : void () {
      # Get the current line number - 4
      my $line = __LINE__;
    }
  }

=head2 new Operator

The C<new> operator creates an object or an array.

=head3 Creating Object

The syntax of creating object creates an object using the L<new operator|/"new Operator">.

  new CLASS_NAME;

The class name must be the name of the L<class|/"Class"> defined by the L<class definition|/"Class Definition">.

The fields of the created object are initialized by the L<initial value|/"Initial Value">.

The reference count of the created object is 0. If the object is assigned to a local variable, a class variable, or a field by L</"Assignment Operator">, the reference count is incremented by 1.

Examples:

  my $object = new Foo;

=head3 Creating Array

The syntax of creating array creates an array using the L<new operator|/"new Operator">.

  new BasicType[LENGTH]

The type must be a L<basic type|/"Basic Type">.

The L<integer promotional conversion|SPVM::Document::Language::Types/"Integer Promotional Conversion"> is performed on the length.

The length must be greater than or equal to 0. Otherwise an exception is thrown.

All elements of the array are initialized by the L<initial value|/"Initial Value">.

The type of the created array is an array type.

Compilation Errors:

The length must be an integer type within int. Otherwise a compilation error occurs.

Examples:

  my $nums = new int[3];
  my $objects = new Foo[3];
  my $objects = new object[3];
  my $values = new Complex_2d[3]

=head3 Creating Multi-Dimensional Array

Multi dimensional arrays can be created using the L<new operator|/"new Operator">.

  new BasicType[][LENGTH]
  new BasicType[]..[][LENGTH]

(C<[]..[]> means two or more C<[]>)

Examples:

  # 2 dimentional int array
  my $nums = new int[][3];
  
  # 3 dimentional int array
  my $nums = new int[][][3];

The max dimention is 255.

=head2 Array Initialization

The array initialization creates an array and initialize the array easily.

  []
  [ELEMENT1, ELEMENT2, ELEMENT3]

The array initialization create an L<array|SPVM::Document::Language::Types/"Array"> that has the length of the elements.

And the array is initialized by the elements.

And the created array is returned.

The type of the created array is the type that 1 dimension is added to the type of the first element.

If no element is specified, the type of the create array becomes L<any object type|/"Any Object Type">.

Examples:

  # int array
  my $nums = [1, 2, 3];
  
  # double array
  my $nums = [1.5, 2.6, 3.7];
  
  # string array
  my $strings = ["foo", "bar", "baz"];

The first example is the same as the following codes.

  # int array
  my $nums = new int[3];
  $nums->[0] = 1;
  $nums->[1] = 2;
  $nums->[2] = 3;

The array initialization has another syntax using C<{}>. 

  {}
  {ELEMENT1, ELEMENT2, ELEMENT3, ELEMENT4}

This is the same as above array init syntax, but the type of the created array is always L</"Any Object Array Type"> C<object[]>.

Compilation Errors:

If the length of the elements is odd number, a compilation error occurs.

Examples:

  # Key values empty
  my $key_values = {};
  
  # Key values
  my $key_values = {foo => 1, bar => "Hello"};

=head2 Getting Local Variable

The getting local variable gets the value of the local variable.

  $var

The return value is the value of the local variable.

The return type is the type of the local variable.

=head2 Setting Local Variable

The setting local variable sets the value of L</"Local Variable"> using the L<assignment operator|/"Assignment Operator">.

  $var = VALUE

The return value is the value after the assignment.

If the type of the assigned value is an object type, the reference count of the object is incremented by 1.

If an object has already been assigned to $var before the assignment, the reference count of the object is decremented by 1.

See the L<scope|/"Scope"> to know the L<garbage collection|/"Garbage Collection"> of local variables.

Compilation Errors:

The assignment of the value must satisfy the L<type assignability|SPVM::Document::Language::Types/"Type Assignability">. Otherwise a compilation error occurs.

=head2 Getting Class Variable

The getting class variable gets the value of the L<class variable|/"Class Variable">.

  $CLASS_NAME::CLASS_VARIABLE_NAME

C<CLASS_NAME::> can be omitted if the class variable belongs to the current L<class|/"Class">.

  $CLASS_VARIABLE_NAME

If the class variable is used in an anon method and C<CLASS_NAME::> can be omitted, its current class means its outer class.

Compilation Errors:

If the class variable does not found, a compilation error occurs.

If the class variable is C<private> and it is accessed outside of the class, a compilation error occurs.

Examples:

  class Foo {
    our $VAR : int;
  
    static method bar : int () {
      my $var1 = $Foo::VAR;
      my $var2 = $VAR;
      
      my $cb = method : void () {
        # $Foo::BAR
        $VAR;
      }
    }
  }

=head2 Setting Class Variable

B<Setting Class Variable operator> sets L</"Class Variable"> Value using the L<assignment operator|/"Assignment Operator">.

  $CLASS_NAME::CLASS_VARIABLE_NAME = VALUE

"CLASS_NAME::" can be omitted when the class Variable belongs to own class.

  $CLASS_VARIABLE_NAME = VALUE

The return value is the value after the setting.

The return type is the type of the class variable.

If the type of the assigned value is an object type, the reference count of the object is incremented by 1.

If an object has already been assigned to $CLASS_VARIABLE_NAME before the assignment, the reference count of the object is decremented by 1.

If the class variable is used in an anon method and C<CLASS_NAME::> can be omitted, its current class means its outer class.

Compilation Errors:

If the assignment does not satisfy the L<type assignability|SPVM::Document::Language::Types/"Type Assignability">, a compilation error occurs.

If the class variable does not found, a compilation error occurs.

If the class variable is C<private> and it is accessed outside of the class, a compilation error occurs.

Examples:

  class Foo {
    our $VAR : int;
  
    static method bar : int () {
      $Foo::VAR = 1;
      $VAR = 3;
    }
    my $cb = method : void () {
      # $Foo::VAR
      $VAR = 5;
    }
  }

=head2 Getting Exception Variable

The setting exception variable gets the value of the L<exception variable|/"Exception Variable">.

  $@

The return value is the value of L<exception variable|/"Exception Variable">.

The return type is the string type.

Examples:
  
  # Getting the exception variable
  my $message = $@;

=head2 Setting Exception Variable

The setting exception variable sets the value of L</"Exception Variable"> using the L<assignment operator|/"Assignment Operator">.

  $@ = VALUE

The type of the assigned value must be the string type.

The return value is the value after the setting.

The return type is the string type.

The reference count of the assigned value is incremented by 1.

If an string has already been assigned to the exception variable before the assignment, the reference count of the string is decremented by 1.

Examples:

  $@ = "Error";

=head2 Getting Field

The getting field gets the field of the object. This is one syntax of the L<field access|/"Field Access">.

  INVOCANT->{FIELD_NAME}

The type of invocant is a class type.

The retrun type is the type of the field.

Examples:

  my $point = Point->new;
  my $x = $point->{x};

=head2 Setting Field

The setting field sets the field of the object. This is one syntax of the L<field access|/"Field Access">.

  INVOCANT->{FIELD_NAME} = VALUE

The type of invocant is a class type.

The return value is the value after the setting. 

The return type is the field type.

If the type of assigned value is a basic object type, the reference count of the object is incremented by 1.

If an object has already been assigned to the field before the assignment, the reference count of that object is decremented by 1.

Compilation Errors:

If the assignment does not satisfy the L<type assignability|SPVM::Document::Language::Types/"Type Assignability">, a compilation error occurs.

Examples:

  my $point = Point->new;
  $point->{x} = 1;

=head2 Getting Multi-Numeric Field

B<Getting Multi-Numeric Field operator> gets the field of the L<multi-numeric value|/"Multi-Numeric Value">. This is one syntax of the L<field access|/"Field Access">.

  INVOCANT->{FIELD_NAME}

The invocant is the multi-numeric type.
  
Getting Multi-Numeric Field operator returns the field value in the multi-numeric value.

The retrun type is the type of the field.

Compilation Errors:

If the field names does not found in the class, a compilation error occurs

Examples:

  my $z : Complex_2d;
  my $re = $z->{re};

=head2 Setting Multi-Numeric Field

Setting Multi-Numeric Field operator sets the field of the L<multi-numeric value|/"Multi-Numeric Value"> using L</"Assignment Operator">. This is one syntax of the L<field access|/"Field Access">.

  INVOCANT->{FIELD_NAME} = RIGHT_OPERAND

The invocant is the multi-numeric type.

Setting Multi-Numeric Field operator returns the value of the field after setting. 

The assignment must satisfy the L<type assignability|SPVM::Document::Language::Types/"Type Assignability">.

The return type is the field type.

Compilation Errors:

If the field names does not found in the class, a compilation error occurs.

Examples:

  my $z : Complex_2d;
  $z->{re} = 2.5;

=head2 Getting Array Element

The getting array element gets the element of the L<array|SPVM::Document::Language::Types/"Array">.

  ARRAY->[INDEX]

The array must be an array type.

The L<integer promotional conversion|SPVM::Document::Language::Types/"Integer Promotional Conversion"> is performed on the index.

The getting array element returns the element that is specifed by the index.

The return type is the type of the element.

The array must be defined. Otherwise an exception is thrown.

The index must be greater than or equal to 0. Otherwise an exception is thrown.

Compilation Errors:

The index must be an integer type within int. Otherwise a compilation error occurs.

Examples:

  my $nums = new int[3];
  my $num = $nums->[1];
  
  my $points = new Point[3];
  my $point = $points->[1];
  
  my $objects : object[] = $points;
  my $object = (Point)$objects->[1];

=head2 Setting Array Element

The setting array element sets the element of the array using the L<assignment operator|/"Assignment Operator">.

  ARRAY->[INDEX] = RIGHT_OPERAND

The array must be an array type.

The L<integer promotional conversion|SPVM::Document::Language::Types/"Integer Promotional Conversion"> is performed on the index.

I<RIGHT_OPERAND> must satisfy L<type assignability|SPVM::Document::Language::Types/"Type Assignability">.

The setting array element returns the value of the element that is set.

The array must be defined. Otherwise an exception is thrown.

The index must be greater than or equal to 0. Otherwise an exception is thrown.

If I<RIGHT_OPERAND> is an object type, the reference count of the object is incremented by 1.

If an object has already been assigned to the field before the assignment, the reference count of the object is decremented by 1.

Compilation Errors:

The index must be an integer type within int. Otherwise a compilation error occurs.

Examples:

  my $nums = new int[3];
  $nums->[1] = 3;
  
  my $points = new Point[3];
  $points->[1] = Point->new(1, 2);
  
  my $objects : object[] = $points;
  $objects->[2] = Point->new(3, 5);

=head2 Type Cast Operator

The type cast operator performs an L<explicite type conversion|SPVM::Document::Language::Types/"Explicite Type Conversion">.

  # Type Cast
  (TYPE)OPERAND
  
  # Postfix Type Cast
  OPERAND->(TYPE)

Compilation Errors:

If the operand of the type cast operator dose not satisfy L<type castability|"Type Castability">, a compilation error occurs.

Examples:
  
  # long to int 
  my $num = (int)123L;
  
  # byte[] to string
  my $num = (string)new byte[3];
  
  # string to byte[]
  my $num = (byte[])"Hello";
  
  # Postfix type cast
  my $stringable = Point->new->(Stringable);

=head2 Method Call

The method call syntax calls a L<method|/"Method">.

=head3 Class Method Call

A method defined as the L<class method|/"Class Method"> can be called using the class method call.

  ClassName->MethodName(ARGS1, ARGS2, ...);
  
  &MethodName(ARGS1, ARGS2, ...);

C<&> means the current class.

If C<&> is used in anon method, it means its outer class.

Compilation Errors:

If the number of arguments does not correct, a compilation error occurs.

If the types of arguments have no type compatible, a compilation error occurs.

Examples:
  
  class Foo {
    
    static method main : void () {
      
      my $ret = Foo->bar(1, 2, 3);
      
      # Same as Foo->bar
      my $ret = &bar(1, 2, 3);
      
      my $cb = method : void () {
        # Same as Foo->bar;
        my $ret = &foo;
      };
    }
    
    static method foo : int () {
      return 5;
    }
  }

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

=head3 Setting the value with Dereference

Setting a value with Dereference sets the actual value from Reference. It was designed to realize the C joint operator C<*>.

  $VARIABLE = OPERAND

Setting a value with Dereference returns the set value.

Compilation Errors:

The variable type must be a reference type. Otherwise a compilation error occurs.

The type of operator must match the type of the variable when dereferenced. Otherwise a compilation error occurs.

Examples:

  my $num : int;
  my $num_ref : int* = \$num;
  $$num_ref = 1;
  
  my $z : Complex_2d;
  my $z_ref : Complex_2d* = \$z;
  
  my $z2 : Complex_2d;
  
  $$z_ref = $z2;

=head3 Getting Multi-Numeric Field via Dereference

The syntax of getting multi-numeric field via dereference gets the field of the L<multi-numeric value|/"Multi-Numeric Value"> via L</"Dereference">. This is one syntax of the L<field access|/"Field Access">

  INVOCANT->{FIELD_NAME}

The invocant is L</"Multi-Numeric Reference Type">.

The getting multi-numeric field via dereference operator returns the field value in the multi-numeric value.

The retrun type is the type of the field.

Compilation Errors:

If the field names does not found in the class, a compilation error occurs

Examples:

  my $z : Complex_2d;
  my $z_ref = \$z;
  my $re = $z_ref->{re};

=head3 Setting Multi-Numeric Field via Dereference

The setting multi-numeric field via dereference operator sets the field of the L<multi-numeric value|/"Multi-Numeric Value"> via L</"Dereference"> using L</"Assignment Operator">. This is one syntax of the L<field access|/"Field Access">.

  INVOCANT->{FIELD_NAME} = RIGHT_OPERAND

The invocant is L</"Multi-Numeric Reference Type">.

The setting multi-numeric field via dereference operator returns the value of the field after setting.

The assignment must satisfy the L<type assignability|SPVM::Document::Language::Types/"Type Assignability">.

The return type is the field type.

Compilation Errors:

If the field names does not found in the class, a compilation error occurs

Examples:

  my $z : Complex_2d;
  my $z_ref = \$z;
  $z_ref->{re} = 2.5;

=head2 Anon Method Operator

The anon method operator defines an L<anon calss|SPVM::Document::Language::Class/"Anon Class"> that has an anon instance method.

And this operator creates an object which type is the anon class by the L<new/"new Operator"> operator, and returns it.
  
  # Anon method
  method : TYPE  (VAR1 : TYPE1, VAR2 : TYPE2, ...) {
  
  }

The way to define the method is the same as the L<method definition|SPVM::Document::Language::Class/"Method Definition">.

Examples:
  
  # Anon method
  class Foo::Bar {
    method some_method : void () {
      my $comparator = (Comparator)method : int ($x1 : object, $x2 : object) {
        my $point1 = (Point)$x1;
        my $point2 = (Point)$x2;
        
        return $point1->x <=> $point2->x;
      };
    }
  }

See also L<Comparator|SPVM::Comparator>.

The above example is the same as the following codes.
  
  # Foo/Bar.spvm
  class Foo::Bar {
    method some_method : void () {
      my $comparator = (Comparator)new Foo::Bar::anon::3::31;
    }
  }
  
  # Foo/Bar/anon/3/31.spvm
  class Foo::Bar::anon::3::31 : public {
    method : int ($x1 : object, $x2 : object) {
      my $point1 = (Point)$x1;
      my $point2 = (Point)$x2;
      
      return $point1->x <=> $point2->x;
    }
  }

=head3 Anon Method Field Definition

The anon method field definition is the syntax to define the field of the anon class of the anon method.

  # Anon method field definitions
  [has FIELD_NAME : TYPE1, has FIELD_NAME : TYPE2, ...] ANON_METHOD_DEFINITION
  
  # Anon method field definitions with field default values
  [has FIELD_NAME : TYPE1 = OPERAND1, has FIELD_NAME : TYPE2 = OPERAND2, ...] ANON_METHOD_DEFINITION
  
  [VAR1 : TYPE1, VAR2 : TYPE2, ...] ANON_METHOD_DEFINITION
  
Examples:

  class Foo::Bar {
    method some_method : void () {
      my $foo = 1;
      my $bar = 5L;
      
      my $comparator = (Comparator)[has foo : int = $foo, has bar : long = $bar] method : int ($x1 : object, $x2 : object) {
        my $foo = $self->{foo};
        my $bar = $self->{bar};
        
        print "$foo\n";
        print "$bar\n";
      };
    }
  }

Same as avobe but more simple:

  class Foo::Bar {
    method some_method : void () {
      my $foo = 1;
      my $bar = 5L;
      
      my $comparator = (Comparator)[$foo : int, $bar : long] method : int ($x1 : object, $x2 : object) {
        print "$foo\n";
        print "$bar\n";
      };
    }
  }

The above example is the same as the following codes.

  # Foo/Bar.spvm
  class Foo::Bar {
    method some_method : void () {
      # Externally defined local variables
      my $foo = 1;
      my $bar = 5L;
      
      my $anon = new Foo::Bar::anon::5::61;
      $anon->{foo} = $foo;
      $anon->{bar} = $bar;
      
      my $comparator = (Comparator)$anon;
    }
  }
  
  # Foo/Bar/anon/5/61.spvm
  class Foo::Bar::anon::5::61 : public {
    has foo : public int;
    has bar : public long;
    
    method : int ($x1 : object, $x2 : object) {
      my $foo = $self->{foo};
      my $bar = $self->{bar};
      
      print "$foo\n";
      print "$bar\n";
    }
  }

=head2 Reference Operator

The reference operator C<\> creates a reference, and returns it.

  \OPERAND

The return type is the reference type of I<OPERAND>.

Compilation Errors:

The operand must be a local variable that type is a numeric type or a multi-numeric type. Otherwise a compilation error occurs.

Examples:
  
  # Create the reference of a numeric type
  my $num : int;
  my $num_ref : int* = \$num;
  
  # Create the reference of a multi-numeric type
  my $z : Complex_2d;
  my $z_ref : Complex_2d* = \$z;

=head2 Dereference Operator

The dereference operator C<$> returns the value referenced by the variable I<VARIABLE>.

  $VARIABLE

The return type is the type of the value referenced by I<VARIABLE>.

Compilation Errors:

The type of the variable must be a reference type. Otherwise a compilation error occurs.

Examples:

  my $num : int;
  my $num_ref : int* = \$num;
  my $num_deref : int = $$num_ref;
  
  my $z : Complex_2d;
  my $z_ref : Complex_2d* = \$z;
  my $z_deref : Complex_2d = $$z_ref;

=head1 See Also

=over 2

=item * L<Class Definition|SPVM::Document::Language::Class>

=item * L<Types|SPVM::Document::Language::Types>

=item * L<Exception Handling|SPVM::Document::Language::ExceptionHandling>

=item * L<Garbage Collection|SPVM::Document::Language::GarbageCollection>

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

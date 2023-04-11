=head1 Name

SPVM::Document::Tutorial::Complex - complex tutorial.

=head1 Description

This document is complex tutorial.

=head1 Exampels

=head2 Complex Tutorial

SPVM provides common arithmetic for complex numbers at the same level as C99.

=head3 Complex Type

Complex Type is Complex_2f for complex float and Complex_2d for complex double.

Complex_2f and Complex_2d is <a href="/language.html#language-type-multi-numeric">Multi Numeric Type</a>. This is allocated on Method Call Stack.

This is not Object Type which is allocated on Heap Memory.

See <a href="https://github.com/yuki-kimoto/SPVM/tree/master/examples/matrix">SPVM Complex Examples</a> at first.

=head4 Complex_2f

  
  # Complex float type
  use Complex_2f;

  my $z : Complex_2f;
  $z->{re} = 1.5f;
  $z->{im} = 1.7f;
  

=head4 Complex_2d

  
  # Complex double type
  use Complex_2d;

  my $z : Complex_2d;
  $z->{re} = 1.5;
  $z->{im} = 1.7;
  

=head3 New Complex Functions

New Complex functions

  
  use Math (complexf, complex);

  # Complex_2f
  my $z = complexf(1.5f, 1.7f);

  # Complex_2d
  my $z = complex(1.5, 1.7);
  

=head3 Complex Operation

=head4 float Complex Addition, Subtract, Multiply, Scalar Multiply, Division

float Complex Addition, Subtract, Multiply, Scalar Multiply, Division.

  
  # float Addition, Subtract, Multiply, Scalar Multiply, Division functions
  use Math(caddf, csubf, cmulf, cscamulf, cdivf);

  my $z1 = complexf(1.5f, 1.7f);
  my $z2 = complexf(2.5f, 2.7f);

  # Addition
  my $z_add = caddf($z1, $z2);

  # Subtract
  my $z_method = csubf($z1, $z2);

  # Multiply
  my $z_mul = cmulf($z1, $z2);

  # Scalar Multiply
  my $z_scamul = cscamulf(3, $z2);

  # Division
  my $z_div = cdivf($z1, $z2);
  

=head4 double Complex Addition, Subtract, Multiply, Scalar Multiply, Division

  
  # double Addition, Subtract, Multiply, Scalar Multiply, Division functions
  use Math(cadd, csub, cmul, cscamul, cdiv);

  my $z1 = complex(1.5, 1.7);
  my $z2 = complex(2.5, 2.7);

  # Addition
  my $z_add = cadd($z1, $z2);

  # Subtract
  my $z_method = csub($z1, $z2);

  # Multiply
  my $z_mul = cmul($z1, $z2);

  # Scalar Multiply
  my $z_scamul = cscamul(3, $z2);

  # Division
  my $z_div = cdiv($z1, $z2);
  

=head3 Trigonometric functions

Trigonometric functions.

=head4 float Trigonometric functions

float Trigonometric functions.

  
  # float Trigonometric functions
  use Math(csinf, ccosf, ctanf);

  my $z = complexf(1.5f, 1.7f);

  # Addition
  my $z_sin = csinf($z);

  # Subtract
  my $z_cos = ccosf($z);

  # Multiply
  my $z_tan = ctanf($z);
  

=head4 double Trigonometric functions

double Trigonometric functions.

  
  # double Trigonometric functions
  use Math(csin, ccos, ctan);

  my $z = complex(1.5, 1.7);

  # Addition
  my $z_sin = csin($z);

  # Subtract
  my $z_cos = ccos($z);

  # Multiply
  my $z_tan = ctan($z);
  

See Math for more complex functions

=head3 Complex Array

SPVM Array of Complex has values arranged in contiguous memory areas.

=head4 Complex_2f[]

  
  # Complex float type
  use Complex_2f;

  my $zs = new Complex_2f[100];

  for (my $i = 0; $i < @$zs; $i++) {
    my $z = $zs->[$i];
    $z->{re} = 1.5f;
    $z->{im} = 1.7f;
  }
  

=head4 Complex_2d

  
  # Complex double type
  use Complex_2d;

  my $zs = new Complex_2d[100];

  for (my $i = 0; $i < @$zs; $i++) {
    my $z = $zs->[$i];
    $z->{re} = 1.5;
    $z->{im} = 1.7;
  }
  

=head3 Call complex function from Perl

Call complex function from Perl. Argument is passed and return value is return.

  
  use SPVM 'MyComplex';

  my $z1 = {re => 1.7, im => 2.7};
  my $z2 = {re => 7.5, im => 2.5};

  my $z_ret = MyComplex->complex_call_from_perl($z1, $z2);

  print "($z_ret->{re}, $z_ret->{im})\n";
  

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

#include <assert.h>
#include <string.h>

#include "spvm_core_func.h"



#include "spvm_core_func_bind.h"

#include "spvm_compiler.h"
#include "spvm_list.h"
#include "spvm_sub.h"
#include "spvm_op.h"

void SPVM_CORE_FUNC_BIND_bind_core_func(SPVM_COMPILER* compiler, SPVM_LIST* op_subs) {
  // Bind native subroutine
  {
    int32_t i;
    for (i = 0; i < op_subs->length; i++) {
      SPVM_OP* op_sub = SPVM_LIST_fetch(op_subs, i);
      SPVM_SUB* sub = op_sub->uv.sub;
      
      if (sub->have_native_desc) {
        // Sub abs name
        const char* sub_name = sub->op_name->uv.name;
        switch (sub_name[0]) {
          case 'a':
            break;
          case 'c':
            break;
          case 'e':
            break;
          case 'f':
            break;
          case 'h':
            break;
          case 'i':
            break;
          case 'l':
            break;
          case 'n':
            break;
          case 'p':
            if (strcmp(sub_name, "print") == 0) {
              sub->native_address = SPVM_CORE_FUNC_print;
            }
            break;
            break;
          case 'r':
            break;
          case 's':
            break;
          case 't':
            if (strcmp(sub_name, "time") == 0) {
              sub->native_address = SPVM_CORE_FUNC_time;
            }
            break;
          case 'w':
            if (strcmp(sub_name, "warn") == 0) {
              sub->native_address = SPVM_CORE_FUNC_warn;
            }
            break;
          case 'B':
            break;
          case 'D':
            break;
          case 'E':
            break;
          case 'F':
            break;
          case 'I':
            break;
          case 'L':
            break;
          case 'N':
            break;
          case 'P':
            break;
          case 'S':
            break;
          default:
            assert(0);
        }
      }
    }
  }
}

/*
  native sub acos : double ($x : double);
  native sub asin : double($x : double);
  native sub atan : double ($x : double);
  native sub atan2 : double ($y : double, $x : double);
  native sub acosh : double ($x : double);
  native sub asinh : double ($x : double);
  native sub atanh : double ($x : double);
  native sub abs : int ($x : int);

  native sub cos : double ($x : double);
  native sub cosh : double ($x : double);
  native sub cbrt : double ($x : double);
  native sub ceil : double ($x : double);

  native sub exp : double ($x : double);
  native sub exp2 : double ($x : double);
  native sub expm1 : double ($x : double);
  native sub erf : double ($x : double);
  native sub erfc : double ($x : double);
  
  native sub fabs : double ($x : double);
  native sub floor : double ($x : double);

  native sub hypot : double ($x : double, $y : double);

  native sub isinff : int($x : float);
  native sub isfinitef : int($x : float);
  native sub isnanf : int ($x : float);
  native sub isinf : int ($x : double);
  native sub isfinite : int ($x : double);
  native sub isnan : int ($x : double);
  
  native sub log : double ($x : double);
  native sub log10 : double ($x : double);
  native sub log1p : double ($x : double);
  native sub labs : long ($x : long);
  native sub lgamma : double ($x : double);

  native sub nearbyint : double ($x : double);

  native sub pow : double ($x : double, $y : double);

  native sub round : double ($x : double);
  native sub remainder : double ($x1 : double, $x2 : double);

  native sub sin : double ($x : double);
  native sub sinh : double ($x : double);
  native sub sqrt : double ($x : double);

  native sub tan : double ($x : double);
  native sub tanh : double ($x : double);
  native sub tgamma : double ($x : double);

  sub BYTE_MIN : byte ()  { return (byte)-128; }
  sub BYTE_MAX : byte () { return (byte)127; }

  native sub DBL_MAX : double ();
  native sub DBL_MIN : double ();
  sub E : double () { return 2.7182818284590452354; }
  native sub FLT_MAX : float ();
  native sub FLT_MIN : float();
  sub INT_MIN : int () { return -2147483648; }
  sub INT_MAX : int () { return 2147483647; }
  native sub INFINITYF : float ();
  native sub INFINITY : double ();
  sub LONG_MIN : long () { return -9223372036854775808L; }
  sub LONG_MAX : long () { return 9223372036854775807L; }
  native sub NANF : float ();
  native sub NAN : double ();
  sub PI : double () { return 3.14159265358979323846; }
  sub SHORT_MIN : short () { return (short)-32768; }
  sub SHORT_MAX : short () { return (short)32767; }
*/
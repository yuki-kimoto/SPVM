#include <assert.h>
#include <string.h>

#include "spvm_core_func.h"



#include "spvm_core_func_bind.h"

#include "spvm_compiler.h"
#include "spvm_list.h"
#include "spvm_sub.h"
#include "spvm_op.h"

void SPVM_CORE_FUNC_BIND_bind_core_func(SPVM_COMPILER* compiler, SPVM_LIST* op_subs) {
  (void)compiler;
  
  return;
  
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
            if (strcmp(sub_name, "acos") == 0) {
              sub->native_address = SPVM_CORE_FUNC_acos;
            }
            else if (strcmp(sub_name, "asin") == 0) {
              sub->native_address = SPVM_CORE_FUNC_asin;
            }
            else if (strcmp(sub_name, "atan") == 0) {
              sub->native_address = SPVM_CORE_FUNC_atan;
            }
            else if (strcmp(sub_name, "atan2") == 0) {
              sub->native_address = SPVM_CORE_FUNC_atan2;
            }
            else if (strcmp(sub_name, "acosh") == 0) {
              sub->native_address = SPVM_CORE_FUNC_acosh;
            }
            else if (strcmp(sub_name, "asinh") == 0) {
              sub->native_address = SPVM_CORE_FUNC_asinh;
            }
            else if (strcmp(sub_name, "atanh") == 0) {
              sub->native_address = SPVM_CORE_FUNC_atanh;
            }
            else if (strcmp(sub_name, "abs") == 0) {
              sub->native_address = SPVM_CORE_FUNC_abs;
            }
            break;
          case 'c':
            if (strcmp(sub_name, "cos") == 0) {
              sub->native_address = SPVM_CORE_FUNC_cos;
            }
            else if (strcmp(sub_name, "cosh") == 0) {
              sub->native_address = SPVM_CORE_FUNC_cosh;
            }
            else if (strcmp(sub_name, "cbrt") == 0) {
              sub->native_address = SPVM_CORE_FUNC_cbrt;
            }
            else if (strcmp(sub_name, "ceil") == 0) {
              sub->native_address = SPVM_CORE_FUNC_ceil;
            }
            break;
          case 'e':
              if (strcmp(sub_name, "exp") == 0) {
                sub->native_address = SPVM_CORE_FUNC_exp;
              }
              else if (strcmp(sub_name, "exp2") == 0) {
                sub->native_address = SPVM_CORE_FUNC_exp2;
              }
              else if (strcmp(sub_name, "expm1") == 0) {
                sub->native_address = SPVM_CORE_FUNC_expm1;
              }
              else if (strcmp(sub_name, "erf") == 0) {
                sub->native_address = SPVM_CORE_FUNC_erf;
              }
              else if (strcmp(sub_name, "erfc") == 0) {
                sub->native_address = SPVM_CORE_FUNC_erfc;
              }
            break;
          case 'f':
            if (strcmp(sub_name, "fabs") == 0) {
              sub->native_address = SPVM_CORE_FUNC_fabs;
            }
            else if (strcmp(sub_name, "floor") == 0) {
              sub->native_address = SPVM_CORE_FUNC_floor;
            }
            break;
          case 'h':
            if (strcmp(sub_name, "hypot") == 0) {
              sub->native_address = SPVM_CORE_FUNC_hypot;
            }
            break;
          case 'i':
            if (strcmp(sub_name, "isinff") == 0) {
              sub->native_address = SPVM_CORE_FUNC_isinff;
            }
            else if (strcmp(sub_name, "isfinitef") == 0) {
              sub->native_address = SPVM_CORE_FUNC_isfinitef;
            }
            else if (strcmp(sub_name, "isnanf") == 0) {
              sub->native_address = SPVM_CORE_FUNC_isnanf;
            }
            else if (strcmp(sub_name, "isinf") == 0) {
              sub->native_address = SPVM_CORE_FUNC_isinf;
            }
            else if (strcmp(sub_name, "isfinite") == 0) {
              sub->native_address = SPVM_CORE_FUNC_isfinite;
            }
            else if (strcmp(sub_name, "isnan") == 0) {
              sub->native_address = SPVM_CORE_FUNC_isnan;
            }
            break;
          case 'l':
            if (strcmp(sub_name, "log") == 0) {
              sub->native_address = SPVM_CORE_FUNC_log;
            }
            else if (strcmp(sub_name, "log10") == 0) {
              sub->native_address = SPVM_CORE_FUNC_log10;
            }
            else if (strcmp(sub_name, "log1p") == 0) {
              sub->native_address = SPVM_CORE_FUNC_log1p;
            }
            else if (strcmp(sub_name, "labs") == 0) {
              sub->native_address = SPVM_CORE_FUNC_labs;
            }
            else if (strcmp(sub_name, "lgamma") == 0) {
              sub->native_address = SPVM_CORE_FUNC_lgamma;
            }
            break;
          case 'n':
            if (strcmp(sub_name, "nearbyint") == 0) {
              sub->native_address = SPVM_CORE_FUNC_nearbyint;
            }
            break;
          case 'p':
            if (strcmp(sub_name, "print") == 0) {
              sub->native_address = SPVM_CORE_FUNC_print;
            }
            else if (strcmp(sub_name, "pow") == 0) {
              sub->native_address = SPVM_CORE_FUNC_pow;
            }
            break;
          case 'r':
            if (strcmp(sub_name, "round") == 0) {
              sub->native_address = SPVM_CORE_FUNC_round;
            }
            else if (strcmp(sub_name, "remainder") == 0) {
              sub->native_address = SPVM_CORE_FUNC_remainder;
            }
            break;
          case 's':
            if (strcmp(sub_name, "sin") == 0) {
              sub->native_address = SPVM_CORE_FUNC_sin;
            }
            else if (strcmp(sub_name, "sinh") == 0) {
              sub->native_address = SPVM_CORE_FUNC_sinh;
            }
            else if (strcmp(sub_name, "sqrt") == 0) {
              sub->native_address = SPVM_CORE_FUNC_sqrt;
            }
            break;
          case 't':
            if (strcmp(sub_name, "time") == 0) {
              sub->native_address = SPVM_CORE_FUNC_time;
            }
            else if (strcmp(sub_name, "tan") == 0) {
              sub->native_address = SPVM_CORE_FUNC_tan;
            }
            else if (strcmp(sub_name, "tanh") == 0) {
              sub->native_address = SPVM_CORE_FUNC_tanh;
            }
            else if (strcmp(sub_name, "tgamma") == 0) {
              sub->native_address = SPVM_CORE_FUNC_tgamma;
            }
            break;
          case 'w':
            if (strcmp(sub_name, "warn") == 0) {
              sub->native_address = SPVM_CORE_FUNC_warn;
            }
            break;
          case 'D':
            if (strcmp(sub_name, "DBL_MAX") == 0) {
              sub->native_address = SPVM_CORE_FUNC_DBL_MAX;
            }
            else if (strcmp(sub_name, "DBL_MIN") == 0) {
              sub->native_address = SPVM_CORE_FUNC_DBL_MIN;
            }
            break;
          case 'E':
            if (strcmp(sub_name, "E") == 0) {
              sub->native_address = SPVM_CORE_FUNC_E;
            }
            break;
          case 'F':
            if (strcmp(sub_name, "FLT_MAX") == 0) {
              sub->native_address = SPVM_CORE_FUNC_FLT_MAX;
            }
            else if (strcmp(sub_name, "FLT_MIN") == 0) {
              sub->native_address = SPVM_CORE_FUNC_FLT_MIN;
            }
            break;
          case 'I':
            if (strcmp(sub_name, "INFINITYF") == 0) {
              sub->native_address = SPVM_CORE_FUNC_INFINITYF;
            }
            else if (strcmp(sub_name, "INFINITY") == 0) {
              sub->native_address = SPVM_CORE_FUNC_INFINITY;
            }
            else if (strcmp(sub_name, "INT8_MIN") == 0) {
              sub->native_address = SPVM_CORE_FUNC_INT8_MIN;
            }
            else if (strcmp(sub_name, "INT8_MAX") == 0) {
              sub->native_address = SPVM_CORE_FUNC_INT8_MAX;
            }
            else if (strcmp(sub_name, "INT16_MIN") == 0) {
              sub->native_address = SPVM_CORE_FUNC_INT16_MIN;
            }
            else if (strcmp(sub_name, "INT16_MAX") == 0) {
              sub->native_address = SPVM_CORE_FUNC_INT16_MAX;
            }
            else if (strcmp(sub_name, "INT32_MIN") == 0) {
              sub->native_address = SPVM_CORE_FUNC_INT32_MIN;
            }
            else if (strcmp(sub_name, "INT32_MAX") == 0) {
              sub->native_address = SPVM_CORE_FUNC_INT32_MAX;
            }
            else if (strcmp(sub_name, "INT64_MIN") == 0) {
              sub->native_address = SPVM_CORE_FUNC_INT64_MIN;
            }
            else if (strcmp(sub_name, "INT64_MAX") == 0) {
              sub->native_address = SPVM_CORE_FUNC_INT64_MAX;
            }
            break;
          case 'N':
            if (strcmp(sub_name, "NANF") == 0) {
              sub->native_address = SPVM_CORE_FUNC_NANF;
            }
            else if (strcmp(sub_name, "NAN") == 0) {
              sub->native_address = SPVM_CORE_FUNC_NAN;
            }
            break;
          case 'P':
            if (strcmp(sub_name, "PI") == 0) {
              sub->native_address = SPVM_CORE_FUNC_PI;
            }
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


  native sub DBL_MAX : double ();
  native sub DBL_MIN : double ();
  native sub E : double ();
  native sub FLT_MAX : float ();
  native sub FLT_MIN : float();
  native sub INFINITYF : float ();
  native sub INFINITY : double ();
  native sub NANF : float ();
  native sub NAN : double ();
  native sub PI : double ();
  native sub INT8_MIN : byte ();
  native sub INT8_MAX : byte ();
  native sub INT16_MIN : short ();
  native sub INT16_MAX : short ();
  native sub INT32_MIN : int ();
  native sub INT32_MAX : int ();
  native sub INT64_MIN : long ();
  native sub INT64_MAX : long ();
*/

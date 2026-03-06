#ifdef _MSC_VER
  /* Branch prediction hint (Not supported in MSVC, defined as a no-op) */
  #define __builtin_expect(expr, val) (expr)
#endif


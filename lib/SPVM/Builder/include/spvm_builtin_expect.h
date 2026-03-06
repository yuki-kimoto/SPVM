/*
 * Define __builtin_expect as a no-op if the compiler does not support it.
 */
#ifndef __builtin_expect
#  ifdef __has_builtin
#    if !__has_builtin(__builtin_expect)
#      define __builtin_expect(x, expected_value) (x)
#    endif
#  else
#    define __builtin_expect(x, expected_value) (x)
#  endif
#endif

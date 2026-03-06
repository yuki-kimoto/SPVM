/*
 * Define __builtin_expect as a no-op if the compiler does not support it.
 */
#if !defined(__has_builtin) || !__has_builtin(__builtin_expect)
#  define __builtin_expect(x, expected_value) (x)
#endif

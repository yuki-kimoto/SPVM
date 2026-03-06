#ifdef _MSC_VER
  #include <intrin.h>
  /* Atomic operations (Mapped to MSVC intrinsics) */
  #define __sync_fetch_and_add(ptr, val)  _InterlockedExchangeAdd((long volatile*)(ptr), (long)(val))
  #define __sync_fetch_and_or(ptr, val)   _InterlockedOr((long volatile*)(ptr), (long)(val))
  #define __sync_fetch_and_xor(ptr, val)  _InterlockedXor((long volatile*)(ptr), (long)(val))
  #define __sync_fetch_and_and(ptr, val)  _InterlockedAnd((long volatile*)(ptr), (long)(val))
#endif

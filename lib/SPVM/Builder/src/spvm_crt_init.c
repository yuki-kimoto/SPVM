/* Suppress MSVC GUI pop-ups on calling assert function by redirecting to stderr. */
/* Uses CRT$XIU section hook to execute this setup before main/DllMain. */
#if defined(_MSC_VER)
  #include <windows.h>
  #include <stdlib.h>
  static void spvm_crt_init(void) {
    _set_error_mode(_OUT_TO_STDERR);
  }
  
  #pragma section(".CRT$XIU", read)
  __declspec(allocate(".CRT$XIU")) void (*spvm_crt_init_ptr)(void) = spvm_crt_init;
#endif

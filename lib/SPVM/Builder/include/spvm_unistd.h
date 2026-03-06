#if defined(_WIN32)
#  include <io.h>
#  define dup _dup
#  define fileno _fileno
#else
#  include <unistd.h>
#endif


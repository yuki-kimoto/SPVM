// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifdef __linux__
  // Enable X/Open System Interfaces (SUSv4) functions and POSIX.1-2008 standard functions
  #define _XOPEN_SOURCE 700

  // Enable BSD and System V extensions
  #define _DEFAULT_SOURCE
#endif

#include <stdlib.h>
#include <inttypes.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <ctype.h>
#include <stdarg.h>
#include <time.h>

#include "spvm_native.h"

#include "spvm_api_cfunc.h"

SPVM_API_CFUNC* SPVM_API_CFUNC_new_api() {
  
  void* env_cfunc_init[]  = {
    SPVM_API_CFUNC_c_strlen,
    SPVM_API_CFUNC_c_memcpy,
    SPVM_API_CFUNC_c_memset,
    SPVM_API_CFUNC_c_memcmp,
    SPVM_API_CFUNC_c_strtoll,
    SPVM_API_CFUNC_c_strtof,
    SPVM_API_CFUNC_c_strtod,
    SPVM_API_CFUNC_c_fputs,
    SPVM_API_CFUNC_c_fgetc,
    SPVM_API_CFUNC_c_snprintf_len,
    SPVM_API_CFUNC_c_errno,
    SPVM_API_CFUNC_c_set_errno,
    SPVM_API_CFUNC_c_fopen,
    SPVM_API_CFUNC_c_freopen,
    SPVM_API_CFUNC_c_fclose,
    SPVM_API_CFUNC_c_fread,
    SPVM_API_CFUNC_c_fwrite,
    SPVM_API_CFUNC_c_fflush,
    SPVM_API_CFUNC_c_fseek,
    SPVM_API_CFUNC_c_ftell,
    SPVM_API_CFUNC_c_feof,
    SPVM_API_CFUNC_c_ferror,
    SPVM_API_CFUNC_c_fileno,
    SPVM_API_CFUNC_c_stdin,
    SPVM_API_CFUNC_c_stdout,
    SPVM_API_CFUNC_c_stderr,
    SPVM_API_CFUNC_c_getenv,
    SPVM_API_CFUNC_c_setenv,
    SPVM_API_CFUNC_c_unsetenv,
    SPVM_API_CFUNC_c__dupenv_s,
    SPVM_API_CFUNC_c__putenv_s,
    SPVM_API_CFUNC_c_localtime,
    SPVM_API_CFUNC_c_tzset,
    SPVM_API_CFUNC_c_malloc,
    SPVM_API_CFUNC_c_calloc,
    SPVM_API_CFUNC_c_realloc,
    SPVM_API_CFUNC_c_free,
    SPVM_API_CFUNC_c_localtime_r,
    SPVM_API_CFUNC_c_localtime_s,
    SPVM_API_CFUNC_c_gmtime_r,
    SPVM_API_CFUNC_c_gmtime_s,
    SPVM_API_CFUNC_c__wfopen,
    SPVM_API_CFUNC_c_fdopen,
    SPVM_API_CFUNC_c_popen,
    SPVM_API_CFUNC_c__wpopen,
    SPVM_API_CFUNC_c_pclose,
    SPVM_API_CFUNC_c__pclose,
  };
  SPVM_API_CFUNC* env_cfunc = calloc(1, sizeof(env_cfunc_init));
  memcpy(env_cfunc, env_cfunc_init, sizeof(env_cfunc_init));
  
  return env_cfunc;
}

void SPVM_API_CFUNC_free_api(SPVM_API_CFUNC* api) {
  free(api);
}

size_t SPVM_API_CFUNC_c_strlen(SPVM_ENV* env, SPVM_VALUE* stack, const char* str) {
  return strlen(str);
}

void* SPVM_API_CFUNC_c_memcpy(SPVM_ENV* env, SPVM_VALUE* stack, void* dest, const void* src, size_t n) {
  return memcpy(dest, src, n);
}

void* SPVM_API_CFUNC_c_memset(SPVM_ENV* env, SPVM_VALUE* stack, void* s, int c, size_t n) {
  return memset(s, c, n);
}

int SPVM_API_CFUNC_c_memcmp(SPVM_ENV* env, SPVM_VALUE* stack, const void* s1, const void* s2, size_t n) {
  return memcmp(s1, s2, n);
}

long long SPVM_API_CFUNC_c_strtoll(SPVM_ENV* env, SPVM_VALUE* stack, const char* str, char** endptr, int base) {
  return strtoll(str, endptr, base);
}

float SPVM_API_CFUNC_c_strtof(SPVM_ENV* env, SPVM_VALUE* stack, const char* str, char** endptr) {
  return strtof(str, endptr);
}

double SPVM_API_CFUNC_c_strtod(SPVM_ENV* env, SPVM_VALUE* stack, const char* str, char** endptr) {
  return strtod(str, endptr);
}

int SPVM_API_CFUNC_c_fputs(SPVM_ENV* env, SPVM_VALUE* stack, const char* s, void* stream) {
  return fputs(s, (FILE*)stream);
}

int SPVM_API_CFUNC_c_fgetc(SPVM_ENV* env, SPVM_VALUE* stack, void* stream) {
  return fgetc((FILE*)stream);
}

int SPVM_API_CFUNC_c_snprintf_len(SPVM_ENV* env, SPVM_VALUE* stack, char* str, size_t size, const char* format, SPVM_VALUE* args, int32_t args_length) {
  if (!format) {
    return -1;
  }

  int32_t total_len = 0;
  int32_t arg_index = 0;
  const char* p = format;
  char* dst = str;
  size_t left = size;

  while (*p) {
    if (*p == '%' && *(p + 1) != '%') {
      /* Start parsing */
      const char* start = p;
      p++;

      /* Flags, width, precision */
      while (*p && (strchr("-+ #0123456789.", *p))) {
        p++;
      }

      /* Length modifiers */
      int32_t is_64bit = 0;
      if (*p == 'l') {
        p++;
        is_64bit = 1; /* long or long long */
        if (*p == 'l') {
          p++;
        }
      } else if (*p == 'j' || *p == 'z' || *p == 't') {
        is_64bit = 1; /* intmax_t, size_t, ptrdiff_t */
        p++;
      } else if (*p == 'h') {
        p++;
        if (*p == 'h') p++;
      } else if (*p == 'L') {
        p++;
      }

      /* Specifier */
      char type = *p;
      if (type) p++;

      if (arg_index >= args_length) {
        return -1;
      }

      /* Sub-format string */
      char sub_fmt[64];
      size_t fmt_len = p - start;
      if (fmt_len > 63) fmt_len = 63;
      memcpy(sub_fmt, start, fmt_len);
      sub_fmt[fmt_len] = '\0';

      int32_t written = 0;
      SPVM_VALUE value = args[arg_index++];

      /* Dispatch by type */
      if (type == 's') {
        written = snprintf(dst, left, sub_fmt, (char*)value.address);
      } else if (type == 'd' || type == 'i') {
        if (is_64bit) written = snprintf(dst, left, sub_fmt, value.lval);
        else written = snprintf(dst, left, sub_fmt, value.ival);
      } else if (type == 'u' || type == 'x' || type == 'X' || type == 'o') {
        if (is_64bit) written = snprintf(dst, left, sub_fmt, (unsigned long long)value.lval);
        else written = snprintf(dst, left, sub_fmt, (unsigned int)value.ival);
      } else if (type == 'f' || type == 'g' || type == 'G' || type == 'e' || type == 'E') {
        written = snprintf(dst, left, sub_fmt, value.dval);
      } else if (type == 'p') {
        written = snprintf(dst, left, sub_fmt, value.address);
      } else if (type == 'c') {
        written = snprintf(dst, left, sub_fmt, value.ival);
      } else {
        return -1;
      }

      if (written < 0) return -1;
      total_len += written;
      
      if ((size_t)written < left) {
        dst += written;
        left -= written;
      } else {
        if (left > 0) {
          dst += (left - 1);
          left = 1;
        }
      }
    } else {
      /* Literal */
      if (*p == '%' && *(p + 1) == '%') p++;
      
      if (left > 1) {
        *dst++ = *p;
        left--;
      }
      p++;
      total_len++;
    }
  }

  /* Null-termination */
  if (size > 0) {
    if (left > 0) {
      *dst = '\0';
    } else {
      str[size - 1] = '\0';
    }
  }

  return total_len;
}

int SPVM_API_CFUNC_c_errno(SPVM_ENV* env, SPVM_VALUE* stack) {
  return errno;
}

void SPVM_API_CFUNC_c_set_errno(SPVM_ENV* env, SPVM_VALUE* stack, int errno_value) {
  errno = errno_value;
}

int SPVM_API_CFUNC_c_fflush(SPVM_ENV* env, SPVM_VALUE* stack, FILE* stream) {
  return fflush(stream);
}

FILE* SPVM_API_CFUNC_c_fopen(SPVM_ENV* env, SPVM_VALUE* stack, const char* path, const char* mode) {
  return fopen(path, mode);
}

FILE* SPVM_API_CFUNC_c_freopen(SPVM_ENV* env, SPVM_VALUE* stack, const char* path, const char* mode, FILE* stream) {
  return freopen(path, mode, stream);
}

int SPVM_API_CFUNC_c_fclose(SPVM_ENV* env, SPVM_VALUE* stack, FILE* stream) {
  return fclose(stream);
}

size_t SPVM_API_CFUNC_c_fread(SPVM_ENV* env, SPVM_VALUE* stack, void* ptr, size_t size, size_t nmemb, FILE* stream) {
  return fread(ptr, size, nmemb, stream);
}

size_t SPVM_API_CFUNC_c_fwrite(SPVM_ENV* env, SPVM_VALUE* stack, const void* ptr, size_t size, size_t nmemb, FILE* stream) {
  return fwrite(ptr, size, nmemb, stream);
}

int SPVM_API_CFUNC_c_fseek(SPVM_ENV* env, SPVM_VALUE* stack, FILE* stream, long offset, int whence) {
  return fseek(stream, offset, whence);
}

long SPVM_API_CFUNC_c_ftell(SPVM_ENV* env, SPVM_VALUE* stack, FILE* stream) {
  return ftell(stream);
}

int SPVM_API_CFUNC_c_feof(SPVM_ENV* env, SPVM_VALUE* stack, FILE* stream) {
  return feof(stream);
}

int SPVM_API_CFUNC_c_ferror(SPVM_ENV* env, SPVM_VALUE* stack, FILE* stream) {
  return ferror(stream);
}

int SPVM_API_CFUNC_c_fileno(SPVM_ENV* env, SPVM_VALUE* stack, FILE* stream) {
  return fileno(stream);
}

FILE* SPVM_API_CFUNC_c_stdin(SPVM_ENV* env, SPVM_VALUE* stack) {
  return stdin;
}

FILE* SPVM_API_CFUNC_c_stdout(SPVM_ENV* env, SPVM_VALUE* stack) {
  return stdout;
}

FILE* SPVM_API_CFUNC_c_stderr(SPVM_ENV* env, SPVM_VALUE* stack) {
  return stderr;
}

char* SPVM_API_CFUNC_c_getenv(SPVM_ENV* env, SPVM_VALUE* stack, const char* name) {
  return getenv(name);
}

int SPVM_API_CFUNC_c_setenv(SPVM_ENV* env, SPVM_VALUE* stack, const char* name, const char* value, int overwrite) {
#ifndef _WIN32
  return setenv(name, value, overwrite);
#else
  abort();
#endif
}

int SPVM_API_CFUNC_c_unsetenv(SPVM_ENV* env, SPVM_VALUE* stack, const char* name) {
#ifndef _WIN32
  return unsetenv(name);
#else
  abort();
#endif
}

int SPVM_API_CFUNC_c__dupenv_s(SPVM_ENV* env, SPVM_VALUE* stack, char** buffer, size_t* numberOfElements, const char* varname) {
#ifdef _WIN32
  return _dupenv_s(buffer, numberOfElements, varname);
#else
  abort();
#endif
}

int SPVM_API_CFUNC_c__putenv_s(SPVM_ENV* env, SPVM_VALUE* stack, const char* name, const char* value) {
#ifdef _WIN32
  return _putenv_s(name, value);
#else
  abort();
#endif
}

struct tm* SPVM_API_CFUNC_c_localtime(SPVM_ENV* env, SPVM_VALUE* stack, const time_t* timer) {
  return localtime(timer);
}

void SPVM_API_CFUNC_c_tzset(SPVM_ENV* env, SPVM_VALUE* stack) {
  tzset();
}

void* SPVM_API_CFUNC_c_malloc(SPVM_ENV* env, SPVM_VALUE* stack, size_t size) {
  return malloc(size);
}

void* SPVM_API_CFUNC_c_calloc(SPVM_ENV* env, SPVM_VALUE* stack, size_t nmemb, size_t size) {
  return calloc(nmemb, size);
}

void* SPVM_API_CFUNC_c_realloc(SPVM_ENV* env, SPVM_VALUE* stack, void* ptr, size_t size) {
  return realloc(ptr, size);
}

void SPVM_API_CFUNC_c_free(SPVM_ENV* env, SPVM_VALUE* stack, void* ptr) {
  free(ptr);
}

struct tm* SPVM_API_CFUNC_c_localtime_r(SPVM_ENV* env, SPVM_VALUE* stack, const time_t* timer, struct tm* result) {
#ifndef _WIN32
  return localtime_r(timer, result);
#else
  abort();
#endif
}

int SPVM_API_CFUNC_c_localtime_s(SPVM_ENV* env, SPVM_VALUE* stack, struct tm* result, const time_t* timer) {
#ifdef _WIN32
  return localtime_s(result, timer);
#else
  abort();
#endif
}

struct tm* SPVM_API_CFUNC_c_gmtime_r(SPVM_ENV* env, SPVM_VALUE* stack, const time_t* timer, struct tm* result) {
#ifndef _WIN32
  return gmtime_r(timer, result);
#else
  abort();
#endif
}

int SPVM_API_CFUNC_c_gmtime_s(SPVM_ENV* env, SPVM_VALUE* stack, struct tm* result, const time_t* timer) {
#ifdef _WIN32
  return gmtime_s(result, timer);
#else
  abort();
#endif
}

FILE* SPVM_API_CFUNC_c__wfopen(SPVM_ENV* env, SPVM_VALUE* stack, const wchar_t* path, const wchar_t* mode) {
#ifdef _WIN32
  return _wfopen(path, mode);
#else
  abort();
#endif
}

FILE* SPVM_API_CFUNC_c_fdopen(SPVM_ENV* env, SPVM_VALUE* stack, int fd, const char* mode) {
  return fdopen(fd, mode);
}

FILE* SPVM_API_CFUNC_c_popen(SPVM_ENV* env, SPVM_VALUE* stack, const char* command, const char* type) {
#ifndef _WIN32
  return popen(command, type);
#else
  abort();
#endif
}

FILE* SPVM_API_CFUNC_c__wpopen(SPVM_ENV* env, SPVM_VALUE* stack, const wchar_t* command, const wchar_t* type) {
#ifdef _WIN32
  return _wpopen(command, type);
#else
  abort();
#endif
}

int SPVM_API_CFUNC_c_pclose(SPVM_ENV* env, SPVM_VALUE* stack, FILE* stream) {
#ifndef _WIN32
  return pclose(stream);
#else
  abort();
#endif
}

int SPVM_API_CFUNC_c__pclose(SPVM_ENV* env, SPVM_VALUE* stack, FILE* stream) {
#ifdef _WIN32
  return _pclose(stream);
#else
  abort();
#endif
}

void SPVM_API_CFUNC_c_clearerr(SPVM_ENV* env, SPVM_VALUE* stack, FILE* stream) {
  clearerr(stream);
}

int SPVM_API_CFUNC_c_getc(SPVM_ENV* env, SPVM_VALUE* stack, FILE* stream) {
  return getc(stream);
}

int SPVM_API_CFUNC_c_ungetc(SPVM_ENV* env, SPVM_VALUE* stack, int c, FILE* stream) {
  return ungetc(c, stream);
}

char* SPVM_API_CFUNC_c_fgets(SPVM_ENV* env, SPVM_VALUE* stack, char* s, int size, FILE* stream) {
  return fgets(s, size, stream);
}

int SPVM_API_CFUNC_c_setvbuf(SPVM_ENV* env, SPVM_VALUE* stack, FILE* stream, char* buf, int mode, size_t size) {
  return setvbuf(stream, buf, mode, size);
}

int SPVM_API_CFUNC_c_open(SPVM_ENV* env, SPVM_VALUE* stack, const char* pathname, int flags, int mode) {
  return open(pathname, flags, mode);
}

int SPVM_API_CFUNC_c_read(SPVM_ENV* env, SPVM_VALUE* stack, int fd, void* buf, size_t count) {
  return read(fd, buf, count);
}

int SPVM_API_CFUNC_c_write(SPVM_ENV* env, SPVM_VALUE* stack, int fd, const void* buf, size_t count) {
  return write(fd, buf, count);
}

off_t SPVM_API_CFUNC_c_lseek(SPVM_ENV* env, SPVM_VALUE* stack, int fd, off_t offset, int whence) {
  return lseek(fd, offset, whence);
}

int SPVM_API_CFUNC_c_close(SPVM_ENV* env, SPVM_VALUE* stack, int fd) {
  return close(fd);
}

FILE* SPVM_API_CFUNC_c__popen(SPVM_ENV* env, SPVM_VALUE* stack, const wchar_t* command, const wchar_t* type) {
#ifdef _WIN32
  return _popen(command, type);
#else
  abort();
#endif
}

int SPVM_API_CFUNC_c__wopen(SPVM_ENV* env, SPVM_VALUE* stack, const wchar_t* filename, int oflag, int pmode) {
#ifdef _WIN32
  return _wopen(filename, oflag, pmode);
#else
  abort();
#endif
}

int SPVM_API_CFUNC_c__open(SPVM_ENV* env, SPVM_VALUE* stack, const char* filename, int oflag, int pmode) {
#ifdef _WIN32
  return _open(filename, oflag, pmode);
#else
  abort();
#endif
}

int SPVM_API_CFUNC_c__close(SPVM_ENV* env, SPVM_VALUE* stack, int fd) {
#ifdef _WIN32
  return _close(fd);
#else
  abort();
#endif
}

int SPVM_API_CFUNC_c__read(SPVM_ENV* env, SPVM_VALUE* stack, int fd, void* buffer, unsigned int count) {
#ifdef _WIN32
  return _read(fd, buffer, count);
#else
  abort();
#endif
}

int SPVM_API_CFUNC_c__write(SPVM_ENV* env, SPVM_VALUE* stack, int fd, const void* buffer, unsigned int count) {
#ifdef _WIN32
  return _write(fd, buffer, count);
#else
  abort();
#endif
}

long SPVM_API_CFUNC_c__lseek(SPVM_ENV* env, SPVM_VALUE* stack, int fd, long offset, int origin) {
#ifdef _WIN32
  return _lseek(fd, offset, origin);
#else
  abort();
#endif
}

int SPVM_API_CFUNC_c__fileno(SPVM_ENV* env, SPVM_VALUE* stack, FILE* stream) {
#ifdef _WIN32
  return _fileno(stream);
#else
  abort();
#endif
}

FILE* SPVM_API_CFUNC_c__fdopen(SPVM_ENV* env, SPVM_VALUE* stack, int fd, const char* mode) {
#ifdef _WIN32
  return _fdopen(fd, mode);
#else
  abort();
#endif
}

int SPVM_API_CFUNC_c__access(SPVM_ENV* env, SPVM_VALUE* stack, const char* path, int mode) {
#ifdef _WIN32
  return _access(path, mode);
#else
  abort();
#endif
}

int SPVM_API_CFUNC_c__chdir(SPVM_ENV* env, SPVM_VALUE* stack, const char* path) {
#ifdef _WIN32
  return _chdir(path);
#else
  abort();
#endif
}

int SPVM_API_CFUNC_c__chmod(SPVM_ENV* env, SPVM_VALUE* stack, const char* filename, int pmode) {
#ifdef _WIN32
  return _chmod(filename, pmode);
#else
  abort();
#endif
}

int SPVM_API_CFUNC_c__closedir(SPVM_ENV* env, SPVM_VALUE* stack, void* dir) {
#ifdef _WIN32
  return _closedir(dir);
#else
  abort();
#endif
}

int SPVM_API_CFUNC_c__commit(SPVM_ENV* env, SPVM_VALUE* stack, int fd) {
#ifdef _WIN32
  return _commit(fd);
#else
  abort();
#endif
}

char* SPVM_API_CFUNC_c__fullpath(SPVM_ENV* env, SPVM_VALUE* stack, char* absPath, const char* relPath, size_t maxLength) {
#ifdef _WIN32
  return _fullpath(absPath, relPath, maxLength);
#else
  abort();
#endif
}

char* SPVM_API_CFUNC_c__getcwd(SPVM_ENV* env, SPVM_VALUE* stack, char* buffer, int maxlen) {
#ifdef _WIN32
  return _getcwd(buffer, maxlen);
#else
  abort();
#endif
}

char* SPVM_API_CFUNC_c__getdcwd(SPVM_ENV* env, SPVM_VALUE* stack, int drive, char* buffer, int maxlen) {
#ifdef _WIN32
  return _getdcwd(drive, buffer, maxlen);
#else
  abort();
#endif
}

int SPVM_API_CFUNC_c__mkdir(SPVM_ENV* env, SPVM_VALUE* stack, const char* dirname) {
#ifdef _WIN32
  return _mkdir(dirname);
#else
  abort();
#endif
}

void* SPVM_API_CFUNC_c__opendir(SPVM_ENV* env, SPVM_VALUE* stack, const char* name) {
#ifdef _WIN32
  return _opendir(name);
#else
  abort();
#endif
}

void* SPVM_API_CFUNC_c__readdir(SPVM_ENV* env, SPVM_VALUE* stack, void* dir) {
#ifdef _WIN32
  return _readdir(dir);
#else
  abort();
#endif
}

int SPVM_API_CFUNC_c__rename(SPVM_ENV* env, SPVM_VALUE* stack, const char* oldname, const char* newname) {
#ifdef _WIN32
  return _rename(oldname, newname);
#else
  abort();
#endif
}

int SPVM_API_CFUNC_c__rmdir(SPVM_ENV* env, SPVM_VALUE* stack, const char* dirname) {
#ifdef _WIN32
  return _rmdir(dirname);
#else
  abort();
#endif
}

int SPVM_API_CFUNC_c__unlink(SPVM_ENV* env, SPVM_VALUE* stack, const char* filename) {
#ifdef _WIN32
  return _unlink(filename);
#else
  abort();
#endif
}
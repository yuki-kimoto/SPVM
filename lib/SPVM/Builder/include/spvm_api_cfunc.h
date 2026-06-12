// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_API_CFUNC_H
#define SPVM_API_CFUNC_H

#include "spvm_typedecl.h"
#include "spvm_native.h"
#include <inttypes.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <ctype.h>
#include <stdarg.h>
#include <time.h>

SPVM_API_CFUNC* SPVM_API_CFUNC_new_api();

void SPVM_API_CFUNC_free_api(SPVM_API_CFUNC* cfunc);

size_t SPVM_API_c_strlen(SPVM_ENV* env, SPVM_VALUE* stack, const char* str);

void* SPVM_API_c_memcpy(SPVM_ENV* env, SPVM_VALUE* stack, void* dest, const void* src, size_t n);

void* SPVM_API_c_memset(SPVM_ENV* env, SPVM_VALUE* stack, void* s, int c, size_t n);

int SPVM_API_c_memcmp(SPVM_ENV* env, SPVM_VALUE* stack, const void* s1, const void* s2, size_t n);

long long SPVM_API_c_strtoll(SPVM_ENV* env, SPVM_VALUE* stack, const char* str, char** endptr, int base);

float SPVM_API_c_strtof(SPVM_ENV* env, SPVM_VALUE* stack, const char* str, char** endptr);

double SPVM_API_c_strtod(SPVM_ENV* env, SPVM_VALUE* stack, const char* str, char** endptr);

int SPVM_API_c_fputs(SPVM_ENV* env, SPVM_VALUE* stack, const char* s, void* stream);

int SPVM_API_c_fgetc(SPVM_ENV* env, SPVM_VALUE* stack, void* stream);

int SPVM_API_c_snprintf_len(SPVM_ENV* env, SPVM_VALUE* stack, char* str, size_t size, const char* format, SPVM_VALUE* args, int32_t args_length);

int SPVM_API_c_errno(SPVM_ENV* env, SPVM_VALUE* stack);

void SPVM_API_c_set_errno(SPVM_ENV* env, SPVM_VALUE* stack, int errno_value);

FILE* SPVM_API_c_fopen(SPVM_ENV* env, SPVM_VALUE* stack, const char* path, const char* mode);

FILE* SPVM_API_c_freopen(SPVM_ENV* env, SPVM_VALUE* stack, const char* path, const char* mode, FILE* stream);

int SPVM_API_c_fclose(SPVM_ENV* env, SPVM_VALUE* stack, FILE* stream);

size_t SPVM_API_c_fread(SPVM_ENV* env, SPVM_VALUE* stack, void* ptr, size_t size, size_t nmemb, FILE* stream);

size_t SPVM_API_c_fwrite(SPVM_ENV* env, SPVM_VALUE* stack, const void* ptr, size_t size, size_t nmemb, FILE* stream);

int SPVM_API_c_fflush(SPVM_ENV* env, SPVM_VALUE* stack, FILE* stream);

int SPVM_API_c_fseek(SPVM_ENV* env, SPVM_VALUE* stack, FILE* stream, long offset, int whence);

long SPVM_API_c_ftell(SPVM_ENV* env, SPVM_VALUE* stack, FILE* stream);

int SPVM_API_c_feof(SPVM_ENV* env, SPVM_VALUE* stack, FILE* stream);

int SPVM_API_c_ferror(SPVM_ENV* env, SPVM_VALUE* stack, FILE* stream);

int SPVM_API_c_fileno(SPVM_ENV* env, SPVM_VALUE* stack, FILE* stream);

FILE* SPVM_API_c_stdin(SPVM_ENV* env, SPVM_VALUE* stack);

FILE* SPVM_API_c_stdout(SPVM_ENV* env, SPVM_VALUE* stack);

FILE* SPVM_API_c_stderr(SPVM_ENV* env, SPVM_VALUE* stack);

char* SPVM_API_c_getenv(SPVM_ENV* env, SPVM_VALUE* stack, const char* name);

int SPVM_API_c_setenv(SPVM_ENV* env, SPVM_VALUE* stack, const char* name, const char* value, int overwrite);

int SPVM_API_c_unsetenv(SPVM_ENV* env, SPVM_VALUE* stack, const char* name);

int SPVM_API_c__dupenv_s(SPVM_ENV* env, SPVM_VALUE* stack, char** buffer, size_t* numberOfElements, const char* varname);

int SPVM_API_c__putenv_s(SPVM_ENV* env, SPVM_VALUE* stack, const char* name, const char* value);

struct tm* SPVM_API_c_localtime(SPVM_ENV* env, SPVM_VALUE* stack, const time_t* timer);

void SPVM_API_c_tzset(SPVM_ENV* env, SPVM_VALUE* stack);

void* SPVM_API_c_malloc(SPVM_ENV* env, SPVM_VALUE* stack, size_t size);

void* SPVM_API_c_calloc(SPVM_ENV* env, SPVM_VALUE* stack, size_t nmemb, size_t size);

void* SPVM_API_c_realloc(SPVM_ENV* env, SPVM_VALUE* stack, void* ptr, size_t size);

void SPVM_API_c_free(SPVM_ENV* env, SPVM_VALUE* stack, void* ptr);

struct tm* SPVM_API_c_localtime_r(SPVM_ENV* env, SPVM_VALUE* stack, const time_t* timer, struct tm* result);

int SPVM_API_c_localtime_s(SPVM_ENV* env, SPVM_VALUE* stack, struct tm* result, const time_t* timer);

struct tm* SPVM_API_c_gmtime_r(SPVM_ENV* env, SPVM_VALUE* stack, const time_t* timer, struct tm* result);

int SPVM_API_c_gmtime_s(SPVM_ENV* env, SPVM_VALUE* stack, struct tm* result, const time_t* timer);

FILE* SPVM_API_c__wfopen(SPVM_ENV* env, SPVM_VALUE* stack, const wchar_t* path, const wchar_t* mode);

FILE* SPVM_API_c_fdopen(SPVM_ENV* env, SPVM_VALUE* stack, int fd, const char* mode);

FILE* SPVM_API_c_popen(SPVM_ENV* env, SPVM_VALUE* stack, const char* command, const char* type);

FILE* SPVM_API_c__wpopen(SPVM_ENV* env, SPVM_VALUE* stack, const wchar_t* command, const wchar_t* type);

int SPVM_API_c_pclose(SPVM_ENV* env, SPVM_VALUE* stack, FILE* stream);

int SPVM_API_c__pclose(SPVM_ENV* env, SPVM_VALUE* stack, FILE* stream);

#endif

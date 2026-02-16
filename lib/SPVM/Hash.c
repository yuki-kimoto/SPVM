// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_native.h"

#include <stdint.h>
#include <assert.h>

#if defined(_WIN32)
#  include <windows.h>
#  include <bcrypt.h>
#elif defined(__linux__) || defined(__android__)
#  include <sys/random.h>
#  include <unistd.h>
#elif defined(__APPLE__) || defined(__FreeBSD__) || defined(__OpenBSD__)
#  include <stdlib.h>
#endif

// The follwoing algorithm is copied from https://github.com/python/cpython/blob/main/Python/pyhash.c
#define Py_ssize_t int64_t
#  define _le64toh(x) (((uint64_t)(x) << 56) | \
                      (((uint64_t)(x) << 40) & 0xff000000000000ULL) | \
                      (((uint64_t)(x) << 24) & 0xff0000000000ULL) | \
                      (((uint64_t)(x) << 8)  & 0xff00000000ULL) | \
                      (((uint64_t)(x) >> 8)  & 0xff000000ULL) | \
                      (((uint64_t)(x) >> 24) & 0xff0000ULL) | \
                      (((uint64_t)(x) >> 40) & 0xff00ULL) | \
                      ((uint64_t)(x)  >> 56))
#  define ROTATE(x, b) (uint64_t)( ((x) << (b)) | ( (x) >> (64 - (b))) )
#define HALF_ROUND(a,b,c,d,s,t)     \
    a += b; c += d;                 \
    b = ROTATE(b, s) ^ a;           \
    d = ROTATE(d, t) ^ c;           \
    a = ROTATE(a, 32);
#define SINGLE_ROUND(v0,v1,v2,v3)   \
    HALF_ROUND(v0,v1,v2,v3,13,16);  \
    HALF_ROUND(v2,v1,v0,v3,17,21);
static void
lcg_urandom(unsigned int x0, unsigned char *buffer, size_t size)
{
    size_t index;
    unsigned int x;

    x = x0;
    for (index=0; index < size; index++) {
        x *= 214013;
        x += 2531011;
        /* modulo 2 ^ (8 * sizeof(int)) */
        buffer[index] = (x >> 16) & 0xff;
    }
}
static uint64_t
siphash13(uint64_t k0, uint64_t k1, const void *src, Py_ssize_t src_sz) {
    uint64_t b = (uint64_t)src_sz << 56;
    const uint8_t *in = (const uint8_t*)src;

    uint64_t v0 = k0 ^ 0x736f6d6570736575ULL;
    uint64_t v1 = k1 ^ 0x646f72616e646f6dULL;
    uint64_t v2 = k0 ^ 0x6c7967656e657261ULL;
    uint64_t v3 = k1 ^ 0x7465646279746573ULL;

    uint64_t t;
    uint8_t *pt;

    while (src_sz >= 8) {
        uint64_t mi;
        memcpy(&mi, in, sizeof(mi));
        mi = _le64toh(mi);
        in += sizeof(mi);
        src_sz -= sizeof(mi);
        v3 ^= mi;
        SINGLE_ROUND(v0,v1,v2,v3);
        v0 ^= mi;
    }

    t = 0;
    pt = (uint8_t *)&t;
    switch (src_sz) {
        case 7: pt[6] = in[6]; /* fall through */
        case 6: pt[5] = in[5]; /* fall through */
        case 5: pt[4] = in[4]; /* fall through */
        case 4: memcpy(pt, in, sizeof(uint32_t)); break;
        case 3: pt[2] = in[2]; /* fall through */
        case 2: pt[1] = in[1]; /* fall through */
        case 1: pt[0] = in[0]; /* fall through */
    }
    b |= _le64toh(t);

    v3 ^= b;
    SINGLE_ROUND(v0,v1,v2,v3);
    v0 ^= b;
    v2 ^= 0xff;
    SINGLE_ROUND(v0,v1,v2,v3);
    SINGLE_ROUND(v0,v1,v2,v3);
    SINGLE_ROUND(v0,v1,v2,v3);

    /* modified */
    t = (v0 ^ v1) ^ (v2 ^ v3);
    return t;
}

int32_t SPVM__Hash__build_seed(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_self = stack[0].oval;
  
  int32_t seed_int32 = stack[1].ival;
  
  void* obj_seed = stack[2].oval;
  
  assert(obj_seed);
  
  char* seed = (char*)env->get_chars(env, stack, obj_seed);
  int32_t seed_length = env->length(env, stack, obj_seed);
  
  lcg_urandom((unsigned int)seed_int32, (unsigned char*)seed, seed_length);
  
  return 0;
}

int32_t SPVM__Hash___siphash13(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  void* object = stack[0].oval;
  const char* buf = env->get_chars(env, stack, object);
  uint32_t len = env->length(env, stack, object);

  void* obj_seed = stack[1].oval;
  const char* seed = env->get_chars(env, stack, obj_seed);
 
  uint64_t hash = siphash13(*(uint64_t*)seed, (*(uint64_t*)(seed + 8)), buf, len);
  
  stack[0].lval = hash;

  return 0;
}

/* Get OS-specific secure random bytes */
static int32_t get_os_secure_random(unsigned char *buffer, size_t size) {
#if defined(_WIN32)
  /* Windows: BCryptGenRandom */
  if (BCryptGenRandom(NULL, buffer, (ULONG)size, BCRYPT_USE_SYSTEM_PREFERRED_RNG) == 0) {
    return 1;
  }
#elif defined(__APPLE__) || defined(__FreeBSD__) || defined(__OpenBSD__)
  /* macOS, iOS, BSD: arc4random_buf */
  arc4random_buf(buffer, size);
  return 1;
#elif defined(__linux__) || defined(__android__)
  /* Linux, Android: getrandom */
  if (getrandom(buffer, size, 0) == (ssize_t)size) {
    return 1;
  }
#endif
  return 0;
}

int32_t SPVM__Hash__create_seed(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  // SipHash seed size is 16 bytes (128 bits)
  int32_t seed_length = 16;
  
  // Create a new string object for the seed
  void* obj_seed = env->new_string(env, stack, NULL, seed_length);
  unsigned char* seed = (unsigned char*)env->get_chars(env, stack, obj_seed);
  
  // Get secure random bytes from the OS
  int32_t success = get_os_secure_random(seed, (size_t)seed_length);
  
  // Assert that getting OS secure random was successful
  assert(success);
  
  stack[0].oval = obj_seed;
  
  return 0;
}

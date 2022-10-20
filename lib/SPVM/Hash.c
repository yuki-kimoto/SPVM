#include "spvm_native.h"

#include <assert.h>

// https://github.com/gcc-mirror/gcc/blob/master/libstdc++-v3/libsupc++/hash_bytes.cc#L72-L112
int32_t SPVM__Hash___murmur_hash(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  void* object = stack[0].oval;
  uint32_t seed = stack[1].ival;

  const char* buf = env->get_chars(env, stack, object);
  uint32_t len = env->length(env, stack, object);

  uint32_t m = 0x5bd1e995;
  uint32_t hash = seed ^ len;

  // Mix 4 bytes at a time into the hash.
  while(len >= 4) {
    uint32_t k;
    memcpy(&k, buf, sizeof(k));
    k *= m;
    k ^= k >> 24;
    k *= m;
    hash *= m;
    hash ^= k;
    buf += 4;
    len -= 4;
  }

  // Handle the last few bytes of the input array.
  switch(len) {
    case 3:
      hash ^= (unsigned char)buf[2] << 16;
    case 2:
      hash ^= (unsigned char)buf[1] << 8;
    case 1:
      hash ^= (unsigned char)buf[0];
      hash *= m;
    };

  // Do a few final mixes of the hash.
  hash ^= hash >> 13;
  hash *= m;
  hash ^= hash >> 15;
  stack[0].lval = hash; // return a long value to ensure being positive.

  return 0;
}

// The follwoing algorithm is copied from https://github.com/python/cpython/blob/main/Python/pyhash.c
#define Py_ssize_t ssize_t
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

int32_t SPVM__Hash__build_seed128(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_self = stack[0].oval;
  
  int32_t seed_int32 = stack[1].ival;
  
  void* obj_seed128 = stack[2].oval;
  
  assert(obj_seed128);
  
  char* seed128 = (char*)env->get_chars(env, stack, obj_seed128);
  int32_t seed128_length = env->length(env, stack, obj_seed128);
  
  lcg_urandom((unsigned int)seed_int32, seed128, seed128_length);
  
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

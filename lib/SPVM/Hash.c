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

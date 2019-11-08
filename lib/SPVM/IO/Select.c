#ifndef _XOPEN_SOURCE
#  define _XOPEN_SOURCE
#endif

#include "spvm_native.h"

#ifdef _WIN32
  #include <winsock.h>
#else
  #include <sys/types.h>
  #include <sys/time.h>
#endif

#include <math.h>

// Module file name
static const char* MFILE = "SPVM/IO/Select.c";

int32_t SPNATIVE__SPVM__IO__Select___can_read(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  // Self
  void* obj_self = stack[0].oval;
  
  // Handles
  void* obj_handles = stack[1].oval;
  int32_t* handles = env->get_elems_int(env, obj_handles);
  int32_t handles_len = env->length(env, obj_handles);
  
  // Timeout
  double timeout = stack[2].dval;
  double timeout_int;
  
  double timeout_fraction;
  timeout_fraction = modf(timeout, &timeout_int);
  struct timeval tv;
  tv.tv_sec = (int32_t)timeout_int;
  tv.tv_usec = (int32_t)(timeout_fraction * 1000000);
  
  // Set handles to fd_set
  fd_set fds;
  FD_ZERO(&fds);
  int32_t max_handle = 0;
  for (int32_t i = 0; i < handles_len; i++) {
    int32_t handle = handles[i];
    FD_SET(handle, &fds);
    if (handle > max_handle) {
      max_handle = handle;
    }
  }
  
  // select
  int32_t success_count = select(max_handle + 1, &fds, NULL, NULL, &tv);
  
  // Error check
  if (success_count == -1) {
    SPVM_DIE("select fail", MFILE, __LINE__);
  }
  
  // Can handles
  void* obj_can_handles = env->new_iarray(env, success_count);
  int32_t* can_handles = env->get_elems_int(env, obj_can_handles);
  int32_t can_handles_index = 0;
  for (int32_t i = 0; i < handles_len; i++) {
    int32_t handle = handles[i];
    
    if (FD_ISSET(handle, &fds)) {
      can_handles[can_handles_index++] = handle;
    }
  }
  stack[0].oval = obj_can_handles;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__Select___can_write(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  // Self
  void* obj_self = stack[0].oval;
  
  // Handles
  void* obj_handles = stack[1].oval;
  int32_t* handles = env->get_elems_int(env, obj_handles);
  int32_t handles_len = env->length(env, obj_handles);
  
  // Timeout
  double timeout = stack[2].dval;
  double timeout_int;
  
  double timeout_fraction;
  timeout_fraction = modf(timeout, &timeout_int);
  struct timeval tv;
  tv.tv_sec = (int32_t)timeout_int;
  tv.tv_usec = (int32_t)(timeout_fraction * 1000000);
  
  // Set handles to fd_set
  fd_set fds;
  FD_ZERO(&fds);
  int32_t max_handle = 0;
  for (int32_t i = 0; i < handles_len; i++) {
    int32_t handle = handles[i];
    FD_SET(handle, &fds);
    if (handle > max_handle) {
      max_handle = handle;
    }
  }
  
  // select
  int32_t success_count = select(max_handle + 1, NULL, &fds, NULL, &tv);
  
  // Error check
  if (success_count == -1) {
    SPVM_DIE("select fail", MFILE, __LINE__);
  }
  
  // Can handles
  void* obj_can_handles = env->new_iarray(env, success_count);
  int32_t* can_handles = env->get_elems_int(env, obj_can_handles);
  int32_t can_handles_index = 0;
  for (int32_t i = 0; i < handles_len; i++) {
    int32_t handle = handles[i];
    
    if (FD_ISSET(handle, &fds)) {
      can_handles[can_handles_index++] = handle;
    }
  }
  stack[0].oval = obj_can_handles;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__Select___has_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  // Self
  void* obj_self = stack[0].oval;
  
  // Handles
  void* obj_handles = stack[1].oval;
  int32_t* handles = env->get_elems_int(env, obj_handles);
  int32_t handles_len = env->length(env, obj_handles);
  
  // Timeout
  double timeout = stack[2].dval;
  double timeout_int;
  
  double timeout_fraction;
  timeout_fraction = modf(timeout, &timeout_int);
  struct timeval tv;
  tv.tv_sec = (int32_t)timeout_int;
  tv.tv_usec = (int32_t)(timeout_fraction * 1000000);
  
  // Set handles to fd_set
  fd_set fds;
  FD_ZERO(&fds);
  int32_t max_handle = 0;
  for (int32_t i = 0; i < handles_len; i++) {
    int32_t handle = handles[i];
    FD_SET(handle, &fds);
    if (handle > max_handle) {
      max_handle = handle;
    }
  }
  
  
  // select
  int32_t success_count = select(max_handle + 1, NULL, NULL, &fds, &tv);
  
  // Error check
  if (success_count == -1) {
    SPVM_DIE("select fail", MFILE, __LINE__);
  }
  
  // Can handles
  void* obj_can_handles = env->new_iarray(env, success_count);
  int32_t* can_handles = env->get_elems_int(env, obj_can_handles);
  int32_t can_handles_index = 0;
  for (int32_t i = 0; i < handles_len; i++) {
    int32_t handle = handles[i];
    
    if (FD_ISSET(handle, &fds)) {
      can_handles[can_handles_index++] = handle;
    }
  }
  stack[0].oval = obj_can_handles;
  
  return SPVM_SUCCESS;
}

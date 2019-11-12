// Enable strerror_r, fileno
#ifndef _XOPEN_SOURCE
#  define _XOPEN_SOURCE 600
#endif

#include "spvm_native.h"

#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <errno.h>

static const char* MFILE = "SPVM/IO/File.c";

int32_t SPNATIVE__SPVM__IO__File__init_package_vars(SPVM_ENV* env, SPVM_VALUE* stack) {

  SPVM_SET_PACKAGE_VAR_INT(env, "SPVM::IO::File", "$SEEK_SET", SEEK_SET, MFILE, __LINE__);
  SPVM_SET_PACKAGE_VAR_INT(env, "SPVM::IO::File", "$SEEK_CUR", SEEK_CUR, MFILE, __LINE__);
  SPVM_SET_PACKAGE_VAR_INT(env, "SPVM::IO::File", "$SEEK_END", SEEK_END, MFILE, __LINE__);
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__File__fileno(SPVM_ENV* env, SPVM_VALUE* stack) {
  // Self
  void* obj_self = stack[0].oval;
  if (!obj_self) { SPVM_DIE("Self must be defined", MFILE, __LINE__); }
  
  // File fh
  void* obj_fh;
  SPVM_GET_FIELD_OBJECT(env, obj_fh, obj_self, "SPVM::IO::File", "fh", "SPVM::FileHandle", MFILE, __LINE__);
  FILE* fh = (FILE*)env->get_pointer(env, obj_fh);

  if (fh == NULL) { SPVM_DIE("File handle must be defined", MFILE, __LINE__); }
  
  int32_t fno = fileno(fh);
  
  stack[0].ival = fno;

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__File__readline(SPVM_ENV* env, SPVM_VALUE* stack) {
  // Self
  void* obj_self = stack[0].oval;
  if (!obj_self) { SPVM_DIE("Self must be defined", MFILE, __LINE__); }
  
  // File fh
  void* obj_fh;
  SPVM_GET_FIELD_OBJECT(env, obj_fh, obj_self, "SPVM::IO::File", "fh", "SPVM::FileHandle", MFILE, __LINE__);
  FILE* fh = (FILE*)env->get_pointer(env, obj_fh);

  if (fh == NULL) {
    stack[0].oval = NULL;
    return SPVM_SUCCESS;
  }
  
  int32_t scope_id = env->enter_scope(env);
  
  int32_t capacity = 80;
  void* obj_buffer = env->new_barray(env, capacity);
  int8_t* buffer = env->get_elems_byte(env, obj_buffer);
  
  int32_t pos = 0;
  int32_t end_is_eof = 0;
  while (1) {
    int32_t ch = fgetc(fh);
    if (ch == EOF) {
      end_is_eof = 1;
      break;
    }
    else {
      if (pos >= capacity) {
        // Extend buffer capacity
        int32_t new_capacity = capacity * 2;
        void* new_object_buffer = env->new_barray(env, new_capacity);
        int8_t* new_buffer = env->get_elems_byte(env, new_object_buffer);
        memcpy(new_buffer, buffer, capacity);
        
        int32_t removed = env->remove_mortal(env, scope_id, obj_buffer);
        assert(removed);
        
        capacity = new_capacity;
        obj_buffer = new_object_buffer;
        buffer = new_buffer;
      }
      
      if (ch == '\n') {
        buffer[pos] = ch;
        pos++;
        break;
      }
      else {
        buffer[pos] = ch;
        pos++;
      }
    }
  }
  
  if (pos > 0 || !end_is_eof) {
    void* oline;
    if (pos == 0) {
      oline = env->new_barray(env, 0);
    }
    else {
      oline = env->new_barray(env, pos);
      int8_t* line = env->get_elems_byte(env, oline);
      memcpy(line, buffer, pos);
    }
    
    stack[0].oval = oline;
  }
  else {
    stack[0].oval = NULL;
  }
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__File__seek(SPVM_ENV* env, SPVM_VALUE* stack) {

  // Self
  void* obj_self = stack[0].oval;
  if (!obj_self) { SPVM_DIE("Self must be defined", MFILE, __LINE__); }
  
  // File fh
  void* obj_fh;
  SPVM_GET_FIELD_OBJECT(env, obj_fh, obj_self, "SPVM::IO::File", "fh", "SPVM::FileHandle", MFILE, __LINE__);
  FILE* fh = (FILE*)env->get_pointer(env, obj_fh);
  
  // Offset
  int64_t offset = stack[1].lval;
  
  // origin
  int32_t origin = stack[2].ival;
  
  int32_t ret = fseek(fh, offset, origin);
  
  stack[0].ival = ret;

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__File__close(SPVM_ENV* env, SPVM_VALUE* stack) {

  // Self
  void* obj_self = stack[0].oval;
  if (!obj_self) { SPVM_DIE("Self must be defined", MFILE, __LINE__); }
  
  // File fh
  void* obj_fh;
  SPVM_GET_FIELD_OBJECT(env, obj_fh, obj_self, "SPVM::IO::File", "fh", "SPVM::FileHandle", MFILE, __LINE__);
  FILE* fh = (FILE*)env->get_pointer(env, obj_fh);
  
  if (fh) {
    int32_t ret = fclose(fh);
    
    env->set_pointer(env, obj_fh, NULL);
    
    stack[0].ival = ret;
  }
  else {
    stack[0].ival = EOF;
  }

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__File__read(SPVM_ENV* env, SPVM_VALUE* stack) {

  // Self
  void* obj_self = stack[0].oval;
  if (!obj_self) { SPVM_DIE("Self must be defined", MFILE, __LINE__); }
  
  // File fh
  void* obj_fh;
  SPVM_GET_FIELD_OBJECT(env, obj_fh, obj_self, "SPVM::IO::File", "fh", "SPVM::FileHandle", MFILE, __LINE__);
  FILE* fh = (FILE*)env->get_pointer(env, obj_fh);

  // Buffer
  void* obj_buffer = stack[1].oval;
  if (obj_buffer == NULL) {
    stack[0].oval = NULL;
    return SPVM_SUCCESS;
  }
  char* buffer = (char*)env->get_elems_byte(env, obj_buffer);
  int32_t buffer_length = env->length(env, obj_buffer);
  if (buffer_length == 0) {
    stack[0].ival = 0;
    return SPVM_SUCCESS;
  }
  
  int32_t read_length = fread(buffer, 1, buffer_length, fh);
  
  stack[0].ival = read_length;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__File__write(SPVM_ENV* env, SPVM_VALUE* stack) {

  // Self
  void* obj_self = stack[0].oval;
  if (!obj_self) { SPVM_DIE("Self must be defined", MFILE, __LINE__); }
  
  // File fh
  void* obj_fh;
  SPVM_GET_FIELD_OBJECT(env, obj_fh, obj_self, "SPVM::IO::File", "fh", "SPVM::FileHandle", MFILE, __LINE__);
  FILE* fh = (FILE*)env->get_pointer(env, obj_fh);

  int32_t length = stack[2].ival;

  // Buffer
  void* obj_buffer = stack[1].oval;
  if (obj_buffer == NULL) {
    stack[0].oval = NULL;
    return SPVM_SUCCESS;
  }
  char* buffer = (char*)env->get_elems_byte(env, obj_buffer);
  
  int32_t read_length = fwrite(buffer, 1, length, fh);
  
  stack[0].ival = read_length;

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__File__putc(SPVM_ENV* env, SPVM_VALUE* stack) {

  // Self
  void* obj_self = stack[0].oval;
  if (!obj_self) { SPVM_DIE("Self must be defined", MFILE, __LINE__); }
  
  // File fh
  void* obj_fh;
  SPVM_GET_FIELD_OBJECT(env, obj_fh, obj_self, "SPVM::IO::File", "fh", "SPVM::FileHandle", MFILE, __LINE__);
  FILE* fh = (FILE*)env->get_pointer(env, obj_fh);
  
  // Char
  char ch = (char)stack[0].bval;
  
  
  int32_t ret = fputc(ch, obj_fh);
  
  stack[0].ival = ret;

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__File__open(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  // File name
  void* obj_file_name = stack[0].oval;
  if (obj_file_name == NULL) {
    stack[0].oval = NULL;
    return SPVM_SUCCESS;
  }
  const char* file_name = (const char*)env->get_elems_byte(env, obj_file_name);
  
  // Mode
  void* omode = stack[1].oval;
  if (omode == NULL) {
    stack[0].oval = NULL;
    return SPVM_SUCCESS;
  }
  const char* mode = (const char*)env->get_elems_byte(env, omode);
  
  // Check mode
  int32_t valid_mode;
  if (strcmp(mode, "r") == 0) {
    valid_mode = 1;
  }
  else if (strcmp(mode, "w") == 0) {
    valid_mode = 1;
  }
  else if (strcmp(mode, "a") == 0) {
    valid_mode = 1;
  }
  else if (strcmp(mode, "rb") == 0) {
    valid_mode = 1;
  }
  else if (strcmp(mode, "wb") == 0) {
    valid_mode = 1;
  }
  else if (strcmp(mode, "ab") == 0) {
    valid_mode = 1;
  }
  else if (strcmp(mode, "r+") == 0) {
    valid_mode = 1;
  }
  else if (strcmp(mode, "w+") == 0) {
    valid_mode = 1;
  }
  else if (strcmp(mode, "a+") == 0) {
    valid_mode = 1;
  }
  else if (strcmp(mode, "r+b") == 0) {
    valid_mode = 1;
  }
  else if (strcmp(mode, "rb+") == 0) {
    valid_mode = 1;
  }
  else if (strcmp(mode, "w+b") == 0) {
    valid_mode = 1;
  }
  else if (strcmp(mode, "wb+") == 0) {
    valid_mode = 1;
  }
  else if (strcmp(mode, "a+b") == 0) {
    valid_mode = 1;
  }
  else if (strcmp(mode, "ab+") == 0) {
    valid_mode = 1;
  }
  else {
    valid_mode = 0;
  }
  if (!valid_mode) {
    SPVM_DIE("Invalid open mode", MFILE, __LINE__);
  }
  
  errno = 0;
  FILE* fh = fopen(file_name, mode);
  
  if (fh) {
    void* obj_io_file;
    SPVM_NEW_OBJECT(env, obj_io_file, "SPVM::IO::File", MFILE, __LINE__);

    void* obj_fh;
    SPVM_NEW_POINTER(env, obj_fh, "SPVM::FileHandle", fh, MFILE, __LINE__);
    SPVM_SET_FIELD_OBJECT(env, obj_io_file, "SPVM::IO::File", "fh", "SPVM::FileHandle", obj_fh, MFILE, __LINE__);
    
    stack[0].oval = obj_io_file;
  }
  else {
    char errstr[32];
#ifdef _WIN32
    strerror_s(errstr, 32, errno);
#else
    strerror_r(errno, errstr, 32);
#endif
    
    SPVM_DIE("Can't open file \"%s\": %s", file_name, errstr, MFILE, __LINE__);
  }
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__File__STDIN(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef stdin
  stack[0].ival = fileno(stdin);
#else
  SPVM_DIE("Errno STDIN is not defined", MFILE, __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__File__STDOUT(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef stdout
  stack[0].ival = fileno(stdout);
#else
  SPVM_DIE("Errno STDOUT is not defined", MFILE, __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__File__STDERR(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef stderr
  stack[0].ival = fileno(stderr);
#else
  SPVM_DIE("Errno STDERR is not defined", MFILE, __LINE__);
#endif

  return SPVM_SUCCESS;
}

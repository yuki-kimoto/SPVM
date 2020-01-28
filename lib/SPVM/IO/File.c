#include "spvm_native.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

static const char* MFILE = "SPVM/IO/File.c";

int32_t SPNATIVE__SPVM__IO__File__readline(SPVM_ENV* env, SPVM_VALUE* stack) {
  // Self
  void* obj_self = stack[0].oval;
  
  // File fh
  void* obj_fh;
  SPVM_GET_FIELD_OBJECT(env, obj_self, "SPVM::IO::File", "fh", "SPVM::IO::FileHandle", &obj_fh, MFILE, __LINE__);
  FILE* fh = (FILE*)env->get_pointer(env, obj_fh);

  if (fh == NULL) {
    stack[0].oval = NULL;
    return SPVM_SUCCESS;
  }
  
  int32_t scope_id = env->enter_scope(env);
  
  int32_t capacity = 80;
  void* obj_buffer = env->new_byte_array(env, capacity);
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
        void* new_object_buffer = env->new_byte_array(env, new_capacity);
        int8_t* new_buffer = env->get_elems_byte(env, new_object_buffer);
        memcpy(new_buffer, buffer, capacity);
        
        int32_t removed = env->remove_mortal(env, scope_id, obj_buffer);
        
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
      oline = env->new_byte_array(env, 0);
    }
    else {
      oline = env->new_byte_array(env, pos);
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

int32_t SPNATIVE__SPVM__IO__File__read(SPVM_ENV* env, SPVM_VALUE* stack) {

  // Self
  void* obj_self = stack[0].oval;
  
  // File fh
  void* obj_fh;
  SPVM_GET_FIELD_OBJECT(env, obj_self, "SPVM::IO::File", "fh", "SPVM::IO::FileHandle", &obj_fh, MFILE, __LINE__);
  FILE* fh = (FILE*)env->get_pointer(env, obj_fh);

  // Buffer
  void* obj_buffer = stack[1].oval;
  if (obj_buffer == NULL) {
    stack[0].ival = 0;
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

int32_t SPNATIVE__SPVM__IO__File__print(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  // Self
  void* obj_self = stack[0].oval;
  
  // File fh
  void* obj_fh;
  SPVM_GET_FIELD_OBJECT(env, obj_self, "SPVM::IO::File", "fh", "SPVM::IO::FileHandle", &obj_fh, MFILE, __LINE__);
  FILE* fh = (FILE*)env->get_pointer(env, obj_fh);
  
  void* string = stack[1].oval;
  
  const char* bytes = (const char*)env->get_elems_byte(env, string);
  int32_t string_length = env->length(env, string);
  
  // Print
  if (string_length > 0) {
    int32_t write_length = fwrite(bytes, 1, string_length, fh);
    if (write_length != string_length) {
      SPVM_DIE("Can't print string to file handle", MFILE, __LINE__);
    }
  }

  // Flush buffer to file handle if auto flush is true
  int8_t auto_flush;
  SPVM_GET_FIELD_BYTE(env, obj_self, "SPVM::IO::File", "auto_flush", &auto_flush, MFILE, __LINE__);
  if (auto_flush) {
    int32_t ret = fflush(fh);//SPVM::IO::File::print (Don't remove this comment for tests)
    if (ret != 0) {
      SPVM_DIE("Can't flush buffer to file handle", MFILE, __LINE__);
    }
  }
  
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
  const char* real_mode = NULL;
  if (strcmp(mode, "<") == 0) {
    valid_mode = 1;
    real_mode = "rb";
  }
  else if (strcmp(mode, ">") == 0) {
    valid_mode = 1;
    real_mode = "wb";
  }
  else if (strcmp(mode, ">>") == 0) {
    valid_mode = 1;
    real_mode = "wa";
  }
  else if (strcmp(mode, "+<") == 0) {
    valid_mode = 1;
    real_mode = "r+b";
  }
  else if (strcmp(mode, "+>") == 0) {
    valid_mode = 1;
    real_mode = "w+b";
  }
  else if (strcmp(mode, "+>>") == 0) {
    valid_mode = 1;
    real_mode = "a+b";
  }
  else {
    valid_mode = 0;
  }
  if (!valid_mode) {
    SPVM_DIE("Invalid open mode %s", mode, MFILE, __LINE__);
  }
  
  errno = 0;
  FILE* fh = fopen(file_name, real_mode);
  
  if (fh) {
    void* obj_io_file;
    SPVM_NEW_OBJECT(env, obj_io_file, "SPVM::IO::File", MFILE, __LINE__);

    void* obj_fh;
    SPVM_NEW_POINTER(env, obj_fh, "SPVM::IO::FileHandle", fh, MFILE, __LINE__);
    SPVM_SET_FIELD_OBJECT(env, obj_io_file, "SPVM::IO::File", "fh", "SPVM::IO::FileHandle", obj_fh, MFILE, __LINE__);
    
    stack[0].oval = obj_io_file;
  }
  else {
    const char* errstr = strerror(errno);
    
    SPVM_DIE("Can't open file \"%s\": %s", file_name, errstr, MFILE, __LINE__);
  }
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__File__flush(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  // Self
  void* obj_self = stack[0].oval;
  
  // File fh
  void* obj_fh;
  SPVM_GET_FIELD_OBJECT(env, obj_self, "SPVM::IO::File", "fh", "SPVM::IO::FileHandle", &obj_fh, MFILE, __LINE__);
  FILE* fh = (FILE*)env->get_pointer(env, obj_fh);
  
  int32_t ret = fflush(fh);
  
  if (ret != 0) {
    SPVM_DIE("Can't flash to file", MFILE, __LINE__);
  }
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__File__unlink(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  // File
  void* obj_file = stack[0].oval;
  if (!obj_file) { SPVM_DIE("File name must be defined", MFILE, __LINE__); }
  const char* file = (const char*)env->get_elems_byte(env, obj_file);
  
  int32_t ret = remove(file);
  
  if (ret != 0) {
    SPVM_DIE("Can't remove file %s", file, MFILE, __LINE__);
  }
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__File__rename(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  // Srouce src_file
  void* obj_src_file = stack[0].oval;
  if (!obj_src_file) { SPVM_DIE("Source file name must be defined", MFILE, __LINE__); }
  const char* src_file = (const char*)env->get_elems_byte(env, obj_src_file);

  // Dist dist_file
  void* obj_dist_file = stack[1].oval;
  if (!obj_dist_file) { SPVM_DIE("Dist file name must be defined", MFILE, __LINE__); }
  const char* dist_file = (const char*)env->get_elems_byte(env, obj_dist_file);
  
  int32_t ret = rename(src_file, dist_file);
  
  if (ret != 0) {
    SPVM_DIE("Can't rename %s to %s", src_file, dist_file, MFILE, __LINE__);
  }
  
  return SPVM_SUCCESS;
}
